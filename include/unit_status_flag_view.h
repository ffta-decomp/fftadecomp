#ifndef UNIT_STATUS_FLAG_VIEW_H
#define UNIT_STATUS_FLAG_VIEW_H

typedef unsigned char u8;
typedef unsigned short u16;

/* Only the observed halfword at +0x28 is modeled here. Its bit meanings are
 * still unknown; callers should keep using the offset-oriented predicates. */
typedef struct UnitStatusFlagView {
    u8 unknown_00[0x28];
    u16 status_flags;
} UnitStatusFlagView;

#endif
