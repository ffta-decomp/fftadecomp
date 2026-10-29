typedef unsigned char u8;
typedef unsigned int u32;

extern unsigned short WriteUnsignedNumberText(u8 *output, u32 value);
extern unsigned short CopyEncodedTextToBuffer(u8 *output, const u8 *source);

typedef struct {
    u32 word_00;
    /* The context owner is unknown; +4 stores an address of a text pointer. */
    const u8 *const *text_pointer_slot_04;
    u32 word_08;
} TextCallbackContext;

#define TEXT_CONTEXT ((volatile TextCallbackContext *)0x020020d0)
#define DEFAULT_CONTENT_TEXT (*(const u8 *const *)0x08526680)

#if defined(CONTEXT_WORD_08_NUMBER)
u32 WriteContextWord08AsNumber(u8 *output)
{
    WriteUnsignedNumberText(output, TEXT_CONTEXT->word_08);
    return 0;
}
#elif defined(CONTEXT_OR_DEFAULT_CONTENT)
u32 WriteContextOrDefaultContentText(u8 *output)
{
    const u8 *const *text_pointer_slot = TEXT_CONTEXT->text_pointer_slot_04;
    const u8 *source;

    if (text_pointer_slot == 0)
        source = DEFAULT_CONTENT_TEXT;
    else
        source = *text_pointer_slot;
    CopyEncodedTextToBuffer(output, source);
    return 0;
}
#endif
