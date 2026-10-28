/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/080D4BF8.c
 * Original SHA-256: 04613548a6ca2605b0fcadbdf655055aab96f60eb8bb73f126bd307530c39085
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

typedef struct {
    u16 flags;
    u16 offset;
    u8 data[0];
} __attribute__((packed)) Resource;

extern void *func_0800B2A4(u8 kind, const void *data, const void *extra, u8 first, u8 second);
extern void *func_0800B394(u8 kind, const void *data, const void *extra, u8 first, u8 second);
extern void func_0800BEDC(void *object, u8 mode);
extern void func_0800BED8(void *object, s16 value);
extern void func_0800BF04(void *object, u8 first, u8 second);

void *func_080D4BF8(u8 kind, const Resource *resource, u16 value, u8 mode, u8 first, u8 second)
{
    const void *data = resource->data;
    const void *extra = (const u8 *)resource + resource->offset;
    void *object;

    if (resource->flags & 1)
        object = func_0800B2A4(kind, data, extra, first, second);
    else
        object = func_0800B394(kind, data, extra, first, second);
    func_0800BEDC(object, mode);
    func_0800BED8(object, (s16)value);
    func_0800BF04(object, resource->flags & 4, resource->flags & 8);
    return object;
}
