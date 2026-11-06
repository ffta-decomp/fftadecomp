typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;
typedef signed int s32;
typedef struct StageEvent {
    u16 state, opaque02;
    u8 *signal;
    u8 opaque08[12];
    u16 index;
    u8 opaque22[6];
} StageEvent;
typedef struct IndexedStageWork {
    u16 flags, tick;
    u8 opaque04[4];
    u8 index, opaque09[3];
    u8 *signal;
    u16 remaining, opaque18;
    u8 *destination;
    const u8 *source;
    void *sprite, *optional, *background;
    void *sequences[4];
    u16 tilemap[2048];
    u8 opaque4152[4];
} IndexedStageWork;
typedef struct MapDimensions { u8 width, height, opaque02[2]; } MapDimensions;
extern u16 StageDisplayFlags;
extern const void *const StageBackgrounds[];
extern const void *const StageSequencesA[];
extern const void *const StageSequencesB[];
extern const u8 *const StageTileSources[];
extern const u16 StageTileByteCounts[];
#define StageMapSources ((const u16 *const *)0x083A77B8)
#define StageMapDimensions ((const MapDimensions *)0x083A77CC)
extern const s16 StageScales[];
extern void CpuSet(const void *,void *,u32) asm("RetailCall_0814186c");
extern void SetupStageLayer(u32,u32,u32,u32,u32,void *,void *) asm("RetailCall_080d74e0");
extern u32 GetStageLayerMask(u32) asm("RetailCall_080035a8");
extern void *StartSequence(const void *,void *) asm("RetailCall_080d4704");
extern void *PollSequence(void *) asm("RetailCall_080d4774");
extern void *StartBackground(const void *,void *) asm("RetailCall_080d3e9c");
extern void *PollBackground(void *) asm("RetailCall_080d3f08");
extern void SetBackgroundParameters(void *,u32,u32) asm("RetailCall_080d3f84");
extern void SetupOptional(u32,u32,u32,u32,u32,u32) asm("RetailCall_080d4a28");
extern void *CreateOptional(u32,const void *,u32,u32) asm("RetailCall_080d4b64");
extern void PrepareOptional(void *) asm("RetailCall_0800bd7c");
extern void SetOptionalIndex(void *,u32) asm("RetailCall_0800bdf8");
extern void ReleaseOptional(void *,u32) asm("RetailCall_080d4d14");
extern void *GetCopyContext(void) asm("RetailCall_080d3af8");
extern void CopyStageWords(void *,const void *,void *,u32) asm("RetailCall_08000adc");
extern void CopyStageHalfwords(void *,const void *,void *,u32) asm("RetailCall_08000a98");
extern void *CreateStageSprite(const void *,u32,s32,s32,u32,u32,u32,u32) asm("RetailCall_080d5cc0");
extern void SetSpriteFlag(void *,u32) asm("RetailCall_080110f8");
extern void TransformSprite(void *,s32,s32,u32) asm("RetailCall_080112cc");
extern void ReleaseSprite(void *) asm("RetailCall_08011428");
#define READ_INDEX() (*(const volatile u8 *)&work->index)
#define READ_TICK() (*(const volatile u16 *)&work->tick)
#define READ_REMAINING() (*(const volatile u16 *)&work->remaining)

/* One real phase-update operation, shared by two source predecessors.
 * Keep its initialized R2 observation at one inline source site so the
 * pinned compiler can compare the complete duplicated tail truthfully. */
static __inline__ void AdvanceChunkEventPhase(StageEvent *event)
{
    register StageEvent *chunk_event asm("r2") = event;
    asm("" : "+r"(chunk_event));
    chunk_event->state++;
}
s32 AdvanceIndexedAuthoredStage(void *,StageEvent *,IndexedStageWork *) asm("RemainingBand43_0011F95C");
s32 AdvanceIndexedAuthoredStage(void *parent_in,StageEvent *event_in,IndexedStageWork *work_in)
{
    register void *parent asm("r4") = parent_in;
    register StageEvent *event asm("r8") = event_in;
    register IndexedStageWork *work asm("r5") = work_in;
    register u32 flags asm("r1");
    register u32 mask asm("r0");
    register u32 paused asm("r6");
    u16 zero_half;
    u16 white_half;
    u16 *tilemap_snapshot;
    asm("" : "+r"(parent), "+r"(event), "+r"(work));
    flags = work->flags;
    mask = 0x8000;
    asm("" : "+r"(flags), "+r"(mask));
    mask &= flags;
    paused = (u16)mask;
    asm("" : "+r"(paused));
    if (paused) return 0;
    switch (event->state) {
    case 0: {
        u8 *clear_base;
        u32 clear_control;
        register u32 clear_delta asm("r3");
        register u16 *fill_address asm("r0");
        register u32 fill_literal asm("r2");
        register u32 fill_store asm("r1");
        register StageEvent *initial_event asm("r1") = event;
        asm("" : "+r"(initial_event));
        work->index = initial_event->index;
        work->signal = initial_event->signal;
        *work->signal = paused;
        zero_half = paused;
        clear_base = (u8 *)0x03003920;
        clear_control = 0x01000010;
        asm("" : "+r"(clear_base), "+r"(clear_control));
        CpuSet(&zero_half,clear_base,clear_control);
        fill_address = &white_half;
        asm("" : "+r"(fill_address));
        fill_literal = 0x7FFF;
        asm("" : "+r"(fill_literal));
        fill_store = fill_literal;
        asm("" : "+r"(fill_store));
        *fill_address = fill_store;
        clear_delta = 0x220;
        asm("" : "+r"(clear_delta));
        clear_base += clear_delta;
        asm("" : "+r"(clear_base));
        CpuSet(fill_address,clear_base,clear_control);
        break; }
    case 1:
        break;
    case 256:
    {
        u32 layer_mask;
        register u32 display_flags asm("r1");
        SetupStageLayer(1,0,0,0,paused,(void *)0x06008000,(void *)0x06007000);
        layer_mask = GetStageLayerMask(1);
        display_flags = StageDisplayFlags;
        asm("" : "+r"(display_flags));
        display_flags |= layer_mask;
        StageDisplayFlags = display_flags;
        work->sequences[0] = StartSequence((const void *)0x0894D17C,parent);
        work->background = StartBackground((const void *)0x0894D69C,parent);
        SetBackgroundParameters(work->background,2,63);
        goto shared_increment;
    }
    case 257:
        work->background = PollBackground(work->background);
        if (work->background) break;
        *work->signal = 1;
        work->sequences[0] = PollSequence(work->sequences[0]);
        if (work->sequences[0]) break;
        if (READ_INDEX()) {
            u32 layer_mask;
            register u32 display_flags asm("r1");
            SetupOptional(0,2,0,0,paused,1);
            work->optional = CreateOptional(0,(const void *)0x088F3D90,412,8);
            PrepareOptional(work->optional);
            SetOptionalIndex(work->optional,(u16)(READ_INDEX()-1));
            layer_mask = GetStageLayerMask(2);
            display_flags = StageDisplayFlags;
            asm("" : "+r"(display_flags));
            display_flags |= layer_mask;
            StageDisplayFlags = display_flags;
        }
        work->source = StageTileSources[READ_INDEX()];
        work->destination = (u8 *)0x06000000;
        work->remaining = StageTileByteCounts[READ_INDEX()];
        {
            register StageEvent *advance_event asm("r1") = event;
            asm("" : "+r"(advance_event));
            advance_event->state++;
        }
        break;
    case 258:
    {
        u32 final_chunk = 0;
        register u32 chunk asm("r4");
        register u32 remaining_compare asm("r0");
        register u32 maximum_chunk asm("r3");
        remaining_compare = READ_REMAINING();
        asm("" : : "r"(remaining_compare));
        maximum_chunk = 4096;
        asm("" : "+r"(maximum_chunk));
        if (remaining_compare > maximum_chunk) chunk = maximum_chunk;
        else { chunk = READ_REMAINING(); final_chunk = 1; }
        asm("" : "+r"(chunk));
        CopyStageWords(GetCopyContext(),work->source,work->destination,chunk >> 2);
        work->destination += chunk;
        work->source += chunk;
        work->remaining = READ_REMAINING() - chunk;
        if (final_chunk) {
            /* This predecessor performs the same real update as state 260.
             * The initialized event access is identical on both edges. */
            AdvanceChunkEventPhase(event);
        }
        break;
    }
    case 259:
    {
        u16 cursor;
        u8 row;
        u32 index;
        const MapDimensions *first_dimensions;
        white_half = paused;
        {
            register u16 *clear_map asm("r4") = work->tilemap;
            asm("" : "+r"(clear_map));
            CpuSet(&white_half,clear_map,0x01000800);
            cursor = 0;
            row = 0;
            {
                register u32 first_index asm("r1") = READ_INDEX();
                asm("" : "+r"(first_index));
                index = first_index;
            }
            first_dimensions = &StageMapDimensions[index];
            asm("" : "+r"(first_dimensions));
            tilemap_snapshot = clear_map;
        }
        if (paused < first_dimensions->height) {
            register u16 *scan_map asm("r6") = tilemap_snapshot;
            asm("" : "+r"(scan_map));
            do {
                u8 column = 0;
                const MapDimensions *row_dimensions;
                register u32 next_row asm("r12");
                row_dimensions = &StageMapDimensions[index];
                asm("" : "+r"(row_dimensions));
                next_row = row + 1;
                asm("" : "+r"(next_row));
                if (column < row_dimensions->width) {
                    register u32 row_base asm("r4");
                    register const u16 *const *map_sources asm("r10") = StageMapSources;
                    register u32 sentinel asm("r9") = 0x3FF;
                    asm("" : "+r"(map_sources), "+r"(sentinel));
                    row_base = (u32)row << 5;
                    asm("" : "+r"(row_base));
                    do {
                        u32 tile = map_sources[index][cursor];
                        u32 destination;
                        if (tile == sentinel) tile = 0;
                        if (column <= 31) destination = row_base + column;
                        else {
                            u32 wrapped_column = (column & 31) + 1024;
                            asm("" : "+r"(wrapped_column));
                            destination = row_base + wrapped_column;
                        }
                        *(u16 *)((u32)scan_map + (destination << 1)) = tile;
                        cursor++;
                        column++;
                        {
                            register u32 refreshed_index asm("r1") = READ_INDEX();
                            asm("" : "+r"(refreshed_index));
                            index = refreshed_index;
                        }
                    } while (column < StageMapDimensions[index].width);
                }
                row = next_row;
                {
                    register u32 refreshed_index asm("r1") = READ_INDEX();
                    asm("" : "+r"(refreshed_index));
                    index = refreshed_index;
                }
            } while (row < StageMapDimensions[index].height);
        }
        CopyStageHalfwords(GetCopyContext(),tilemap_snapshot,(void *)0x06006000,2048);
        {
            register StageEvent *advance_event asm("r1") = event;
            asm("" : "+r"(advance_event));
            advance_event->state++;
        }
        break;
    }
    case 260:
        work->sequences[0] = StartSequence((const void *)0x0894D18C,parent);
        work->sequences[1] = StartSequence(StageSequencesA[READ_INDEX()],parent);
        work->sequences[2] = StartSequence(StageSequencesB[READ_INDEX()],parent);
        work->sequences[3] = StartSequence((const void *)0x0894D3B0,parent);
        work->background = StartBackground(StageBackgrounds[READ_INDEX()],parent);
        SetBackgroundParameters(work->background,2,63);
        work->sprite = CreateStageSprite((const void *)0x0850903C,READ_INDEX(),120,80,895,7,paused,paused);
        SetSpriteFlag(work->sprite,1);
        {
            AdvanceChunkEventPhase(event);
        }
        break;
    case 261:
    {
        void *last;
        u32 layer_mask;
        if (READ_TICK() <= 83) {
            register void *sprite_arg asm("r0") = work->sprite;
            register const s16 *scale_table asm("r2") = StageScales;
            register u32 tick_index asm("r1");
            s32 scale;
            asm("" : "+r"(sprite_arg), "+r"(scale_table));
            tick_index = READ_TICK();
            asm("" : : "r"(tick_index));
            scale = scale_table[tick_index];
            TransformSprite(sprite_arg,scale,scale,0);
            work->tick = READ_TICK()+1;
        }
        work->background = PollBackground(work->background);
        if (work->background) break;
        work->sequences[0] = PollSequence(work->sequences[0]);
        if (work->sequences[0]) break;
        work->sequences[1] = PollSequence(work->sequences[1]);
        if (work->sequences[1]) break;
        work->sequences[2] = PollSequence(work->sequences[2]);
        if (work->sequences[2]) break;
        last = PollSequence(work->sequences[3]);
        work->sequences[3] = last;
        if (last) break;
        layer_mask = GetStageLayerMask(1);
        StageDisplayFlags &= ~layer_mask;
        ReleaseSprite(work->sprite);
        work->sprite = last;
        if (work->optional) {
            ReleaseOptional(work->optional,0);
            work->optional = last;
        }
        work->tick = 20;
shared_increment:
        {
            register StageEvent *tail_event asm("r4") = event;
            asm("" : "+r"(tail_event));
            tail_event->state++;
        }
        break;
    }
    case 262:
    {
        u32 next_tick = READ_TICK()-1;
        work->tick = (u16)next_tick;
        if (!(next_tick << 16)) {
            register u32 reset_phase asm("r0") = 2;
            asm("" : "+r"(reset_phase));
            event->state = reset_phase;
        }
        break;
    }
    }
    return 0;
}
typedef char WorkSize[(sizeof(IndexedStageWork)==4156)?1:-1];
typedef char EventSize[(sizeof(StageEvent)==28)?1:-1];
typedef char DimensionsStride[(sizeof(MapDimensions)==4)?1:-1];
__asm__(".global StageDisplayFlags\n.set StageDisplayFlags,0x03000940\n"
        ".global StageBackgrounds\n.set StageBackgrounds,0x083A775C\n"
        ".global StageSequencesA\n.set StageSequencesA,0x083A7770\n"
        ".global StageSequencesB\n.set StageSequencesB,0x083A7784\n"
        ".global StageTileSources\n.set StageTileSources,0x083A7798\n"
        ".global StageTileByteCounts\n.set StageTileByteCounts,0x083A77AC\n"
        ".global StageMapSources\n.set StageMapSources,0x083A77B8\n"
        ".global StageMapDimensions\n.set StageMapDimensions,0x083A77CC\n"
        ".global StageScales\n.set StageScales,0x083A77E0\n");

__asm__(".global RetailCall_08000a98\n.thumb_set RetailCall_08000a98, 0x08000a99\n.global RetailCall_08000adc\n.thumb_set RetailCall_08000adc, 0x08000add\n.global RetailCall_080035a8\n.thumb_set RetailCall_080035a8, 0x080035a9\n.global RetailCall_0800bd7c\n.thumb_set RetailCall_0800bd7c, 0x0800bd7d\n.global RetailCall_0800bdf8\n.thumb_set RetailCall_0800bdf8, 0x0800bdf9\n.global RetailCall_080110f8\n.thumb_set RetailCall_080110f8, 0x080110f9\n.global RetailCall_080112cc\n.thumb_set RetailCall_080112cc, 0x080112cd\n.global RetailCall_08011428\n.thumb_set RetailCall_08011428, 0x08011429\n.global RetailCall_080d3af8\n.thumb_set RetailCall_080d3af8, 0x080d3af9\n.global RetailCall_080d3e9c\n.thumb_set RetailCall_080d3e9c, 0x080d3e9d\n.global RetailCall_080d3f08\n.thumb_set RetailCall_080d3f08, 0x080d3f09\n.global RetailCall_080d3f84\n.thumb_set RetailCall_080d3f84, 0x080d3f85\n.global RetailCall_080d4704\n.thumb_set RetailCall_080d4704, 0x080d4705\n.global RetailCall_080d4774\n.thumb_set RetailCall_080d4774, 0x080d4775\n.global RetailCall_080d4a28\n.thumb_set RetailCall_080d4a28, 0x080d4a29\n.global RetailCall_080d4b64\n.thumb_set RetailCall_080d4b64, 0x080d4b65\n.global RetailCall_080d4d14\n.thumb_set RetailCall_080d4d14, 0x080d4d15\n.global RetailCall_080d5cc0\n.thumb_set RetailCall_080d5cc0, 0x080d5cc1\n.global RetailCall_080d74e0\n.thumb_set RetailCall_080d74e0, 0x080d74e1\n.global RetailCall_0814186c\n.thumb_set RetailCall_0814186c, 0x0814186d\n");
