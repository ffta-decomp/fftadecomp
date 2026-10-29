typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed int s32;
extern u8 UnitPool[];
extern u8 *volatile JobMenuOwner;
extern const u8 PortraitVariantRows[];
extern const u8 PortraitResource[];
extern u32 ReadUnitRecordPropertyAndSlot(const void *, u8 *);
extern void DecodePortraitResource(const void *, void *, u32, u32);
extern void CopyPortraitCpuSet(const void *, void *, u32);
__asm__(".global UnitPool\n.set UnitPool,0x02000000\n"
        ".global JobMenuOwner\n.set JobMenuOwner,0x03002818\n"
        ".global PortraitVariantRows\n.set PortraitVariantRows,0x08393f0c\n"
        ".global PortraitResource\n.set PortraitResource,0x083b5a5c\n"
        ".global ReadUnitRecordPropertyAndSlot\n.thumb_set ReadUnitRecordPropertyAndSlot,0x08022239\n"
        ".global DecodePortraitResource\n.thumb_set DecodePortraitResource,0x08005319\n"
        ".global CopyPortraitCpuSet\n.thumb_set CopyPortraitCpuSet,0x0814186d");
struct PortraitOutBytes { u8 all; u8 single; u8 unused[2]; };
void RefreshJobCompletionPortraits(u32 incoming) __asm__("CoreScene34_00087B30");
void RefreshJobCompletionPortraits(u32 incoming)
{
    struct PortraitOutBytes out;
    register u32 slot __asm__("r2") = (u8)incoming;
    register u8 *workspace __asm__("r9");
    __asm__("" : "+r"(slot));
    workspace = (u8 *)0x02003CB0;
    __asm__("" : "+r"(workspace) : "r"(slot));
    if (slot == 255) {
        s32 index = 0;
        register u32 unit_offset __asm__("r6") = 0;
        register u32 second_cursor __asm__("r8") = 0xFFFFEC00;
        u32 first_cursor = 0;
        __asm__("" : "+r"(unit_offset), "+r"(second_cursor));
        do {
            u8 *destination = (u8 *)(0x06015300 + second_cursor);
            register u32 pool_base __asm__("r1");
            register u8 *flag_address __asm__("r0");
            u32 property;
            register u8 *query_input __asm__("r0");
            register u8 *out_pointer __asm__("r1");
            register u8 *cache_entry __asm__("r2");
            register u32 cache_offset __asm__("r1");
            if (index <= 7)
                destination = (u8 *)(0x06011000 + first_cursor);
            __asm__("" : "+r"(destination));
            pool_base = (u32)UnitPool;
            __asm__("" : "+r"(pool_base));
            flag_address = (u8 *)(unit_offset + pool_base);
            __asm__("" : "+r"(flag_address));
            if (flag_address[132]) {
                query_input = (u8 *)(pool_base + 128);
                __asm__("" : "+r"(query_input));
                query_input = (u8 *)(unit_offset + (u32)query_input);
                __asm__("" : "+r"(query_input));
                out_pointer = &out.all;
                __asm__("" : "+r"(out_pointer));
                property = ReadUnitRecordPropertyAndSlot(query_input, out_pointer);
                cache_entry = JobMenuOwner;
                __asm__("" : "+r"(cache_entry));
                cache_offset = 0xBCC;
                __asm__("" : "+r"(cache_offset));
                cache_entry += cache_offset;
                __asm__("" : "+r"(cache_entry));
                cache_entry += index;
                __asm__("" : "+r"(cache_entry));
                out_pointer = &out.all;
                __asm__("" : "+r"(out_pointer));
                *cache_entry = *out_pointer;
                DecodePortraitResource(PortraitResource, workspace,
                                       PortraitVariantRows[property * 2], 1);
                CopyPortraitCpuSet(workspace, destination, 0x140);
            }
            {
                register u32 unit_step __asm__("r0") = 264;
                register u32 vram_step __asm__("r1");
                __asm__("" : "+r"(unit_step));
                unit_offset += unit_step;
                vram_step = 640;
                __asm__("" : "+r"(vram_step));
                second_cursor += vram_step;
                first_cursor += vram_step;
            }
            index++;
        } while (index <= 23);
    } else {
        u8 *destination;
        register u32 pool_base __asm__("r3");
        register u32 unit_offset __asm__("r1");
        register u32 record_group __asm__("r0");
        register u32 variant __asm__("r2");
        register const u8 *resource __asm__("r0");
        register u8 *query_input __asm__("r0");
        u32 property;
        if (slot <= 7)
            destination = (u8 *)(0x06011000 + slot * 640);
        else
            destination = (u8 *)(0x06015300 + (slot - 8) * 640);
        __asm__("" : "+r"(destination));
        pool_base = (u32)UnitPool;
        __asm__("" : "+r"(pool_base));
        record_group = slot * 33;
        __asm__("" : "+r"(record_group));
        unit_offset = record_group << 3;
        __asm__("" : "+r"(unit_offset));
        query_input = (u8 *)(unit_offset + pool_base);
        __asm__("" : "+r"(query_input));
        if (query_input[132]) {
            query_input = (u8 *)(pool_base + 128);
            __asm__("" : "+r"(query_input));
            query_input = (u8 *)(unit_offset + (u32)query_input);
            __asm__("" : "+r"(query_input));
            property = ReadUnitRecordPropertyAndSlot(query_input, &out.single);
            variant = PortraitVariantRows[property * 2];
            __asm__("" : "+r"(variant));
            resource = PortraitResource;
            __asm__("" : "+r"(resource));
            DecodePortraitResource(resource, workspace, variant, 1);
            CopyPortraitCpuSet(workspace, destination, 0x140);
        }
    }
}
