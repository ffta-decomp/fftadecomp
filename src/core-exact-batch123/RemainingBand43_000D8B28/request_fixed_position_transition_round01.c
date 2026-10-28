typedef signed short s16;
typedef unsigned short u16;
typedef unsigned int u32;
extern u32 ConfigurePositionTransition(int x, int y, u32 first,
                                      u32 second, u32 third);
__asm__(".thumb_set ConfigurePositionTransition,0x0801bb95");
u32 RequestFixedPositionTransition(int x_word, int y_word)
    __asm__("RemainingBand43_000D8B28");
u32 RequestFixedPositionTransition(int x_word, int y_word)
{
    s16 x = x_word;
    s16 y = y_word;
    u32 low_result;
    /* This real service mutates shared transition state; it is not a query. */
    low_result = (u16)ConfigurePositionTransition(x, y, 4, 16, 4);
    /* The native NEG/LSR31 normalizes the zero-extended halfword. */
    return (0u - low_result) >> 31;
}
