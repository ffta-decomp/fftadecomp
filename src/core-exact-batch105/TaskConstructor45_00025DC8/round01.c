typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;
struct SelectionList {
    u8 unknown_00[22]; u8 visible; u8 unknown_17;
    u16 total; s16 top; u8 unknown_1c[4];
};
struct SelectionWidget { u8 unknown_00[17]; s8 row; u8 unknown_12[2]; };
struct SelectionOptions { u8 unknown_00[4]; u16 limit; u8 unknown_06[3]; u8 flags; u8 unknown_0a[10]; };
struct SelectionState {
    u8 unknown_00[8]; u8 slot; s8 count; u8 unknown_0a[2];
    u8 controller[44]; struct SelectionList list;
    struct SelectionWidget primary; struct SelectionWidget secondary;
    struct SelectionOptions options; u32 *choices;
    void *availability; void *records;
};
struct SavedSelection { u16 top; s8 row; u8 row_high; };
struct SelectionWorkspace { u8 unknown_00[4]; u8 mode; u8 has_single_page; u8 unknown_06[18]; u32 previous_choice; };
extern void SetManagedControllerData(void *, void *, u16, u16);
extern u32 GetManagedSelectionVisibleCount(struct SelectionList *);
extern void AdjustManagedSavedSelection(struct SelectionState *, struct SavedSelection *);
extern void SetManagedSelectionListFlags(struct SelectionList *, u32, u32);
extern u32 QueryManagedSelectionIndex(struct SelectionList *, int);
extern void BindManagedSelectionRowCallback(struct SelectionList *, u32, void *);
extern void RenderManagedSelectionRow(struct SelectionState *, int);
extern void RefreshManagedSelectionList(struct SelectionList *);
extern void SetManagedSelectionRowAttribute(struct SelectionList *, int, u32);
extern void BindManagedControllerCallbacks(void *, u32, u32);
extern void SetManagedWidgetRow(struct SelectionWidget *, u32);
extern void SetManagedWidgetMode(struct SelectionWidget *, u32);
extern void FinalizeManagedController(void *);
#define CURRENT_SELECTION (*(struct SelectionWorkspace **)0x0200f438)
#define OFFSET_OF(type, field) ((u32)&(((type *)0)->field))
typedef char SelectionListSize[(sizeof(struct SelectionList) == 32) ? 1 : -1];
typedef char StateListOffset[(OFFSET_OF(struct SelectionState, list) == 56) ? 1 : -1];
typedef char StatePrimaryOffset[(OFFSET_OF(struct SelectionState, primary) == 88) ? 1 : -1];
typedef char StateOptionsOffset[(OFFSET_OF(struct SelectionState, options) == 128) ? 1 : -1];
typedef char StateChoicesOffset[(OFFSET_OF(struct SelectionState, choices) == 148) ? 1 : -1];

void RebuildManagedSelectionState(struct SelectionState *state, u8 adjust)
{
    struct SelectionList *list;
    struct SelectionOptions *options;
    struct SelectionWorkspace **workspace_cell;
    struct SelectionWorkspace *current;
    struct SavedSelection *saved;
    struct SelectionWidget *primary;
    void *controller;
    u32 saved_offset;
    u32 item;
    u32 callback;
    int row;
    int count;

    list = &state->list;
    options = &state->options;
    workspace_cell = (struct SelectionWorkspace **)0x0200f438;
    saved_offset = 1092 + (u32)state->slot * 4;
    saved = (struct SavedSelection *)((u8 *)*workspace_cell + saved_offset);
    SetManagedControllerData(state->controller, state->records, 512, options->limit);
    state->count = GetManagedSelectionVisibleCount(list);
    if (adjust != 0)
        AdjustManagedSavedSelection(state, saved);
    list->top = saved->top;
    switch ((*workspace_cell)->mode) {
    case 12:
        SetManagedSelectionListFlags(list, 0, 1);
        break;
    case 2:
        item = QueryManagedSelectionIndex(list, saved->row);
        current = CURRENT_SELECTION;
        current->previous_choice = state->choices[(u16)item];
        break;
    case 3:
        BindManagedSelectionRowCallback(list, 0x08025d85, state);
        break;
    case 13:
    case 14:
        BindManagedSelectionRowCallback(list, 0x08025dad, state);
        break;
    }
    row = 0;
    count = state->count;
    controller = state->controller;
    primary = &state->primary;
    while (row < count) {
        RenderManagedSelectionRow(state, (s16)row);
        ++row;
        count = state->count;
    }
    RefreshManagedSelectionList(list);
    SetManagedSelectionRowAttribute(list, saved->row, 11);
    if (list->visible < options->limit) {
        callback = 0x08017f05;
        CURRENT_SELECTION->has_single_page = 0;
    } else {
        callback = 0;
        CURRENT_SELECTION->has_single_page = 1;
    }
    {
        /* Native captures the controller argument before the callback address. */
        register void *controller_argument asm("r0") = controller;
        asm("" : "+r" (controller_argument));
        BindManagedControllerCallbacks(controller_argument, 0x08017e81, callback);
    }
    SetManagedWidgetRow(primary, (u8)saved->row);
    if ((options->flags & 1) != 0)
        SetManagedWidgetMode(primary, 0);
    FinalizeManagedController(controller);
}
asm(".thumb_set SetManagedControllerData, 0x08016211\n"
    ".thumb_set GetManagedSelectionVisibleCount, 0x08017b51\n"
    ".thumb_set AdjustManagedSavedSelection, 0x08025d15\n"
    ".thumb_set SetManagedSelectionListFlags, 0x080175e1\n"
    ".thumb_set QueryManagedSelectionIndex, 0x08017b69\n"
    ".thumb_set BindManagedSelectionRowCallback, 0x08017ac5\n"
    ".thumb_set RenderManagedSelectionRow, 0x08025b55\n"
    ".thumb_set RefreshManagedSelectionList, 0x08017ad9\n"
    ".thumb_set SetManagedSelectionRowAttribute, 0x08017af5\n"
    ".thumb_set BindManagedControllerCallbacks, 0x08015d59\n"
    ".thumb_set SetManagedWidgetRow, 0x08017fb1\n"
    ".thumb_set SetManagedWidgetMode, 0x08017d19\n"
    ".thumb_set FinalizeManagedController, 0x08016235\n");
