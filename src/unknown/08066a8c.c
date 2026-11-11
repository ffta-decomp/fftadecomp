typedef unsigned char u8;
typedef unsigned int u32;
struct PanelTextControl {
    u8 unknown00[16];
    u8 column,row,width;
};
struct MarkerPanel {
    u8 unknown00[8];
    u8 mode;
    u8 unknown09[27];
    struct PanelTextControl text;
};
extern const u8 gPanelModeMarker[];
extern void DrawPanelMarker(const u8 *,int,int,u32,u32,u32,u32,u32,u32,u32,u32);
asm(".global gPanelModeMarker\n.set gPanelModeMarker,0x08393ade\n"
    ".global DrawPanelMarker\n.thumb_set DrawPanelMarker,0x08001f35\n");
void DrawMenuModeMarker(struct MarkerPanel *panel)
    asm("RemainingCore48_00066A8C");
void DrawMenuModeMarker(struct MarkerPanel *panel)
{
    struct PanelTextControl *text=&panel->text;
    if ((u8)(panel->mode-5)<=1)
        DrawPanelMarker(gPanelModeMarker,((text->column+text->width)<<3)-40,
                        (text->row<<3)-4,0,0,0,0,0,0,0,0);
}
