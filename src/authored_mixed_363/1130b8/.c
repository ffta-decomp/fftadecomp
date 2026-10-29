#include "interfaces.h"
void AdvanceAuthoredWindowRecords(struct AuthoredWindowRecord *records,u8 count) __asm__("RemainingBand43_001130B8");
void AdvanceAuthoredWindowRecords(struct AuthoredWindowRecord *records,u8 count)
{
    u16 z_coordinate,y_coordinate,x_coordinate;
    u8 index;
    for (index=0;index<count;index++) {
        struct AuthoredWindowRecord *record=(struct AuthoredWindowRecord *)(index*40u+(u32)records);
        struct DefinitionRamp *x,*y;
        s16 screen_x,screen_y;
        if (!record->object) continue;
        x=&record->x;
        AdvanceCoordinateRamp(x);
        y=&record->y;
        AdvanceCoordinateRamp(y);
        if (record->scaled_coordinates) {
            SetResourceCoordinates(record->object,(s16)x->value>>6,(s16)y->value>>6,0);
            if ((u8)CoordinateRampComplete(x)) {
                register s32 start asm("r1")=(s16)record->x.value;
                u16 delta;
                asm("" : "+r"(start));
                delta=record->x_delta;
                InitializeCoordinateRamp(x,start,
                    (s16)(delta+((s16)delta>>2)+record->x.value),record->x_duration);
            }
            if ((u8)CoordinateRampComplete(y)) {
                register s32 start asm("r1")=(s16)record->y.value;
                u16 delta;
                asm("" : "+r"(start));
                delta=record->y_delta;
                InitializeCoordinateRamp(y,start,
                    (s16)(delta+((s16)delta>>2)+record->y.value),record->y_duration);
            }
        } else {
            SetResourceCoordinates(record->object,(s16)x->value,(s16)y->value,0);
            if ((u8)CoordinateRampComplete(x)) {
                register s32 start asm("r1");
                register u32 delta asm("r2");
                register u32 current asm("r3");
                /* Original raw-x input phase: signed start, then two U16
                   sources. Calculating/normalizing the target remains C. */
                asm("movs r0,#16\n\t"
                    "ldrsh %0,[%3,r0]\n\t"
                    "ldrh %1,[%3,#10]\n\t"
                    "ldrh %2,[%3,#16]"
                    : "=&r"(start), "=&r"(delta), "=&r"(current)
                    : "r"(record) : "r0", "cc", "memory");
                InitializeCoordinateRamp(x,start,
                    (s16)(delta+current),record->x_duration);
            }
            if ((u8)CoordinateRampComplete(y)) {
                register s32 start asm("r1");
                register u32 delta asm("r2");
                register u32 current asm("r3");
                /* Original raw-y input phase: signed start, then two U16
                   sources. Calculating/normalizing the target remains C. */
                asm("movs r0,#28\n\t"
                    "ldrsh %0,[%3,r0]\n\t"
                    "ldrh %1,[%3,#12]\n\t"
                    "ldrh %2,[%3,#28]"
                    : "=&r"(start), "=&r"(delta), "=&r"(current)
                    : "r"(record) : "r0", "cc", "memory");
                InitializeCoordinateRamp(y,start,
                    (s16)(delta+current),record->y_duration);
            }
        }
        record=(struct AuthoredWindowRecord *)(index*40u+(u32)records);
        ReadResourceCoordinates(record->object,&x_coordinate,&y_coordinate,&z_coordinate);
        screen_x=x_coordinate;
        if (screen_x < -8 || ((screen_y=y_coordinate)>167) ||
            ((screen_x>247 || screen_y < -8) && record->scaled_coordinates)) {
            RemoveResource(record->object);
            record->object=0;
        }
    }
}
