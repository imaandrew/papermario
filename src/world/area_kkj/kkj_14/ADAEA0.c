#include "kkj_14.h"

ApiStatus func_80240000_ADAEA0(Evt* script, s32 isInitialCall) {
    if (evt_get_variable(NULL, GB_StoryProgress) == -128) {
        sprintf(wMapBgName, "nok_bg");
    }
    return ApiStatus_BLOCK;
}

static char* N(exit_str_0) = "pra_01\0\0kkj_11\0\0kkj_01\0\0kkj_26\0\0kkj_15\0\0kkj_27\0\0kkj_26";
