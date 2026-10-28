/* Method-local interface declarations from the frozen build. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
extern u8 GetGameFlag(int);
extern u32 ReadProperty(void *,int);
extern u8 Check8240(void *);

asm(".global GetGameFlag\n.thumb_set GetGameFlag,0x80c9541\n.global ReadProperty\n.thumb_set ReadProperty,0x80c7ea5\n.global Check8240\n.thumb_set Check8240,0x80c8241");
u8 SelectFlagUnlockedUnitCommand(void *unit,u16 *value)
{
    int flag;
    *value = 14;
    if (GetGameFlag(2)) goto unavailable;
    if (ReadProperty(unit,38) <= 9) goto unavailable;
    if (Check8240(unit)) goto unavailable;
    switch (ReadProperty(unit,3)) {
    case 1: case 23:
        *value = 80;
        flag = 0x23d;
        break;
    case 2:
        *value = 81;
        flag = 0x241;
        break;
    case 3: case 20:
        *value = 82;
        flag = 0x240;
        break;
    case 4:
        *value = 83;
        flag = 0x242;
        break;
    case 5:
        *value = 84;
        flag = 0x23f;
        break;
    default: goto unavailable;
    }
    if (!GetGameFlag(flag)) goto unavailable;
    return 1;
unavailable:
    return 0;
}
