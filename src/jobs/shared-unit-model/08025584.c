/* Method-local interface declarations from the frozen build. */
typedef unsigned char u8;
typedef unsigned short u16;
struct MenuContext { u8 prefix[16]; u16 selected; u8 gap[10]; const void *unit; };
extern struct MenuContext *gMenuContext;
extern u8 ReadChoiceCounter(const void *unit);
extern void ReadChoices(u16 index, u8 *choices);
extern u8 DecodeChoice(u8 code);

asm(".global gMenuContext\n.set gMenuContext,0x0200f438\n.global ReadChoiceCounter\n.thumb_set ReadChoiceCounter,0x080ce411\n.global ReadChoices\n.thumb_set ReadChoices,0x080c9209\n.global DecodeChoice\n.thumb_set DecodeChoice,0x080c9135");
u8 DecodeSelectedUnitChoice(void)
{
    u8 choices[3];
    u8 selected_slot;
    u8 ordinal;
    u8 slot;
    ReadChoices(ReadChoiceCounter(gMenuContext->unit) + 202, choices);
    selected_slot = 0;
    ordinal = 0;
    for (slot = 0; slot <= 2; slot++) {
        if (choices[slot]) {
            if (ordinal == gMenuContext->selected) {
                selected_slot = slot;
                break;
            }
            ordinal++;
        }
    }
    return DecodeChoice(choices[selected_slot]);
}
