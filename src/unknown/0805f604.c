typedef unsigned char u8;
struct MenuPanelContext { void *parent; void *opaque4; void *panels[2]; u8 flags[2]; };
extern struct MenuPanelContext *gMenuContext;
extern u8 *GetPanelData(void *);
__asm__(".global gMenuContext\n.set gMenuContext,0x0200f44c\n.global GetPanelData\n.thumb_set GetPanelData,0x08005bfd");
unsigned QueryMenuCompletion(void)
{
    unsigned busy=0;
    unsigned missing_flags=0;
    unsigned registered=0;
    int i;
    for(i=0;i<2;++i) {
        struct MenuPanelContext *context=gMenuContext;
        void *handle=context->panels[i];
        if(handle!=0) {
            if(GetPanelData(handle)[2]!=0) ++busy;
            ++registered;
        } else missing_flags+=context->flags[i];
    }
    if(missing_flags!=0) {
        if(registered==0) return 1;
        {
            unsigned result=busy;
            if(result!=0) result=1;
            return result;
        }
    }
    if(registered==2) {
        unsigned complete=0;
        if(busy==2) complete=1;
        return complete;
    }
    return busy;
}
