#include "interfaces.h"
u32 CoreRegion30_00060618(struct Object *object)
{
 u32 detail;struct Config *config=&object->config;
 u8 changed=0,navigation;u16 pressed=gKeys.pressed,result;
 if(pressed&4) {
  detail=P_Detail(object,(s16)C_Index(object->selector,(s8)object->effect.row));
  ((u16*)gRoot)[15]=detail;
  if((u16)detail) {((u16*)gRoot)[15]=detail-1;gRoot->command=8;return 1;}
 }
 if(pressed&2) {
  P_ChannelSound(1,105);
  if(config->flags&8)gRoot->command=2;else gRoot->command=1;
  *((u8*)gRoot+23)=object->type;return 1;
 }
 if(pressed&1) {
  result=P_Accept(object,(s16)C_Index(object->selector,(s8)object->effect.row),&changed);
  if((s16)result==-2){P_ChannelSound(1,107);return 0;}
  if(config->flags&4)gRoot->command=4;else gRoot->command=3;
  if(changed)P_Sound(156);
  else if((s16)result>=0)P_Sound(100);
  else P_ChannelSound(1,107);
  gRoot->result=result;*((u8*)gRoot+23)=object->type;return 1;
 }
 if((config->flags&32) && (pressed&512)) {
  result=P_Toggle(object,(s16)C_Index(object->selector,(s8)object->effect.row));
  if((s16)result==-2 || (s16)result==2){P_ChannelSound(1,107);return 0;}
  if((s16)result<2)P_Sound(156);
  gRoot->command=6;gRoot->result=result;*((u8*)gRoot+23)=object->type;return 1;
 }
 if((config->flags&64) && (pressed&256) && object->script){gRoot->command=7;return 1;}
 if(config->flags&1) {
  if(P_Preview(object) && object->script)P_Stop(object);
 } else if(config->flags&2) {
  navigation=P_Navigate(object);
  if(navigation && object->script)P_Stop(object);
  return navigation==2;
 }
 return 0;
}
