typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef struct { u8 prefix[4]; u16 result_selector; u8 result_state; } SceneResultContext;
typedef struct { u8 opcode; u8 selector; } SceneResultCommand;
typedef char SelectorOffset[((u32)&((SceneResultContext*)0)->result_selector==4)?1:-1];
typedef char StateOffset[((u32)&((SceneResultContext*)0)->result_state==6)?1:-1];
