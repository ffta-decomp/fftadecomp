typedef unsigned char u8;typedef signed short s16;typedef signed int s32;
struct Record {u8 identity;};
struct SelectionContext {u8 prefix[27],record_count,gap28[4];struct Record *records[0];};
extern struct SelectionContext *gSelection;
__asm__(".global gSelection\n.set gSelection,0x0200F44C");
