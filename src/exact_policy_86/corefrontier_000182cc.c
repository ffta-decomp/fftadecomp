/* Method-local interface declarations from the frozen build. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
struct MenuContext { u8 unknown00[22]; u16 mask22,mask24; u8 unknown1a[14]; u8 flags40; };
struct MissionRecordIdPrefix { u32 mission_id:10; u32 unknown_high:6; } __attribute__((packed));
typedef char MissionIdPrefixSize[sizeof(struct MissionRecordIdPrefix)==2?1:-1];
struct MissionMenuRuntime { const struct MissionRecordIdPrefix *record; u8 unknown04[8]; u16 mission_id; u8 unknown0e[4]; u8 mode; u8 unknown13[161]; u8 available; };
struct SceneFlags {u8 unknown00[0x2fc0];u8 mode_flags;};
typedef char RuntimeModeOffset[(u32)&((struct MissionMenuRuntime*)0)->mode==18?1:-1];
typedef char RuntimeAvailableOffset[(u32)&((struct MissionMenuRuntime*)0)->available==180?1:-1];
typedef char MenuFlagsOffset[(u32)&((struct MenuContext*)0)->flags40==40?1:-1];
extern const u8 *const gMenuText[];
extern struct MissionMenuRuntime gMissionMenu;
extern struct SceneFlags gSceneFlags;
extern u32 GetMissionProperty(u16,u8);
extern u32 ReadSaveByte(u16);
extern u32 CanUseCurrentContent(u8);
__asm__(".global gMenuText\n.set gMenuText,0x0836d678\n.global gMissionMenu\n.set gMissionMenu,0x020020d0\n.global gSceneFlags\n.set gSceneFlags,0x02000000\n.global GetMissionProperty\n.thumb_set GetMissionProperty,0x080ce4dd\n.global ReadSaveByte\n.thumb_set ReadSaveByte,0x080c95a9\n.global CanUseCurrentContent\n.thumb_set CanUseCurrentContent,0x080ced5d");

const u8 *ConfigureMissionMenuChoice(struct MenuContext *menu,u8 kind,u16 *option);
const u8 *ConfigureMissionMenuChoice(struct MenuContext *menu,u8 kind,u16 *option)
{
    const u8 *text=gMenuText[kind];
    switch(kind) {
    case 1: case 2:
        menu->mask22=0x1000;
        menu->mask24=0x8000;
        break;
    case 9: {
        u16 mission;
        menu->mask22=0x1000;
        menu->mask24=0x8000;
        if (gMissionMenu.record)
            mission=gMissionMenu.record->mission_id;
        else mission=gMissionMenu.mission_id;
        if (GetMissionProperty(mission,2)==3) {
            switch(*option) {
            case 1: *option=10; break;
            case 2: *option=11; break;
            }
        }
        if (gMissionMenu.mode==4) {
            u32 alternate=(u8)ReadSaveByte(13)==1;
            switch(*option) {
            case 0:
                if (gMissionMenu.available) {
                    if ((u8)CanUseCurrentContent(1)) *option=15;
                    else *option=13;
                }
                break;
            case 3:
                if (!alternate) *option=12;
                else *option=16;
                break;
            case 4:
                if (!alternate) {
                    if ((u8)CanUseCurrentContent(1)) *option=15;
                    else *option=13;
                }
                break;
            }
        }
        break;
    }
    case 3: case 4: case 10: case 11: case 12: case 13: case 14: case 15:
        menu->flags40=0;
        menu->mask22=0x80;
        menu->mask24=0x100;
        break;
    default: break;
    }
    if ((gSceneFlags.mode_flags&24)==8) {
        menu->mask22=0x1000;
        menu->mask24=0x8000;
    }
    return text;
}
