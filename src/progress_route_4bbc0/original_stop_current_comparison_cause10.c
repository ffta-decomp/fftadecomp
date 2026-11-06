typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;
typedef signed int s32;
struct RouteNode { u8 bytes[20]; };
struct RouteEdge { u8 weight; u8 rest[7]; };
extern const struct RouteNode gRouteNodes[];
extern const struct RouteEdge gRouteEdges[];
extern u8 gRouteProgress;
void ComputeProgressGatedRoutes(u8,u8*,u8*) __asm__("CoreRegion_0004BBC0");
void ComputeProgressGatedRoutes(u8 initial,u8 *distance,u8 *predecessor)
{
    u8 targets[4];
    u8 edge_ids[4];
    u16 costs[32];
    u16 index;
    u16 current;
    u16 stop;
    for(index=0;index<=31;index++) {
        u8 *distance_slot=&distance[index];
        predecessor[index]=255;
        *distance_slot=255;
        costs[index]=0xEFFF;
    }
    current=initial;
    stop=(u16)(s16)current;
    distance[(s16)current]=0;
    costs[(s16)current]=0;
    do {
        s16 node=(s16)current;
        if(distance[node]!=255) {
            const struct RouteNode *record=&gRouteNodes[node];
            targets[0]=record->bytes[3];
            targets[1]=record->bytes[7];
            targets[2]=record->bytes[11];
            targets[3]=record->bytes[15];
            edge_ids[0]=record->bytes[2];
            edge_ids[1]=record->bytes[6];
            edge_ids[2]=record->bytes[10];
            edge_ids[3]=record->bytes[14];
            for(index=0;index<=3;index++) {
                u32 progress=gRouteProgress;
                u8 *edge;
                u8 *target;
                u8 *current_distance;
                u8 target_id;
                s32 next_distance;
                if(!(progress&1) && targets[index]==8)continue;
                {
                    /* Native second gate updates its actual mask carrier,
                     * not the already captured progress word. */
                    register u32 second_mask asm("r0")=2;
                    asm volatile("" : "+r"(second_mask));
                    second_mask &= progress;
                    if(!second_mask && targets[index]==27)continue;
                }
                edge=&edge_ids[index];
                if(*edge==0)continue;
                current_distance=&distance[(s16)current];
                next_distance=(s32)*current_distance+1;
                target=&targets[index];
                target_id=*target;
                if(next_distance>distance[target_id])continue;
                if(next_distance==distance[target_id]) {
                    s32 next_cost=(s32)costs[(s16)current]+gRouteEdges[*edge-1].weight;
                    if(next_cost>=costs[target_id])continue;
                    costs[target_id]=(u16)next_cost;
                }
                {
                    u8 *destination=&distance[*target];
                    *destination=*current_distance+1;
                }
                predecessor[*target]=(u8)current;
                stop=(u16)(s16)current;
            }
        }
        {
            /* The original increments the shifted working word first.
             * Its signed high half controls wrap, its unsigned high half
             * becomes the next circular ordinal. Neither view is truncated
             * before the comparison. */
            u32 latch_current=current;
            u32 next_high;
            /* Original takes a fresh working copy here, separate from the
             * earlier shifted value retained through edge processing. */
            asm volatile("" : "+r"(latch_current));
            next_high=(latch_current<<16)+0x10000;
            current=(u16)(next_high>>16);
            if(((s32)next_high>>16)>31)current=0;
        }
    } while(stop!=current);
}
__asm__(".global gRouteNodes\n.set gRouteNodes,0x08391e40\n.global gRouteEdges\n.set gRouteEdges,0x083931b0\n.global gRouteProgress\n.set gRouteProgress,0x02002e58\n");
