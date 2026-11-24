typedef unsigned char u8;
typedef signed short s16;
typedef signed int s32;
typedef void (*PositionCallback)(void *, s16, s16, void *);
struct BattleWorkOwner {
    u8 unknown_000[28];
    void *work_record;
};
extern void QueueRecordWork(void *, s32, PositionCallback, void *);
extern void AdvanceRecordWork(u8 advance);
extern void ApplyBattlePositionCallback(void *, s16, s16, void *);
__asm__(".global QueueRecordWork\n.thumb_set QueueRecordWork, 0x08148861\n"
        ".global AdvanceRecordWork\n.thumb_set AdvanceRecordWork, 0x08148915\n"
        ".global ApplyBattlePositionCallback\n.thumb_set ApplyBattlePositionCallback, 0x08097815");

/* Preserve the actual callback request and advance even when the queue rejects it. */
void QueueBattleRecordPositionCallback(struct BattleWorkOwner *owner, u8 advance,
                                      void *callback_context)
    __asm__("CoreFrontier_0009A5E0");
void QueueBattleRecordPositionCallback(struct BattleWorkOwner *owner, u8 advance,
                                      void *callback_context)
{
    QueueRecordWork(owner->work_record, 255, ApplyBattlePositionCallback,
                    callback_context);
    AdvanceRecordWork(advance);
}
