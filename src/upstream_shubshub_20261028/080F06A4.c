/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/080F06A4.c
 * Original SHA-256: f7d233c99f4795850e4fc5101a22c992889ce48fcbfeb460d753bf2d5ae69539
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed short s16;

typedef struct {
    u16 phase;
    u16 unknown_02;
    void *primary;
    u32 unknown_08[3];
    u16 unknown_14;
    u16 flag;
} Descriptor;

typedef struct {
    u16 countdown;
    u8 flag;
    u8 unknown_03;
    s16 x;
    s16 y;
    void *auxiliary;
    u8 unknown_0C[16];
    void *effect;
    void *resource_child;
    void *stage;
    void *primary;
    void *entity_child;
    void *result;
} Payload;

extern void func_080D38B4(void);
extern void *func_080E03F8(void *, const void *, u8, u8, void *, void *);
extern void *func_080E05DC(void *);
extern u8 func_080D8858(void *, u16);
extern void *func_080DD4A4(void *, u8);
extern void *func_080DD748(void *, s16 *, s16 *, u32);
extern u8 func_080DD73C(void *);
extern void *func_080D6098(s16, s16, u16, u8, u16, void *, const void *, void *);
extern void *func_080DCFE4(void *, const void *, u8, u16, u16, void *, u16);
extern u8 func_080DD580(void *);
extern void *func_080DFD8C(const void *, u8, u16, u16, void *);
extern void *func_080DD4B4(void *, u8);
extern void func_080DF860(void *);
extern void *func_080D4704(const void *, void *);
extern void *func_080D6134(void *);
extern void *func_080D4774(void *);
extern void *func_080DBA5C(void *);
extern void *func_080DFED8(void *);

/* Target: complete [0x080F06A4, 0x080F082C), 392 bytes.
 * f0b5474680b484b080460e1c141c3388012b23d0012b02dc002b08d0abe08020400083421dd00130834277d0a3e0f08aa0707268a26203250006002800d000250549009340460190101c2a1c0123eff781fe60628fe00000d89d3908e3f7d8f889e0606aeff768ff6062002800d082e0a06a0021e8f79ef80006002879d0a06a0021ecf7bdfe051c211da21d0023edf709f8a060edf700f80006002802d0e0880838e0800421605e0622a15e04220092221c0c320192104a02924246039200220123e5f797fce061022000904046019046200290281c00210c220023ecf730fce0620327281cecf7f9fe0006002805d03220208003e00000fc9d39080227064841460091391c00220023eff7edfa2063308801302ee000005c9e3908208800280fd001382080000400280ad1a06a0021ecf76efeeff742f812484146e3f790ff2062e069e5f7a4fce061002813d1206ae3f7beff206200280dd1e06aebf72cf9e062002807d1206beff764fb2063002801d102203080002004b008bc9846f0bc02bc0847d89d9408
 */
u32 func_080F06A4(void *task, Descriptor *descriptor, Payload *payload)
{
    switch (descriptor->phase) {
    case 0: {
        u8 mode;
        payload->flag = descriptor->flag;
        payload->primary = descriptor->primary;
        mode = 3;
        if (payload->flag)
            mode = 0;
        payload->stage = func_080E03F8(payload->primary, (const void *)0x08399DD8,
                                      mode, 1, 0, task);
        break;
    }
    case 1:
        func_080D38B4();
        break;
    case 0x100:
        payload->stage = func_080E05DC(payload->stage);
        if (!payload->stage) {
            if (!func_080D8858(payload->primary, 0))
                descriptor->phase = 2;
            else {
                void *entity = func_080DD4A4(payload->primary, 0);
                u8 mode;
                payload->auxiliary = func_080DD748(entity, &payload->x, &payload->y, 0);
                if (func_080DD73C(payload->auxiliary))
                    payload->y -= 8;
                payload->effect = func_080D6098(payload->x, payload->y, 0, 1, 4,
                                               payload->unknown_0C, (const void *)0x08399DFC, task);
                payload->entity_child = func_080DCFE4(entity, 0, 12, 0, 2, task, 70);
                mode = 3;
                if (func_080DD580(entity))
                    payload->countdown = 50;
                else
                    mode = 2;
                payload->result = func_080DFD8C((const void *)0x08399E5C, mode, 0, 0, task);
                descriptor->phase++;
            }
        }
        break;
    case 0x101:
        if (payload->countdown) {
            payload->countdown--;
            if (!payload->countdown) {
                func_080DF860(func_080DD4B4(payload->primary, 0));
                payload->resource_child = func_080D4704((const void *)0x08949DD8, task);
            }
        }
        payload->effect = func_080D6134(payload->effect);
        if (payload->effect)
            break;
        payload->resource_child = func_080D4774(payload->resource_child);
        if (payload->resource_child)
            break;
        payload->entity_child = func_080DBA5C(payload->entity_child);
        if (payload->entity_child)
            break;
        payload->result = func_080DFED8(payload->result);
        if (!payload->result)
            descriptor->phase = 2;
        break;
    }
    return 0;
}
