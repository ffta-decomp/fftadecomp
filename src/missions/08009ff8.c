typedef unsigned char u8;
typedef unsigned short u16;
extern u8 GetGameFlag(u16);
extern void SetGameFlag(u16,u16);

asm(".global GetGameFlag\n.thumb_set GetGameFlag,0x80c9541\n.global SetGameFlag\n.thumb_set SetGameFlag,0x80c9575");
void ConsumeProgressFlag543(void) __asm__("Registered39_00009FF8");
/* The role of flag543 is unknown; retail clears it only after a LOW8 test. */
void ConsumeProgressFlag543(void)
{
    register unsigned int flag_to_read __asm__("r0") = 543;
    /* Distinct call-argument definitions; neither value crosses a helper. */
    __asm__ volatile ("" : : "r" (flag_to_read));
    if (GetGameFlag(flag_to_read)) {
        register unsigned int flag_to_clear __asm__("r0") = 543;
        __asm__ volatile ("" : : "r" (flag_to_clear));
        SetGameFlag(flag_to_clear, 0);
    }
}
