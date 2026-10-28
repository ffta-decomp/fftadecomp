typedef unsigned char u8;
typedef unsigned int u32;
struct UnitReference {
    u32 index;
    u8 unknown_04[258];
    u8 kind;
};

void *ResolveUnitReferenceFromOriginal(struct UnitReference *reference)
{
    u32 index = reference->index;
    u8 kind = reference->kind;
    void **table;
    if (kind == 0)
        goto primary_table;
    if (kind == 1)
        goto secondary_table;
    return (void *)0x02001f1c;

primary_table:
    table = (void **)0x085680dc;
    goto indexed_return;
secondary_table:
    table = (void **)0x085516d0;
indexed_return:
    index <<= 2;
    index += (u32)table;
    return *(void **)index;
}
