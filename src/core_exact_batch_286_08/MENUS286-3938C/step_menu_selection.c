typedef unsigned char u8;
typedef unsigned short u16;
struct MenuSelection { u8 opaque[0xf1c]; u8 count; u8 opaque1[2]; u8 selected; u8 mirror; };
extern struct MenuSelection *gMenuSelection;
extern u16 gMenuKeys[];
__asm__(".global gMenuSelection\n.set gMenuSelection,0x03002810\n.global gMenuKeys\n.set gMenuKeys,0x03000000");
unsigned StepMenuSelection(unsigned unused0,void *unused1,unsigned unused2,unsigned flags)
{
    unsigned result=0;
    if(flags&1) {
        unsigned keys=gMenuKeys[2]&192;
        if(keys&128) {
            unsigned next=gMenuSelection->selected+1;
            struct MenuSelection *context;
            unsigned count;
            gMenuSelection->selected=next;
            context=gMenuSelection;
            count=context->count;
            if((u8)next>=count) { context->selected=count-1; result=2; }
        } else if(keys&64) {
            unsigned next=gMenuSelection->selected-1;
            gMenuSelection->selected=next;
            if((u8)next==255) {gMenuSelection->selected=0; result=1;}
        }
    }
    gMenuSelection->mirror=gMenuSelection->selected;
    return result;
}
