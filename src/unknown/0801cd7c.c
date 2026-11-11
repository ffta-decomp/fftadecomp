typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;
u32 Source52_0001CD7C(int raw_x,int raw_y)
{
 u16 y=raw_y;
 int x=(s16)raw_x;
 int second;
 if(x<0) goto invalid;
 if(x>15) goto invalid;
 second=(s16)y;
 if(second<0) goto invalid;
 if(second>15) goto invalid;
 return 1;
invalid:
 return 0;
}
