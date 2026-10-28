typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;
typedef signed int s32;
struct ActorSequenceContext {u16 state;u8 unknown02[2];void **actors;};
struct ActorActionOutput {u8 unknown00[52];u16 action;};
struct ThreeActorSequence {
    u16 timer;u8 completed;u8 unknown03[5];
    void **source;void *actors[3];void *resources[3];void *prelude,*overlay;
};
extern const u8 gPrelude[],gStartFrames[3],gEndFrames[3],gOverlay[];
extern const u16 gActorParameters[3];
extern const u8 gActorEffect[];
extern void *StartScenePrelude(const void*,u32,void*) asm("RetailCall_080D7A70");
extern void RestoreSceneStage(void) asm("RetailCall_080D35D8");
extern void *PollScenePrelude(void*) asm("RetailCall_080D7ABC");
extern void *RetainActorRecord(void*) asm("RetailCall_080DD34C");
extern struct ActorActionOutput *GetActorActionOutput(void*) asm("RetailCall_080DD350");
extern void ReadActorCoordinates(void*,s16*,s16*) asm("RetailCall_080DBDC8");
extern void *CreateSceneObject(const void*,u32,s16,s16,u32,u32,u32,u32) asm("RetailCall_080D5CC0");
extern void EnableDefinitionResourceFlagEight(void*) asm("RetailCall_08011198");
extern void *StartSceneOverlay(const void*,u32,u32,u32,void*) asm("RetailCall_080DFD8C");
extern u32 PollAndReleaseDefinitionWorkset(void**,u16) asm("RetailCall_080D5F24");
extern void RestoreActorMotionPresentation(void*) asm("RetailCall_080DE390");
extern void *CopyBytes(void*,const void*,u32) asm("RetailCall_081443FC");
typedef char WorkSize[(sizeof(struct ThreeActorSequence)==44)?1:-1];
u32 AdvanceDefinition402ThreeActorSequence(void*,struct ActorSequenceContext*,struct ThreeActorSequence*) asm("OriginalSceneDefinitionQuestion_0011E618");
u32 AdvanceDefinition402ThreeActorSequence(void *owner,struct ActorSequenceContext *context,struct ThreeActorSequence *work)
{
    s32 state=context->state;
    switch(state) {
    case 0: {
        u8 index;
        work->source=context->actors;
        work->prelude=StartScenePrelude(gPrelude,2,owner);
        index=0;
        do {
            work->actors[index]=RetainActorRecord(work->source[index]);
        } while(++index<=2);
        break;
    }
    case 1:
        RestoreSceneStage();
        break;
    case 256:
        work->prelude=PollScenePrelude(work->prelude);
        if(work->prelude) break;
        context->state++;
        break;
    case 257: {
        u8 start_frames[3];
        u8 end_frames[3];
        u16 parameters[3];
        u8 index;
        CopyBytes(start_frames,gStartFrames,3);
        CopyBytes(end_frames,gEndFrames,3);
        CopyBytes(parameters,gActorParameters,6);
        index=0;
        do {
            if(work->timer==start_frames[index]) {
                s16 x,y;
                u32 flags;
                void *actor=work->actors[index];
                register s16 *x_out asm("r4")=&x;
                register s16 *y_out asm("r5")=&y;
                /* Native defines these two stack addresses in the selected
                 * actor branch, then consumes both after the coordinate call.
                 * The initialized read/write addresses depend on this actual
                 * actor evaluation; no value is invented by the annotation. */
                asm("" : "+r"(x_out), "+r"(y_out) : "r"(actor));
                ReadActorCoordinates(actor,x_out,y_out);
                work->resources[index]=CreateSceneObject(gActorEffect,0,*x_out,*y_out,945,6,0,0);
                EnableDefinitionResourceFlagEight(work->resources[index]);
                flags=(index&1)?16:8;
                flags|=4;
                work->overlay=StartSceneOverlay(gOverlay,1,flags,0,owner);
            }
            if(work->timer==end_frames[index]) {
                struct ActorActionOutput *output=GetActorActionOutput(work->actors[index]);
                output->action=parameters[index];
                RestoreActorMotionPresentation(work->actors[index]);
                work->completed++;
            }
        } while(++index<=2);
        work->timer++;
        if(work->completed>2) context->state++;
        break;
    }
    case 258:
        if((u8)PollAndReleaseDefinitionWorkset(work->resources,3)) context->state=2;
        break;
    }
    return 0;
}
__asm__(".global RetailCall_08011198\n.thumb_set RetailCall_08011198,0x08011199");
__asm__(".global RetailCall_080D35D8\n.thumb_set RetailCall_080D35D8,0x080d35d9");
__asm__(".global RetailCall_080D5CC0\n.thumb_set RetailCall_080D5CC0,0x080d5cc1");
__asm__(".global RetailCall_080D5F24\n.thumb_set RetailCall_080D5F24,0x080d5f25");
__asm__(".global RetailCall_080D7A70\n.thumb_set RetailCall_080D7A70,0x080d7a71");
__asm__(".global RetailCall_080D7ABC\n.thumb_set RetailCall_080D7ABC,0x080d7abd");
__asm__(".global RetailCall_080DBDC8\n.thumb_set RetailCall_080DBDC8,0x080dbdc9");
__asm__(".global RetailCall_080DD34C\n.thumb_set RetailCall_080DD34C,0x080dd34d");
__asm__(".global RetailCall_080DD350\n.thumb_set RetailCall_080DD350,0x080dd351");
__asm__(".global RetailCall_080DE390\n.thumb_set RetailCall_080DE390,0x080de391");
__asm__(".global RetailCall_080DFD8C\n.thumb_set RetailCall_080DFD8C,0x080dfd8d");
__asm__(".global RetailCall_081443FC\n.thumb_set RetailCall_081443FC,0x081443fd");
__asm__(".global gPrelude\n.set gPrelude,0x083a734c");
__asm__(".global gStartFrames\n.set gStartFrames,0x08149fc4");
__asm__(".global gEndFrames\n.set gEndFrames,0x08149fc7");
__asm__(".global gActorParameters\n.set gActorParameters,0x08149fca");
__asm__(".global gActorEffect\n.set gActorEffect,0x084faaa4");
__asm__(".global gOverlay\n.set gOverlay,0x083a7364");
