typedef unsigned char u8;
typedef signed int s32;
typedef unsigned int u32;

struct AllocationHandle {
    u8 unknown_00[8];
};

extern void *AllocateHandleMemory(struct AllocationHandle *handle,
                                  u32 byte_count);
extern void ReleaseHandleAllocation(struct AllocationHandle *handle,
                                    void *allocation);
extern u32 CoreDependency29_000028C8(u32 allocation, u32 output,
                                     u32 count, u32 element_size,
                                     u32 callback);

u32 CoreRegion_00050CE8(void *context, void *output)
{
    void *original_output;
    u8 *record;
    u32 cursor_address;
    u32 count;
    s32 remaining;

    original_output = output;
    record = (u8 *)0x02002948;
    count = 0;
    remaining = 15;
    cursor_address = (u32)output;
    do {
        if (record[20] != 0) {
            if (original_output != 0) {
                *(u32 *)cursor_address = (u32)record;
            }
            cursor_address += 4;
            count++;
        }
        remaining--;
        record += 28;
    } while (remaining >= 0);

    if (count != 0 && original_output != 0) {
        u32 root;
        struct AllocationHandle *handle;
        void *allocation;

        root = *(u32 *)context;
        handle = (struct AllocationHandle *)(*(u32 *)((u8 *)root + 8));
        allocation = AllocateHandleMemory(handle, 100);
        (void)CoreDependency29_000028C8((u32)allocation, (u32)original_output,
                                        count, 4, 0x08050CDD);
        root = *(u32 *)context;
        handle = (struct AllocationHandle *)(*(u32 *)((u8 *)root + 8));
        ReleaseHandleAllocation(handle, allocation);
    }
    return count;
}

__asm__(".global AllocateHandleMemory\n.thumb_set AllocateHandleMemory, 0x08005B01");
__asm__(".global ReleaseHandleAllocation\n.thumb_set ReleaseHandleAllocation, 0x08005B0D");
__asm__(".global CoreDependency29_000028C8\n.thumb_set CoreDependency29_000028C8, 0x080028C9");
