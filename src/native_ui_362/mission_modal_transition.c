typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
struct MissionHead {
    void *mission_object;
    void *data;
    u8 unknown_08[4];
    u16 mission_id;
    u8 unknown_0e[2];
    u8 record;
    u8 mode;
    u8 action;
};
struct MissionMenu {
    u8 unknown_00;
    u8 active;
    u8 flags;
    u8 unknown_03[3];
    u8 phase;
    u8 unknown_07[85];
    u8 *dialog;
};
struct ContextRule {
    u8 unknown_00[8];
    u16 flags;
    u8 unknown_0a[2];
};
extern struct MissionMenu MissionMenu;
extern u8 GameState[];
extern struct MissionHead MissionHead;
extern const struct ContextRule ContextRules[];
extern void (*const ClearBytes)(void *,u32);
extern void (*const CopyBytes)(void *,const void *,u32);
extern void *GetConsumerContext(void);
extern void SetRegistryFlagFromZero(void *,u32);
extern void BeginTransition(void);
extern u32 TransitionReady(void);
extern const u8 *GetSelectionPalette(u8);
extern u8 ReadSaveByte(u16);
extern void *FindLiveMissionRecord(u16);
extern void *FindUnitPoolRecordById(u16);
extern void BeginMissionModal(u32);
extern void *AllocatePoolBytes(u32);
extern void ReleasePoolAllocation(void *);
extern void InitializeDialog(void *,u8,u32,void *,void *,u16,u16,u8,u8,u16);
extern void SetPairCursor(void *,const void *,short,short);
extern u32 PollDialog(void);
extern u32 PollMissionChoice(void);
extern void DrawMissionIndicators(void);
extern void FinishMissionModal(void);
extern void ChangeSceneMode(u32);
extern u8 TileLayer[];
extern u8 TextLayer[];
extern u8 ChoiceCursorFirst[];
extern u8 ChoiceCursorSecond[];
extern u8 PaletteDestination[];
u32 AdvanceMissionModalTransition(void) __asm__("SceneRegisteredRoot_00023AF4");
u32 AdvanceMissionModalTransition(void)
{
    struct MissionMenu *menu;
    u32 phase;
    {
        register struct MissionMenu *entry_view __asm__("r0")=&MissionMenu;
        register u32 loaded_phase __asm__("r1");
        __asm__("" : "+r"(entry_view));
        loaded_phase=entry_view->phase;
        __asm__("" : "+r"(loaded_phase) : "r"(entry_view));
        menu=entry_view;
        phase=loaded_phase;
    }
    switch(phase) {
    case 0:
        SetRegistryFlagFromZero(GetConsumerContext(),0);
        BeginTransition();
        MissionMenu.phase=1;
        break;
    case 1: {
        register u8 *game __asm__("r4");
        u8 *selected_context;
        register u8 *choice_destination __asm__("r0");
        u32 rule_mask;
        u16 *pending;
        register struct MissionHead *head __asm__("r1");
        void *data;
        register u32 choice_zero __asm__("r2");
        if (!(u8)TransitionReady()) break;
        CopyBytes(PaletteDestination,GetSelectionPalette(12)+24,2);
        game=GameState;
        __asm__("" : "+r"(game));
        selected_context=game+0x3c2a;
        {
            register u32 rule_offset __asm__("r0")=(u32)*selected_context * 12;
            const struct ContextRule *rule;
            __asm__("" : "+r"(rule_offset));
            rule=(const struct ContextRule *)((const u8 *)ContextRules+rule_offset);
            rule_mask=(u16)(rule->flags & 8);
        }
        __asm__("" : "+r"(rule_mask));
        if (rule_mask) {
            struct MissionHead *rule_head=(struct MissionHead *)(game+0x20d0);
            rule_head->mission_object=0;
            {
                register u32 context_value __asm__("r1")=*selected_context;
                __asm__("" : "+r"(context_value));
                game[0x2184]=context_value;
            }
            rule_head->mode=1;
            {
                register u32 data_offset __asm__("r1")=0x2fc4;
                register void *rule_data __asm__("r0");
                __asm__("" : "+r"(data_offset));
                rule_data=game+data_offset;
                __asm__("" : "+r"(rule_data) : "r"(game));
                rule_head->data=rule_data;
            }
            goto start_modal;
        }
        {
            register u32 pending_offset __asm__("r2")=0x3c28;
            __asm__("" : "+r"(pending_offset));
            pending=(u16 *)(game+pending_offset);
        }
        if (*pending) {
            if (ReadSaveByte(13)==1) {
                {
                    register u32 head_offset __asm__("r3")=0x20d0;
                    __asm__("" : "+r"(head_offset));
                    head=(struct MissionHead *)(game+head_offset);
                    __asm__("" : "+r"(head));
                }
                {
                    u32 pending_id=*pending;
                    choice_zero=0;
                    __asm__("" : "+r"(choice_zero) : "r"(pending_id));
                    head->mission_id=pending_id;
                }
                head->mode=4;
                head->mission_object=(void *)(u32)rule_mask;
                {
                    register u32 choice_offset __asm__("r1")=0x2184;
                    __asm__("" : "+r"(choice_offset));
                    choice_destination=game+choice_offset;
                    __asm__ __volatile__("" : "+r"(choice_destination));
                }
            } else {
                void *mission=FindLiveMissionRecord(*pending);
                head=(struct MissionHead *)(game+0x20d0);
                __asm__("" : "+r"(head));
                head->mission_object=mission;
                head->mode=5;
                choice_zero=0;
                __asm__("" : "+r"(choice_zero));
                head->mission_id=rule_mask;
                choice_destination=game+0x2184;
                __asm__ __volatile__("" : "+r"(choice_destination));
            }
            *choice_destination=choice_zero;
            game=GameState;
            __asm__("" : "+r"(game));
            if (game[0x3c2a]==8) {
                data=FindUnitPoolRecordById(10);
                head=(struct MissionHead *)(game+0x20d0);
                __asm__("" : "+r"(head));
                goto store_modal_data;
            }
            head=(struct MissionHead *)(game+0x20d0);
            __asm__("" : "+r"(head));
            goto default_modal_data;
        }
        head=(struct MissionHead *)(game+0x20d0);
        __asm__("" : "+r"(head));
        head->mission_object=0;
        {
            register u32 context_value __asm__("r2")=*selected_context;
            __asm__("" : "+r"(context_value));
            game[0x2184]=context_value;
        }
        head->mode=1;
default_modal_data:
        data=game+0x2fc4;
store_modal_data:
        head->data=data;
start_modal:
        MissionHead.record=0;
        MissionHead.action=4;
        BeginMissionModal(1);
        MissionMenu.phase=2;
        break;
    }
    case 2: {
        u8 *dialog=AllocatePoolBytes(1976);
        menu=&MissionMenu;
        menu->dialog=dialog;
        ClearBytes(dialog,1976);
        InitializeDialog(dialog+4,9,MissionHead.record,TileLayer,TextLayer,
                         2,1,24,16,224);
        SetPairCursor(dialog+1944,ChoiceCursorFirst,216,14);
        SetPairCursor(dialog+1960,ChoiceCursorSecond,24,14);
        menu->phase=3;
        break;
    }
    case 3: {
        u8 *dialog=menu->dialog;
        if ((u16)PollDialog()) {
            u32 next_phase;
            if (dialog[1]&1) {
                next_phase=5;
            } else {
                if (MissionHead.mode>1) dialog[0]=1;
                next_phase=4;
            }
            menu->phase=next_phase;
        }
        goto draw_indicators;
    }
    case 4:
        if ((u8)PollMissionChoice()) MissionMenu.phase=3;
draw_indicators:
        DrawMissionIndicators();
        break;
    case 5:
        MissionHead.mission_object=0;
        MissionHead.mission_id=0;
        *((u8 *)&MissionHead+180)=0;
        MissionHead.mode=0;
        MissionHead.data=0;
        ReleasePoolAllocation(menu->dialog);
        menu->dialog=0;
        FinishMissionModal();
        ChangeSceneMode(5);
        menu->flags=128;
        SetRegistryFlagFromZero(GetConsumerContext(),1);
        menu->active=0;
        return 1;
    }
    return 21;
}
__asm__(".global MissionMenu\n.set MissionMenu,0x0200f390\n"
        ".global GameState\n.set GameState,0x02000000\n"
        ".global MissionHead\n.set MissionHead,0x020020d0\n"
        ".global ContextRules\n.set ContextRules,0x08563a70\n"
        ".global ClearBytes\n.set ClearBytes,0x0836d4b8\n"
        ".global CopyBytes\n.set CopyBytes,0x0836d4bc\n"
        ".global TileLayer\n.set TileLayer,0x030008b0\n"
        ".global TextLayer\n.set TextLayer,0x03000990\n"
        ".global ChoiceCursorFirst\n.set ChoiceCursorFirst,0x0851ba72\n"
        ".global ChoiceCursorSecond\n.set ChoiceCursorSecond,0x0851ba7a\n"
        ".global PaletteDestination\n.set PaletteDestination,0x030039f8\n"
        ".global GetConsumerContext\n.thumb_set GetConsumerContext,0x08096d7d\n"
        ".global SetRegistryFlagFromZero\n.thumb_set SetRegistryFlagFromZero,0x0809a261\n"
        ".global BeginTransition\n.thumb_set BeginTransition,0x080a9549\n"
        ".global TransitionReady\n.thumb_set TransitionReady,0x080a9589\n"
        ".global GetSelectionPalette\n.thumb_set GetSelectionPalette,0x080cba85\n"
        ".global ReadSaveByte\n.thumb_set ReadSaveByte,0x080c95a9\n"
        ".global FindLiveMissionRecord\n.thumb_set FindLiveMissionRecord,0x080d2de1\n"
        ".global FindUnitPoolRecordById\n.thumb_set FindUnitPoolRecordById,0x080c83cd\n"
        ".global BeginMissionModal\n.thumb_set BeginMissionModal,0x08022a05\n"
        ".global AllocatePoolBytes\n.thumb_set AllocatePoolBytes,0x08022841\n"
        ".global ReleasePoolAllocation\n.thumb_set ReleasePoolAllocation,0x08022855\n"
        ".global InitializeDialog\n.thumb_set InitializeDialog,0x0801174d\n"
        ".global SetPairCursor\n.thumb_set SetPairCursor,0x08017fa9\n"
        ".global PollDialog\n.thumb_set PollDialog,0x08011861\n"
        ".global PollMissionChoice\n.thumb_set PollMissionChoice,0x08023dbd\n"
        ".global DrawMissionIndicators\n.thumb_set DrawMissionIndicators,0x08023e89\n"
        ".global FinishMissionModal\n.thumb_set FinishMissionModal,0x0802317d\n"
        ".global ChangeSceneMode\n.thumb_set ChangeSceneMode,0x0802292d\n"
        ".global _call_via_r2\n.thumb_set _call_via_r2,0x0814224d\n"
        ".global _call_via_r3\n.thumb_set _call_via_r3,0x08142251\n");
