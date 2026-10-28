typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;
struct PrimaryTaskGraphic {
    u8 unknown0[8];
    s16 secondary_x;
    s16 height;
    u8 unknown12[6];
    u8 status;
    u8 columns;
    u8 unknown20[16];
    void *graphic;
};
extern void SubmitTaskGraphic(void *, int, int, u32, u32, u32, u32, u32,
                              u32, u32, u32);
__asm__(".global SubmitTaskGraphic\n.thumb_set SubmitTaskGraphic,0x08001cf1");
/* Truncate the optional displacement before the outgoing signed-halfword conversion. */
void DrawPrimaryUnitTaskGraphic(struct PrimaryTaskGraphic *payload)
{
    u16 position = (u16)payload->secondary_x;
    void *graphic;
    if (payload->status & 16) {
        register u32 columns __asm__("r1") = payload->columns * 8;
        register int signed_position __asm__("r0") = (s16)position;
        /* Preserve the original pre-subtraction sign extension, not just final low16 equivalence. */
        __asm__("" : "+r"(signed_position) : "r"(columns));
        position = signed_position - columns;
    }
    graphic = payload->graphic;
    if (graphic != 0)
        SubmitTaskGraphic(graphic, (s16)position, payload->height, 0,
                          0, 1, 1, 0, 576, 1, 0);
}
