typedef unsigned char u8;
typedef unsigned int u32;
typedef signed int s32;
struct TurnUnit {
    u8 unknown_prefix[260];
    u8 ordering_tag;
    u8 unknown_tail[3];
};
struct TurnUnitRecord { struct TurnUnit *unit; };
struct TurnContext {
    s32 count;
    struct TurnUnit units[13];
    struct TurnUnitRecord *records[0];
};
struct TurnRosterView {
    u8 unknown_prefix[0xe18];
    const void *roster;
};
typedef char TurnUnitSize[(sizeof(struct TurnUnit)==264)?1:-1];
typedef char TurnRecordsOffset[((u32)&((struct TurnContext*)0)->records==0xd6c)?1:-1];
typedef char TurnRosterOffset[((u32)&((struct TurnRosterView*)0)->roster==0xe18)?1:-1];
extern void (*const gTurnContextClear)(u8*,s32);
extern void (*volatile const gTurnUnitCopy)(u8*,const u8*,s32);
extern s32 CollectTurnUnitRecords(const void*,struct TurnUnitRecord**);
__asm__(".global gTurnContextClear\n.set gTurnContextClear,0x0836d4b8\n.global gTurnUnitCopy\n.set gTurnUnitCopy,0x0836d4bc\n.global CollectTurnUnitRecords\n.thumb_set CollectTurnUnitRecords,0x08099cdd\n.global _call_via_r2\n.thumb_set _call_via_r2,0x0814224d\n.global _call_via_r3\n.thumb_set _call_via_r3,0x08142251");
