typedef unsigned char u8;
typedef unsigned short u16;

struct ContentFlagSaveView {
    u8 unknown_prefix[0x2192];
    u16 halfword_2192;
    u16 halfword_2194;
};

extern struct ContentFlagSaveView gSaveData;
extern void SetGameFlag(u16 flag, u16 value);

/* The field and flag names remain offset-based until caller evidence identifies them. */
void CopySaveHalfword2194To2192AndSetFlag21F(void)
{
    gSaveData.halfword_2192 = gSaveData.halfword_2194;
    SetGameFlag(0x21f, 1);
}
