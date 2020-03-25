#include  "usbcache.h"

static  ST_USB_CACHE   usbCache[3];
void usbcache_init(void)
{
    int i;
    for(i=0;i<3;i++)
    {
        usbCache[i].readPos =0;
        usbCache[i].writePos =0;
    }
}

void usbcache_push(u8 id,u8 *buff, u8 size)
{
    int  i;
    ST_USB_CACHE  *p =&usbCache[id];
    for(i=0;i<size;i++)
    {
        p->cache[p->writePos++] =*buff++;
        if(p->writePos == USB_CACHE_SIZE)
        {
            p->writePos =0;
        }
    }
    if(size < 64)
    {
        p->doneSignal =1;
    }
}


void usbcache_hoopcpy(u8 *dst,u8 *src, u8 pos,u8 size)
{
    int32_t i;
    for(i=0;i<size;i++){
       dst[i]= src[(pos + i) % USB_CACHE_SIZE];
    }
}


u8 usbcache_pull(u8 id,u8 *pbuff,u8 size)
{
    ST_USB_CACHE  *p =&usbCache[id];
    int32_t  rlen =p->writePos - p->readPos;
    if(rlen < 0)
        rlen +=USB_CACHE_SIZE;
    if(rlen >= size)
    {
        usbcache_hoopcpy(pbuff,p->cache,p->readPos,size);
        p->readPos +=size;
    }
    else if((rlen > 0)&&(p->doneSignal > 0))
    {         
        p->doneSignal =0;
        usbcache_hoopcpy(pbuff,p->cache,p->readPos,rlen);  
        p->readPos =(p->readPos + rlen) % USB_CACHE_SIZE;
    }
    else 
    {
        rlen =0;
    }   
    return rlen;
}









