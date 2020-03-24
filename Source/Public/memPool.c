
#include	"memPool.h"
#include  <string.h>

#define		Debug(fmt,args...)	  USART_Debug(1,"MemPool.c",__LINE__,fmt,##args)

#define		LIST_TAIL			1
#define     PACKAGE_SIZE        (1024*8)
#define		NODE_MAX			(PACKAGE_SIZE / POOL_BUFF_SIZE)
#define     LIST_MAX            7

__align(4) static  volatile u32     MemLock[LIST_MAX];
__align(4) static  MemPackage_ST   *MemList[LIST_MAX];
__align(4) static  MemPackage_ST   *MemTail[LIST_MAX];
__align(4) static  MemPackage_ST   MemPool[NODE_MAX];

void	MemPool_GetKey(u8 id)
{
    while(MemLock[id])
	{
		__nop();
		__nop();
		__nop();
		__nop();
		__nop();
		__nop();
		__nop();
		__nop();
		__nop();
		__nop();
	}
    MemLock[id] =1;
}
void	MemPool_FreeKey(u8 id)
{
    MemLock[id] =0;
}

void	MemPool_Init(void)
{
	u8	i;
	for(i=0;i<NODE_MAX-1;i++)
	{
		MemPool[i].isFull =0;
        MemPool[i].pNext  =&MemPool[i+1];
	}
    MemPool[NODE_MAX-1].isFull =0;
    MemPool[NODE_MAX-1].pNext  =NULL;

    for(i=0;i<LIST_MAX;i++)
    {
        MemList[i] =NULL;
		MemTail[i] =NULL;
        MemLock[i] =0;
    }
    MemList[FreeListID] =&MemPool[0];
	MemTail[FreeListID] =&MemPool[NODE_MAX-1];
}

MemPackage_ST	*MemPool_GetNode(void)
{
	MemPackage_ST *temp=NULL;
	MemPool_GetKey(FreeListID);
	if(MemList[FreeListID] !=NULL)
	{
		temp  =MemList[FreeListID];
		MemList[FreeListID] =MemList[FreeListID]->pNext;
		temp->pNext =NULL;
#ifdef	LIST_TAIL
		if(temp == MemTail[FreeListID])
		{
			MemTail[FreeListID] =NULL;
		}
#endif
	}
	else
	{
		Debug("memory pool is empty\n");
	}
	MemPool_FreeKey(FreeListID);
	return temp;
}

void	MemPool_FreeNode(MemPackage_ST	*pNode)
{
	MemPackage_ST *temp=NULL;
    MemPackage_ST *bklist=NULL;
	pNode->isFull =0;
	pNode->pNext  =NULL;
	MemPool_GetKey(FreeListID);
#ifndef LIST_TAIL
	if(MemList[FreeListID] !=NULL)
	{
		temp	=MemList[FreeListID];
		while(temp)
		{
			bklist =temp;
			temp =temp->pNext;
		}
		bklist->pNext =pNode;
	}
	else
	{
		MemList[FreeListID] =pNode;
	}
#else
	if(MemTail[FreeListID] !=NULL)
	{
		MemTail[FreeListID]->pNext =pNode;
	}
	else if(MemList[FreeListID] == NULL)
	{
		MemTail[FreeListID] =MemList[FreeListID]=pNode;
	}
	else
	{
		Debug("anything is wrong\n");
	}
	
#endif
	MemPool_FreeKey(FreeListID);
}


u8	MemPool_WriteNode(u8 id,u8 *pbuff,u8 len)
{
	u8  IsOk =0;
	MemPackage_ST	*pWrite,*pAddList,*pBkList;
	pWrite =MemPool_GetNode();
	if(pWrite !=NULL)
	{
		pWrite->isFull	=len;
        IsOk =len;
		memcpy(pWrite->Buff,pbuff,len);
		MemPool_GetKey(id);    
#ifndef	LIST_TAIL  
		if(MemList[id] !=NULL)
		{
			pAddList	=MemList[id];
			while(pAddList)
			{
				pBkList  =pAddList;
				pAddList =pAddList->pNext;
			}
			pBkList->pNext =pWrite;
		}
		else
		{
			MemList[id] =pWrite;
		}
#else
		if(MemTail[id] !=NULL)
		{
			MemTail[id]->pNext =pWrite;
		}
		else if(MemList[id] == NULL)
		{
			MemList[id] =MemTail[id] =pWrite;	
		}
		else
		{
			Debug("anything is wrong\n");
		}				
#endif
		MemPool_FreeKey(id);
	}
	return IsOk;
}

void	MemPool_WriteBytes(u8 id,u8 *pbuff,u8 len)
{
	u8  wrlen;
    while((id < LIST_MAX)&&(id > 0) && (len > 0))
    {
        if(len > POOL_BUFF_SIZE)	wrlen =POOL_BUFF_SIZE;
        else			            wrlen =len;			
        if(MemPool_WriteNode(id,pbuff, wrlen))
        {
            pbuff	+=wrlen;
            len 	-=wrlen;
        }
        else
        {
            Debug("get memory Node failed\r\n");
            len =0;
        }
    }
}


u8	MemPool_ReadNode(u8 id,u8 *pbuff)
{
	u8  rlen =0;
    MemPackage_ST	*pRead=NULL;
    MemPool_GetKey(id);        
    if(MemList[id] !=NULL)
    {
        pRead	=MemList[id];
        MemList[id] =MemList[id]->pNext;
#ifdef LIST_TAIL
		if( pRead== MemTail[id])
		{
			MemTail[id] =NULL;
		}
#endif
    }
    MemPool_FreeKey(id);
    if(pRead != NULL)
    {
        rlen =pRead->isFull;
        memcpy(pbuff,pRead->Buff,pRead->isFull);
        MemPool_FreeNode(pRead);
    }
	return rlen;
}


u8	MemPool_ReadBytes(u8 id,u8 *pRbuff,u8 len)
{
	u8  rlen,glen=0;
    len    =(len / POOL_BUFF_SIZE) * POOL_BUFF_SIZE;
    while((id < LIST_MAX)&&(id > 0) && (len > 0))
    {
        rlen  =MemPool_ReadNode(id,pRbuff);		
        if(rlen !=0)
        {
            pRbuff	+=rlen;
            len 	-=rlen;
            glen    +=rlen;
        }
        else
        {
            len  =0;
        }
    }
    return glen;
}

