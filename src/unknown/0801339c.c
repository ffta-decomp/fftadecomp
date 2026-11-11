typedef unsigned char u8;
typedef unsigned short u16;
struct ManagedDialogContext { u8 unknown_00[32]; u16 output_flags; };
extern struct ManagedDialogContext *ManagedDialogContextCell;
void SetManagedDialogOutputFlags(u16 flags)
{
    ManagedDialogContextCell->output_flags = flags | 1;
}
asm(".set ManagedDialogContextCell, 0x0200918c\n");
