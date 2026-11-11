#include "ffta/unsigned_types.h"

struct NestedScriptContext {
    u16 unknown_0;
    u16 pc;
    const u8 *script;
};

/* Only the observed halfword has a known width; its game meaning is unresolved. */
struct ScriptGameStateView {
    u8 unknown_before_3c9c[0x3c9c];
    u16 transaction_value_3c9c;
};
extern struct ScriptGameStateView gEwramBase;
extern u8 *FindUnitPoolRecordById(u32 requested_id);
