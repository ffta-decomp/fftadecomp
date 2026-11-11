typedef unsigned char u8;
typedef unsigned int u32;
struct BattleSceneWorkBuffer { void *context; u8 remaining_state[2344]; };
typedef char BufferSize[sizeof(struct BattleSceneWorkBuffer)==2348?1:-1];
typedef void (*ClearBytesFunction)(void *, u32);
extern void *AllocateGlobalPoolBytes(u32);
struct BattleSceneWorkBuffer *CreateBattleSceneWorkBuffer(void *context)
{
    struct BattleSceneWorkBuffer *state;
    u32 byte_count = sizeof(struct BattleSceneWorkBuffer);
    state = AllocateGlobalPoolBytes(byte_count);
    (*(ClearBytesFunction *)0x0836d4b8)(state, byte_count);
    state->context = context;
    return state;
}
asm(".global AllocateGlobalPoolBytes\n.thumb_set AllocateGlobalPoolBytes,0x08022841\n");
asm(".global _call_via_r0\n.thumb_set _call_via_r0,0x08142245\n");
asm(".global _call_via_r1\n.thumb_set _call_via_r1,0x08142249\n");
asm(".global _call_via_r2\n.thumb_set _call_via_r2,0x0814224d\n");
asm(".global _call_via_r3\n.thumb_set _call_via_r3,0x08142251\n");
asm(".global _call_via_r4\n.thumb_set _call_via_r4,0x08142255\n");
asm(".global _call_via_r5\n.thumb_set _call_via_r5,0x08142259\n");
asm(".global _call_via_r6\n.thumb_set _call_via_r6,0x0814225d\n");
