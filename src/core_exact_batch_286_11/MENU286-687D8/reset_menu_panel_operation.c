typedef unsigned char u8;
typedef unsigned int u32;
struct MenuPanel {
    u8 unknown00[9];
    u8 callback_id;
    u8 unknown0a[4];
    u8 pending;
    u8 unknown0f[13];
    u8 text_value;
    u8 unknown1d[7];
    u8 text_control[76];
    u8 child[20];
};
extern void SetPanelTextValue(void *,u32);
extern void ConfigurePanelChild(void *,u32);
extern u32 RegisterPanelCallback(u32,void *);
asm(".global SetPanelTextValue\n.thumb_set SetPanelTextValue,0x08017509\n"
    ".global ConfigurePanelChild\n.thumb_set ConfigurePanelChild,0x08017d19\n"
    ".global RegisterPanelCallback\n.thumb_set RegisterPanelCallback,0x080098f5\n");
void ResetMenuPanelOperation(struct MenuPanel *panel)
    asm("RemainingCore48_000687D8");
void ResetMenuPanelOperation(struct MenuPanel *panel)
{
    SetPanelTextValue(panel->text_control,panel->text_value);
    ConfigurePanelChild(panel->child,0);
    panel->pending=0;
    panel->callback_id=RegisterPanelCallback(0x08066e09,panel);
}
