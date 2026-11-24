/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/080DADE8.c
 * Original SHA-256: ddc9999c414c531dcbe91026033b142197a7986359f822219e3cbf515d4a8327
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
typedef unsigned char u8;

typedef struct {
    u8 unknown_0[0xB];
    u8 value;
} TaskState;

extern TaskState *func_08005BFC(void *task);

/* 0x080DADE8: 18 bytes. Set the task state's byte at offset 0xB. */
void func_080DADE8(void *task, u8 value)
{
    TaskState *state = func_08005BFC(task);

    state->value = value;
}
