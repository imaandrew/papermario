#include "iwa_03.h"

SlideParams N(SlideData) = {
    .heading = 89.0f,
    .maxDescendAccel = 0.41f,
    .launchVelocity = -0.25f,
    .maxDescendVelocity = 16.0f,
    .integrator = { 9.612, -0.452, 0.003, -0.023 },
};

API_CALLABLE(N(SetPlayerSliding)) {
    gPlayerStatus.slideParams = script->varTablePtr[0];
    gPlayerStatus.flags |= PS_FLAGS_SLIDING;
    return ApiStatus_DONE2;
}

EvtScript N(EVS_UpdateSliding) = {
    EVT_SET(LVar0, EVT_PTR(N(SlideData)))
    EVT_CALL(N(SetPlayerSliding))
    EVT_RETURN
    EVT_END
};

EvtScript N(EVS_UseSlide) = {
    EVT_CALL(DisablePlayerInput, TRUE)
    EVT_WAIT(10)
    EVT_THREAD
        EVT_CALL(PlaySoundAtCollider, COLLIDER_st1, SOUND_20A2, 0)
        EVT_CALL(MakeLerp, 0, -80, 10, EASING_LINEAR)
        EVT_LOOP(0)
            EVT_CALL(UpdateLerp)
            EVT_CALL(RotateModel, MODEL_se1, LVar0, 0, -1, 0)
            EVT_WAIT(1)
            EVT_IF_EQ(LVar1, 0)
                EVT_BREAK_LOOP
            EVT_END_IF
        EVT_END_LOOP
    EVT_END_THREAD
    EVT_WAIT(15)
    EVT_CALL(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_BITS, COLLIDER_st1, COLLIDER_FLAGS_UPPER_MASK)
    EVT_CALL(SetPlayerSpeed, EVT_FLOAT(3.0))
    EVT_CALL(PlayerMoveTo, -1460, -60, 0)
    EVT_CALL(DisablePlayerInput, FALSE)
    EVT_WAIT(100)
    EVT_THREAD
        EVT_CALL(PlaySoundAtCollider, COLLIDER_st1, SOUND_20A2, 0)
        EVT_CALL(MakeLerp, -80, 0, 30, EASING_LINEAR)
        EVT_LOOP(0)
            EVT_CALL(UpdateLerp)
            EVT_CALL(RotateModel, MODEL_se1, LVar0, 0, -1, 0)
            EVT_WAIT(1)
            EVT_IF_EQ(LVar1, 0)
                EVT_BREAK_LOOP
            EVT_END_IF
        EVT_END_LOOP
    EVT_END_THREAD
    EVT_CALL(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_CLEAR_BITS, COLLIDER_st1, COLLIDER_FLAGS_UPPER_MASK)
    EVT_RETURN
    EVT_END
};

EvtScript N(EVS_BindSlideTriggers) = {
    EVT_BIND_TRIGGER(EVT_PTR(N(EVS_UseSlide)), TRIGGER_WALL_PRESS_A, COLLIDER_st1, 1, 0)
    EVT_BIND_TRIGGER(EVT_PTR(N(EVS_UpdateSliding)), TRIGGER_FLOOR_TOUCH, COLLIDER_suberi0, 1, 0)
    EVT_CALL(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_SURFACE, COLLIDER_suberi0, SURFACE_TYPE_SLIDE)
    EVT_RETURN
    EVT_END
};
