/* Synthetic code-generation probes for the pinned agbcc Thumb backend.
 * Not game implementations; see docs/agbcc-o2-matching.md.
 * Keep normal and diagnostic compilations on the same fixed O2 profile.
 */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
struct Natural70 { u8 bytes[70]; };
struct Packed70 { u8 bytes[70]; } __attribute__((packed));
struct Flags70 { u8 prefix[65]; u16 flags; u8 suffix[3]; } __attribute__((packed));
extern u8 external_table[];
extern int sink(int);
unsigned natural_size(void) { return sizeof(struct Natural70); }
unsigned packed_size(void) { return sizeof(struct Packed70); }
unsigned flags_size(void) { return sizeof(struct Flags70); }
u8 index_byte(const u8 *p, u32 i) { return p[i]; }
u16 index_half(const u16 *p, u32 i) { return p[i]; }
u32 index_word(const u32 *p, u32 i) { return p[i]; }
int signed_half(const short *p, u32 i) { return p[i]; }
u8 natural_row(const struct Natural70 *p, u32 i) { return p[i].bytes[69]; }
u8 packed_row(const struct Packed70 *p, u32 i) { return p[i].bytes[69]; }
u16 packed_full(const struct Flags70 *p) { return p->flags; }
u32 packed_mask(const struct Flags70 *p) { return p->flags & 0x400; }
u32 bytes_mask(const u8 *p) { return (p[65] | (p[66] << 8)) & 0x400; }
u32 fixed_address(void) { return *(u32 *)(0x02000000u + 0x28c8); }
u8 external_offset(u32 i) { return external_table[i * 70 + 69]; }
u8 fixed_offset(u32 i) { return ((const u8 *)0x0855ae4c)[i * 70 + 69]; }
u32 same_mask_separate(u32 x) { if ((x & 1) && (x & 2)) return 7; return 0; }
u32 same_mask_combined(u32 x) { if ((x & 3) == 3) return 7; return 0; }
u32 interval_boolean(u16 x) { return (u16)(x - 336) <= 22; }
static inline u32 interval_numeric_helper(u16 x) { u16 t = x - 336; u32 out = 0; if (t <= 22) out = 1; return out; }
u32 interval_numeric(u16 x) { return interval_numeric_helper(x); }
int early_returns(int x) { if (x == 2) return sink(8); if (x == 3) return sink(9); return 0; }
int shared_return(int x) { int result; if (x == 2) { result = sink(8); goto done; } if (x == 3) { result = sink(9); goto done; } result = 0; done: return result; }
extern const struct Flags70 external_definitions[];
u32 packed_symbol_mask(u32 i) { return external_definitions[i].flags & 0x400; }
u32 packed_fixed_mask(u32 i) { return ((const struct Flags70 *)0x0855ae4c)[i].flags & 0x400; }
u32 packed_fixed_full(u32 i) { return ((const struct Flags70 *)0x0855ae4c)[i].flags; }
u32 packed_offset_pointer_mask(const u8 *p, u32 i) { const struct Flags70 *d = (const struct Flags70 *)(p + i * 70); return d->flags & 0x400; }
u32 packed_branch(const struct Flags70 *p) { if (p->flags & 0x400) return 7; return 0; }
u32 packed_boolean(const struct Flags70 *p) { return (p->flags & 0x400) != 0; }
u32 large_const_byte(const u8 *p) { return p[0x1234]; }
u32 large_const_pair(const u8 *p) { return p[0x1234] + p[0x4321]; }
u32 large_const_keep_base(const u8 *p) { u32 value = p[0x1234]; return value + p[0]; }
