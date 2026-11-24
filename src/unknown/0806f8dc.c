typedef unsigned char u8;
typedef unsigned short u16;
extern u8 PanelTransition(u8 *, int);
extern void LoadSelection(void *, u16);
extern void DrawSelection(void *, u16);
extern void UpdateSelection(u8 *);
u8 SceneTaskDependency_0006F8DC(u8 *p, u16 selection)
{
    u8 i;
    u8 *flags;
    p[0x1ed0] = 0;
    switch(p[0]) {
    case 0:
        if (PanelTransition(p,0)) p[0]=1;
        break;
    case 1:
        if (*(u16 *)(p+6) != selection) {
            *(u16 *)(p+6)=selection;
            LoadSelection(*(u8 **)0x0200f428+0x1a88,*(u16 *)(p+6));
            DrawSelection(*(u8 **)0x0200f428+0x1a88,*(u16 *)(p+6));
            i=0;
            flags = p+2;
            for(;i<3;i++) flags[i]=0;
        }
        UpdateSelection(p);
        break;
    case 2:
        p[1]=0;
        p[0]=3;
        break;
    case 3:
        if (PanelTransition(p,1)) p[0]=4;
        break;
    case 4:
        break;
    }
    return p[0];
}
asm(".global PanelTransition\n.thumb_set PanelTransition, 0x0806fe1d\n.global LoadSelection\n.thumb_set LoadSelection, 0x0806fabd\n.global DrawSelection\n.thumb_set DrawSelection, 0x0806fb51\n.global UpdateSelection\n.thumb_set UpdateSelection, 0x0806f995");
