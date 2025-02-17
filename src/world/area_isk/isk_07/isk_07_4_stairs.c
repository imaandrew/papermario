#include "isk_07.h"

EvtScript N(EVS_RedStairs_FlipCCW) = {
    EVT_CALL(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_BITS, COLLIDER_o1994, COLLIDER_FLAGS_UPPER_MASK)
    EVT_CALL(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_CLEAR_BITS, COLLIDER_o2000, COLLIDER_FLAGS_UPPER_MASK)
    EVT_CALL(PlaySoundAtCollider, COLLIDER_o2000, SOUND_80000002, 0)
    EVT_CALL(MakeLerp, 0, 90, 30, EASING_QUADRATIC_OUT)
    EVT_LABEL(10)
        EVT_CALL(UpdateLerp)
        EVT_CALL(RotateModel, MODEL_g311, LVar0, 0, 0, 1)
        EVT_WAIT(1)
        EVT_IF_EQ(LVar1, 1)
            EVT_GOTO(10)
        EVT_END_IF
    EVT_CALL(StopSound, SOUND_80000002)
    EVT_RETURN
    EVT_END
};

EvtScript N(EVS_RedStairs_FlipCW) = {
    EVT_CALL(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_CLEAR_BITS, COLLIDER_o1994, COLLIDER_FLAGS_UPPER_MASK)
    EVT_CALL(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_BITS, COLLIDER_o2000, COLLIDER_FLAGS_UPPER_MASK)
    EVT_CALL(PlaySoundAtCollider, COLLIDER_o1994, SOUND_80000002, 0)
    EVT_CALL(MakeLerp, 90, 0, 30, EASING_QUADRATIC_OUT)
    EVT_LABEL(10)
        EVT_CALL(UpdateLerp)
        EVT_CALL(RotateModel, MODEL_g311, LVar0, 0, 0, 1)
        EVT_WAIT(1)
        EVT_IF_EQ(LVar1, 1)
            EVT_GOTO(10)
        EVT_END_IF
    EVT_CALL(StopSound, SOUND_80000002)
    EVT_RETURN
    EVT_END
};

EvtScript N(EVS_FlipRedStairs) = {
    EVT_CALL(InterpCamTargetPos, 0, 1, 369, -349, 369, 20)
    EVT_CALL(SetCamSpeed, CAM_DEFAULT, EVT_FLOAT(1.0))
    EVT_CALL(UseSettingsFrom, CAM_DEFAULT, 369, -349, 369)
    EVT_CALL(SetPanTarget, CAM_DEFAULT, 369, -349, 369)
    EVT_WAIT(1)
    EVT_CALL(PanToTarget, CAM_DEFAULT, 0, 1)
    EVT_CALL(WaitForCam, CAM_DEFAULT, EVT_FLOAT(1.0))
    EVT_IF_EQ(MF_StairsFlipped, FALSE)
        EVT_EXEC_WAIT(N(EVS_RedStairs_FlipCCW))
        EVT_SET(MF_StairsFlipped, TRUE)
    EVT_ELSE
        EVT_EXEC_WAIT(N(EVS_RedStairs_FlipCW))
        EVT_SET(MF_StairsFlipped, FALSE)
    EVT_END_IF
    EVT_CALL(ShakeCam, CAM_DEFAULT, 0, 3, EVT_FLOAT(0.1))
    EVT_CALL(GetPlayerPos, LVar0, LVar1, LVar2)
    EVT_CALL(SetPanTarget, CAM_DEFAULT, LVar0, LVar1, LVar2)
    EVT_CALL(WaitForCam, CAM_DEFAULT, EVT_FLOAT(1.0))
    EVT_CALL(PanToTarget, CAM_DEFAULT, 0, 0)
    EVT_CALL(DisablePlayerInput, FALSE)
    EVT_SET(AF_ISK07_FlippingRedStairs, FALSE)
    EVT_RETURN
    EVT_END
};

EvtScript N(EVS_SetupStairs) = {
    EVT_CALL(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_CLEAR_BITS, COLLIDER_o1994, COLLIDER_FLAGS_UPPER_MASK)
    EVT_CALL(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_BITS, COLLIDER_o2000, COLLIDER_FLAGS_UPPER_MASK)
    EVT_SET(MF_StairsFlipped, FALSE)
    EVT_BIND_TRIGGER(EVT_PTR(N(EVS_FlipRedStairs)), TRIGGER_AREA_FLAG_SET, AF_ISK07_FlippingRedStairs, 1, 0)
    EVT_RETURN
    EVT_END
};
