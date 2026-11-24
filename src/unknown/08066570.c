typedef unsigned char u8;
extern unsigned QueryReleaseReady(unsigned);
extern void ReleaseTask(void *);
__asm__(".global QueryReleaseReady\n.thumb_set QueryReleaseReady,0x080099a5\n.global ReleaseTask\n.thumb_set ReleaseTask,0x08005b41");
unsigned TryReleaseMenuChildren(u8 *context) {
 if((u8)QueryReleaseReady(context[9])) {
  void **second=(void **)(context+156);
  if(*second) {ReleaseTask(*second);*second=0;}
  {
   void **first=(void **)(context+152);
   if(*first) {ReleaseTask(*first);*first=0;}
  }
  return 1;
 }
 return 0;
}
