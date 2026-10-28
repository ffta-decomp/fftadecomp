typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
struct BattleUnit;
struct Payload { u8 prefix[12]; struct BattleUnit *unit; };
struct DmaRequest;
extern void *gUnitTaskContext;
extern u32 ReadTaskUnitField(const struct BattleUnit *, u8);
extern struct DmaRequest *TakeUnitTaskRingRecord(void);
extern void QueueDmaCopy32(struct DmaRequest *, u32, u32, u16);
/* Preserve the entry root and selected source across both independent queue appends. */
void QueueUnitTaskKindContents(struct Payload *payload)
{
    u8 *root = gUnitTaskContext;
    u8 *source = root + 3164;
    u32 kind = ReadTaskUnitField(payload->unit, 1);
    struct DmaRequest *request;
    switch (kind) {
    case 20:
        source = root + 3612;
        break;
    case 21:
        source = root + 3388;
        break;
    }
    request = TakeUnitTaskRingRecord();
    QueueDmaCopy32(request, (u32)source, 0x06009740, 32);
    request = TakeUnitTaskRingRecord();
    QueueDmaCopy32(request, (u32)(source + 128), 0x06009b60, 24);
}
asm(".global gUnitTaskContext\n.set gUnitTaskContext,0x0200F440\n"
    ".global ReadTaskUnitField\n.thumb_set ReadTaskUnitField,0x080C7EA5\n"
    ".global TakeUnitTaskRingRecord\n.thumb_set TakeUnitTaskRingRecord,0x0802BA09\n"
    ".global QueueDmaCopy32\n.thumb_set QueueDmaCopy32,0x08000ADD\n");
