typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef unsigned int u32;
struct Actor;
struct OccupancyOwner { u8 unknown_00[16]; void *actors; };
struct Actor { u8 unknown_00[60]; void *grid; u8 unknown_40[64]; struct OccupancyOwner *occupancy; };
struct RouteCell { s8 x, y; u8 unknown_02[2]; };
struct OccupancyQuery { u32 unknown_00; s8 x, y; u16 unknown_06; struct Actor *occupant; };
extern int ReadGridCell(void *, int, int) __asm__("0x08149384");
extern int TraceRoute(void *, struct RouteCell *, int, int) __asm__("0x081492d0");
extern int CheckBattleCoordinateGate(struct Actor *, int, int, int) __asm__("0x08097504");
extern int FindCoordinateOccupant(void *, struct OccupancyQuery *) __asm__("CoordinateOccupantCallback");
__asm__(".thumb_set CoordinateOccupantCallback, 0x0809abb1");
extern void VisitActors(void *, int (*)(void *, struct OccupancyQuery *), struct OccupancyQuery *) __asm__("0x080c7cc0");
int SelectUsableRoutePrefix(struct Actor *actor, u8 initial_x, u8 initial_y, u8 limit, struct RouteCell *route) __asm__("CoreFrontier_000989AC");
int SelectUsableRoutePrefix(struct Actor *actor, u8 initial_x, u8 initial_y, u8 limit, struct RouteCell *route)
{
    struct OccupancyQuery query;
    register struct OccupancyOwner **initial_owner_field __asm__("r4");
    register struct OccupancyOwner **owner __asm__("r10");
    register struct Actor *initial_occupant __asm__("r0");
    register struct RouteCell *cursor __asm__("r6");
    int ordinal;
    if (!ReadGridCell(actor->grid, initial_x, initial_y))
        return -1;
    initial_owner_field = &actor->occupancy;
    {
        struct OccupancyOwner *initial_owner = *initial_owner_field;
        query.occupant = 0;
        query.x = initial_x;
        query.y = initial_y;
        VisitActors(initial_owner->actors, FindCoordinateOccupant, &query);
    }
    /* Read the real callback output and define the scan owner at this boundary. */
    __asm__("ldr %0, %3\n\tmov %1, %2"
        : "=&l" (initial_occupant), "=&r" (owner)
        : "r" (initial_owner_field), "m" (query.occupant));
    if (initial_occupant)
        return -1;
    {
        int count = TraceRoute(actor->grid, route, initial_x, initial_y);
        if (count <= 0)
            return -1;
        ordinal = count - 1;
    }
    if (ordinal >= 0) {
        register struct OccupancyQuery *scan_query __asm__("r9") = &query;
        __asm__("" : "+r" (scan_query));
        {
            u32 byte_offset = ordinal * sizeof(struct RouteCell);
            /* Real cursor begins at the final address ADD, after scalar arithmetic. */
            __asm__("add %0, %1, %2"
                : "=&l" (cursor) : "l" (byte_offset), "l" (route) : "cc");
        }
        while (ordinal >= 0) {
        register int x __asm__("r5") = cursor->x;
        register int y __asm__("r4") = cursor->y;
        /* Actual signed coordinates survive the gate call for byte publication. */
        __asm__("" : "+r" (x), "+r" (y));
        if (CheckBattleCoordinateGate(actor, x, y, limit)) {
            register struct OccupancyOwner *current_owner __asm__("r0");
            register struct OccupancyOwner **owner_address __asm__("r1") = owner;
            int available;
            /* Real owner-word producer; C keeps the query writes and list-head load. */
            __asm__("ldr %0, [%1]"
                : "=&l" (current_owner)
                : "l" (owner_address), "m" (*owner_address));
            query.occupant = 0;
            scan_query->x = x;
            scan_query->y = y;
            VisitActors(current_owner->actors, FindCoordinateOccupant, &query);
            {
            struct Actor *occupant = query.occupant;
            available = 1;
            if (occupant != 0 && occupant != actor)
                available = 0;
            }
            if (available)
                break;
        }
        --cursor;
        --ordinal;
        }
    }
    return ordinal + 1;
}
