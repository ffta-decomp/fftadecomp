typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;
typedef signed int s32;
typedef unsigned int u32;
typedef struct SceneRingObject {
    void *object;
    u8 angle;
    u8 opaque05[3];
} SceneRingObject;
extern s32 QuerySceneRingAxisX(u32) asm("RetailCall_08007A60");
extern s32 QuerySceneRingAxisY(u32) asm("RetailCall_08007A4C");
extern void PositionSceneRingObject(void *,s32,s32,u32) asm("RetailCall_080107D4");
void UpdateAuthoredSceneRing(SceneRingObject *,u8) asm("RemainingBand43_0011C644");
void UpdateAuthoredSceneRing(SceneRingObject *objects,u8 radius)
{
    u8 index;
    for (index = 0; index < 8; index++) {
        SceneRingObject *entry = &objects[index];
        u16 x = (s16)((s16)QuerySceneRingAxisX(entry->angle) * radius) >> 8;
        u32 y_phase = (u32)((s16)QuerySceneRingAxisY(entry->angle) * radius) << 16;
        void *object = entry->object;
        u32 x_phase = (u32)x << 16;
        x_phase += (u32)120 << 16;
        PositionSceneRingObject(object,(s32)x_phase >> 16,((s32)y_phase >> 24) + 64,0);
        entry->angle += 2;
    }
}
__asm__(".global RetailCall_08007A60\n.thumb_set RetailCall_08007A60,0x08007A61\n"
        ".global RetailCall_08007A4C\n.thumb_set RetailCall_08007A4C,0x08007A4D\n"
        ".global RetailCall_080107D4\n.thumb_set RetailCall_080107D4,0x080107D5");
