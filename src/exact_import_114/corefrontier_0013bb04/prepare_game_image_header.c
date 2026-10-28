#include "interfaces.h"

/* Observed header allocation; the two field meanings remain tentative. */
typedef struct {
    u8 preceding_header[48];
    u16 low10 : 10;
    u16 high6 : 6;
    u16 version;
} ImageHeaderFields;
typedef char HeaderFieldsSize[(sizeof(ImageHeaderFields) == 52) ? 1 : -1];
typedef char HeaderVersionOffset[((u32)&((ImageHeaderFields *)0)->version == 50) ? 1 : -1];

void PrepareGameImageHeader(u8 slot, u8 *image)
{
    ImageHeaderFields *header = (ImageHeaderFields *)image;
    u32 summary;
    u8 copied_byte;

    CopyImageBytes(image + 26, image + 0x1f1c, 20);
    copied_byte = image[137];
    image[46] = copied_byte;
    header->low10 = ImageHalf(image, 0x2fbc);
    header->high6 = image[0x2fbe];
    CopyImageBytes(image + 82, image + 0x21a0, 20);
    copied_byte = image[0x21b4];
    ImageHalf(image, 116) = copied_byte;
    ImageHalf(image, 118) = SaveCall_13B9F8(image);
    ImageHalf(image, 50) = 1;
    summary = SaveCall_13BA5C(image, image[0x2182]);
    ImageHalf(image, 54) = summary;
    ImageHalf(image, 56) = summary >> 16;
}
