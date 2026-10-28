typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;
typedef signed int s32;
struct SelectionRequest {u8 unused0,active,status,index;u16 scene_id;u8 substate;};
extern struct SelectionRequest gSelectionRequest;
extern void BeginManagedSelection(u8);
extern s32 ServiceManagedSelection(void);
u32 AdvanceManagedSelectionHandoff(void) __asm__("SceneRegisteredRoot_00023A40");
u32 AdvanceManagedSelectionHandoff(void)
{
    struct SelectionRequest *request=&gSelectionRequest;
    u32 completion;
    __asm__("" : "+r"(request));
    switch(request->substate) {
    case 0:
        BeginManagedSelection(request->index);
        request->substate=1;
        break;
    case 1: {
        register u32 shifted __asm__("r0")=(u32)ServiceManagedSelection()<<16;
        register u32 result __asm__("r1")=shifted>>16;
        __asm__("" : "+r"(shifted) : "r"(result));
        if(shifted!=0) {
            shifted=result<<16;
            __asm__("" : "+r"(shifted));
            if((s32)shifted<0) {
                request->status=128;
                request->substate=2;
            }else {
                completion=0;
                request->status=completion;
                goto finish;
            }
        }
        break;
    }
    case 2:
        completion=request->status;
        if(completion!=0)break;
finish:
        request->active=completion;
        return 1;
    }
    return 19;
}
__asm__(".global gSelectionRequest\n.set gSelectionRequest,0x0200f390\n.global BeginManagedSelection\n.thumb_set BeginManagedSelection,0x0802542d\n.global ServiceManagedSelection\n.thumb_set ServiceManagedSelection,0x08025465");
