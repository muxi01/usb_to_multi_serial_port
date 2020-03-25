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
#include "HW_Config.h"
#include "USART_Dev.h"
#include "usbcache.h"

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
static u8     dmaBuff[PORT_NUM][DMA_BUFF_SIZE]={0};

int main(void)
{
    u8 i,rlen;
    usbcache_init();
    BSP_Init();
    // BSP_TimOpen(TIM_3, 7200, 10000, LedHandler);
    USB_Config();
    while (1)
    {
        for(i=0;i< PORT_NUM; i++)
        {
            if(!USART_GetDmaIsBusy(COMn[i]))
            {
                rlen =usbcache_pull((u8)COMn[i],dmaBuff[i],DMA_BUFF_SIZE);
                if(rlen > 0)
                {
                    USART_DmaTx(COMn[i], dmaBuff[i], rlen);
                }
            }          
        }       
    }
}

