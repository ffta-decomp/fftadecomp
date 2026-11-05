typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;
typedef signed int s32;
extern void *ResolveActorIdentity(void *);
extern void *ReadActorResource(void *, u8 *, u8 *);
extern void AssignActorResource(void *, void *);
extern void AssignActorFirstByte(void *, u32);
extern void AssignActorSecondByte(void *, u32);
extern u32 ReadActorHandleValue(void *);
extern void AssignActorSignedValue(void *, s32);
extern u32 ReadActorPalette(void *);
extern void AssignActorPalette(void *, s32);
extern void CopyActorPalette(const void *, void *, u32);
extern u16 ActorPaletteBuffer[];
void InitializeActorDefinition(void *, void *, u8) __asm__("RemainingBand43_000DC414");
void InitializeActorDefinition(void *actor, void *destination, u8 override)
{
    u8 first, second;
    u32 palette;
    void *handle = ResolveActorIdentity(actor);
    u8 *first_out;
    u8 *second_out;
    void *resource;
    /* Native defines the first OUT address before the second. Each real
     * address is initialized and consumed by the following helper only. */
    first_out = &first;
    __asm__("" : "+r" (first_out));
    second_out = &second;
    __asm__("" : "+r" (second_out));
    resource = ReadActorResource(handle, first_out, second_out);
    AssignActorResource(destination, resource);
    {
        register const u8 *address __asm__("r0") = &first;
        register u32 value __asm__("r1");
        /* Island 1, 2B: unconditional physical byte read. ReadActorResource
         * can leave this actual stack byte unwritten; no C scalar read/default. */
        __asm__ volatile ("ldrb %0, [%1]" : "=l" (value)
                          : "l" (address), "m" (*address));
        AssignActorFirstByte(destination, value);
    }
    {
        register const u8 *address __asm__("r0") = &second;
        register u32 value __asm__("r1");
        /* Island 2, 2B: same defined load for the independent second byte. */
        __asm__ volatile ("ldrb %0, [%1]" : "=l" (value)
                          : "l" (address), "m" (*address));
        AssignActorSecondByte(destination, value);
    }
    AssignActorSignedValue(destination, (s16)ReadActorHandleValue(
        ResolveActorIdentity(actor)));
    palette = (u8)ReadActorPalette(actor);
    if (override != 255) {
        CopyActorPalette((u8 *)ActorPaletteBuffer + (palette << 5),
                         (u8 *)ActorPaletteBuffer + ((u32)override << 5), 16);
        palette = override;
    }
    AssignActorPalette(destination, (s8)palette);
}
__asm__(".global ResolveActorIdentity\n.thumb_set ResolveActorIdentity,0x080dd351\n"
        ".global ReadActorResource\n.thumb_set ReadActorResource,0x08099c05\n"
        ".global AssignActorResource\n.thumb_set AssignActorResource,0x0801133d\n"
        ".global AssignActorFirstByte\n.thumb_set AssignActorFirstByte,0x08011119\n"
        ".global AssignActorSecondByte\n.thumb_set AssignActorSecondByte,0x08011121\n"
        ".global ReadActorHandleValue\n.thumb_set ReadActorHandleValue,0x08099bf5\n"
        ".global AssignActorSignedValue\n.thumb_set AssignActorSignedValue,0x08011151\n"
        ".global ReadActorPalette\n.thumb_set ReadActorPalette,0x08099c11\n"
        ".global AssignActorPalette\n.thumb_set AssignActorPalette,0x08011141\n"
        ".global CopyActorPalette\n.thumb_set CopyActorPalette,0x0814186d\n"
        ".global ActorPaletteBuffer\n.set ActorPaletteBuffer,0x03003a60\n");
