typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct MissionContentContext {
    u32 selected_record_address;
    u32 tagged_content;
} MissionContentContext;
extern volatile MissionContentContext gContentState;
#define TEXT_CONTEXT ((volatile u8 *)&gContentState)
extern volatile const u32 MissionContextTextPointers[];
__asm__(".global MissionContextTextPointers\n.set MissionContextTextPointers, 0x08526680");
#define CONTEXT_TEXT_POINTERS_08526680 MissionContextTextPointers

extern u32 GetItemProperty(u16 item_id, u8 property_id);
extern u16 DecodeMissionItemId(u8 encoded_id);
extern u32 GetContentPointer123(u16 content_index);
extern u32 ResolveContextTextPointerFromByte(u16 encoded_value);
extern u32 ResolveContextRecordTextPointer(const void *record);
extern u16 CopyEncodedTextToBuffer(u8 *output, const u8 *source);

#if defined(FFTA_TEXT_CALLBACK_M_197BC)
u32 WriteContextCategorySelectedText(u8 *output)
{
    u32 context_word = gContentState.tagged_content;
    u16 category = (u16)(context_word >> 16);
    u16 context_value = (u16)context_word;
    const u8 *source;

    switch (category) {
    case 1: {
        u16 content_index = DecodeMissionItemId((u8)context_value);
        source = (const u8 *)GetContentPointer123(content_index);
        break;
    }
    case 2:
        source = (const u8 *)ResolveContextTextPointerFromByte(context_value);
        break;
    default: {
        volatile const u32 *text_pointers = CONTEXT_TEXT_POINTERS_08526680;
        u32 item_text_index = GetItemProperty(context_value, 0);
        source = (const u8 *)text_pointers[item_text_index];
        break;
    }
    }

    CopyEncodedTextToBuffer(output, source);
    return 0;
}
#endif

#if defined(FFTA_TEXT_CALLBACK_M_19814)
u32 WriteContextRecordSelectedText(u8 *output)
{
    u32 context_word = gContentState.tagged_content;
    const u8 *resolved_source = (const u8 *)
        ResolveContextRecordTextPointer((const void *)context_word);

    if (context_word != 0) {
        CopyEncodedTextToBuffer(output, resolved_source);
    } else {
        const u8 *fallback_source =
            (const u8 *)CONTEXT_TEXT_POINTERS_08526680[0];
        CopyEncodedTextToBuffer(output, fallback_source);
    }

    return 0;
}
#endif
