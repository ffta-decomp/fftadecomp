typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;
struct UnitRecord;
struct PrimaryUnitPayload {
    u16 operation;
    u16 unknown2;
    s16 x;
    s16 y;
    s16 secondary_x;
    u16 height;
    struct UnitRecord *unit;
    u16 flags;
    u8 status;
    u8 unknown19;
    u8 kind;
    u8 unknown21[3];
    u8 transfer_count;
    u8 transfer_index;
    u16 transfer_bytes;
    u8 *destination;
    u8 *source;
    u32 field36;
};
struct UnitTaskRequest { u16 operation; u16 unknown2; struct UnitRecord *unit;
    u8 unknown8[12]; u16 flags; u8 unknown22[6]; };
struct TaskSlots { u8 unknown0[8]; void *primary; };
struct LayerBindings { u16 *unknown0; u16 *horizontal; };
struct DisplayShadow { u16 control; };
struct TaskVisualRecord;
typedef void (*MemoryCopy)(void *, const void *, u32);
extern struct TaskSlots *gUnitTaskContext;
extern struct LayerBindings gLayer2;
extern struct LayerBindings gLayer3;
extern struct DisplayShadow gDisplayShadow;
extern MemoryCopy gMemoryCopy;
extern void ConfigureLayer(u32, u32, u32, u32, u32, void *, void *);
extern void PreparePrimaryContents(struct PrimaryUnitPayload *, u8);
extern void UpdatePrimaryContents(struct PrimaryUnitPayload *, u8);
extern void ClearPrimaryContents(struct PrimaryUnitPayload *);
extern void RestorePrimaryContents(struct PrimaryUnitPayload *);
extern void PreparePrimaryTransfer(struct PrimaryUnitPayload *);
extern void DrawPrimaryContents(struct PrimaryUnitPayload *);
extern struct TaskVisualRecord *TakeUnitTaskRingRecord(void);
extern void QueuePrimaryTransfer(struct TaskVisualRecord *, void *, const void *, u32);
__asm__(".global gUnitTaskContext\n.set gUnitTaskContext,0x0200f440\n.global gLayer2\n.set gLayer2,0x030008b0\n.global gLayer3\n.set gLayer3,0x03000990\n.global gDisplayShadow\n.set gDisplayShadow,0x03000940\n.global gMemoryCopy\n.set gMemoryCopy,0x0836d4bc\n.global ConfigureLayer\n.thumb_set ConfigureLayer,0x0801e459\n.global PreparePrimaryContents\n.thumb_set PreparePrimaryContents,0x0802cabd\n.global UpdatePrimaryContents\n.thumb_set UpdatePrimaryContents,0x0802cbd5\n.global ClearPrimaryContents\n.thumb_set ClearPrimaryContents,0x0802cead\n.global RestorePrimaryContents\n.thumb_set RestorePrimaryContents,0x0802cfb1\n.global PreparePrimaryTransfer\n.thumb_set PreparePrimaryTransfer,0x0802d015\n.global DrawPrimaryContents\n.thumb_set DrawPrimaryContents,0x0802d05d\n.global TakeUnitTaskRingRecord\n.thumb_set TakeUnitTaskRingRecord,0x0802ba09\n.global QueuePrimaryTransfer\n.thumb_set QueuePrimaryTransfer,0x08000add\n.global _call_via_r3\n.thumb_set _call_via_r3,0x08142251");
typedef char transfer_offset_check[(u32)&((struct PrimaryUnitPayload *)0)->destination==28?1:-1];
/* Original request continuations remain separate; helpers may change payload fields. */
u32 RunPrimaryUnitTask(void *ignored_task, struct UnitTaskRequest *request,
                       struct PrimaryUnitPayload *payload)
{
    u32 flags;
    u32 next_operation;
    register u32 horizontal_origin __asm__("r1");
    switch (request->operation) {
    case 1:
        if (gUnitTaskContext != 0)
            gUnitTaskContext->primary = 0;
        break;
    case 0:
        ConfigureLayer(2, 1, 0, 0, 0, (void *)0x06008000, (void *)0x0600e000);
        ConfigureLayer(3, 1, 1, 0, 0, (void *)0x06008000, (void *)0x06005000);
        gDisplayShadow.control |= 0xc00;
        payload->status = 1;
        payload->unit = request->unit;
        payload->flags = request->flags;
        {
            register u32 initial_x __asm__("r2") = (u16)-136;
            register u32 origin_value __asm__("r3");
            register u16 *horizontal __asm__("r0");
            /* Lower the original halfword stores directly, without a separate signed member temporary. */
            __asm__("" : "+r"(initial_x));
            *(u16 *)&payload->x = (u16)initial_x;
            payload->y = 13;
            *(u16 *)&payload->secondary_x = (u16)initial_x;
            payload->height = 152;
            horizontal = gLayer2.horizontal;
            origin_value = 512;
            horizontal_origin = origin_value;
            __asm__("" : "+r"(horizontal_origin) : "r"(origin_value), "r"(horizontal), "r"(initial_x));
            *horizontal = horizontal_origin - initial_x;
        }
        goto write_layer3;
    case 261:
        if (!(payload->status & 16))
            break;
        goto draw;
    case 269:
        next_operation = 256;
        goto set_request;
    case 256:
        payload->kind = 7;
        PreparePrimaryContents(payload, 7);
        payload->operation = 257;
        request->operation = 267;
        goto write_both;
    case 266:
        payload->unit = request->unit;
        payload->flags = request->flags;
        payload->kind = (payload->flags >> 4) & 1;
        PreparePrimaryContents(payload, payload->kind);
        flags = (u16)(payload->flags & 16);
        payload->operation = flags != 0 ? 268 : 258;
        if (flags != 0)
            payload->secondary_x = -136;
        request->operation = 267;
        break;
    case 267:
        UpdatePrimaryContents(payload, payload->kind);
        DrawPrimaryContents(payload);
        next_operation = payload->operation;
        goto set_request;
    case 257:
        payload->x += 18;
        if (payload->transfer_index < payload->transfer_count) {
            QueuePrimaryTransfer(TakeUnitTaskRingRecord(), payload->destination,
                                 payload->source, payload->transfer_bytes >> 2);
            payload->source += payload->transfer_bytes;
            payload->destination += payload->transfer_bytes;
            if (++payload->transfer_index == payload->transfer_count)
                gMemoryCopy((void *)0x03003b20, (u8 *)gUnitTaskContext + 0x1f9c, 96);
        }
        if (payload->x >= 0 && payload->transfer_index == payload->transfer_count) {
            payload->x = 0;
            payload->status = 2;
            request->operation = 258;
        }
        payload->secondary_x = payload->x;
        DrawPrimaryContents(payload);
    write_both:
        {
            register u16 *horizontal __asm__("r2") = gLayer2.horizontal;
            u32 x_offset = (u16)payload->x;
            register u32 origin_value __asm__("r3") = 512;
            horizontal_origin = origin_value;
            /* Distinct original producer, outgoing origin and store-address roles are all defined. */
            __asm__("" : "+r"(horizontal_origin) : "r"(origin_value), "r"(horizontal), "r"(x_offset));
            *horizontal = horizontal_origin - x_offset;
        }
    write_layer3:
        *gLayer3.horizontal = horizontal_origin - (u16)payload->x;
        break;

    case 268:
        payload->secondary_x += 18;
        {
            register u32 initial_index __asm__("r0") = payload->transfer_index;
            register u32 initial_count __asm__("r1") = payload->transfer_count;
            /* These are the original pre-call count operands, not a cached post-call limit. */
            __asm__("" : "+r"(initial_index) : "r"(initial_count));
            if (initial_index < initial_count) {
            QueuePrimaryTransfer(TakeUnitTaskRingRecord(), payload->destination,
                                 payload->source, payload->transfer_bytes >> 2);
            payload->source += payload->transfer_bytes;
            payload->destination += payload->transfer_bytes;
            {
                register u32 advanced_index __asm__("r0") = ++payload->transfer_index;
                register u32 current_count __asm__("r2") = payload->transfer_count;
                /* The queue/copy helper may replace the live count; obtain it again. */
                __asm__("" : "+r"(advanced_index) : "r"(current_count));
                if (advanced_index == current_count)
                    gMemoryCopy((void *)0x03003b20, (u8 *)gUnitTaskContext + 0x1f9c, 96);
            }
            }
        }
        if (payload->secondary_x >= 0 && payload->transfer_index == payload->transfer_count) {
            payload->secondary_x = payload->x;
            payload->status = 2;
            request->operation = 258;
        }
        goto draw;
    case 259:
        request->operation = 261;
        if (payload->status != 3) {
            request->operation = 262;
            *gLayer2.horizontal = 512 - (u16)payload->x;
            *gLayer3.horizontal = 512 - (u16)payload->x;
        }
        goto draw;
    case 258:
    draw:
        DrawPrimaryContents(payload);
        break;
    case 262:
        payload->x -= 18;
        if (payload->x <= -136) {
            payload->x = -136;
            PreparePrimaryTransfer(payload);
            request->operation = 263;
        }
        payload->secondary_x = payload->x;
        *gLayer2.horizontal = 512 - (u16)payload->x;
        *gLayer3.horizontal = 512 - (u16)payload->x;
        break;
    case 263:
        *gLayer2.horizontal = 0;
        *gLayer3.horizontal = 0;
        request->operation = 261;
        payload->status = 3;
        break;
    case 260:
        payload->unit = request->unit;
        payload->flags = request->flags;
        payload->x = -136;
        payload->y = 13;
        payload->secondary_x = -136;
        payload->height = 152;
        payload->field36 = 0;
        ConfigureLayer(2, 1, 0, 0, 0, (void *)0x06008000, (void *)0x0600e000);
        ConfigureLayer(3, 1, 1, 0, 0, (void *)0x06008000, (void *)0x06005000);
        gDisplayShadow.control |= 0xc00;
        *gLayer2.horizontal = 512 - (u16)payload->x;
        *gLayer3.horizontal = 512 - (u16)payload->x;
        payload->status = 1;
        break;
    case 264:
        if (!(payload->status & 16)) {
            ClearPrimaryContents(payload);
            payload->status |= 16;
        }
        DrawPrimaryContents(payload);
        next_operation = 261;
        goto set_request;
    case 265:
        if (payload->status != 2) {
            RestorePrimaryContents(payload);
            payload->status = 2;
        }
        DrawPrimaryContents(payload);
        next_operation = 258;
    set_request:
        request->operation = next_operation;
        break;
    }
    return 0;
}
