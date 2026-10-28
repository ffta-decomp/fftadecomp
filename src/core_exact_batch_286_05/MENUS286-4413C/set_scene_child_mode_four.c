typedef unsigned char u8;
typedef struct { u8 prefix[142]; unsigned char mode:3; unsigned char remaining:5; } SceneChild;
void CoreRegion_0004413C(void) { SceneChild *child=*(SceneChild**)(*(u8**)0x03002810+4); child->mode=4; }
