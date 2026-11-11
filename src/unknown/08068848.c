typedef unsigned char u8;
typedef unsigned int u32;
extern void RefreshMenuContent(void *);
extern void PublishAssociatedSelection(void *);
void RefreshAssociatedMenu(u8 *menu)
{
 RefreshMenuContent(menu);
 if(*(u32 *)(menu+16)!=0) PublishAssociatedSelection(menu);
}
asm(".global RefreshMenuContent\n.thumb_set RefreshMenuContent,0x080682e5\n.global PublishAssociatedSelection\n.thumb_set PublishAssociatedSelection,0x08066c29");
