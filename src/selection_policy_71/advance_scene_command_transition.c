/* Method-local interface declarations from the frozen build. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
struct SceneCommand {u8 unknown00[4];u16 actor_id;u8 state;};
struct TransitionState {u8 scene;u8 phase;u8 unknown02[0x92];u16 flags;u16 mode;};
struct SaveImage {u8 unknown00[0x2c78];void *reward_slot;u8 unknown2c7c[0x3b1c - 0x2c7c];u8 reward[0x108];u32 result_flags;u16 result_count;u8 result_index;};
struct ResultRecord {u8 unknown00[7];u8 enabled;u8 unknown08[4];};
extern struct TransitionState transition;
extern struct SaveImage live_save;
extern const struct ResultRecord result_records[];
extern u8 *active_reward;
extern void BeginSceneEntityTransition_081253CC(void);
extern void FinishSceneEntityTransition_081258AC(void);
extern void ResetSceneEntityTransition_081256C8(void);
extern void *FindUnusedMissionRewardUnitSlot_0803600C(void);
extern u32 SelectWeightedMissionReward(u32,u8 *);
extern void SetGameFlag(u16,u16);
extern void ApplySceneState(u16,u8);
typedef char SaveImageLayout[sizeof(struct SaveImage)==0x3c2c?1:-1];
typedef char TransitionLayout[sizeof(struct TransitionState)==0x98?1:-1];
asm(".global transition\n.set transition,0x0200f390");
asm(".global live_save\n.set live_save,0x02000000");
asm(".global result_records\n.set result_records,0x08563a70");
asm(".global active_reward\n.set active_reward,0x030027f4");
asm(".global BeginSceneEntityTransition_081253CC\n.thumb_set BeginSceneEntityTransition_081253CC,0x081253cd");
asm(".global FinishSceneEntityTransition_081258AC\n.thumb_set FinishSceneEntityTransition_081258AC,0x081258ad");
asm(".global ResetSceneEntityTransition_081256C8\n.thumb_set ResetSceneEntityTransition_081256C8,0x081256c9");
asm(".global FindUnusedMissionRewardUnitSlot_0803600C\n.thumb_set FindUnusedMissionRewardUnitSlot_0803600C,0x0803600d");
asm(".global SelectWeightedMissionReward\n.thumb_set SelectWeightedMissionReward,0x080d241d");
asm(".global SetGameFlag\n.thumb_set SetGameFlag,0x080c9575");
asm(".global ApplySceneState\n.thumb_set ApplySceneState,0x08022e91");

u32 AdvanceSceneCommandTransition(struct SceneCommand *command)
{
    switch(command->state) {
    case 1:
        BeginSceneEntityTransition_081253CC();
        command->state=2;
        break;
    case 2:
        if(!(transition.flags&2)) {
            FinishSceneEntityTransition_081258AC();
            return 0x100;
        }
        break;
    case 3:
        ResetSceneEntityTransition_081256C8();
        transition.flags&=0xff7f;
        transition.flags&=0xfffe;
        transition.flags|=8;
        if(live_save.result_count==0)
            transition.flags|=16;
        transition.mode=1;
        command->state=4;
        break;
    case 5:
        {
        u32 result_offset;
        const struct ResultRecord *result;
        ResetSceneEntityTransition_081256C8();
        transition.flags&=0xff7f;
        transition.flags&=0xfffe;
        transition.flags|=8;
        if(live_save.result_count==0)
            transition.flags|=16;
        result_offset=(u32)live_save.result_index*sizeof(struct ResultRecord);
        result=(const struct ResultRecord *)((const u8 *)result_records+result_offset);
        if(result->enabled || (live_save.result_flags&4)) {
            transition.phase=0;
            transition.mode=3;
        } else {
            transition.mode=2;
        }
        command->state=6;
        }
        break;
    case 4:
    case 6:
        if(!(transition.flags&8)) {
            transition.flags|=1;
            return 0x100;
        }
        break;
    case 7:
        {
            u32 content_id=0x179;
            u8 *reward;
            live_save.reward_slot=FindUnusedMissionRewardUnitSlot_0803600C();
            reward=live_save.reward;
            switch(command->actor_id) {
            case 9: content_id=0x17b;break;
            case 4: content_id=0x17c;break;
            case 12: content_id=0x190;break;
            case 94: content_id=0x17e;break;
            case 10: break;
            }
            SelectWeightedMissionReward(content_id,reward);
            active_reward=reward;
            SetGameFlag(74,1);
            ApplySceneState(4,16);
            transition.scene=27;
            command->state=8;
        }
        break;
    case 8:
        if(transition.scene==32) {
            SetGameFlag(74,0);
            return 0x100;
        }
        break;
    }
    return 0x11c;
}
