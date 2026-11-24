typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;
typedef signed int s32;
struct ProjectedPoint { u16 x, y, depth; };
struct CoordinatePair { u16 x, y; };
struct BattleCoordinateTransition {
    s32 target_x, target_y;
    s32 current_x, current_y;
    u32 angle;
    u32 rate;
    s32 step;
    s16 saved_x, saved_y;
    u32 parameter;
    s32 maximum_delta;
};
extern void ProjectBattlePoint(s16, s16, s16, u16 *, u16 *, u16 *);
extern void ReadCurrentCoordinates(u16 *, u16 *);
extern u32 BiosArcTan2(s32, s32);
asm(".global ProjectBattlePoint\n.thumb_set ProjectBattlePoint,0x0801c919\n.global ReadCurrentCoordinates\n.thumb_set ReadCurrentCoordinates,0x0801e6f1\n.global BiosArcTan2\n.thumb_set BiosArcTan2,0x08141861");

void InitializeBattleCoordinateTransition(struct BattleCoordinateTransition *state,
    s16 x, s16 height, s16 y, s16 offset_x, s16 offset_y,
    u32 parameter, u32 rate)
{
    struct ProjectedPoint projected;
    struct CoordinatePair current;
    s32 current_x, current_y;
    s32 delta_x, delta_y;
    s32 signed_offset_x = offset_x;
    s32 signed_offset_y = offset_y;
    register u16 *projected_y_out asm("r6");
    register u16 *current_y_out asm("r5");

    /* These signed values are live across the projection, not extended afterward. */
    asm("" : "+r"(signed_offset_x), "+r"(signed_offset_y));
    /* Original input narrowing precedes formation of the retained Y output address. */
    asm("" : : "r"((s32)x), "r"((s32)height), "r"((s32)y));
    projected_y_out = &projected.y;
    /* The original retains each Y output address across its producer call. */
    asm("" : "+r"(projected_y_out));
    ProjectBattlePoint(x, height, y,
                      &projected.x, projected_y_out, &projected.depth);
    state->target_x = (u32)((s16)projected.x + signed_offset_x) << 8;
    state->target_y = (u32)((s16)*projected_y_out + signed_offset_y) << 8;
    if (state->step == 0)
        state->step = 256;
    current_y_out = &current.y;
    asm("" : "+r"(current_y_out));
    ReadCurrentCoordinates(&current.x, current_y_out);
    state->saved_x = current.x;
    state->saved_y = *current_y_out;
    current_x = (u32)state->saved_x << 8;
    state->current_x = current_x;
    current_y = (u32)state->saved_y << 8;
    state->current_y = current_y;
    state->parameter = parameter;
    state->rate = rate;
    delta_x = (u32)state->target_x - (u32)current_x;
    if (delta_x < 0)
        delta_x = 0u - (u32)delta_x;
    delta_y = (u32)state->target_y - (u32)current_y;
    if (delta_y < 0)
        delta_y = 0u - (u32)delta_y;
    if (delta_x > delta_y)
        state->maximum_delta = delta_x;
    else
        state->maximum_delta = delta_y;
    state->angle = (u16)BiosArcTan2((s32)((u32)delta_x << 8) >> 16,
                                   (s32)((u32)delta_y << 8) >> 16) >> 8;
    state->step = 256;
}
