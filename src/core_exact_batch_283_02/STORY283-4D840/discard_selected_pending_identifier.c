typedef unsigned short u16;
typedef unsigned int u32;
extern u32 ReadCurrentSelectionWord(void);
extern int RemoveFirstPendingIdentifier(u16 identifier);
extern void *AllocateOperationContext(u32 byte_length);
extern void CompactPendingHalfwordsAndDispatch(void *context);
extern void FreeOperationContext(void *context);
extern void RefreshPendingIdentifierList(unsigned char mode);
asm(".global ReadCurrentSelectionWord\n.thumb_set ReadCurrentSelectionWord,0x0804e9d1\n"
    ".global RemoveFirstPendingIdentifier\n.thumb_set RemoveFirstPendingIdentifier,0x08038695\n"
    ".global AllocateOperationContext\n.thumb_set AllocateOperationContext,0x0804ca59\n"
    ".global CompactPendingHalfwordsAndDispatch\n.thumb_set CompactPendingHalfwordsAndDispatch,0x080cb27d\n"
    ".global FreeOperationContext\n.thumb_set FreeOperationContext,0x0804ca6d\n"
    ".global RefreshPendingIdentifierList\n.thumb_set RefreshPendingIdentifierList,0x0804e359\n");

/* Dedicated selected-ID transaction. Preserve the LOW16 selection, unconditional
 * compaction/continuation, and allocation lifetime across the real dispatch.
 * Related pointer-record deletion uses a different size/mode and stays separate. */
void IsolatedCore57_0004D840(void)
{
    void *context;
    RemoveFirstPendingIdentifier((u16)ReadCurrentSelectionWord());
    context = AllocateOperationContext(98);
    CompactPendingHalfwordsAndDispatch(context);
    FreeOperationContext(context);
    RefreshPendingIdentifierList(5);
}
