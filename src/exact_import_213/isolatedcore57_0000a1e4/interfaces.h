typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct BattleScriptCursor {
    u16 unknown_0;
    u16 cursor;
} BattleScriptCursor;
typedef char CursorOffsetMustBeTwo[((unsigned int)&((BattleScriptCursor *)0)->cursor == 2) ? 1 : -1];

extern u32 ReadGameFlag(u16 flag_id);
asm(".global ReadGameFlag\n.thumb_set ReadGameFlag, 0x080c9541");
