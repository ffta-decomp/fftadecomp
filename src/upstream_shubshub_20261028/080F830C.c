/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/080F830C.c
 * Original SHA-256: 04706d4163ef81e4c3ea590c611b75b373ef909f54f6913057a591748009d7c9
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* Target [0x080F830C, 0x080F8608), 764 bytes:
 * f0b54f464646c0b485b0071c0e1c141c31880648814275d081420edc012941d0012905dc002917d05de100000101000080204000814238d055e10648814200d19ce0814200da79e00130814200d117e149e1000003010000f08ae07170686061a1711420315e8d204000814207d10122a271f06802210840002800d022720623e079002800d00023606905490022009201971a1c0023e8f729f8a06123e100002cbf3908dbf780fa1de1a069e8f710f9a061002800d016e16069dbf7c5fb0006002800d00de12823a079012804d1207a3423002800d158236069211c0c31221c09320092064a019200220292039204971a1c0123e5f7b2fd606430880130f1e0d0bf3908607a002800d1ece0e068009701210c220023e3f777fba063a079012807d105480097012104220023e7f7a8fca06430880130d5e0d8bf3908a06be3f707fb051ca563002d00d0cce0e0680021e5f7aeff606ce3f7f5fae068221c0932054b0095019502970121e6f73df8606430880130b6e00000d4bf3908607a002800d1b0e060690021e0f7e0f90006000e8146002800d1a4e060690021e4f7fcff051ca21c211c0023e5f748f920612d480021635e61880439090409140091002101910222def7a6fe2748391cdcf714f920632648391c0a22dcf71ef960632448391cdbf7d5fce0620022a05e0222a15e03220092221c1c3201921e4a0292039700220123ddf7c2fda0621b480097012104220023e7f734fca0641848804604200090019718200290281c41460c221823e4f752fde0634946022910d160690121e4f7aaff051c0a20009001974a200290281c41460c224a23e4f73efd2064308801303fe09c468f08fca09408b0aa94089cd6940874bf3908e0bf3908bcbf3908e068e5f72ffe000600282cd0e06adbf7b5fce062002826d1206bdcf7e5f82063002820d102200af7f9ff134a118881431180606bdcf7d8f86063002813d1a06addf7b2fda06200280dd1e06be3f740fae063002807d1206ce3f73afa2064002801d102203080002005b018bc9846a146f0bc02bc0847000040090003
 */

typedef struct {
    u16 phase;
    u16 unknown_02;
    void *object;
    u32 unknown_08;
    u32 flags;
    u32 unknown_10;
    s16 selector;
    u16 mode;
} Descriptor080F830C;

typedef struct {
    s16 x;
    s16 y;
    u16 unknown_04;
    u8 variant;
    u8 mode;
    u8 alternate;
    u8 ready;
    u16 unknown_0a;
    void *object;
    void *coordinate_result;
    void *source;
    void *initial_child;
    u32 unknown_1c[3];
    void *coordinate_child;
    void *effect_child;
    void *first_child;
    void *second_child;
    void *transition_child;
    void *first_object_child;
    void *second_object_child;
    void *animation_child;
    void *record_child;
} Payload080F830C;

extern void *func_080E03F8(void *, const void *, u8, u8, u32, void *);
extern void func_080D38B4(void);
extern void *func_080E05DC(void *);
extern u8 func_080D3B54(void *);
extern void *func_080DDF68(void *, void **, u16, u8, u8 *, const void *, u16, u16, void *);
extern void *func_080DBB14(void *, u8, u8, u16, void *);
extern void *func_080DFD8C(const void *, u8, u16, u16, void *);
extern void *func_080DBA5C(void *);
extern void func_080DE3BC(void *, u8);
extern void func_080DBA50(void *);
extern void *func_080DE4F4(void *, u8, u8 *, const void *, u16, u16, void *);
extern u8 func_080D8858(void *, u16);
extern void *func_080DD4A4(void *, u8);
extern void *func_080DD748(void *, s16 *, s16 *, u32);
extern void func_080D7220(const void *, u8, u8, s16, s16, u16);
extern void *func_080D4704(const void *, void *);
extern void *func_080D4724(const void *, void *, u16);
extern void *func_080D3E9C(const void *, void *);
extern void *func_080D6098(s16, s16, u16, u8, u16, void *, const void *, void *);
extern void *func_080DCFE4(void *, const void *, u8, u16, u16, void *, u16);
extern u8 func_080DE1F0(void *);
extern void *func_080D3F08(void *);
extern void *func_080D4774(void *);
extern u16 func_080035A8(u8);
extern void *func_080D6134(void *);

u32 func_080F830C(void *task, Descriptor080F830C *descriptor,
                  Payload080F830C *payload)
{
    u8 mode;
    u16 code;
    u8 count;
    void *object;

    switch (descriptor->phase) {
    case 0:
        payload->mode = descriptor->mode;
        payload->source = descriptor->object;
        payload->variant = 0;
        if (descriptor->selector == 0x11a) {
            payload->variant = 1;
            if (descriptor->flags & 2)
                payload->alternate = 1;
        }
        mode = 6;
        if (payload->mode != 0)
            mode = 0;
        payload->initial_child = func_080E03F8(payload->source,
            (const void *)0x0839BF2C, mode, 0, 0, task);
        break;
    case 1:
        func_080D38B4();
        break;
    case 0x100:
        payload->initial_child = func_080E05DC(payload->initial_child);
        if (payload->initial_child != 0)
            break;
        if (func_080D3B54(payload->source)) {
            descriptor->phase = 2;
            break;
        }
        code = 40;
        if (payload->variant == 1) {
            if (payload->alternate == 0)
                code = 88;
            else
                code = 52;
        }
        payload->animation_child = func_080DDF68(payload->source,
            &payload->object, code, 1, &payload->ready,
            (const void *)0x0839BFD0, 0, 0, task);
        descriptor->phase++;
        break;
    case 0x101:
        if (payload->ready == 0)
            break;
        payload->transition_child = func_080DBB14(payload->object, 1, 12, 0, task);
        if (payload->variant == 1)
            payload->record_child = func_080DFD8C((const void *)0x0839BFD8,
                1, 4, 0, task);
        descriptor->phase++;
        break;
    case 0x102:
        payload->transition_child = func_080DBA5C(payload->transition_child);
        if (payload->transition_child != 0)
            break;
        func_080DE3BC(payload->object, 0);
        func_080DBA50(payload->animation_child);
        payload->animation_child = func_080DE4F4(payload->object, 1,
            &payload->ready, (const void *)0x0839BFD4, 0, 0, task);
        descriptor->phase++;
        break;
    case 0x103:
        if (payload->ready == 0)
            break;
        count = func_080D8858(payload->source, 0);
        if (count == 0) {
            descriptor->phase = 2;
            break;
        }
        object = func_080DD4A4(payload->source, 0);
        payload->coordinate_result = func_080DD748(object,
            &payload->x, &payload->y, 0);
        func_080D7220((const void *)0x088F469C, 0, 2,
            payload->x, (s16)(payload->y - 4), 0);
        payload->first_child = func_080D4704((const void *)0x0894A0FC, task);
        payload->second_child = func_080D4724((const void *)0x0894AAB0, task, 10);
        payload->effect_child = func_080D3E9C((const void *)0x0894D69C, task);
        payload->coordinate_child = func_080D6098(payload->x, payload->y,
            0, 1, 3, payload->unknown_1c, (const void *)0x0839BF74, task);
        payload->record_child = func_080DFD8C((const void *)0x0839BFE0,
            1, 4, 0, task);
        payload->first_object_child = func_080DCFE4(object,
            (const void *)0x0839BFBC, 12, 24, 4, task, 24);
        if (count == 2) {
            object = func_080DD4A4(payload->source, 1);
            payload->second_object_child = func_080DCFE4(object,
                (const void *)0x0839BFBC, 12, 74, 10, task, 74);
        }
        descriptor->phase++;
        break;
    case 0x104:
        if (func_080DE1F0(payload->object) == 0)
            break;
        payload->effect_child = func_080D3F08(payload->effect_child);
        if (payload->effect_child != 0)
            break;
        payload->first_child = func_080D4774(payload->first_child);
        if (payload->first_child != 0)
            break;
        *(u16 *)0x03000940 &= ~func_080035A8(2);
        payload->second_child = func_080D4774(payload->second_child);
        if (payload->second_child != 0)
            break;
        payload->coordinate_child = func_080D6134(payload->coordinate_child);
        if (payload->coordinate_child != 0)
            break;
        payload->first_object_child = func_080DBA5C(payload->first_object_child);
        if (payload->first_object_child != 0)
            break;
        payload->second_object_child = func_080DBA5C(payload->second_object_child);
        if (payload->second_object_child == 0)
            descriptor->phase = 2;
        break;
    }
    return 0;
}
