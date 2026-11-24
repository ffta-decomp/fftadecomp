typedef unsigned char u8;
typedef unsigned int u32;
extern u32 GetUnitProperty(const u8 *,u8);


asm(".global GetUnitProperty\n.thumb_set GetUnitProperty,0x080c92f1");
u32 HasUnitJobProperty22Flag80(const u8 *) asm("CoreContinuation_0012C960");

/* Both original branches define a full-word numeric return before the join.
 * Input-only operands preserve those initialized definitions without changing
 * a value or emitting an instruction. Callers may consume LOW8. */
u32 HasUnitJobProperty22Flag80(const u8 *unit)
{
    u32 result;
    if ((GetUnitProperty(unit, 22) & 128) != 0) {
        result = 1;
        asm("" : : "r"(result));
    } else {
        result = 0;
        asm("" : : "r"(result));
    }
    return result;
}
