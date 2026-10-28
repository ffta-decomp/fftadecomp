/* Method-local interface declarations from the frozen build. */
typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef unsigned int u32;
struct OptionContext { u8 unknown_00[8]; u8 mode; u8 unknown_09[135]; s8 *options; };
typedef char OptionsOffsetCheck[(unsigned)&((struct OptionContext *)0)->options == 144 ? 1 : -1];
extern u8 GetGameFlag(u16 flag);
extern u32 CountAvailableMissionRecords(void *output, u32 limit);
extern u16 CountSelectedRecordFlags(void);
extern u32 CountNonzeroFourByteRecords(void *output);
extern u32 CountNonzeroSavedHalfwords(void *output);
extern u32 CountActiveContextRecords(struct OptionContext *context, void *output);
__asm__(".global GetGameFlag\n.thumb_set GetGameFlag, 0x80c9541");
__asm__(".global CountAvailableMissionRecords\n.thumb_set CountAvailableMissionRecords, 0x80d0ab1");
__asm__(".global CountSelectedRecordFlags\n.thumb_set CountSelectedRecordFlags, 0x80ce8a9");
__asm__(".global CountNonzeroFourByteRecords\n.thumb_set CountNonzeroFourByteRecords, 0x8050c75");
__asm__(".global CountNonzeroSavedHalfwords\n.thumb_set CountNonzeroSavedHalfwords, 0x8050ca5");
__asm__(".global CountActiveContextRecords\n.thumb_set CountActiveContextRecords, 0x8050ce9");

u32 RefreshContextOptionAvailability(struct OptionContext *context);
u32 RefreshContextOptionAvailability(struct OptionContext *context)
{
    if (context->mode != 1)
        return 0;
    if (GetGameFlag(0x207)) {
        s8 **options = &context->options;
        u32 previous_first = (u8)(*options)[3];
        u32 previous_second = (u8)(*options)[4];
        u32 count;
        u16 selected_count;
        u8 active_count;
        count = CountAvailableMissionRecords(0, 16);
        if (count == 0)
            (*options)[0] = count;
        selected_count = CountSelectedRecordFlags();
        if (selected_count == 0)
            (*options)[1] = selected_count;
        active_count = (u8)CountNonzeroFourByteRecords(0);
        if (active_count == 0)
            (*options)[3] = active_count;
        active_count = (u8)CountNonzeroSavedHalfwords(0);
        if (active_count == 0)
            (*options)[4] = active_count;
        count = CountActiveContextRecords(context, 0);
        if (count == 0)
            (*options)[5] = count;
        {
            u32 changed = 0;
            if (previous_first != (*options)[3] || previous_second != (*options)[4])
                changed = 1;
            return changed;
        }
    } else {
        s8 **options = &context->options;
        u32 previous_first = (u8)(*options)[3];
        u32 count;
        u16 selected_count;
        u8 active_count;
        count = CountAvailableMissionRecords(0, 16);
        if (count == 0)
            (*options)[0] = count;
        selected_count = CountSelectedRecordFlags();
        if (selected_count == 0)
            (*options)[1] = selected_count;
        active_count = (u8)CountNonzeroFourByteRecords(0);
        if (active_count == 0)
            (*options)[3] = active_count;
        count = CountActiveContextRecords(context, 0);
        if (count == 0)
            (*options)[4] = count;
        return previous_first != (*options)[3];
    }
}
