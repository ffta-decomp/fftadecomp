typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;
struct Ramp {u16 value;s16 remaining,error;u16 step,period,magnitude;};
struct Work {u16 delay;u8 unknown2[6];struct Ramp first,second;u32 unknown32;};
typedef char WorkSize[sizeof(struct Work)==36?1:-1];
extern void ReadChannels(u8 *,u8 *);
extern void SetChannelMode(u32,u32);
extern void SetChannels(u32,u32);
extern void InitializeRamp(struct Ramp *,u16,u16,u16);
extern void AdvanceRamp(struct Ramp *);
extern u32 RampComplete(struct Ramp *);
u32 AdvanceAuthoredPairedEnvelope(void *,u16 *,struct Work *) asm("RemainingBand43_0011ACF4");
u32 AdvanceAuthoredPairedEnvelope(void *parent,u16 *phase,struct Work *work)
{
    u8 first_channel,second_channel;
    switch(*phase) {
    case 0:
        break;
    case 256:
        if(work->delay!=0) {
            --work->delay;
            break;
        }
        ReadChannels(&first_channel,&second_channel);
        SetChannelMode(first_channel,1);
        SetChannelMode(second_channel,1);
        SetChannels(0,0);
        InitializeRamp(&work->first,0,15,20);
        InitializeRamp(&work->second,0,15,20);
        ++*phase;
        break;
    case 257: {
        struct Ramp *first=&work->first;
        struct Ramp *second;
        AdvanceRamp(first);
        second=&work->second;
        AdvanceRamp(second);
        SetChannels((u8)work->first.value,(u8)work->second.value);
        if((u8)RampComplete(first) && (u8)RampComplete(second)) {
            InitializeRamp(first,15,0,20);
            InitializeRamp(second,15,0,20);
            ++*phase;
        }
        break;
    }
    case 258: {
        struct Ramp *first=&work->first;
        struct Ramp *second;
        AdvanceRamp(first);
        second=&work->second;
        AdvanceRamp(second);
        SetChannels((u8)work->first.value,(u8)work->second.value);
        if((u8)RampComplete(first) && (u8)RampComplete(second))
            *phase=2;
        break;
    }
    }
    return 0;
}
asm(".global ReadChannels\n.thumb_set ReadChannels,0x0801e611\n.global SetChannelMode\n.thumb_set SetChannelMode,0x080d4d59\n.global SetChannels\n.thumb_set SetChannels,0x080d4da1\n.global InitializeRamp\n.thumb_set InitializeRamp,0x080e0609\n.global AdvanceRamp\n.thumb_set AdvanceRamp,0x080e064d\n.global RampComplete\n.thumb_set RampComplete,0x080e0691\n");
