typedef unsigned char u8;
typedef unsigned int u32;
typedef signed int s32;
typedef void (*BufferOperation)(void *,u32);
extern BufferOperation SceneBufferOperations[];
extern const u8 InventoryCategoryIds[];
extern void InvokeBufferOperation(void *,u32,BufferOperation);
extern s32 CollectEligibleInventoryClassEntries(void *,u32);
__asm__(".global SceneBufferOperations\n.set SceneBufferOperations,0x0836d4b8\n"
        ".global InventoryCategoryIds\n.set InventoryCategoryIds,0x08393aca\n"
        ".global InvokeBufferOperation\n.thumb_set InvokeBufferOperation,0x0814224d\n"
        ".global CollectEligibleInventoryClassEntries\n.thumb_set CollectEligibleInventoryClassEntries,0x08067f15");
void BuildAvailableInventoryCategories(u8 *incoming) __asm__("RemainingCore48_00068660");
void BuildAvailableInventoryCategories(u8 *incoming)
{
    register u8 *context __asm__("r5") = incoming;
    register BufferOperation *operations __asm__("r4") = SceneBufferOperations;
    register u8 *destination __asm__("r0") = incoming;
    register s32 ordinal __asm__("r6");
    register u32 offset __asm__("r1");
    register BufferOperation operation __asm__("r2");
    __asm__("" : "+r"(context), "+r"(operations), "+r"(destination));
    destination += 180;
    operation = operations[0];
    __asm__("" : "+r"(destination), "+r"(operation));
    InvokeBufferOperation(destination,8,operation);
    context[12] = 0;
    destination = *(u8 **)context;
    __asm__("" : "+r"(destination));
    offset = 0xA04;
    __asm__("" : "+r"(offset));
    destination += offset;
    operation = operations[0];
    __asm__("" : "+r"(destination), "+r"(operation));
    InvokeBufferOperation(destination,32,operation);
    ordinal = 0;
    __asm__("" : "+r"(ordinal));
    do {
        register const u8 *category_base __asm__("r0") = InventoryCategoryIds;
        register const u8 *category __asm__("r4");
        __asm__("" : "+r"(category_base));
        __asm__(".Lw4_68660_category_add_begin:\n\tadd %0,%1,%2\n.Lw4_68660_category_add_end:"
                : "=l"(category) : "l"(ordinal), "l"(category_base) : "cc");
        __asm__("" : "+r"(category));
        if (CollectEligibleInventoryClassEntries(0,*category) != 0) {
            destination = context + 180;
            __asm__("" : "+r"(destination));
            destination += context[12];
            __asm__("" : "+r"(destination));
            *destination = *category;
            context[12]++;
        }
        ordinal++;
    } while (ordinal <= 5);
}
