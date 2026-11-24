typedef unsigned char u8; typedef signed char s8;
extern void identity(void *,unsigned); extern void set_cursor(void *,unsigned); extern void prepare_row(int); extern void move_list(void *,unsigned,unsigned); extern void mark_row(void *,int,unsigned); extern unsigned row_index(void *,int); extern void refresh(unsigned);
void CoreFrontier_00009394(u8 direction,u8 row,u8 wrap){
 u8 *root=*(u8 **)0x02009188; u8 *cursor=root+784; u8 *scroll=root+804; u8 *list=root+752;
 identity(scroll,direction);
 if(!wrap){register unsigned selected __asm__("r1")=row;__asm__("" : "+r"(selected));set_cursor(cursor,selected);} else {prepare_row((s8)row);move_list(list,direction,1);}
 mark_row(list,*(s8 *)(cursor+17),11);
 refresh((u8)row_index(list,*(s8 *)(cursor+17)));
}
__asm__(".thumb_set identity,0x08017fbd\n.thumb_set set_cursor,0x08017fb1\n.thumb_set prepare_row,0x08008f95\n.thumb_set move_list,0x08017885\n.thumb_set mark_row,0x08017af5\n.thumb_set row_index,0x08017b69\n.thumb_set refresh,0x08009415");
