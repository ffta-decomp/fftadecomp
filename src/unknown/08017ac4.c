typedef unsigned short u16;
typedef struct SelectionCallbackRecord {
    void *callback;
    void *context;
    unsigned char unknown[8];
    u16 flags;
} SelectionCallbackRecord;
void SetSelectionCallbackContext(SelectionCallbackRecord *record, void *callback, void *context) __asm__("sub_08017AC4");
void SetSelectionCallbackContext(SelectionCallbackRecord *record, void *callback, void *context)
{
    record->flags |= 2;
    record->callback = callback;
    record->context = context;
}
