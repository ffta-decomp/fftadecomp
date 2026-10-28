typedef unsigned char u8;
struct SceneUnitContext {
    u8 unknown_000[0x8d4];
    void *unit_record_group;
};
extern struct SceneUnitContext *gSceneUnitContext;
asm(".global gSceneUnitContext\n.set gSceneUnitContext,0x020159cc");
void *PublishSceneUnitRecordGroup(void *group) asm("Remaining38_00121E08");
void *PublishSceneUnitRecordGroup(void *group)
{
    gSceneUnitContext->unit_record_group=group;
    return group;
}
