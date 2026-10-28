typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
struct ActionStage { u16 phase; u8 before_payload[18]; u16 payload; };
extern u8 *ActionStageRootCell;
extern u8 ActionStageScratch[];
extern const u8 ActionStageSource[];
extern void DecodeActionStage_0800543C(void *, const void *);
extern void CreateActionChoice_080280F4(void *);
extern void SoundActionStage_08141540(u32);
extern u32 MoveActionChoice_080292A0(void *);
extern void DrawActionChoice_080292E0(void *);
extern u32 HandleActionChoice_08029350(void *);
extern void UpdateActionWidget_08017C68(void *);
u32 TaskConstructor45_000293DC(u32 origin, struct ActionStage *stage, u8 *object)
{
    u16 phase = stage->phase;
    switch (phase) {
    case 0:
        *(u32 *)object = origin;
        *(u32 *)(object + 4) = phase;
        object[8] = stage->payload;
        DecodeActionStage_0800543C(ActionStageScratch, ActionStageSource);
        break;
    case 256:
        CreateActionChoice_080280F4(object);
        SoundActionStage_08141540(101);
        stage->phase = 257;
        break;
    case 260:
        ActionStageRootCell[2] = 1;
        stage->phase = 3;
        break;
    case 257:
        if ((u8)MoveActionChoice_080292A0(object) != 0)
            stage->phase = 258;
        DrawActionChoice_080292E0(object);
        break;
    case 259:
        DrawActionChoice_080292E0(object);
        stage->phase = 260;
        break;
    case 258:
        if ((u8)HandleActionChoice_08029350(object) != 0)
            stage->phase = 259;
        UpdateActionWidget_08017C68(object + 88);
        DrawActionChoice_080292E0(object);
        break;
    case 1:
        break;
    }
    return 0;
}
asm(".set ActionStageRootCell,0x0200f438\n.set ActionStageScratch,0x02003cb0\n.set ActionStageSource,0x08418f14\n.thumb_set DecodeActionStage_0800543C,0x0800543d\n.thumb_set CreateActionChoice_080280F4,0x080280f5\n.thumb_set SoundActionStage_08141540,0x08141541\n.thumb_set MoveActionChoice_080292A0,0x080292a1\n.thumb_set DrawActionChoice_080292E0,0x080292e1\n.thumb_set HandleActionChoice_08029350,0x08029351\n.thumb_set UpdateActionWidget_08017C68,0x08017c69\n");
