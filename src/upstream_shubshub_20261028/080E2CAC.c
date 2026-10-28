/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/080E2CAC.c
 * Original SHA-256: 7e6c0146659954793df0c2c852eb954ffb7922347b9f6e20c1b61eea818d8274
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* 0x080E2CAC..0x080E2D04: 88 bytes. */
typedef struct {
    u16 state;
    u16 unknown_02;
    u32 unknown_04;
    void *argument;
} ChildEvent;

typedef struct {
    void *argument;
    void *child;
} ChildWork;

extern void *func_080DF90C(void *argument, int mode, void *parent);
extern void *func_080DBA5C(void *object);

int func_080E2CAC(void *parent, ChildEvent *event, ChildWork *work)
{
    switch (event->state) {
    case 0:
        work->argument = event->argument;
        break;
    case 1:
        break;
    case 0x100:
        work->child = func_080DF90C(work->argument, 0, parent);
        event->state++;
        break;
    case 0x101:
        work->child = func_080DBA5C(work->child);
        if (!work->child)
            event->state = 2;
        break;
    }
    return 0;
}
