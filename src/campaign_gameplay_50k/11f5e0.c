typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;
typedef signed int s32;
typedef struct SceneTransformDefinition {
    s16 first_start, first_end, second_start, second_end, angle_start, angle_end;
    u16 duration, opaque14;
} SceneTransformDefinition;
typedef struct SceneTransformRow {
    u16 tick;
    u8 mode, opaque03;
    SceneTransformDefinition definition;
} SceneTransformRow;
typedef struct SceneEvent {
    u16 state, opaque02;
    const SceneTransformDefinition *definition;
    void **objects;
    u8 opaque12[8];
    u16 mode, skip_background;
    u8 opaque24[4];
} SceneEvent;
typedef struct SecondStageWork {
    u16 flags;
    u16 tick;
    u8 opaque04[4];
    u8 ordinal;
    u8 opaque09[3];
    void *child, *sprite, *background, *sequence;
    void *windows[2];
    void *prelude;
    u8 opaque40[4];
} SecondStageWork;
typedef struct SceneDisplay {
    u16 flags;
    u8 opaque02[56];
    volatile u8 lane58, lane59, lane60, lane61;
    u8 lane62;
    volatile u8 lane63;
    volatile s8 lane64;
    volatile u8 lane65, lane66, lane67, lane68;
} SceneDisplay;
typedef s32 (*SceneCallback)(void *,SceneEvent *,void *);
extern SceneDisplay AuthoredStageDisplay;
extern const s16 SecondStageScales[];
extern const SceneTransformRow SecondStageTimeline[];
extern void *StartPrelude(const void *,u32,void *) asm("RetailCall_080d7a70");
extern void *PollPrelude(void *) asm("RetailCall_080d7abc");
extern void CpuSet(const void *,void *,u32) asm("RetailCall_0814186c");
extern void StartStageResource(const void *,u32,u32,s32,s32,u32) asm("RetailCall_080d73ac");
extern void ApplyStageResource(const void *,u32,s32,s32,s32,s32,u32) asm("RetailCall_080d6e30");
extern void SetStageLayer(u32) asm("RetailCall_08003620");
extern u32 GetStageLayerMask(u32) asm("RetailCall_080035a8");
extern void *StartStageBackground(const void *,void *) asm("RetailCall_080d3e9c");
extern void *PollStageBackground(void *) asm("RetailCall_080d3f08");
extern void *CreateStageSprite(const void *,u32,s32,s32,u32,u32,u32,u32) asm("RetailCall_080d5cc0");
extern void *CreateStageWindow(u32,s32,s32,void *) asm("RetailCall_080dab84");
extern void SetStageWindowMode(void *,u32) asm("RetailCall_080d9ba8");
extern void ConfigureStageResourceA(const void *,u32,u32,u32,u32,u32) asm("RetailCall_080d7220");
extern void ConfigureStageResourceB(const void *,u32,u32,u32,u32,u32,u32) asm("RetailCall_080d72c8");
extern void *StartStageSequence(const void *,void *) asm("RetailCall_080d4704");
extern void StopSceneChild(void *) asm("RetailCall_08005b58");
extern void *CreateSceneChild(SceneCallback,u32,const SceneEvent *,void *) asm("RetailCall_08005b6c");
extern s32 PairedTransformChild(void *,SceneEvent *,void *) asm("StageChild_0811F28D");
extern void *PollStageSprite(void *) asm("RetailCall_08011484");
extern void *PollStageSequence(void *) asm("RetailCall_080d4774");
extern void *PollStageWindow(void *) asm("RetailCall_080d9b64");
/* Preserve only observed fresh reads; ordinary stores have no old-field read. */
#define READ_TICK() (*(const volatile u16 *)&work->tick)
#define READ_ORDINAL() (*(const volatile u8 *)&work->ordinal)
s32 AdvanceAuthoredSecondStage(void *,SceneEvent *,SecondStageWork *) asm("RemainingBand43_0011F5E0");
s32 AdvanceAuthoredSecondStage(void *parent_in,SceneEvent *event_in,SecondStageWork *work_in)
{
    register void *parent asm("r9") = parent_in;
    SceneEvent *event = event_in;
    register SecondStageWork *work asm("r5") = work_in;
    register u32 entry_flags asm("r2");
    register u32 pause_mask asm("r0");
    register u32 paused asm("r6");
    u16 zero_half;
    asm("" : "+r"(parent), "+r"(event), "+r"(work));
    entry_flags = work->flags;
    pause_mask = 0x8000;
    asm("" : "+r"(entry_flags), "+r"(pause_mask));
    pause_mask &= entry_flags;
    paused = (u16)pause_mask;
    asm("" : "+r"(paused));
    if (paused) return 0;
    switch (event->state) {
    case 0:
        work->prelude = StartPrelude((const void *)0x083A73F8,6,parent);
        zero_half = paused;
        CpuSet(&zero_half,(void *)0x03003940,0x01000010);
        break;
    case 1:
        break;
    case 256:
        work->prelude = PollPrelude(work->prelude);
        if (!work->prelude) {
            work->flags |= 1;
            event->state++;
        }
        break;
    case 257:
    {
        const void *resource = (const void *)0x088F66E0;
        u32 layer_mask;
        register const s16 *scale asm("r1");
        StartStageResource(resource,0,2,120,80,paused);
        scale = SecondStageScales;
        ApplyStageResource(resource,2,120,80,*scale,
            ({ const s16 *next_scale = scale;
               asm("" : "+r"(next_scale));
               *next_scale; }),paused);
        SetStageLayer(1);
        layer_mask = GetStageLayerMask(2);
        {
            register u32 flags_word asm("r1") = AuthoredStageDisplay.flags;
            asm("" : "+r"(flags_word));
            flags_word |= layer_mask;
            AuthoredStageDisplay.flags = flags_word;
        }
        work->background = StartStageBackground((const void *)0x0894DEDC,parent);
        event->state++;
        break;
    }
    case 258:
    {
        u32 next_tick;
        if (READ_TICK() <= 19) {
            ApplyStageResource((const void *)0x088F66E0,2,120,80,
                SecondStageScales[READ_TICK()],
                SecondStageScales[READ_TICK()],paused);
        }
        next_tick = READ_TICK() + 1;
        work->tick = next_tick;
        if ((u16)next_tick > 19) {
            work->background = PollStageBackground(work->background);
            if (!work->background) {
                work->tick = 20;
                event->state++;
            }
        }
        break;
    }
    case 259:
    {
        u32 next_tick = READ_TICK() - 1;
        register u32 zero_source asm("r3") = 0;
        register u32 display_zero asm("r8");
        register u32 first_zero asm("r0");
        register u32 lane_zero asm("r2");
        volatile u8 *byte_lane;
        register volatile u8 *lane60_address asm("r0");
        u32 layer_mask;
        asm("" : "+r"(zero_source));
        display_zero = zero_source;
        asm("" : "+r"(display_zero));
        work->tick = (u16)next_tick;
        if (next_tick << 16) break;
        layer_mask = GetStageLayerMask(2);
        AuthoredStageDisplay.flags &= ~layer_mask;
        SetStageLayer(0);
        work->sprite = CreateStageSprite((const void *)0x085088B4,0,120,80,664,8,paused,paused);
        AuthoredStageDisplay.lane66 = 31;
        AuthoredStageDisplay.lane67 = 63;
        AuthoredStageDisplay.lane68 = 31;
        /* One observed old-byte read, then one byte write at each site.
         * The first and repeated zero copies have distinct native consumers. */
        byte_lane = (volatile u8 *)&AuthoredStageDisplay + 59;
        (void)*byte_lane;
        first_zero = display_zero;
        asm("" : "+r"(first_zero));
        *byte_lane = first_zero;
        byte_lane = (volatile u8 *)&AuthoredStageDisplay + 58;
        (void)*byte_lane;
        lane_zero = display_zero;
        asm("" : "+r"(lane_zero));
        *byte_lane = lane_zero;
        byte_lane = (volatile u8 *)&AuthoredStageDisplay + 63;
        (void)*byte_lane;
        *byte_lane = lane_zero;
        AuthoredStageDisplay.lane62 = 255;
        byte_lane = (volatile u8 *)&AuthoredStageDisplay + 61;
        (void)*byte_lane;
        *byte_lane = lane_zero;
        /* R0 starts again at the real shadow base for this separate access. */
        lane60_address = (volatile u8 *)&AuthoredStageDisplay;
        asm("" : "+r"(lane60_address));
        lane60_address += 60;
        (void)*lane60_address;
        *lane60_address = lane_zero;
        byte_lane = (volatile u8 *)&AuthoredStageDisplay + 65;
        (void)*byte_lane;
        *byte_lane = lane_zero;
        AuthoredStageDisplay.lane64 = -1;
        AuthoredStageDisplay.flags |= 0x6000;
        work->windows[0] = CreateStageWindow(1,0,0,parent);
        work->windows[1] = CreateStageWindow(0,0,0,parent);
        SetStageWindowMode(work->windows[0],1);
        SetStageWindowMode(work->windows[1],1);
        ConfigureStageResourceA((const void *)0x088F68CC,1,3,0,paused,paused);
        ConfigureStageResourceB((const void *)0x088F68CC,1,3,0,paused,paused,1);
        work->sequence = StartStageSequence((const void *)0x0894D018,parent);
        event->state++;
        break;
    }
    case 260:
    {
        SceneEvent child_event;
        if (READ_TICK() == SecondStageTimeline[READ_ORDINAL()].tick) {
            if (work->child) StopSceneChild(work->child);
            child_event.mode = SecondStageTimeline[READ_ORDINAL()].mode;
            child_event.skip_background = paused;
            child_event.definition = &SecondStageTimeline[READ_ORDINAL()].definition;
            child_event.objects = &work->windows[0];
            work->child = CreateSceneChild(PairedTransformChild,60,&child_event,parent);
            work->ordinal = (u8)(READ_ORDINAL()+1);
        }
        work->tick = (u16)(READ_TICK()+1);
        if (READ_ORDINAL() > 6) {
            work->sprite = PollStageSprite(work->sprite);
            if (!work->sprite) {
                work->tick = 12;
                event->state++;
            }
        }
        break;
    }
    case 261:
    {
        u32 next_tick = READ_TICK();
        if (next_tick) {
            next_tick--;
            work->tick = (u16)next_tick;
            if (next_tick << 16) break;
            {
                register u32 completion_mask asm("r0") = 2;
                asm("" : "+r"(completion_mask));
                work->flags = completion_mask | entry_flags;
            }
        }
        if (work->child) {
            StopSceneChild(work->child);
            work->child = (void *)paused;
        }
        AuthoredStageDisplay.flags &= 0x9FFF;
        work->sequence = PollStageSequence(work->sequence);
        if (work->sequence) break;
        work->windows[0] = PollStageWindow(work->windows[0]);
        if (work->windows[0]) break;
        work->windows[1] = PollStageWindow(work->windows[1]);
        if (work->windows[1]) break;
        event->state = 2;
        break;
    }
    }
    return 0;
}
typedef char EventSize[(sizeof(SceneEvent)==28)?1:-1];
typedef char WorkSize[(sizeof(SecondStageWork)==44)?1:-1];
typedef char TimelineStride[(sizeof(SceneTransformRow)==20)?1:-1];
__asm__(".global RetailCall_080035a8\n.thumb_set RetailCall_080035a8,0x080035a9\n"
        ".global RetailCall_08003620\n.thumb_set RetailCall_08003620,0x08003621\n"
        ".global RetailCall_08005b58\n.thumb_set RetailCall_08005b58,0x08005b59\n"
        ".global RetailCall_08005b6c\n.thumb_set RetailCall_08005b6c,0x08005b6d\n"
        ".global RetailCall_08011484\n.thumb_set RetailCall_08011484,0x08011485\n"
        ".global RetailCall_080d3e9c\n.thumb_set RetailCall_080d3e9c,0x080d3e9d\n"
        ".global RetailCall_080d3f08\n.thumb_set RetailCall_080d3f08,0x080d3f09\n"
        ".global RetailCall_080d4704\n.thumb_set RetailCall_080d4704,0x080d4705\n"
        ".global RetailCall_080d4774\n.thumb_set RetailCall_080d4774,0x080d4775\n"
        ".global RetailCall_080d5cc0\n.thumb_set RetailCall_080d5cc0,0x080d5cc1\n"
        ".global RetailCall_080d6e30\n.thumb_set RetailCall_080d6e30,0x080d6e31\n"
        ".global RetailCall_080d7220\n.thumb_set RetailCall_080d7220,0x080d7221\n"
        ".global RetailCall_080d72c8\n.thumb_set RetailCall_080d72c8,0x080d72c9\n"
        ".global RetailCall_080d73ac\n.thumb_set RetailCall_080d73ac,0x080d73ad\n"
        ".global RetailCall_080d7a70\n.thumb_set RetailCall_080d7a70,0x080d7a71\n"
        ".global RetailCall_080d7abc\n.thumb_set RetailCall_080d7abc,0x080d7abd\n"
        ".global RetailCall_080d9b64\n.thumb_set RetailCall_080d9b64,0x080d9b65\n"
        ".global RetailCall_080d9ba8\n.thumb_set RetailCall_080d9ba8,0x080d9ba9\n"
        ".global RetailCall_080dab84\n.thumb_set RetailCall_080dab84,0x080dab85\n"
        ".global RetailCall_0814186c\n.thumb_set RetailCall_0814186c,0x0814186d\n"
        ".global StageChild_0811F28D\n.thumb_set StageChild_0811F28D,0x0811F28D\n"
        ".global AuthoredStageDisplay\n.set AuthoredStageDisplay,0x03000940\n"
        ".global SecondStageScales\n.set SecondStageScales,0x083A76A8\n"
        ".global SecondStageTimeline\n.set SecondStageTimeline,0x083A76D0\n");
