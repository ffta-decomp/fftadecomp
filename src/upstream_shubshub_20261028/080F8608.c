/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/080F8608.c
 * Original SHA-256: db327372983e934162f6dfda051820695222ff60dab7354bd2acf7ffe96574ee
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* Target 0x080F8608, complete [0x080F8608, 0x080F86EA), 226 bytes:
 * f0b584b0061c0d1c141c2988012963d0012902dc002908d05ee08020400081420ed00130814249d056e0a88a20706868a060a11c221d0023e5f782f8e0604be00221605e0422a15e02220092221c10320192174a0292039600220123ddf718fda06121780127381c08400222002800d00422a0680f4900920196142202920c221423e4f7abfce0612178381c08400822002800d01022084804210a43009601210023e7f76ffb20622888013013e00000c0c03908f0c0390818c13908a069ddf735fda061002807d1e069e3f7c3f9e061002801d102202880002004b0f0bc02bc0847
 */

typedef struct {
    u16 phase;
    u16 unknown_02;
    void *object;
    u8 unknown_08[12];
    u16 selector;
} Descriptor080F8608;

typedef struct {
    u8 selector;
    u8 unknown_01;
    s16 x;
    s16 y;
    u16 unknown_06;
    void *object;
    void *coordinate_result;
    u32 unknown_10[2];
    void *coordinate_child;
    void *object_child;
    void *record_child;
} Payload080F8608;

extern void *func_080DD748(void *, s16 *, s16 *, u32);
extern void *func_080D6098(s16, s16, u16, u8, u16, void *, const void *, void *);
extern void *func_080DCFE4(void *, const void *, u8, u16, u16, void *, u16);
extern void *func_080DFD8C(const void *, u8, u16, u16, void *);
extern void *func_080D6134(void *);
extern void *func_080DBA5C(void *);

u32 func_080F8608(void *task, Descriptor080F8608 *descriptor,
                  Payload080F8608 *payload)
{
    u16 object_flags;
    u16 record_flags;

    switch (descriptor->phase) {
    case 0:
        payload->selector = descriptor->selector;
        payload->object = descriptor->object;
        payload->coordinate_result = func_080DD748(payload->object,
            &payload->x, &payload->y, 0);
        break;
    case 1:
        break;
    case 0x100:
        payload->coordinate_child = func_080D6098(payload->x, payload->y,
            0, 1, 2, payload->unknown_10, (const void *)0x0839C0C0, task);
        object_flags = payload->selector & 1 ? 4 : 2;
        payload->object_child = func_080DCFE4(payload->object,
            (const void *)0x0839C0F0, 12, 20, object_flags, task, 20);
        record_flags = payload->selector & 1 ? 16 : 8;
        payload->record_child = func_080DFD8C((const void *)0x0839C118,
            1, record_flags | 4, 0, task);
        descriptor->phase++;
        break;
    case 0x101:
        payload->coordinate_child = func_080D6134(payload->coordinate_child);
        if (payload->coordinate_child != 0)
            break;
        payload->object_child = func_080DBA5C(payload->object_child);
        if (payload->object_child == 0)
            descriptor->phase = 2;
        break;
    }
    return 0;
}
