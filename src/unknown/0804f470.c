typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;
struct MarkerRecord {
 const void *descriptor;
 s16 x,y;
 u16 offset_x;
 s16 offset_y;
 u8 depth,selector;
 u16 trailing_state;
};
struct MarkerCycleState {
 u8 unknown00[9];
 u8 enabled;
 u8 unknown0a[2];
 struct MarkerRecord first;
 struct MarkerRecord second;
};
typedef char MarkerStride[(sizeof(struct MarkerRecord)==16)?1:-1];
extern u8 gSelectionContext[];
extern void DrawPositionedMarker(const struct MarkerRecord *record);
/* Only the first marker's trailing halfword is the observed frame counter.
 * The same offset in the second marker remains uninterpreted. */
void CoreRegion_0004F470(struct MarkerCycleState *state)
{
 if(state->enabled && gSelectionContext[18]!=3) {
  int tick=state->first.trailing_state+1;
  state->first.trailing_state=tick;
  if((s16)tick>5) {
   int offset;
   state->first.trailing_state=0;
   offset=state->first.offset_x+1;
   state->first.offset_x=offset;
   if((s16)offset>2) state->first.offset_x=0;
   offset=state->second.offset_x-1;
   state->second.offset_x=offset;
   if((s16)offset<=-3) state->second.offset_x=0;
  }
  DrawPositionedMarker(&state->first);
  DrawPositionedMarker(&state->second);
 }
}
asm(".global gSelectionContext\n.set gSelectionContext,0x020020D0");
asm(".global DrawPositionedMarker\n.thumb_set DrawPositionedMarker,0x08017FE9");
