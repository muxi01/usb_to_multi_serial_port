

#include "misc.h"
#include "stm32f10x.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_usart.h"
#include "stm32f10x_dma.h"
#include "USART_Dev.h"

#define     UART1_PORT            GPIOA 
#define     USART1_TX_PIN         9
#define     USART1_RX_PIN         10
#define     TX_IO_MODE            GPIO_Mode_AF_OD       //GPIO_Mode_AF_PP
#define     RX_IO_MODE            GPIO_Mode_IPU         //GPIO_Mode_IN_FLOATING

static ST_USART_RX_BUFF   rxbuff[3];

static void USART1_Init(u32 BaudRate,void *IdleEn)
{
	USART_InitTypeDef  USART_InitStruct;
	GPIO_InitTypeDef 	 GPIO_InitStruct;
	NVIC_InitTypeDef 		NVIC_InitStructure;
	
    GPIO_InitStruct.GPIO_Pin	=USART1_TX_PIN;
	GPIO_InitStruct.GPIO_Speed	=GPIO_Speed_50MHz;
	GPIO_InitStruct.GPIO_Mode 	=TX_IO_MODE;
	GPIO_Init(UART1_PORT, &GPIO_InitStruct);

	GPIO_InitStruct.GPIO_Pin    =USART1_RX_PIN;
	GPIO_InitStruct.GPIO_Speed	=GPIO_Speed_50MHz;
	GPIO_InitStruct.GPIO_Mode 	=RX_IO_MODE;
	GPIO_Init(UART1_PORT, &GPIO_InitStruct);

    GPIO_PinRemapConfig(GPIO_Remap_USART1,ENABLE);

	USART_InitStruct.USART_BaudRate 		=BaudRate;
	USART_InitStruct.USART_WordLength 	    =USART_WordLength_8b;
	USART_InitStruct.USART_StopBits 		=USART_StopBits_1;
	USART_InitStruct.USART_Parity 			=USART_Parity_No;
	USART_InitStruct.USART_HardwareFlowControl	=USART_HardwareFlowControl_None;
	USART_InitStruct.USART_Mode 				=USART_Mode_Rx|USART_Mode_Tx;
	USART_Init(USART1, &USART_InitStruct);

	NVIC_InitStructure.NVIC_IRQChannel						=USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority	=UART1_NVIC_IRQChnPrePri;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority 			=UART1_NVIC_IRQChnSubPri;
	NVIC_InitStructure.NVIC_IRQChannelCmd 					=ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	if(IdleEn !=NULL)
	{
		USART_ITConfig(USART1, USART_IT_IDLE, ENABLE);
	}
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
	USART_Cmd(USART1, ENABLE);
}


#define     UART2_PORT           GPIOA
#define     USART2_TX_PIN         2
#define     USART2_RX_PIN         3

static void USART2_Init(u32 BaudRate,void *IdleEn)
{
	USART_InitTypeDef  USART_InitStruct;
	GPIO_InitTypeDef 	 GPIO_InitStruct;
	NVIC_InitTypeDef 		NVIC_InitStructure;
	
	GPIO_InitStruct.GPIO_Pin		=USART2_TX_PIN;
	GPIO_InitStruct.GPIO_Speed	    =GPIO_Speed_50MHz;
	GPIO_InitStruct.GPIO_Mode		=TX_IO_MODE;
	GPIO_Init(UART2_PORT, &GPIO_InitStruct);

	GPIO_InitStruct.GPIO_Pin		=USART2_RX_PIN;
	GPIO_InitStruct.GPIO_Speed	    =GPIO_Speed_50MHz;
	GPIO_InitStruct.GPIO_Mode		=RX_IO_MODE;
	GPIO_Init(UART2_PORT, &GPIO_InitStruct);
	
    GPIO_PinRemapConfig(GPIO_Remap_USART2,ENABLE);
	
	USART_InitStruct.USART_BaudRate			=BaudRate;
	USART_InitStruct.USART_WordLength		=USART_WordLength_8b;
	USART_InitStruct.USART_StopBits			=USART_StopBits_1;
	USART_InitStruct.USART_Parity 			=USART_Parity_No;
	USART_InitStruct.USART_HardwareFlowControl=USART_HardwareFlowControl_None;
	USART_InitStruct.USART_Mode				=USART_Mode_Rx  | USART_Mode_Tx;
	USART_Init(USART2, &USART_InitStruct);

	NVIC_InitStructure.NVIC_IRQChannel 		                =USART2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority	= UART2_NVIC_IRQChnPrePri;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority 			= UART2_NVIC_IRQChnSubPri;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	if(IdleEn !=NULL)
	{
		USART_ITConfig(USART2, USART_IT_IDLE, ENABLE);
	}
	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);
	USART_Cmd(USART2, ENABLE);
}

#define     UART3_PORT          GPIOB
#define     UART3_IO_TX         10
#define     UART3_IO_RX         11


void USART3_Init(u32 BaudRate,void *IdleEn)
{
	USART_InitTypeDef  USART_InitStruct;
	GPIO_InitTypeDef 	 GPIO_InitStruct;
	NVIC_InitTypeDef 		NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3,   ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,    ENABLE);
	

	GPIO_InitStruct.GPIO_Pin	=UART3_IO_TX;
	GPIO_InitStruct.GPIO_Speed	=GPIO_Speed_50MHz;
	GPIO_InitStruct.GPIO_Mode 	=TX_IO_MODE;
	GPIO_Init(UART3_PORT, &GPIO_InitStruct);

	GPIO_InitStruct.GPIO_Pin	=UART3_IO_RX;
	GPIO_InitStruct.GPIO_Speed	=GPIO_Speed_50MHz;
	GPIO_InitStruct.GPIO_Mode 	=RX_IO_MODE;
	GPIO_Init(UART3_PORT, &GPIO_InitStruct);

	
    GPIO_PinRemapConfig(GPIO_FullRemap_USART3,ENABLE);

	USART_InitStruct.USART_BaudRate			=BaudRate;
	USART_InitStruct.USART_WordLength		=USART_WordLength_8b;
	USART_InitStruct.USART_StopBits			=USART_StopBits_1;
	USART_InitStruct.USART_Parity 			=USART_Parity_No;
	USART_InitStruct.USART_HardwareFlowControl=USART_HardwareFlowControl_None;
	USART_InitStruct.USART_Mode					=USART_Mode_Rx|USART_Mode_Tx;
	USART_Init(USART3, &USART_InitStruct);

	NVIC_InitStructure.NVIC_IRQChannel 		=USART3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority	= UART3_NVIC_IRQChnPrePri;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority 			= UART3_NVIC_IRQChnSubPri;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	
	if(IdleEn !=NULL)
	{
		USART_ITConfig(USART3, USART_IT_IDLE, ENABLE);
	}
	USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);
	USART_Cmd(USART3, ENABLE);

}


void USART_DefInit(void)
{
    int i;
    int bps =115200;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1 | 
                            RCC_APB2Periph_GPIOA | 
                            RCC_APB2Periph_GPIOB |
                            RCC_APB2Periph_GPIOC |
                            RCC_APB2Periph_AFIO   ,ENABLE);

    RCC_APB1PeriphClockCmd( RCC_APB1Periph_USART2 |
                            RCC_APB1Periph_USART3 ,   ENABLE);

    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1 ,   ENABLE);

    USART1_Init(bps, (void *)1);
    USART2_Init(bps, (void *)1);
    USART3_Init(bps, (void *)1);
    for(i=0;i<3;i++)
    {
        rxbuff[i].idelSignal =0;
        rxbuff[i].readPos   =0;
        rxbuff[i].writePos  =0;
    }
}

const void  *USARTtable[]=      {USART1, USART2, USART3};


void USART_SendBytes(ENUM_COM_ID com,u8 *pbuff,u16 len)
{
    uint8_t  index =(uint8_t)com;
    while(len--)
    {				
        USART_SendData((USART_TypeDef*)USARTtable[index], *pbuff++);
        while(USART_GetFlagStatus((USART_TypeDef*)USARTtable[index], USART_FLAG_TXE) == RESET) {}
    }   
}



void Usart_DmaTxCfg(DMA_Channel_TypeDef* DMAy_Chn, u32 UARTx_DR, u32 MemoryBaseAddr, u32 Datasize)
{
    DMA_InitTypeDef 	DMA_InitStructure;
	
	DMA_DeInit(DMAy_Chn);
    DMA_InitStructure.DMA_PeripheralBaseAddr        =UARTx_DR; 
    DMA_InitStructure.DMA_MemoryBaseAddr            =MemoryBaseAddr;
    DMA_InitStructure.DMA_DIR                       = DMA_DIR_PeripheralDST;
    DMA_InitStructure.DMA_BufferSize                = Datasize ;
    DMA_InitStructure.DMA_PeripheralInc             = DMA_PeripheralInc_Disable;
    DMA_InitStructure.DMA_MemoryInc                 = DMA_MemoryInc_Enable;
    DMA_InitStructure.DMA_PeripheralDataSize        = DMA_PeripheralDataSize_Byte; 
    DMA_InitStructure.DMA_MemoryDataSize            = DMA_MemoryDataSize_Byte;
    DMA_InitStructure.DMA_Mode                      = DMA_Mode_Normal;
    DMA_InitStructure.DMA_Priority                  = DMA_Priority_VeryHigh;
    DMA_InitStructure.DMA_M2M                       = DMA_M2M_Disable;
    DMA_Init(DMAy_Chn, &DMA_InitStructure);
}


//DMA1_CHN4
void Usart_DmaUsart1Tx(u32 BuffAddr,u16 BuffSize)
{
	NVIC_InitTypeDef NVIC_InitStructure;
  	NVIC_InitStructure.NVIC_IRQChannel					   	= DMA1_Channel4_IRQn;	
   	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority    = USART_DMA_Prepri;	
    NVIC_InitStructure.NVIC_IRQChannelSubPriority		   	= USART1_DMA_SubPri;
    NVIC_InitStructure.NVIC_IRQChannelCmd				   	= ENABLE;
    DMA_Cmd(DMA1_Channel4, DISABLE);
    
    NVIC_Init(&NVIC_InitStructure);	  
    Usart_DmaTxCfg(DMA1_Channel4, (u32)&USART1->DR, BuffAddr, BuffSize);
    USART_DMACmd(USART1, USART_DMAReq_Tx, ENABLE);
    DMA_ITConfig(DMA1_Channel4,DMA_IT_TC | DMA_IT_TE, ENABLE); 
    DMA_Cmd(DMA1_Channel4, ENABLE);		
}

//DMA1_CHN7
void Usart_DmaUsart2Tx(u32 BuffAddr,u16 BuffSize)
{
	NVIC_InitTypeDef NVIC_InitStructure;
  	NVIC_InitStructure.NVIC_IRQChannel					   	= DMA1_Channel7_IRQn;	
   	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority    = USART_DMA_Prepri;	
    NVIC_InitStructure.NVIC_IRQChannelSubPriority		   	= USART2_DMA_SubPri;
    NVIC_InitStructure.NVIC_IRQChannelCmd				   	= ENABLE;
    DMA_Cmd(DMA1_Channel7, DISABLE);
    
    NVIC_Init(&NVIC_InitStructure);	  
    Usart_DmaTxCfg(DMA1_Channel7, (u32)&USART2->DR, BuffAddr, BuffSize);
    USART_DMACmd(USART2, USART_DMAReq_Tx, ENABLE);
    DMA_ITConfig(DMA1_Channel7,DMA_IT_TC | DMA_IT_TE, ENABLE); 
    DMA_Cmd(DMA1_Channel7, ENABLE);		
}

//DMA1_chn2
void Usart_DmaUsart3Tx(u32 BuffAddr,u16 BuffSize)
{
	NVIC_InitTypeDef NVIC_InitStructure;
  	NVIC_InitStructure.NVIC_IRQChannel					   	= DMA1_Channel2_IRQn;	
   	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority    = USART_DMA_Prepri;	
    NVIC_InitStructure.NVIC_IRQChannelSubPriority		   	= USART2_DMA_SubPri;
    NVIC_InitStructure.NVIC_IRQChannelCmd				   	= ENABLE;
    DMA_Cmd(DMA1_Channel2, DISABLE);
    
    NVIC_Init(&NVIC_InitStructure);	  
    Usart_DmaTxCfg(DMA1_Channel2, (u32)&USART3->DR, BuffAddr, BuffSize);
    USART_DMACmd(USART3, USART_DMAReq_Tx, ENABLE);
    DMA_ITConfig(DMA1_Channel2,DMA_IT_TC | DMA_IT_TE, ENABLE); 
    DMA_Cmd(DMA1_Channel2, ENABLE);		
}


static  u8   dmaStatus[3]={0};
void USART_DmaTx(ENUM_COM_ID com,u8 *pBuff,u16 BuffSize)
{    
	 switch(com)
     {
         case COM1:
            Usart_DmaUsart1Tx((u32)pBuff,  BuffSize);
            dmaStatus[0] =1;
         break;
         case COM2:
            Usart_DmaUsart2Tx((u32)pBuff,  BuffSize);
            dmaStatus[1] =1;
         break;
         case COM3:
            Usart_DmaUsart3Tx((u32)pBuff,  BuffSize);
            dmaStatus[2] =1;
         break;
     }
}	

void USART_DmaDone(ENUM_COM_ID com)
{
    dmaStatus[(u8)com] =0;
}


u8   USART_GetDmaIsBusy(ENUM_COM_ID com)
{
    return dmaStatus[(u8)com];
}


void USART_InterruptServer(ENUM_COM_ID com,u8 newByte,u8 IsIdle)
{
    ST_USART_RX_BUFF   *p=&rxbuff[(u8)com];
    if(!IsIdle)
    {
        p->buff[p->writePos++] =newByte;
        if(p->writePos == USART_RX_BUFF_LEN){
            p->writePos =0;
        }
    }
    else if(p->writePos > 0)
    {
        p->idelSignal =1;
    }
}

void USART_hoopcpy(u8 *dst,u8 *src, u8 pos,u8 size)
{
    int32_t i;
    for(i=0;i<size;i++){
       dst[i]= src[(pos + i) % USART_RX_BUFF_LEN];
    }
}

u8 USART_readHoop(ENUM_COM_ID com,u8 *pbuff,u8 size)
{
    ST_USART_RX_BUFF   *p=&rxbuff[(u8)com];
    int32_t  rlen =p->writePos - p->readPos;
    if(rlen < 0)
        rlen +=USART_RX_BUFF_LEN;  
    if(rlen >= size)
    {
        USART_hoopcpy(pbuff,p->buff,p->readPos,size);
        p->readPos +=size;
    }
    else if((p->idelSignal > 0)&&(rlen > 0))
    {           
        p->idelSignal =0;
        USART_hoopcpy(pbuff,p->buff,p->readPos,rlen);  
        p->readPos =(p->readPos + rlen) % USART_RX_BUFF_LEN;
    }
    else
    {
        rlen =0;
    }   
    return rlen;
}


static  char  	  DebugBuff[200];
#include  <stdarg.h>
#include  <string.h>
void USART_Debug(u32 isOut,char *file,u32 line,char *msg,...)
{
    va_list argp; 
    u8 len =0;
    if(isOut)
    {
        sprintf((char *)DebugBuff,"\r\n %s--%d-->",file,line);
        len =strlen(DebugBuff);
        va_start(argp, msg);
        vsnprintf((char *)DebugBuff + len, sizeof(DebugBuff) - len, msg, argp); 
        va_end(argp);		
        USART_SendBytes(COM3,(u8 *)DebugBuff,strlen(DebugBuff));	
	}   		
}


void USART1_IRQHandler(void)
{
    u8  data;
    if(USART_GetITStatus(USART1,USART_IT_IDLE) != RESET)
    {
        USART_InterruptServer(COM1,0,1);
        USART_ClearITPendingBit(USART1, USART_IT_IDLE);
    }
    if(USART_GetITStatus(USART1,USART_IT_RXNE) != RESET)
    {
        data =USART_ReceiveData(USART1) & 0XFF;
        USART_InterruptServer(COM1,data,0);
        USART_ClearITPendingBit(USART1, USART_IT_RXNE);
    }
}

void USART2_IRQHandler(void)
{
    u8  data;
    if(USART_GetITStatus(USART2,USART_IT_IDLE) != RESET)
    {
        USART_InterruptServer(COM2,0,1);
        USART_ClearITPendingBit(USART2, USART_IT_IDLE);
    }
    if(USART_GetITStatus(USART2,USART_IT_RXNE) != RESET)
    {
        data =USART_ReceiveData(USART2) & 0XFF;
        USART_InterruptServer(COM2,data,0);
        USART_ClearITPendingBit(USART2, USART_IT_RXNE);
    }
}

void USART3_IRQHandler(void)
{
    u8  data;
    if(USART_GetITStatus(USART3,USART_IT_IDLE) != RESET)
    {
        USART_InterruptServer(COM3,0,1);
        USART_ClearITPendingBit(USART3, USART_IT_IDLE);
    }
    if(USART_GetITStatus(USART3,USART_IT_RXNE) != RESET)
    {
        data =USART_ReceiveData(USART3) & 0XFF;
        USART_InterruptServer(COM3,data,0);
        USART_ClearITPendingBit(USART3, USART_IT_RXNE);
    }
}

void DMA1_Channel4_IRQHandler(void)
{
    if(DMA_GetITStatus(DMA1_IT_TC4) == TRUE)
    {
        DMA_ClearFlag(DMA1_IT_TC4);		
        DMA_Cmd(DMA1_Channel4, DISABLE);
        USART_DmaDone(COM1);
    }
    if(DMA_GetITStatus(DMA1_IT_TE4) == TRUE)
    {
        DMA_ClearFlag(DMA1_IT_TE4);
        DMA_Cmd(DMA1_Channel4, DISABLE);
        USART_DmaDone(COM1);
    }
}

void DMA1_Channel7_IRQHandler(void)
{
    if(DMA_GetITStatus(DMA1_IT_TC7) == TRUE)
    {
        DMA_ClearFlag(DMA1_IT_TC7);		
        DMA_Cmd(DMA1_Channel7, DISABLE);
        USART_DmaDone(COM2);
    }
    if(DMA_GetITStatus(DMA1_IT_TE7) == TRUE)
    {
        DMA_ClearFlag(DMA1_IT_TE7);
        DMA_Cmd(DMA1_Channel4, DISABLE);
        USART_DmaDone(COM2);
    }
}

void DMA1_Channel2_IRQHandler(void)
{
    if(DMA_GetITStatus(DMA1_IT_TC2) == TRUE)
    {
        DMA_ClearFlag(DMA1_IT_TC2);		
        DMA_Cmd(DMA1_Channel2, DISABLE);
        USART_DmaDone(COM3);
    }
    if(DMA_GetITStatus(DMA1_IT_TE2) == TRUE)
    {
        DMA_ClearFlag(DMA1_IT_TE2);
        DMA_Cmd(DMA1_Channel4, DISABLE);
        USART_DmaDone(COM3);
    }
}

