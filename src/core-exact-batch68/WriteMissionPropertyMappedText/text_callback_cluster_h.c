typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

#define TEXT_CONTEXT ((volatile u8 *)0x020020d0)
#define JOB_CONTENT_POINTERS ((const u32 *)0x085567f0)
#define CONTEXT_COUNT (*(volatile const u8 *)0x020021c6)
#define CONTEXT_INDEXED_WORDS ((const u32 *)0x08569034)
typedef struct __attribute__((packed)) {
    u16 mission_id : 10;
    u16 unknown_id_bits : 6;
} PackedMissionRecord;
typedef char MissionRecordSize[sizeof(PackedMissionRecord) == 2 ? 1 : -1];
#define SELECTED_RECORD_ID(record) \
    (((const volatile PackedMissionRecord *)(record))->mission_id)

extern const volatile u32 MissionRequirementContentPointers[];
__asm__(".global MissionRequirementContentPointers\n.set MissionRequirementContentPointers,0x085567f0\n");

extern u32 GetMissionProperty(u16 mission_id, u8 selector);
extern u32 DecodeMissionItemId(u8 encoded_item_id);
extern u32 GetContentPointer123(u16 content_index);
extern u32 CopyEncodedTextToBuffer(u8 *output, const u8 *source);
extern u32 WriteUnsignedNumberText(u8 *output, u32 value);
extern u32 WriteTextControlMarker(u8 *output, u8 marker);

#if defined(CALLBACK_H_1920C)
u32 WriteMissionConditionalByteText(u8 *output)
{
    const volatile u8 *record =
        (const volatile u8 *)(*(volatile const u32 *)TEXT_CONTEXT);
    /* Retail keeps this selected byte live in r2 across the flag test. */
    register u32 value __asm__("r2") = record[3];

    if ((record[2] & 0x1c) != 0) {
        u16 mission_id = SELECTED_RECORD_ID(record);
        value = (u8)GetMissionProperty(mission_id, 0x10);
        if (value == 0)
            value = 0xff;
    }

    if (value == 0xff) {
        CopyEncodedTextToBuffer(output,
            (const u8 *)*(const volatile u32 *)0x08526680);
        return 8;
    }

    WriteUnsignedNumberText(output, value);
    return 0;
}
#elif defined(CALLBACK_H_19268)
u32 WriteMissionPackedByteText(u8 *output)
{
    const volatile u8 *record =
        (const volatile u8 *)(*(volatile const u32 *)TEXT_CONTEXT);
    u8 value = (u8)(((record[2] & 3) << 6) | (record[1] >> 2));

    WriteUnsignedNumberText(output, value);
    return 0;
}
#elif defined(CALLBACK_H_1928C)
u32 WriteContextIndexedWordText(u8 *output)
{
    u8 count = CONTEXT_COUNT;
    if (count == 0)
        return 0;

    count = CONTEXT_COUNT;
    CopyEncodedTextToBuffer(output, (const u8 *)CONTEXT_INDEXED_WORDS[count]);
    return 0;
}
#elif defined(CALLBACK_H_192C0)
u32 WriteMissionPropertyMappedText(u8 *output, u32 parameter)
{
    u8 parameter_u8 = (u8)parameter;
    volatile u8 *record =
        (volatile u8 *)(*(volatile const u32 *)TEXT_CONTEXT);
    u8 *cursor = output;
    u32 field_address = (u32)record + parameter_u8;
    u8 field;
    u16 content_index;
    u8 selector;
    u16 first_property;

    field_address -= 0x1e;
    field = *(volatile u8 *)field_address;
    content_index = (u16)DecodeMissionItemId(field);
    if (content_index == 0) {
        CopyEncodedTextToBuffer(cursor,
            (const u8 *)*(const volatile u32 *)0x08526680);
        return 0;
    }

    selector = 0;
    switch (parameter_u8) {
    case 0x22:
        selector = 0x2a;
        break;
    case 0x23:
        selector = 0x2c;
        break;
    default:
        break;
    }

    first_property = (u16)GetMissionProperty(SELECTED_RECORD_ID(record), selector);
    if (first_property != 0)
        cursor += (u16)WriteTextControlMarker(cursor, 3);

    cursor += (u16)CopyEncodedTextToBuffer(
        cursor, (const u8 *)GetContentPointer123(content_index));

    /* Retail reloads the ID bytes here while retaining the original record pointer. */
    if (GetMissionProperty(SELECTED_RECORD_ID(record),
                           (u8)(selector + 1)) != 0) {
        cursor += (u16)CopyEncodedTextToBuffer(
            cursor, (const u8 *)MissionRequirementContentPointers[66]);
    }

    if (first_property != 0)
        WriteTextControlMarker(cursor, 0);
    return 0;
}
#else
#error Select one callback-cluster-H entry
#endif
