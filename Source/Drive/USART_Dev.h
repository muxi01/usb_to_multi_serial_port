#ifndef		__USART_DEV__H__
#define		__USART_DEV__H__


#define     USART_RX_BUFF_LEN       256
typedef     enum{
    COM1=0,
    COM2,
    COM3,
}ENUM_COM_ID;

typedef     struct{
    u8    buff[USART_RX_BUFF_LEN];
    int32_t   writePos;
    int32_t   readPos;
    int32_t   idelSignal;
}ST_USART_RX_BUFF;


#define		UART1_NVIC_IRQChnPrePri		3
#define		UART1_NVIC_IRQChnSubPri		2

#define		UART3_NVIC_IRQChnPrePri		3
#define		UART3_NVIC_IRQChnSubPri		3


#define		UART2_NVIC_IRQChnPrePri		3
#define		UART2_NVIC_IRQChnSubPri		5

#define		USART_DMA_Prepri		    5

#define     USART1_DMA_SubPri           1
#define     USART2_DMA_SubPri           2
#define     USART3_DMA_SubPri           3

#define     TRUE        SET 
#ifndef			NULL
#define     NULL        ((void *)0)
#endif

void USART_DefInit();
void USART_Cfg(ENUM_COM_ID com,u32 bps);
u8   USART_GetDmaIsBusy(ENUM_COM_ID com);
void USART_DmaTx(ENUM_COM_ID com,u8 *pBuff,u16 BuffSize);
void USART_DmaTxIrqServer(ENUM_COM_ID com);
void USART_InterruptServer(ENUM_COM_ID com,u8 newByte,u8 IsIdle);
void USART_Debug(u32 isOut,char *file,u32 line,char *msg,...);
u8   USART_readHoop(ENUM_COM_ID com,u8 *pbuff,u8 size);
#endif


