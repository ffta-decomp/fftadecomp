typedef unsigned char u8;
typedef unsigned short u16;
struct ShiftMenuContext {u8 observed0[12];u8 *buffer;u8 observed16[5];u8 width;};
extern u8 MenuShiftScratch[];
extern void CopyMenuShift(void *,void *,unsigned);
extern void DrawMenuShiftRow(void *,unsigned,unsigned);
__asm__(".global MenuShiftScratch\n.set MenuShiftScratch,0x02003cb0\n.global CopyMenuShift\n.thumb_set CopyMenuShift,0x0814186d\n.global DrawMenuShiftRow\n.thumb_set DrawMenuShiftRow,0x08053f09");
void ShiftMenuContentRow(struct ShiftMenuContext *ctx,u16 id,u8 ordinal,u16 mode) {
 u8 *scratch=MenuShiftScratch;
 unsigned stride;
 __asm__("" : "+r"(scratch));
 stride=3*ctx->width;
 if(mode==128) {
  CopyMenuShift(ctx->buffer+2*stride,scratch,3*stride);
  CopyMenuShift(scratch,ctx->buffer,3*stride);
  DrawMenuShiftRow(ctx,ordinal,id);
 } else if(mode==64) {
  CopyMenuShift(ctx->buffer,scratch,3*stride);
  CopyMenuShift(scratch,ctx->buffer+2*stride,3*stride);
  DrawMenuShiftRow(ctx,ordinal,id);
 }
}
