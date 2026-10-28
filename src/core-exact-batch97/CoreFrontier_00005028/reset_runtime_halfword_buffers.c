typedef unsigned char u8;typedef unsigned short u16;
struct RuntimeMode {u8 mode;u8 unknown1[293];u16 value294;};
void CpuSet(const u16 *,u16 *,unsigned int) __asm__("RetailCall_0814186c");
void CoreFrontier_00005028(void)
{
    u16 first_zero,second_zero;
    u16 *first_buffer,*second_buffer;
    register unsigned int value __asm__("r1");
    register struct RuntimeMode *mode __asm__("r2");
    register unsigned int clear_zero __asm__("r5");
    register unsigned int offset __asm__("r3");
    register u16 *destination __asm__("r0");
    register u16 *reset __asm__("r0")=(u16 *)0x03002b68;
    /* Native materializes this real address before defining the zero value. */
    asm("" : "+r" (reset));
    value=0;
    *reset=value;
    mode=(struct RuntimeMode *)0x030028a0;
    /* Keep the defined zero in r1 while the native mode base enters r2. */
    asm("" : "+r" (mode), "+r" (value));
    if(mode->mode!=8)value=5;
    /* Native retains a defined 294-byte offset in r3 and stores via r0. */
    offset=294;
    asm("" : "+r" (offset));
    destination=(u16 *)((u8 *)mode+offset);
    asm("" : "+r" (destination));
    /* Native keeps this defined zero in r5 across all four halfword stores
     * and both real BIOS calls, beginning before the mode-value store. */
    clear_zero=0;
    asm("" : "+r" (clear_zero));
    *destination=value;
    first_buffer=(u16 *)0x03002890;
    *first_buffer=clear_zero;
    second_buffer=(u16 *)0x03002b50;
    *second_buffer=clear_zero;
    first_zero=clear_zero;
    CpuSet(&first_zero,first_buffer+1,0x01000006);
    second_zero=clear_zero;
    CpuSet(&second_zero,second_buffer+1,0x01000006);
}
asm(".global RetailCall_0814186c\n.thumb_set RetailCall_0814186c,0x0814186d\n");
