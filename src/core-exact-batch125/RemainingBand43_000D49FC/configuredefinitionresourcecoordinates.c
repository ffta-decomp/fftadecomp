#include "../../../src/task_tree_core.h"

typedef signed char s8;
typedef signed short s16;

extern void ConfigureDefinitionResource(u8,u8,u16,s16,s16,u8);
void ConfigureDefinitionResourceCoordinates(u8 slot, u8 mode, u16 parameter,
                                            s16 x, s16 y)
{
    ConfigureDefinitionResource(slot,mode,parameter,x,y,0);
}

asm(".global ConfigureDefinitionResource\n.thumb_set ConfigureDefinitionResource,0x80d4a29\n");
