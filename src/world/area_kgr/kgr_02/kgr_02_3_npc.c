#include "kgr_02.h"

ApiStatus N(AwaitPartnerWatt)(Evt* script, s32 isInitialCall) {
    if (gPartnerActionStatus.actingPartner == PARTNER_WATT) {
        return ApiStatus_DONE2;
    } else {
        return ApiStatus_BLOCK;
    }
}

ApiStatus N(AwaitPartnerNotWatt)(Evt* script, s32 isInitialCall) {
    if (gPartnerActionStatus.actingPartner != PARTNER_WATT) {
        return ApiStatus_DONE2;
    } else {
        return ApiStatus_BLOCK;
    }
}

s32 N(D_80240970_8AADC0) = 0;

EvtScript N(EVS_Dummy) = {
    EVT_WAIT(1)
    EVT_RETURN
    EVT_END
};

EvtScript N(EVS_Flotsam_Bobbing) = {
    EVT_LOOP(0)
        EVT_CALL(MakeLerp, 0, -10, 25, EASING_QUADRATIC_OUT)
        EVT_LOOP(0)
            EVT_CALL(UpdateLerp)
            EVT_CALL(TranslateModel, LVar2, 0, LVar0, 0)
            EVT_CALL(TranslateModel, LVar3, 0, LVar0, 0)
            EVT_CALL(TranslateModel, LVar4, 0, LVar0, 0)
            EVT_WAIT(1)
            EVT_IF_EQ(LVar1, 0)
                EVT_BREAK_LOOP
            EVT_END_IF
        EVT_END_LOOP
        EVT_CALL(MakeLerp, -10, 0, 30, EASING_QUADRATIC_OUT)
        EVT_LOOP(0)
            EVT_CALL(UpdateLerp)
            EVT_CALL(TranslateModel, LVar2, 0, LVar0, 0)
            EVT_CALL(TranslateModel, LVar3, 0, LVar0, 0)
            EVT_CALL(TranslateModel, LVar4, 0, LVar0, 0)
            EVT_WAIT(1)
            EVT_IF_EQ(LVar1, 0)
                EVT_BREAK_LOOP
            EVT_END_IF
        EVT_END_LOOP
    EVT_END_LOOP
    EVT_RETURN
    EVT_END
};

EvtScript N(EVS_SetupFlotsam) = {
    EVT_SET(LVar2, MODEL_hako1)
    EVT_SET(LVar3, MODEL_bin2)
    EVT_SET(LVar4, MODEL_hako4)
    EVT_EXEC_GET_TID(N(EVS_Flotsam_Bobbing), LVarA)
    EVT_WAIT(5)
    EVT_SET(LVar2, MODEL_bin1)
    EVT_SET(LVar3, MODEL_hako6)
    EVT_SET(LVar4, MODEL_hako5)
    EVT_EXEC_GET_TID(N(EVS_Flotsam_Bobbing), LVarB)
    EVT_WAIT(5)
    EVT_SET(LVar2, MODEL_hako2)
    EVT_SET(LVar3, MODEL_hako3)
    EVT_SET(LVar4, MODEL_bin4)
    EVT_EXEC_GET_TID(N(EVS_Flotsam_Bobbing), LVarC)
    EVT_WAIT(5)
    EVT_SET(LVar2, MODEL_fune_s)
    EVT_SET(LVar3, MODEL_fune_u)
    EVT_SET(LVar4, MODEL_bin3)
    EVT_EXEC_GET_TID(N(EVS_Flotsam_Bobbing), LVarD)
    EVT_CALL(SetNpcVar, NPC_Fuzzipede, 2, 0)
    EVT_LOOP(0)
        EVT_CALL(GetNpcVar, NPC_Fuzzipede, 2, LVar0)
        EVT_IF_EQ(LVar0, 1)
            EVT_BREAK_LOOP
        EVT_END_IF
        EVT_WAIT(1)
    EVT_END_LOOP
    EVT_KILL_THREAD(LVarA)
    EVT_KILL_THREAD(LVarB)
    EVT_KILL_THREAD(LVarC)
    EVT_KILL_THREAD(LVarD)
    EVT_RETURN
    EVT_END
};

EvtScript N(EVS_Fuzzipede_ReactToLight) = {
    EVT_SET(LVarA, 0)
    EVT_SET(LVarB, 0)
    EVT_CALL(WaitForPlayerInputEnabled)
    EVT_LOOP(0)
        EVT_IF_EQ(LVarA, 0)
            EVT_CALL(N(AwaitPartnerWatt))
            EVT_IF_EQ(LVarB, 0)
                EVT_CALL(DisablePlayerInput, TRUE)
                EVT_CALL(SetNpcJumpscale, NPC_SELF, EVT_FLOAT(1.0))
                EVT_CALL(GetPlayerPos, LVar0, LVar1, LVar2)
                EVT_IF_LT(LVar0, 0)
                    EVT_ADD(LVar0, 80)
                EVT_ELSE
                    EVT_ADD(LVar0, -80)
                EVT_END_IF
                EVT_CALL(NpcJump0, NPC_SELF, LVar0, 0, 0, 20)
                EVT_CALL(GetNpcPos, NPC_SELF, LVar0, LVar1, LVar2)
                EVT_CALL(NpcJump0, NPC_SELF, LVar0, LVar1, LVar2, 10)
                EVT_CALL(SpeakToPlayer, NPC_SELF, ANIM_Fuzzipede_Anim24, ANIM_Fuzzipede_Anim04, 0, MSG_MAC_Port_009B)
                EVT_CALL(SetSelfVar, 0, 1)
                EVT_SET(LVarB, 1)
                EVT_CALL(DisablePlayerInput, FALSE)
            EVT_END_IF
            EVT_CALL(SetSelfEnemyFlagBits, ENEMY_FLAGS_IGNORE_TOUCH | ENEMY_FLAGS_IGNORE_JUMP, 0)
            EVT_SET(LVarA, 1)
        EVT_ELSE
            EVT_CALL(N(AwaitPartnerNotWatt))
            EVT_CALL(SetSelfEnemyFlagBits, ENEMY_FLAGS_IGNORE_TOUCH | ENEMY_FLAGS_IGNORE_JUMP, 1)
            EVT_SET(LVarA, 0)
        EVT_END_IF
        EVT_WAIT(1)
    EVT_END_LOOP
    EVT_RETURN
    EVT_END
};

EvtScript N(EVS_Fuzzipede_JumpAround) = {
    EVT_LOOP(0)
        EVT_CALL(PlaySoundAtNpc, NPC_SELF, SOUND_20D9, 0)
        EVT_CALL(NpcJump0, NPC_SELF, -100, 80, -80, 20)
        EVT_WAIT(10)
        EVT_CALL(PlaySoundAtNpc, NPC_SELF, SOUND_20D9, 0)
        EVT_CALL(NpcJump0, NPC_SELF, 100, 80, -80, 20)
        EVT_WAIT(10)
        EVT_CALL(PlaySoundAtNpc, NPC_SELF, SOUND_20D9, 0)
        EVT_CALL(NpcJump0, NPC_SELF, 30, 40, -80, 20)
        EVT_WAIT(10)
        EVT_CALL(PlaySoundAtNpc, NPC_SELF, SOUND_20D9, 0)
        EVT_CALL(NpcJump0, NPC_SELF, 135, 15, -100, 20)
        EVT_WAIT(10)
        EVT_CALL(PlaySoundAtNpc, NPC_SELF, SOUND_20D9, 0)
        EVT_CALL(NpcJump0, NPC_SELF, 30, 0, 0, 20)
        EVT_WAIT(10)
    EVT_END_LOOP
    EVT_RETURN
    EVT_END
};

EvtScript N(EVS_NpcAI_Fuzzipede) = {
    EVT_EXEC(N(EVS_SetupFlotsam))
    EVT_LOOP(0)
        EVT_CALL(GetSelfVar, 0, LVar0)
        EVT_IF_EQ(LVar0, 1)
            EVT_BREAK_LOOP
        EVT_END_IF
        EVT_WAIT(1)
    EVT_END_LOOP
    EVT_EXEC_GET_TID(N(EVS_Fuzzipede_JumpAround), LVarA)
    EVT_CALL(SetSelfVar, 3, LVarA)
    EVT_LOOP(0)
        EVT_CALL(GetSelfVar, 1, LVar0)
        EVT_IF_EQ(LVar0, 1)
            EVT_BREAK_LOOP
        EVT_END_IF
        EVT_WAIT(1)
    EVT_END_LOOP
    EVT_CALL(SetSelfEnemyFlagBits, ENEMY_FLAGS_100000, 0)
    EVT_CALL(StartBossBattle, SONG_SPECIAL_BATTLE)
    EVT_RETURN
    EVT_END
};

EvtScript N(EVS_NpcHit_Fuzzipede) = {
    EVT_CALL(DisablePlayerInput, TRUE)
    EVT_CALL(GetSelfVar, 3, LVar0)
    EVT_KILL_THREAD(LVar0)
    EVT_CALL(SetSelfVar, 1, 1)
    EVT_RETURN
    EVT_END
};

EvtScript N(EVS_NpcDefeat_Fuzzipede) = {
    EVT_CALL(DisablePlayerPhysics, TRUE)
    EVT_CALL(SetPlayerActionState, ACTION_STATE_LAND)
    EVT_CALL(SetPlayerPos, -40, 0, 0)
    EVT_CALL(SetPlayerFlagBits, PS_FLAGS_NO_FLIPPING, TRUE)
    EVT_CALL(InterpPlayerYaw, 90, 0)
    EVT_CALL(SetPlayerFlagBits, PS_FLAGS_NO_FLIPPING, FALSE)
    EVT_CALL(SetNpcPos, NPC_SELF, 30, 0, 0)
    EVT_CALL(SetNpcYaw, NPC_SELF, 270)
    EVT_CALL(UseSettingsFrom, CAM_DEFAULT, -5, 0, 0)
    EVT_CALL(SetPanTarget, CAM_DEFAULT, -5, 0, 0)
    EVT_CALL(SetCamSpeed, CAM_DEFAULT, EVT_FLOAT(90.0))
    EVT_CALL(PanToTarget, CAM_DEFAULT, 0, 1)
    EVT_WAIT(1)
    EVT_CALL(SpeakToPlayer, NPC_SELF, ANIM_Fuzzipede_Anim24, ANIM_Fuzzipede_Anim04, 0, MSG_MAC_Port_009D)
    EVT_WAIT(10)
    EVT_CALL(ShowMessageAtScreenPos, MSG_MAC_Port_009E, -300, 100)
    EVT_WAIT(10)
    EVT_CALL(FadeOutMusic, 0, 1000)
    EVT_CALL(SetSelfVar, 2, 1)
    EVT_THREAD
        EVT_CALL(PlaySound, SOUND_42)
        EVT_SET(LVar0, 0)
        EVT_LOOP(150)
            EVT_ADD(LVar0, 1)
            EVT_CALL(TranslateGroup, MODEL_mizu, 0, LVar0, 0)
            EVT_CALL(TranslateModel, MODEL_hako1, 0, LVar0, 0)
            EVT_CALL(TranslateModel, MODEL_hako2, 0, LVar0, 0)
            EVT_CALL(TranslateModel, MODEL_hako3, 0, LVar0, 0)
            EVT_CALL(TranslateModel, MODEL_hako6, 0, LVar0, 0)
            EVT_CALL(TranslateModel, MODEL_bin1, 0, LVar0, 0)
            EVT_CALL(TranslateModel, MODEL_bin2, 0, LVar0, 0)
            EVT_CALL(TranslateModel, MODEL_bin3, 0, LVar0, 0)
            EVT_CALL(TranslateModel, MODEL_bin4, 0, LVar0, 0)
            EVT_WAIT(1)
        EVT_END_LOOP
    EVT_END_THREAD
    EVT_THREAD
        EVT_SET(LVar0, 0)
        EVT_LOOP(75)
            EVT_ADD(LVar0, 1)
            EVT_CALL(TranslateGroup, MODEL_fune, 0, LVar0, 0)
            EVT_CALL(TranslateModel, MODEL_hako4, 0, LVar0, 0)
            EVT_CALL(TranslateModel, MODEL_hako5, 0, LVar0, 0)
            EVT_WAIT(1)
        EVT_END_LOOP
    EVT_END_THREAD
    EVT_THREAD
        EVT_WAIT(20)
        EVT_CALL(HidePlayerShadow, TRUE)
        EVT_CALL(EnableNpcShadow, NPC_PARTNER, FALSE)
        EVT_CALL(SetPlayerAnimation, ANIM_Mario_80017)
        EVT_CALL(GetPlayerPos, LVar1, LVar0, LVar3)
        EVT_LOOP(150)
            EVT_ADD(LVar0, 1)
            EVT_CALL(SetPlayerPos, LVar1, LVar0, LVar3)
            EVT_WAIT(1)
        EVT_END_LOOP
    EVT_END_THREAD
    EVT_THREAD
        EVT_WAIT(20)
        EVT_CALL(EnableNpcShadow, NPC_SELF, FALSE)
        EVT_CALL(GetNpcPos, NPC_Fuzzipede, LVar1, LVar0, LVar3)
        EVT_LOOP(150)
            EVT_ADD(LVar0, 1)
            EVT_CALL(SetNpcPos, NPC_SELF, LVar1, LVar0, LVar3)
            EVT_WAIT(1)
        EVT_END_LOOP
    EVT_END_THREAD
    EVT_CHILD_THREAD
        EVT_LOOP(0)
            EVT_CALL(InterpNpcYaw, NPC_Fuzzipede, 90, 7)
            EVT_WAIT(10)
            EVT_CALL(InterpNpcYaw, NPC_Fuzzipede, 270, 7)
            EVT_WAIT(10)
        EVT_END_LOOP
    EVT_END_CHILD_THREAD
    EVT_WAIT(120)
    EVT_CALL(GotoMap, EVT_PTR("mac_05"), mac_05_ENTRY_2)
    EVT_WAIT(100)
    EVT_CALL(InterruptUsePartner)
    EVT_CALL(DisablePlayerPhysics, FALSE)
    EVT_CALL(DisablePlayerInput, FALSE)
    EVT_RETURN
    EVT_END
};

EvtScript N(EVS_NpcAuxAI_Fuzzipede) = {
    EVT_CALL(SetNpcPos, NPC_SELF, 100, 80, -80)
    EVT_EXEC(N(EVS_Fuzzipede_ReactToLight))
    EVT_RETURN
    EVT_END
};

NpcSettings N(NpcSettings_Fuzzipede) = {
    .defaultAnim = ANIM_Fuzzipede_Anim04,
    .height = 24,
    .radius = 24,
    .otherAI = &N(EVS_NpcAuxAI_Fuzzipede),
    .ai = &N(EVS_NpcAI_Fuzzipede),
    .onHit = &N(EVS_NpcHit_Fuzzipede),
    .onDefeat = &N(EVS_NpcDefeat_Fuzzipede),
    .unk_24 = 100,
};

StaticNpc N(NpcData_Fuzzipede) = {
    .id = NPC_Fuzzipede,
    .settings = &N(NpcSettings_Fuzzipede),
    .pos = { 333.0f, -10.0f, -130.0f },
    .yaw = 90,
    .flags = ENEMY_FLAGS_4 | ENEMY_FLAGS_100 | ENEMY_FLAGS_800 | ENEMY_FLAGS_8000 | ENEMY_FLAGS_40000 | ENEMY_FLAGS_100000 | ENEMY_FLAGS_IGNORE_TOUCH | ENEMY_FLAGS_IGNORE_JUMP | ENEMY_FLAGS_IGNORE_HAMMER | ENEMY_FLAGS_10000000,
    .drops = {
        .dropFlags = NPC_DROP_FLAGS_80,
        .heartDrops  = NO_DROPS,
        .flowerDrops = NO_DROPS,
    },
    .animations = {
        .idle   = ANIM_Fuzzipede_Anim04,
    },
};

NpcGroupList N(DefaultNPCs) = {
    NPC_GROUP(N(NpcData_Fuzzipede), BTL_KGR_FORMATION_00, BTL_KGR_STAGE_00),
    {}
};
