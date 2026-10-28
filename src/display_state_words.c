typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

/* The meanings of the state bytes are not yet established from callers. */
#define STATE_FLAG (*(volatile u8 *)0x030034d1)
#define STATE_VALUE (*(volatile u16 *)0x030034d2)

#if defined(DISPLAY_STATE_HIGH_BIT)
void SetDisplayStateValueWithHighBit(u16 value)
{
    STATE_FLAG = 0;
    /* Force the second retail address literal instead of pointer increment. */
    __asm__ volatile("" ::: "r2");
    STATE_VALUE = value | 0x8000;
}
#elif defined(DISPLAY_STATE_VALUE)
void SetDisplayStateValue(u16 value)
{
    STATE_FLAG = 0;
    STATE_VALUE = value;
}
#elif defined(DISPLAY_STATE_FLAG_VALUE)
void SetDisplayStateFlagAndValue(u16 value, u32 flag)
{
    STATE_FLAG = flag;
    STATE_VALUE = value;
}
#elif defined(DISPLAY_STATE_CLEAR)
void ClearDisplayStateValue(void)
{
    STATE_FLAG = 0;
    /* Preserve the retail reload of the halfword destination address. */
    __asm__ volatile("" ::: "r1");
    STATE_VALUE = 0xfffe;
}
#elif defined(DISPLAY_STATE_FLAG_CLEAR)
void SetDisplayStateFlagAndClearValue(u32 flag)
{
    STATE_FLAG = flag;
    /* Preserve the retail reload of the halfword destination address. */
    __asm__ volatile("" ::: "r1");
    STATE_VALUE = 0xfffe;
}
#elif defined(DISPLAY_STATE_RESULT)
u16 GetDisplayStateResult(void)
{
    return *(volatile u16 *)0x030034d4;
}
#elif defined(DISPLAY_STATE_ACTIVE)
int IsDisplayStatePointerActive(void)
{
    volatile unsigned int *state = *(volatile unsigned int **)0x030034b8;
    if (state == 0)
        return 0;
    return *state != 0;
}
#elif defined(DISPLAY_STATE_FLAG_HIGH_BIT)
void SetDisplayStateFlagAndValueWithHighBit(u16 value, u32 flag)
{
    STATE_FLAG = flag;
    /* Preserve the retail reload of the halfword destination address. */
    __asm__ volatile("" ::: "r2");
    STATE_VALUE = value | 0x8000;
}
#else
#error Select one display-state routine
#endif
