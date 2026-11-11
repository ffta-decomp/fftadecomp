typedef unsigned char u8;
typedef unsigned short u16;
struct SlotChoice { u16 observed0;u8 choice;u8 observed3; };
struct MenuChoiceView {u8 observed_prefix[296];struct SlotChoice slots[0];};
extern struct MenuChoiceView *gMenuChoiceContext;
__asm__(".global gMenuChoiceContext\n.set gMenuChoiceContext,0x0200f44c");
unsigned QueryMenuSlotChoice(u8 slot) {
 unsigned offset;
 register u8 *base __asm__("r1");
 struct MenuChoiceView **cell=&gMenuChoiceContext;
 __asm__("" : "+r"(cell));
 offset=4*slot+296;
 __asm__("" : "+r"(offset));
 base=(u8 *)*cell;
 base+=offset;
 __asm__("" : "+r"(base));
 return base[2];
}
