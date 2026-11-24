typedef signed short s16;
struct MenuContextPrefix { void *parent; };
extern struct MenuContextPrefix *gMenuContext;
extern void *GetParentPanelData(void *);
extern unsigned QueryPanelDecision(void *);
__asm__(".global gMenuContext\n.set gMenuContext,0x0200f44c\n.global GetParentPanelData\n.thumb_set GetParentPanelData,0x08005a25\n.global QueryPanelDecision\n.thumb_set QueryPanelDecision,0x0805f605");
int QueryMenuPanelStatus(void)
{
    if(gMenuContext==0 || gMenuContext->parent==0) return -1;
    return (s16)QueryPanelDecision(GetParentPanelData(gMenuContext->parent));
}
