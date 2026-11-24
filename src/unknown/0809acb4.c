typedef unsigned char u8;
typedef unsigned int u32;
struct BattleContinuationOwner {
    u8 unknown_00[84];
    void *first_object;
    void *second_object;
};
typedef void (*ContinuationOperation)(void *object);
struct ContinuationDispatch { ContinuationOperation operation; };
#define CONTINUATION_DISPATCH ((const struct ContinuationDispatch *)0x0839403c)
u32 DispatchBattleContinuationObjects(struct BattleContinuationOwner *owner,
                                      void *unused_visitor_argument)
{
    void *object;
    object = owner->first_object;
    if (object != 0)
        CONTINUATION_DISPATCH->operation(object);
    object = owner->second_object;
    if (object != 0)
        CONTINUATION_DISPATCH->operation(object);
    return 1;
}

asm(".global _call_via_r1\n.thumb_set _call_via_r1,0x08142249\n");
