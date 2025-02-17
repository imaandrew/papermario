#include "kmr_20.h"

API_CALLABLE(N(SetAmbienceVolumeHalf_Rooms)){
    au_ambience_set_volume(0, 1000, 63);
    return ApiStatus_DONE2;
}

API_CALLABLE(N(SetAmbienceVolumeFull_Rooms)){
    au_ambience_set_volume(0, 1000, 127);
    return ApiStatus_DONE2;
}

EvtScript N(EVS_SetDoorRot_House) = {
    EVT_CALL(RotateGroup, MODEL_g14, LVar0, 0, 1, 0)
    EVT_RETURN
    EVT_END
};

EvtScript N(EVS_MoveWalls_House) = {
    EVT_CALL(RotateGroup, MODEL_g60, LVar0, 1, 0, 0)
    EVT_CALL(RotateGroup, MODEL_g34, LVar0, -1, 0, 0)
    EVT_SWITCH(LVar0)
        EVT_CASE_EQ(90)
            EVT_SET(MF_Unk_0C, TRUE)
            EVT_CALL(SetNpcFlagBits, NPC_Luigi_0, NPC_FLAG_2, FALSE)
            EVT_CALL(EnableGroup, MODEL_g60, FALSE)
            EVT_CALL(EnableGroup, MODEL_g34, FALSE)
        EVT_CASE_EQ(0)
            EVT_IF_EQ(MF_Unk_0C, TRUE)
                EVT_CALL(EnableGroup, MODEL_g72, TRUE)
                EVT_SET(MF_Unk_0C, FALSE)
                EVT_CALL(SetNpcFlagBits, NPC_Luigi_0, NPC_FLAG_2, TRUE)
            EVT_END_IF
        EVT_CASE_DEFAULT
            EVT_CALL(EnableGroup, MODEL_g60, TRUE)
            EVT_CALL(EnableGroup, MODEL_g34, TRUE)
    EVT_END_SWITCH
    EVT_RETURN
    EVT_END
};

EvtScript N(EVS_ToggleVis_House) = {
    EVT_SWITCH(LVar0)
        EVT_CASE_EQ(0)
            EVT_CALL(N(SetAmbienceVolumeHalf_Rooms))
            EVT_CALL(EnableGroup, MODEL_g20, TRUE)
            EVT_CALL(EnableGroup, MODEL_g21, TRUE)
            EVT_CALL(EnableGroup, MODEL_g49, TRUE)
            EVT_CALL(EnableModel, MODEL_g56, TRUE)
        EVT_CASE_EQ(1)
        EVT_CASE_EQ(2)
        EVT_CASE_EQ(3)
            EVT_CALL(N(SetAmbienceVolumeFull_Rooms))
            EVT_CALL(EnableGroup, MODEL_g20, FALSE)
            EVT_CALL(EnableGroup, MODEL_g21, FALSE)
            EVT_CALL(EnableGroup, MODEL_g49, FALSE)
            EVT_CALL(EnableModel, MODEL_g56, FALSE)
            EVT_CALL(EnableGroup, MODEL_g72, FALSE)
    EVT_END_SWITCH
    EVT_RETURN
    EVT_END
};

s32 N(InteriorNPCs_House)[] = {
    NPC_Luigi_0,
    -1
};

EvtScript N(EVS_SetupRooms) = {
    EVT_CALL(MakeDoorAdvanced,
        VIS_GROUP_PAIR(VIS_GROUP_0, VIS_GROUP_0),
        EVT_PTR(N(EVS_SetDoorRot_House)),
        EVT_PTR(N(EVS_MoveWalls_House)),
        NULL,
        EVT_PTR(N(EVS_ToggleVis_House)),
        COLLIDER_o246,
        COLLIDER_o245,
        MODEL_g62,
        EVT_PTR(N(InteriorNPCs_House)))
    EVT_CALL(GetEntryID, LVar0)
    EVT_SWITCH(LVar0)
        EVT_CASE_OR_EQ(kmr_20_ENTRY_2)
        EVT_CASE_OR_EQ(kmr_20_ENTRY_3)
            EVT_CALL(EnableGroup, MODEL_g20, TRUE)
            EVT_CALL(EnableGroup, MODEL_g21, TRUE)
            EVT_CALL(EnableGroup, MODEL_g49, TRUE)
            EVT_CALL(EnableModel, MODEL_g56, TRUE)
            EVT_CALL(EnableGroup, MODEL_g72, FALSE)
            EVT_CALL(N(func_80241C9C_8EDABC))
            EVT_CALL(RotateGroup, MODEL_g60, 90, 1, 0, 0)
            EVT_CALL(RotateGroup, MODEL_g34, 90, -1, 0, 0)
            EVT_CALL(EnableGroup, MODEL_g60, FALSE)
            EVT_CALL(EnableGroup, MODEL_g34, FALSE)
            EVT_CALL(N(SetAmbienceVolumeHalf_Rooms))
        EVT_END_CASE_GROUP
        EVT_CASE_DEFAULT
            EVT_SET(LVar0, 3)
            EVT_EXEC(N(EVS_ToggleVis_House))
    EVT_END_SWITCH
    EVT_RETURN
    EVT_END
};
