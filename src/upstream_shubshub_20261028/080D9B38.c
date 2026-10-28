/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/080D9B38.c
 * Original SHA-256: 79a9be2c2ac0e9de9140c4a342dd0d8bb2df92ebc073aaf8029949da70263079
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

struct TaskData080D9B38 {
    u8 state;
};

extern struct TaskData080D9B38 *func_08005BFC(void *task);

/* Complete [0x080D9B38, 0x080D9B46): 14 bytes, 6 instructions. */
void func_080D9B38(void *task)
{
    func_08005BFC(task)->state = 1;
}
