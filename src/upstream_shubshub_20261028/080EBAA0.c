/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/080EBAA0.c
 * Original SHA-256: 7e92563a7289aecd1bf91432a63222ab9ac62c77788bed35828101fb88b60725
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
/* 0x080EBAA0 - 182 bytes, complete target bytes:
 * 70b5051c0e1c141c318801294fd0012902dc002908d04ae080204000814208d0013081421ed042e07068e060282020803de02088013820800004002837d10748291ce8f70ffe60600548291ce8f7d6f9a060782020803088013027e03490940800d79408208800280dd001382080000400281cd100201e212a1cf4f725f92061e06802f02df86068e8f724fe606000280dd1a068e8f7e8f9a060002807d12069f4f7caf92061002801d102203080002070bc02bc0847
 */
#include "ffta.h"

typedef struct {
    u16 phase;
    u16 unknown_02;
    u32 value;
} Descriptor080EBAA0;

typedef struct {
    u16 countdown;
    u16 unknown_02;
    void *first_child;
    void *second_child;
    u32 value;
    void *third_child;
} Payload080EBAA0;

extern void *func_080D4704(const void *record, void *parent);
extern void *func_080D3E9C(const void *record, void *parent);
extern void *func_080DFD68(u8 value, u16 duration, void *parent);
extern void func_080EDB80(u32 value);
extern void *func_080D4774(void *child);
extern void *func_080D3F08(void *child);
extern void *func_080DFED8(void *child);

u32 func_080EBAA0(void *task, Descriptor080EBAA0 *descriptor,
                  Payload080EBAA0 *payload)
{
    switch (descriptor->phase) {
    case 0:
        payload->value = descriptor->value;
        payload->countdown = 40;
        break;
    case 1:
        break;
    case 0x100:
        if (--payload->countdown == 0) {
            payload->first_child = func_080D4704((const void *)0x08949034, task);
            payload->second_child = func_080D3E9C((const void *)0x0894D700, task);
            payload->countdown = 120;
            descriptor->phase++;
        }
        break;
    case 0x101:
        if (payload->countdown != 0) {
            if (--payload->countdown != 0)
                break;
            payload->third_child = func_080DFD68(0, 30, task);
            func_080EDB80(payload->value);
        }
        if ((payload->first_child = func_080D4774(payload->first_child)) == 0 &&
            (payload->second_child = func_080D3F08(payload->second_child)) == 0 &&
            (payload->third_child = func_080DFED8(payload->third_child)) == 0)
            descriptor->phase = 2;
        break;
    }
    return 0;
}
