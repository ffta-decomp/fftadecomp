typedef unsigned int u32;
struct BattleRecordCapture { u32 count; u32 *cursor; };
typedef u32 (*CapturedRecordCallback)(u32, struct BattleRecordCapture *);
struct BattleCaptureCallback { struct BattleRecordCapture *capture; CapturedRecordCallback callback; };
struct BattleCaptureOwner { u32 unknown00[5]; void *list; };
extern u32 AppendBattleRecordAddress_0809AC20(u32, struct BattleRecordCapture *);
extern u32 VisitBattleOwnerWord_0809ABE8(const void *, const struct BattleCaptureCallback *);
extern void TraverseBattleCaptureList_080C7CC0(void *, u32 (*)(const void *, const struct BattleCaptureCallback *), const struct BattleCaptureCallback *);
u32 CaptureBattleContextRecordAddresses(struct BattleCaptureOwner *owner, u32 *output)
{
    struct BattleRecordCapture capture;
    struct BattleCaptureCallback callback;
    CapturedRecordCallback append;
    capture.count = 0;
    capture.cursor = output;
    append = AppendBattleRecordAddress_0809AC20;
    callback.capture = &capture;
    callback.callback = append;
    TraverseBattleCaptureList_080C7CC0(owner->list, VisitBattleOwnerWord_0809ABE8, &callback);
    return capture.count;
}
asm(".thumb_set AppendBattleRecordAddress_0809AC20,0x0809ac21\n");
asm(".thumb_set VisitBattleOwnerWord_0809ABE8,0x0809abe9\n");
asm(".thumb_set TraverseBattleCaptureList_080C7CC0,0x080c7cc1\n");
