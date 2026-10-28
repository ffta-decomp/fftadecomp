typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
struct BattleMarkerNode { void *object; u8 active, x, y, scaled_value; struct BattleMarkerNode *next; };
struct BattleMarkerState { struct BattleMarkerNode *head; struct BattleMarkerNode nodes[13]; u8 counter; };
typedef char marker_state_size[(sizeof(struct BattleMarkerState)==164)?1:-1];
typedef void (*MarkerFlagsFunction)(void *, int);
typedef u32 (*MarkerDescriptorFunction)(void *, const void *);
typedef void (*MarkerFieldsFunction)(void *, u32, u32, u32, u32, u32);
extern MarkerFlagsFunction MarkerFlagsCell;
extern MarkerDescriptorFunction MarkerDescriptorCell;
extern MarkerFieldsFunction MarkerFieldsCell;
extern void (*const MarkerClearCell)(void *, u32);
extern void (*const MarkerCopyCell)(void *, const void *, u32);
extern u16 MarkerPalette[];
extern const u8 MarkerObjectDescriptor[];
extern void *AllocateMarkerState_08022840(u32);
extern void *CreateMarkerWorkObject_0808F79C(void);
extern const u8 *GetMarkerPalette_080CBABC(u32);
struct BattleMarkerState *CreateBattleFrameMarkerState(void)
{
    struct BattleMarkerState *state;
    MarkerDescriptorFunction *descriptor_cell;
    MarkerFieldsFunction *fields_cell;
    register u32 offset asm("r6");
    register int remaining asm("r5");
    const u8 *palette;
    void (*const *copy_cell)(void *, const void *, u32);
    u16 *destination;
    state = AllocateMarkerState_08022840(164);
    MarkerClearCell(state, 164);
    descriptor_cell = &MarkerDescriptorCell;
    fields_cell = &MarkerFieldsCell;
    /* Exact original loop initializer: real defined outputs, no shadow cursor. */
    asm("mov %0, #0\n\tmov %1, #12" : "=r"(offset), "=r"(remaining));
    do {
        void *object;
        struct BattleMarkerNode *node;
        object = CreateMarkerWorkObject_0808F79C();
        node = state->nodes;
        /* Preserve the two observed independent address inputs. */
        asm("" : "+r"(node), "+r"(offset));
        node = (struct BattleMarkerNode *)((u8 *)node + offset);
        node->object = object;
        MarkerFlagsCell(object, -127);
        (*descriptor_cell)(node->object, MarkerObjectDescriptor);
        (*fields_cell)(node->object, 0, 0, 0, 0, 10);
        offset += 12;
    } while (--remaining >= 0);
    copy_cell = &MarkerCopyCell;
    destination = MarkerPalette;
    palette = GetMarkerPalette_080CBABC(4);
    (*copy_cell)(destination, palette + 4, 14);
    return state;
}
asm(".set MarkerFlagsCell, 0x08394040\n");
asm(".set MarkerDescriptorCell, 0x08394038\n");
asm(".set MarkerFieldsCell, 0x08394034\n");
asm(".set MarkerClearCell, 0x0836d4b8\n");
asm(".set MarkerCopyCell, 0x0836d4bc\n");
asm(".set MarkerPalette, 0x03003ba4\n");
asm(".set MarkerObjectDescriptor, 0x0839168c\n");
asm(".thumb_set AllocateMarkerState_08022840, 0x08022841\n");
asm(".thumb_set CreateMarkerWorkObject_0808F79C, 0x0808f79d\n");
asm(".thumb_set GetMarkerPalette_080CBABC, 0x080cbabd\n");
asm(".thumb_set _call_via_r2, 0x0814224d\n");
asm(".thumb_set _call_via_r3, 0x08142251\n");
asm(".thumb_set _call_via_r4, 0x08142255\n");
