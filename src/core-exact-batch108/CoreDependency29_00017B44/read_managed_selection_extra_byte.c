typedef unsigned char u8;
typedef unsigned int u32;

struct ManagedSelectionExtraView {
    u8 unknown_00[21];
    u8 extra_byte;
};

u32 ReadManagedSelectionExtraByte(const struct ManagedSelectionExtraView *data)
{
    return data->extra_byte;
}
