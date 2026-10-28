typedef unsigned char u8;
typedef signed short s16;
typedef unsigned short u16;
typedef signed int s32;
typedef unsigned int u32;
struct CoordinateStep {
    s32 target_x, target_y;
    s32 current_x, current_y;
    s32 angle, rate, step;
};
extern u32 BiosArcTan2(s32, s32);
extern s32 DivideSigned(s32, s32);
extern s32 ReadAngleX(u8);
extern s32 ReadAngleY(u8);
asm(".global BiosArcTan2\n.thumb_set BiosArcTan2,0x08141861\n.global DivideSigned\n.thumb_set DivideSigned,0x081426b9\n.global ReadAngleX\n.thumb_set ReadAngleX,0x08007a61\n.global ReadAngleY\n.thumb_set ReadAngleY,0x08007a4d");

void AdvanceBattleCoordinateStep(struct CoordinateStep *state)
{
    s32 delta_x = (u32)state->target_x - (u32)state->current_x;
    register s32 bios_x asm("r0") = (s32)((u32)delta_x << 8) >> 16;
    s32 delta_y;
    u32 desired_angle;
    s32 difference;
    register s32 angle_step asm("r1");
    register s32 component asm("r0");
    register s32 displacement asm("r1");
    /* The original finishes narrowing the X argument before reading Y. */
    asm("" : "+r"(bios_x));
    delta_y = (u32)state->target_y - (u32)state->current_y;
    desired_angle = (u16)BiosArcTan2(bios_x,
                                    (s32)((u32)delta_y << 8) >> 16) >> 8;
    difference = desired_angle - (u32)state->angle;
    if (difference > 128)
        difference = (u32)difference - 256;
    else if (difference < -128)
        difference = (u32)difference + 256;
    angle_step = DivideSigned((u32)state->rate * (u32)difference, 100);
    /* Preserve the quotient before reloading the helper-visible record angle. */
    asm("" : "+r"(angle_step));
    state->angle = (u32)state->angle + (u32)angle_step;
    if (state->angle < 0)
        state->angle = (u32)state->angle + 256;
    if (state->angle > 255)
        state->angle = (u32)state->angle - 256;
    component = (s16)ReadAngleX((u8)state->angle);
    /* Keep the actual table result while loading the live step multiplier. */
    asm("" : "+r"(component));
    displacement = (u32)state->step * (u32)component;
    /* The original retains the defined product accumulator through its shift. */
    asm("" : "+r"(displacement));
    displacement >>= 8;
    state->current_x = (u32)state->current_x + (u32)displacement;
    component = (s16)ReadAngleY((u8)state->angle);
    asm("" : "+r"(component));
    displacement = (u32)state->step * (u32)component;
    asm("" : "+r"(displacement));
    displacement >>= 8;
    state->current_y = (u32)state->current_y + (u32)displacement;
}
