#include "interfaces.h"
BattleRecord *BattleCallbackProducer_000A8194(void *actor,u16 first,u16 second,u32 x,u32 y,u32 mode,u32 extra)
{
 register BattleRecord *record __asm__("r6");
 u8 *cursor,*last;
 register u8 *marker __asm__("r5");
 /* Original entry captures LOW8 x/y in R9/R10 across allocation and clears. */
 register u32 clear_size __asm__("r8");
 register u32 captured_x __asm__("r9");
 register u32 captured_y __asm__("r10");
 u32 captured_extra;
 /* Actual native LOW8 definitions: x, then y, then extra. */
 captured_x=(u8)x;
 __asm__("" : "+r"(captured_x));
 captured_y=(u8)y;
 __asm__("" : "+r"(captured_y));
 captured_extra=(u8)extra;
 record=AllocateRecord(0x3498);
 /* Original A81CC defines returned record R6 through final return/cleanup. */
 __asm__("" : "+r"(record));
 ClearBytesCell(record,0x3498);
 /* Original A81DA..DE defines call size R8 after full-block clear. */
 clear_size=708;
 __asm__("" : "+r"(clear_size));
 marker=record->bytes+28;
 /* Original independent moving sentinel address A81E0..E2, not record base. */
 __asm__("" : "+r"(marker));
 cursor=record->bytes;
 last=record->bytes+0x23f4;
 do {
  ClearBytesCell(cursor,clear_size);
  *marker=255;
  {
   /* Original loop defines this R0 step only after the byte sentinel store. */
   register u32 pointer_step __asm__("r0") = 708;
   __asm__("" : "+r"(pointer_step));
   marker+=pointer_step;
   cursor+=pointer_step;
  }
 } while ((s32)(u32)cursor <= (s32)(u32)last);
 {
  /* Original postloop ABI producers: R9 -> R1 -> signed R2, R10 -> R0 -> signed R3. */
  register u32 x_input __asm__("r1");
  register u32 y_input __asm__("r0");
  register s32 signed_x __asm__("r2");
  register s32 signed_y __asm__("r3");
  x_input=captured_x;
  __asm__("" : "+r"(x_input));
  signed_x=(s32)(x_input<<24);
  __asm__("" : "+r"(signed_x));
  signed_x>>=24;
  __asm__("" : "+r"(signed_x));
  y_input=captured_y;
  __asm__("" : "+r"(y_input));
  signed_y=(s32)(y_input<<24);
  __asm__("" : "+r"(signed_y));
  signed_y>>=24;
  __asm__("" : "+r"(signed_y));
  /* Each real outgoing input is defined at its actual store consumer. */
  ProcessRecords(record,actor,signed_x,signed_y,
    ({ register u32 outgoing_first __asm__("r1") = first;
       __asm__("" : "+r"(outgoing_first)); outgoing_first; }),
    ({ register u32 outgoing_second __asm__("r0") = second;
       __asm__("" : "+r"(outgoing_second)); outgoing_second; }),
    (u8)mode,
    ({ register u32 outgoing_extra __asm__("r1") = captured_extra;
       __asm__("" : "+r"(outgoing_extra)); outgoing_extra; }));
 }
 if (record->bytes[0x26bd]==0) {
  FreeRecord(record);
  record=0;
 }
 return record;
}
