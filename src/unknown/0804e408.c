typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;
struct MessageSelectionRecord {u16 value;u16 selection;};
struct MessageMenuRoot {u8 prefix[0x53c];struct MessageSelectionRecord records[0];};
struct MessageMenuContext {struct MessageMenuRoot *root;u16 flags;s16 result;u8 mode;u8 unknown9[89];u16 value;u8 unknown100[21];u8 selection;};
struct MenuMessage {u16 state;u8 unknown2[18];u16 mode;};
extern struct MessageMenuRoot *gMessageMenuRoot;
extern void InitializeMessageMenu(void *);
extern unsigned WaitMessageMenu(void *);
extern unsigned QueryMessageExit(void *);
extern unsigned QueryMessageContinue(void *);
extern void ResetMessageMenu(void *);
extern unsigned WaitMessageTransition(void *);
extern unsigned UpdateMessageInput(void *);
extern void TickMessageMenu(void *);
extern void ExitMessagePanel(void *);
extern void RefreshMessageSelection(void *);
extern void RestoreMessageMenu(void *);
extern void UpdateMessageMenu(void *);
__asm__(".global gMessageMenuRoot\n.set gMessageMenuRoot,0x201f548\n.global InitializeMessageMenu\n.thumb_set InitializeMessageMenu,0x804ed6d\n.global WaitMessageMenu\n.thumb_set WaitMessageMenu,0x804ef69\n.global QueryMessageExit\n.thumb_set QueryMessageExit,0x8050e15\n.global QueryMessageContinue\n.thumb_set QueryMessageContinue,0x804ef91\n.global ResetMessageMenu\n.thumb_set ResetMessageMenu,0x804f061\n.global WaitMessageTransition\n.thumb_set WaitMessageTransition,0x804f0f5\n.global UpdateMessageInput\n.thumb_set UpdateMessageInput,0x804f14d\n.global TickMessageMenu\n.thumb_set TickMessageMenu,0x804f371\n.global ExitMessagePanel\n.thumb_set ExitMessagePanel,0x8050de9\n.global RefreshMessageSelection\n.thumb_set RefreshMessageSelection,0x8050e1d\n.global RestoreMessageMenu\n.thumb_set RestoreMessageMenu,0x8050e29");
unsigned StepMenuMessage(void *ignored,struct MenuMessage *message,struct MessageMenuContext *ctx) {
 struct MessageSelectionRecord *record;
 switch(message->state) {
 case 0:
  ctx->mode=message->mode;
  ctx->root=gMessageMenuRoot;
  break;
 case 256:
  InitializeMessageMenu(ctx);
  message->state=257;
  break;
 case 257:
  if((u8)WaitMessageMenu(ctx)) {
   if((u8)QueryMessageExit(ctx)) message->state=261;
   else message->state=259;
  }
  break;
 case 263:
  if((u8)WaitMessageTransition(ctx)) message->state=259;
  break; case 259:
  if((u8)UpdateMessageInput(ctx)) {
   switch(ctx->result) {
   default:
    record=&ctx->root->records[ctx->mode];
    record->value=ctx->value;
    record->selection=ctx->selection;
    message->state=261;
    break;
   case -4:
    ResetMessageMenu(ctx);
    ctx->result=0;
    message->state=263;
    break;
   case -3:
    ctx->result=0;
    message->state=262;
    break;
   }
  }
  TickMessageMenu(ctx);
  break;
 case 262:
  RefreshMessageSelection(ctx);
  TickMessageMenu(ctx);
  message->state=259;
  break;
 case 261:
  if(ctx->flags&128) {
   ctx->flags&=0xff7f;
   message->state=3;
  } else if(ctx->flags&64) {
   ctx->flags&=0xffbf;
   ExitMessagePanel(ctx);
   message->state=258;
  } else if(ctx->flags&32) {
   ctx->flags&=0xffdf;
   message->state=259;
  }
  break;
 case 258:
  if((u8)QueryMessageContinue(ctx)) {
   ctx->result=-2;
   message->state=261;
  }
  break;
 case 1:break;

 }
 if(message->state>256) RestoreMessageMenu(ctx);
 return 0;
}
