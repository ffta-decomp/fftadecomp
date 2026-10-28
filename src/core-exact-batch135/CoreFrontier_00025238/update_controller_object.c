typedef unsigned char u8; typedef unsigned short u16; typedef short s16; typedef unsigned int u32;
struct State { void *object; u8 mode,a,b,index; u32 unused; u16 x,pad14,z; };
typedef void (*ObjectCall)(void *,int); typedef void (*ResourceCall)(void *,const void *);
extern const s16 ObjectVerticalOffsets[];
extern void *CreateObject(void) __asm__("RetailCall_0808f79c");
extern u32 Height(u32,u32) __asm__("RetailCall_0801cc18");
extern void Project(int,int,int,s16*,s16*,s16*) __asm__("RetailCall_0801c918");
extern void Transform(int,int,s16*,s16*) __asm__("RetailCall_0801c960");
extern void Draw(const void*,int,int,int,int,int) __asm__("RetailCall_08001dac");
extern void Position(void*,int,int,int) __asm__("RetailCall_0808efcc");
void UpdateBattleControllerObject(struct State *state) __asm__("CoreFrontier_00025238");
void UpdateBattleControllerObject(struct State *state)
{
    u16 x,z; u32 height; u8 rawHeight; int worldX,worldZ; s16 sx,sy,sz;
    if (!state->object) {
        state->object=CreateObject();
        (*(ResourceCall *)0x08394038)(state->object,(const void*)0x0839155c);
        (*(ObjectCall *)0x08394040)(state->object,-124);
        (*(ObjectCall *)0x08394054)(state->object,1);
    }
    x=(state->x<<5)+16;
    z=(state->z<<5)+16;
    rawHeight=Height((u8)state->x,(u8)state->z);
    worldX=(s16)x;
    height=(u8)rawHeight<<4;
    worldZ=(s16)z;
    Project(worldX,height,worldZ,&sx,&sy,&sz);
    Transform(sx,sy,&sx,&sy);
    Draw((const void*)0x08391554,sx-5,sy-ObjectVerticalOffsets[state->index>>1],0,0,0);
    if(state->object) Position(state->object,worldX,height,worldZ);
}
__asm__(".global RetailCall_0808f79c\n.thumb_set RetailCall_0808f79c, 0x808f79d");
__asm__(".global RetailCall_0801cc18\n.thumb_set RetailCall_0801cc18, 0x801cc19");
__asm__(".global RetailCall_0801c918\n.thumb_set RetailCall_0801c918, 0x801c919");
__asm__(".global RetailCall_0801c960\n.thumb_set RetailCall_0801c960, 0x801c961");
__asm__(".global RetailCall_08001dac\n.thumb_set RetailCall_08001dac, 0x8001dad");
__asm__(".global RetailCall_0808efcc\n.thumb_set RetailCall_0808efcc, 0x808efcd");

/* Original R2 Thumb indirect-call trampoline; emits no instructions. */
__asm__(".global _call_via_r2\n.thumb_set _call_via_r2,0x0814224d");

/* Original signed-halfword ROM table, with no invented capacity. */
__asm__(".global ObjectVerticalOffsets\n.set ObjectVerticalOffsets,0x0839141c");
