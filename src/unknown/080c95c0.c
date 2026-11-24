typedef unsigned char u8;
typedef unsigned short u16;

/* The complete save image layout is still being recovered. */
struct SaveImage {
    u8 unknown_prefix[0x2030];
    u8 bytes[0];
};

extern struct SaveImage gSaveData;

void WriteSaveByte(u16 index, u8 value)
{
    gSaveData.bytes[index] = value;
}
