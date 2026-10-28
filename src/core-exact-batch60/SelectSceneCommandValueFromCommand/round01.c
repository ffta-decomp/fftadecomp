/* Original authored selection command: three ordered continuations. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
struct SceneSelectionRow { u8 prefix[38]; u8 selection_value; u8 trailing; };
struct SceneSelectionRuntime { u8 prefix[148]; volatile u16 flags; };
typedef char selection_row_size_check[(sizeof(struct SceneSelectionRow)==40)?1:-1];
typedef char selection_value_offset_check[((u32)&(((struct SceneSelectionRow*)0)->selection_value)==38)?1:-1];
typedef char selection_flags_offset_check[((u32)&(((struct SceneSelectionRuntime*)0)->flags)==148)?1:-1];
extern const struct SceneSelectionRow gSceneSelectionRows[];
extern struct SceneSelectionRuntime gSceneSelectionRuntimeView;
asm(".global gSceneSelectionRows\n.set gSceneSelectionRows,0x0854cd54\n.global gSceneSelectionRuntimeView\n.set gSceneSelectionRuntimeView,0x0200f390\n");
extern void ClearSelectedSceneRuntimeBytes(u32,u32);
extern u32 GetCurrentOrPendingSceneRecordIndex(void);
extern u32 GetIndexedFlagState(u32);
extern void SetSceneRuntimeCommandByte(u32);
extern void ApplySceneSelectionValue(u32);
extern void FinalizeSceneSelectionCommand(void);
u32 SelectSceneCommandValueFromCommand(u32 *scene_context,const u8 *command)
{
    const struct SceneSelectionRow *row;
    u32 index;
    u8 selected_value;
    (void)scene_context;
    ClearSelectedSceneRuntimeBytes(0,255);
    if (command[1] == 255) {
        index = (u16)GetCurrentOrPendingSceneRecordIndex();
        row = gSceneSelectionRows + index;
        if (gSceneSelectionRuntimeView.flags & 0x80) {
            selected_value = (u8)GetIndexedFlagState(20);
            ApplySceneSelectionValue(selected_value);
            SetSceneRuntimeCommandByte(selected_value);
        } else {
            SetSceneRuntimeCommandByte(row->selection_value);
            ApplySceneSelectionValue(row->selection_value);
        }
    } else {
        SetSceneRuntimeCommandByte(command[1]);
        ApplySceneSelectionValue(command[1]);
    }
    FinalizeSceneSelectionCommand();
    return 0x100;
}
