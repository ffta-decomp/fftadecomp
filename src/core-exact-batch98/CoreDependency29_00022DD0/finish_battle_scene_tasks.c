typedef unsigned char u8;
typedef unsigned int u32;
typedef void (*SceneTaskCallback)(u32 slot, u8 *status);
struct SceneTaskGroup {
    u8 unknown_00[8];
    SceneTaskCallback *callbacks;
    u8 *statuses;
};
extern void *CopySceneTaskBytes(void *destination, const void *source, u32 size);
__asm__(".global CopySceneTaskBytes\n.thumb_set CopySceneTaskBytes,0x081443fd");
__asm__(".global _call_via_r2\n.thumb_set _call_via_r2,0x0814224d");
void FinishBattleSceneTasks(void) __asm__("CoreDependency29_00022DD0");
void FinishBattleSceneTasks(void)
{
    u8 slots[2];
    int position;
    register struct SceneTaskGroup *group __asm__("r5");
    CopySceneTaskBytes(slots, (const void *)0x08149994, 2);
    position = 0;
    group = (struct SceneTaskGroup *)0x03002710;
    __asm__("" : "+r"(group) : "r"(position));
    do {
        u32 slot = slots[position];
        register SceneTaskCallback *callbacks __asm__("r0") = group->callbacks;
        register u32 slot_offset __asm__("r4");
        __asm__("" : "+r"(callbacks));
        slot_offset = slot * 4;
        __asm__("" : "+r"(slot_offset));
        if (*(SceneTaskCallback *)(slot_offset + (u32)callbacks) != 0) {
            group->statuses[slot] = 255;
            {
                register SceneTaskCallback *callback_address __asm__("r2") =
                    (SceneTaskCallback *)(slot_offset + (u32)group->callbacks);
                register u32 callback_slot __asm__("r0");
                __asm__("" : "+r"(callback_address));
                callback_slot = slot;
                __asm__("" : "+r"(callback_slot) : "r"(callback_address));
                {
                    register u8 *status_address __asm__("r1") =
                        &group->statuses[callback_slot];
                    __asm__("" : "+r"(status_address) : "r"(callback_slot));
                    (*callback_address)(callback_slot, status_address);
                }
            }
        }
    } while (++position <= 1);
}
