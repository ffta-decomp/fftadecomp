/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/0808A424.c
 * Original SHA-256: 27e5ff8bc272d7c29b9e9955c65ae984970b21a8531a67e0582452eef2eca482
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;

struct Window {
    u8 unknown_00[3];
    unsigned int hidden : 1;
    unsigned int flags : 7;
    u8 unknown_04[4];
    u16 source_offset;
    u16 destination_offset;
    u8 unknown_0C[0x1C];
    u8 source_stride;
    u8 unknown_29[7];
    s8 left;
    s8 top;
    s8 right;
    s8 bottom;
    s8 x;
    s8 y;
    s8 width;
    s8 height;
    s8 clipped_width;
    s8 clipped_height;
    u8 unknown_3A[0x12];
};

extern struct Window data_030009E0[];

int func_0808A424(int index)
{
    int source_offset = 0;
    int destination_offset;

    data_030009E0[index].hidden = 1;

    if (data_030009E0[index].x >= data_030009E0[index].right)
        return 0;
    if (data_030009E0[index].x + data_030009E0[index].width <= data_030009E0[index].left)
        return 0;
    if (data_030009E0[index].y >= data_030009E0[index].bottom)
        return 0;
    if (data_030009E0[index].y + data_030009E0[index].height <= data_030009E0[index].top)
        return 0;

    data_030009E0[index].hidden = 0;

    if (data_030009E0[index].x >= data_030009E0[index].left) {
        int right = data_030009E0[index].width + data_030009E0[index].x;

        if (right < data_030009E0[index].right) {
            data_030009E0[index].clipped_width = data_030009E0[index].width;
            destination_offset = data_030009E0[index].x;
        } else {
            right -= data_030009E0[index].right;
            data_030009E0[index].clipped_width = data_030009E0[index].width - right;
            destination_offset = data_030009E0[index].x;
        }
    } else {
        int right;

        destination_offset = data_030009E0[index].left;
        source_offset = data_030009E0[index].left - data_030009E0[index].x;

        right = data_030009E0[index].width + data_030009E0[index].x;

        if (right < data_030009E0[index].right)
            data_030009E0[index].clipped_width = right - data_030009E0[index].left;
        else
            data_030009E0[index].clipped_width = data_030009E0[index].right - data_030009E0[index].left;
    }

    if (data_030009E0[index].y >= data_030009E0[index].top) {
        int bottom = data_030009E0[index].height + data_030009E0[index].y;

        if (bottom < data_030009E0[index].bottom) {
            data_030009E0[index].clipped_height = data_030009E0[index].height;
            destination_offset += data_030009E0[index].y * 32;
        } else {
            bottom -= data_030009E0[index].bottom;
            data_030009E0[index].clipped_height = data_030009E0[index].height - bottom;
            destination_offset += data_030009E0[index].y * 32;
        }
    } else {
        int bottom;

        destination_offset += data_030009E0[index].top * 32;
        source_offset += (data_030009E0[index].top - data_030009E0[index].y)
            * data_030009E0[index].source_stride;

        bottom = data_030009E0[index].height + data_030009E0[index].y;

        if (bottom < data_030009E0[index].bottom)
            data_030009E0[index].clipped_height = bottom - data_030009E0[index].top;
        else
            data_030009E0[index].clipped_height = data_030009E0[index].bottom - data_030009E0[index].top;
    }

    data_030009E0[index].source_offset = source_offset;
    data_030009E0[index].destination_offset = destination_offset;
    return 1;
}
