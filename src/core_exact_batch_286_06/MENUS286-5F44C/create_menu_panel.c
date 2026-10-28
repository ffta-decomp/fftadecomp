typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
struct PanelDescriptor { u8 opaque0[20]; u16 selector; u16 slot; u32 opaque24; };
struct MenuPanelContext { void *parent; void *opaque4; void *panels[2]; u8 flags[2]; };
extern struct MenuPanelContext *gMenuContext;
extern void MenuPanelCallback(void *);
extern void *CreatePanelTask(void *,void (*)(void *),unsigned,const struct PanelDescriptor *,unsigned);
__asm__(".global gMenuContext\n.set gMenuContext,0x0200f44c\n.global MenuPanelCallback\n.thumb_set MenuPanelCallback,0x0806094d\n.global CreatePanelTask\n.thumb_set CreatePanelTask,0x08005955");
void CreateMenuPanel(u8 selector)
{
    struct PanelDescriptor descriptor;
    struct MenuPanelContext *context;
    void *child;
    int slot;
    if(gMenuContext->panels[0]==0) slot=0;
    else if(gMenuContext->panels[1]==0) slot=1;
    else for(;;) {}
    descriptor.selector=selector;
    descriptor.slot=slot;
    child=CreatePanelTask(gMenuContext->parent,MenuPanelCallback,152,&descriptor,0);
    context=gMenuContext;
    context->panels[slot]=child;
    context->flags[slot]=0;
}
