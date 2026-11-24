typedef unsigned char u8;
typedef unsigned int u32;
typedef signed int s32;
extern void GenerateWorldRouteParents(u32,u8*,u8*);
__asm__(".global GenerateWorldRouteParents\n.thumb_set GenerateWorldRouteParents,0x0804bbc1");
u32 BuildWorldPathRoute(u32 start,u32 destination,u8 *parents) __asm__("CoreRegion_0004BB5C");
u32 BuildWorldPathRoute(u32 start,u32 destination,u8 *parents)
{
    u8 route[32];
    /* Original R3 carries the initialized backtrack length, then the countdown. */
    register s32 length __asm__("r3");
    s32 output_index;
    register u32 current __asm__("r2");
    register u8 *route_parents __asm__("r6");
    register u8 *parent_address __asm__("r0");
    if (destination == start)
        return 0;
    /* Original captures its surviving pointer only after the equality exit. */
    route_parents = parents;
    __asm__("" : "+r"(route_parents));
    GenerateWorldRouteParents((u8)start,route,parents);
    if (route[destination] == 255)
        return 0;
    length = 0;
    __asm__("" : "+r"(length));
    current = destination;
    __asm__("" : "+r"(current));
    do {
        route[length] = (u8)current;
        /* Original full address is defined separately from the byte result. */
        parent_address = route_parents+current;
        __asm__("" : "+r"(parent_address));
        current = *parent_address;
        ++length;
    } while (current != start);
    route[length] = (u8)current;
    output_index = 0;
    while (length >= 0) {
        route_parents[output_index] = route[length];
        ++output_index;
        --length;
    }
    return (u8)(output_index-1);
}
