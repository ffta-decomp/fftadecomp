#include "../../../src/task_tree_core.h"

struct DmaRequest;
struct DefinitionIconTransfer {
    u8 decoded_icon[128];
    u16 icon_id;
    u16 unknown_82;
    void *destination;
};
typedef char IconTransferPayloadSize[sizeof(struct DefinitionIconTransfer)==136?1:-1];
extern void LoadItemIconGraphic(u8 *,u16);
extern void *NextManagedTaskTransferRequest(void);
extern void QueueDmaCopy16(struct DmaRequest *,u32,u32,u16);
u32 AdvanceDefinitionIconTransfer(TaskNode *,u16 *,struct DefinitionIconTransfer *)
    asm("RemainingBand43_000D65D4");
u32 AdvanceDefinitionIconTransfer(TaskNode *task,u16 *event,
                                  struct DefinitionIconTransfer *payload)
{
    switch (event[0]) {
    case 0:
        payload->icon_id=event[10];
        payload->destination=*(void **)(event+2);
        break;
    case 1:
        break;
    case 256: {
        struct DmaRequest *request;
        LoadItemIconGraphic(payload->decoded_icon,payload->icon_id);
        request=NextManagedTaskTransferRequest();
        QueueDmaCopy16(request,(u32)payload->decoded_icon,(u32)payload->destination,64);
        event[0]++;
        break;
    }
    case 257:
        event[0]=3;
        break;
    }
    return 0;
}
asm(".global LoadItemIconGraphic\n.thumb_set LoadItemIconGraphic,0x080cb981\n"
    ".global NextManagedTaskTransferRequest\n.thumb_set NextManagedTaskTransferRequest,0x080d3af9\n"
    ".global QueueDmaCopy16\n.thumb_set QueueDmaCopy16,0x08000a99\n");
