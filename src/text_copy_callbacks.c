typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

extern u16 CopyEncodedTextToBuffer(u8 *output, const u8 *source);

typedef struct {
    const u8 *primary_text;
    u8 reserved_04[4];
    const u8 *secondary_text;
} TextCallbackContext;

#define TEXT_CONTEXT ((volatile TextCallbackContext *)0x020020d0)

#if defined(CONFIRMED_PLAYER_NAME)
u32 WriteConfirmedPlayerName(u8 *output)
{
    CopyEncodedTextToBuffer(output, (const u8 *)0x02001f1c);
    return 0;
}
#elif defined(SECONDARY_STORED_TEXT)
u32 WriteSecondaryStoredText(u8 *output)
{
    /* The source at 0x020021a0 is observed but its owner is unresolved. */
    CopyEncodedTextToBuffer(output, (const u8 *)0x020021a0);
    return 0;
}
#elif defined(CONTEXT_SECONDARY_TEXT)
u32 WriteContextSecondaryText(u8 *output)
{
    const u8 *source = TEXT_CONTEXT->secondary_text;
    CopyEncodedTextToBuffer(output, source);
    return 0;
}
#elif defined(CONTEXT_PRIMARY_TEXT)
u32 WriteContextPrimaryText(u8 *output)
{
    const u8 *source = TEXT_CONTEXT->primary_text;
    CopyEncodedTextToBuffer(output, source);
    return 0;
}
#endif
