typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;
struct TaskNode;
struct UnitRecord;
struct UnitTaskPayload {
    u16 operation;
    u16 unknown2;
    s16 x;
    s16 y;
    u32 unknown8;
    struct UnitRecord *unit;
    u16 flags;
    u8 status;
};
struct UnitTaskRequest {
    u16 operation;
    u16 unknown2;
    struct UnitRecord *unit;
    u8 unknown8[12];
    u16 flags;
    u8 unknown22[6];
};
struct UnitTaskSlots { u8 unknown0[12]; struct TaskNode *secondary; };
extern struct UnitTaskSlots *gUnitTaskContext;
struct InputState { u16 unknown0; u16 edges; };
extern struct InputState gInputState;
extern void InitializeSecondaryTaskPosition(struct UnitTaskPayload *);
extern void PrepareSecondaryTaskContents(struct UnitTaskPayload *);
extern void UpdateSecondaryTaskContents(struct UnitTaskPayload *);
extern void DrawSecondaryTaskContents(struct UnitTaskPayload *);
extern void PlayTaskSound(u32);
extern u32 InvokeTaskCallback(struct TaskNode *, struct UnitTaskRequest *);
__asm__(".global gUnitTaskContext\n.set gUnitTaskContext,0x0200f440\n.global gInputState\n.set gInputState,0x03000000\n.global InitializeSecondaryTaskPosition\n.thumb_set InitializeSecondaryTaskPosition,0x0802d521\n.global PrepareSecondaryTaskContents\n.thumb_set PrepareSecondaryTaskContents,0x0802c169\n.global UpdateSecondaryTaskContents\n.thumb_set UpdateSecondaryTaskContents,0x0802c271\n.global DrawSecondaryTaskContents\n.thumb_set DrawSecondaryTaskContents,0x0802c399\n.global PlayTaskSound\n.thumb_set PlayTaskSound,0x08141521\n.global InvokeTaskCallback\n.thumb_set InvokeTaskCallback,0x08005c05");
typedef char unit_offset_check[(u32)&((struct UnitTaskPayload *)0)->unit==12?1:-1];
typedef char status_offset_check[(u32)&((struct UnitTaskPayload *)0)->status==18?1:-1];
typedef char request_size_check[sizeof(struct UnitTaskRequest)==28?1:-1];
/* Requests and payload retain their entry addresses while helper-visible fields reload. */
u32 RunSecondaryUnitTask(struct TaskNode *task, struct UnitTaskRequest *request,
                         struct UnitTaskPayload *payload)
{
    u32 finished;
    u32 horizontal;
    switch (request->operation) {
    case 1:
        if (gUnitTaskContext != 0)
            gUnitTaskContext->secondary = 0;
        break;
    case 0:
        payload->status = 1;
        payload->unit = request->unit;
        payload->flags = request->flags;
        InitializeSecondaryTaskPosition(payload);
        break;
    case 269:
        request->operation = 256;
        break;
    case 256:
        PrepareSecondaryTaskContents(payload);
        payload->operation = 257;
        request->operation = 267;
        break;
    case 266:
        payload->unit = request->unit;
        payload->flags = request->flags;
        PrepareSecondaryTaskContents(payload);
        payload->operation = 258;
        horizontal = (u16)(payload->flags & 64);
        if (horizontal != 0)
            horizontal = 160;
        payload->x = horizontal;
        payload->status = 2;
        break;
    case 267:
        UpdateSecondaryTaskContents(payload);
        DrawSecondaryTaskContents(payload);
        request->operation = payload->operation;
        break;
    case 257:
        finished = 0;
        if (payload->flags & 64) {
            payload->x -= 12;
            if (payload->x <= 160) {
                payload->x = 160;
                finished = 1;
            }
        } else {
            payload->x += 12;
            if (payload->x >= 0) {
                payload->x = 0;
                finished = 1;
            }
        }
        DrawSecondaryTaskContents(payload);
        if (finished != 0) {
            payload->status = 2;
            request->operation = 258;
        }
        break;
    case 258:
        if (!(payload->flags & 16) && (gInputState.edges & 4)) {
            PlayTaskSound(156);
            {
                /* Keep the observed settings root before its byte181 field. */
                register u8 *selection __asm__("r1") = (u8 *)0x020020d0;
                __asm__("" : "+r"(selection));
                selection += 181;
                *selection ^= 1;
            }
            request->operation = 266;
            request->unit = payload->unit;
            request->flags = payload->flags;
            InvokeTaskCallback(task, request);
            request->operation = 267;
        }
        DrawSecondaryTaskContents(payload);
        break;
    case 259:
        request->operation = 261;
        if (payload->flags & 64)
            payload->x = 204;
        else
            payload->x = -44;
        if (payload->status != 3) {
            payload->status = 3;
            DrawSecondaryTaskContents(payload);
        }
        break;
    }
    return 0;
}
