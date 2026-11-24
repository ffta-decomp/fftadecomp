typedef unsigned char u8;typedef signed char s8;typedef unsigned short u16;typedef signed short s16;typedef unsigned int u32;typedef signed int s32;
typedef struct {u8 unknown0[248];u8 facing;} Unit;
typedef struct {Unit *unit;u8 unknown4[4];s16 x,y,z;u8 unknown14[17];s8 facing;} Actor;
typedef struct {Actor *actor;u32 unknown4;void *auxiliary;u16 flags,result;u8 unknown16[14];s16 effect_a,effect_b;u8 unknown34[10];} Result;
typedef struct {Actor *source;u8 unknown4[6];u8 origin_x,origin_y;u8 unknown12[4];u16 mode,ability;s16 x,y,z;u8 unknown26[6];Result records[15];u8 unknown692[12];u8 count;} Transaction;
u8 Category(Unit*,u16) __asm__("RetailCall_0812ee98");
s8 Direction(s8,s8) __asm__("RetailCall_0809d6bc");
void Action(Actor*,u16,s8,u16) __asm__("RetailCall_0809836c");
void Reaction(s8,s8,s8*,s8*) __asm__("RetailCall_080a1d84");
void SetEffect(Actor*,u16,u16) __asm__("RetailCall_0809a570");
void UpdateDirection(Actor*,s8,u32) __asm__("RetailCall_0809d854");
void Effect(s32,s32,s32,s32,s32) __asm__("RetailCall_080a92e4");
s32 AbilityProperty(u32,u32) __asm__("RetailCall_080ca7a4");
void Sound(u32) __asm__("RetailCall_08141520");void ChannelSound(u32,u32) __asm__("RetailCall_08141570");
/* Coordinates store five fractional bits. Differences narrow to signed bytes
 * before choosing a facing; callbacks require fresh actor/flag loads. */
void ApplyBattleResultFeedback(Transaction *transaction)
{
 s32 special_hit=0,any_hit=0,any_miss=0,index;
 s8 reaction_a,reaction_b;
 if(!transaction->count&&!transaction->mode&&
    (Category(transaction->source->unit,transaction->ability)==13||
     Category(transaction->source->unit,transaction->ability)==14||
     Category(transaction->source->unit,transaction->ability)==19)){
  Effect(0,transaction->x,transaction->y,transaction->z,21);
  ChannelSound(2,141);
 }
 for(index=0;index<transaction->count;++index){
  switch(transaction->records[index].result){
  case 3:case 4:{
   s8 direction=Direction((s8)((transaction->source->x>>5)-transaction->origin_x),(s8)((transaction->source->z>>5)-transaction->origin_y));
   Action(transaction->records[index].actor,3,direction,0);
   transaction->records[index].actor->unit->facing=transaction->records[index].actor->facing;
   ChannelSound(1,236);break;
  }
  case 1:
   any_hit=1;
   if(transaction->records[index].flags&32)special_hit=1;
   Action(transaction->records[index].actor,5,transaction->records[index].actor->facing,0);
   Reaction(transaction->source->facing,transaction->records[index].actor->facing,&reaction_a,&reaction_b);
   if(reaction_a)SetEffect(transaction->records[index].actor,0,512);
   if(reaction_b)SetEffect(transaction->records[index].actor,0,1024);
   break;
  case 2:
   if(!transaction->records[index].auxiliary){
    s8 direction=Direction((s8)((transaction->source->x>>5)-transaction->origin_x),(s8)((transaction->source->z>>5)-transaction->origin_y));
    Action(transaction->records[index].actor,4,direction,0);
    transaction->records[index].actor->unit->facing=transaction->records[index].actor->facing;
   }
   if(transaction->ability){
    switch(Category(transaction->source->unit,transaction->ability)){
    case 1:case 2:case 3:case 4:case 5:case 6:case 7:case 8:case 9:case 15:any_miss=1;break;
    case 10:case 11:case 12:case 14:case 16:case 17:case 18:any_miss=1;break;
    }
   }else any_miss=1;
   UpdateDirection(transaction->records[index].actor,transaction->source->facing,3);
   break;
  }
  if(transaction->records[index].flags&32){
   Actor *actor=transaction->records[index].actor;
   Effect(0,actor->x,actor->y,actor->z,20);
  }
  if(transaction->records[index].flags&1){
   Effect(transaction->records[index].effect_a,transaction->records[index].actor->x,(s16)(transaction->records[index].actor->y+48),transaction->records[index].actor->z,0);
  }
  if(transaction->records[index].flags&2){
   Effect(transaction->records[index].effect_b,transaction->records[index].actor->x,(s16)(transaction->records[index].actor->y+48),transaction->records[index].actor->z,0);
  }
 }
 if(!any_hit){if(any_miss==1)Sound(133);}
 else if(special_hit)Sound(139);
 else{
  u16 ability=transaction->ability;
  s32 property;
  if(!ability)property=-1;
  else property=AbilityProperty(ability,3);
  switch(property){
  case 1:case 2:case 3:case 4:case 5:case 6:case 7:case 9:Sound(123);break;
  case 8:case 15:Sound(124);break;
  case 10:case 11:case 12:Sound(125);break;
  case 13:case 14:Sound(138);break;
  case 16:
   switch(ability){
   case 206:case 207:case 209:Sound(131);break;
   case 208:case 211:Sound(132);break;
   case 203:Sound(130);break;
   default:Sound(129);break;
   }break;
  case 19:break;
  default:Sound(126);break;
  }
 }
}
typedef char CheckResult[(sizeof(Result)==44)?1:-1];

asm(".global RetailCall_0809836c\n.thumb_set RetailCall_0809836c,0x0809836d\n.global RetailCall_0809a570\n.thumb_set RetailCall_0809a570,0x0809a571\n.global RetailCall_0809d6bc\n.thumb_set RetailCall_0809d6bc,0x0809d6bd\n.global RetailCall_0809d854\n.thumb_set RetailCall_0809d854,0x0809d855\n.global RetailCall_080a1d84\n.thumb_set RetailCall_080a1d84,0x080a1d85\n.global RetailCall_080a92e4\n.thumb_set RetailCall_080a92e4,0x080a92e5\n.global RetailCall_080ca7a4\n.thumb_set RetailCall_080ca7a4,0x080ca7a5\n.global RetailCall_0812ee98\n.thumb_set RetailCall_0812ee98,0x0812ee99\n.global RetailCall_08141520\n.thumb_set RetailCall_08141520,0x08141521\n.global RetailCall_08141570\n.thumb_set RetailCall_08141570,0x08141571\n");
