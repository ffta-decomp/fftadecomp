/* Method-local interface declarations from the frozen build. */
typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;
typedef signed int s32;
struct Unit { u8 unknown00[40]; u16 flags; u8 unknown2a[204]; u8 x,y,direction; u8 unknownf9[15]; };
struct Actor { struct Unit *unit; u8 unknown04[6]; s16 height; u8 unknown0c[19]; s8 variant; u8 unknown20[16]; u32 flags; u8 unknown34[32]; void *object; };
struct Origin {u8 unknown00[6]; u8 completed;};
struct Task {u16 phase; u16 unknown02; struct Origin *origin;};
struct Entrance {struct Origin *origin; struct Actor *candidates[13]; struct Actor *selected; s16 timer; s16 saved_height; u8 flags; u8 unknown41[3];};
struct ContentRecord {u8 unknown00[33]; u8 template_id; u8 unknown22[6];};
struct UnitTemplate {u8 bytes[48];};
struct DisplayShadow {u8 unknown00[74]; volatile u8 control_low,control_high,blend_a,blend_b;};
extern u8 content_bank[];
extern struct DisplayShadow display_shadow;
extern void (*const update_object)(void *,u32,u32,u32,u32,u32);
extern void *GetContentConsumerContext(void);
extern s32 CollectContextListPayloadsAt10(void *,struct Actor **);
extern int ReadUnitStatusBit12(const struct Unit *);
extern u16 ReadCurrentContentIndex(void);
extern struct Unit *FindUnitPoolSlot(u32 reserved);
extern void InitializeUnitFromTemplate(struct Unit *,const struct UnitTemplate *,u8);
extern u8 ReadContentValue0(void);
extern u8 ReadContentValue1(void);
extern struct Actor *FindOrCreateActor(void *,struct Unit *);
extern void SetActorState(struct Actor *,u16,s8,u16);
extern void PlayEnabledSound(u16);
#define OFF(T,F) ((u32)&(((T*)0)->F))
typedef char UnitLayout[sizeof(struct Unit)==264?1:-1];
typedef char EntranceLayout[sizeof(struct Entrance)==68?1:-1];
typedef char ActorHeightOffset[OFF(struct Actor,height)==10?1:-1];
typedef char ActorVariantOffset[OFF(struct Actor,variant)==31?1:-1];
typedef char ActorObjectOffset[OFF(struct Actor,object)==84?1:-1];
asm(".global content_bank\n.set content_bank,0x854cd54");
asm(".global display_shadow\n.set display_shadow,0x3000940");
asm(".global update_object\n.set update_object,0x8394034");
asm(".global ReadUnitStatusBit12\n.thumb_set ReadUnitStatusBit12,0x80c8299");
asm(".global FindUnitPoolSlot\n.thumb_set FindUnitPoolSlot,0x80c83a5");
asm(".global InitializeUnitFromTemplate\n.thumb_set InitializeUnitFromTemplate,0x80c9645");
asm(".global FindOrCreateActor\n.thumb_set FindOrCreateActor,0x8092441");
asm(".global SetActorState\n.thumb_set SetActorState,0x809836d");
asm(".global PlayEnabledSound\n.thumb_set PlayEnabledSound,0x8141521");
asm(".global GetContentConsumerContext\n.thumb_set GetContentConsumerContext,0x8096d7d");
asm(".global CollectContextListPayloadsAt10\n.thumb_set CollectContextListPayloadsAt10,0x8099cdd");
asm(".global ReadContentValue0\n.thumb_set ReadContentValue0,0x80c84f5");
asm(".global ReadContentValue1\n.thumb_set ReadContentValue1,0x80c8531");
asm(".global __divsi3\n.thumb_set __divsi3,0x81426b9");
/* The observed pointer is word1 of the bank link at base+1160. */
struct TemplateBankLink {u32 unknown; const struct UnitTemplate *templates;};


s32 AdvanceContentActorEntrance(u32 unused, struct Task *task, struct Entrance *entrance)
{
    switch (task->phase) {
    case 0: {
        struct Actor **candidate;
        s32 count;
        void *context;
        entrance->origin = task->origin;
        entrance->selected = 0;
        context = GetContentConsumerContext();
        candidate = entrance->candidates;
        count = CollectContextListPayloadsAt10(context, candidate);
        if (count > 0) {
            s32 remaining = count;
            do {
                if ((u8)ReadUnitStatusBit12((*candidate)->unit))
                    entrance->selected = *candidate;
                candidate++;
            } while (--remaining != 0);
        }
        break;
    }
    case 1:
        break;
    case 256:
        if (entrance->selected) {
            task->phase = 257;
        } else {
            u16 index = ReadCurrentContentIndex();
            const struct ContentRecord *record = (const struct ContentRecord *)content_bank + index;
            const struct TemplateBankLink *link = (const struct TemplateBankLink *)(content_bank + 1160);
            s32 template_offset = record->template_id * 48 - 48;
            const struct UnitTemplate *unit_template = (const struct UnitTemplate *)((const u8 *)link->templates + template_offset);
            struct Unit *unit = FindUnitPoolSlot(0);
            InitializeUnitFromTemplate(unit, unit_template, 0);
            unit->flags |= 0x1000;
            unit->direction = 0;
            unit->x = ReadContentValue0();
            unit->y = ReadContentValue1();
            entrance->selected = FindOrCreateActor(GetContentConsumerContext(), unit);
            entrance->selected->flags |= 5;
            task->phase = 257;
        }
        break;
    case 257:
        display_shadow.control_low = 64;
        display_shadow.control_high = 63;
        display_shadow.blend_a = 0;
        display_shadow.blend_b = 16;
        entrance->timer = 0;
        SetActorState(entrance->selected, 3, 0, 0);
        entrance->selected->flags &= ~5;
        entrance->saved_height = entrance->selected->height;
        entrance->selected->height += 80;
        update_object(entrance->selected->object, 1, 0, 0, 0, 0);
        PlayEnabledSound(200);
        task->phase = 258;
        break;
    case 258: {
        s32 fade_complete = 0;
        s32 delta, step;
        if (++entrance->timer > 1) {
            entrance->timer = 0;
            if (display_shadow.blend_a <= 15) {
                s32 value = display_shadow.blend_a + 1;
                display_shadow.blend_a = value;
            } else if (display_shadow.blend_b != 0) {
                s32 value = display_shadow.blend_b - 1;
                display_shadow.blend_b = value;
            } else {
                update_object(entrance->selected->object, 0, 0, 0, 0, 0);
                display_shadow.control_low = 0;
                fade_complete = 1;
            }
        }
        delta = entrance->saved_height - entrance->selected->height;
        step = delta / 8;
        if (step == 0 && delta != 0)
            step = delta / (delta < 0 ? -delta : delta);
        entrance->selected->height += step;
        if ((step < 0 ? -step : step) <= 0 && !(entrance->flags & 1)) {
            SetActorState(entrance->selected, 4, 0, 0);
            entrance->flags |= 1;
        }
        if (step == 0 && fade_complete) {
            task->phase = 259;
            entrance->timer = 0;
        }
        break;
    }
    case 259:
        if (++entrance->timer > 7) {
            entrance->timer = 0;
            entrance->selected->variant++;
            if (entrance->selected->variant > 3) {
                entrance->selected->variant = 0;
                SetActorState(entrance->selected, 8, entrance->selected->variant, 0);
                task->phase = 261;
            } else {
                SetActorState(entrance->selected, 9, entrance->selected->variant, 0);
            }
        }
        break;
    case 261:
        entrance->origin->completed = 1;
        task->phase = 3;
        break;
    }
    return 0;
}
