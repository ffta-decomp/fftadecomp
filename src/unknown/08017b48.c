typedef unsigned char u8;
typedef unsigned int u32;

/* The broader role of data byte22 is tentative; retain the observed wrap. */
u32 ReadManagedSelectionShiftedByte(const u8 *data)
{
    return (u8)(data[22] << 1);
}
