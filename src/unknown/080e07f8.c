struct Task;
extern unsigned int IsTaskFinished(struct Task *);
extern void ReleaseTask(struct Task *);
__asm__(".global IsTaskFinished\n.thumb_set IsTaskFinished, 0x08005bb1\n.global ReleaseTask\n.thumb_set ReleaseTask, 0x08005b59");
static inline unsigned char Finished(struct Task *task)
{ if(IsTaskFinished(task) != 0) return 1; else return 0; }
struct Task *RemainingBand43_000E07F8(struct Task *task)
{
 if(task != (struct Task *)0) {
   if(Finished(task)) {ReleaseTask(task);return (struct Task *)0;}
 }
 return task;
}
