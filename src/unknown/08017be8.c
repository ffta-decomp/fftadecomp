short GetSelectionDataEnd(const unsigned short *data) __asm__("CoreFrontier_00017BE8");
short GetSelectionDataEnd(const unsigned short *data)
{
    return (short)(data[12] - 1);
}
