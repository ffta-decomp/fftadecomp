/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/080EE948.c
 * Original SHA-256: cca1cc83c9ae35d261463a7560daae9a1370784eb1c9e780835e4c7f588d8b7d
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
/* Target 0x080EE948, complete [0x080EE948, 0x080EEB50), 520 bytes:
 * 70b584b0061c0d1c141c2b888020400083422ad0834204dc002b0dd0012b21d0eae081204000834258d0834246db0130834200d1b8e0dfe0e88ae0716a68a26203250006002800d00025054900930196101c2a1c0123f1f72bfd2062cce00000b4983908e4f782ffc6e0206af1f712fe2062002800d0bfe0a06a0021eef76efda060a11c221d0023eef7bafee060eef7b1fe0006002802d0a0880838a080e079002802d081204000a5e0a16a0620321c00f07afa2062288801309ce0206af1f7e9fd2062002800d096e0a06a0621321c00f01afa6062288801308ce0a06aeef735fd0006002804d1606a00f09bfa60627ee0e079002805d1606a00f075fa0006002879d00221605e0422a15e01220092221c103201921e4a0292039600220123e7f716fb60610220235e0421605e0090002002210022e5f7bdff1649f122920000200623e6f76af8a061022014f788fd114a1188014311801048311ce5f7faf9e061a0680e490a22009201965a2202920c225a23eef792fae0620a480096012104220023f1f75ef920632888013032e0d898390854eb8e084009000344d89408f098390804993908606a00f03bfa6062002821d1e069e5f703fae06100281bd1a0690021e6f70ef9a061002814d1022014f746fd0b4a1188814311806069e7f705fb6061002807d1e06aecf793ffe062002801d102202880002004b070bc02bc0847000040090003
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
} Descriptor080EE948;

typedef struct {
    u16 unknown_00;
    s16 x;
    s16 y;
    u8 unknown_06;
    u8 flag;
    void *entity;
    void *auxiliary;
    u8 unknown_10[4];
    void *effect;
    void *object;
    void *resource_task;
    void *stage;
    void *variant_task;
    void *primary;
    void *animation;
    void *result;
} Payload080EE948;

extern u16 g_control_flags_03000940;
extern u32 func_080035A8(u8 index);
extern void func_080D38B4(void);
extern void *func_080DD4A4(void *primary, u8 mode);
extern void *func_080DD748(void *entity, s16 *x, s16 *y, u32 mode);
extern u8 func_080DD73C(void *auxiliary);
extern u8 func_080DD494(void *primary);
extern void *func_080E03F8(void *primary, const void *data, u8 first,
                          u8 second, void *argument, void *parent);
extern void *func_080E05DC(void *task);
extern void *func_080EEEF0(u8 variant, void *primary, void *parent);
extern void *func_080EEE50(void *primary, u8 variant, void *parent);
extern void *func_080EEF6C(void *task);
extern u8 func_080EEF30(void *task);
extern void *func_080D6098(s16 x, s16 y, u16 third, u8 mode, u16 count,
                          void *output, const void *data, void *parent);
extern void func_080D49FC(u8 first, u8 second, u16 third, s16 x, s16 y);
extern void *func_080D4B64(u8 first, const void *data, u16 tile, u8 order);
extern void *func_080D3E9C(const void *data, void *parent);
extern void *func_080DCFE4(void *entity, const void *data, u8 third,
                          u16 fourth, u16 fifth, void *parent, u16 seventh);
extern void *func_080DFD8C(const void *data, u8 second, u16 third,
                          u16 fourth, void *parent);
extern void *func_080D3F08(void *task);
extern void *func_080D4D2C(void *object, u8 mode);
extern void *func_080D6134(void *task);
extern void *func_080DBA5C(void *task);

u32 func_080EE948(void *task, Descriptor080EE948 *descriptor,
                  Payload080EE948 *payload)
{
    u8 mode;

    switch (descriptor->phase) {
    case 0:
        payload->flag = descriptor->flag;
        payload->primary = descriptor->primary;
        mode = 3;
        if (payload->flag)
            mode = 0;
        payload->stage = func_080E03F8(payload->primary,
            (const void *)0x083998B4, mode, 1, 0, task);
        break;
    case 1:
        func_080D38B4();
        break;
    case 0x100:
        payload->stage = func_080E05DC(payload->stage);
        if (payload->stage == 0) {
            payload->entity = func_080DD4A4(payload->primary, 0);
            payload->auxiliary = func_080DD748(payload->entity,
                                             &payload->x, &payload->y, 0);
            if (func_080DD73C(payload->auxiliary))
                payload->y -= 8;
            if (payload->flag) {
                descriptor->phase = 0x102;
            } else {
                payload->stage = func_080EEEF0(6, payload->primary, task);
                descriptor->phase++;
            }
        }
        break;
    case 0x101:
        payload->stage = func_080E05DC(payload->stage);
        if (payload->stage == 0) {
            payload->variant_task = func_080EEE50(payload->primary, 6, task);
            descriptor->phase++;
        }
        break;
    case 0x102:
        if (!func_080DD494(payload->primary)) {
            payload->variant_task = func_080EEF6C(payload->variant_task);
            if (!payload->variant_task)
                descriptor->phase = 2;
        } else if (payload->flag || func_080EEF30(payload->variant_task)) {
            payload->effect = func_080D6098(payload->x, payload->y, 0, 1, 1,
                payload->unknown_10, (const void *)0x083998D8, task);
            func_080D49FC(0, 2, 0, payload->x, payload->y);
            payload->object = func_080D4B64(0, (const void *)0x088EEB54,
                                          0x3C4, 6);
            {
                u32 mask = func_080035A8(2);
                u16 flags = g_control_flags_03000940;
                flags |= mask;
                g_control_flags_03000940 = flags;
            }
            payload->resource_task = func_080D3E9C((const void *)0x0894D844,
                                                  task);
            payload->animation = func_080DCFE4(payload->entity,
                (const void *)0x083998F0, 12, 90, 10, task, 90);
            payload->result = func_080DFD8C((const void *)0x08399904,
                                          1, 4, 0, task);
            descriptor->phase++;
        }
        break;
    case 0x103:
        payload->variant_task = func_080EEF6C(payload->variant_task);
        if (payload->variant_task)
            break;
        payload->resource_task = func_080D3F08(payload->resource_task);
        if (payload->resource_task)
            break;
        payload->object = func_080D4D2C(payload->object, 0);
        if (payload->object)
            break;
        {
            u32 mask = func_080035A8(2);
            g_control_flags_03000940 &= ~mask;
        }
        payload->effect = func_080D6134(payload->effect);
        if (payload->effect)
            break;
        payload->animation = func_080DBA5C(payload->animation);
        if (!payload->animation)
            descriptor->phase = 2;
        break;
    }
    return 0;
}
