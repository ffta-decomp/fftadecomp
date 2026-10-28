typedef unsigned char u8;
typedef unsigned short u16;
typedef short s16;
typedef unsigned int u32;
struct PairSceneState { u8 unused0, active, result_flags, kind, unused4, unused5, stage; };
extern struct PairSceneState PairSceneState;
extern void CreatePairChooser_0802F400(u32);
extern u32 PollPairChooser_0802F560(void);
u32 SceneRegisteredRoot_00023AA0(void)
{
    struct PairSceneState *state = &PairSceneState;
    switch (state->stage) {
    case 0:
        CreatePairChooser_0802F400(7168);
        state->stage = 1;
        break;
    case 1:
        {
            register u32 shifted asm("r0") = PollPairChooser_0802F560();
            register u32 result asm("r1");
            /* Two original Thumb instructions retain both low16 << 16 for
               the zero test and zero-extended low16 for the signed outcome.
               R0 has the real full helper result; R1 is defined by LSRS.
               This 4-byte island is 4/74 original instruction bytes (5.41%). */
            asm("lsl %0, %0, #16\n\tlsr %1, %0, #16"
                : "+r" (shifted), "=r" (result) : : "cc");
            if (shifted != 0) {
                register u32 sign_bits asm("r0") = result << 16;
                asm("" : : "r" (sign_bits));
                if ((int)sign_bits < 0)
                    state->result_flags = 128;
                else
                    state->result_flags = 0;
                PairSceneState.active = 0;
                return 1;
            }
        }
        break;
    }
    return 20;
}
asm(".set PairSceneState,0x0200f390\n.thumb_set CreatePairChooser_0802F400,0x0802f401\n.thumb_set PollPairChooser_0802F560,0x0802f561\n");
