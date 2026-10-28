/* Method-local interface declarations from the frozen build. */
typedef unsigned char u8;typedef unsigned short u16;typedef unsigned int u32;
struct Scene {u8 unknown0,active,request_flags,request_index;u16 scene_id;u8 substate,mode,message_state,gap9[4],config;u8 gap14[134];u16 flags;};
struct GameContext {const u8 *definition;u8 gap4[168];u16 record_index;};
struct Definition {u16 text;u8 unknown2[26];};
extern struct Scene gScene;extern struct GameContext gGame;
extern const struct Definition gDefinitions[];
extern const u8 *const gTexts[];
extern void InitializeSceneRequests(u32),InitializeSceneObjects(u32),ReleaseSceneObjects(void),ReleaseSceneRequests(void),SetSceneRequest(u8);
extern u8 ReadSceneRequest(void);
extern u32 HandleSceneRequest(u8),AdvanceModal(void),AdvanceScene17(void),AdvanceScene18(void),AdvanceScene19(void),AdvanceScene20(void),AdvanceScene21(void);
__asm__(".global InitializeSceneRequests\n.thumb_set InitializeSceneRequests,0x8025325");
__asm__(".global InitializeSceneObjects\n.thumb_set InitializeSceneObjects,0x802b63d");
__asm__(".global ReleaseSceneObjects\n.thumb_set ReleaseSceneObjects,0x802b6a1");
__asm__(".global ReleaseSceneRequests\n.thumb_set ReleaseSceneRequests,0x8025375");
__asm__(".global SetSceneRequest\n.thumb_set SetSceneRequest,0x8025449");
__asm__(".global ReadSceneRequest\n.thumb_set ReadSceneRequest,0x80254a1");
__asm__(".global HandleSceneRequest\n.thumb_set HandleSceneRequest,0x80233a1");
__asm__(".global AdvanceModal\n.thumb_set AdvanceModal,0x8023489");
__asm__(".global AdvanceScene17\n.thumb_set AdvanceScene17,0x8023561");
__asm__(".global AdvanceScene18\n.thumb_set AdvanceScene18,0x8023989");
__asm__(".global AdvanceScene19\n.thumb_set AdvanceScene19,0x8023a41");
__asm__(".global AdvanceScene20\n.thumb_set AdvanceScene20,0x8023aa1");
__asm__(".global AdvanceScene21\n.thumb_set AdvanceScene21,0x8023af5");
__asm__(".global gScene\n.set gScene,0x200f390");
__asm__(".global gGame\n.set gGame,0x20020d0");
__asm__(".global gDefinitions\n.set gDefinitions,0x855187c");
__asm__(".global gTexts\n.set gTexts,0x85567f0");

void AdvanceSceneRequestOwner(void *unused,u8 *state)
{
    switch (*state) {
    case 0:
        InitializeSceneRequests(0x1600);
        InitializeSceneObjects(0x2E00);
        *state=1;
        break;
    case 255:
        ReleaseSceneObjects();
        ReleaseSceneRequests();
        break;
    case 1:
        if (gScene.request_flags) {
            gScene.active=1;
            if (gScene.request_flags==2) {
                gScene.request_flags=1;
                SetSceneRequest(gScene.request_index);
                if (gScene.flags&32) {
                    if (gScene.flags&64) {
                        const struct Definition *definition=&gDefinitions[gGame.record_index];
                        gGame.definition=gTexts[definition->text];
                        gScene.message_state=46;
                    } else {
                        gGame.definition=0;
                        gScene.message_state=45;
                    }
                }
                gScene.config=8;
                switch (gScene.scene_id) {
                case 13:case 14:case 15:
                    gScene.mode=1;
                    gScene.substate=2;
                    *state=17;
                    break;
                case 20:case 21:case 22:
                    gScene.mode=8;
                    gScene.substate=2;
                    *state=17;
                    break;
                }
            } else *state=HandleSceneRequest(ReadSceneRequest());
        }
        break;
    case 16:*state=AdvanceModal();break;
    case 17:*state=AdvanceScene17();break;
    case 18:*state=AdvanceScene18();break;
    case 19:*state=AdvanceScene19();break;
    case 20:*state=AdvanceScene20();break;
    case 21:*state=AdvanceScene21();break;
    }
}
