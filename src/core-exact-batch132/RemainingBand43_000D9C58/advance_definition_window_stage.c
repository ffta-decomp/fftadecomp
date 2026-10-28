#include "../../../src/task_tree_core.h"

typedef signed short s16;
struct DefinitionWindowEvent {
    u16 state;
    u16 unknown_02;
    u32 unknown_04[4];
    s16 destination_selector;
    u16 right;
    u16 left;
    u16 unknown_1a;
};
struct ScanlineWindowObject;
struct DefinitionWindowState {
    u8 publish_requested;
    u8 unknown_01[3];
    struct ScanlineWindowObject *object;
};
struct DefinitionWindowTargets { void *entries[2]; };
typedef char DefinitionWindowEventMustBe28Bytes[sizeof(struct DefinitionWindowEvent)==28?1:-1];
typedef char DefinitionWindowStateMustBe8Bytes[sizeof(struct DefinitionWindowState)==8?1:-1];
typedef char DefinitionWindowTargetsMustBe8Bytes[sizeof(struct DefinitionWindowTargets)==8?1:-1];
extern const struct DefinitionWindowTargets gDefinitionWindowTargets;
extern void CopyDefinitionWindowScanlines(const void *,void *);
extern struct ScanlineWindowObject *CreateDefinitionScanlineObject(
    void (*)(const void *,void *),u16,u16,void *);
extern u32 ReadDefinitionObjectDataWord(const void *);
extern void DestroyDefinitionScanlineObject(struct ScanlineWindowObject *);
extern void RequestDefinitionScanlinePublish(struct ScanlineWindowObject *);

u32 AdvanceDefinitionWindowStage(TaskNode *task,struct DefinitionWindowEvent *event,
                                  struct DefinitionWindowState *payload)
{
    switch (event->state) {
    case 0: {
        struct DefinitionWindowTargets targets = gDefinitionWindowTargets;
        volatile u8 *buffer;
        u16 row;
        payload->object = CreateDefinitionScanlineObject(
            CopyDefinitionWindowScanlines,320,2,targets.entries[event->destination_selector]);
        buffer = (volatile u8 *)ReadDefinitionObjectDataWord(payload->object);
        row = 0;
        do {
            u16 right = event->right;
            u16 left;
            /* Keep the native byte reads and fresh event values at each row. */
            (void)buffer[1];
            buffer[1] = right;
            left = event->left;
            (void)buffer[0];
            buffer[0] = left;
            buffer += 2;
            row++;
        } while (row <= 159);
        break;
    }
    case 1:
        DestroyDefinitionScanlineObject(payload->object);
        break;
    case 256:
        if (payload->publish_requested != 0) {
            RequestDefinitionScanlinePublish(payload->object);
            event->state++;
        }
        break;
    case 257:
        event->state = 2;
        break;
    }
    return 0;
}

asm(".global CreateDefinitionScanlineObject\n.thumb_set CreateDefinitionScanlineObject,0x0800c3cd\n"
    ".global ReadDefinitionObjectDataWord\n.thumb_set ReadDefinitionObjectDataWord,0x0800c615\n"
    ".global DestroyDefinitionScanlineObject\n.thumb_set DestroyDefinitionScanlineObject,0x0800c669\n"
    ".global RequestDefinitionScanlinePublish\n.thumb_set RequestDefinitionScanlinePublish,0x0800c6c1\n"
    ".global CopyDefinitionWindowScanlines\n.thumb_set CopyDefinitionWindowScanlines,0x080dae71\n"
    ".global gDefinitionWindowTargets\n.set gDefinitionWindowTargets,0x08149b2c\n");
