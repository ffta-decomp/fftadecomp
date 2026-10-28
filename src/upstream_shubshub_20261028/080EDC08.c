/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/080EDC08.c
 * Original SHA-256: 90d28839fb235542be102b6addb4756f4d6888745d7a722119e32a13d04ac402
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* Target 0x080EDC08, complete [0x080EDC08, 0x080EDE64), 604 bytes:
 * f0b557464e464546e0b483b0051c8846161c0b88054883425fd083420ddc012b2ed0012b04dc002b14d00ee10101000080204000834226d007e10548834200d18ee083425adb0130834200d1e6e0fce0030100004146c88a70724c68746302220006002800d00022044900930195201c0123f2f7bdfbf062e7e0000000943908e5f714fee1e0f06af2f7a4fcf062002800d0dae0706b0021eff700fcf060b11c321db31deff74cfd3061eff743fd0006002802d0b0881030b080707a002802d081204000bfe0716b00202a1c01f00cf9f062414608880130b6e0f06af2f77afcf062002800d0b0e0706b00212a1c01f0abf83063414608880130a5e0706beff7c5fb0006002804d1306b01f02bf9306396e0707a002806d1306b01f005f90006002800d191e0f0680b49022200920195242202920c222423eff750f9b06307480095012104220023f2f71cf8f06341460888013078e0000020943908349439080027072082461421891989462748381831880078814240d10220325e244c3c192078b3881b181b041b140621705e009020480190514602911f480021e8f76cf8bd004d4428600220325e2078b3881b181b041b140621705e0090164801905146029115480121e8f757f8fc1ca4004c44206028680121494223f73af92068012123f736f9307a013030720006000e032803d14146088801300880781c0006070e022fb3d93088013030801ee0189439081b943908a903000054c24f08306b01f0a1f83063002810d1301c14300621e8f775f80006002808d0b06bedf70bfeb063002802d1022041460880002003b038bc9846a146aa46f0bc02bc0847
 */

typedef struct {
    u16 phase;
    u8 unknown_02[2];
    void *wrapper;
    u8 unknown_08[14];
    u16 flag;
} Descriptor080EDC08;

typedef struct {
    u16 counter;
    s16 x;
    s16 y;
    s16 z;
    u8 created;
    u8 flag;
    u8 unknown_0A[2];
    void *wrapper;
    void *underlying;
    void *objects[6];
    void *setup_child;
    void *sequence_child;
    void *forwarded;
    void *wrapper_child;
    void *record_child;
} Payload080EDC08;

extern void func_080D38B4(void);
extern void *func_080E03F8(void *, const void *, u8, u8, const s16 *, void *);
extern void *func_080E05DC(void *);
extern void *func_080DD4A4(void *, u8);
extern void *func_080DD748(void *, s16 *, s16 *, s16 *);
extern u32 func_080DD73C(void *);
extern void *func_080EEEF0(u8, void *, void *);
extern void *func_080EEE50(void *, u8, void *);
extern u32 func_080DD494(void *);
extern void *func_080EEF6C(void *);
extern u32 func_080EEF30(void *);
extern void *func_080DCFE4(void *, const void *, u8, u16, u16, void *, s16);
extern void *func_080DFD8C(const void *, u8, u16, u16, void *);
extern void *func_080D5E80(const void *, u16, s16, s16, s16, s16, u8);
extern void func_08011058(void *, s16);
extern u32 func_080D5F24(void **, u16);
extern void *func_080DBA5C(void *);
extern const u8 g_event_parameters_08399418[];
extern u8 g_offsets_0839941B[];

u32 func_080EDC08(void *task, Descriptor080EDC08 *descriptor,
                  Payload080EDC08 *payload)
{
    u8 mode;
    u8 i;

    switch (descriptor->phase) {
    case 0:
        payload->flag = descriptor->flag;
        payload->forwarded = descriptor->wrapper;
        mode = 2;
        if (payload->flag != 0)
            mode = 0;
        payload->setup_child = func_080E03F8(payload->forwarded,
            (const void *)0x08399400, mode, 1, 0, task);
        break;
    case 1:
        func_080D38B4();
        break;
    case 0x100:
        payload->setup_child = func_080E05DC(payload->setup_child);
        if (payload->setup_child != 0)
            break;
        payload->wrapper = func_080DD4A4(payload->forwarded, 0);
        payload->underlying = func_080DD748(payload->wrapper,
            &payload->x, &payload->y, &payload->z);
        if ((u8)func_080DD73C(payload->underlying) != 0)
            payload->y += 16;
        if (payload->flag != 0) {
            descriptor->phase = 0x102;
        } else {
            payload->setup_child = func_080EEEF0(0, payload->forwarded, task);
            descriptor->phase++;
        }
        break;
    case 0x101:
        payload->setup_child = func_080E05DC(payload->setup_child);
        if (payload->setup_child != 0)
            break;
        payload->sequence_child = func_080EEE50(payload->forwarded, 0, task);
        descriptor->phase++;
        break;
    case 0x102:
        if ((u8)func_080DD494(payload->forwarded) == 0) {
            payload->sequence_child = func_080EEF6C(payload->sequence_child);
            if (payload->sequence_child == 0)
                descriptor->phase = 2;
            break;
        }
        if (payload->flag == 0 &&
            (u8)func_080EEF30(payload->sequence_child) == 0)
            break;
        payload->wrapper_child = func_080DCFE4(payload->wrapper,
            (const void *)0x08399420, 12, 36, 2, task, 36);
        payload->record_child = func_080DFD8C((const void *)0x08399434,
            1, 4, 0, task);
        descriptor->phase++;
        break;
    case 0x103:
        for (i = 0; i < 3; i++) {
            if (payload->counter == g_event_parameters_08399418[i]) {
                payload->objects[i] = func_080D5E80((const void *)0x084FC254,
                    0, payload->x, (s16)(payload->y + g_offsets_0839941B[i]),
                    payload->z, 0x3A9, 7);
                payload->objects[i + 3] = func_080D5E80((const void *)0x084FC254,
                    1, payload->x, (s16)(payload->y + g_offsets_0839941B[i]),
                    payload->z, 0x3A9, 7);
                func_08011058(payload->objects[i], -1);
                func_08011058(payload->objects[i + 3], 1);
                payload->created++;
                if (payload->created == 3)
                    descriptor->phase++;
            }
        }
        payload->counter++;
        break;
    case 0x104:
        payload->sequence_child = func_080EEF6C(payload->sequence_child);
        if (payload->sequence_child != 0)
            break;
        if ((u8)func_080D5F24(payload->objects, 6) == 0)
            break;
        payload->wrapper_child = func_080DBA5C(payload->wrapper_child);
        if (payload->wrapper_child == 0)
            descriptor->phase = 2;
        break;
    }
    return 0;
}
