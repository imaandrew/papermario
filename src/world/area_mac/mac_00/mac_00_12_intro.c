#include "mac_00.h"

EvtScript N(EVS_PlayerExitPipe_Intro) = {
    EVT_CALL(DisablePlayerPhysics, TRUE)
    EVT_CALL(HidePlayerShadow, TRUE)
    EVT_CALL(SetPlayerPos, -100, -10, -370)
    EVT_CALL(InterpPlayerYaw, 135, 0)
    EVT_WAIT(2)
    EVT_CALL(PlaySoundAtPlayer, SOUND_ENTER_PIPE, 0)
    EVT_CALL(func_802D286C, 0x100)
    EVT_CALL(func_802D2520, ANIM_Mario_10002, 5, 2, 1, 1, 0)
    EVT_CALL(GetPlayerPos, LVar0, LVar1, LVar2)
    EVT_LOOP(40)
        EVT_ADD(LVar1, 1)
        EVT_CALL(SetPlayerPos, LVar0, LVar1, LVar2)
        EVT_WAIT(1)
    EVT_END_LOOP
    EVT_CALL(func_802D2520, ANIM_Mario_10002, 0, 0, 0, 0, 0)
    EVT_CALL(HidePlayerShadow, FALSE)
    EVT_CALL(DisablePlayerPhysics, FALSE)
    EVT_RETURN
    EVT_END
};

EvtScript N(EVS_LuigiExitPipe_Intro) = {
    EVT_CALL(EnableNpcShadow, NPC_Luigi_Intro, FALSE)
    EVT_CALL(SetNpcPos, NPC_Luigi_Intro, -100, -35, -370)
    EVT_CALL(SetNpcYaw, NPC_Luigi_Intro, 135)
    EVT_WAIT(2)
    EVT_CALL(PlaySoundAtNpc, NPC_Luigi_Intro, SOUND_ENTER_PIPE, 0)
    EVT_CALL(func_802CFE2C, 0, 0x100)
    EVT_CALL(func_802CFD30, 0, FOLD_TYPE_5, 2, 1, 1, 0)
    EVT_CALL(SetNpcPos, NPC_Luigi_Intro, -100, -10, -370)
    EVT_CALL(GetNpcPos, NPC_Luigi_Intro, LVar0, LVar1, LVar2)
    EVT_LOOP(45)
        EVT_ADD(LVar1, 1)
        EVT_CALL(SetNpcPos, NPC_Luigi_Intro, LVar0, LVar1, LVar2)
        EVT_WAIT(1)
    EVT_END_LOOP
    EVT_CALL(func_802CFD30, 0, FOLD_TYPE_NONE, 0, 0, 0, 0)
    EVT_CALL(SetNpcPos, NPC_Luigi_Intro, -100, 30, -370)
    EVT_WAIT(3)
    EVT_CALL(EnableNpcShadow, NPC_Luigi_Intro, TRUE)
    EVT_RETURN
    EVT_END
};

EvtScript N(EVS_Scene_Intro) = {
    EVT_CALL(DisablePlayerInput, TRUE)
    EVT_CALL(UseSettingsFrom, CAM_DEFAULT, -100, 30, -370)
    EVT_CALL(SetPanTarget, CAM_DEFAULT, -100, 30, -370)
    EVT_CALL(SetCamDistance, CAM_DEFAULT, EVT_FLOAT(300.0))
    EVT_CALL(SetCamSpeed, CAM_DEFAULT, EVT_FLOAT(90.0))
    EVT_CALL(PanToTarget, CAM_DEFAULT, 0, 1)
    EVT_THREAD
        EVT_EXEC_WAIT(N(EVS_PlayerExitPipe_Intro))
        EVT_WAIT(10)
        EVT_CALL(func_802D1270, -60, -320, EVT_FLOAT(4.0))
        EVT_WAIT(63)
        EVT_CALL(func_802D1270, 80, -60, EVT_FLOAT(4.0))
        EVT_CALL(func_802D1270, 180, 0, EVT_FLOAT(4.0))
        EVT_CALL(func_802D1270, 650, 0, EVT_FLOAT(4.0))
    EVT_END_THREAD
    EVT_THREAD
        EVT_WAIT(70)
        EVT_EXEC_WAIT(N(EVS_LuigiExitPipe_Intro))
        EVT_WAIT(10)
        EVT_CALL(SetNpcFlagBits, NPC_Luigi_Intro, NPC_FLAG_GRAVITY, TRUE)
        EVT_CALL(SetNpcAnimation, NPC_Luigi_Intro, ANIM_Luigi_Run)
        EVT_CALL(SetNpcSpeed, NPC_Luigi_Intro, EVT_FLOAT(4.0))
        EVT_CALL(NpcMoveTo, NPC_Luigi_Intro, 80, -60, 0)
        EVT_CALL(NpcMoveTo, NPC_Luigi_Intro, 180, 0, 0)
        EVT_CALL(NpcMoveTo, NPC_Luigi_Intro, 650, 0, 0)
    EVT_END_THREAD
    EVT_WAIT(70)
    EVT_CALL(SetPanTarget, CAM_DEFAULT, -60, 0, -320)
    EVT_CALL(SetCamDistance, CAM_DEFAULT, EVT_FLOAT(600.0))
    EVT_CALL(SetCamSpeed, CAM_DEFAULT, EVT_FLOAT(2.0))
    EVT_CALL(PanToTarget, CAM_DEFAULT, 0, 1)
    EVT_CALL(WaitForCam, CAM_DEFAULT, EVT_FLOAT(1.0))
    EVT_CALL(UseSettingsFrom, CAM_DEFAULT, 400, 0, 0)
    EVT_CALL(SetPanTarget, CAM_DEFAULT, 400, 0, 0)
    EVT_CALL(SetCamDistance, CAM_DEFAULT, EVT_FLOAT(450.0))
    EVT_CALL(SetCamSpeed, CAM_DEFAULT, EVT_FLOAT(0.5))
    EVT_CALL(PanToTarget, CAM_DEFAULT, 0, 1)
    EVT_CALL(WaitForCam, CAM_DEFAULT, EVT_FLOAT(1.0))
    EVT_CALL(GotoMap, EVT_PTR("mac_01"), mac_01_ENTRY_4)
    EVT_WAIT(100)
    EVT_CALL(DisablePlayerInput, FALSE)
    EVT_RETURN
    EVT_END
};
