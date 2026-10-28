typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;
struct TaskGroup;
struct TaskNode;
typedef u32 (*TaskCallback)(struct TaskNode *, u16 *, u8 *);
struct ManagedSelectionView {
    s16 result;
    u8 ready;
    u8 active;
    u8 mode;
    u8 unknown_05[27];
    struct TaskGroup *group;
};
struct SelectionStartTemplate {
    u32 unknown_words[5];
    u16 mode_index;
    u16 unknown_tail[3];
};
extern struct ManagedSelectionView *gManagedSelection;
extern struct TaskNode *CreateTaskNode(struct TaskGroup *, TaskCallback, u32,
                                       const u32 *, struct TaskNode *);
extern u32 CheckSavedSelectionEligibility(struct TaskNode *, u16 *, u8 *);
extern u32 RunSelectionController(struct TaskNode *, u16 *, u8 *);
extern void PrepareSelectionDisplay(u32 ignored_mode_index);
extern const u8 *GetSelectionPalette(u8 index);
extern void (*gCopySelectionBytes)(void *, const void *, u32);
extern u16 gSelectionPaletteColor;
__asm__(".global gManagedSelection\n.set gManagedSelection,0x0200f438\n.global CreateTaskNode\n.thumb_set CreateTaskNode,0x08005955\n.global CheckSavedSelectionEligibility\n.thumb_set CheckSavedSelectionEligibility,0x08028ff5\n.global RunSelectionController\n.thumb_set RunSelectionController,0x08028de1\n.global PrepareSelectionDisplay\n.thumb_set PrepareSelectionDisplay,0x08022b25\n.global GetSelectionPalette\n.thumb_set GetSelectionPalette,0x080cba85\n.global gCopySelectionBytes\n.set gCopySelectionBytes,0x0836d4bc\n.global gSelectionPaletteColor\n.set gSelectionPaletteColor,0x030039f8\n.global _call_via_r3\n.thumb_set _call_via_r3,0x08142251");
typedef char template_size_check[sizeof(struct SelectionStartTemplate) == 28 ? 1 : -1];
typedef char mode_offset_check[(u32)&((struct SelectionStartTemplate *)0)->mode_index == 20 ? 1 : -1];
void BeginManagedSelectionMode(u8 mode, struct TaskNode *parent) __asm__("CoreFrontier_000253B0");
void BeginManagedSelectionMode(u8 mode, struct TaskNode *parent)
{
    struct SelectionStartTemplate request;
    gManagedSelection->mode = mode;
    gManagedSelection->result = 0;
    if (mode == 17) {
        /* The original special branch supplies an uninitialized template. */
        CreateTaskNode(gManagedSelection->group, CheckSavedSelectionEligibility,
                       164, (const u32 *)&request, parent);
    } else {
        u32 mode_index;
        register struct SelectionStartTemplate *request_fields __asm__("r1") = &request;
        const u8 *palette;
        void (**copy_service)(void *, const void *, u32);
        void *destination;
        /* The original prepares R1 before computing the full R0 mode index. */
        __asm__("" : "+r"(request_fields));
        mode_index = (u32)mode - 1;
        request_fields->mode_index = mode_index;
        /* This callee ignores R0; preserve the observed full caller value. */
        PrepareSelectionDisplay(mode_index);
        copy_service = &gCopySelectionBytes;
        destination = &gSelectionPaletteColor;
        /* The native frame retains these addresses across the palette query;
         * the callback itself is still read only after that query returns. */
        __asm__("" : "+r"(copy_service), "+r"(destination));
        palette = GetSelectionPalette(12);
        (*copy_service)(destination, palette + 24, 2);
        CreateTaskNode(gManagedSelection->group, RunSelectionController,
                       164, (const u32 *)&request, parent);
    }
}
