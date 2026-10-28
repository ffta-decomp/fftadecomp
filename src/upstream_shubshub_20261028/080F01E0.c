/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/080F01E0.c
 * Original SHA-256: 2963fcde491a87e705b1b797cdfcac4f59bfe72fd9aa957004a822bdb0a18b6b
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;

typedef struct {
    u16 phase;
    u16 unknown_02;
    void *primary;
    u8 unknown_08[14];
    u16 flag;
} Descriptor080F01E0;

typedef struct {
    u16 countdown;
    u8 flag;
    u8 unknown_03;
    s16 x;
    s16 y;
    void *entity;
    void *auxiliary;
    u8 unknown_10[12];
    void *effect;
    void *first_child;
    void *second_child;
    u32 unknown_28;
    void *optional_effect;
    void *resource_child;
    void *stage;
    void *primary;
    void *animation;
    void *result;
} Payload080F01E0;

extern u16 g_control_flags_03000940;
extern u32 func_080035A8(u8 index);
extern void func_080D38B4(void);
extern void *func_080DD4A4(void *primary, u8 index);
extern void *func_080E03F8(void *primary, const void *data, u8 mode,
                          u8 action, void *argument, void *parent);
extern void *func_080E05DC(void *task);
extern u8 func_080D8858(void *primary, u16 flags);
extern void *func_080DD748(void *entity, s16 *x, s16 *y, u32 mode);
extern void *func_080D6098(s16 x, s16 y, u16 third, u8 mode, u16 count,
                          void *output, const void *data, void *parent);
extern void func_080D7220(const void *resource, u8 index, u8 layer,
                          s16 x, s16 y, u16 flags);
extern void *func_080D4704(const void *resource, void *parent);
extern void *func_080D3E9C(const void *resource, void *parent);
extern void *func_080DFD8C(const void *data, u8 mode, u16 third,
                          u16 fourth, void *parent);
extern u8 func_080DD580(void *entity);
extern void *func_080DCFE4(void *entity, const void *data, u8 third,
                          u16 fourth, u16 fifth, void *parent, u16 seventh);
extern void *func_080D3F08(void *task);
extern void *func_080D4774(void *task);
extern void *func_080D6134(void *task);
extern void *func_080DBA5C(void *task);

/* Target: complete [0x080F01E0, 0x080F03D0), 496 bytes.
 * f0b584b0061c0f1c141c3d888020400085422cd0854204dc002d0dd0012d23d0dfe00448854200d17ee00130854200d1aae0d6e001010000f88aa0707868a0630021edf73ff9a0600522a078002800d00022a06b0349009501960123f0f7dcf86063bee0789c3908e3f734fbb9e0606bf0f7c4f9051c6563002d00d0b1e0a06b0021e8f7f9fa0006002800d1a7e0a068211da21d0023edf767fae0600421605e0622a15e03220092221c10320192184a0292039600220123e5f7fefee06115480421635ee1880839090409140091019500210222e6f7b4ff0f48311ce4f722fa20620e48311ce4f71dfa60620c48311ce3f7e4fd20630b480096022104220023eff754fd2064642020803888013067e0b49c39089c468f08bc93940878b094089cd69408289d39082088013820800004002856d1a068edf733f90006002810d00422a05e0622a15e01220092221c283201920b4a0292039600220123e5f7acfee062a06807490222009201960a2202920c220a23ecf746fee063388801302fe0fc9c3908149d3908206be3f7cdfd2063002826d1206ae4f7fdf92062002820d1606ae4f7f7f9606200281ad1022013f70bf90e4a118881431180e069e5f7cafee06100280dd1e06ae5f7c4fee062002807d1e06bebf752fbe063002801d102203880002004b0f0bc02bc084740090003
 */
u32 func_080F01E0(void *task, Descriptor080F01E0 *descriptor,
                  Payload080F01E0 *payload)
{
    u8 mode;

    switch (descriptor->phase) {
    case 0:
        payload->flag = descriptor->flag;
        payload->primary = descriptor->primary;
        payload->entity = func_080DD4A4(payload->primary, 0);
        mode = 5;
        if (payload->flag)
            mode = 0;
        payload->stage = func_080E03F8(payload->primary,
            (const void *)0x08399C78, mode, 1, 0, task);
        break;
    case 1:
        func_080D38B4();
        break;
    case 0x100:
        payload->stage = func_080E05DC(payload->stage);
        if (payload->stage)
            break;
        if (!func_080D8858(payload->primary, 0)) {
            descriptor->phase = 2;
            break;
        }
        payload->auxiliary = func_080DD748(payload->entity,
                                          &payload->x, &payload->y, 0);
        payload->effect = func_080D6098(payload->x, payload->y, 0, 1, 3,
            payload->unknown_10, (const void *)0x08399CB4, task);
        func_080D7220((const void *)0x088F469C, 0, 2,
                      payload->x, (s16)(payload->y - 8), 0);
        payload->first_child = func_080D4704((const void *)0x089493BC, task);
        payload->second_child = func_080D4704((const void *)0x0894B078, task);
        payload->resource_child = func_080D3E9C((const void *)0x0894D69C, task);
        payload->result = func_080DFD8C((const void *)0x08399D28, 2, 4, 0, task);
        payload->countdown = 100;
        descriptor->phase++;
        break;
    case 0x101:
        payload->countdown--;
        if (payload->countdown)
            break;
        if (func_080DD580(payload->entity))
            payload->optional_effect = func_080D6098(payload->x, payload->y,
                0, 1, 1, &payload->unknown_28, (const void *)0x08399CFC, task);
        payload->animation = func_080DCFE4(payload->entity,
            (const void *)0x08399D14, 12, 10, 2, task, 10);
        descriptor->phase++;
        break;
    case 0x102:
        payload->resource_child = func_080D3F08(payload->resource_child);
        if (payload->resource_child)
            break;
        payload->first_child = func_080D4774(payload->first_child);
        if (payload->first_child)
            break;
        payload->second_child = func_080D4774(payload->second_child);
        if (payload->second_child)
            break;
        {
            u32 mask = func_080035A8(2);
            g_control_flags_03000940 &= ~mask;
        }
        payload->effect = func_080D6134(payload->effect);
        if (payload->effect)
            break;
        payload->optional_effect = func_080D6134(payload->optional_effect);
        if (payload->optional_effect)
            break;
        payload->animation = func_080DBA5C(payload->animation);
        if (!payload->animation)
            descriptor->phase = 2;
        break;
    }
    return 0;
}
