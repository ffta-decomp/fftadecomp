typedef unsigned char u8;
typedef signed short s16;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct LayerExitRequest {
    u16 state, unknown_02;
    void *record;
    u8 unknown_08[12];
    s16 range_gate;
    u16 range_parameter, layer;
} LayerExitRequest;

typedef struct LayerExitPayload {
    u8 layer, unknown_01[3];
    void *record;
    void *auxiliary;
    void *range;
} LayerExitPayload;

extern void *StartRange(u16 start, u16 count, u16 parameter);
extern void *ReleaseCompletedRange(void *range);
extern void *CreateDefinitionAuxiliary(const void *definition, void *parent);
extern void ConfigureDefinitionAuxiliary(void *auxiliary, u8 first, u8 second);
extern void SetDefinitionRecordFlag(void *record, u8 mode);
extern void *PollDefinitionAuxiliary(void *auxiliary);
/* The selected halfword getter returns a zero-extended full R0 here. */
extern u32 GetDisplayLayerMask(u8 layer);
extern const u8 LayerExitDefinition[];
extern u16 DisplayControlShadow;

u32 AdvanceDefinitionLayerExit(void *context, LayerExitRequest *request,
                               LayerExitPayload *payload)
    __asm__("RemainingBand43_000DB6D0");
u32 AdvanceDefinitionLayerExit(void *context, LayerExitRequest *request,
                               LayerExitPayload *payload)
{
    int state = request->state;
    switch (state) {
    case 0:
        payload->record = request->record;
        payload->layer = (u8)request->layer;
        /* A zero gate leaves the previous range pointer untouched. */
        if (request->range_gate != 0)
            payload->range = StartRange(144, 16, request->range_parameter);
        break;
    case 1:
        break;
    case 256:
        payload->range = ReleaseCompletedRange(payload->range);
        if (payload->range != 0)
            break;
        payload->auxiliary = CreateDefinitionAuxiliary(LayerExitDefinition, context);
        ConfigureDefinitionAuxiliary(payload->auxiliary, 12, 255);
        SetDefinitionRecordFlag(payload->record, 1);
        /* The helper may alias this request; reload rather than using state. */
        request->state++;
        break;
    case 257: {
        u32 layer_mask;
        payload->auxiliary = PollDefinitionAuxiliary(payload->auxiliary);
        if (payload->auxiliary != 0)
            break;
        layer_mask = GetDisplayLayerMask(payload->layer);
        DisplayControlShadow &= ~layer_mask;
        request->state = 2;
        break;
    }
    }
    return 0;
}

__asm__(".global StartRange\n.thumb_set StartRange,0x08147AD1\n"
        ".global ReleaseCompletedRange\n.thumb_set ReleaseCompletedRange,0x081484CD\n"
        ".global CreateDefinitionAuxiliary\n.thumb_set CreateDefinitionAuxiliary,0x080D3E9D\n"
        ".global ConfigureDefinitionAuxiliary\n.thumb_set ConfigureDefinitionAuxiliary,0x080D3F85\n"
        ".global SetDefinitionRecordFlag\n.thumb_set SetDefinitionRecordFlag,0x080DBEB5\n"
        ".global PollDefinitionAuxiliary\n.thumb_set PollDefinitionAuxiliary,0x080D3F09\n"
        ".global GetDisplayLayerMask\n.thumb_set GetDisplayLayerMask,0x080035A9\n"
        ".global LayerExitDefinition\n.set LayerExitDefinition,0x0894DA44\n"
        ".global DisplayControlShadow\n.set DisplayControlShadow,0x03000940\n");
