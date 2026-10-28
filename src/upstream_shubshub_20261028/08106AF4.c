/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/08106AF4.c
 * Original SHA-256: acaa5b21cccf62ca7e30c04a4eed3050d6b9fb52e42a256ce3349d65dc942edd
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* Target 0x08106AF4, complete [0x08106AF4, 0x08106C02), 270 bytes:
 * f0b584b0071c0e1c151c3388012b21d0012b02dc002b08d074e08020400083421bd0013083425fd06ce0f08aa87074682c6204220006002800d00022044900930197201c0123d9f75dfce8615ae0000020073a08ccf7b4fe54e0e869d9f744fde86100284ed1286a0021d1f77bfe0006002845d0286a0021d6f79afc041c291daa1d0023d6f7e6fda8600421685e0622a95e032200922a1c0c3201920f4a0292039700220123cff77dfaa8610c490420009001975a200290201c0c225a23d6f717fa686207480097032104220023d9f7e3f8a8623088013013e0000050073a0898073a08ac073a08a869cff7a9faa861002807d1686ad4f737ff6862002801d102203080002004b0f0bc02bc0847
 */

/* Local access views; original declaration types and extents are unknown. */
typedef struct {
    u16 phase;
    u16 unknown_02;
    void *actor;
    u8 unknown_08[14];
    u16 flag;
} Descriptor08106AF4;

typedef struct {
    u8 unknown_00[2];
    u8 flag;
    u8 unknown_03;
    s16 x;
    s16 y;
    void *coordinate_result;
    u8 unknown_0c[12];
    void *position_child;
    void *initial_child;
    void *actor;
    void *effect_child;
    void *record_child;
} Payload08106AF4;

extern const u8 data_083A0720[];
extern const u8 data_083A0750[];
extern const u8 data_083A0798[];
extern const u8 data_083A07AC[];

/* Prototypes describe the argument values used at these call sites. */
extern void *func_080E03F8(void *, const void *, u8, u8, u32, void *);
extern void func_080D38B4(void);
extern void *func_080E05DC(void *);
extern u8 func_080D8858(void *, u16);
extern void *func_080DD4A4(void *, u8);
extern void *func_080DD748(void *, s16 *, s16 *, u32);
extern void *func_080D6098(s16, s16, u16, u8, u16, void *, const void *, void *);
extern void *func_080DCFE4(void *, const void *, u8, s16, s16, void *, s16);
extern void *func_080DFD8C(const void *, u8, u16, u16, void *);
extern void *func_080D6134(void *);
extern void *func_080DBA5C(void *);

u32 func_08106AF4(void *task, Descriptor08106AF4 *descriptor,
                  Payload08106AF4 *payload)
{
    void *actor;
    void *actor_object;
    u8 animation;

    switch (descriptor->phase) {
    case 0:
        payload->flag = descriptor->flag;
        actor = descriptor->actor;
        payload->actor = actor;
        animation = 4;
        if (payload->flag != 0)
            animation = 0;
        payload->initial_child = func_080E03F8(actor, data_083A0720,
            animation, 1, 0, task);
        break;
    case 1:
        func_080D38B4();
        break;
    case 0x100:
        payload->initial_child = func_080E05DC(payload->initial_child);
        if (payload->initial_child != 0)
            break;
        if (func_080D8858(payload->actor, 0) == 0) {
            descriptor->phase = 2;
            break;
        }
        actor_object = func_080DD4A4(payload->actor, 0);
        payload->coordinate_result = func_080DD748(actor_object,
            &payload->x, &payload->y, 0);
        payload->position_child = func_080D6098(payload->x, payload->y,
            0, 1, 3, payload->unknown_0c, data_083A0750, task);
        payload->effect_child = func_080DCFE4(actor_object, data_083A0798,
            12, 90, 4, task, 90);
        payload->record_child = func_080DFD8C(data_083A07AC, 3, 4, 0, task);
        descriptor->phase++;
        break;
    case 0x101:
        payload->position_child = func_080D6134(payload->position_child);
        if (payload->position_child != 0)
            break;
        payload->effect_child = func_080DBA5C(payload->effect_child);
        if (payload->effect_child != 0)
            break;
        descriptor->phase = 2;
        break;
    }
    return 0;
}
