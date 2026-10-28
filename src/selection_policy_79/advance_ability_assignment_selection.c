/* Method-local interface declarations from the frozen build. */
typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef unsigned int u32;
struct Unit {u8 prefix[6];u8 field6,field7,derived8;u8 gap9[45];u8 assigned54;u8 gap55[3];u8 assigned58,assigned59,assigned60;};
struct AbilityContext {
u8 unknown0[1067];
u8 preview_mode;
u8 unknown42c[48];
u8 pane[1];
u8 unknown45d[260];
u8 category_source;
u8 unknown562[1725];
u8 category;
u8 unknownc20[1297];
u8 filter;
u8 unknown1132[1];
u8 flags1133;
u8 unknown1134[3024];
u8 preview_pending;
u8 unknown1d05[1];
u8 ui_mode;
u8 unknown1d07[5];
struct Unit *unit;
u8 unknown1d10[4010];
u8 controller_state;
u8 unknown2cbb[3];
u8 flag2cbe;
u8 unknown2cbf[7];
u16 selection_status;
u16 selection;
u8 unknown2cca[134];
void *list;
};
struct Window {u8 state;u8 unknown1[51];s8 timer;u8 unknown53[23];};
struct TaskSystem {u8 prefix[8];void **callbacks;u8 *states;};
struct KeyState {u16 held,pressed;};
extern struct AbilityContext *gAbilityContext;
extern struct Window gWindows[];
extern struct TaskSystem gTaskSystem;
extern struct KeyState gKeys;
extern u8 gResumeState,gWaitWindow,gEntryCount;
extern const u8 gCategoryTypes[];
extern void *CopyCategoryTypes(void*,const void*,u32);
extern void DrawAbilityList(int);
extern u32 BuildAbilityList(int,u8,void*);
extern const u16 *GetWindowText(int,int,int,int);
extern void FillWindowText(int,const u16*,u16,u16);
extern void InitializeAbilitySelection(int,void*,int,int,int,int);
extern void RefreshAbilityPreview(void),ActivatePane(void*),HidePane(void*);
extern void SetWindowState(int,u16);
extern u32 PollAbilitySelection(int,u16),RecalculateUnitByte8(const struct Unit*);
extern void PlaySound(u16);
extern void SetChildTask(struct TaskSystem*,u8,void(*)(void*,u8*),u8);
extern void AbilityChildPrimary(void*,u8*),AbilityChildOther(void*,u8*);
extern void ResetUnitPreview(int),LoadUnitPreview(struct Unit*),RefreshPane(void*,int);
__asm__(".global CopyCategoryTypes\n.thumb_set CopyCategoryTypes,0x81443fd");
__asm__(".global DrawAbilityList\n.thumb_set DrawAbilityList,0x807dc25");
__asm__(".global BuildAbilityList\n.thumb_set BuildAbilityList,0x807d96d");
__asm__(".global GetWindowText\n.thumb_set GetWindowText,0x808b8e5");
__asm__(".global FillWindowText\n.thumb_set FillWindowText,0x808b859");
__asm__(".global InitializeAbilitySelection\n.thumb_set InitializeAbilitySelection,0x808136d");
__asm__(".global RefreshAbilityPreview\n.thumb_set RefreshAbilityPreview,0x807b859");
__asm__(".global ActivatePane\n.thumb_set ActivatePane,0x8089ce5");
__asm__(".global HidePane\n.thumb_set HidePane,0x8088f5d");
__asm__(".global SetWindowState\n.thumb_set SetWindowState,0x808a605");
__asm__(".global PollAbilitySelection\n.thumb_set PollAbilitySelection,0x8084da1");
__asm__(".global RecalculateUnitByte8\n.thumb_set RecalculateUnitByte8,0x80c9079");
__asm__(".global PlaySound\n.thumb_set PlaySound,0x8141541");
__asm__(".global SetChildTask\n.thumb_set SetChildTask,0x8006af9");
__asm__(".global AbilityChildPrimary\n.thumb_set AbilityChildPrimary,0x807c7e9");
__asm__(".global AbilityChildOther\n.thumb_set AbilityChildOther,0x807d241");
__asm__(".global ResetUnitPreview\n.thumb_set ResetUnitPreview,0x8074ce9");
__asm__(".global LoadUnitPreview\n.thumb_set LoadUnitPreview,0x8074a55");
__asm__(".global RefreshPane\n.thumb_set RefreshPane,0x80774b5");
__asm__(".global gAbilityContext\n.set gAbilityContext,0x3002818");
__asm__(".global gWindows\n.set gWindows,0x30009e0");
__asm__(".global gTaskSystem\n.set gTaskSystem,0x3002730");
__asm__(".global gKeys\n.set gKeys,0x3000000");
__asm__(".global gResumeState\n.set gResumeState,0x200f237");
__asm__(".global gWaitWindow\n.set gWaitWindow,0x200f238");
__asm__(".global gEntryCount\n.set gEntryCount,0x200f239");
__asm__(".global gCategoryTypes\n.set gCategoryTypes,0x81499c0");

void AdvanceAbilityAssignmentSelection(void *unused,u8 *state)
{
    u8 category_types[4];
    CopyCategoryTypes(category_types,gCategoryTypes,4);
    switch (*state) {
    case 0: {
        int row,remaining;
        gAbilityContext->category=gAbilityContext->category_source;
        DrawAbilityList(0);
        gAbilityContext->flags1133=0;
        gAbilityContext->flag2cbe=0;
        gEntryCount=BuildAbilityList(category_types[gAbilityContext->category],gAbilityContext->unit->field6,gAbilityContext->list);
        for (row=2,remaining=4;remaining>=0;row+=2,--remaining) {
            const u16 *text=GetWindowText(5,1,0,row);
            FillWindowText(5,text,0,14);
        }
        InitializeAbilitySelection(0,gAbilityContext->list,5,0,0,0);
        RefreshAbilityPreview();
        gAbilityContext->ui_mode=3;
        gAbilityContext->preview_mode=10;
        gWaitWindow=3;
        SetWindowState(3,5);
        gResumeState=7;
        *state=9;
        break;
    }
    case 4: {
        int row,remaining;
        DrawAbilityList(1);
        ActivatePane(gAbilityContext->pane);
        for (row=2,remaining=4;remaining>=0;row+=2,--remaining) {
            const u16 *text=GetWindowText(5,1,0,row);
            FillWindowText(5,text,0,14);
        }
        gAbilityContext->controller_state=1;
        *state=7;
        break;
    }
    case 7:
        if (PollAbilitySelection(0,199)==255) {
            gAbilityContext->controller_state=8;
            gWaitWindow=5;
            SetWindowState(5,5);
            gResumeState=18;
            *state=9;
        } else if (gAbilityContext->selection_status==1) {
            PlaySound(155);
            if (gAbilityContext->category==0) {
                gAbilityContext->unit->assigned54=gAbilityContext->selection;
                gAbilityContext->unit->derived8=RecalculateUnitByte8(gAbilityContext->unit);
            } else if (gAbilityContext->category==1) gAbilityContext->unit->assigned58=gAbilityContext->selection;
            else if (gAbilityContext->category==2) gAbilityContext->unit->assigned59=gAbilityContext->selection;
            else if (gAbilityContext->category==3) gAbilityContext->unit->assigned60=gAbilityContext->selection;
            gWaitWindow=5;
            SetWindowState(5,5);
            gResumeState=18;
            *state=9;
        } else if (gAbilityContext->selection_status==2) {
            PlaySound(104);
            gAbilityContext->ui_mode=0;
            gWaitWindow=5;
            SetWindowState(5,5);
            gResumeState=18;
            *state=9;
        } else {
            if (gKeys.pressed&256) {
                PlaySound(100);
                gAbilityContext->ui_mode=0;
                if (gAbilityContext->category==0) gAbilityContext->filter=1;
                else if (gAbilityContext->category==1) gAbilityContext->filter=2;
                else if (gAbilityContext->category==2) gAbilityContext->filter=3;
                else gAbilityContext->filter=5;
                HidePane(gAbilityContext->pane);
                gResumeState=8;
                *state=11;
            }
            if (gAbilityContext->controller_state==6) SetWindowState(5,2);
        }
        break;
    case 11:
        if (gWindows[4].timer>29) {
            SetWindowState(5,5);
            gWindows[4].timer=30;
            *state=gResumeState;
        } else gWindows[4].timer=(u8)gWindows[4].timer+1;
        SetWindowState(4,3);
        break;
    case 10:
        if (gWindows[4].timer<=20) {
            gAbilityContext->ui_mode=3;
            gWindows[4].timer=20;
            *state=gResumeState;
        } else gWindows[4].timer=(u8)gWindows[4].timer-1;
        SetWindowState(4,3);
        break;
    case 8:
        if (gAbilityContext->filter==1) {
            gAbilityContext->filter=1;
            SetChildTask(&gTaskSystem,7,AbilityChildPrimary,2);
        } else SetChildTask(&gTaskSystem,7,AbilityChildOther,2);
        *state=16;
        break;
    case 16:
        if (gTaskSystem.states[7]==18) {
            gAbilityContext->preview_pending=0;
            ResetUnitPreview(30);
            LoadUnitPreview(gAbilityContext->unit);
            RefreshPane(gAbilityContext->pane,1);
            gWindows[4].timer=30;
            if (gEntryCount==0) DrawAbilityList(2);
            gResumeState=4;
            *state=10;
        }
        break;
    case 9:
        if (gWindows[gWaitWindow].state==0) *state=gResumeState;
        break;
    case 17:
        SetWindowState(5,5);
        *state=18;
        break;
    case 1:case 2:case 3:case 5:case 6:case 12:case 13:case 14:case 15:case 18:
        break;
    }
}
