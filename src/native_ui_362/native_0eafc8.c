typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;
typedef signed int s32;
typedef struct {s16 x,y;} Position;
typedef struct {Position value[4];} Positions;
typedef struct {u16 timer,padding;void *orbiters[4];void *trails[20];} OrbitWork;
extern void *CreateObject(const void *,u32,s32,s32,u32,u32,u32,u32) __asm__("0x080D5CC0");
extern void CopyBytes(void *,const void *,u32) __asm__("0x081443FC");
extern s32 Cosine(u32) __asm__("0x08007A60");
extern s32 Sine(u32) __asm__("0x08007A4C");
extern void SetPosition(void *,s32,s32,u32) __asm__("0x080107D4");
extern u32 FindTrailSlot(void **,u32) __asm__("0x080D5FA4");
extern void UpdateTrails(void **,u32) __asm__("0x080D5F24");
extern void CloseObjects(void **,u32) __asm__("0x080D5F74");
u32 RemainingBand43_000EAFC8(void *unused,u16 *event,OrbitWork *work)
{
    Positions positions;
    u8 phases[4];
    u16 times[12];
    switch (*event) {
    case 0: {
        u16 i;
        positions=*(const Positions *)0x08149CA4;
        for (i=0;i<4;i++)
            work->orbiters[i]=CreateObject((const void *)0x084F7288,2,positions.value[i].x,positions.value[i].y,954,6,1,0);
        break;
    }
    case 1:
        break;
    case 256: {
        u16 i;
        u32 matched;
        positions=*(const Positions *)0x08149CB4;
        CopyBytes(phases,(const void *)0x08149CC4,4);
        CopyBytes(times,(const void *)0x08149CC8,24);
        i=0;
        if(work->timer!=times[0]) {
            register u32 limit __asm__("r3")=12;
            __asm__("" : "+r" (limit));
            do {
                ++i;
                if(i>=limit) break;
            } while(*(volatile u16 *)&work->timer!=times[i]);
        }
        matched=(u8)i;
        for (i=0;i<4;i++) {
            u16 x;
            s16 sx,sy;
            s32 rawCosine;
            u32 spawn_limit;
            rawCosine=Cosine((u8)(phases[i]-2*(u8)work->timer));
            __asm__("" : "+r" (rawCosine) : "r" (&positions.value[i]));
            x=((s16)rawCosine>>2)+(u16)positions.value[i].x;
            sy=((s16)Sine((u8)(phases[i]-2*(u8)work->timer))>>2)+(u16)positions.value[i].y;
            sx=(s16)x;
            SetPosition(work->orbiters[i],sx,sy,0);
            spawn_limit=sizeof(times)/sizeof(times[0]);
            if((u16)(sx+4)<=247 && sy>=-4 && sy<=163 && matched<spawn_limit) {
                u16 slot=(u16)FindTrailSlot(work->trails,20);
                work->trails[(s16)slot]=CreateObject((const void *)0x084F7288,3,sx,sy,954,6,1,0);
            }
        }
        UpdateTrails(work->trails,20);
        if(++work->timer==64) ++*event;
        break;
    }
    case 257:
        CloseObjects(work->orbiters,4);
        CloseObjects(work->trails,20);
        *event=2;
        break;
    }
    return 0;
}
