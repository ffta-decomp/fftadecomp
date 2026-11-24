typedef unsigned char u8;
typedef signed char s8;
typedef signed short s16;
typedef unsigned int u32;

struct OptionsMenuWindow { u8 prefix[17]; u8 selected; };

struct SavedSettings {
    u8 cursor_type:1;
    u8 cursor_speed:2;
    u8 message_speed:2;
    u8 reserved_bit5:1;
    u8 attack_name:1;
    u8 judge_points:1;
    u8 show_exp:1;
    u8 include_unequipped:1;
    u8 l_button:3;
    u8 reserved_byte1:3;
    u8 color_mode:2;
    u8 reserved_byte2:6;
    u8 reserved_byte3;
} __attribute__((packed));
typedef char SettingsSize[sizeof(struct SavedSettings)==4?1:-1];
extern u8 *gSavedOptionsContext;
extern const struct SavedSettings gDefaultSavedSettings;
extern int CompareSavedSettingsBytes(const void *, const void *, int);
extern void ApplySavedCursorSpeed(u8);
extern u32 ReadOptionSelectionRow(void *, s8);
extern void RetailCopyBytes(void *, const void *, u32);
__asm__(".global gSavedOptionsContext\n.set gSavedOptionsContext,0x02009188");
__asm__(".global gDefaultSavedSettings\n.set gDefaultSavedSettings,0x0851ba4e");
__asm__(".global CompareSavedSettingsBytes\n.thumb_set CompareSavedSettingsBytes,0x080096b1");
__asm__(".global ApplySavedCursorSpeed\n.thumb_set ApplySavedCursorSpeed,0x08009921");
__asm__(".global ReadOptionSelectionRow\n.thumb_set ReadOptionSelectionRow,0x08017b69");
__asm__(".global RetailCopyBytes\n.thumb_set RetailCopyBytes,0x081443fd");

/* Query the working copy, or apply the selected value to that same snapshot.
 * A callback may replace the context; retain the original settings pointer. */
u32 QueryOrUpdateSavedOption(u8 option, u8 query)
{
    u8 *context = gSavedOptionsContext;
    struct SavedSettings *settings = (struct SavedSettings *)(context + 0x1bcc);
    if (query) {
        switch (option) {
        case 0: return settings->color_mode;
        case 1: return settings->cursor_type;
        case 2: return settings->cursor_speed;
        case 3: return settings->message_speed != 0;
        case 4: return (((const u8 *)settings)[0] >> 6) & 1;
        case 5: return ((const u8 *)settings)[1] & 1;
        case 6: return settings->judge_points;
        case 7: return (((const u8 *)settings)[1] >> 1) & 1;
        case 8: return settings->l_button;
        case 9: {
            int comparison = CompareSavedSettingsBytes(settings, &gDefaultSavedSettings, 4);
            u32 is_default = 0;
            if (comparison == 0)
                is_default = 1;
            return is_default;
        }
        }
    } else {
        void *selection_view = context + 752;
        struct OptionsMenuWindow *window = (struct OptionsMenuWindow *)(context + 784);
        u32 row_result = ReadOptionSelectionRow(selection_view, (s8)window->selected);
        u8 *current_context = gSavedOptionsContext;
        s16 row = (s16)row_result;
        u32 value;
        current_context += row * 4;
        value = current_context[824];
        switch (option) {
        case 0: settings->color_mode = value; break;
        case 1: settings->cursor_type = value; break;
        case 2:
            settings->cursor_speed = value;
            ApplySavedCursorSpeed(settings->cursor_speed);
            break;
        case 3: settings->message_speed = (0u - value) >> 31; break;
        case 4: settings->attack_name = (0u - value) >> 31; break;
        case 5: settings->show_exp = (0u - value) >> 31; break;
        case 6: settings->judge_points = (0u - value) >> 31; break;
        case 7: settings->include_unequipped = (0u - value) >> 31; break;
        case 8: settings->l_button = value; break;
        case 9:
            if (value == 0)
                return 1;
            {
                u8 *reset_destination = gSavedOptionsContext;
                reset_destination += 0x1bcc;
                RetailCopyBytes(reset_destination, &gDefaultSavedSettings, 4);
            }
            break;
        }
    }
    return 0;
}
