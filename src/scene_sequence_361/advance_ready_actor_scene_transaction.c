typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;
typedef signed int s32;
struct SceneContext {u16 state;u8 unknown02[2];void *record;};
struct ActorTransaction {u16 delay;u8 ready,unknown03;s16 x,y;void *record,*script,*resource,*child,*overlay;};
struct ActorActionOutput {u8 unknown00[52];u16 action;};
struct SceneDisplayShadow {u16 control;};
extern struct SceneDisplayShadow gSceneDisplay;
__asm__(".global gSceneDisplay\n.set gSceneDisplay,0x03000940");
extern u32 ReadRecordCoordinates(void*,s16*,s16*) asm("RetailCall_080DBDC8");
extern u32 SetRecordPreparation(void*,u32) asm("RetailCall_080DE3BC");
extern void *StartReadyActorChild(void*,u8*,u32,u32,u32,u32,u32,void*) asm("RetailCall_080DE4B0");
extern void *StartSceneOverlay(const void*,u32,u32,u32,void*) asm("RetailCall_080DFD8C");
extern u32 StartCoordinateEffect(const void*,u32,u32,s32,s32,u32) asm("RetailCall_080D7220");
extern void *StartSceneResource(const void*,void*) asm("RetailCall_080D4704");
extern void *StartSceneScript(const void*,void*) asm("RetailCall_080D3E9C");
extern u32 ConfigureSceneScript(void*,u32,u32) asm("RetailCall_080D3F84");
extern struct ActorActionOutput *GetActorActionOutput(void*) asm("RetailCall_080DD350");
extern u32 SetActorSequence(void*,u32) asm("RetailCall_080DE10C");
extern u32 SetActorMode(void*,u32) asm("RetailCall_080DBC18");
extern u32 SetActorAction(void*,u32) asm("RetailCall_080DD720");
extern void *PollSceneScript(void*) asm("RetailCall_080D3F08");
extern void *PollSceneResource(void*) asm("RetailCall_080D4774");
extern u32 SceneLayerMask(u32) asm("RetailCall_080035A8");
extern u32 ActorSequenceDone(void*) asm("RetailCall_080DE1F0");
typedef char WorkSize[(sizeof(struct ActorTransaction)==28)?1:-1];
u32 AdvanceAuthoredActorTransaction(void*,struct SceneContext*,struct ActorTransaction*) asm("RemainingBand43_0011C50C");
u32 AdvanceAuthoredActorTransaction(void *owner,struct SceneContext *context,struct ActorTransaction *work)
{
    s32 state=context->state;
    switch(state) {
    case 0:
        work->record=context->record;
        ReadRecordCoordinates(work->record,&work->x,&work->y);
        SetRecordPreparation(work->record,0);
        /* Native state snapshot is zero on this arm; it supplies the three
         * outgoing zero words without inventing an independent live value. */
        work->child=StartReadyActorChild(work->record,&work->ready,2,3,state,state,state,owner);
        work->overlay=StartSceneOverlay((void*)0x083A6CE4,1,4,0,owner);
        break;
    case 256:
        if(!work->ready) break;
        StartCoordinateEffect((void*)0x088F469C,1,3,work->x,work->y,0);
        work->resource=StartSceneResource((void*)0x0894C7A4,owner);
        work->script=StartSceneScript((void*)0x0894D69C,owner);
        ConfigureSceneScript(work->script,8,255);
        work->delay=26;
        context->state++;
        break;
    case 257:
        work->delay--;
        if(work->delay) break;
        GetActorActionOutput(work->record)->action=116;
        SetActorSequence(work->record,36);
        SetActorMode(work->record,0);
        SetActorAction(work->record,4);
        context->state++;
        break;
    case 258:
        work->script=PollSceneScript(work->script);
        if(work->script) break;
        work->resource=PollSceneResource(work->resource);
        if(work->resource) break;
        {
            u32 mask=SceneLayerMask(3);
            u32 control=gSceneDisplay.control;
            control&=~mask;
            gSceneDisplay.control=control;
        }
        if((u8)ActorSequenceDone(work->record)) context->state=2;
        break;
    }
    return 0;
}

__asm__(".global RetailCall_080035A8\n.thumb_set RetailCall_080035A8, 0x80035a9");

__asm__(".global RetailCall_080D3E9C\n.thumb_set RetailCall_080D3E9C, 0x80d3e9d");

__asm__(".global RetailCall_080D3F08\n.thumb_set RetailCall_080D3F08, 0x80d3f09");

__asm__(".global RetailCall_080D3F84\n.thumb_set RetailCall_080D3F84, 0x80d3f85");

__asm__(".global RetailCall_080D4704\n.thumb_set RetailCall_080D4704, 0x80d4705");

__asm__(".global RetailCall_080D4774\n.thumb_set RetailCall_080D4774, 0x80d4775");

__asm__(".global RetailCall_080D7220\n.thumb_set RetailCall_080D7220, 0x80d7221");

__asm__(".global RetailCall_080DBC18\n.thumb_set RetailCall_080DBC18, 0x80dbc19");

__asm__(".global RetailCall_080DBDC8\n.thumb_set RetailCall_080DBDC8, 0x80dbdc9");

__asm__(".global RetailCall_080DD350\n.thumb_set RetailCall_080DD350, 0x80dd351");

__asm__(".global RetailCall_080DD720\n.thumb_set RetailCall_080DD720, 0x80dd721");

__asm__(".global RetailCall_080DE10C\n.thumb_set RetailCall_080DE10C, 0x80de10d");

__asm__(".global RetailCall_080DE1F0\n.thumb_set RetailCall_080DE1F0, 0x80de1f1");

__asm__(".global RetailCall_080DE3BC\n.thumb_set RetailCall_080DE3BC, 0x80de3bd");

__asm__(".global RetailCall_080DE4B0\n.thumb_set RetailCall_080DE4B0, 0x80de4b1");

__asm__(".global RetailCall_080DFD8C\n.thumb_set RetailCall_080DFD8C, 0x80dfd8d");
