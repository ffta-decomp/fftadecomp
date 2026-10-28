#ifndef LOCATION_COMMIT_H
#define LOCATION_COMMIT_H
typedef unsigned char u8;
typedef unsigned int u32;
struct LocationSelection { u8 unknown0[170]; u8 one_based_record; };
struct SceneRootView { u8 unknown0[4]; struct LocationSelection *selection; };
union LocationFlags { u8 raw; struct { u8 location:5; u8 other:3; } __attribute__((packed)) bits; } __attribute__((packed));
/* A shifted view of a six-byte record; only its packed location byte is used. */
struct ShiftedLocationView { u8 unknown0[0x2e36]; union LocationFlags flags; };
struct PersistentLocationView { u8 unknown0[0x2e54]; union LocationFlags current; };
typedef char flags_size[sizeof(union LocationFlags)==1?1:-1];
typedef char flags_offset[(unsigned long)&((struct ShiftedLocationView*)0)->flags==0x2e36?1:-1];
typedef char current_offset[(unsigned long)&((struct PersistentLocationView*)0)->current==0x2e54?1:-1];
extern struct SceneRootView *gLocationScene;
extern u8 gLocationSave[];
__asm__(".global gLocationScene\n.set gLocationScene,0x03002810\n.global gLocationSave\n.set gLocationSave,0x02000000");
#endif
