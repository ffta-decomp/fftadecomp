typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
struct LiveUnitContentState {
    u8 unknown_00[7];
    u8 kind;
    u8 unknown_08[32];
    u16 flags;
    u8 unknown_2a[22];
    u8 content_markers[0];
};
typedef char UnitContentPrefixSize[(sizeof(struct LiveUnitContentState)==64)?1:-1];
extern u32 GetUnitProperty(struct LiveUnitContentState *unit, u32 property);
__asm__(".thumb_set GetUnitProperty, 0x080c92f1");
