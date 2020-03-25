#ifndef		__USB_CACHE__H__
#define		__USB_CACHE__H__

#include "stm32f10x.h"

#define  USB_CACHE_SIZE    3072

typedef  struct 
{
    u8  cache[USB_CACHE_SIZE];
    int32_t  writePos;
    int32_t  readPos; 
    int32_t  doneSignal;
}ST_USB_CACHE;


void usbcache_init(void);
void usbcache_push(u8 id,u8 *buff, u8 size);
u8 usbcache_pull(u8 id,u8 *pbuff,u8 size);
#endif
