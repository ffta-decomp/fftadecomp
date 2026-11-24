/* Original5044B authored timeline. Raw helper declarations retain each physical caller argument. */
#include "ffta/unsigned_types.h"
typedef signed char s8;
typedef signed short s16;
typedef signed int s32;
struct Rectangle {u16 left,top,right,bottom;};
#define BYTE_AT(p,o) (*(u8 *)((u8 *)(p)+(o)))
#define HALF_AT(p,o) (*(u16 *)((u8 *)(p)+(o)))
#define WORD_AT(p,o) (*(u32 *)((u8 *)(p)+(o)))
struct DisplayShadow {u8 gap0[10];volatile u16 h10,h12;u8 gap14[52];volatile u8 b66,b67;u8 gap68[10];volatile u8 b78;};
#define SHADOW ((struct DisplayShadow *)0x03000940)
#define SHADOW_B(o) SHADOW->b##o
#define SHADOW_H(o) SHADOW->h##o
struct SceneBufferGlobals { u8 prefix[20]; void *first; u8 between[28]; void *second; };
extern struct SceneBufferGlobals scene_buffers __asm__("0x03000E60");
extern struct SceneBufferGlobals scene_buffers_second __asm__("0x03000E80");
extern u8 *scene_workspace;
extern void *clear_callback;
extern u8 scene_mode,local_exit_flag;
struct SceneInputState { u16 prior; u16 pressed; };
extern struct SceneInputState scene_input_state __asm__("0x03000000");
extern const u8 cue_table[],cue_selectors[];
extern u8 scene_palette_buffer[];
extern const u32 cue_timestamps[];
void AdvanceAuthoredSceneTimeline(void *,u8 *) asm("CoreRegistered40_0013C0EC");
extern void Cue(u32);
extern void RemoveHook(u32);
extern void ReleaseSceneTask(void *);
extern u32 ReadSceneFlag(u32);
extern void * RequestSceneWorkspace(u32);
extern void ReleaseSceneWorkspace(void *);
extern void SetAuthoredSelector(u32);
extern void RefreshSceneAux(void);
extern u32 AdvanceSceneCue(void *, void *, void *, void *);
extern void QueueTransition(void *);
extern void AdvanceRectangle(void *);
extern u32 AdvanceCoordinateCue(u32,u32,u32,s32,s32,s32,s32);
extern void ConfigureOwnerMotion(void *,u32,u32,u32,u32);
extern void DrawOwner(void *,u32,u32,u32);
extern void BeginCueObject(void *,u32,u32,u32,u32,u32);
extern void AdvanceCueObject(void *);
extern void AdvanceTransition(void *);
extern void InitializeRectangle(void *,const void *,u32,u32);
extern void ConfigureRectangle(void *,const void *,u32);
extern void BindRectangle(void *,const void *,u32);
extern void SetRectangleActive(void *,u32);
extern void ReadRectangle(void *,struct Rectangle *);
extern void SetOwnerMode(void *,u32);
extern void InitializeOwner(void *,const void *,u32,u32,u32,u32,u32,u32,u32,s32,u32,u32);
extern void BindOwnerSequence(void *,const void *);
extern void SetOwnerState(void *,u32);
extern void SetOwnerActive(void *,u32);
extern void SetOwnerRectangle(void *,const struct Rectangle *);
extern void InitializeCueObject(void *);
extern void StopCueObject(void *);
extern void InitializeTransition(void *);
extern void SetTransitionMode(void *,u32);
extern void ConfigureTransition(void *,u32,u32,u32,u32);
extern void ShowSceneText(u32);
extern u32 ReadSceneConnection(void);
extern void CopyHalfwords(const void *,void *,u32);
extern void CallClearViaR2(void *,u32,void *);
extern void * BeginTransitionVariant(u32,u32,u32);
extern void * BeginTransition(u32,u32,u32);
extern void * BeginSavedTransition(u32,u32,u32,const void *);
extern void ResetSceneResources(void);
extern void ActivateTransition(void *);
extern void SceneOperation_13f438(void);
extern void SceneOperation_13f794(void);
extern void SceneOperation_13fc24(void);
extern void SceneOperation_13fc8c(void);
extern void SceneOperation_1457fc(void);
extern void SceneOperation_13f22c(void);
extern void SceneOperation_13f604(void);
extern void SceneOperation_13fcf0(void);
extern void SceneOperation_13f898(void);
extern void SceneOperation_13f934(void);
extern void SceneOperation_13f9f8(void);
extern void SceneOperation_13faa0(void);

void AdvanceAuthoredSceneTimeline(void *unused, u8 *state) {
    u16 first_fill;
    u16 second_fill;
    struct Rectangle rectangle;
    u8 *state_slot;
    s32 first_tick;
    s32 cue_tick;
    s32 timer_snapshot;
    s32 cue_offset;
    u32 skip_delay;
    u8 flag_value;
    u8 connected;
    u8 entry_phase;
    u8 cue_index;
    register u32 stop_index __asm__("r6");
    u8 init_index;
    register u32 event_index __asm__("r6");
    u8 *snapshot_0;
    u8 *snapshot_1;
    u8 *snapshot_3;
    u8 *snapshot_4;
    u8 *snapshot_5;
    u8 *snapshot_6;
    u8 *snapshot_7;
    u8 *snapshot_8;
    u8 *snapshot_9;
    u8 *snapshot_10;
    u8 *snapshot_11;
    u8 *snapshot_12;
    u8 *snapshot_13;
    u8 *snapshot_15;
    u8 *snapshot_16;
    u8 *snapshot_17;
    u8 *snapshot_18;
    u8 *snapshot_19;
    u8 *snapshot_20;
    u8 *snapshot_21;
    u8 *snapshot_22;
    u8 *snapshot_23;
    u8 *snapshot_14;
    u8 *snapshot_24;
    u8 *snapshot_25;
    u8 *snapshot_26;
    u8 *snapshot_27;
    u8 *snapshot_28;
    u8 *snapshot_29;
    u8 *snapshot_30;
    u8 *snapshot_31;
    u8 *snapshot_32;
    u8 *snapshot_33;
    u8 *snapshot_34;
    u8 *snapshot_35;
    u8 *snapshot_37;
    u8 *snapshot_38;
    u8 *snapshot_39;
    u8 *snapshot_40;
    u8 *snapshot_41;
    u8 *snapshot_42;
    u8 *snapshot_45;
    u8 *snapshot_46;
    u8 *snapshot_47;
    const u8 *cue_descriptor;
    void *skip_transition;

    state_slot = state;
    entry_phase = *state;
    switch (entry_phase) {                              /* irregular */
    case 0x0:{
        register u8 **workspace_cell __asm__("r5");
        register u32 cue_stride __asm__("r4");
        Cue(0x31A);
        workspace_cell=&scene_workspace;__asm__("" : "+r"(workspace_cell));
        snapshot_0 = RequestSceneWorkspace(0xCB70);
        *workspace_cell = snapshot_0;
        CallClearViaR2(snapshot_0, 0xCB70, clear_callback);
        CallClearViaR2((*workspace_cell) + 0x8FDC, 0x190, clear_callback);
        CallClearViaR2((*workspace_cell) + 0x916C, 0x64, clear_callback);
        CallClearViaR2((*workspace_cell) + 0x91D0, 0x64, clear_callback);
        InitializeTransition((*workspace_cell) + 0x8B84);
        SceneOperation_1457fc();
        SceneOperation_13f22c();
        SceneOperation_13f604();
        SetOwnerActive((*workspace_cell) + 0x94C0, 0);
        SetOwnerActive((*workspace_cell) + 0xA67C, 0);
        SetOwnerActive((*workspace_cell) + 0xB838, 0);
        InitializeRectangle((*workspace_cell) + 0x8B8C, (const void *)0x083A9008, 0, 0);
        InitializeRectangle((*workspace_cell) + 0x8BB0, (const void *)0x083A9008, 1, 0);
        BindRectangle((*workspace_cell) + 0x8B8C, 0, 0);
        SHADOW_H(10) = 0xFFB0U;
        SHADOW_H(12) = 0xFFF8U;
        WORD_AT((*workspace_cell), 0x8FD8) = (s32) entry_phase;
        *state_slot = 1;
        init_index = 0;
        cue_stride = 0x4C; __asm__("" : "+r"(cue_stride));
        do {
            InitializeCueObject((*workspace_cell) + ((init_index * cue_stride) + 0xC9F4));
            init_index += 1;
        } while ((u32) init_index <= 4U);
        break;}
    case 0x1:
        snapshot_3 = scene_workspace;
        if ((WORD_AT(snapshot_3, 0x8FD8) == 0x3C) && (BYTE_AT(snapshot_3, 0x9234) == 0) && ((ReadSceneFlag(0x44) << 0x18) == 0)) {
            BYTE_AT((scene_workspace), 0x91D0) = entry_phase;
        }
        snapshot_31 = scene_workspace;
        timer_snapshot = WORD_AT(snapshot_31, 0x8FD8);
        if (timer_snapshot == 1) {
            if (BYTE_AT(snapshot_31, 0x9234) == 0) {
                BYTE_AT(snapshot_31, 0x91D1) = (u8) timer_snapshot;
            }
            snapshot_14 = scene_workspace;
            first_tick = WORD_AT(snapshot_14, 0x8FD8);
            if ((first_tick == 1) && (BYTE_AT(snapshot_14, 0x9234) == 0)) {
                BYTE_AT(snapshot_14, 0x91D2) = (u8) first_tick;
            }
        }
        snapshot_24 = scene_workspace;
        if ((WORD_AT(snapshot_24, 0x8FD8) == 0x3C) && (BYTE_AT(snapshot_24, 0x9234) == 0)) {
            BYTE_AT(snapshot_24, 0x91D3) = 1U;
        }
        snapshot_25 = scene_workspace;
        if ((WORD_AT(snapshot_25, 0x8FD8) == 0xF0) && (BYTE_AT(snapshot_25, 0x9234) == 0)) {
            BYTE_AT(snapshot_25, 0x91D4) = 1U;
        }
        snapshot_37 = scene_workspace;
        if ((WORD_AT(snapshot_37, 0x8FD8) == 0x14A) && (BYTE_AT(snapshot_37, 0x9234) == 0)) {
            BYTE_AT(snapshot_37, 0x91D5) = 1U;
        }
        snapshot_38 = scene_workspace;
        if ((WORD_AT(snapshot_38, 0x8FD8) == 0x14E) && (BYTE_AT(snapshot_38, 0x9234) == 0)) {
            BYTE_AT(snapshot_38, 0x91D6) = 1U;
        }
        snapshot_39 = scene_workspace;
        if ((WORD_AT(snapshot_39, 0x8FD8) == 0x14F) && (BYTE_AT(snapshot_39, 0x9234) == 0)) {
            BYTE_AT(snapshot_39, 0x91D7) = 1U;
        }
        snapshot_40 = scene_workspace;
        if ((WORD_AT(snapshot_40, 0x8FD8) == 0x1FE) && (BYTE_AT(snapshot_40, 0x9234) == 0)) {
            BYTE_AT(snapshot_40, 0x91D8) = 1U;
        }
        snapshot_41 = scene_workspace;
        if ((WORD_AT(snapshot_41, 0x8FD8) == 0x294) && (BYTE_AT(snapshot_41, 0x9234) == 0)) {
            BYTE_AT(snapshot_41, 0x91D9) = 1U;
        }
        snapshot_42 = scene_workspace;
        if (WORD_AT(snapshot_42, 0x8FD8) == 0x2D0) {
            if (BYTE_AT(snapshot_42, 0x9234) == 0) {
                BYTE_AT(snapshot_42, 0x91DA) = 1U;
                goto block_51;
            }
        } else {
block_51:
            if (BYTE_AT((scene_workspace), 0x9234) == 0) {
                u32 cue_object_stride;
                cue_index = 0;
                do {
                    register u32 entry_time __asm__("r1");
                    register const u32 *tick_address __asm__("r0");
                    cue_offset = cue_index * 0x14;
                    cue_descriptor = cue_table + cue_offset;
                    snapshot_45 = scene_workspace;
                    /* One real stride working definition feeds all three
                     * original object-address MULs. Keep known ROM field
                     * roots independent; no ASM operand creates this value. */
                    cue_object_stride = 0x4C;
                    tick_address = (const u32 *)(snapshot_45 + 0x8FD8); __asm__("" : "+r"(tick_address));
                    entry_time = WORD_AT(cue_table, cue_offset); __asm__("" : "+r"(entry_time));
                    cue_tick = *tick_address;
                    if (entry_time == cue_tick) {
                        register u32 begin_offset __asm__("r0") = cue_index;
                        /* Original copy/MUL has its own destructive value;
                         * the loop ordinal survives the callback. */
                        __asm__("" : "+r"(begin_offset));
                        begin_offset *= cue_object_stride;
                        BeginCueObject(snapshot_45 + (begin_offset + 0xC9F4), BYTE_AT(cue_descriptor, 0x10), WORD_AT(cue_table, cue_offset + 8), WORD_AT(cue_table, cue_offset + 12), (s32) HALF_AT(cue_descriptor, 0x12), (s32) BYTE_AT(cue_descriptor, 0x11));
                    } else if (WORD_AT(cue_table, cue_offset + 4) == cue_tick) {
                        register u32 stop_offset __asm__("r0") = cue_index;
                        __asm__("" : "+r"(stop_offset));
                        stop_offset *= cue_object_stride;
                        StopCueObject(snapshot_45 + (stop_offset + 0xC9F4));
                    }
                    {
                        register u32 advance_offset __asm__("r1") = cue_index;
                        __asm__("" : "+r"(advance_offset));
                        advance_offset *= cue_object_stride;
                        AdvanceCueObject(scene_workspace + (advance_offset + 0xC9F4));
                    }
                    cue_index += 1;
                } while ((u32) cue_index <= 4U);
            }
        }
        snapshot_46 = scene_workspace;
        if (BYTE_AT(snapshot_46, 0x91D0) != 0) {
            BYTE_AT((scene_workspace), 0x91D0) = AdvanceSceneCue(snapshot_46 + 0x916C, snapshot_46 + 0x916D, snapshot_46 + 0x8FDC, snapshot_46 + 0x8FE0);
        }
        snapshot_47 = scene_workspace;
        if (BYTE_AT(snapshot_47, 0x91D1) != 0) {
            QueueTransition(BeginSavedTransition(1, 0xEF, 0x1E, snapshot_47 + 0x8BDA));
            QueueTransition(BeginSavedTransition(0xFF, 1, 0x1E, scene_workspace + 0x8DD6));
            QueueTransition(BeginSavedTransition(0xF0, 0xF, 0x1E, scene_workspace + 0x8DB8));
            BYTE_AT((scene_workspace), 0x91D1) = 0U;
        }
        snapshot_32 = scene_workspace;
        if (BYTE_AT(snapshot_32, 0x91D2) != 0) {
            BYTE_AT((scene_workspace), 0x91D2) = AdvanceCoordinateCue(0, 0x12C, (u16)WORD_AT(snapshot_32, 0x8FE4), -80, -8, -0x50, 0x68);
            snapshot_26 = scene_workspace;
            WORD_AT(snapshot_26, 0x8FE4) = (s32) ((s32) WORD_AT(snapshot_26, 0x8FE4) + 1);
        }
        if (BYTE_AT((scene_workspace), 0x91D3) != 0) {
            register u32 cleared __asm__("r4");
            register u8 *clear_address __asm__("r0");
            if ((ReadSceneFlag(0x44) << 0x18) == 0) {
                ShowSceneText(0x2A);
            }
            clear_address = scene_workspace + 0x91D3;
            cleared = 0;
            /* Both actual values first meet at the following store. */
            __asm__("" : "+r"(clear_address), "+r"(cleared));
            *clear_address = cleared;
            SetOwnerActive(scene_workspace + 0x94C0, 1);
            InitializeOwner(scene_workspace + 0x94C0, (const void *)0x083A8FE0, 0, 0x2BC, 0x19, cleared, cleared, cleared, 2, -1, cleared, cleared);
            BindOwnerSequence(scene_workspace + 0x94C0, (const void *)0x083A8EAC);
        }
        if (BYTE_AT((scene_workspace), 0x91D4) != 0) {
            QueueTransition(BeginTransition(1, 0xEF, 0x19));
            BYTE_AT((scene_workspace), 0x91D4) = 0U;
        }
        if (BYTE_AT((scene_workspace), 0x91D5) != 0) {
            SceneOperation_13fc24();
            BYTE_AT((scene_workspace), 0x91D5) = 0U;
        }
        if (BYTE_AT((scene_workspace), 0x91D6) != 0) {
            SceneOperation_13fc8c();
            QueueTransition(BeginSavedTransition(1, 0xEF, 0x19, scene_workspace + 0x8BDA));
            InitializeOwner(scene_workspace + 0xA67C, (const void *)0x083A8FE8, 6, 0x2BC, 0x19, 4, 1, 2, 2, -1, 0, 0);
            SetOwnerActive(scene_workspace + 0xA67C, 1);
            BYTE_AT((scene_workspace), 0x91D6) = 0U;
        }
        snapshot_27 = scene_workspace;
        if (BYTE_AT(snapshot_27, 0x91D7) != 0) {
            BYTE_AT((scene_workspace), 0x91D7) = AdvanceCoordinateCue(0, 0xF0, (u16)WORD_AT(snapshot_27, 0x8FE8), -72, -8, -0x48, 0x68);
            snapshot_28 = scene_workspace;
            WORD_AT(snapshot_28, 0x8FE8) = (s32) ((s32) WORD_AT(snapshot_28, 0x8FE8) + 1);
        }
        snapshot_29 = scene_workspace;
        if (BYTE_AT(snapshot_29, 0x91D8) != 0) {
            ConfigureRectangle(snapshot_29 + 0x8B8C, (const void *)0x083A9010, 0x32);
            BYTE_AT((scene_workspace), 0x91D8) = 0U;
        }
        if (BYTE_AT((scene_workspace), 0x91D9) != 0) {
            register u8 **stop_cell __asm__("r5");
            register u32 stop_stride __asm__("r4");
            stop_index = 0;
            stop_cell = &scene_workspace;
            stop_stride = 0x4C;
            /* Independent native preheader definitions, all initialized
             * before their first consumers in the stop loop. */
            __asm__("" : "+r"(stop_index), "+r"(stop_cell), "+r"(stop_stride));
            do {
                StopCueObject((*stop_cell) + ((stop_index * stop_stride) + 0xC9F4));
                {
                    register u32 next_stop __asm__("r0");
                    next_stop = stop_index + 1; __asm__("" : "+r"(next_stop));
                    stop_index = (u8)next_stop;
                }
            } while ((u32) stop_index <= 4U);
            ResetSceneResources();
            QueueTransition(BeginTransitionVariant(0x170, 0x50, 0xA));
            QueueTransition(BeginTransitionVariant(1, 0xEF, 0xA));
            QueueTransition(BeginTransitionVariant(0x160, 0x10, 0xA));
            BYTE_AT((scene_workspace), 0x91D9) = 0U;
        }
        if (BYTE_AT((scene_workspace), 0x91DA) == 0) {

        } else {
            register u16 *fill_target __asm__("r0");
            register u32 fill_zero __asm__("r5");
            fill_target = &first_fill; __asm__("" : "+r"(fill_target));
            fill_zero = 0; __asm__("" : "+r"(fill_zero));
            *fill_target = fill_zero;
            CopyHalfwords(fill_target, scene_palette_buffer, 0x01000100);
            second_fill = fill_zero;
            CopyHalfwords(&second_fill, scene_palette_buffer + 512, 0x01000100);
            SetOwnerActive(scene_workspace + 0x94C0, 0);
            SetOwnerActive(scene_workspace + 0xA67C, 0);
            *state_slot = 2;
        }
        break;
    case 0x2:{
        register void **clear_cell __asm__("r4");
        register void *clear_fn __asm__("r2");
        register u8 *clear_target __asm__("r0");
        SetRectangleActive(scene_workspace + 0x8B8C, 0);
        SetRectangleActive(scene_workspace + 0x8BB0, 0);
        clear_cell=&clear_callback; __asm__("" : "+r"(clear_cell));
        CallClearViaR2(scene_workspace + 0x8FDC, 0x190, *clear_cell);
        clear_target = scene_workspace + 0x916C; __asm__("" : "+r"(clear_target));
        clear_fn = *clear_cell; __asm__("" : "+r"(clear_fn));
        CallClearViaR2(clear_target, 0x64, clear_fn);
        clear_target = scene_workspace + 0x91D0; __asm__("" : "+r"(clear_target));
        clear_fn = *clear_cell; __asm__("" : "+r"(clear_fn));
        CallClearViaR2(clear_target, 0x64, clear_fn);
        clear_target = scene_workspace + 0x8B6C; __asm__("" : "+r"(clear_target));
        clear_fn = *clear_cell; __asm__("" : "+r"(clear_fn));
        CallClearViaR2(clear_target, 0x14, clear_fn);
        ResetSceneResources();
        SceneOperation_13f438();
        SceneOperation_13f794();
        SetOwnerState(scene_workspace + 0x94C0, 0);
        Cue(9);
        InitializeOwner(scene_workspace + 0xA67C, (const void *)0x083A9018, 6, 0xFA, 0x32, 4, 1, 1, (s32) entry_phase, -1, 0, 0);
        ConfigureOwnerMotion(scene_workspace + 0xA67C, 0x64, 0x46, 0x100, 0x10);
        *state_slot = 3;
        break;}
    case 0x3:
        event_index = 0; __asm__("" : "+r"(event_index));
        do {
            snapshot_33 = scene_workspace;
            if ((WORD_AT(snapshot_33, 0x8FD8) == cue_timestamps[event_index]) && ((BYTE_AT(snapshot_33, 0x9234) == 0) || (cue_selectors[event_index] == 0))) {
                register u8 *event_flag_base __asm__("r0") = snapshot_33 + 0x91D0;
                event_flag_base[event_index] = 1;
            }
            {
                /* Actual native pre-truncation R0 value; no empty template. */
                register u32 next_event __asm__("r0") = event_index + 1;
                event_index = (u8) next_event;
            }
        } while ((u32) event_index <= 0x27U);
        snapshot_30 = scene_workspace;
        if (BYTE_AT(snapshot_30, 0x91D0) != 0) {
            BindRectangle(snapshot_30 + 0x8B8C, (const void *)0x083A9018, 0);
            SetOwnerActive(scene_workspace + 0xA67C, 1);
            ConfigureTransition(scene_workspace + 0x8B84, 0x10, 0, 0xD1, 0x3C);
            BYTE_AT((scene_workspace), 0x91D0) = 0U;
        }
        snapshot_4 = scene_workspace;
        if (BYTE_AT(snapshot_4, 0x91D1) != 0) {
            InitializeRectangle(snapshot_4 + 0x8B8C, (const void *)0x083A9018, 0, 0);
            ConfigureRectangle(scene_workspace + 0x8B8C, (const void *)0x083A9020, 0xB4);
            BYTE_AT((scene_workspace), 0x91D1) = 0U;
        }
        snapshot_5 = scene_workspace;
        if (BYTE_AT(snapshot_5, 0x91D3) != 0) {
            ConfigureTransition(snapshot_5 + 0x8B84, 0, 0x10, 0xD1, 0x28);
            BYTE_AT((scene_workspace), 0x91D3) = 0U;
        }
        snapshot_6 = scene_workspace;
        if (BYTE_AT(snapshot_6, 0x91D2) != 0) {
            ReadRectangle(snapshot_6 + 0x8B8C, &rectangle);
            rectangle.left = (u16) (rectangle.left - 0x10);
            rectangle.top = (u16) (rectangle.top - 0x10);
            rectangle.right = (u16) (rectangle.right + 0x10);
            rectangle.bottom = (u16) (rectangle.bottom + 0x10);
            SetOwnerRectangle(scene_workspace + 0xA67C, &rectangle);
        }
        snapshot_7 = scene_workspace;
        if (BYTE_AT(snapshot_7, 0x91D4) != 0) {
            register void **buffer_callback_cell __asm__("r2");
            register u32 cleared_pair __asm__("r1");
            register u8 *first_flag __asm__("r0");
            SetOwnerActive(snapshot_7 + 0xA67C, 0);
            buffer_callback_cell = &clear_callback;
            CallClearViaR2(scene_buffers.first, 0x800, *buffer_callback_cell);
            first_flag=scene_workspace + 0x91D4;
            cleared_pair=0;
            /* Same actual initialized base/zero consumers; one estimated insn. */
            __asm__("" : "+r"(first_flag), "+r"(cleared_pair));
            *first_flag = cleared_pair;
            BYTE_AT((scene_workspace), 0x91D2) = cleared_pair;
            SetRectangleActive(scene_workspace + 0x8B8C, cleared_pair);
        }
        if (BYTE_AT((scene_workspace), 0x91D5) != 0) {
            SetAuthoredSelector(0);
            BYTE_AT((scene_workspace), 0x91D5) = 0U;
        }
        if (BYTE_AT((scene_workspace), 0x91D6) != 0) {
            SetAuthoredSelector(1);
            BYTE_AT((scene_workspace), 0x91D6) = 0U;
        }
        if (BYTE_AT((scene_workspace), 0x91D7) != 0) {
            SetAuthoredSelector(3);
            BYTE_AT((scene_workspace), 0x91D7) = 0U;
        }
        if (BYTE_AT((scene_workspace), 0x91D8) != 0) {
            SetAuthoredSelector(4);
            BYTE_AT((scene_workspace), 0x91D8) = 0U;
        }
        if (BYTE_AT((scene_workspace), 0x91D9) != 0) {
            SetAuthoredSelector(2);
            BYTE_AT((scene_workspace), 0x91D9) = 0U;
        }
        if (BYTE_AT((scene_workspace), 0x91DA) != 0) {
            SceneOperation_13fcf0();
            Cue(2);
            InitializeOwner(scene_workspace + 0xB838, (const void *)0x083A8FF0, 6, 0xFA, 0x19, 4, 1, 1, 2, 1, 0x88, 0x10);
            ConfigureOwnerMotion(scene_workspace + 0xB838, 0x64, 0x46, 0x100, 0xC);
            SetOwnerActive(scene_workspace + 0xB838, 1);
            InitializeRectangle(scene_workspace + 0x8BB0, (const void *)0x083A9028, 1, 0);
            BindRectangle(scene_workspace + 0x8BB0, (const void *)0x083A9028, 0);
            ConfigureTransition(scene_workspace + 0x8B84, 0x10, 0, 0xD2, 0x28);
            SHADOW_B(66) &= 0xDF;
            SHADOW_B(67) |= 0x20;
            BYTE_AT((scene_workspace), 0x91DA) = 0U;
        }
        snapshot_8 = scene_workspace;
        if (BYTE_AT(snapshot_8, 0x91DB) != 0) {
            BYTE_AT((scene_workspace), 0x91DB) = AdvanceCoordinateCue(1, 0xB4, (u16)WORD_AT(snapshot_8, 0x8FE0), -0x88, -0x10, -0x60, 0x18);
            snapshot_9 = scene_workspace;
            WORD_AT(snapshot_9, 0x8FE0) = (s32) ((s32) WORD_AT(snapshot_9, 0x8FE0) + 1);
        }
        snapshot_10 = scene_workspace;
        if (BYTE_AT(snapshot_10, 0x91DC) != 0) {
            ConfigureTransition(snapshot_10 + 0x8B84, 0, 0x10, 0xD2, 0x28);
            SHADOW_B(66) = (u8) (0xDF & SHADOW_B(66));
            SHADOW_B(67) = (u8) (0x20 | SHADOW_B(67));
            BYTE_AT((scene_workspace), 0x91DC) = 0U;
        }
        snapshot_11 = scene_workspace;
        if (BYTE_AT(snapshot_11, 0x91DD) != 0) {
            register void **buffer_callback_cell __asm__("r2");
            SetOwnerActive(snapshot_11 + 0xB838, 0);
            buffer_callback_cell = &clear_callback; __asm__("" : "+r"(buffer_callback_cell));
            CallClearViaR2(scene_buffers_second.first, 0x800, *buffer_callback_cell);
            BYTE_AT((scene_workspace), 0x91DD) = 0U;
            SetRectangleActive(scene_workspace + 0x8BB0, 0);
        }
        if (BYTE_AT((scene_workspace), 0x91DE) != 0) {
            SetAuthoredSelector(5);
            BYTE_AT((scene_workspace), 0x91DE) = 0U;
        }
        if (BYTE_AT((scene_workspace), 0x91DF) != 0) {
            SetAuthoredSelector(6);
            BYTE_AT((scene_workspace), 0x91DF) = 0U;
        }
        snapshot_12 = scene_workspace;
        if (BYTE_AT(snapshot_12, 0x91E0) != 0) {
            SetOwnerMode(snapshot_12 + 0x8364, 2);
            BYTE_AT((scene_workspace), 0x91E0) = 0U;
        }
        if (BYTE_AT((scene_workspace), 0x91E1) != 0) {
            SceneOperation_13f898();
            Cue(2);
            InitializeOwner(scene_workspace + 0xA67C, (const void *)0x083A8FF8, 6, 0xFA, 0x19, 4, 1, 1, 2, 0, 0x20, 0x28);
            ConfigureOwnerMotion(scene_workspace + 0xA67C, 0x64, 0x46, 0x100, 0xC);
            SetOwnerActive(scene_workspace + 0xA67C, 1);
            InitializeRectangle(scene_workspace + 0x8B8C, (const void *)0x083A9030, 0, 0);
            BindRectangle(scene_workspace + 0x8B8C, (const void *)0x083A9030, 0);
            ConfigureTransition(scene_workspace + 0x8B84, 0x10, 0, 0xD1, 0x28);
            SHADOW_B(67) = (u8) (0xDF & SHADOW_B(67));
            SHADOW_B(66) = (u8) (0x20 | SHADOW_B(66));
            BYTE_AT((scene_workspace), 0x91E1) = 0U;
        }
        snapshot_13 = scene_workspace;
        if (BYTE_AT(snapshot_13, 0x91E2) != 0) {
            BYTE_AT((scene_workspace), 0x91E2) = AdvanceCoordinateCue(0, 0xF0, (u16)WORD_AT(snapshot_13, 0x8FE4), -32, -0x28, -0x20, 8);
            snapshot_15 = scene_workspace;
            WORD_AT(snapshot_15, 0x8FE4) = (s32) ((s32) WORD_AT(snapshot_15, 0x8FE4) + 1);
        }
        snapshot_34 = scene_workspace;
        if (BYTE_AT(snapshot_34, 0x91E3) != 0) {
            SHADOW_B(67) = (u8) (0xDF & SHADOW_B(67));
            SHADOW_B(66) = (u8) (SHADOW_B(66) | 0x20);
            ConfigureTransition(snapshot_34 + 0x8B84, 0, 0x10, 0xD1, 0x28);
            SHADOW_B(67) = (u8) (SHADOW_B(67) | 0x20);
            SHADOW_B(66) = (u8) (SHADOW_B(66) | 0x20);
            BYTE_AT((scene_workspace), 0x91E3) = 0U;
        }
        snapshot_16 = scene_workspace;
        if (BYTE_AT(snapshot_16, 0x91E4) != 0) {
            register void **buffer_callback_cell __asm__("r2");
            SetOwnerActive(snapshot_16 + 0xA67C, 0);
            SetRectangleActive(scene_workspace + 0x8B8C, 0);
            buffer_callback_cell = &clear_callback;
            CallClearViaR2(scene_buffers.first, 0x800, *buffer_callback_cell);
            BYTE_AT((scene_workspace), 0x91E4) = 0U;
        }
        if (BYTE_AT((scene_workspace), 0x91E5) != 0) {
            SetAuthoredSelector(7);
            BYTE_AT((scene_workspace), 0x91E5) = 0U;
        }
        if (BYTE_AT((scene_workspace), 0x91E6) != 0) {
            SetAuthoredSelector(8);
            BYTE_AT((scene_workspace), 0x91E6) = 0U;
        }
        if (BYTE_AT((scene_workspace), 0x91E7) != 0) {
            SceneOperation_13f934();
            Cue(0xB);
            InitializeOwner(scene_workspace + 0xB838, (const void *)0x083A9000, 6, 0xFA, 0x32, 4, 1, 1, 2, 1, 0x58, 8);
            ConfigureOwnerMotion(scene_workspace + 0xB838, 0x64, 0x46, 0x100, 0x10);
            SetOwnerActive(scene_workspace + 0xB838, 1);
            InitializeRectangle(scene_workspace + 0x8BB0, (const void *)0x083A9038, 1, 0);
            BindRectangle(scene_workspace + 0x8BB0, (const void *)0x083A9038, 0);
            ConfigureTransition(scene_workspace + 0x8B84, 0x10, 0, 0xD2, 0x3C);
            BYTE_AT((scene_workspace), 0x91E7) = 0U;
        }
        snapshot_17 = scene_workspace;
        if (BYTE_AT(snapshot_17, 0x91E8) != 0) {
            BYTE_AT((scene_workspace), 0x91E8) = AdvanceCoordinateCue(1, 0xF0, (u16)WORD_AT(snapshot_17, 0x8FE8), -0x58, -8, -0x68, -0x20);
            snapshot_18 = scene_workspace;
            WORD_AT(snapshot_18, 0x8FE8) = (s32) ((s32) WORD_AT(snapshot_18, 0x8FE8) + 1);
        }
        snapshot_19 = scene_workspace;
        if (BYTE_AT(snapshot_19, 0x91E9) != 0) {
            ConfigureTransition(snapshot_19 + 0x8B84, 0, 0x10, 0xD2, 0x3C);
            BYTE_AT((scene_workspace), 0x91E9) = 0U;
        }
        snapshot_20 = scene_workspace;
        if (BYTE_AT(snapshot_20, 0x91EA) != 0) {
            register void **buffer_callback_cell __asm__("r2");
            SetOwnerActive(snapshot_20 + 0xB838, 0);
            SetRectangleActive(scene_workspace + 0x8BB0, 0);
            buffer_callback_cell = &clear_callback;
            CallClearViaR2(scene_buffers_second.first, 0x800, *buffer_callback_cell);
            BYTE_AT((scene_workspace), 0x91EA) = 0U;
        }
        if (BYTE_AT((scene_workspace), 0x91EB) != 0) {
            SetAuthoredSelector(9);
            BYTE_AT((scene_workspace), 0x91EB) = 0U;
        }
        if (BYTE_AT((scene_workspace), 0x91EC) != 0) {
            SetAuthoredSelector(0xA);
            BYTE_AT((scene_workspace), 0x91EC) = 0U;
        }
        if (BYTE_AT((scene_workspace), 0x91ED) != 0) {
            SetAuthoredSelector(0xB);
            BYTE_AT((scene_workspace), 0x91ED) = 0U;
        }
        if (BYTE_AT((scene_workspace), 0x91EE) != 0) {
            SetAuthoredSelector(0xC);
            BYTE_AT((scene_workspace), 0x91EE) = 0U;
        }
        if (BYTE_AT((scene_workspace), 0x91EF) != 0) {
            SceneOperation_13f9f8();
            BYTE_AT((scene_workspace), 0x91EF) = 0U;
        }
        snapshot_21 = scene_workspace;
        if (BYTE_AT(snapshot_21, 0x91F0) != 0) {
            InitializeRectangle(snapshot_21 + 0x8B8C, (const void *)0x083A9040, 0, 0);
            ConfigureRectangle(scene_workspace + 0x8B8C, (const void *)0x083A9048, 0xB4);
            ConfigureTransition(scene_workspace + 0x8B84, 0x10, 0, 0xD1, 0x64);
            BYTE_AT((scene_workspace), 0x91F0) = 0U;
        }
        if (BYTE_AT((scene_workspace), 0x91F2) != 0) {
            SceneOperation_13faa0();
            BYTE_AT((scene_workspace), 0x91F2) = 0U;
        }
        if (BYTE_AT((scene_workspace), 0x91F3) != 0) {
            ActivateTransition(BeginTransition(0, 0x60, 0x3C));
            ActivateTransition(BeginTransition(0x100, 0x60, 0x3C));
            ActivateTransition(BeginTransition(0x190, 0x30, 0x3C));
            ActivateTransition(BeginTransition(0xFE, 1, 0x3C));
            SetOwnerMode(scene_workspace + 0x8874, 2);
            InitializeRectangle(scene_workspace + 0x8B8C, (const void *)0x083A9048, 0, 0);
            ConfigureRectangle(scene_workspace + 0x8B8C, (const void *)0x083A9050, 0x3C);
            BYTE_AT((scene_workspace), 0x91F3) = 0U;
        }
        snapshot_22 = scene_workspace;
        if (BYTE_AT(snapshot_22, 0x91F1) != 0) {
            BYTE_AT((scene_workspace), 0x91F1) = AdvanceCoordinateCue(0, 0xB4, (u16)WORD_AT(snapshot_22, 0x9004), -0xA, -0x28, -0x40, -0x18);
            snapshot_23 = scene_workspace;
            WORD_AT(snapshot_23, 0x9004) = (s32) ((s32) WORD_AT(snapshot_23, 0x9004) + 1);
        }
        if (BYTE_AT((scene_workspace), 0x91F4) != 0) {
            SetAuthoredSelector(0xD);
            BYTE_AT((scene_workspace), 0x91F4) = 0U;
        }
        if (BYTE_AT((scene_workspace), 0x91F6) != 0) {
            SetAuthoredSelector(0xF);
            BYTE_AT((scene_workspace), 0x91F6) = 0U;
        }
        if (BYTE_AT((scene_workspace), 0x91F5) != 0) {
            SetAuthoredSelector(0xE);
            BYTE_AT((scene_workspace), 0x91F5) = 0U;
        }
        if (BYTE_AT((scene_workspace), 0x91F7) != 0) {
            *state_slot = 0xFF;
            BYTE_AT((scene_workspace), 0x91F7) = 0U;
        }
        break;
    case 0x4:
        local_exit_flag = 1;
        ResetSceneResources();
        scene_mode = 0xFF;
        ReleaseSceneWorkspace(scene_workspace);
        RemoveHook(0);
        RemoveHook(3);
        ReleaseSceneTask((void *)0x0200F3A0);
        break;
    case 0xFF:
        ResetSceneResources();
        scene_mode = 2;
        ReleaseSceneWorkspace(scene_workspace);
        RemoveHook(0);
        RemoveHook(3);
        ReleaseSceneTask((void *)0x0200F3A0);
        break;
    }
    DrawOwner(scene_workspace + 0x94C0, 0x64, 0x40, 0x100);
    DrawOwner(scene_workspace + 0xA67C, 0x64, 0x46, 0x100);
    DrawOwner(scene_workspace + 0xB838, 0x64, 0x46, 0x100);
    RefreshSceneAux();
    AdvanceRectangle(scene_workspace + 0x8B8C);
    AdvanceRectangle(scene_workspace + 0x8BB0);
    snapshot_35 = scene_workspace;
    WORD_AT(snapshot_35, 0x8FD8) = (s32) (WORD_AT(snapshot_35, 0x8FD8) + 1);
    if (BYTE_AT(snapshot_35, 0x9234) == 0) {
        if (8 & scene_input_state.pressed) {
            connected = ReadSceneConnection();
            if (connected == 1) {
                flag_value = ReadSceneFlag(0x44);
                if (flag_value == 0) {
                    ResetSceneResources();
                    skip_transition = BeginTransition(0, 0x200, 8);
                    WORD_AT(scene_workspace, 0x9238) = (u32)skip_transition;
                    QueueTransition(skip_transition);
                    SetTransitionMode(scene_workspace + 0x8B84, 0);
                    {
                        register struct DisplayShadow *shadow_base __asm__("r0") = SHADOW;
                        __asm__("" : "+r"(shadow_base));
                        shadow_base->b78 = flag_value;
                    }
                    snapshot_1 = scene_workspace;
                    HALF_AT(snapshot_1, 0x8B80) = (u16) flag_value;
                    BYTE_AT(snapshot_1, 0x9234) = connected;
                }
            }
        }
    } else {
        skip_delay = HALF_AT(snapshot_35, 0x8B80) + 1;
        HALF_AT(snapshot_35, 0x8B80) = skip_delay;
        if ((u16) skip_delay > 7U) {
            *state_slot = 4;
        }
    }
    AdvanceTransition(scene_workspace + 0x8B84);
}

asm(".global scene_palette_buffer\n.set scene_palette_buffer,0x03003860\n.global Cue\n.thumb_set Cue,0x08002825\n.global RemoveHook\n.thumb_set RemoveHook,0x08000d91\n.global ReleaseSceneTask\n.thumb_set ReleaseSceneTask,0x08006b9d\n.global ReadSceneFlag\n.thumb_set ReadSceneFlag,0x080c9541\n.global RequestSceneWorkspace\n.thumb_set RequestSceneWorkspace,0x0813c0c5\n.global ReleaseSceneWorkspace\n.thumb_set ReleaseSceneWorkspace,0x0813c0d9\n.global SetAuthoredSelector\n.thumb_set SetAuthoredSelector,0x0813d4a1\n.global RefreshSceneAux\n.thumb_set RefreshSceneAux,0x0813d519\n.global AdvanceSceneCue\n.thumb_set AdvanceSceneCue,0x0813d6a1\n.global QueueTransition\n.thumb_set QueueTransition,0x0813dafd\n.global AdvanceRectangle\n.thumb_set AdvanceRectangle,0x0813db45\n.global AdvanceCoordinateCue\n.thumb_set AdvanceCoordinateCue,0x0813dd59\n.global ConfigureOwnerMotion\n.thumb_set ConfigureOwnerMotion,0x0813e1dd\n.global DrawOwner\n.thumb_set DrawOwner,0x0813e349\n.global BeginCueObject\n.thumb_set BeginCueObject,0x0813e9f5\n.global AdvanceCueObject\n.thumb_set AdvanceCueObject,0x0813ead5\n.global AdvanceTransition\n.thumb_set AdvanceTransition,0x0813eb65\n.global InitializeRectangle\n.thumb_set InitializeRectangle,0x0813ebc1\n.global ConfigureRectangle\n.thumb_set ConfigureRectangle,0x0813ec05\n.global BindRectangle\n.thumb_set BindRectangle,0x0813ec29\n.global SetRectangleActive\n.thumb_set SetRectangleActive,0x0813ec5d\n.global ReadRectangle\n.thumb_set ReadRectangle,0x0813ec65\n.global SetOwnerMode\n.thumb_set SetOwnerMode,0x0813ee19\n.global InitializeOwner\n.thumb_set InitializeOwner,0x0813ee21\n.global BindOwnerSequence\n.thumb_set BindOwnerSequence,0x0813eef9\n.global SetOwnerState\n.thumb_set SetOwnerState,0x0813ef2d\n.global SetOwnerActive\n.thumb_set SetOwnerActive,0x0813ef35\n.global SetOwnerRectangle\n.thumb_set SetOwnerRectangle,0x0813ef39\n.global InitializeCueObject\n.thumb_set InitializeCueObject,0x0813f125\n.global StopCueObject\n.thumb_set StopCueObject,0x0813f12d\n.global InitializeTransition\n.thumb_set InitializeTransition,0x0813f135\n.global SetTransitionMode\n.thumb_set SetTransitionMode,0x0813f13d\n.global ConfigureTransition\n.thumb_set ConfigureTransition,0x0813f141\n.global ShowSceneText\n.thumb_set ShowSceneText,0x081416dd\n.global ReadSceneConnection\n.thumb_set ReadSceneConnection,0x0814180d\n.global CopyHalfwords\n.thumb_set CopyHalfwords,0x0814186d\n.global CallClearViaR2\n.thumb_set CallClearViaR2,0x0814224d\n.global BeginTransitionVariant\n.thumb_set BeginTransitionVariant,0x08147a7d\n.global BeginTransition\n.thumb_set BeginTransition,0x08147ad1\n.global BeginSavedTransition\n.thumb_set BeginSavedTransition,0x08147d2d\n.global ResetSceneResources\n.thumb_set ResetSceneResources,0x08148541\n.global ActivateTransition\n.thumb_set ActivateTransition,0x08148601\n.global SceneOperation_13f438\n.thumb_set SceneOperation_13f438,0x0813f439\n.global SceneOperation_13f794\n.thumb_set SceneOperation_13f794,0x0813f795\n.global SceneOperation_13fc24\n.thumb_set SceneOperation_13fc24,0x0813fc25\n.global SceneOperation_13fc8c\n.thumb_set SceneOperation_13fc8c,0x0813fc8d\n.global SceneOperation_1457fc\n.thumb_set SceneOperation_1457fc,0x081457fd\n.global SceneOperation_13f22c\n.thumb_set SceneOperation_13f22c,0x0813f22d\n.global SceneOperation_13f604\n.thumb_set SceneOperation_13f604,0x0813f605\n.global SceneOperation_13fcf0\n.thumb_set SceneOperation_13fcf0,0x0813fcf1\n.global SceneOperation_13f898\n.thumb_set SceneOperation_13f898,0x0813f899\n.global SceneOperation_13f934\n.thumb_set SceneOperation_13f934,0x0813f935\n.global SceneOperation_13f9f8\n.thumb_set SceneOperation_13f9f8,0x0813f9f9\n.global SceneOperation_13faa0\n.thumb_set SceneOperation_13faa0,0x0813faa1\n.global scene_workspace\n.set scene_workspace,0x0200f3b0\n.global clear_callback\n.set clear_callback,0x0836d4b8\n.global scene_mode\n.set scene_mode,0x0200f390\n.global local_exit_flag\n.set local_exit_flag,0x0300280c\n.global pressed_keys\n.set pressed_keys,0x03000002\n.global cue_table\n.set cue_table,0x083a8efc\n.global cue_selectors\n.set cue_selectors,0x083a9218\n.global cue_timestamps\n.set cue_timestamps,0x083a9240\n");
