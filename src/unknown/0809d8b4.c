typedef unsigned char u8;
typedef unsigned int u32;
extern u32 PollPendingContext(void *context) __asm__("RetailCall_0809ccd4");
u8 CoreFrontier_0009D8B4(void *context)
{
    return (u8)PollPendingContext(context);
}
