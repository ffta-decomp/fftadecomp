typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed int s32;

struct MenuRowView {
    u8 unknown00[17];
    u8 row;
};

extern u8 *gMenuOwner;
extern const u16 gMenuKeyShadow;
extern const u8 gSelectionState[];
extern const u8 gCommonTextPointers[];
extern void *PreserveMenuScrollObject(void *, u32);
extern u32 QueryClampedSelectionIndex(void *, s32);
extern const u8 *ReadMappedJobContentPointer(u8);
/* The row is the full saved byte; this callee interprets its LOW8 as signed. */
extern void RenderSelectionText(const u8 *, void *, u32, u32);
/* The original explicitly passes a third word of one. The selected callee
 * consumes only the first two arguments; no meaning is assigned to the extra. */
extern void ApplySceneKeyIfResolved(void *, u16, ...);

__asm__(
    ".global gMenuOwner\n.set gMenuOwner,0x0200f428\n"
    ".global gMenuKeyShadow\n.set gMenuKeyShadow,0x03000000\n"
    ".global gSelectionState\n.set gSelectionState,0x02000000\n"
    ".global gCommonTextPointers\n.set gCommonTextPointers,0x085567f0\n"
    ".global PreserveMenuScrollObject\n.thumb_set PreserveMenuScrollObject,0x08017fbd\n"
    ".global QueryClampedSelectionIndex\n.thumb_set QueryClampedSelectionIndex,0x08017b69\n"
    ".global ReadMappedJobContentPointer\n.thumb_set ReadMappedJobContentPointer,0x080ccb69\n"
    ".global RenderSelectionText\n.thumb_set RenderSelectionText,0x0805c3d5\n"
    ".global ApplySceneKeyIfResolved\n.thumb_set ApplySceneKeyIfResolved,0x08017885\n"
);

void RefreshMappedJobList(void) __asm__("CoreClosure31_0005ABB0");

void RefreshMappedJobList(void)
{
    u8 *owner = gMenuOwner;
    register struct MenuRowView *controls __asm__("r0") =
        (struct MenuRowView *)(owner + 0xd40);
    u8 row;
    u32 keys;

    /* The actual control base is formed before its separate byte field read. */
    __asm__("" : "+r"(controls));
    row = controls->row;
    keys = gMenuKeyShadow;

    if (keys & 64) {
        u32 selected;
        u32 record_offset;
        register u32 record_base __asm__("r3");

        row = (u8)(row - 1);
        PreserveMenuScrollObject(owner + 0xd54, 64);
        selected = (u8)QueryClampedSelectionIndex(gMenuOwner + 0xd20, (s8)row);
        record_base = (u32)gSelectionState;
        __asm__("" : "+r"(record_base));
        record_offset = (u32)selected * 16;

        if (*(u32 *)(record_offset + record_base + 0x2e78) != 0) {
            const u8 *text = ReadMappedJobContentPointer(selected);
            RenderSelectionText(text, gMenuOwner + 0xd20, row, 0);
        } else {
            register u32 flag_base __asm__("r0") = record_base + 0x2e7c;
            __asm__("" : "+r"(flag_base));
            if (*(u8 *)(record_offset + flag_base) != 0) {
                const u8 *text = ReadMappedJobContentPointer(selected);
                RenderSelectionText(text, gMenuOwner + 0xd20, row, 4);
            } else {
                register const u8 *table __asm__("r0") = gCommonTextPointers;
                const u8 *text;
                __asm__("" : "+r"(table));
                text = *(const u8 *const *)(table + 152);
                RenderSelectionText(text, gMenuOwner + 0xd20, row, 0);
            }
        }
        ApplySceneKeyIfResolved(gMenuOwner + 0xd20, 64, 1);
        return;
    }

    {
    register u32 active_keys __asm__("r0") = (u32)keys & 128;
    /* This fullword predicate is the original R0 result, separate from keys. */
    __asm__("" : "+r"(active_keys));
    if (active_keys) {
        u32 selected;
        u32 record_offset;
        register u32 record_base __asm__("r3");

        row = (u8)(row + 1);
        PreserveMenuScrollObject(owner + 0xd54, 128);
        selected = (u8)QueryClampedSelectionIndex(gMenuOwner + 0xd20, (s8)row);
        record_base = (u32)gSelectionState;
        __asm__("" : "+r"(record_base));
        record_offset = (u32)selected * 16;

        if (*(u32 *)(record_offset + record_base + 0x2e78) != 0) {
            const u8 *text = ReadMappedJobContentPointer(selected);
            RenderSelectionText(text, gMenuOwner + 0xd20, row, 0);
        } else {
            register u32 flag_base __asm__("r0") = record_base + 0x2e7c;
            __asm__("" : "+r"(flag_base));
            if (*(u8 *)(record_offset + flag_base) != 0) {
                const u8 *text = ReadMappedJobContentPointer(selected);
                RenderSelectionText(text, gMenuOwner + 0xd20, row, 4);
            } else {
                register const u8 *table __asm__("r0") = gCommonTextPointers;
                const u8 *text;
                __asm__("" : "+r"(table));
                text = *(const u8 *const *)(table + 152);
                RenderSelectionText(text, gMenuOwner + 0xd20, row, 0);
            }
        }
        ApplySceneKeyIfResolved(gMenuOwner + 0xd20, 128, 1);
    }
    }
}
