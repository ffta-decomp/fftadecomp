typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;
typedef struct {
    s8 phase, displayed_rule, scan_rule;
    u8 dwell, timing, special_rule_range;
    u16 unknown_06;
    s16 oscillation_offset, fade_step;
} StatusCycle;
extern u32 SelectUnitStateRule(const void *unit, u16 rule);
__asm__(".global SelectUnitStateRule\n.thumb_set SelectUnitStateRule,0x0809da0d");
void IsolatedCore57_0009DCC4(const void *unit, StatusCycle *cycle)
{
    /* Native countdown stays in r1 while r0 forms the preserved high bit. */
    register int countdown __asm__("r1") = (cycle->timing & ~0x80) - 1;
    int phase;
    if (countdown < 0) countdown = 0;
    __asm__("" : "+r" (countdown));
    cycle->timing = (cycle->timing & 0x80) | countdown;
    if (countdown <= 0) {
        cycle->timing = (cycle->timing & 0x80) | 4;
        if (cycle->timing & 0x80) {
            cycle->oscillation_offset++;
            if (cycle->oscillation_offset > 1) cycle->timing ^= 0x80;
        } else {
            cycle->oscillation_offset--;
            if (cycle->oscillation_offset < -1) cycle->timing ^= 0x80;
        }
    }
    phase = cycle->phase;
    switch (phase) {
    case 1:
        cycle->displayed_rule = SelectUnitStateRule(unit, (u16)cycle->scan_rule);
        cycle->scan_rule++;
        if (cycle->scan_rule > 24) cycle->scan_rule = phase;
        if (cycle->displayed_rule != 0) {
            int rule = (u16)cycle->displayed_rule;
            switch (rule) {
            case 10: case 11: case 12: case 13:
                rule = 1;
                break;
            default:
                rule = 0;
                break;
            }
            cycle->special_rule_range = rule;
            cycle->phase = 2;
            cycle->fade_step = 5;
            cycle->timing = (cycle->timing & 0x80) | 4;
        }
        break;
    case 2:
        cycle->fade_step--;
        if (cycle->fade_step <= 0) {
            cycle->fade_step = 0;
            cycle->phase = 3;
            if (cycle->dwell > 79) cycle->dwell = 0;
        }
        break;
    case 3:
        cycle->dwell++;
        if (cycle->dwell > 79) {
            /* Native saves full helper return in r1 before signed-byte reload. */
            register u32 next_rule __asm__("r1");
            cycle->dwell = 0;
            next_rule = SelectUnitStateRule(unit, (u16)(cycle->displayed_rule + 1));
            __asm__("" : "+r" (next_rule));
            if (next_rule != cycle->displayed_rule) cycle->phase = 4;
        }
        break;
    case 4:
        cycle->fade_step++;
        if ((u16)cycle->fade_step > 5) {
            cycle->fade_step = 5;
            cycle->phase = 0;
        }
        break;
    }
}
