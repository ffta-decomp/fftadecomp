typedef unsigned char u8;
struct MenuPanelContext { void *parent; void *opaque4; void *panels[2]; };
extern struct MenuPanelContext *gMenuContext;
extern u8 *GetPanelData(void *);
__asm__(".global gMenuContext\n.set gMenuContext,0x0200f44c\n.global GetPanelData\n.thumb_set GetPanelData,0x08005bfd");
void RouteMenuPanelState(u8 selector,u8 mode)
{
    u8 *child=0;
    int i;
    unsigned state;
    if(selector==0) {
        void *handle=gMenuContext->panels[0];
        if(handle==0) return;
        child=GetPanelData(handle);
    } else {
        for(i=0;i<2;++i) {
            void *handle=gMenuContext->panels[i];
            if(handle!=0) {
                child=GetPanelData(handle);
                if(child[0]==selector) break;
            }
        }
        if(i==2) return;
    }
    state=2;
    if(mode!=0) state=6;
    child[2]=state;
}
