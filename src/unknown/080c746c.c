typedef unsigned int u32;
struct RecordBuffer {
    u32 unknown_before_08[2];
    void *buffer;
};
extern void ReleaseGlobalPoolAllocation(void *allocation);
__asm__(".global ReleaseGlobalPoolAllocation\n.thumb_set ReleaseGlobalPoolAllocation, 0x08022855");

void ReleaseRecordBuffer(struct RecordBuffer *record)
    __asm__("CoreRegion30_000C746C");
void ReleaseRecordBuffer(struct RecordBuffer *record)
{
    if (record->buffer != 0) {
        ReleaseGlobalPoolAllocation(record->buffer);
        record->buffer = 0;
    }
}
