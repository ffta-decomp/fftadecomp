typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef signed short s16;
struct MenuDescriptor {u8 p0[4];u16 count;u8 p6[8];u16 tile;};
struct MenuPanel {u8 observed[44];};
struct MenuList {u8 observed0[22];u8 visible;u8 observed23[3];u16 value;u8 observed28[4];};
struct MenuCursor {u8 observed[44];};
struct MenuRecord {u16 value;u8 selected;u8 unknown3;};
struct MenuRoot {u8 prefix[0x53c];struct MenuRecord records[0];};
struct MenuContext {struct MenuRoot *root;u16 flags;u8 unknown6[2];u8 mode;u8 unknown9;u8 count;u8 unknown11;struct MenuDescriptor descriptor;struct MenuPanel panel;struct MenuList list;struct MenuCursor cursor;void *handle;};
extern void InitializePolicyPanel(void *,void *,unsigned,unsigned);
extern void SetPolicyCallback(void *,void *,void *);
extern unsigned QueryPolicyRows(void *);
extern void PopulatePolicyRow(void *,int);
extern void RefreshPolicyList(void *);
extern void MarkPolicyRow(void *,int,unsigned);
extern void AdjustPolicyRow(void *,unsigned,unsigned);
extern void SetPolicyContinuation(void *,void *,void *);
extern void SetPolicyCursor(void *,unsigned);
extern void TickPolicyPanel(void *);
extern void ShowPolicyCursor(void *,unsigned);
extern void InitializePolicyAlternate(void *);
extern void InitializePolicyModeEight(void *);
__asm__(".global InitializePolicyPanel\n.thumb_set InitializePolicyPanel,0x08016211\n.global SetPolicyCallback\n.thumb_set SetPolicyCallback,0x08017ac5\n.global QueryPolicyRows\n.thumb_set QueryPolicyRows,0x08017b51\n.global PopulatePolicyRow\n.thumb_set PopulatePolicyRow,0x080505bd\n.global RefreshPolicyList\n.thumb_set RefreshPolicyList,0x08017ad9\n.global MarkPolicyRow\n.thumb_set MarkPolicyRow,0x08017af5\n.global AdjustPolicyRow\n.thumb_set AdjustPolicyRow,0x08050b9d\n.global SetPolicyContinuation\n.thumb_set SetPolicyContinuation,0x08015d59\n.global SetPolicyCursor\n.thumb_set SetPolicyCursor,0x08017fb1\n.global TickPolicyPanel\n.thumb_set TickPolicyPanel,0x08016235\n.global ShowPolicyCursor\n.thumb_set ShowPolicyCursor,0x08017d19\n.global InitializePolicyAlternate\n.thumb_set InitializePolicyAlternate,0x0804fbb1\n.global InitializePolicyModeEight\n.thumb_set InitializePolicyModeEight,0x080503e5");
void InitializeMenuRowPolicy(struct MenuContext *ctx) {
 struct MenuPanel *panel;
 struct MenuDescriptor *descriptor;
 struct MenuList *list;
 struct MenuCursor *cursor;
 struct MenuRecord *record;
 struct {void *continuation;struct MenuCursor *cursor;} snapshots;
 u8 mode;
 register void *new_continuation __asm__("r1");
 register void *continuation_panel __asm__("r0");
 register void *continuation_function __asm__("r1");
 int i;
 unsigned count;
 switch(ctx->mode) {
 case 1:case 3:case 4:case 5:case 6:
  panel=&ctx->panel;
  descriptor=&ctx->descriptor;
  list=&ctx->list;
  cursor=&ctx->cursor;
  snapshots.continuation=0;
  record=&ctx->root->records[ctx->mode];
  InitializePolicyPanel(panel,ctx->handle,(u16)(320+descriptor->tile),descriptor->count);
  mode=ctx->mode;
  snapshots.cursor=cursor;
  __asm__("" : "+r"(mode), "+m"(snapshots.cursor));
  switch(mode) {
   case 3:SetPolicyCallback(list,(void *)0x0804fae5,ctx);break;
   case 4:SetPolicyCallback(list,(void *)0x0804fb39,ctx);break;
   case 5:SetPolicyCallback(list,(void *)0x0804fb85,ctx);break;
  }
  list->value=record->value;
  count=QueryPolicyRows(list);
  ctx->count=count;
  for(i=0;i<(int)count;) {
   PopulatePolicyRow(ctx,(s16)i);
   ++i;
   count=ctx->count;
  }
  RefreshPolicyList(list);
  MarkPolicyRow(list,(s8)record->selected,11);
  if(ctx->mode==4) {
   for(i=0;i<ctx->count;++i) AdjustPolicyRow(ctx,(u8)i,1);
  }
  if(list->visible<descriptor->count) {
   new_continuation=(void *)0x08017f05;
   __asm__("" : "+r"(new_continuation));
   snapshots.continuation=new_continuation;
  }
  else ctx->flags|=16;
  continuation_function=(void *)0x08017e81;
  continuation_panel=panel;
  __asm__("" : "+r"(continuation_function), "+r"(continuation_panel));
  SetPolicyContinuation(continuation_panel,continuation_function,snapshots.continuation);
  SetPolicyCursor(cursor,record->selected);
  TickPolicyPanel(panel);
  if(*(u8 *)&ctx->flags&1) ShowPolicyCursor(snapshots.cursor,1);
  break;
 case 2:case 7:InitializePolicyAlternate(ctx);break;
 case 8:InitializePolicyModeEight(ctx);break;
 }
}
