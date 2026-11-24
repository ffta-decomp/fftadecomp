typedef unsigned short u16;
typedef unsigned int u32;
extern void BiosClearSelectionHalfwords(const void *, void *, u32);
void ClearManagedSelectionTextCells(void *destination, u16 count)
{
    u32 zero = 0;
    BiosClearSelectionHalfwords(&zero, destination, ((u32)count << 3) | 0x01000000);
}
asm(".thumb_set BiosClearSelectionHalfwords, 0x08141869\n");
