typedef unsigned char u8;
typedef unsigned int u32;

typedef struct ScenePlacementUnit {
    u8 unknown00[4];
    u8 presence_code;
    u8 unknown05[241];
    u8 placement_x;
    u8 placement_y;
    u8 facing;
    u8 saved_placement_x;
    u8 saved_placement_y;
    u8 unknown251[13];
} ScenePlacementUnit;
typedef char ScenePlacementUnitSizeCheck[sizeof(ScenePlacementUnit) == 264 ? 1 : -1];

typedef struct ScenePlacementEntity {
    ScenePlacementUnit *unit;
} ScenePlacementEntity;

typedef struct ScriptActorBinding {
    u32 unknown00;
    ScenePlacementUnit *unit;
} ScriptActorBinding;

extern ScenePlacementUnit gUnitPoolA[12];
void *GetSceneActionContextBase(void);
ScenePlacementEntity *ResolvePlacementEntity(void *, ScenePlacementUnit *)
    __asm__("PlacementHelper_08092440");
void ApplyPlacementState(ScenePlacementEntity *, u32, u32)
    __asm__("PlacementHelper_08124710");
int UnitField27HasBit15(const ScenePlacementUnit *);
ScriptActorBinding *ResolveScriptActorBinding(u32)
    __asm__("PlacementHelper_08121C70");
