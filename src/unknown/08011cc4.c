typedef unsigned short u16;
typedef unsigned int u32;
typedef struct { unsigned char before[34]; u16 setting; } DialogTextContext;
extern DialogTextContext *gDialogTextContext;
void SetDialogTextSetting(u32 value) asm("CoreDependency29_00011CC4");
void SetDialogTextSetting(u32 value) { gDialogTextContext->setting = value; }
asm(".global gDialogTextContext\n.set gDialogTextContext, 0x0200918c\n");
