typedef unsigned char u8;
typedef unsigned int u32;
extern void *LookupDefinitionRecord(void *record, u32 index);

void *GetDefinitionTargetRecord(void *record, u8 index)
{
    return LookupDefinitionRecord(record, index);
}

asm(".global LookupDefinitionRecord\n.thumb_set LookupDefinitionRecord,0x080A8811\n");
