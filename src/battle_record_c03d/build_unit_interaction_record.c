/* Method-local interface declarations from the frozen build. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

#define RETAIL_THUMB_ALIAS(symbol, address) \
    __asm__(".global " #symbol "\n.thumb_set " #symbol ", " address "\n")

RETAIL_THUMB_ALIAS(BuildRecordFields, "0x080c2315");
RETAIL_THUMB_ALIAS(ReadRecordByte16, "0x0813413d");
RETAIL_THUMB_ALIAS(GetCurrentContentContext, "0x08096d7d");
RETAIL_THUMB_ALIAS(FindContentRecord, "0x08099545");
RETAIL_THUMB_ALIAS(TestContentRecord, "0x0812e4a9");
RETAIL_THUMB_ALIAS(UnitStateE8HasBit7, "0x080cd945");
RETAIL_THUMB_ALIAS(TestUnitState, "0x080c82b9");
RETAIL_THUMB_ALIAS(TestInteraction, "0x0813569d");

extern u32 BuildRecordFields(u32 first_unit, u32 second_unit,
                             u32 first_value, u32 second_value,
                             u32 output_04, u32 output_0c,
                             u32 output_0e, u32 output_11,
                             u32 third_value);
extern u32 ReadRecordByte16(u32 unit, u32 first_value);
extern u32 GetCurrentContentContext(void);
extern u32 FindContentRecord(u32 content_context);
extern u32 TestContentRecord(u32 unit);
extern u32 UnitStateE8HasBit7(u32 unit);
extern u32 TestUnitState(u32 unit);
extern u32 TestInteraction(u32 first_unit, u32 second_unit,
                           u32 first_value, u32 zero);

void CoreRegion30_000C2618(u8 *output, u8 *first_context,
                             u8 *second_context, u32 first_arg,
                             u32 second_arg, u32 third_arg);


#define READ_UNIT(context) (*(const u32 *)(context))

void BuildUnitInteractionRecord(u8 *output, u8 *first_context,
                             u8 *second_context, u32 first_arg,
                             u32 second_arg, u32 third_arg)
{
    u16 first_value = (u16)first_arg;
    u16 second_value = (u16)second_arg;
    u16 third_value = (u16)third_arg;
    u8 saved_unit_byte;
    u32 result;
    u32 content_context;
    u32 content_record;

    *(u16 *)(output + 0) = first_value;
    *(u16 *)(output + 2) = second_value;
    saved_unit_byte = *(u8 *)(READ_UNIT(first_context) + 248);
    *(u8 *)(READ_UNIT(first_context) + 248) =
        *(u8 *)(READ_UNIT(second_context) + 248);

    result = BuildRecordFields(READ_UNIT(first_context),
                               READ_UNIT(second_context),
                               first_value, second_value,
                               (u32)(output + 4), (u32)(output + 12),
                               (u32)(output + 14), (u32)(output + 17),
                               third_value);
    *(u16 *)(output + 10) = (u8)result;
    *(u8 *)(READ_UNIT(first_context) + 248) = saved_unit_byte;
    if (*(u16 *)(output + 10) == 0)
        return;

    output[16] = (u8)ReadRecordByte16(READ_UNIT(first_context), first_value);
    content_context = GetCurrentContentContext();
    content_record = FindContentRecord(content_context);
    if (content_record == 0)
        return;
    if ((u8)TestContentRecord(*(u32 *)content_record) == 0)
        return;
    if ((u8)UnitStateE8HasBit7(READ_UNIT(first_context)) != 0)
        return;
    if ((u8)TestUnitState(READ_UNIT(first_context)) != 0)
        return;
    if ((u8)TestInteraction(READ_UNIT(first_context),
                            READ_UNIT(second_context), first_value, 0) != 0)
        output[17] |= 2;
}
