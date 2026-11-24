typedef unsigned char u8;
typedef unsigned short u16;
struct SavedOptionsCloseFields {
    u8 unknown00[174];
    u8 field174;
    u8 unknown175;
    u16 field176;
};
struct SavedOptionsContext;
extern struct SavedOptionsCloseFields gSavedOptionsCloseFields;
extern struct SavedOptionsContext *gSavedOptionsContext;
__asm__(".global gSavedOptionsCloseFields\n.set gSavedOptionsCloseFields,0x020020d0");
__asm__(".global gSavedOptionsContext\n.set gSavedOptionsContext,0x02009188");

void ClearSavedOptionsContext(void)
{
    struct SavedOptionsCloseFields *section = &gSavedOptionsCloseFields;
    section->field174 = 0;
    section->field176 = 0;
    gSavedOptionsContext = 0;
}
