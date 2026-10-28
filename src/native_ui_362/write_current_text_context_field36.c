typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
struct ActiveTextContextPrefix {u8 unknown[36];u16 value36;};
extern struct ActiveTextContextPrefix *gActiveTextContext;
void SetActiveTextContextValue36(u32) asm("CoreFrontier_00013428");
void SetActiveTextContextValue36(u32 value)
{
    gActiveTextContext->value36=(u16)value;
}
__asm__(".global gActiveTextContext\n.set gActiveTextContext,0x0200918C");
