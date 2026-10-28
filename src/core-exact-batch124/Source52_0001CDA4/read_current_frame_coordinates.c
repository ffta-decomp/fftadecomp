typedef unsigned char u8;
typedef unsigned short u16;
typedef short s16;
static inline void CaptureCurrentFrame(u8 *a, u8 *b, u8 *c, u8 *d)
{
    const u8 *state = (const u8 *)0x02007F10;
    *a = state[13];
    *b = state[15];
    *c = state[10];
    *d = state[12];
}
static inline void CaptureCurrentFrameDepth(u8 *e, u8 *f)
{
    const u8 *state = (const u8 *)0x02007F10;
    *e = state[14];
    *f = state[11];
}
void Source52_0001CDA4(s16 *out_x, s16 *out_y, s16 *out_z)
{
    u8 a, b, c, d, e, f;
    int x;
    CaptureCurrentFrame(&a, &b, &c, &d);
    CaptureCurrentFrameDepth(&e, &f);
    x = (a << 5) + 16;
    x >>= 1;
    *out_y = (e - f) << 3;
    *out_z = ((b << 5) + 16) >> 1;
    x += 16;
    x += c << 5;
    *out_x = x;
    *out_y = (u16)*out_y + (f << 4);
    *out_z = (u16)*out_z + 16 + (d << 5);
}
