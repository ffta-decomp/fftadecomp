typedef unsigned char u8;
typedef short s16;
typedef unsigned int u32;
extern u8 MapCornerQueryGate;
extern u32 EvaluateMapCornerState(s16,s16,s16,u8,u8,u8);
u8 CheckMapCornerState(s16 x, s16 y, s16 layer, u8 primary,
                       u8 enabled, u8 reserved)
{
    u8 result;
    MapCornerQueryGate = 1;
    result = EvaluateMapCornerState(x,y,layer,primary,enabled,reserved);
    MapCornerQueryGate = 0;
    return result;
}
asm(".set MapCornerQueryGate,0x0200f1d0\n");
asm(".thumb_set EvaluateMapCornerState,0x0801e711\n");
