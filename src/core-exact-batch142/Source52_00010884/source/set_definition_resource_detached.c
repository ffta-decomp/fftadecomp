typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
struct Resource {u8 unknown0[20];u16 flags;u8 unknown22[6];u8 list;u8 mode;u8 unknown30[26];struct Resource *previous,*next;};
extern void ReconcileDefinitionResource(struct Resource*);
void SetDefinitionResourceDetached(struct Resource*,u8) __asm__("Source52_00010884");
void SetDefinitionResourceDetached(struct Resource *incoming,u8 detached)
{
    register struct Resource *entry __asm__("r0")=incoming;
    register u32 request __asm__("r1")=(u32)detached<<24;
    struct Resource *resource;
    /* Preserve full shifted LOW8 truth and entry pointer before the native capture. */
    __asm__("" : "+r"(request), "+r"(entry));
    resource=entry;
    if(request) {
        register u32 active __asm__("r0");
        register u32 mode __asm__("r0")=resource->mode;
        if(mode==0)goto activeA;
        /* Retain the distinct native compare after the zero-mode edge. */
        __asm__("" : "+r"(mode));
        if(mode==1 || (resource->flags&128)) {
activeA:
            active=1;
        }else active=0;
        /* Native code materializes this numeric predicate before testing it. */
        __asm__("" : "+r"(active));
        if(active)return;
        resource->flags|=128;
    }else {
        register u32 active __asm__("r0");
        register u32 mode __asm__("r0")=resource->mode;
        if(mode==0)goto activeB;
        /* Retain the distinct native compare after the zero-mode edge. */
        __asm__("" : "+r"(mode));
        if(mode==1 || (resource->flags&128)) {
activeB:
            active=1;
        }else active=0;
        __asm__("" : "+r"(active));
        if(!active)return;
        resource->flags&=0xff7f;
    }
    {
    struct Resource **head=0;
    switch(resource->list) {
    case 0:head=(struct Resource**)0x02009178;break;
    case 1:head=(struct Resource**)0x0200917c;break;
    case 2:head=(struct Resource**)0x02009174;break;
    case 3:head=(struct Resource**)0x02009180;break;
    }
    {
        struct Resource *previous=resource->previous;
        struct Resource *next=resource->next;
        if(previous)previous->next=next;
        else *head=next;
        if(next)next->previous=previous;
    }
    ReconcileDefinitionResource(resource);
    }
}
__asm__(".global ReconcileDefinitionResource\n.thumb_set ReconcileDefinitionResource,0x080105c5");
