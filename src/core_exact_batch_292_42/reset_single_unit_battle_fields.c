#ifndef SINGLE_UNIT_BATTLE_RESET_INTERFACES_H
#define SINGLE_UNIT_BATTLE_RESET_INTERFACES_H
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
struct BattleUnitFieldView;
typedef void (*UnitClearFunction)(void *,u32);
extern UnitClearFunction const gUnitClearFunction;
extern u32 ReadUnitField(const struct BattleUnitFieldView *,u8 selector);
__asm__(
".global gUnitClearFunction\n.set gUnitClearFunction,0x0836D4B8\n"
".global ReadUnitField\n.thumb_set ReadUnitField,0x080C7EA5\n");
#endif


/* Preserve the two original value queries and the distinct clear ranges;
 * existing unit-field and RAM-clear implementations remain unchanged. */
void ResetSingleUnitBattleFields(struct BattleUnitFieldView *unit)
{
    register u8 *unit_phase asm("r4") = (u8 *)unit;
    register u32 zero_phase asm("r5");
    register u16 *halfword_cursor asm("r0");
    u32 value;
    {
        register const struct BattleUnitFieldView *first_query_unit asm("r0") = unit;
        /* Both original pointer homes are defined before the first query. */
        asm("" : : "r"(unit_phase), "r"(first_query_unit));
        value = ReadUnitField(first_query_unit,20);
    }
    zero_phase = 0;
    asm("" : "+r"(zero_phase));
    *(u16 *)(unit_phase + 24) = value;
    value = ReadUnitField((const struct BattleUnitFieldView *)unit_phase,22);
    *(u16 *)(unit_phase + 28) = value;
    halfword_cursor = (u16 *)(unit_phase + 208);
    asm("" : "+r"(halfword_cursor));
    *halfword_cursor = zero_phase;
    halfword_cursor += 2;
    asm("" : "+r"(halfword_cursor));
    *halfword_cursor = zero_phase;
    {
        register UnitClearFunction const *clear_cell asm("r5") = &gUnitClearFunction;
        asm("" : "+r"(clear_cell));
        halfword_cursor += 10;
        asm("" : "+r"(halfword_cursor));
        (*clear_cell)(halfword_cursor,8);
        unit_phase += 216;
        asm("" : "+r"(unit_phase));
        (*clear_cell)(unit_phase,16);
    }
}
