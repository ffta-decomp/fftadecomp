#ifndef SCENE_CONTEXT_ABI_H
#define SCENE_CONTEXT_ABI_H
/* Agbcc/ARM7TDMI ABI; explicitly 8/16/32-bit integer types and 32-bit pointers. */
typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;
typedef signed int s32;
#define SCENE_ROOT_POINTER_ADDRESS ((volatile u32 *)0x020159ccu)
#define SCENE_RUNTIME_CONTROL_OFFSET 0x0cu
#define SCENE_PATH_BASE_OFFSET 0x58u
#define SCENE_PATH_SLOT_STRIDE 0x84u
#define SCENE_COMMAND_BYTE_OFFSET 0x0fu
#define SCENE_RUNTIME_WORD_OFFSET 0x10u
#define SCENE_TASK_CONTEXT_OFFSET 0x898u
#define SCENE_ENTITY_RECORD_OFFSET 0x89cu
#define SCENE_HANDLE_SLOT_COUNT 16u
#define scene_root_byte(offset) ((volatile u8 *)(u32)(*SCENE_ROOT_POINTER_ADDRESS + (offset)))
#endif
