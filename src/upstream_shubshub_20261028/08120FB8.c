/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/08120FB8.c
 * Original SHA-256: c38ee76b8e6c0c39d453fda7921114b81764664d6314ecccf99067b49c8f5f3a
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* 0x08120FB8..0x0812104C: 148 bytes, including the literal pool. */
typedef struct {
    u16 event;
    u16 unknown_02;
    void *payload;
} Message;

typedef struct {
    u16 timer;
    u16 unknown_02;
    void *handle;
    void *payload;
} MessageWork;

typedef struct {
    u16 held;
    u16 pressed;
} InputState;

extern InputState data_03000000;
extern void *func_080D3508(u16, void *, int);
extern u8 func_080D3878(void *);
extern void func_080D3864(void *);

u32 func_08120FB8(void *owner, Message *message, MessageWork *work)
{
    switch (message->event) {
    case 0:
        work->payload = message->payload;
        break;
    case 2:
        break;
    case 0x100:
        work->handle = func_080D3508(0x15E, work->payload, 0);
        ++message->event;
        break;
    case 0x101:
        if (func_080D3878(work->handle))
            ++message->event;
        break;
    case 0x102:
        if (data_03000000.pressed & 1) {
            func_080D3864(work->handle);
            work->timer = 30;
            ++message->event;
        }
        break;
    case 0x103:
        if (--work->timer == 0)
            message->event = 2;
        break;
    }
    return 0;
}
