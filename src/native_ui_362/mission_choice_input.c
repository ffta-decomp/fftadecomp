typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
struct InputSnapshot { u16 held, pressed, repeated; };
struct MissionMenu { u8 unknown_00[92]; u8 *dialog; };
struct MissionChoice { u8 unknown_00[16]; u8 selected, count; };
extern struct InputSnapshot KeyState;
extern struct MissionMenu MissionMenu;
extern struct MissionChoice MissionChoice;
extern void RequestDefinitionRoute(int, int);
extern void RequestFixedDefinition(u32);
extern void ResetDialogTextState(void);
extern void RenderDialogRecord(u32, u32);
u32 HandleMissionChoiceInput(void) __asm__("CoreFrontier_00023DBC");
u32 HandleMissionChoiceInput(void)
{
    u32 changed=0;
    u32 pressed=KeyState.pressed;
    register u32 decrement_snapshot __asm__("r2")=pressed;
    u8 *dialog;
    u32 confirmed;
    __asm__("" : "+r"(decrement_snapshot) : "r"(pressed));
    dialog=MissionMenu.dialog;
    if (pressed&2) {
        RequestDefinitionRoute(1,105);
        ResetDialogTextState();
        dialog[0]=0;
        {
            u32 old_flags=dialog[1];
            register u32 result_flags __asm__("r0")=1;
            __asm__("" : "+r"(result_flags) : "r"(old_flags));
            result_flags|=old_flags;
            __asm__("" : "+r"(result_flags));
            dialog[1]=result_flags;
        }
        goto handled;
    }
    confirmed=pressed&1;
    if (confirmed) {
        RequestFixedDefinition(100);
        ResetDialogTextState();
        dialog[0]=0;
        {
            u32 old_flags=dialog[1];
            register u32 result_flags __asm__("r0")=1;
            __asm__("" : "+r"(result_flags) : "r"(old_flags));
            result_flags|=old_flags;
            __asm__("" : "+r"(result_flags));
            dialog[1]=result_flags;
        }
        goto handled;
    }
    if (pressed&16) {
        u32 selected;
        if (MissionChoice.count==1) return 0;
        changed=1;
        selected=MissionChoice.selected;
        if ((int)selected < MissionChoice.count-1)
            MissionChoice.selected=selected+1;
        else
            MissionChoice.selected=confirmed;
    } else if ((decrement_snapshot &=32)) {
        register struct MissionChoice *choice __asm__("r1")=&MissionChoice;
        int count;
        u32 selected;
        __asm__("" : "+r"(choice));
        count=choice->count;
        if (count==1) return 0;
        changed=1;
        selected=choice->selected;
        if (selected)
            selected--;
        else
            selected=count-1;
        choice->selected=selected;
    }
    if (!changed) return 0;
    RequestFixedDefinition(109);
    ResetDialogTextState();
    RenderDialogRecord(9,MissionChoice.selected);
handled:
    return 1;
}
__asm__(".global KeyState\n.set KeyState,0x03000000\n"
        ".global MissionMenu\n.set MissionMenu,0x0200f390\n"
        ".global MissionChoice\n.set MissionChoice,0x020020d0\n"
        ".global RequestDefinitionRoute\n.thumb_set RequestDefinitionRoute,0x08141571\n"
        ".global RequestFixedDefinition\n.thumb_set RequestFixedDefinition,0x08141541\n"
        ".global ResetDialogTextState\n.thumb_set ResetDialogTextState,0x08013365\n"
        ".global RenderDialogRecord\n.thumb_set RenderDialogRecord,0x08011b31\n");
