typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;
typedef signed int s32;
typedef union SceneMotionFirstWord {
    struct { u32 selector : 8; u32 unused : 24; } selector_view;
    struct { u8 selector, mode; s16 delta_x; } fields;
    u32 word;
} SceneMotionFirstWord;
typedef union SceneMotionSecondWord {
    struct { s16 delta_y; u16 argument; } fields;
    u32 word;
} SceneMotionSecondWord;
typedef char first_word_size[sizeof(SceneMotionFirstWord)==4 ? 1:-1];
typedef char second_word_size[sizeof(SceneMotionSecondWord)==4 ? 1:-1];
extern void ComputeSceneMotionDeltas(u32, s32, s32, s16 *, s16 *);
extern void CreateSceneMotionTask(void *, u32, u32);

typedef struct SceneMotionPayload {
    SceneMotionFirstWord first;
    SceneMotionSecondWord second;
} SceneMotionPayload;

/* The constructor copies the physical first word, then replaces only selector. */
static inline SceneMotionFirstWord WithMotionSelector(u8 selector, SceneMotionFirstWord first)
{
    first.selector_view.selector = selector;
    return first;
}

u32 Scene51_00123398(void *context, const u8 *command)
{
    SceneMotionPayload payload;
    u32 selector = command[1];
    u32 preserve_upper_bytes = 0xffffff00u;
    /* The original prepares selector and its preserve mask before copying the
       physical word. Both are initialized inputs; this emits no instructions. */
    asm("" : : "r"(selector), "r"(preserve_upper_bytes));
    payload.first = WithMotionSelector(selector, payload.first);
    ComputeSceneMotionDeltas(payload.first.fields.selector,
                             (s8)command[2], (s8)command[3],
                             &payload.first.fields.delta_x, &payload.second.fields.delta_y);
    payload.first.fields.mode = command[4];
    payload.second.fields.argument = command[5] | ((u32)command[6] << 8);
    CreateSceneMotionTask(context, payload.first.word, payload.second.word);
    return 0x115;
}
asm(".global ComputeSceneMotionDeltas\n.thumb_set ComputeSceneMotionDeltas,0x08124e75\n"
    ".global CreateSceneMotionTask\n.thumb_set CreateSceneMotionTask,0x08127b81");
