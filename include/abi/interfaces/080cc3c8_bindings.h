typedef unsigned char u8;
typedef unsigned int u32;
struct PackedProgressionRow {
    unsigned int increment0:5;
    unsigned int increment1:5;
    unsigned int increment2:5;
    unsigned int increment3:5;
    unsigned int increment4:5;
    unsigned int increment5:5;
    unsigned int increment6:5;
    unsigned int increment7:5;
    unsigned int increment8:5;
    unsigned int cap:8;
    unsigned int reserved:3;
} __attribute__((packed));
typedef char row_size_must_be_7[(sizeof(struct PackedProgressionRow)==7)?1:-1];
extern const struct PackedProgressionRow gProgressionRows[];
__asm__(".global gProgressionRows\n.set gProgressionRows,0x08528c24");
