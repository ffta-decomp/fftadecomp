typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
struct SceneRequest { u8 phase, active, pending, selection; u16 command; u8 step; };
extern struct SceneRequest gSceneRequest;
extern void *GetSceneTask(u32 slot);
extern void RequestSceneTaskClose(void *task);
u32 RouteSelectedSceneCommand(u8 command)
{
 switch(command) {
 case 4:
  gSceneRequest.command=command;
  gSceneRequest.step=0;
  return 16;
 case 13: case 14: case 15:
  gSceneRequest.command=command;
  gSceneRequest.selection=command+249;
  gSceneRequest.step=0;
  return 17;
 case 10:
  gSceneRequest.command=command;
  RequestSceneTaskClose(GetSceneTask(1));
  gSceneRequest.step=0;
  return 18;
 case 1:
  gSceneRequest.command=command;
  gSceneRequest.selection=2;
  gSceneRequest.step=0;
  return 19;
 case 3:
  gSceneRequest.command=command;
  gSceneRequest.selection=3;
  gSceneRequest.step=0;
  return 20;
 case 2:
  gSceneRequest.command=command;
  gSceneRequest.step=0;
  return 21;
 default:
  gSceneRequest.pending=0;
  gSceneRequest.active=0;
  return 1;
 }
}
asm(".global gSceneRequest\n.set gSceneRequest,0x0200f390\n.global GetSceneTask\n.thumb_set GetSceneTask,0x0802d72d\n.global RequestSceneTaskClose\n.thumb_set RequestSceneTaskClose,0x0802d705");
