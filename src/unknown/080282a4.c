typedef unsigned char u8;
struct SelectionControl;
struct SelectionRestartGateView {
    u8 unknown[8];
    u8 mode;
};
struct SelectionRestartPayloadView {
    u8 unknown[12];
    u8 control_prefix[116];
    struct SelectionRestartGateView gate;
};
struct SelectionBranchContextView {
    u8 unknown[708];
    u8 branch_data[0];
};
extern struct SelectionBranchContextView *gManagedSelection;
extern void ConfigureSelectionBranches_08013B7C(struct SelectionRestartGateView *,
                                               struct SelectionControl *, void *);
extern void ActivateSelectionControl_08016C90(struct SelectionControl *, u8 mode);
__asm__(".global gManagedSelection\n.set gManagedSelection,0x0200f438\n.global ConfigureSelectionBranches_08013B7C\n.thumb_set ConfigureSelectionBranches_08013B7C,0x08013b7d\n.global ActivateSelectionControl_08016C90\n.thumb_set ActivateSelectionControl_08016C90,0x08016c91");
void RestartSelectionControls(struct SelectionRestartPayloadView *payload) __asm__("TaskConstructor45_000282A4");
void RestartSelectionControls(struct SelectionRestartPayloadView *payload)
{
    struct SelectionControl *control = (struct SelectionControl *)payload->control_prefix;
    struct SelectionRestartGateView *gate = &payload->gate;
    ConfigureSelectionBranches_08013B7C(gate, control, gManagedSelection->branch_data);
    /* The first service can change the mode consumed by the second service. */
    ActivateSelectionControl_08016C90(control, gate->mode);
}
