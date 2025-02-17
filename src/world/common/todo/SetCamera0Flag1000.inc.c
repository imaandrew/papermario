#include "common.h"
#include "npc.h"
#include "camera.h"

ApiStatus N(SetCamera0Flag1000)(Evt* script, s32 isInitialCall) {
    Camera* camera = &gCameras[CAM_DEFAULT];

    camera->flags |= CAMERA_FLAGS_1000;
    return ApiStatus_DONE2;
}
