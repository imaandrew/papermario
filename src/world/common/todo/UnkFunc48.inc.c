#include "common.h"
#include "npc.h"

ApiStatus N(UnkFunc48)(Evt* script, s32 isInitialCall) {
    gPlayerStatus.pitch = evt_get_variable(script, *script->ptrReadPos);
    return ApiStatus_DONE2;
}
