typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef struct { u16 counter, padding; void *child; } TimedChildWork;
extern void ReadLayers(u8 *, u8 *) __asm__("0x0801E610");
extern void *CreateTimedChild(u32,u32,u32,const void *,void *) __asm__("0x080D979C");
extern void ConfigureTimedChild(void *,u32,u32,u32) __asm__("0x080D984C");
extern void BeginChildClose(void *) __asm__("0x080D9B38");
extern void CloseChild(void *) __asm__("0x080D9B58");
extern void MarkScrollDirty(void) __asm__("0x0801B878");
u32 RemainingBand43_000EA3E8(void *parent,u16 *phase,TimedChildWork *work)
{
    switch (*phase) {
    case 0:
        work->counter=90;
        break;
    case 256:
        if (work->counter && !--work->counter) {
            u8 first, second;
            u32 layer;
            u8 *firstValue;
            ReadLayers(&first,&second);
            firstValue=&first;
            __asm__("" : "+r" (firstValue));
            layer=second;
            if (layer>*firstValue) layer=*firstValue;
            work->child=CreateTimedChild(2,layer,0,(const void *)0x08398A80,parent);
            ConfigureTimedChild(work->child,0,16,143);
            work->counter=210;
            ++*phase;
        }
        break;
    case 257:
        if (work->counter && !--work->counter) {
            BeginChildClose(work->child);
            ++*phase;
        }
        break;
    case 258:
        CloseChild(work->child);
        MarkScrollDirty();
        *phase=2;
        break;
    }
    return 0;
}
