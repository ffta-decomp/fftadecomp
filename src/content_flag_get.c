typedef unsigned char u8;
typedef unsigned short u16;

extern u8 GetGameFlag(u16 flag);

/* Flag 0x21f is consumed by nearby content-state code; its game meaning is unknown. */
u8 GetContentFlag21F(void)
{
    return GetGameFlag(0x21f);
}
