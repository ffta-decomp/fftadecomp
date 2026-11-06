#include "fixed_scene.h"

/* Existing mask getters return zero-extended halfwords in the full R0 carrier. */
u32 ReadAuthoredDisplayMaskHigh(u8);
u32 ReadAuthoredDisplayMaskLow(u8);
