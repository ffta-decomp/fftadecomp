/* Method-local interface declarations from the frozen build. */
typedef unsigned char u8;
extern u8 gPhase;
extern u8 gLocalFlag;
extern u8 gTask[];
extern u8 gTaskData[];
extern u8 gTaskWork[];
extern void CallbackA(void);
extern void CallbackB(void);
extern void Setup(void);
extern void InitTask(void *,void *,void *,int);
extern void SetTaskCallback(void *,int,void (*)(void));
extern void PollTask(void *,int);
extern u8 GetGameFlag(int);
extern void TriggerEvent(int);
extern void ContinueEvent(void);
extern void Teardown(void);
extern u8 CheckCompletion(void);
extern void FinishMode(void);
extern void ChangeMode(int);

asm(".global gPhase\n.set gPhase,0x200f390\n.global gLocalFlag\n.set gLocalFlag,0x300280c\n.global gTask\n.set gTask,0x200f3a0\n.global gTaskData\n.set gTaskData,0x200f3b8\n.global gTaskWork\n.set gTaskWork,0x200f3b4\n.global CallbackA\n.thumb_set CallbackA,0x813c0ed\n.global CallbackB\n.thumb_set CallbackB,0x813db35\n.global Setup\n.thumb_set Setup,0x813c065\n.global InitTask\n.thumb_set InitTask,0x8006a7d\n.global SetTaskCallback\n.thumb_set SetTaskCallback,0x8006add\n.global PollTask\n.thumb_set PollTask,0x80069f5\n.global GetGameFlag\n.thumb_set GetGameFlag,0x80c9541\n.global TriggerEvent\n.thumb_set TriggerEvent,0x8009afd\n.global ContinueEvent\n.thumb_set ContinueEvent,0x8009fd1\n.global Teardown\n.thumb_set Teardown,0x813c0a9\n.global CheckCompletion\n.thumb_set CheckCompletion,0x800395d\n.global FinishMode\n.thumb_set FinishMode,0x8003919\n.global ChangeMode\n.thumb_set ChangeMode,0x80038c9\n");
void AdvancePairedTaskSceneMode(void *unused,u8 *state)
{
    switch (*state) {
    case 0:
        gLocalFlag = 0;
        Setup();
        InitTask(gTask,gTaskData,gTaskWork,1);
        SetTaskCallback(gTask,0,CallbackA);
        gPhase = *state = 1;
        break;
    case 1:
        PollTask(gTask,1);
        *state = gPhase;
        if (GetGameFlag(68) && *state == 2) {
            TriggerEvent(5);
            ContinueEvent();
            *state = 255;
        }
        break;
    case 2:
        InitTask(gTask,gTaskData,gTaskWork,1);
        SetTaskCallback(gTask,0,CallbackB);
        gPhase = *state = 3;
        break;
    case 3:
        PollTask(gTask,1);
        *state = gPhase;
        break;
    case 255:
        Teardown();
        if (CheckCompletion()) FinishMode();
        else ChangeMode(5);
        break;
    }
}
