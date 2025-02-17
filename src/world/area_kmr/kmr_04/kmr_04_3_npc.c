#include "kmr_04.h"
#include "effects.h"

NpcSettings N(NpcSettings_JrTroopa) = {
    .height = 32,
    .radius = 24,
    .level = 99,
};

EvtScript N(EVS_NpcAuxAI_Goompa) = {
    EVT_CALL(SetNpcFlagBits, NPC_SELF, NPC_FLAG_GRAVITY, FALSE)
    EVT_CALL(SetNpcFlagBits, NPC_SELF, NPC_FLAG_ENABLE_HIT_SCRIPT | NPC_FLAG_40, TRUE)
    EVT_CALL(SetNpcPos, NPC_SELF, 0, -1000, 0)
    EVT_CALL(EnableNpcShadow, NPC_SELF, FALSE)
    EVT_RETURN
    EVT_END
};

EvtScript N(EVS_NpcAux_Goompa) = {
    EVT_RETURN
    EVT_END
};

#include "world/common/todo/CheckPartnerFlags1000.inc.c"

API_CALLABLE(N(GetPlayerHP)) {
    script->varTable[0] = get_player_data()->curHP;

    return ApiStatus_DONE2;
}

EvtScript N(EVS_NpcAI_Goompa) = {
    EVT_LABEL(1)
    EVT_SWITCH(GB_StoryProgress)
        EVT_CASE_EQ(STORY_CH0_GOOMPA_JOINED_PARTY)
            EVT_LOOP(0)
                EVT_CALL(GetPlayerPos, LVar0, LVar1, LVar2)
                EVT_WAIT(1)
                EVT_IF_LE(LVar0, 370)
                    EVT_BREAK_LOOP
                EVT_END_IF
            EVT_END_LOOP
            EVT_CALL(DisablePlayerInput, TRUE)
            EVT_CALL(func_802CF56C, 0)
            EVT_CALL(GetPlayerPos, LVar0, LVar1, LVar2)
            EVT_ADD(LVar0, 30)
            EVT_CALL(SetNpcSpeed, NPC_PARTNER, EVT_FLOAT(2.0))
            EVT_CALL(NpcMoveTo, LVar0, LVar1, LVar2, 0)
            EVT_WAIT(5)
            EVT_CALL(DisablePartnerAI, 0)
            EVT_CALL(SpeakToPlayer, NPC_PARTNER, ANIM_Goompa_Talk, ANIM_Goompa_Idle, 0, MSG_CH0_00A9)
            EVT_CALL(SetNpcAnimation, NPC_PARTNER, ANIM_Goompa_Idle)
            EVT_CALL(EnablePartnerAI)
            EVT_WAIT(10)
            EVT_CALL(DisablePlayerInput, FALSE)
            EVT_SET(GB_StoryProgress, STORY_CH0_LOOKING_FOR_HAMMER)
        EVT_CASE_EQ(STORY_CH0_FOUND_HAMMER)
            EVT_IF_EQ(AB_KMR_0, 0)
                EVT_LABEL(10)
                EVT_WAIT(1)
                EVT_CALL(GetPlayerPos, LVar0, LVar1, LVar2)
                EVT_IF_LT(LVar0, 360)
                    EVT_GOTO(10)
                EVT_END_IF
                EVT_IF_GT(LVar0, 400)
                    EVT_GOTO(10)
                EVT_END_IF
                EVT_IF_LT(LVar2, -36)
                    EVT_GOTO(10)
                EVT_END_IF
                EVT_IF_GT(LVar2, 85)
                    EVT_GOTO(10)
                EVT_END_IF
                EVT_CALL(DisablePlayerInput, TRUE)
                EVT_CALL(N(CheckPartnerFlags1000))
                EVT_CALL(DisablePartnerAI, 0)
                EVT_CALL(SetNpcFlagBits, NPC_PARTNER, NPC_FLAG_40, TRUE)
                EVT_CALL(SetNpcAnimation, NPC_PARTNER, ANIM_Goompa_Walk)
                EVT_CALL(SetNpcSpeed, NPC_PARTNER, EVT_FLOAT(3.0))
                EVT_CALL(NpcMoveTo, NPC_PARTNER, 420, 6, 0)
                EVT_THREAD
                    EVT_WAIT(3)
                    EVT_CALL(PlayerFaceNpc, NPC_PARTNER, 3)
                EVT_END_THREAD
                EVT_CALL(SpeakToPlayer, NPC_PARTNER, ANIM_Goompa_Talk, ANIM_Goompa_Idle, 0, MSG_CH0_00AC)
                EVT_CALL(SetNpcAnimation, NPC_PARTNER, ANIM_Goompa_Idle)
                EVT_WAIT(10)
                EVT_THREAD
                    EVT_CALL(SetPlayerSpeed, EVT_FLOAT(3.0))
                    EVT_CALL(PlayerMoveTo, 395, 0, 0)
                    EVT_CALL(InterpPlayerYaw, 90, 0)
                EVT_END_THREAD
                EVT_CALL(SetNpcFlagBits, NPC_PARTNER, NPC_FLAG_ENABLE_HIT_SCRIPT, TRUE)
                EVT_CALL(SetNpcSpeed, NPC_PARTNER, EVT_FLOAT(6.0))
                EVT_CALL(SetNpcAnimation, NPC_PARTNER, ANIM_Goompa_Run)
                EVT_CALL(NpcMoveTo, NPC_PARTNER, 582, 6, 0)
                EVT_CALL(SetNpcAnimation, NPC_PARTNER, ANIM_Goompa_Idle)
                EVT_CALL(SetNpcFlagBits, NPC_PARTNER, NPC_FLAG_ENABLE_HIT_SCRIPT, FALSE)
                EVT_CALL(PlaySoundAtNpc, NPC_PARTNER, SOUND_61, 0)
                EVT_CALL(SpeakToPlayer, NPC_PARTNER, ANIM_Goompa_Talk, ANIM_Goompa_Idle, 0, MSG_CH0_00AD)
                EVT_WAIT(10)
                EVT_THREAD
                    EVT_SET(LVar0, 0)
                    EVT_CALL(func_802CDE68, -4, 10)
                    EVT_LOOP(60)
                        EVT_ADD(LVar0, 53)
                        EVT_CALL(SetNpcRotation, NPC_PARTNER, 0, 0, LVar0)
                        EVT_CALL(PlayerFaceNpc, NPC_PARTNER, FALSE)
                        EVT_WAIT(1)
                    EVT_END_LOOP
                    EVT_CALL(func_802CDE68, -4, 0)
                    EVT_CALL(SetNpcRotation, NPC_PARTNER, 0, 0, 0)
                EVT_END_THREAD
                EVT_THREAD
                    EVT_CALL(ShakeCam, CAM_DEFAULT, 0, 15, EVT_FLOAT(1.0))
                EVT_END_THREAD
                EVT_PLAY_EFFECT(EFFECT_DAMAGE_STARS, 1, 495, 15, 9, 460, 15, 9, 6)
                EVT_CALL(SetNpcAnimation, NPC_PARTNER, ANIM_Goompa_Injured)
                EVT_CALL(NpcMoveTo, NPC_PARTNER, 250, 6, 60)
                EVT_CALL(SetNpcAnimation, NPC_PARTNER, ANIM_Goompa_Injured)
                EVT_CALL(SetNpcRotation, NPC_PARTNER, 0, 0, 0)
                EVT_THREAD
                    EVT_LOOP(20)
                        EVT_CALL(SetNpcPos, NPC_PARTNER, 250, 0, 6)
                        EVT_WAIT(3)
                        EVT_CALL(SetNpcPos, NPC_PARTNER, 250, 0, 0)
                        EVT_WAIT(3)
                    EVT_END_LOOP
                EVT_END_THREAD
                EVT_SET(AB_KMR_0, 1)
            EVT_END_IF
    EVT_END_SWITCH
    EVT_WAIT(1)
    EVT_GOTO(1)
    EVT_RETURN
    EVT_END
};

EvtScript N(EVS_NpcInteract_Goompa) = {
    EVT_RETURN
    EVT_END
};

EvtScript N(EVS_NpcDefeat_Goompa) = {
    EVT_RETURN
    EVT_END
};

EvtScript N(EVS_NpcIdle_JrTroopa) = {
    EVT_CALL(func_800445D4, LVar0)
    EVT_SWITCH(LVar0)
        EVT_CASE_EQ(100)
            EVT_LABEL(0)
            EVT_SWITCH(AB_KMR_0)
                EVT_CASE_EQ(1)
                    EVT_EXEC(N(EVS_SetJrTroopaMusic))
                    EVT_THREAD
                        EVT_WAIT(20)
                        EVT_CALL(GetPlayerPos, LVar0, LVar1, LVar2)
                        EVT_CALL(UseSettingsFrom, CAM_DEFAULT, LVar0, LVar1, LVar2)
                        EVT_CALL(SetPanTarget, CAM_DEFAULT, 430, LVar1, LVar2)
                        EVT_CALL(SetCamDistance, CAM_DEFAULT, EVT_FLOAT(275.0))
                        EVT_CALL(SetCamPitch, CAM_DEFAULT, EVT_FLOAT(17.5), EVT_FLOAT(-7.5))
                        EVT_CALL(SetCamSpeed, CAM_DEFAULT, EVT_FLOAT(2.0))
                        EVT_CALL(PanToTarget, CAM_DEFAULT, 0, 1)
                        EVT_CALL(WaitForCam, CAM_DEFAULT, EVT_FLOAT(1.0))
                    EVT_END_THREAD
                    EVT_CALL(SetNpcPos, NPC_JrTroopa, 630, 0, 0)
                    EVT_CALL(EnableNpcShadow, NPC_SELF, TRUE)
                    EVT_WAIT(1)
                    EVT_CALL(PlayerFaceNpc, NPC_JrTroopa, 3)
                    EVT_CALL(SetNpcSpeed, NPC_JrTroopa, EVT_FLOAT(3.0))
                    EVT_CALL(SetNpcAnimation, NPC_JrTroopa, ANIM_JrTroopa_Run)
                    EVT_CALL(NpcMoveTo, NPC_JrTroopa, 465, 0, 0)
                    EVT_CALL(SetNpcAnimation, NPC_JrTroopa, ANIM_JrTroopa_PointIdle)
                    EVT_CALL(PlayerFaceNpc, NPC_JrTroopa, 3)
                    EVT_CALL(SpeakToPlayer, NPC_JrTroopa, ANIM_JrTroopa_PointTalk, ANIM_JrTroopa_PointIdle, 0, MSG_CH0_00AE)
                    EVT_WAIT(10)
                    EVT_THREAD
                        EVT_CALL(GetPlayerPos, LVar0, LVar1, LVar2)
                        EVT_CALL(UseSettingsFrom, CAM_DEFAULT, LVar0, LVar1, LVar2)
                        EVT_CALL(SetPanTarget, CAM_DEFAULT, 430, LVar1, LVar2)
                        EVT_CALL(SetCamSpeed, CAM_DEFAULT, EVT_FLOAT(4.0))
                        EVT_CALL(PanToTarget, CAM_DEFAULT, 0, 1)
                        EVT_CALL(WaitForCam, CAM_DEFAULT, EVT_FLOAT(1.0))
                        EVT_CALL(PanToTarget, CAM_DEFAULT, 0, 0)
                    EVT_END_THREAD
                    EVT_CALL(StartBossBattle, SONG_JR_TROOPA_BATTLE)
            EVT_END_SWITCH
            EVT_WAIT(1)
            EVT_GOTO(0)
        EVT_CASE_OR_EQ(101)
        EVT_CASE_OR_EQ(102)
        EVT_CASE_OR_EQ(3)
        EVT_CASE_OR_EQ(103)
        EVT_END_CASE_GROUP
    EVT_END_SWITCH
    EVT_RETURN
    EVT_END
};

EvtScript N(EVS_NpcDefeat_JrTroopa) = {
    EVT_CALL(GetBattleOutcome, LVar0)
    EVT_SWITCH(LVar0)
        EVT_CASE_EQ(OUTCOME_PLAYER_WON)
            EVT_CALL(GetPlayerPos, LVar0, LVar1, LVar2)
            EVT_CALL(UseSettingsFrom, CAM_DEFAULT, LVar0, LVar1, LVar2)
            EVT_CALL(SetPanTarget, CAM_DEFAULT, 400, LVar1, LVar2)
            EVT_CALL(SetCamDistance, CAM_DEFAULT, EVT_FLOAT(275.0))
            EVT_CALL(SetCamPitch, CAM_DEFAULT, EVT_FLOAT(15.0), EVT_FLOAT(-7.5))
            EVT_CALL(SetCamSpeed, CAM_DEFAULT, EVT_FLOAT(90.0))
            EVT_CALL(PanToTarget, CAM_DEFAULT, 0, 1)
            EVT_CALL(WaitForCam, CAM_DEFAULT, EVT_FLOAT(1.0))
            EVT_CALL(PlayerFaceNpc, NPC_SELF, FALSE)
            EVT_CALL(SetNpcAnimation, NPC_SELF, ANIM_JrTroopa_Hurt)
            EVT_CALL(SpeakToPlayer, NPC_SELF, ANIM_JrTroopa_Hurt, ANIM_JrTroopa_Hurt, 0, MSG_CH0_00B5)
            EVT_CALL(SetNpcSpeed, NPC_SELF, EVT_FLOAT(6.0))
            EVT_CALL(SetNpcAnimation, NPC_SELF, ANIM_JrTroopa_Run)
            EVT_CALL(NpcMoveTo, NPC_SELF, 564, 10, 0)
            EVT_CALL(SetNpcPos, NPC_SELF, NPC_DISPOSE_LOCATION)
            EVT_WAIT(60)
            EVT_CALL(SetNpcPos, NPC_SELF, 564, 0, 10)
            EVT_CALL(NpcMoveTo, NPC_SELF, 435, 10, 0)
            EVT_CALL(SpeakToPlayer, NPC_SELF, ANIM_JrTroopa_PointTalk, ANIM_JrTroopa_PointIdle, 0, MSG_CH0_00B6)
            EVT_CALL(NpcMoveTo, NPC_SELF, 564, 10, 0)
            EVT_CALL(SetNpcAnimation, NPC_SELF, ANIM_JrTroopa_Idle)
            EVT_CALL(SetNpcPos, NPC_SELF, NPC_DISPOSE_LOCATION)
            EVT_THREAD
                EVT_CALL(ResetCam, CAM_DEFAULT, 4)
            EVT_END_THREAD
            EVT_EXEC(N(EVS_SetNormalMusic))
            EVT_SET(AB_KMR_0, 0)
            EVT_SET(GB_StoryProgress, STORY_CH0_DEFEATED_JR_TROOPA)
            EVT_CALL(DisablePlayerInput, FALSE)
    EVT_END_SWITCH
    EVT_RETURN
    EVT_END
};

NpcSettings N(NpcSettings_Goompa) = {
    .defaultAnim = ANIM_Goompa_Idle,
    .height = 24,
    .radius = 24,
    .otherAI = &N(EVS_NpcAuxAI_Goompa),
    .onInteract = &N(EVS_NpcInteract_Goompa),
    .ai = &N(EVS_NpcAI_Goompa),
    .aux = &N(EVS_NpcAux_Goompa),
    .onDefeat = &N(EVS_NpcDefeat_Goompa),
    .flags = ENEMY_FLAGS_1 | ENEMY_FLAGS_4 | ENEMY_FLAGS_100,
};

EvtScript N(EVS_NpcInit_JrTroopa) = {
    EVT_CALL(SetNpcPos, NPC_SELF, 0, -1000, 0)
    EVT_CALL(EnableNpcShadow, NPC_SELF, FALSE)
    EVT_CALL(BindNpcIdle, NPC_SELF, EVT_PTR(N(EVS_NpcIdle_JrTroopa)))
    EVT_CALL(BindNpcDefeat, NPC_SELF, EVT_PTR(N(EVS_NpcDefeat_JrTroopa)))
    EVT_RETURN
    EVT_END
};

StaticNpc N(NpcData_JrTroopa) = {
    .id = NPC_JrTroopa,
    .settings = &N(NpcSettings_JrTroopa),
    .pos = { NPC_DISPOSE_LOCATION },
    .yaw = 0,
    .flags = ENEMY_FLAGS_100 | ENEMY_FLAGS_400 | ENEMY_FLAGS_800 | ENEMY_FLAGS_40000 | ENEMY_FLAGS_200000 | ENEMY_FLAGS_800000,
    .init = &N(EVS_NpcInit_JrTroopa),
    .drops = {
        .dropFlags = NPC_DROP_FLAGS_80,
        .heartDrops  = NO_DROPS,
        .flowerDrops = NO_DROPS,
    },
    .animations = {
        .idle   = ANIM_JrTroopa_Idle,
        .walk   = ANIM_JrTroopa_Walk,
        .run    = ANIM_JrTroopa_Walk,
        .chase  = ANIM_JrTroopa_Walk,
        .anim_4 = ANIM_JrTroopa_Idle,
        .anim_5 = ANIM_JrTroopa_Idle,
        .death  = ANIM_JrTroopa_Idle,
        .hit    = ANIM_JrTroopa_Idle,
        .anim_8 = ANIM_JrTroopa_Idle,
        .anim_9 = ANIM_JrTroopa_Idle,
        .anim_A = ANIM_JrTroopa_Idle,
        .anim_B = ANIM_JrTroopa_Idle,
        .anim_C = ANIM_JrTroopa_Idle,
        .anim_D = ANIM_JrTroopa_Idle,
        .anim_E = ANIM_JrTroopa_Idle,
        .anim_F = ANIM_JrTroopa_Idle,
    },
};

StaticNpc N(NpcData_GoombaFamily) = {
    .id = NPC_Goompa,
    .settings = &N(NpcSettings_Goompa),
    .pos = { -58.0f, 0.0f, 130.0f },
    .yaw = 0,
    .flags = ENEMY_FLAGS_100 | ENEMY_FLAGS_200000,
    .animations = {
    },
};

NpcGroupList N(DefaultNPCs) = {
    NPC_GROUP(N(NpcData_JrTroopa), BTL_KMR_PART_3_FORMATION_02),
    NPC_GROUP(N(NpcData_GoombaFamily)),
    {}
};
