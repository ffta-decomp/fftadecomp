typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;
typedef signed int s32;
struct Event { u16 phase, unknown2; void *actor; void *out_y; u8 unknown12[8]; u16 x, y; u32 unknown24; };
struct Work {
    s16 x, y; u16 delay; u8 variant, unknown7;
    u16 selected_x, selected_y; void *palette_backup; void *effect;
    void *child_a, *child_b, *child_c, *child_d, *child_e, *child_f, *child_g;
    void *setup; void *actor; void *closing; void *fade;
};
typedef u32 (*Callback)(void *, struct Event *, struct Work *);
typedef char EventSize[sizeof(struct Event)==28?1:-1];
typedef char WorkSize[sizeof(struct Work)==64?1:-1];
extern u32 Child112AEC(void *, struct Event *, struct Work *) __asm__("RetailChild112AEC");
extern u32 Child112E88(void *, struct Event *, struct Work *) __asm__("RetailChild112E88");
extern u32 Child112F80(void *, struct Event *, struct Work *) __asm__("RetailChild112F80");
extern u32 Child113220(void *, struct Event *, struct Work *) __asm__("RetailChild113220");
extern u32 Child11360C(void *, struct Event *, struct Work *) __asm__("RetailChild11360C");
extern u32 Child113918(void *, struct Event *, struct Work *) __asm__("RetailChild113918");
extern u32 Child113C68(void *, struct Event *, struct Work *) __asm__("RetailChild113C68");
extern void *Spawn(Callback, u32, struct Event *, void *) __asm__("RetailCall_08005b6c");
extern void *PollFade(void *) __asm__("RetailCall_080dfed8");
extern void *PollSetup(void *) __asm__("RetailCall_080e05dc");
extern void *PollChild(void *) __asm__("RetailCall_080e051c");
extern void *PollClosing(void *) __asm__("RetailCall_08115b40");
extern void *Fade(u32, u32, void *) __asm__("RetailCall_080dfd68");
extern void *CreateSetup(void *, const void *, u32, u32, u32, void *) __asm__("RetailCall_080e03f8");
extern void GetCoordinates(s16 *, s16 *) __asm__("RetailCall_0801e6f0");
extern void SetupPhaseOne(void) __asm__("RetailCall_080d38b4");
extern void *Allocate(u32) __asm__("RetailCall_0800a654");
extern void Free(void *) __asm__("RetailCall_0800a668");
extern void CopyHalfwords(const void *, void *, u32) __asm__("RetailCall_0814186c");
extern const void *PaletteAddress(void) __asm__("RetailCall_080d3904");
extern void RestoreDisplay(void) __asm__("RetailCall_0801e2a4");
extern void GetDisplayBytes(u8 *, u8 *) __asm__("RetailCall_0801e610");
extern u32 DisplayMask(u32) __asm__("RetailCall_080035a8");
extern void SetCoordinates(s32, s32) __asm__("RetailCall_0801e5e0");
extern void RefreshDisplay(void) __asm__("RetailCall_0801b878");
extern void FinishActor(void *) __asm__("RetailCall_08115acc");
extern void FinishDisplay(void) __asm__("RetailCall_0801db3c");
extern void *CreateClosing(void *, u32, void *) __asm__("RetailCall_08115ae4");
extern const u8 SetupResource[] __asm__("RetailSetupResource");
extern u16 PaletteShadow[95] __asm__("RetailPaletteShadow");
extern u16 DisplayShadow __asm__("RetailDisplayShadow");

u32 OriginalAuthoredSequence_00113CE0(void *task, struct Event *event, struct Work *work)
{
    struct Event event_a, event_b, event_c, event_d, event_e, event_f, event_g;
    u8 first, second;
    s32 phase = event->phase;
    switch (phase) {
    case 0: {
        u16 variant = event->y;
        void *actor;
        u32 mode;
        work->variant = variant;
        actor = event->actor;
        work->actor = actor;
        mode = 9;
        if ((u32)variant << 24)
            mode = 0;
        work->setup = CreateSetup(actor, SetupResource, mode, 7, phase, task);
        GetCoordinates(&work->x, &work->y);
        break;
    }
    case 1:
        SetupPhaseOne();
        break;
    case 256:
        if (work->variant) {
            work->setup = PollSetup(work->setup);
            if (work->setup)
                break;
            event->phase = 265;
            break;
        } else {
            work->setup = PollSetup(work->setup);
            if (work->setup)
                break;
            work->fade = Fade(1, 30, task);
            event->phase += 1;
            break;
        }
    case 257:
        work->fade = PollFade(work->fade);
        if (work->fade)
            break;
        event_a.actor = &work->selected_x;
        event_a.out_y = &work->selected_y;
        work->child_a = Spawn(Child112AEC, 28, &event_a, task);
        event->phase += 1;
        break;
    case 258:
        work->child_a = PollChild(work->child_a);
        if (work->child_a)
            break;
        work->palette_backup = Allocate(192);
        CopyHalfwords(PaletteShadow, work->palette_backup, 95);
        CopyHalfwords(PaletteAddress(), PaletteShadow, 95);
        event_b.x = work->selected_x;
        event_b.y = work->selected_y;
        work->child_b = Spawn(Child112E88, 28, &event_b, task);
        event->phase += 1;
        break;
    case 259:
        work->child_b = PollChild(work->child_b);
        if (work->child_b)
            break;
        event_c.actor = &work->effect;
        work->child_c = Spawn(Child112F80, 28, &event_c, task);
        event->phase += 1;
        break;
    case 260:
        work->child_c = PollChild(work->child_c);
        if (work->child_c)
            break;
        work->child_d = Spawn(Child113220, 680, &event_d, task);
        event->phase += 1;
        break;
    case 261:
        work->child_d = PollChild(work->child_d);
        if (work->child_d)
            break;
        event_e.actor = &work->effect;
        work->child_e = Spawn(Child11360C, 44, &event_e, task);
        event->phase += 1;
        break;
    case 262:
        work->child_e = PollChild(work->child_e);
        if (work->child_e)
            break;
        event_f.actor = &work->effect;
        work->child_f = Spawn(Child113918, 96, &event_f, task);
        event->phase += 1;
        break;
    case 263:
        work->child_f = PollChild(work->child_f);
        if (work->child_f)
            break;
        work->child_g = Spawn(Child113C68, 16, &event_g, task);
        work->delay = 30;
        event->phase += 1;
        break;
    case 264: {
        u32 remaining = work->delay - 1;
        u8 *first_out, *second_out;
        u32 mask, shadow;
        work->delay = remaining;
        if (remaining << 16)
            break;
        RestoreDisplay();
        first_out = &first;
        second_out = &second;
        /* Actual constructor OUT addresses die at this call. Later byte
         * observations have fresh stack addresses; no fabricated values. */
        __asm__("" : "+r" (first_out), "+r" (second_out));
        GetDisplayBytes(first_out, second_out);
        mask = DisplayMask(first);
        shadow = DisplayShadow;
        DisplayShadow = shadow | mask;
        mask = DisplayMask(second);
        shadow = DisplayShadow;
        DisplayShadow = shadow | mask;
        SetCoordinates(work->x, work->y);
        RefreshDisplay();
        CopyHalfwords(work->palette_backup, PaletteShadow, 95);
        Free(work->palette_backup);
        FinishActor(work->actor);
        FinishDisplay();
        work->fade = Fade(0, 30, task);
        event->phase += 1;
        break;
    }
    case 265:
        work->fade = PollFade(work->fade);
        if (work->fade)
            break;
        work->child_g = PollChild(work->child_g);
        if (work->child_g)
            break;
        work->closing = CreateClosing(work->actor, 3, task);
        event->phase += 1;
        break;
    case 266:
        work->closing = PollClosing(work->closing);
        if (work->closing)
            break;
        event->phase = 2;
        break;
    }
    return 0;
}

__asm__(".global RetailChild112AEC\n.thumb_set RetailChild112AEC,0x8112aed\n.global RetailChild112E88\n.thumb_set RetailChild112E88,0x8112e89\n.global RetailChild112F80\n.thumb_set RetailChild112F80,0x8112f81\n.global RetailChild113220\n.thumb_set RetailChild113220,0x8113221\n.global RetailChild11360C\n.thumb_set RetailChild11360C,0x811360d\n.global RetailChild113918\n.thumb_set RetailChild113918,0x8113919\n.global RetailChild113C68\n.thumb_set RetailChild113C68,0x8113c69\n.global RetailSetupResource\n.set RetailSetupResource,0x83a3554\n.global RetailPaletteShadow\n.set RetailPaletteShadow,0x3003862\n.global RetailDisplayShadow\n.set RetailDisplayShadow,0x3000940\n.global RetailCall_08005b6c\n.thumb_set RetailCall_08005b6c,0x8005b6d\n.global RetailCall_080dfed8\n.thumb_set RetailCall_080dfed8,0x80dfed9\n.global RetailCall_080e05dc\n.thumb_set RetailCall_080e05dc,0x80e05dd\n.global RetailCall_080e051c\n.thumb_set RetailCall_080e051c,0x80e051d\n.global RetailCall_08115b40\n.thumb_set RetailCall_08115b40,0x8115b41\n.global RetailCall_080dfd68\n.thumb_set RetailCall_080dfd68,0x80dfd69\n.global RetailCall_080e03f8\n.thumb_set RetailCall_080e03f8,0x80e03f9\n.global RetailCall_0801e6f0\n.thumb_set RetailCall_0801e6f0,0x801e6f1\n.global RetailCall_080d38b4\n.thumb_set RetailCall_080d38b4,0x80d38b5\n.global RetailCall_0800a654\n.thumb_set RetailCall_0800a654,0x800a655\n.global RetailCall_0800a668\n.thumb_set RetailCall_0800a668,0x800a669\n.global RetailCall_0814186c\n.thumb_set RetailCall_0814186c,0x814186d\n.global RetailCall_080d3904\n.thumb_set RetailCall_080d3904,0x80d3905\n.global RetailCall_0801e2a4\n.thumb_set RetailCall_0801e2a4,0x801e2a5\n.global RetailCall_0801e610\n.thumb_set RetailCall_0801e610,0x801e611\n.global RetailCall_080035a8\n.thumb_set RetailCall_080035a8,0x80035a9\n.global RetailCall_0801e5e0\n.thumb_set RetailCall_0801e5e0,0x801e5e1\n.global RetailCall_0801b878\n.thumb_set RetailCall_0801b878,0x801b879\n.global RetailCall_08115acc\n.thumb_set RetailCall_08115acc,0x8115acd\n.global RetailCall_0801db3c\n.thumb_set RetailCall_0801db3c,0x801db3d\n.global RetailCall_08115ae4\n.thumb_set RetailCall_08115ae4,0x8115ae5\n");
