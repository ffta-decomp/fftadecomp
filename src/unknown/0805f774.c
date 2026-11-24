typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef signed short s16;
extern u8 *gMenuContext;
extern int GetLastMenuRow(void *);
extern void PlayMenuSound(unsigned);
extern void RebuildMenuView(void *);
__asm__(".global gMenuContext\n.set gMenuContext,0x0200f44c\n.global GetLastMenuRow\n.thumb_set GetLastMenuRow,0x08017be9\n.global PlayMenuSound\n.thumb_set PlayMenuSound,0x08141541\n.global RebuildMenuView\n.thumb_set RebuildMenuView,0x0806025d");
void NavigateMenuPage(u8 *view,u8 direction)
{
    u8 *widget=view+60;
    u8 *control=view+92;
    u16 *output=(u16 *)(gMenuContext+296+4*view[0]);
    int initial=*(s16 *)(widget+26);
    int start=initial;
    int bound=(s16)GetLastMenuRow(widget)+1;
    unsigned cursor=control[17];
    int remaining=*(s8 *)(view+1);
    while(remaining!=0) {
        --remaining;
        if(direction==128) {
            int step=*(s8 *)(view+1);
            if(start+step<bound) ++start;
            else {
                remaining=0;
                if(initial==bound-step) cursor=step-1;
            }
        } else {
            if(start>0) --start;
            else {
                remaining=0;
                if(initial==0) cursor=0;
            }
        }
    }
    if(initial!=start || control[17]!=cursor) {
        output[0]=start;
        output[1]=cursor;
        PlayMenuSound(109);
        RebuildMenuView(view);
    }
}
