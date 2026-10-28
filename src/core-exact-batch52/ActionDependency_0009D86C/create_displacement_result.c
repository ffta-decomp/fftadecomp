typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef unsigned int u32;
struct DisplacementResult { u8 helper_header[8]; u16 value; u8 helper_body[90]; };
typedef void (*ClearAllocation)(void *, u32);
extern void *AllocateBattleResult(u32 bytes);
extern void InitializeDisplacementResult(struct DisplacementResult *, void *, s8);
asm(".global AllocateBattleResult\n.thumb_set AllocateBattleResult,0x08022841\n.global InitializeDisplacementResult\n.thumb_set InitializeDisplacementResult,0x0809cc3d\n.global _call_via_r2\n.thumb_set _call_via_r2,0x0814224d");
/* Allocation/clear precede the halfword store and existing initializer. */
struct DisplacementResult *CreateBattleDisplacementResult(void *context,
    u8 direction, u16 value)
{
    struct DisplacementResult *result = AllocateBattleResult(100);
    (*(ClearAllocation *)0x0836d4b8)(result, 100);
    result->value = value;
    InitializeDisplacementResult(result, context, (s8)direction);
    return result;
}
