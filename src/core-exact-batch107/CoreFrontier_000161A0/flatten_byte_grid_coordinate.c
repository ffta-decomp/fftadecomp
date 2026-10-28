typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
u32 CoreFrontier_000161A0(u32 input_x,u32 input_y,u32 input_stride)
{
 u8 x=input_x;
 u8 y=input_y;
 u8 stride=input_stride;
 return (u16)(y*stride+x);
}
