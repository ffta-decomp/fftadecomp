typedef unsigned char u8;
typedef unsigned short u16;
struct Context {u8 gap[24];u8 *unit;};
extern struct Context *gContext;
extern u8 *GetOptions(void *,int,u8 *,u8 *);
extern void *GetContentContext(void);
extern void *FindRecord(void *,void *);
extern u8 CheckOption(void *,u8);
extern int ReadOptionProperty(u16,int);
