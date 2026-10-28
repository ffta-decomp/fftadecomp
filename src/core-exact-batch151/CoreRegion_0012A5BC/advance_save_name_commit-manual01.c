#include "../../../src/task_tree_core.h"
/* A prefix view only; the editor's total allocation and other fields are unknown. */
struct SaveNameContext {
    u8 unknown_00[6];
    u16 name_kind;
    u8 unknown_08[0x312 - 8];
    u8 edited_name[18];
    u8 primary_cursor;
    u8 secondary_cursor;
    u8 name_length;
    u8 unknown_327;
    u8 reset_required;
    u8 unknown_329[3];
    void *window;
    u8 phase;
};
#define MEMBER_OFFSET(T, M) ((u32)&((T *)0)->M)
typedef char EditedNameOffset[MEMBER_OFFSET(struct SaveNameContext, edited_name) == 0x312 ? 1 : -1];
typedef char ResetOffset[MEMBER_OFFSET(struct SaveNameContext, reset_required) == 0x328 ? 1 : -1];
typedef char WindowOffset[MEMBER_OFFSET(struct SaveNameContext, window) == 0x32c ? 1 : -1];
typedef char PhaseOffset[MEMBER_OFFSET(struct SaveNameContext, phase) == 0x330 ? 1 : -1];
extern u8 PrimaryLiveName[];
extern u8 SecondaryLiveName[];
extern const u8 * const PrimaryDefaultNames[];
extern const u8 * const SecondaryDefaultNames[];
extern const u8 ResetNameReference[];
extern const u8 NameDialogText[];
extern const u8 NameDialogStyle[];
extern u32 IsNameBufferBlank(const u8 *);
extern u32 IsSamePaddedName(const u8 *, const u8 *);
extern void CopyNormalizedEditedName(struct SaveNameContext *, u8 *);
extern u16 CopyEncodedTextToBuffer(u8 *, const u8 *);
extern void BiosCpuSet(const void *, void *, u32);
extern u32 NameByteLength(const u8 *);
extern void PadEditedName(const u8 *);
extern void UpdateSaveNameEditor(struct SaveNameContext *);
extern void ShowNameDialog(void *, u32, u32, const u8 *, const u8 *, u32, u32, u32, u32, u32);
extern void ConfigureNameDialog(u32);
extern u32 PollNameDialog(void);
extern u32 QueryNameDialogChoice(void);
extern void PrepareSaveReset(u32, u32);
extern void EraseAllSaveSectorsWithRetries(void);
extern void FinishNameDialog(u32);
void AdvanceSaveNameCommit(u16 *outer_state, struct SaveNameContext *context)
{
    u16 *state_destination = outer_state;
    u8 phase;
    u16 next_outer_state;
    asm("" : "+r"(state_destination));
    phase = context->phase;
    switch (phase) {
    case 0: {
        u16 name_kind;
        context->reset_required = phase;
        name_kind = context->name_kind;
        if (name_kind != 0) {
            u8 *primary_edited = context->edited_name;
            if ((u8)IsNameBufferBlank(primary_edited) != 0) {
                CopyEncodedTextToBuffer(PrimaryLiveName, PrimaryDefaultNames[2]);
                BiosCpuSet(PrimaryLiveName, primary_edited, 10);
                context->name_length = NameByteLength(primary_edited) >> 1;
                PadEditedName(primary_edited);
                context->primary_cursor = phase;
                context->secondary_cursor = phase;
                goto update_editor;
            }
            if ((u8)IsSamePaddedName(primary_edited, ResetNameReference) != 0)
                context->reset_required = 1;
            else
                CopyNormalizedEditedName(context, PrimaryLiveName);
        } else {
            u8 *secondary_edited = context->edited_name;
            if ((u8)IsNameBufferBlank(secondary_edited) != 0) {
                CopyEncodedTextToBuffer(SecondaryLiveName, SecondaryDefaultNames[0]);
                BiosCpuSet(SecondaryLiveName, secondary_edited, 10);
                context->name_length = NameByteLength(secondary_edited) >> 1;
                PadEditedName(secondary_edited);
                context->primary_cursor = name_kind;
                context->secondary_cursor = name_kind;
update_editor:
                UpdateSaveNameEditor(context);
            } else {
                CopyNormalizedEditedName(context, SecondaryLiveName);
            }
        }
        if (context->reset_required != 0) {
            ShowNameDialog(context->window, 1, 44, NameDialogText, NameDialogStyle,
                           5, 5, 19, 4, 928);
            ConfigureNameDialog(2);
        } else {
            ShowNameDialog(context->window, 1, 8, NameDialogText, NameDialogStyle,
                           5, 5, 19, 4, 928);
            ConfigureNameDialog(2);
        }
        context->phase = 1;
        break;
    }
    case 1:
        if ((u16)PollNameDialog() != 0) {
            if ((u8)QueryNameDialogChoice() != 0) {
                goto finish_outer;
            } else if (context->reset_required != 0) {
                PrepareSaveReset(1, 136);
                EraseAllSaveSectorsWithRetries();
                context->phase = 2;
            } else {
                next_outer_state = 263;
                goto store_outer;
            }
        }
        break;
    case 2:
        ShowNameDialog(context->window, 1, 46, NameDialogText, NameDialogStyle,
                       4, 5, 21, 4, 928);
        ConfigureNameDialog(2);
        context->phase = 3;
        break;
    case 3:
        if ((u16)PollNameDialog() != 0) {
            FinishNameDialog(100);
            goto finish_outer;
        }
        break;
    }
    return;
finish_outer:
    next_outer_state = 260;
store_outer:
    *state_destination = next_outer_state;
}
asm(".global PrimaryLiveName\n.set PrimaryLiveName,0x02001f1c\n.global SecondaryLiveName\n.set SecondaryLiveName,0x020021a0\n.global PrimaryDefaultNames\n.set PrimaryDefaultNames,0x085516d0\n.global SecondaryDefaultNames\n.set SecondaryDefaultNames,0x08565f14\n.global ResetNameReference\n.set ResetNameReference,0x083a8284\n.global NameDialogText\n.set NameDialogText,0x030008b0\n.global NameDialogStyle\n.set NameDialogStyle,0x03000990\n.global IsNameBufferBlank\n.thumb_set IsNameBufferBlank,0x0812b571\n.global IsSamePaddedName\n.thumb_set IsSamePaddedName,0x0812a819\n.global CopyNormalizedEditedName\n.thumb_set CopyNormalizedEditedName,0x0812a879\n.global CopyEncodedTextToBuffer\n.thumb_set CopyEncodedTextToBuffer,0x08018c25\n.global BiosCpuSet\n.thumb_set BiosCpuSet,0x0814186d\n.global NameByteLength\n.thumb_set NameByteLength,0x081444b9\n.global PadEditedName\n.thumb_set PadEditedName,0x0812b59d\n.global UpdateSaveNameEditor\n.thumb_set UpdateSaveNameEditor,0x0812ae8d\n.global ShowNameDialog\n.thumb_set ShowNameDialog,0x0801174d\n.global ConfigureNameDialog\n.thumb_set ConfigureNameDialog,0x0801339d\n.global PollNameDialog\n.thumb_set PollNameDialog,0x08011861\n.global QueryNameDialogChoice\n.thumb_set QueryNameDialogChoice,0x08013381\n.global PrepareSaveReset\n.thumb_set PrepareSaveReset,0x08141571\n.global EraseAllSaveSectorsWithRetries\n.thumb_set EraseAllSaveSectorsWithRetries,0x0813bc31\n.global FinishNameDialog\n.thumb_set FinishNameDialog,0x08141541\n");
