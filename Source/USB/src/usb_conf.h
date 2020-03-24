/**
  ******************************************************************************
  * @file    usb_conf.h
  * @author  MCD Application Team
  * @version V4.0.0
  * @date    21-January-2013
  * @brief   Virtual COM Port Demo configuration  header
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


/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __USB_CONF_H
#define __USB_CONF_H

/* Includes ------------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
/* External variables --------------------------------------------------------*/

/*-------------------------------------------------------------*/
/* EP_NUM */
/* defines how many endpoints are used by the device */
/*-------------------------------------------------------------*/

#define EP_NUM                    (7)

/*-------------------------------------------------------------*/
/* --------------   Buffer Description Table  -----------------*/
/*-------------------------------------------------------------*/
/* buffer table base address */
/* buffer table base address */
#define ENDPOINT_DATA_SIZE    (64)
#define ENDPOINT_CMD_SIZE     (8)
#define BTABLE_ADDRESS        (0x00)


/* EP0  */
/* rx/tx buffer base address  0x4000 6000 - 0x4000 63FF */

#define ENDP0_PACKAGE_SIZE  (ENDPOINT_CMD_SIZE * 6) 

#define ENDP0_TX_SIZE       (ENDPOINT_CMD_SIZE * 6)
#define ENDP0_RX_SIZE       (ENDPOINT_CMD_SIZE * 6)

#define ENDP1_TX_SIZE       (ENDPOINT_DATA_SIZE)
#define ENDP1_RX_SIZE       (ENDPOINT_DATA_SIZE)

#define ENDP2_TX_SIZE       (0)
#define ENDP2_RX_SIZE       (ENDPOINT_CMD_SIZE)

#define ENDP3_TX_SIZE       (ENDPOINT_DATA_SIZE)
#define ENDP3_RX_SIZE       (ENDPOINT_DATA_SIZE)

#define ENDP4_TX_SIZE       (0)
#define ENDP4_RX_SIZE       (ENDPOINT_CMD_SIZE)

#define ENDP5_TX_SIZE       (ENDPOINT_DATA_SIZE)
#define ENDP5_RX_SIZE       (ENDPOINT_DATA_SIZE)

#define ENDP6_TX_SIZE       (0)
#define ENDP6_RX_SIZE       (ENDPOINT_CMD_SIZE)


#define ENDP0_TXADDR        (BTABLE_ADDRESS)
#define ENDP0_RXADDR        (ENDP0_TXADDR + ENDP0_TX_SIZE)

#define ENDP1_TXADDR        (ENDP0_RXADDR + ENDP0_RX_SIZE)
#define ENDP1_RXADDR        (ENDP1_TXADDR + ENDP1_TX_SIZE)

#define ENDP2_TXADDR        (ENDP1_RXADDR + ENDP1_RX_SIZE)
#define ENDP2_RXADDR        (ENDP2_TXADDR + ENDP2_TX_SIZE)

#define ENDP3_TXADDR        (ENDP2_RXADDR + ENDP2_RX_SIZE)
#define ENDP3_RXADDR        (ENDP3_TXADDR + ENDP3_TX_SIZE)

#define ENDP4_TXADDR        (ENDP3_RXADDR + ENDP3_RX_SIZE)
#define ENDP4_RXADDR        (ENDP4_TXADDR + ENDP4_TX_SIZE)

#define ENDP5_TXADDR        (ENDP4_RXADDR + ENDP4_RX_SIZE)
#define ENDP5_RXADDR        (ENDP5_TXADDR + ENDP5_TX_SIZE)

#define ENDP6_TXADDR        (ENDP5_RXADDR + ENDP5_RX_SIZE)
#define ENDP6_RXADDR        (ENDP6_TXADDR + ENDP6_TX_SIZE)

#if ((ENDP6_RXADDR + ENDP6_RX_SIZE) > 512)
#error "endpoint memory malloc faulted"
#endif
/*-------------------------------------------------------------*/
/* -------------------   ISTR events  -------------------------*/
/*-------------------------------------------------------------*/
/* IMR_MSK */
/* mask defining which events has to be handled */
/* by the device application software */
#define IMR_MSK (CNTR_CTRM  | CNTR_WKUPM | CNTR_SUSPM | CNTR_ERRM  | CNTR_SOFM \
                 | CNTR_ESOFM | CNTR_RESETM )

/*#define CTR_CALLBACK*/
/*#define DOVR_CALLBACK*/
/*#define ERR_CALLBACK*/
/*#define WKUP_CALLBACK*/
/*#define SUSP_CALLBACK*/
/*#define RESET_CALLBACK*/
#define SOF_CALLBACK
/*#define ESOF_CALLBACK*/
/* CTR service routines */
/* associated to defined endpoints */

//#define  EP1_IN_Callback   NOP_Process
#define  EP2_IN_Callback   NOP_Process
//#define  EP3_IN_Callback   NOP_Process
#define  EP4_IN_Callback   NOP_Process
//#define  EP5_IN_Callback   NOP_Process
#define  EP6_IN_Callback   NOP_Process
#define  EP7_IN_Callback   NOP_Process

//#define  EP1_OUT_Callback   NOP_Process
//#define  EP2_OUT_Callback   NOP_Process
//#define  EP3_OUT_Callback   NOP_Process
//#define  EP4_OUT_Callback   NOP_Process
//#define  EP5_OUT_Callback   NOP_Process
//#define  EP6_OUT_Callback   NOP_Process
#define  EP7_OUT_Callback   NOP_Process

#endif /* __USB_CONF_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
