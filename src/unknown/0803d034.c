typedef unsigned char u8;
typedef unsigned int u32;

struct AcquisitionOptionList {
    u32 count;
    u8 header_fields[20];
    void *records;
    u8 reserved_to_records[532];
    u8 record_storage[1];
};

struct AcquisitionNode {
    u8 preceding_fields[29];
    u8 selector;
};

struct AcquisitionContext {
    void *field0;
    struct AcquisitionNode *node;
};

typedef char option_list_storage_offset[
    ((u32)&((struct AcquisitionOptionList *)0)->record_storage == 560) ? 1 : -1];

extern void CopyAcquisitionListTemplate(const void *source, void *destination,
                                      u32 control);
extern void AppendDefaultAcquisitionOptions(u32 *count, u32 selector,
                                           void *records);
extern u32 AppendAvailableAcquisitionOptions(u32 *count, u32 selector,
                                            void *records, u8 enabled);

__asm__(".global CopyAcquisitionListTemplate\n"
        ".thumb_set CopyAcquisitionListTemplate, 0x0814186d\n"
        ".global AppendDefaultAcquisitionOptions\n"
        ".thumb_set AppendDefaultAcquisitionOptions, 0x0803cdad\n"
        ".global AppendAvailableAcquisitionOptions\n"
        ".thumb_set AppendAvailableAcquisitionOptions, 0x0803cef9\n");

/* The existing appenders own eligibility and update count through its address.
 * Selector zero leaves the list empty; selectors 2..6 prepend fixed options. */
u32 BuildAcquisitionOptionList(struct AcquisitionOptionList *list,
                             u8 *has_record_options)
{
    u32 count;
    void *records;
    const void *list_template = (const void *)0x083918c4;
    u32 selector = 0;

    CopyAcquisitionListTemplate(list_template, list, 14);
    records = list->record_storage;
    list->records = records;
    count = selector;
    *has_record_options = selector;
    selector = (*(struct AcquisitionContext **)0x03002810)->node->selector;
    if (selector != 0) {
        if (selector - 2 <= 4)
            AppendDefaultAcquisitionOptions(&count, selector, records);
        *has_record_options = (u8)AppendAvailableAcquisitionOptions(
            &count, selector, records, 1);
    }
    list->count = count;
    return count;
}
