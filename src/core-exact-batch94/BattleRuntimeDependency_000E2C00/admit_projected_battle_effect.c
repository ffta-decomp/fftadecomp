typedef signed short s16;
typedef unsigned char u8;
extern void ProjectPosition(int x,int height,int y,s16 *out_x,s16 *out_y);
extern void AdmitProjectedEffect(void *owner,int x,int y,unsigned int parameter_a,unsigned int parameter_b);
__asm__(".global ProjectPosition\n.thumb_set ProjectPosition,0x0801c985\n.global AdmitProjectedEffect\n.thumb_set AdmitProjectedEffect,0x080e29c5");
void AdmitProjectedBattleEffect(void *owner,s16 x,s16 height,s16 y,u8 parameter_a,u8 parameter_b) __asm__("BattleRuntimeDependency_000E2C00");
void AdmitProjectedBattleEffect(void *owner,s16 x,s16 height,s16 y,u8 parameter_a,u8 parameter_b)
{
    s16 projected_x;
    s16 projected_y;
    ProjectPosition(x,height,y,&projected_x,&projected_y);
    AdmitProjectedEffect(owner,projected_x,projected_y,parameter_a,parameter_b);
}
