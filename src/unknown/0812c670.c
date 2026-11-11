typedef signed int s32;
/* Battle avoidance uses the original inclusive5..95 result,with guard94. */
s32 ClampBattleAvoidance(s32 value) asm("CoreRegion_0012C670");
s32 ClampBattleAvoidance(s32 value)
{
    if (value <= 4)
        value = 5;
    else if (value > 94)
        value = 95;
    return value;
}
