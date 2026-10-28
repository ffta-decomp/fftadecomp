typedef unsigned char u8;
typedef unsigned int u32;

struct ActionAdapterBase {
    const void *word0;
    u8 unknown[124];
    void *word128;
};

struct ActionAdapterRecord {
    u32 word0;
    u32 word4;
};

extern u32 EffectApplicationCall_08098E7C(
    void *context_word128,
    const void *base_word0,
    u32 record_word0,
    u32 record_word4,
    u32 forwarded_r2,
    u32 forwarded_r3);

u32 ActionDependency_0009AA94(
    struct ActionAdapterBase *base,
    struct ActionAdapterRecord *record,
    u32 forwarded_r2,
    u32 forwarded_r3)
{
    void *baseWord128 = base->word128;
    const void *baseWord0 = base->word0;
    u32 recordWord0 = record->word0;
    u32 recordWord4 = record->word4;
    return EffectApplicationCall_08098E7C(
        baseWord128,
        baseWord0,
        recordWord0,
        recordWord4,
        forwarded_r2,
        forwarded_r3);
}
