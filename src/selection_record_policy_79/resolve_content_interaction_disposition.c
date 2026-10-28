/* Method-local interface declarations from the frozen build. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct {
    u8 before_indices[160];
    u16 default_index;
    u16 override_index;
} ContentSelectionContext;

typedef struct {
    u8 before_kind[34];
    u8 kind;
    u8 unknown_23;
    u8 ready;
    u8 trailing[3];
} ContentRecord;
typedef char RecordStride[(sizeof(ContentRecord) == 40) ? 1 : -1];
typedef char KindOffset[((u32)&(((ContentRecord *)0)->kind) == 34) ? 1 : -1];
typedef char ReadyOffset[((u32)&(((ContentRecord *)0)->ready) == 36) ? 1 : -1];

extern ContentSelectionContext gContentSelection;
extern const ContentRecord gContentRecords[];
typedef struct {
    u8 before_flags[0x3c24];
    u32 flags;
} ContentState;
typedef char FlagsOffset[((u32)&(((ContentState *)0)->flags) == 0x3c24) ? 1 : -1];
extern ContentState gContentState;
extern u32 ReadSaveByte(u32);
extern u32 Query_08009C94(void);
extern u32 Query_08009DD0(void);
extern u32 Query_08009CE0(void);
extern void *GetContentConsumerContext(void);
extern u32 Query_0809A7B8(void *);
extern u32 Query_0809A8C8(void *);
extern u32 Query_0809A77C(void *);
extern u32 Query_0809A848(void *);
extern u32 CanUseCurrentContent(u32);
extern void ActivateContentCode(u32);

asm(".global gContentSelection\n.set gContentSelection,0x020020d0\n"
    ".global gContentRecords\n.set gContentRecords,0x0854cd54\n"
    ".global gContentState\n.set gContentState,0x02000000\n"
    ".global ReadSaveByte\n.thumb_set ReadSaveByte,0x080c95a9\n"
    ".global Query_08009C94\n.thumb_set Query_08009C94,0x08009c95\n"
    ".global Query_08009DD0\n.thumb_set Query_08009DD0,0x08009dd1\n"
    ".global Query_08009CE0\n.thumb_set Query_08009CE0,0x08009ce1\n"
    ".global GetContentConsumerContext\n.thumb_set GetContentConsumerContext,0x08096d7d\n"
    ".global Query_0809A7B8\n.thumb_set Query_0809A7B8,0x0809a7b9\n"
    ".global Query_0809A8C8\n.thumb_set Query_0809A8C8,0x0809a8c9\n"
    ".global Query_0809A77C\n.thumb_set Query_0809A77C,0x0809a77d\n"
    ".global Query_0809A848\n.thumb_set Query_0809A848,0x0809a849\n"
    ".global CanUseCurrentContent\n.thumb_set CanUseCurrentContent,0x080ced5d\n"
    ".global ActivateContentCode\n.thumb_set ActivateContentCode,0x08009afd\n");


/* Resolve content interaction outcome; unestablished type meanings stay numeric. */
u32 ResolveContentInteractionDisposition(u32 fallback_arg)
{
    u32 fallback = (u8)fallback_arg;
    u32 index;
    const ContentRecord *record;

    if (gContentSelection.override_index == 0)
        index = gContentSelection.default_index;
    else
        index = gContentSelection.override_index;
    record = &gContentRecords[index];

    if ((u8)ReadSaveByte(13) != 1) {
        if ((u8)Query_08009C94() != 0)
            return 1;
        if ((u8)Query_08009DD0() != 0)
            return 1;
    }

    if (record->ready == 0) {
        if ((u8)Query_0809A7B8(GetContentConsumerContext()) == 0) {
            if ((u8)CanUseCurrentContent(0) != 0)
                gContentState.flags |= 4;
            ActivateContentCode(170);
            return 1;
        }
    }

    switch (record->kind) {
    case 0:
        if ((u8)Query_0809A8C8(GetContentConsumerContext()) == 0 &&
            (u8)Query_08009CE0() != 0)
            return 1;
        break;
    case 1:
        if ((u8)Query_0809A77C(GetContentConsumerContext()) == 0) {
            if ((u8)Query_08009CE0() != 0)
                return 1;
            return 2;
        }
        break;
    case 3:
        if ((u8)Query_0809A848(GetContentConsumerContext()) == 0) {
            if ((u8)Query_08009CE0() != 0)
                return 1;
            return 2;
        }
        break;
    case 2:
        if ((u8)Query_0809A77C(GetContentConsumerContext()) == 0)
            return 2;
        break;
    }
    return fallback;
}
