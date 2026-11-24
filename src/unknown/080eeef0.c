typedef unsigned char u8;
typedef unsigned int u32;
typedef signed short s16;
extern void PrepareAuthoredResource(const void *, u32, u32, u32, u32);
extern void *CreateDefinitionEffect(void *, const void *, u32, u32, const s16 *, void *);
void *RemainingBand43_000EEEF0(u32 raw_variant, void *record, void *parent)
{
    u32 variant = (u8)raw_variant;
    PrepareAuthoredResource((const void *)0x088EA550, 6, 1, variant, 1);
    return CreateDefinitionEffect(record, (const void *)0x08399978, 1, 2, (const s16 *)0, parent);
}
asm(".global PrepareAuthoredResource\n.thumb_set PrepareAuthoredResource, 0x080d45d1\n.global CreateDefinitionEffect\n.thumb_set CreateDefinitionEffect, 0x080e03f9\n");
