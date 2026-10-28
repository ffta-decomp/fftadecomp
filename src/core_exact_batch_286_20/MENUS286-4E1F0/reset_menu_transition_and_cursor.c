typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
extern u8 *GetMenuTaskPayload(void *);
extern void EnablePrimaryMenuCursor(void *);
extern void RefreshModeOneSelection(void *);
void ResetMenuTransitionAndCursor(void *task)
{
 u8 *menu=GetMenuTaskPayload(task);
 u32 flags;
 register u32 request_mask asm("r0");
 *(u16 *)(menu+6)=0;
 flags=*(u16 *)(menu+4);
 request_mask=32;
 asm("" : "+r" (request_mask) : "r" (flags));
 request_mask|=flags;
 asm("" : "+r" (request_mask));
 *(u16 *)(menu+4)=request_mask;
 if(menu[8]<=8)EnablePrimaryMenuCursor(menu);
 if(menu[8]==1)RefreshModeOneSelection(menu);
}
asm(".global GetMenuTaskPayload\n.thumb_set GetMenuTaskPayload,0x08005bfd\n.global EnablePrimaryMenuCursor\n.thumb_set EnablePrimaryMenuCursor,0x08050e35\n.global RefreshModeOneSelection\n.thumb_set RefreshModeOneSelection,0x08050e55");
