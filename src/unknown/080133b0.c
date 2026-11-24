typedef unsigned char u8;
typedef unsigned short u16;
struct ProgressState {u8 observed0[22];u16 limit;u16 value;u8 observed26[14];u8 complete;};
extern struct ProgressState *gProgressState;
extern u8 gSaveData[];
__asm__(".global gProgressState\n.set gProgressState,0x0200918c\n.global gSaveData\n.set gSaveData,0x02000000");
void ApplyConfiguredProgressLimit(u16 limit) {
 struct ProgressState *state=gProgressState;
 state->limit=limit?limit:1;
 if((gSaveData[0x2fc0]&24)==8) state->limit=4096;
 state=gProgressState;
 if(state->limit==4096) {state->value=32768;state->complete=1;}
}
