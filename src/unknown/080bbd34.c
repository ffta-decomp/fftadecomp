typedef unsigned char u8;
typedef signed char s8;
typedef signed short s16;
typedef unsigned int u32;
typedef signed int s32;
struct Task;
struct CoordinateCadence {
    s16 x;
    s16 height;
    s16 y;
    /* Physical ordinary-RAM byte; actual signed-value/read boundaries
     * are retained at the use sites, not by global volatile storage. */
    s8 ticks;
    u8 reserved7;
};
/* Raw caller words preserve signed coordinates/phase before the existing
 * implementation consumes LOW16 coordinates and LOW8 parameters. */
extern void EmitCoordinateCadenceEffect(struct Task *,s32,s32,s32,u32,s32);
extern u32 PollTaskStateByte(const struct Task *);
asm(".global EmitCoordinateCadenceEffect\n.thumb_set EmitCoordinateCadenceEffect,0x080e2c01\n"
    ".global PollTaskStateByte\n.thumb_set PollTaskStateByte,0x080d3879\n");
u32 UpdateCoordinateEffectCadence(struct CoordinateCadence *rows,s32 count,
                                   struct Task *owner)
    __asm__("CoreFrontier_000BBD34");
u32 UpdateCoordinateEffectCadence(struct CoordinateCadence *rows,s32 count,
                                   struct Task *owner)
{
    u32 pending=0;
    u32 four;
    s32 remaining;
    s32 phase;
    register s32 active_ticks __asm__("r0");
    /* Original null-owner branch returns the already materialized zero,
     * bypassing the non-null path's pending-value move. */
    if(owner==0)
        return 0;
    /* Original compares the initialized zero pending word to signed count. */
    if((s32)pending<count) {
        four=4;
        remaining=count;
        do {
            active_ticks=rows->ticks;
            /* Original first load defines a full signed R0 before testing. */
            asm("" : "+r" (active_ticks));
            if(active_ticks!=0) {
                pending=1;
                /* Preserve the actual initialized row address across the
                 * second distinct read; no memory clobber or new value. */
                asm("" : "+r" (rows));
                phase=rows->ticks;
                switch(phase) {
                case 16:
                    EmitCoordinateCadenceEffect(owner,rows->x,rows->height,rows->y,four,four);
                    break;
                case 12:
                    EmitCoordinateCadenceEffect(owner,rows->x,rows->height,rows->y,5,four);
                    break;
                case 8:
                    EmitCoordinateCadenceEffect(owner,rows->x,rows->height,rows->y,6,four);
                    break;
                case 4:
                    EmitCoordinateCadenceEffect(owner,rows->x,rows->height,rows->y,7,phase);
                    break;
                }
                /* Original decrements a freshly read byte with one store;
                 * the ordinary RAM write has no extra volatile RMW read. */
                rows->ticks = rows->ticks - 1;
            }
            remaining--;
            rows++;
        } while(remaining!=0);
    }
    if((u8)PollTaskStateByte(owner)==0)
        pending=1;
    return pending;
}
