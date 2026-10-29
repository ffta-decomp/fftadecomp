typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;
typedef signed int s32;
struct DefinitionRamp { u16 value; s16 remaining,error; u16 step,period,magnitude; };
struct AuthoredWindowRecord {
    u8 scaled_coordinates;
    u8 unknown_01[3];
    void *object;
    u16 unknown_08;
    u16 x_delta,y_delta;
    u8 x_duration,y_duration;
    struct DefinitionRamp x,y;
};
struct CoordinateOutputs { u16 x,y,z; };
typedef char RampSize12[sizeof(struct DefinitionRamp)==12?1:-1];
typedef char RecordSize40[sizeof(struct AuthoredWindowRecord)==40?1:-1];
/* Physical caller registers retain signed/fullword values; existing helpers
   consume the corresponding low16 values. Helper bodies are reused unchanged. */
extern void InitializeCoordinateRamp(struct DefinitionRamp*,s32,s32,u32) __asm__("RetailCall_080e0608");
extern void AdvanceCoordinateRamp(struct DefinitionRamp*) __asm__("RetailCall_080e064c");
extern u32 CoordinateRampComplete(const struct DefinitionRamp*) __asm__("RetailCall_080e0690");
extern void SetResourceCoordinates(void*,s32,s32,s32) __asm__("RetailCall_080107d4");
extern u32 ReadResourceCoordinates(const void*,u16*,u16*,u16*) __asm__("RetailCall_08011040");
extern void RemoveResource(void*) __asm__("RetailCall_08011428");
asm(".global RetailCall_080e0608\n.thumb_set RetailCall_080e0608,0x080e0609\n"
    ".global RetailCall_080e064c\n.thumb_set RetailCall_080e064c,0x080e064d\n"
    ".global RetailCall_080e0690\n.thumb_set RetailCall_080e0690,0x080e0691\n"
    ".global RetailCall_080107d4\n.thumb_set RetailCall_080107d4,0x080107d5\n"
    ".global RetailCall_08011040\n.thumb_set RetailCall_08011040,0x08011041\n"
    ".global RetailCall_08011428\n.thumb_set RetailCall_08011428,0x08011429\n");
