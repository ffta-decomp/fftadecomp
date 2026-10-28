/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/080EE2F4.c
 * Original SHA-256: ce55bc60e3bb8c8c75f2b7811738ea4515ffcf9afdb5468346e64e845278621c
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
    u16 unknown_00;
    s16 x;
    s16 y;
    u8 unknown_06;
    u8 flag;
    void *entity;
    void *auxiliary;
    u8 unknown_10[12];
    void *effect;
    void *object;
    void *resource_child;
    void *stage;
    void *variant_child;
    void *primary;
    void *entity_child;
    void *result;
} Payload;

extern u16 g_control_flags_03000940;
extern u32 func_080035A8(u8);
extern void func_080D38B4(void);
extern void *func_080E03F8(void *, const void *, u8, u8, void *, void *);
extern void *func_080E05DC(void *);
extern void *func_080DD4A4(void *, u8);
extern void *func_080DD748(void *, s16 *, s16 *, u32);
extern u8 func_080DD73C(void *);
extern void *func_080EEEF0(u8, void *, void *);
extern void *func_080EEE50(void *, u8, void *);
extern u8 func_080DD494(void *);
extern u8 func_080EEF30(void *);
extern void *func_080EEF6C(void *);
extern void *func_080D6098(s16, s16, u16, u8, u16, void *, const void *, void *);
extern void func_080D49FC(u8, u8, u16, s16, s16);
extern void *func_080D4B64(u8, const void *, u16, u8);
extern void *func_080D3E9C(const void *, void *);
extern void *func_080DCFE4(void *, const void *, u8, u16, u16, void *, u16);
extern void *func_080DFD8C(const void *, u8, u16, u16, void *);
extern void *func_080D3F08(void *);
extern void *func_080D4D2C(void *, u8);
extern void *func_080D6134(void *);
extern void *func_080DBA5C(void *);

/* Target: complete [0x080EE2F4, 0x080EE4FC), 520 bytes.
 * 70b584b0061c0d1c141c2b888020400083422ad0834204dc002b0dd0012b21d0eae081204000834258d0834246db0130834200d1b8e0dfe0e88ae0716a68226303250006002800d00025054900930196101c2a1c0123f2f755f8a062cce0000044963908e5f7acfac6e0a06af2f73cf9a062002800d0bfe0206b0021eff798f8a060a11c221d0023eff7e4f9e060eff7dbf90006002802d0a0880838a080e079002802d081204000a5e0216b0320321c00f0a4fda062288801309ce0a06af2f713f9a062002800d096e0206b0321321c00f044fde062288801308ce0206beff75ff80006002804d1e06a00f0c5fde0627ee0e079002805d1e06a00f09ffd0006002879d00221605e0422a15e03220092221c103201921e4a0292039600220123e7f740fee0610220235e0421605e0090002002210022e6f7e7fa1649f222920000200623e6f794fb2062022015f7b2f8114a1188014311801048311ce5f724fd6062a0680e490a2200920196282202920c222823eef7bcfd60630a480096012104220023f1f788fca0632888013032e06896390844e98e084009000324d89408b0963908c4963908e06a00f065fde062002821d1606ae5f72dfd606200281bd1206a0021e6f738fc2062002814d1022015f770f80b4a118881431180e069e7f72ffee061002807d1606bedf7bdfa6063002801d102202880002004b070bc02bc0847000040090003
 */
u32 func_080EE2F4(void *task, Descriptor *descriptor, Payload *payload)
{
    u8 mode;

    switch (descriptor->phase) {
    case 0: {
        payload->flag = descriptor->flag;
        payload->primary = descriptor->primary;
        mode = 3;
        if (payload->flag)
            mode = 0;
        payload->stage = func_080E03F8(payload->primary, (const void *)0x08399644,
                                      mode, 1, 0, task);
        break;
    }
    case 1:
        func_080D38B4();
        break;
    case 0x100:
        payload->stage = func_080E05DC(payload->stage);
        if (!payload->stage) {
            payload->entity = func_080DD4A4(payload->primary, 0);
            payload->auxiliary = func_080DD748(payload->entity, &payload->x, &payload->y, 0);
            if (func_080DD73C(payload->auxiliary))
                payload->y -= 8;
            if (payload->flag)
                descriptor->phase = 0x102;
            else {
                payload->stage = func_080EEEF0(3, payload->primary, task);
                descriptor->phase++;
            }
        }
        break;
    case 0x101:
        payload->stage = func_080E05DC(payload->stage);
        if (!payload->stage) {
            payload->variant_child = func_080EEE50(payload->primary, 3, task);
            descriptor->phase++;
        }
        break;
    case 0x102:
        if (!func_080DD494(payload->primary)) {
            payload->variant_child = func_080EEF6C(payload->variant_child);
            if (!payload->variant_child)
                descriptor->phase = 2;
        } else if (payload->flag || func_080EEF30(payload->variant_child)) {
            payload->effect = func_080D6098(payload->x, payload->y, 0, 1, 3,
                                           payload->unknown_10, (const void *)0x08399668, task);
            func_080D49FC(0, 2, 0, payload->x, payload->y);
            payload->object = func_080D4B64(0, (const void *)0x088EE944, 0x3C8, 6);
            {
                u32 mask = func_080035A8(2);
                u16 flags = g_control_flags_03000940;
                flags |= mask;
                g_control_flags_03000940 = flags;
            }
            payload->resource_child = func_080D3E9C((const void *)0x0894D824, task);
            payload->entity_child = func_080DCFE4(payload->entity, (const void *)0x083996B0,
                                                12, 40, 10, task, 40);
            payload->result = func_080DFD8C((const void *)0x083996C4, 1, 4, 0, task);
            descriptor->phase++;
        }
        break;
    case 0x103:
        payload->variant_child = func_080EEF6C(payload->variant_child);
        if (payload->variant_child)
            break;
        payload->resource_child = func_080D3F08(payload->resource_child);
        if (payload->resource_child)
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
        payload->entity_child = func_080DBA5C(payload->entity_child);
        if (!payload->entity_child)
            descriptor->phase = 2;
        break;
    }
    return 0;
}
