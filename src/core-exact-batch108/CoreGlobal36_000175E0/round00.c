typedef unsigned char u8;
typedef unsigned short u16;
struct SelectionFlags { u8 unknown_00[16]; u16 flags; };
void ModifyManagedSelectionFlags(struct SelectionFlags *selection, u8 operation, u16 mask)
{
    switch (operation) {
    case 0: selection->flags = mask; break;
    case 1: selection->flags |= mask; break;
    case 2: selection->flags &= ~mask; break;
    }
}
