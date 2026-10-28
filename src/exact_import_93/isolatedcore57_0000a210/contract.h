typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef struct { u8 prefix[0x2194]; u16 choices[0]; u8 count_gap[8]; u8 choice_count; } SaveChoiceView;
typedef char ChoicesOffset[((u32)&((SaveChoiceView *)0)->choices==0x2194)?1:-1];
typedef char CountOffset[((u32)&((SaveChoiceView *)0)->choice_count==0x219c)?1:-1];
extern SaveChoiceView gSave;
__asm__(".set gSave, 0x02000000");
