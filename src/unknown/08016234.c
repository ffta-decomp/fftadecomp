typedef unsigned char u8;
extern void UpdateSelectionWidget(void *widget);

void UpdateManagedSelectionWidgets(u8 *controller)
{
    UpdateSelectionWidget(controller + 76);
    UpdateSelectionWidget(controller + 96);
}

asm(".global UpdateSelectionWidget\n"
    ".thumb_set UpdateSelectionWidget, 0x08017c69\n");
