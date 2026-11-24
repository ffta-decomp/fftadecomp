typedef signed short s16;
typedef unsigned short u16;
typedef unsigned int u32;
extern void ReadCurrentPosition(s16 *x, s16 *height, s16 *y);
extern void ProjectBattlePoint(s16 x, s16 height, s16 y,
                              u16 *out_x, u16 *out_y, u16 *out_depth);
extern u32 ConfigurePositionTransition(int x, int y, u32 first,
                                      u32 second, u32 third);
__asm__(".thumb_set ReadCurrentPosition,0x0801cda5\n"
        ".thumb_set ProjectBattlePoint,0x0801c919\n"
        ".thumb_set ConfigurePositionTransition,0x0801bb95");
u32 RequestCurrentPositionTransition(void)
    __asm__("RemainingBand43_000D85A0");
u32 RequestCurrentPositionTransition(void)
{
    s16 current_x, current_height, current_y;
    u16 projected_x, projected_y, projected_depth;
    u32 low_result;
    int adjusted_y;
    /* Both real helpers unconditionally define their three halfword outputs. */
    ReadCurrentPosition(&current_x, &current_height, &current_y);
    ProjectBattlePoint(current_x, current_height, current_y,
                       &projected_x, &projected_y, &projected_depth);
    projected_x -= 120;
    adjusted_y = projected_y - 80;
    projected_y = adjusted_y;
    low_result = (u16)ConfigurePositionTransition((s16)projected_x,
                                                 (s16)adjusted_y, 4, 16, 4);
    /* Preserve the native normalization of a zero-extended halfword. */
    return (0u - low_result) >> 31;
}
