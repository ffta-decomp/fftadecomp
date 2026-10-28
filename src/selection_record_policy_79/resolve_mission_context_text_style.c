/* Method-local interface declarations from the frozen build. */
typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct {
    u8 before_mode[11];
    u8 mode;
    u16 format;
    u8 unknown_0e;
    s8 initialized;
    u8 before_scales[6];
    u16 scale_x;
    u16 scale_y;
    u8 before_dimensions[3];
    u8 columns;
    u8 rows;
    u8 field_1f;
    u8 before_field22[2];
    u16 field_22;
    u8 before_clear[4];
    u8 clear_state;
    u8 before_variant[2];
    u8 variant;
    u8 before_flags[14];
    u16 flags;
} TextContext;

typedef struct {
    u16 mission_id:10;
    u16 other_bits:6;
} __attribute__((packed)) SelectedMission;

typedef struct {
    SelectedMission *selected;
    u8 before_fallback[8];
    u16 fallback_id;
    u8 before_mode[4];
    u8 mode;
    u8 before_enabled[161];
    u8 enabled;
} MissionTextContext;

#define FIELD_OFFSET(type, field) ((u32)&(((type *)0)->field))
typedef char FormatOffset[(FIELD_OFFSET(TextContext, format) == 12) ? 1 : -1];
typedef char ScaleOffset[(FIELD_OFFSET(TextContext, scale_x) == 22) ? 1 : -1];
typedef char DimensionOffset[(FIELD_OFFSET(TextContext, columns) == 29) ? 1 : -1];
typedef char VariantOffset[(FIELD_OFFSET(TextContext, variant) == 43) ? 1 : -1];
typedef char FlagsOffset[(FIELD_OFFSET(TextContext, flags) == 58) ? 1 : -1];
typedef char MissionModeOffset[(FIELD_OFFSET(MissionTextContext, mode) == 18) ? 1 : -1];
typedef char EnabledOffset[(FIELD_OFFSET(MissionTextContext, enabled) == 180) ? 1 : -1];

extern const u8 *gFixedTextPointers[];
extern MissionTextContext gMissionTextContext;
extern u8 gEwramTextState[];
extern const u8 *LookupCodeText(u32 code);
extern u32 RemapCode(u32 code);
extern u32 GetMissionProperty(u32 mission_id, u32 selector);
extern u32 ReadSaveByte(u32 selector);
extern u32 CanUseCurrentContent(u32 kind);

asm(".global gFixedTextPointers\n.set gFixedTextPointers,0x0836d678\n"
    ".global gMissionTextContext\n.set gMissionTextContext,0x020020d0\n"
    ".global gEwramTextState\n.set gEwramTextState,0x02000000\n"
    ".global LookupCodeText\n.thumb_set LookupCodeText,0x08009a25\n"
    ".global RemapCode\n.thumb_set RemapCode,0x08009a91\n"
    ".global GetMissionProperty\n.thumb_set GetMissionProperty,0x080ce4dd\n"
    ".global ReadSaveByte\n.thumb_set ReadSaveByte,0x080c95a9\n"
    ".global CanUseCurrentContent\n.thumb_set CanUseCurrentContent,0x080ced5d\n");


/* Select text/style and adjust mission-context codes; meanings remain provisional. */
const u8 *ResolveMissionContextTextStyle(TextContext *output, u32 selector_arg,
                              u16 *code, u8 *reset_output)
{
    u32 selector = (u8)selector_arg;
    const u8 *text = 0;
    u32 mapped_code;
    u32 mission_id;
    u32 save_choice;

    *reset_output = (u32)text;
    text = gFixedTextPointers[selector];
    switch (selector) {
    case 1: case 2:
        output->columns = 13;
        output->rows = 3;
        output->format = 2048;
        output->mode = 16;
        output->field_1f = 11;
        output->flags |= 6;
        if (selector == 2 || *code == 37)
            output->flags |= 64;
        break;
    case 3: case 4: case 5:
        if (selector == 3) {
            text = LookupCodeText(*code);
            mapped_code = RemapCode(*code);
            *code = mapped_code;
            output->format = 32;
            output->mode = 128;
            output->variant = 1;
        } else if (selector == 5) {
            text = LookupCodeText(*code);
            mapped_code = RemapCode(*code);
            *code = mapped_code;
            output->format = 4096;
        } else {
            output->format = 48;
            output->mode = 130;
            output->variant = 2;
        }
        output->clear_state = 0;
        output->scale_x = 128;
        output->scale_y = 256;
        output->columns = 21;
        output->rows = 4;
        output->field_1f = 11;
        if (output->initialized == 0)
            output->initialized = 1;
        break;
    case 8:
        output->format = 192;
        output->flags |= 96;
        output->field_22 = 2;
        break;
    case 9:
        output->format = 192;
        output->flags |= 16;
        if (gMissionTextContext.selected != 0)
            mission_id = gMissionTextContext.selected->mission_id;
        else
            mission_id = gMissionTextContext.fallback_id;
        if (GetMissionProperty(mission_id, 2) == 3) {
            switch (*code) {
            case 1: *code = 10; break;
            case 2: *code = 11; break;
            }
        }
        if (gMissionTextContext.mode == 4) {
            save_choice = ((u8)ReadSaveByte(13) == 1);
            switch (*code) {
            case 0:
                if (gMissionTextContext.enabled != 0) {
                    if ((u8)CanUseCurrentContent(1) != 0)
                        *code = 15;
                    else
                        *code = 13;
                }
                break;
            case 3:
                if (save_choice == 0)
                    *code = 12;
                else
                    *code = 16;
                break;
            case 4:
                if (save_choice == 0) {
                    if ((u8)CanUseCurrentContent(1) != 0)
                        *code = 15;
                    else
                        *code = 13;
                }
                break;
            }
        }
        break;
    case 16: case 17: case 18: case 19: case 20: case 21:
    case 22: case 23: case 24: case 25: case 26:
        output->columns = 13;
        output->rows = 3;
        output->format = 2048;
        output->mode = 16;
        output->field_1f = 11;
        output->flags |= 74;
        break;
    case 6: case 7:
        output->format = 4096;
        break;
    case 10: case 11: case 12: case 13: case 14: case 15:
        output->clear_state = 0;
        output->scale_x = 128;
        output->scale_y = 256;
        output->columns = 21;
        output->rows = 4;
        output->format = 32;
        output->mode = 128;
        output->field_1f = 11;
        output->variant = 1;
        if (output->initialized == 0)
            output->initialized = 1;
        break;
    }

    if ((gEwramTextState[0x2fc0] & 24) == 8) {
        output->scale_x = 4096;
        output->scale_y = 32768;
    }
    return text;
}
