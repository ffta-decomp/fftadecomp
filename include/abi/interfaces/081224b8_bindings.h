typedef unsigned char u8;typedef unsigned short u16;typedef unsigned int u32;
struct SceneContext {u8 unknown00[6];u8 mode;};
struct ModeState {u8 unknown00[150];u16 mode;};
extern u8 GetGameFlag(u16);
extern void InitializeSceneModeThree(void);
extern void PrepareSceneModeNine(void);
extern int IsSceneModeNineReady(void);
extern void RunSceneModeNine(struct SceneContext *);
extern void RunSceneModeTen(struct SceneContext *);
extern void RunSceneModeEleven(struct SceneContext *);
extern void RunSceneModeFourteen(struct SceneContext *);
#define SceneModeState ((const struct ModeState*)0x0200f390)
