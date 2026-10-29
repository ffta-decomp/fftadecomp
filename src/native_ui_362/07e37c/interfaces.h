typedef unsigned char u8;typedef signed char s8;typedef unsigned short u16;typedef signed short s16;typedef unsigned int u32;
struct Unit {u8 prefix[40];u16 flags;};struct Snapshot {u32 words[3];u16 half,tail;};
struct Context {
u8 unknown_0[37];
u8 tick;
u16 row;
u8 buffer_a[512];
u8 buffer_b[512];
u8 unknown_428[2];
u8 saved_preview;
u8 unknown_42b[11];
u16 x;
u16 y;
u8 category_cursor;
u8 saved_cursor;
u8 unknown_43c[4];
void *display;
u8 unknown_444[8];
u8 menu_mode;
u8 preview_enabled;
u8 unknown_44e[2];
u8 progress;
u8 unknown_451[1];
u8 effect_flags;
u8 effect_delay;
void *display_handle;
u16 graphic_offset;
u16 graphic_scale;
u8 selector[261];
u8 category;
u8 next_category;
u8 unknown_563[1059];
u8 selection_index;
u8 unknown_987[5];
struct Snapshot selection_record;
u8 unknown_99c[588];
s16 scroll_source_x;
s16 scroll_source_y;
u8 unknown_bec[4];
s16 source_x;
s16 source_y;
u8 unknown_bf4[1];
u8 pending;
u8 unknown_bf6[6];
struct Snapshot saved_record;
u16 counter;
u8 unknown_c0e[15];
u8 mode;
u8 unknown_c1e[4326];
u8 preview;
u8 unknown_1d05[4];
u8 unit_state;
u8 unknown_1d0a[2];
struct Unit *unit;
};
extern struct Context *gContext;extern struct Unit *gPending;
/* Independently overlapping views of the one shared context frame. */
#define FIELD(c,t,o) (*(t*)((u8*)(c)+(o)))
#define UNIT(c) ((c)->unit)
#define SELECTION_RECORD(c) ((c)->selection_record)
#define SAVED_RECORD(c) ((c)->saved_record)
#define PREVIEW_ENABLED(c) ((c)->preview_enabled)
#define UNIT_STATE(c) ((c)->unit_state)
#define SNAPSHOT_HALF(c) ((c)->saved_record.half)
#define COUNTER(c) ((c)->counter)
#define PENDING(c) ((c)->pending)
#define CATEGORY(c) ((c)->category)
#define NEXT_CATEGORY(c) ((c)->next_category)
#define MODE(c) ((c)->mode)
#define X(c) ((c)->x)
#define Y(c) ((c)->y)
#define SAVED_PREVIEW(c) ((c)->saved_preview)
#define PREVIEW(c) ((c)->preview)
#define CATEGORY_CURSOR(c) ((c)->category_cursor)
#define SAVED_CURSOR(c) ((c)->saved_cursor)
#define EFFECT_FLAGS(c) ((c)->effect_flags)
#define EFFECT_DELAY(c) ((c)->effect_delay)
#define DISPLAY_HANDLE(c) ((c)->display_handle)
#define GRAPHIC_OFFSET(c) ((c)->graphic_offset)
#define GRAPHIC_SCALE(c) ((c)->graphic_scale)
#define SELECTOR(c) ((c)->selector)
#define LABEL_BUFFER(c) ((u8*)(c)+744)
#define SOURCE_X(c) ((c)->source_x)
#define SOURCE_Y(c) ((c)->source_y)
#define SCROLL_SOURCE_X(c) ((c)->scroll_source_x)
#define SCROLL_SOURCE_Y(c) ((c)->scroll_source_y)
#define TICK(c) ((c)->tick)
#define ROW(c) ((c)->row)
#define ROOT_CALLBACK(c) FIELD(c,u8,0x44F)
struct Window {u8 state,pad1[4],flags,pad6[47],timer,pad54[22];};
struct Surface {u8 prefix[12],width,height,gap14[6];void *data;};
struct TaskSystem {u8 prefix[12];u8 *states;};struct Graphics {u8 prefix[4];u8 *resource;};struct Keys {u16 held,pressed,repeat;};
extern struct Window gWindows[];extern struct Surface gSurfaceA,gSurfaceB,gSurfaceD;extern struct TaskSystem gTasks;extern struct Graphics gGraphics;extern struct Keys gKeys;
extern u8 gResume,gWaitWindow,gAlternate,gScrollX,gScrollY,gChoicesAvailable,gScratch[],gTextScratch[];extern const u8 gTiles[],gPalette[],gSelectorData[];
extern void F_SetPreview(u8),F_ResetUnitPreview(void),F_LoadUnitPreview(int,struct Unit*,int,int),F_InitializeGraphic(void*,int,int,int,int,int,int,const void*,const void*,int,int),F_CpuSet(const void*,void*,u32),F_CopyUnitGraphic(void*,struct Unit*),F_SetLabel(void*,u8),F_ResetActor(struct Unit*),F_Register(struct TaskSystem*,u8,void(*)(void*,u8*)),EquipmentCallback(void*,u8*),AbilityAssignmentCallback(void*,u8*),JobChangeCallback(void*,u8*),F_HideSelector(void*),F_SetWindow(int,u16),F_FillText(int,const u16*,u16,u16),F_InitSelector(void*,const void*,int,int,int,int,int,int,int,int,u8),F_SetSound(u16),F_ShowMessage(void*,u16,void*,void*),F_SetActorMode(u8),F_MoveGraphic(void*,u8,u8,u8),F_RemoveGraphic(void*,int),F_SetRow(int,u8),F_Release(void*);
extern u32 F_UnitGraphicSize(struct Unit*),F_LabelId(struct Unit*,u8);extern void *F_GetDisplay(struct Unit*);extern u8 F_Restricted(struct Unit*),F_HasChoices(struct Unit*);extern u16 F_SelectorIndex(void*),F_PollSelector(void*,u16),F_PollMessage(void);extern u16 *F_GetText(int,int,int,int);
__asm__(".global gContext\n.set gContext,0x3002818");
__asm__(".global gPending\n.set gPending,0x30027f4");
__asm__(".global gWindows\n.set gWindows,0x30009e0");
__asm__(".global gSurfaceA\n.set gSurfaceA,0x30008b0");
__asm__(".global gSurfaceB\n.set gSurfaceB,0x3000990");
__asm__(".global gSurfaceD\n.set gSurfaceD,0x3000e80");
__asm__(".global gTasks\n.set gTasks,0x3002730");
__asm__(".global gGraphics\n.set gGraphics,0x3000e30");
__asm__(".global gKeys\n.set gKeys,0x3000000");
__asm__(".global gResume\n.set gResume,0x200f23c");
__asm__(".global gWaitWindow\n.set gWaitWindow,0x200f23d");
__asm__(".global gAlternate\n.set gAlternate,0x200f23e");
__asm__(".global gScrollX\n.set gScrollX,0x200f23f");
__asm__(".global gScrollY\n.set gScrollY,0x200f240");
__asm__(".global gChoicesAvailable\n.set gChoicesAvailable,0x200f241");
__asm__(".global gScratch\n.set gScratch,0x3003860");
__asm__(".global gTextScratch\n.set gTextScratch,0x2003cb0");
__asm__(".global gTiles\n.set gTiles,0x894eaf4");
__asm__(".global gPalette\n.set gPalette,0x894eb80");
__asm__(".global gSelectorData\n.set gSelectorData,0x8393b7c");
__asm__(".global F_SetPreview\n.thumb_set F_SetPreview,0x8079691");
__asm__(".global F_ResetUnitPreview\n.thumb_set F_ResetUnitPreview,0x80753c9");
__asm__(".global F_LoadUnitPreview\n.thumb_set F_LoadUnitPreview,0x8075621");
__asm__(".global F_InitializeGraphic\n.thumb_set F_InitializeGraphic,0x804c525");
__asm__(".global F_CpuSet\n.thumb_set F_CpuSet,0x814186d");
__asm__(".global F_CopyUnitGraphic\n.thumb_set F_CopyUnitGraphic,0x80cb869");
__asm__(".global F_SetLabel\n.thumb_set F_SetLabel,0x80cb8d5");
__asm__(".global F_ResetActor\n.thumb_set F_ResetActor,0x80748ad");
__asm__(".global F_Register\n.thumb_set F_Register,0x8006add");
__asm__(".global EquipmentCallback\n.thumb_set EquipmentCallback,0x80775a9");
__asm__(".global AbilityAssignmentCallback\n.thumb_set AbilityAssignmentCallback,0x8078819");
__asm__(".global JobChangeCallback\n.thumb_set JobChangeCallback,0x8085aa9");
__asm__(".global F_HideSelector\n.thumb_set F_HideSelector,0x8089cad");
__asm__(".global F_SetWindow\n.thumb_set F_SetWindow,0x808a605");
__asm__(".global F_FillText\n.thumb_set F_FillText,0x808b891");
__asm__(".global F_InitSelector\n.thumb_set F_InitSelector,0x8088df1");
__asm__(".global F_SetSound\n.thumb_set F_SetSound,0x8141541");
__asm__(".global F_ShowMessage\n.thumb_set F_ShowMessage,0x8019a8d");
__asm__(".global F_SetActorMode\n.thumb_set F_SetActorMode,0x8076421");
__asm__(".global F_MoveGraphic\n.thumb_set F_MoveGraphic,0x804c789");
__asm__(".global F_RemoveGraphic\n.thumb_set F_RemoveGraphic,0x804c7a1");
__asm__(".global F_SetRow\n.thumb_set F_SetRow,0x8087555");
__asm__(".global F_Release\n.thumb_set F_Release,0x8021ad1");
__asm__(".global F_UnitGraphicSize\n.thumb_set F_UnitGraphicSize,0x80cb809");
__asm__(".global F_LabelId\n.thumb_set F_LabelId,0x80cb7c1");
__asm__(".global F_GetDisplay\n.thumb_set F_GetDisplay,0x80cb929");
__asm__(".global F_Restricted\n.thumb_set F_Restricted,0x80c8241");
__asm__(".global F_HasChoices\n.thumb_set F_HasChoices,0x80751ad");
__asm__(".global F_SelectorIndex\n.thumb_set F_SelectorIndex,0x8089d65");
__asm__(".global F_PollSelector\n.thumb_set F_PollSelector,0x8088fed");
__asm__(".global F_PollMessage\n.thumb_set F_PollMessage,0x8011861");
__asm__(".global F_GetText\n.thumb_set F_GetText,0x808b8e5");
__asm__(".global __modsi3\n.thumb_set __modsi3,0x08142951");

/* Observed slot status view: the original computes resource+700, then stores H20. */
struct GraphicStatus {u8 unknown[20];u16 status;};
