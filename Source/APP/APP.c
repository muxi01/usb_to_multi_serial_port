/*
********************************************************************************
*
*                                 APP.c
*
* File          : APP.c
* Version       : V1.0
* Author        : whq
* Mode          : Thumb2
* Toolchain     : 
* Description   : ���������
*                
* History       :
* Date          : 2013.07.21
*******************************************************************************/


#include <string.h>

#include "APP.h"
#include "BSP.h"
#include "BSP_tim.h"

#include "memPool.h"
#include "HW_Config.h"
#include "USART_Dev.h"

void LedHandler(void)
{
    IO_TOGGLE(eLED_0);
}

/*******************************************************************************
* Function Name : int main(void)
* Description   : ���������
* Input         : 
* Output        : 
* Other         : 
* Date          : 2013.07.21
*******************************************************************************/

#define       PORT_NUM          3
#define       DMA_BUFF_SIZE     64
static const  ENUM_COM_ID COMn[PORT_NUM]={COM1,COM2,COM3};
static const  u8        MemoryID[PORT_NUM]={USART1_TX_ID, USART2_TX_ID, USART3_TX_ID};
static u8     dmaBuff[PORT_NUM][DMA_BUFF_SIZE]={0};
int main(void)
{
    u8 i,rlen;
    u8  *pDmaBuff,memid;
    ENUM_COM_ID com;
    MemPool_Init();
    BSP_Init();
    BSP_TimOpen(TIM_3, 7200, 10000, LedHandler);
    USB_Config();
    while (1)
    {
        for(i=0;i< PORT_NUM; i++)
        {
            com         =COMn[i];
            memid       =MemoryID[i];
            pDmaBuff    =dmaBuff[i];

            if(!USART_GetDmaIsBusy(com))
            {
                rlen =MemPool_ReadBytes(memid,pDmaBuff,DMA_BUFF_SIZE);
                if(rlen > 0)
                {
                    USART_DmaTx(com, pDmaBuff, rlen);
                }
            }          
        }       
    }
}



