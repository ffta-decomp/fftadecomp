typedef unsigned char u8;

/* Each selector exposes one observed item-adjustment descriptor in ROM. */
extern const u8 gItemAdjustment2[];
extern const u8 gItemAdjustment3[];
extern const u8 gItemAdjustment4[];
extern const u8 gItemAdjustment5[];
extern const u8 gItemAdjustment6[];

const void *GetItemAdjustmentRecord(u8 selector)
{
    switch (selector) {
    case 2: return gItemAdjustment2;
    case 3: return gItemAdjustment3;
    case 4: return gItemAdjustment4;
    case 5: return gItemAdjustment5;
    case 6: return gItemAdjustment6;
    default: return 0;
    }
}
