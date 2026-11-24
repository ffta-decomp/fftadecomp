#include "abi/interfaces/08131dec_bindings.h"

void CaptureAffectedByte105(volatile ApplicationContext *context)
{
    ApplicationHalf(context, 24) = ApplicationByte(context->affected, 261);
}
