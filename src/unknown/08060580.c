typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;
struct ContentContext {u8 observed0[27];u8 origin;u8 observed28[4];u8 *entries[0];};
extern struct ContentContext *gContentContext;
extern u16 gMenuContentIds[];
extern unsigned MapMenuEntryId(unsigned);
__asm__(".global gContentContext\n.set gContentContext,0x0200f44c\n.global gMenuContentIds\n.set gMenuContentIds,0x0852a13e\n.global MapMenuEntryId\n.thumb_set MapMenuEntryId,0x080cb53d");
u16 ResolveMenuContentId(u8 *context,u16 row) {
 u16 result=0;
 switch(context[0]) {
 case 1: result=gMenuContentIds[41+(s16)row]+1; break;
 case 5: {
  if((s16)row<=1) {
   struct ContentContext *root=gContentContext;
   int index=(s16)row-2;
   u8 *entry;
   __asm__("" : "+r"(root), "+r"(index));
   entry=root->entries[index+root->origin];
   if(entry==0 || entry[0]==0) result=gMenuContentIds[64]+1;
   else {
    __asm__("" : "+r"(entry));
    result=MapMenuEntryId(entry[0])+1;
   }
  } else result=gMenuContentIds[67]+1;
  break;
 }
 case 6: result=MapMenuEntryId(gContentContext->entries[(s16)row][0])+1;break;
 }
 return result;
}
