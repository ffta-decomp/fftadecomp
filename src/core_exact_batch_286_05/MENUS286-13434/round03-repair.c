typedef unsigned short u16;
typedef unsigned int u32;
typedef struct { unsigned char before[58]; u16 flags; } DialogTextContext;
extern DialogTextContext *gDialogTextContext;
u32 EnableTextContextFlag512(void) asm("SceneTaskDependency_00013434");
u32 EnableTextContextFlag512(void) { DialogTextContext *context=gDialogTextContext; u32 flags=context->flags; register u32 mask asm("r3") = 512; /* Preserve the original initialized mask and its copy into the return value. */ asm("" : "+r"(mask) : "r"(flags)); { register u32 result asm("r0") = mask; /* The real old flags stay live across this return-value definition. */ asm("" : "+r"(result) : "r"(flags)); result |= flags; context->flags=result; return result; } }
asm(".global gDialogTextContext\n.set gDialogTextContext, 0x0200918c\n");
