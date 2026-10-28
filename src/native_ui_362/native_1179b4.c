typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed int s32;
typedef struct {u16 value,opaque[5];} Curve;
typedef struct {u16 counter,pad;u32 untouched;void *script;Curve firstCurve,secondCurve;void *first,*second;} SequenceWork;
typedef struct {u16 control;u8 pad[56];volatile u8 b58,b59,b60,b61;u8 b62;volatile u8 b63,b64,b65,b66,b67,b68;u8 pad69[5];volatile u8 b74;} Shadow;
extern Shadow DisplayShadow __asm__("0x03000940");
extern void SetupScene(const void *,u32,u32,u32,u32,u32) __asm__("0x080D7220");
extern u32 ChannelMask(u32) __asm__("0x080035D0");
extern u32 LayerMask(u32) __asm__("0x080035A8");
extern void InitCurve(Curve *,s32,s32,u32) __asm__("0x080E0608");
extern void TickCurve(Curve *) __asm__("0x080E064C");
extern u32 CurveDone(Curve *) __asm__("0x080E0690");
extern void *CreateWave(u32,u32,u32,void *) __asm__("0x080DAB84");
extern void SetWaveFlag(void *,u32) __asm__("0x080D9BA8");
extern void SetWavePosition(void *,u32,u32,u32) __asm__("0x080DAC40");
extern void *PollWave(void *) __asm__("0x080D9B64");
extern void *CreateScript(const void *,void *) __asm__("0x080D3E9C");
extern void *PollScript(void *) __asm__("0x080D3F08");
u32 RemainingBand43_001179B4(void *parent,u16 *event,SequenceWork *work)
{
    switch(*event) {
    case 1:
        break;
    case 256: {
        Shadow *shadow;
        u32 firstMask;
        SetupScene((const void *)0x088F46CC,0,2,0,0,0);
        firstMask=ChannelMask(2);
        shadow=&DisplayShadow;
        shadow->b66=63&~firstMask;
        shadow->b67=63;
        shadow->b68=63&~ChannelMask(2);
        shadow->b59=0;
        shadow->b58=0;
        shadow->b63=0;
        shadow->b62=255;
        shadow->b61=0;
        shadow->b60=0;
        shadow->b65=0;
        shadow->b64=-1;
        shadow->control|=0x6000;
        InitCurve(&work->firstCurve,0,64,60);
        InitCurve(&work->secondCurve,0,64,54);
        work->counter=6;
        work->first=CreateWave(1,0,0,parent);
        work->second=CreateWave(0,0,0,parent);
        SetWaveFlag(work->first,1);
        SetWaveFlag(work->second,1);
        work->script=CreateScript((const void *)0x0894D69C,parent);
        ++*event;
        break;
    }
    case 257: {
        u16 before;
        register u32 remaining __asm__("r6");
        TickCurve(&work->firstCurve);
        SetWavePosition(work->first,120,80,work->firstCurve.value);
        before=work->counter;
        remaining=before;
        __asm__("" : "+r" (remaining));
        if(remaining) {work->counter=before-1;break;}
        TickCurve(&work->secondCurve);
        SetWavePosition(work->second,120,80,work->secondCurve.value);
        if((u8)CurveDone(&work->firstCurve) && (u8)CurveDone(&work->secondCurve)) {
            Shadow *shadow=&DisplayShadow;
            shadow->b74=remaining;
            shadow->control&=0x9FFF;
            shadow->control&=~LayerMask(2);
            ++*event;
        }
        break;
    }
    case 258:
        work->first=PollWave(work->first);
        if(work->first) break;
        work->second=PollWave(work->second);
        if(work->second) break;
        work->script=PollScript(work->script);
        if(work->script) break;
        *event=2;
        break;
    }
    return 0;
}
