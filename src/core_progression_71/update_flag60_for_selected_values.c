/* Method-local interface declarations from the frozen build. */
typedef unsigned char u8;
typedef unsigned short u16;
extern u8 gSaveData[];
extern void SetGameFlag(u16 flag, u16 value);
typedef unsigned int u32;


/* Preserve the listed values and the separate96 continuation; no modulo rule. */
void UpdateFlag60ForSelectedValues(void)
{
    u32 value = gSaveData[0x21b4];

    if (value == 10 || value == 20 || value == 30 || value == 40 ||
        value == 50 || value == 60 || value == 70 || value == 80 || value == 90)
        SetGameFlag(60, 1);
    else if (value == 96)
        SetGameFlag(60, 1);
}
