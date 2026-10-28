typedef unsigned char u8;
typedef unsigned int u32;
extern void SelectAudioCue(u32 cue) __asm__("0x08141540");
extern u32 CheckGameFlag(u32 flag) __asm__("0x080c9540");
#define SCENE_HOLDER ((u8 **)0x0200f428)
struct SceneRow { u8 prefix[17]; u8 choice; u8 suffix[14]; };
typedef char SceneRowSize[(sizeof(struct SceneRow) == 32) ? 1 : -1];

void ContinueGameMenuChoice(u8 *caller_state)
{
    u8 *scene;
    u8 choice;
    SelectAudioCue(100);
    if ((u8)CheckGameFlag(794) == 0) {
        scene = *SCENE_HOLDER;
        choice = ((struct SceneRow *)scene)[167].choice;
        switch (choice) {
        case 0:
            caller_state[0] = 20;
            scene[0x446c] = 22;
            break;
        case 1:
            caller_state[0] = 20;
            scene[0x446c] = 23;
            break;
        case 2:
            caller_state[0] = 20;
            scene[0x446c] = 40;
            break;
        default:
            break;
        }
    } else {
        scene = *SCENE_HOLDER;
        choice = ((struct SceneRow *)scene)[167].choice;
        switch (choice) {
        case 0:
            caller_state[0] = 20;
            scene[0x446c] = 22;
            break;
        case 1:
            caller_state[0] = 20;
            scene[0x446c] = 23;
            break;
        case 2:
            caller_state[0] = 20;
            scene[0x446c] = 24;
            break;
        case 3:
            caller_state[0] = 20;
            scene[0x446c] = 40;
            break;
        default:
            break;
        }
    }
}
