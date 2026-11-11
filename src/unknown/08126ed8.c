typedef unsigned char u8; typedef unsigned int u32;
struct Block { u32 words[32]; u32 count; };
typedef void (*CopyFunction)(void *,const void *,u32);
extern struct Block *GetBlock(u32) __asm__("RetailCall_08121c58");
void CopySceneSequence(void*,u8,u8,u8) __asm__("CoreRegion_00126ED8");
void CopySceneSequence(void *output,u8 first,u8 count,u8 reverse)
{
    struct Block *block; u8 *out=output; int i,j,n;
    if (!reverse) {
        block=GetBlock(first);
        for(i=0;i<count;) {
            if (i>=count-1)
                (*(CopyFunction*)0x0836d4bc)(out,block,block->count*4);
            else
                (*(CopyFunction*)0x0836d4bc)(out,block,(block->count-1)*4);
            out+=block->count*4-4;
            i++;
            block++;
        }
    } else {
        for(i=0;i<count;) {
            block=GetBlock((u8)(first+count-1-i));
            if(i>=count-1) n=block->count;
            else n=block->count-1;
            j=0;
            i++;
            while(j<n) {
                j++;
                (*(CopyFunction*)0x0836d4bc)(out,&block->words[block->count-j],4);
                out+=4;
            }
        }
    }
}
/* Original function/callback identities; no instructions emitted. */
__asm__(".global RetailCall_08121c58\n.thumb_set RetailCall_08121c58,0x08121c59");
__asm__(".global _call_via_r3\n.thumb_set _call_via_r3,0x08142251");
