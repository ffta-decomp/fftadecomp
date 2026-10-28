typedef unsigned char u8;
typedef unsigned short u16;
struct OfferContext { u8 prefix[0x1d48]; u8 selected[20]; };
extern struct OfferContext *gOfferContext;
extern u16 gOfferStock[20];
asm(".global gOfferContext\n.set gOfferContext,0x0200f428\n.global gOfferStock\n.set gOfferStock,0x02001f3c");
