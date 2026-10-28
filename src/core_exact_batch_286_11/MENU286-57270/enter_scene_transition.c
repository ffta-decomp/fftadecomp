typedef unsigned char u8;
typedef unsigned int u32;

extern u8 *SceneStateRoot;
extern void PlaySceneCue(u32 cue);
__asm__(".global SceneStateRoot\n.set SceneStateRoot,0x0200F428\n.global PlaySceneCue\n.thumb_set PlaySceneCue,0x08141541");

void SceneTaskDependency_00057270(u8 *state)
{
    PlaySceneCue(100u);
    state[0] = 220u;
    SceneStateRoot[0x2D38] = 120u;
}
