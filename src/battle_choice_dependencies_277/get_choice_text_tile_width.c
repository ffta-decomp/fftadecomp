typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
extern u32 ReadChoiceTextMetric(const u8 *text);
extern u32 RoundUpChoiceMetric(u16 value,u16 multiple);
__asm__(".global ReadChoiceTextMetric\n.thumb_set ReadChoiceTextMetric,0x08014779\n.global RoundUpChoiceMetric\n.thumb_set RoundUpChoiceMetric,0x08013bc1");
u32 GetChoiceTextTileWidth(const u8 *text)
{
 u32 metric=ReadChoiceTextMetric(text);
 metric=RoundUpChoiceMetric((u16)metric,8);
 return ((u16)metric)>>3;
}
