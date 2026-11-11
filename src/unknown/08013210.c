typedef unsigned char u8;typedef unsigned short u16;typedef unsigned int u32;
struct ActiveTextState {
    u8 unknown0[11];u8 dirty;u16 control;
    u8 unknown14[29];u8 flags;const void *reference;u32 timing;
    u8 unknown52[6];u16 status;
    u8 unknown60[0x754-60];u32 resolved;
};
extern struct ActiveTextState *gActiveTextState;
extern u32 ResolveDialogRecordResource(const void*) asm("RetailCall_080CB928");
void SetDialogRecordAndSide(const void*,u8,u32) asm("CoreDependency29_00013210");
void SetDialogRecordAndSide(const void *record,u8 side,u32 parameter)
{
    {
        struct ActiveTextState *initial_context=gActiveTextState;
        initial_context->status|=128;
        initial_context->reference=record;
        initial_context->timing=parameter;
    }
    if(record) {
        u32 result=ResolveDialogRecordResource(record);
        gActiveTextState->resolved=result;
    }
    if(side) {
        struct ActiveTextState *mode_context;
        gActiveTextState->flags&=254;
        gActiveTextState->flags|=2;
        mode_context=gActiveTextState;
        mode_context->control|=16;
        mode_context->dirty|=2;
    } else {
        struct ActiveTextState *mode_context;
        gActiveTextState->flags&=253;
        gActiveTextState->flags|=1;
        mode_context=gActiveTextState;
        mode_context->control&=0xFFEF;
        mode_context->dirty&=253;
    }
    if(!record) gActiveTextState->flags=0;
}
__asm__(".global RetailCall_080CB928\n.thumb_set RetailCall_080CB928,0x080CB929");
__asm__(".global gActiveTextState\n.set gActiveTextState,0x0200918C");
