typedef unsigned char u8;
typedef signed char s8;
extern void *identity(void *,unsigned);
extern void set_cursor(void *,unsigned);
extern void prepare_row(void *,int);
extern void move_list(void *,unsigned,unsigned);
extern unsigned refresh_row(void *,unsigned,unsigned);
void CoreRegion_00050A8C(u8 *panel,u8 direction,u8 row,u8 wrap) {
 u8 *cursor=panel+104;
 u8 *scroll=panel+124;
 u8 *list=panel+72;
 identity(scroll,direction);
 if (!wrap) { register unsigned selected __asm__("r1")=row; __asm__("" : "+r"(selected)); set_cursor(cursor,selected); }
 else { prepare_row(panel,(s8)row); move_list(list,direction,1); }
 refresh_row(panel,cursor[17],0);
}
__asm__(".thumb_set identity,0x08017fbd\n.thumb_set set_cursor,0x08017fb1\n.thumb_set prepare_row,0x080505bd\n.thumb_set move_list,0x08017885\n.thumb_set refresh_row,0x08050b9d");
