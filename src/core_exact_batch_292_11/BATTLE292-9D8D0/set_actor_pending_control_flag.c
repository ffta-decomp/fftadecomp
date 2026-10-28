typedef unsigned char u8;
typedef struct {u8 unknown0[12];u8 flags;} ActorControl;
void SetActorPendingControlFlag(ActorControl *actor,u8 control)
{
 if(control==0)actor->flags|=2;
 else actor->flags&=253;
}
