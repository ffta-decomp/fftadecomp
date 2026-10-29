typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
struct UnitKey { u8 packed; };
struct UnitRecord {
    u8 unknown0[40];
    u16 status;
    u8 unknown42[218];
    u8 group;
    u8 unknown261[3];
};
struct ExchangeState;
extern u8 ReadSaveByte(u16 index);
extern struct ExchangeState *GetBattleContext(void);
extern struct UnitRecord *GetContextUnit(struct ExchangeState *state,u32 index);
extern struct UnitRecord gPrimaryUnits[24];
extern struct UnitRecord gSecondaryUnits[12];
typedef char UnitSize264[(sizeof(struct UnitRecord)==264)?1:-1];
