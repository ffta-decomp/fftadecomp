typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;
struct EffectNode {
    u8 preceding00[8];
    s16 coordinate08;
    u16 coordinate0a;
    s16 coordinate0c;
    u8 unknown0e[17];
    s8 operation_tag;
    u8 unknown20[16];
    u32 flags;
};
struct RecordEffectSequence {
    struct EffectNode *node;
    u16 flags;
    s16 effect_slot;
    u8 unknown08[5];
    u8 stage;
};
struct BattleEffectRoot {
    u8 preceding00[0x26c0];
    u16 flags;
    u16 unknown26c2;
    void *pending_task;
};
extern void SequenceSpawnEffect(s16, s16, s16, s16, u32);
extern void SequenceApplyNodeOperation(struct EffectNode *, u32, s8, u16);
extern u32 SequencePollNode(struct EffectNode *);
extern void SequenceLaunchSession(void);
extern u32 SequenceSessionReady(void);
extern u32 SequenceAdvanceSession(void);
extern void *SequenceCreateTask(u16, u32, struct EffectNode *);
extern u32 SequenceTaskReady(void *);
extern void SequenceEndTask(void *);
asm(".global SequenceSpawnEffect\n.thumb_set SequenceSpawnEffect,0x080a92e5\n.global SequenceApplyNodeOperation\n.thumb_set SequenceApplyNodeOperation,0x0809836d\n.global SequencePollNode\n.thumb_set SequencePollNode,0x08099c65\n.global SequenceLaunchSession\n.thumb_set SequenceLaunchSession,0x080d376d\n.global SequenceSessionReady\n.thumb_set SequenceSessionReady,0x080d37f9\n.global SequenceAdvanceSession\n.thumb_set SequenceAdvanceSession,0x080d39b1\n.global SequenceCreateTask\n.thumb_set SequenceCreateTask,0x080d3509\n.global SequenceTaskReady\n.thumb_set SequenceTaskReady,0x080d3879\n.global SequenceEndTask\n.thumb_set SequenceEndTask,0x080d3865");

/* Each call performs one stage; stage5 reports completion without redispatch. */
u32 AdvanceBattleRecordEffectSequence(struct BattleEffectRoot *root,
                                     struct RecordEffectSequence *record)
{
    u32 next_stage;
    switch (record->stage) {
    case 0:
        SequenceSpawnEffect(record->effect_slot, record->node->coordinate08,
            (s16)(record->node->coordinate0a + 48), record->node->coordinate0c, 0);
        if (record->effect_slot < 0)
            goto finish;
        SequenceApplyNodeOperation(record->node, 5, record->node->operation_tag, 0);
        next_stage = 1;
        goto store_stage;
    case 1:
        if (SequencePollNode(record->node) == 0)
            break;
        if (record->flags & 0x1000)
            goto prepare_session;
finish:
        record->stage = 5;
    case 5:
        return 0;
prepare_session:
        {
            u16 *root_flags = &root->flags;
            if (*root_flags & 8)
                goto stage_three;
            SequenceLaunchSession();
            *root_flags |= 8;
            next_stage = 2;
            goto store_stage;
        }
    case 2:
        if ((u8)SequenceSessionReady() == 0)
            break;
        if ((u8)SequenceAdvanceSession() == 0)
            break;
stage_three:
        next_stage = 3;
        goto store_stage;
    case 3:
        {
            void *pending_task = SequenceCreateTask(348, 0, record->node);
            root->pending_task = pending_task;
        }
        next_stage = 4;
        goto store_stage;
    case 4:
        {
            void **pending_cell = &root->pending_task;
            if (*pending_cell != (void *)0) {
                if ((u8)SequenceTaskReady(*pending_cell) == 0)
                    break;
                SequenceEndTask(*pending_cell);
                *pending_cell = 0;
            }
        }
        {
            /* Recall253 cause01: the native footer reloads record->node into r2,
             * reads node flags into r0, ORs the initialized bit mask in r1, and
             * stores through r2. Keep this real initialized pointer at r2 after
             * SequenceEndTask so the source preserves the original reload point. */
            register struct EffectNode *node asm("r2") = record->node;
            u32 node_flags = node->flags;
            node_flags |= 16;
            node->flags = node_flags;
        }
        next_stage = 5;
        goto store_stage;
    default:
        break;
    }
    return 1;
store_stage:
    record->stage = next_stage;
    return 1;
}
