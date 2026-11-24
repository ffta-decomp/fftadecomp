typedef unsigned int u32;

extern void *Allocate_08007138(void *storage, u32 byte_count) asm("Allocate_08007138");

void *CoreRegion_0004CA58(u32 byte_count)
{
    register u32 count_in_r1 asm("r1") = byte_count;
    return Allocate_08007138(*(void **)0x0201f53c, count_in_r1);
}
