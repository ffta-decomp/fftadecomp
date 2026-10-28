/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/08031264.c
 * Original SHA-256: ce85989687c6aa313113d31e54a219151b42696933f73506cc799564632e7012
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* 0x08031264..0x080312A8: 68 bytes. */
typedef struct {
    u8 unknown_00[0x78];
    void *owner;
    u8 unknown_7C[0x1C];
    void *member98;
    u8 unknown_9C[0xB6C];
    void *memberC08;
} OwnerState;

typedef struct {
    u8 unknown_00[4];
    void *member;
} MemberState;

extern OwnerState *g_state_03002810;
extern MemberState data_03000E30;
extern void func_08007170(void *owner, void *member);

void func_08031264(void)
{
    func_08007170(g_state_03002810->owner, g_state_03002810->memberC08);
    func_08007170(g_state_03002810->owner, g_state_03002810->member98);
    func_08007170(g_state_03002810->owner, data_03000E30.member);
    func_08007170(g_state_03002810->owner, g_state_03002810);
}
