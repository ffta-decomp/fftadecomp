typedef unsigned char u8;
typedef unsigned int u32;
extern u32 IsMenuTaskFinished(u32);
extern void ReleaseMenuResource(void *);
u32 ReleaseFinishedMenuResources(u8 *menu)
{
 if((u8)IsMenuTaskFinished(menu[9])!=0){
  void **resource=(void **)(menu+148);
  if(*resource!=0){
   ReleaseMenuResource(*resource);
   *resource=0;
  }
  menu+=144;
  if(*(void **)menu!=0){
   ReleaseMenuResource(*(void **)menu);
   *(void **)menu=0;
  }
  return 1;
 }
 return 0;
}
asm(".global IsMenuTaskFinished\n.thumb_set IsMenuTaskFinished,0x080099a5\n.global ReleaseMenuResource\n.thumb_set ReleaseMenuResource,0x08005b41");
