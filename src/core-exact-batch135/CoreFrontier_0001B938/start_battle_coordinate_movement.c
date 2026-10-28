typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;
struct Curve {int words[11];};
struct CoordinateMotion {
    u8 unknown0[36];u16 x,y;u8 unknown40[12];
    u8 moving,done;u16 target_x,target_y,speed;
    struct Curve x_curve,y_curve;
};
typedef char CurveSize[sizeof(struct Curve)==44?1:-1];
extern struct CoordinateMotion gCoordinateMotion;
extern u32 BiosSquareRoot(u32);
extern int BiosDivide(int,int);
extern int BiosRemainder(int,int);
extern void InitializeCurve(struct Curve *,int,int,int,int);
u32 CoreFrontier_0001B938(u16 target_x,u16 target_y)
{
    s16 dx,dy;
    int x,y;
    u16 current_x,current_y;
    u16 distance,duration;
    if((s16)target_x == (s16)gCoordinateMotion.x &&
       (s16)target_y == (s16)gCoordinateMotion.y)return 0;
    current_x=gCoordinateMotion.x;
    x=(s16)target_x;
    dx=(s16)(x-current_x);
    current_y=gCoordinateMotion.y;
    y=(s16)target_y;
    dy=(s16)(y-current_y);
    distance=(u16)BiosSquareRoot(((u32)(dx*dx)+(u32)(dy*dy))<<8);
    distance>>=4;
    duration=BiosDivide(distance,gCoordinateMotion.speed);
    if(BiosRemainder(distance,gCoordinateMotion.speed))duration++;
    gCoordinateMotion.target_x=target_x;
    gCoordinateMotion.target_y=target_y;
    InitializeCurve(&gCoordinateMotion.x_curve,(s16)gCoordinateMotion.x,0,
                    x,duration-1);
    InitializeCurve(&gCoordinateMotion.y_curve,(s16)gCoordinateMotion.y,0,
                    y,duration-1);
    gCoordinateMotion.moving=1;
    gCoordinateMotion.done=0;
    return duration;
}
asm(".global gCoordinateMotion\n.set gCoordinateMotion,0x02007f40\n.global BiosSquareRoot\n.thumb_set BiosSquareRoot,0x08141899\n.global BiosDivide\n.thumb_set BiosDivide,0x08141871\n.global BiosRemainder\n.thumb_set BiosRemainder,0x08141875\n.global InitializeCurve\n.thumb_set InitializeCurve,0x080075cd\n");
