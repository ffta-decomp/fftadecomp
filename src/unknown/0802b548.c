typedef unsigned int u32;
typedef struct { unsigned char before[0x797]; unsigned char status; } PanelChild;
u32 GetPanelChildStatus(PanelChild *child) asm("SceneTaskDependency_0002B548");
u32 GetPanelChildStatus(PanelChild *child) { return child->status; }
