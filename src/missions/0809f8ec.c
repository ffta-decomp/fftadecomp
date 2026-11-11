/* Method-local interface declarations from the frozen build. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;
typedef signed int s32;
extern u8 GetGameFlag(u16 flag);


void ReduceBattleChargeForActionFlags(u8 *unit);
void ReduceBattleChargeForActionFlags(u8 *unit)
{
    s16 *charge_time = (s16 *)(unit + 208);
    s32 adjusted_charge = *charge_time;

    adjusted_charge -= 500;

    /* Flags 3 and 4 add independent charge costs; their labels are unresolved. */
    if (GetGameFlag(3))
        adjusted_charge -= 200;
    if (GetGameFlag(4))
        adjusted_charge -= 300;
    if (adjusted_charge < 0)
        adjusted_charge = 0;

    *(u16 *)(unit + 212) = 0;
    *charge_time = (s16)adjusted_charge;
}
