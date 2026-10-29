typedef unsigned char u8;
typedef unsigned int u32;
typedef unsigned short u16;
/* Actual 16-byte mission record emitted by whole-exact D29D4. */
struct Record {
    u32 identifier:10;
    u32 definition_value16:8;
    u32 record_type:3;
    u32 unknown02:3;
    u8 definition_value14;
    u8 unknown04[2];
    u16 random_value;
    u8 unknown08[8];
} __attribute__((packed));
typedef char RecordStride[(sizeof(struct Record)==16)?1:-1];
struct Context {void *allocator;u8 gap[12];struct Record *selected;u8 gap2[0xa3c-20];struct Record selection;};
extern struct Context *gContext;
extern u32 gCopyRoutine;
extern struct Record * AllocateBuffer(void *,int);
extern void FreeBuffer(void *,void *);
extern u8 GetGameFlag(int);
extern void SetGameFlag(int,int);
extern int FillRecords(struct Record *);
extern void CopyTrampoline(void *,void *,int,u32);
