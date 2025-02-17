#include "kmr_02.h"

EvtScript N(EVS_OpenDoor_ToadHouse) = {
    EVT_CALL(RotateModel, MODEL_o275, LVar0, 0, 1, 0)
    EVT_RETURN
    EVT_END
};

EvtScript N(EVS_MoveWalls_ToadHouse) = {
    EVT_SET(LVar1, LVar0)
    EVT_ADD(LVar1, LVar0)
    EVT_CALL(RotateModel, MODEL_k_k_1, LVar1, 0, 1, 0)
    EVT_CALL(RotateModel, MODEL_k_k_2, LVar1, 0, 1, 0)
    EVT_CALL(RotateModel, MODEL_k_k_3, LVar1, 0, 1, 0)
    EVT_CALL(RotateModel, MODEL_o272, LVar1, 0, 1, 0)
    EVT_RETURN
    EVT_END
};

EvtScript N(EVS_ToggleVis_ToadHouse) = {
    EVT_SWITCH(LVar0)
        EVT_CASE_EQ(0)
            EVT_CALL(SetGroupEnabled, MODEL_kino_in, 1)
            EVT_CALL(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_CLEAR_BITS, COLLIDER_o767, COLLIDER_FLAGS_UPPER_MASK)
        EVT_CASE_EQ(1)
        EVT_CASE_EQ(2)
            EVT_THREAD
                EVT_WAIT(5)
            EVT_END_THREAD
            EVT_CALL(GetPlayerPos, LVar0, LVar1, LVar2)
            EVT_CALL(UseSettingsFrom, CAM_DEFAULT, LVar0, LVar1, LVar2)
            EVT_CALL(SetPanTarget, CAM_DEFAULT, LVar0, LVar1, LVar2)
            EVT_CALL(PanToTarget, CAM_DEFAULT, 0, 0)
        EVT_CASE_EQ(3)
            EVT_CALL(SetGroupEnabled, MODEL_kino_in, 0)
            EVT_CALL(EnableModel, MODEL_o422, TRUE)
            EVT_CALL(EnableModel, MODEL_o424, TRUE)
    EVT_END_SWITCH
    EVT_RETURN
    EVT_END
};

EvtScript N(EVS_SetWallsDown_ToadHouse) = {
    EVT_CALL(SetGroupEnabled, MODEL_kino_in, 1)
    EVT_CALL(RotateModel, MODEL_k_k_1, 180, 0, 1, 0)
    EVT_CALL(RotateModel, MODEL_k_k_2, 180, 0, 1, 0)
    EVT_CALL(RotateModel, MODEL_k_k_3, 180, 0, 1, 0)
    EVT_CALL(RotateModel, MODEL_o272, 180, 0, 1, 0)
    EVT_CALL(EnableModel, MODEL_o561, FALSE)
    EVT_CALL(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_BITS, COLLIDER_o767, COLLIDER_FLAGS_UPPER_MASK)
    EVT_RETURN
    EVT_END
};

EvtScript N(EVS_ToadSignSwinging) = {
    EVT_LABEL(9)
        EVT_CALL(MakeLerp, 10, -10, 30, EASING_COS_IN_OUT)
        EVT_LABEL(10)
            EVT_CALL(UpdateLerp)
            EVT_CALL(RotateModel, MODEL_kanban, LVar0, EVT_FLOAT(35.498), 0, EVT_FLOAT(-9.511))
            EVT_WAIT(1)
            EVT_IF_EQ(LVar1, 1)
                EVT_GOTO(10)
            EVT_END_IF
        EVT_CALL(MakeLerp, -10, 10, 30, EASING_COS_IN_OUT)
        EVT_LABEL(11)
            EVT_CALL(UpdateLerp)
            EVT_CALL(RotateModel, MODEL_kanban, LVar0, EVT_FLOAT(35.498), 0, EVT_FLOAT(-9.511))
            EVT_WAIT(1)
            EVT_IF_EQ(LVar1, 1)
                EVT_GOTO(11)
            EVT_END_IF
        EVT_GOTO(9)
    EVT_RETURN
    EVT_END
};

s32 N(InsideNPCs_ToadHouse)[] = {
    NPC_Toad,
    -1
};

EvtScript N(EVS_SetupToadHouse) = {
    EVT_CALL(RotateModel, MODEL_o320, 180, 0, 1, 0)
    EVT_CALL(GetEntryID, LVar0)
    EVT_IF_NE(LVar0, kmr_02_ENTRY_5)
        EVT_CALL(SetGroupEnabled, MODEL_kino_in, 0)
    EVT_END_IF
    // toad house
    EVT_CALL(MakeDoorAdvanced,
        VIS_GROUP_PAIR(VIS_GROUP_0, VIS_GROUP_0),
        EVT_PTR(N(EVS_OpenDoor_ToadHouse)),
        EVT_PTR(N(EVS_MoveWalls_ToadHouse)),
        NULL,
        EVT_PTR(N(EVS_ToggleVis_ToadHouse)),
        COLLIDER_deilit7,
        COLLIDER_deilit8,
        MODEL_kinopi,
        EVT_PTR(N(InsideNPCs_ToadHouse)))
    EVT_EXEC(N(EVS_ToadSignSwinging))
    EVT_RETURN
    EVT_END
};
