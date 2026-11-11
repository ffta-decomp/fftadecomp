typedef unsigned char u8;
struct ContentRange { u8 prefix[28]; u8 range[108]; };
struct ContentRangeSet { u8 prefix[4]; struct ContentRange entries[6]; };
extern void ClearContentRange(void *range);
void ClearContentRanges(struct ContentRangeSet *set)
{
 u8 index;
 for(index=0;index<6;index++)
  ClearContentRange(set->entries[index].range);
}
__asm__(".global Registered39_001379C8\n.thumb_set Registered39_001379C8,ClearContentRanges\n.global ClearContentRange\n.thumb_set ClearContentRange,0x081378ed\n");
