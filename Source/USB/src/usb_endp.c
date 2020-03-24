/**
  ******************************************************************************
  * @file    usb_endp.c
  * @author  MCD Application Team
  * @version V4.0.0
  * @date    21-January-2013
  * @brief   Endpoint routines
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2013 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */


/* Includes ------------------------------------------------------------------*/
#include "usb_lib.h"
#include "usb_desc.h"
#include "usb_mem.h"
#include "hw_config.h"
#include "usb_istr.h"
#include "usb_pwr.h"
#include "memPool.h"
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/

/* Interval between sending IN packets in frame number (1 frame = 1ms) */
#define VCOMPORT_IN_FRAME_INTERVAL             5

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

static const uint16_t ENDP_ADDR_TABLE[EP_NUM][4]={
    {ENDP0_TXADDR,  ENDP0_RXADDR,   ENDP0_TX_SIZE,      ENDP0_RX_SIZE},
    {ENDP1_TXADDR,  ENDP1_RXADDR,   ENDP1_TX_SIZE,      ENDP1_RX_SIZE},
    {ENDP2_TXADDR,  ENDP2_RXADDR,   ENDP2_TX_SIZE,      ENDP2_RX_SIZE},
    {ENDP3_TXADDR,  ENDP3_RXADDR,   ENDP3_TX_SIZE,      ENDP3_RX_SIZE},
    {ENDP4_TXADDR,  ENDP4_RXADDR,   ENDP4_TX_SIZE,      ENDP4_RX_SIZE},
    {ENDP5_TXADDR,  ENDP5_RXADDR,   ENDP5_TX_SIZE,      ENDP5_RX_SIZE},
    {ENDP6_TXADDR,  ENDP6_RXADDR,   ENDP6_TX_SIZE,      ENDP6_RX_SIZE},
};

#define ENDP_TX_ADDR(n)     ENDP_ADDR_TABLE[n][0]
#define ENDP_RX_ADDR(n)     ENDP_ADDR_TABLE[n][1]
#define ENDP_TX_SIZE(n)     ENDP_ADDR_TABLE[n][2]
#define ENDP_RX_SIZE(n)     ENDP_ADDR_TABLE[n][3]

/* Private function prototypes -----------------------------------------------*/

static uint8_t txBuff[EP_NUM][ENDPOINT_DATA_SIZE]={0};
static uint8_t rxBuff[EP_NUM][ENDPOINT_DATA_SIZE]={0};
static uint8_t beGoing[EP_NUM]={0};


static const  uint8_t usbTmemID[EP_NUM]={0,USART1_RX_ID,0,USART2_RX_ID,0,USART3_RX_ID};

void MoveDataBuffer2Usb(uint8_t nEndp)
{
    uint16_t len = 0;
    if((nEndp < EP_NUM)&&(ENDP_TX_SIZE(nEndp) >0))
    {
        len = MemPool_ReadBytes(usbTmemID[nEndp],txBuff[nEndp], ENDP_TX_SIZE(nEndp));

        if (len > 0)
        {
            beGoing[nEndp]  =(len == ENDP_TX_SIZE(nEndp)) ? 1 : 0;
            UserToPMABufferCopy(txBuff[nEndp], ENDP_TX_ADDR(nEndp), len);
            SetEPTxCount(nEndp, len);
            SetEPTxValid(nEndp);        
        }
        else if(beGoing[nEndp])
        {
            beGoing[nEndp] =0;
            SetEPTxCount(nEndp,  0);
            SetEPTxValid(nEndp);
        }
    }
}


static const uint8_t  usbRmemID[EP_NUM]={0,USART1_TX_ID, 0,USART2_TX_ID,0,USART3_TX_ID};

void MoveDataUsb2Buffer(uint8_t nEndp)
{ 
    uint16_t USB_Rx_Cnt;
    if((nEndp < EP_NUM)&&(ENDP_RX_SIZE(nEndp) > 0))
    {
        USB_Rx_Cnt = USB_SIL_Read(nEndp, rxBuff[nEndp]);
        MemPool_WriteBytes(usbRmemID[nEndp], rxBuff[nEndp], USB_Rx_Cnt);
        SetEPRxValid(nEndp);
    }
}



void configture2Usart(uint8_t nEndp)
{
    uint16_t USB_Rx_Cnt;
    if((nEndp < EP_NUM)&&(ENDP_RX_SIZE(nEndp) > 0))
    {
        USB_Rx_Cnt = USB_SIL_Read(nEndp, rxBuff[nEndp]);
        ///USB_RxWrite(nEndp, rxBuff[nEndp], USB_Rx_Cnt);
        SetEPRxValid(nEndp);
    }
}

/* Private functions ---------------------------------------------------------*/

/*******************************************************************************
* Function Name  : EP1_IN_Callback
* Description    :
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
void EP1_IN_Callback (void)
{
    MoveDataBuffer2Usb(ENDP1);
}

void EP1_OUT_Callback(void)
{
    MoveDataUsb2Buffer(ENDP1);
}

void EP2_OUT_Callback (void)
{
    configture2Usart(ENDP2);
}

void EP3_IN_Callback (void)
{
    MoveDataBuffer2Usb(ENDP3);
}

void EP3_OUT_Callback(void)
{
    MoveDataUsb2Buffer(ENDP3);
}

void EP4_OUT_Callback (void)
{
    configture2Usart(ENDP4);
}

void EP5_IN_Callback (void)
{
    MoveDataBuffer2Usb(ENDP5);
}

void EP5_OUT_Callback(void)
{
    MoveDataUsb2Buffer(ENDP5);
}

void EP6_OUT_Callback (void)
{
    configture2Usart(ENDP6);
}


/*******************************************************************************
* Function Name  : SOF_Callback / INTR_SOFINTR_Callback
* Description    :
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
void SOF_Callback(void)
{
}
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

