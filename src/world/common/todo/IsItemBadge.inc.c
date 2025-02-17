#include "common.h"
#include "npc.h"

ApiStatus N(IsItemBadge)(Evt* script, s32 isInitialCall) {
    Bytecode* args = script->ptrReadPos;
    s32 itemIndex = evt_get_variable(script, *args++);

    script->varTable[0] = FALSE;
    if (gItemTable[itemIndex].typeFlags & ITEM_TYPE_FLAG_BADGE) {
        script->varTable[0] = TRUE;
    }

    return ApiStatus_DONE2;
}
