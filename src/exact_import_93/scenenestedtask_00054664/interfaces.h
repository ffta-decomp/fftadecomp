typedef unsigned char u8; typedef unsigned short u16; typedef unsigned int u32; typedef int s32;
struct Surface { u8 reserved[16]; u32 tiles; u8 *data; };
struct Keys { u16 held, pressed; };
extern u8 *gRoot;
extern struct Surface gSurfaceA,gSurfaceB;
extern struct Keys gKeys;
extern const void *gTextTable[];
extern const u16 gMessageMap[];
extern const u8 gMessageBytes[],gTextureSource[];
extern void NSetupRegion(int,int,int,int);
extern void NSetEffect(void*,int);
extern void NInitializeMenu(void);
extern u8 NGetStage(void*);
extern void NInitializeController(void*,u8,int,int,int,u16);
extern void NSetControllerOption(void*,int);
extern void NSetControllerEnabled(void*,int);
extern int NHasSelectedPoolUnit(void);
extern void NSetControllerMode(void*,int);
extern void NSetControllerText(void*,int);
extern void NInitializeWindow(void*,void*,void*,int,int,int,int,int,int,int,int,int);
extern void NSetWindowOption(void*,int);
extern void NSetRegion(int,int,int,int);
extern u8 NWindowReady(void*);
extern void NFillWindow(void*,int,int,int);
extern void NBindWindow(void*,void*,u16,int);
extern void NDecodeTexture(void*,const void*,void*,int,int,int);
extern void NSetTexturePalette(void*,int);
extern void NPrintTexture(void*,void*,void*,u8,int,int,int);
extern void NRefreshList(void*);
extern void NSetWindowVisible(void*,int);
extern void NProcessSelectedPoolUnits(void);
extern void NOpenListWindow(void*,int,int,int,int,int,int);
extern void NBindList(void*,void*,int,int);
extern u16 NGetListCount(void*);
extern void NSetListText(const void*,void*,u8,int);
extern void NSetWindowCallback(void*,void*,int);
extern void NSetListRange(void*,int,int);
extern void NOpenDetail(void*,u8,void*,void*,int);
extern void NSuspendMessage(void*);
extern void NBeginDetail(void);
extern void NAdvanceChoice(void*,int,int,int,void*,int);
extern void NAdvanceWindow(void*);
extern void NRegisterTask(void*,int,void*);
extern u16 NDetailReady(void);
extern void NCloseMenu(void);
extern void NClearRegion(int,int,int,int);
extern void NResetTasks(void*);
#define AT(o) (gRoot + (o))
#define BYTE(o) (*(u8*)AT(o))
#define HALF(o) (*(u16*)AT(o))
#define WORD(o) (*(u32*)AT(o))
#define POINTER(o) (*(void**)AT(o))
