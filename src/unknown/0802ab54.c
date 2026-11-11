typedef unsigned char u8;
struct PanelOperation { u8 unknown00[128]; u8 state; };
u8 ReadPanelOperationState(const struct PanelOperation *operation)
    asm("SceneTaskDependency_0002AB54");
u8 ReadPanelOperationState(const struct PanelOperation *operation)
{
    return operation->state;
}
