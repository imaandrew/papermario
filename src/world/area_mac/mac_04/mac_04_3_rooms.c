#include "mac_04.h"

s32 set_background_color_blend(s32, s32, s32, s32);

API_CALLABLE(N(InitEntryFromToybox)) {
    func_8011B950(MODEL_heiho_house, -1, 1, 1);
    set_background_color_blend(0, 0, 0, 255);
    gCameras[CAM_DEFAULT].bgColor[0] = 0;
    gCameras[CAM_DEFAULT].bgColor[1] = 0;
    gCameras[CAM_DEFAULT].bgColor[2] = 0;
    return ApiStatus_DONE2;
}

EvtScript N(EVS_SetDoorRot_Shop) = {
    EVT_CALL(RotateModel, MODEL_msdoor, LVar0, 0, -1, 0)
    EVT_RETURN
    EVT_END
};

EvtScript N(EVS_MoveWalls_Shop) = {
    EVT_SET(LVar1, LVar0)
    EVT_CALL(RotateModel, MODEL_my1, LVar1, -1, 0, 0)
    EVT_CALL(RotateModel, MODEL_my2, LVar1, -1, 0, 0)
    EVT_CALL(RotateModel, MODEL_my3, LVar1, -1, 0, 0)
    EVT_CALL(RotateModel, MODEL_my4, LVar1, -1, 0, 0)
    EVT_CALL(RotateModel, MODEL_my5, LVar1, -1, 0, 0)
    EVT_CALL(RotateModel, MODEL_mk1, LVar1, 1, 0, 0)
    EVT_CALL(RotateModel, MODEL_mk2, LVar1, 1, 0, 0)
    EVT_CALL(RotateModel, MODEL_mk3, LVar1, 1, 0, 0)
    EVT_RETURN
    EVT_END
};

EvtScript N(EVS_ToggleVis_Shop) = {
    EVT_SWITCH(LVar0)
        EVT_CASE_EQ(0)
            EVT_CALL(EnableGroup, MODEL_mise_in, TRUE)
            EVT_EXEC(N(EVS_80248B08))
        EVT_CASE_EQ(3)
            EVT_CALL(EnableGroup, MODEL_mise_in, FALSE)
    EVT_END_SWITCH
    EVT_RETURN
    EVT_END
};

EvtScript N(EVS_SetDoorRot_NiceHouse) = {
    EVT_CALL(RotateModel, MODEL_rndoor, LVar0, 0, -1, 0)
    EVT_RETURN
    EVT_END
};

EvtScript N(EVS_MoveWalls_NiceHouse) = {
    EVT_SET(LVar1, LVar0)
    EVT_CALL(RotateModel, MODEL_rnk1, LVar1, 1, 0, 0)
    EVT_CALL(RotateModel, MODEL_rnk2, LVar1, 1, 0, 0)
    EVT_CALL(RotateModel, MODEL_rnk3, LVar1, 1, 0, 0)
    EVT_CALL(RotateModel, MODEL_rnk4, LVar1, 1, 0, 0)
    EVT_SET(LVar1, LVar0)
    EVT_CALL(RotateModel, MODEL_rnk5, LVar1, 0, 1, 0)
    EVT_CALL(RotateModel, MODEL_rnk6, LVar1, 0, 1, 0)
    EVT_RETURN
    EVT_END
};

EvtScript N(EVS_DropDoor_NiceHouse) = {
    EVT_CALL(RotateModel, MODEL_rndoor, LVar0, 1, 0, 0)
    EVT_RETURN
    EVT_END
};

EvtScript N(EVS_ToggleVis_NiceHouse) = {
    EVT_SWITCH(LVar0)
        EVT_CASE_EQ(0)
            EVT_CALL(EnableGroup, MODEL_rin_in, TRUE)
        EVT_CASE_EQ(3)
            EVT_CALL(EnableGroup, MODEL_rin_in, FALSE)
    EVT_END_SWITCH
    EVT_RETURN
    EVT_END
};

EvtScript N(EVS_SetDoorRot_Storeroom) = {
    EVT_CALL(RotateModel, MODEL_skd, LVar0, 0, -1, 0)
    EVT_RETURN
    EVT_END
};

EvtScript N(EVS_MoveWalls_Storeroom) = {
    EVT_SET(LVar1, LVar0)
    EVT_MULF(LVar1, EVT_FLOAT(2.78125))
    EVT_CALL(TranslateModel, MODEL_skk1, 0, 0, LVar1)
    EVT_CALL(TranslateModel, MODEL_skk2, 0, 0, LVar1)
    EVT_CALL(TranslateModel, MODEL_skk3, 0, 0, LVar1)
    EVT_CALL(TranslateModel, MODEL_skk4, 0, 0, LVar1)
    EVT_CALL(TranslateModel, MODEL_skk5, 0, 0, LVar1)
    EVT_CALL(TranslateModel, MODEL_skk6, 0, 0, LVar1)
    EVT_CALL(TranslateModel, MODEL_skk7, 0, 0, LVar1)
    EVT_RETURN
    EVT_END
};

EvtScript N(EVS_DropDoor_Storeroom) = {
    EVT_CALL(RotateModel, MODEL_skd, LVar0, 0, 0, -1)
    EVT_RETURN
    EVT_END
};

EvtScript N(EVS_ToggleVis_Storeroom) = {
    EVT_SWITCH(LVar0)
        EVT_CASE_EQ(0)
    EVT_END_SWITCH
    EVT_RETURN
    EVT_END
};

EvtScript N(EVS_SetDoorRot_Warehouse) = {
    EVT_CALL(RotateModel, MODEL_hh_door, LVar0, 0, -1, 0)
    EVT_RETURN
    EVT_END
};

EvtScript N(EVS_MoveWalls_Warehouse) = {
    EVT_SET(LVar1, LVar0)
    EVT_CALL(RotateModel, MODEL_hk1, LVar1, 0, 0, -1)
    EVT_CALL(RotateModel, MODEL_hk2, LVar1, 0, 0, -1)
    EVT_CALL(RotateModel, MODEL_hk3, LVar1, 0, 0, -1)
    EVT_RETURN
    EVT_END
};

EvtScript N(EVS_ToggleVis_Warehouse) = {
    EVT_SWITCH(LVar0)
        EVT_CASE_EQ(0)
            EVT_CALL(EnableGroup, MODEL_heiho_in, TRUE)
            EVT_SET(MF_MusicMixTrigger, TRUE)
        EVT_CASE_EQ(1)
            EVT_EXEC(N(D_80248798_84B368))
        EVT_CASE_EQ(3)
            EVT_CALL(EnableGroup, MODEL_heiho_in, FALSE)
            EVT_CALL(EnableGroup, MODEL_hi_soto, TRUE)
            EVT_SET(MF_MusicMixTrigger, FALSE)
    EVT_END_SWITCH
    EVT_RETURN
    EVT_END
};

EvtScript N(EVS_SetDoorRot_HiddenRoom) = {
    EVT_CALL(RotateModel, MODEL_hkai1, LVar0, 0, -1, 0)
    EVT_CALL(RotateModel, MODEL_hkai2, LVar0, 0, -1, 0)
    EVT_RETURN
    EVT_END
};

EvtScript N(EVS_MoveWalls_HiddenRoom) = {
    EVT_SET(LVar1, LVar0)
    EVT_CALL(RotateModel, MODEL_hk4, LVar1, 0, 0, -1)
    EVT_CALL(RotateModel, MODEL_hk5, LVar1, 0, 0, -1)
    EVT_CALL(RotateModel, MODEL_hk6, LVar1, 0, 0, -1)
    EVT_RETURN
    EVT_END
};

EvtScript N(EVS_ToggleVis_HiddenRoom) = {
    EVT_RETURN
    EVT_END
};

s32 N(InsideNPCs_Shop)[] = {
    NPC_HarryT,
    NPC_ShyGuy_02,
    -1
};

s32 N(InsideNPCs_NiceHouse)[] = {
    NPC_NewResident1,
    NPC_NewResident2,
    -1
};

s32 N(InsideNPCs_Warehouse)[] = {
    NPC_ShyGuy_01,
    -1
};

EvtScript N(EVS_MakeHiddenRoom) = {
    EVT_CALL(MakeDoorAdvanced,
        VIS_GROUP_PAIR(VIS_GROUP_0, VIS_GROUP_2),
        EVT_PTR(N(EVS_SetDoorRot_HiddenRoom)),
        EVT_PTR(N(EVS_MoveWalls_HiddenRoom)),
        NULL,
        EVT_PTR(N(EVS_ToggleVis_HiddenRoom)),
        COLLIDER_deilit_hk,
        COLLIDER_deilit_hku,
        MODEL_o13,
        NULL)
    EVT_RETURN
    EVT_END
};

EvtScript N(EVS_MakeStoreroom) = {
    EVT_CALL(MakeDoorAdvanced,
        VIS_GROUP_PAIR(VIS_GROUP_2, VIS_GROUP_2),
        EVT_PTR(N(EVS_SetDoorRot_Storeroom)),
        EVT_PTR(N(EVS_MoveWalls_Storeroom)),
        EVT_PTR(N(EVS_DropDoor_Storeroom)),
        EVT_PTR(N(EVS_ToggleVis_Storeroom)),
        COLLIDER_deilit_sku,
        COLLIDER_deilit_sk,
        MODEL_o13,
        NULL)
    EVT_RETURN
    EVT_END
};

EvtScript N(EVS_SetupRooms) = {
    // harry's shop on the right
    EVT_CALL(MakeDoorAdvanced,
        VIS_GROUP_PAIR(VIS_GROUP_1, VIS_GROUP_2),
        EVT_PTR(N(EVS_SetDoorRot_Shop)),
        EVT_PTR(N(EVS_MoveWalls_Shop)),
        NULL,
        EVT_PTR(N(EVS_ToggleVis_Shop)),
        COLLIDER_deilit_m,
        COLLIDER_deilit_mu,
        MODEL_mise,
        EVT_PTR(N(InsideNPCs_Shop)))
    // nice house in the middle
    EVT_CALL(MakeDoorAdvanced,
        VIS_GROUP_PAIR(VIS_GROUP_0, VIS_GROUP_2),
        EVT_PTR(N(EVS_SetDoorRot_NiceHouse)),
        EVT_PTR(N(EVS_MoveWalls_NiceHouse)),
        EVT_PTR(N(EVS_DropDoor_NiceHouse)),
        EVT_PTR(N(EVS_ToggleVis_NiceHouse)),
        COLLIDER_deilit_r,
        COLLIDER_deilit_ru,
        MODEL_rinjin,
        EVT_PTR(N(InsideNPCs_NiceHouse)))
    // warehouse on the left
    EVT_CALL(MakeDoorAdvanced,
        VIS_GROUP_PAIR(VIS_GROUP_0, VIS_GROUP_2),
        EVT_PTR(N(EVS_SetDoorRot_Warehouse)),
        EVT_PTR(N(EVS_MoveWalls_Warehouse)),
        NULL,
        EVT_PTR(N(EVS_ToggleVis_Warehouse)),
        COLLIDER_deilit_h,
        COLLIDER_deilit_hu,
        MODEL_heiho_house,
        EVT_PTR(N(InsideNPCs_Warehouse)))
    EVT_IF_GE(GB_StoryProgress, STORY_CH4_RETURNED_STOREROOM_KEY)
        EVT_EXEC_WAIT(N(EVS_MakeStoreroom))
    EVT_END_IF
    EVT_IF_GE(GB_StoryProgress, STORY_CH4_FOUND_HIDDEN_DOOR)
        EVT_EXEC_WAIT(N(EVS_MakeHiddenRoom))
    EVT_END_IF
    EVT_CALL(GetEntryID, LVar0)
    EVT_SWITCH(LVar0)
        EVT_CASE_RANGE(mac_04_ENTRY_2, mac_04_ENTRY_3)
            EVT_CALL(SetGroupEnabled, MODEL_heiho_in, 1)
            EVT_CALL(N(InitEntryFromToybox))
            EVT_SET(LVar0, 90)
            EVT_CALL(RotateModel, MODEL_hk1, LVar0, 0, 0, -1)
            EVT_CALL(RotateModel, MODEL_hk2, LVar0, 0, 0, -1)
            EVT_CALL(RotateModel, MODEL_hk3, LVar0, 0, 0, -1)
            EVT_CALL(RotateModel, MODEL_hk4, LVar0, 0, 0, -1)
            EVT_CALL(RotateModel, MODEL_hk5, LVar0, 0, 0, -1)
            EVT_CALL(RotateModel, MODEL_hk6, LVar0, 0, 0, -1)
        EVT_CASE_DEFAULT
            EVT_SET(LVar0, 3)
            EVT_EXEC(N(EVS_ToggleVis_Shop))
            EVT_EXEC(N(EVS_ToggleVis_NiceHouse))
    EVT_END_SWITCH
    EVT_RETURN
    EVT_END
};
