typedef unsigned char u8;
typedef unsigned int u32;
struct SelectionControlView {
    u8 unknown[31];
    u8 mode;
};
extern void PrepareSelectionControl(struct SelectionControlView *control);
__asm__(".global PrepareSelectionControl\n.thumb_set PrepareSelectionControl,0x08016d65");
void SetSelectionControlMode(struct SelectionControlView *control, u32 mode) __asm__("sub_08017508");
void SetSelectionControlMode(struct SelectionControlView *control, u32 mode)
{
    control->mode = mode;
    PrepareSelectionControl(control);
}
