#include "flo_18.h"

#include "world/common/todo/UnkFunc42.inc.c"

#include "world/common/enemy/complete/Lakitu.h"
#include "world/common/enemy/complete/YMagikoopa.h"

NpcSettings N(NpcSettings_Lakitu) = {
    .height = 32,
    .radius = 24,
    .level = 20,
    .onHit = &EnemyNpcHit,
    .onDefeat = &EnemyNpcDefeat,
};

NpcSettings N(NpcSettings_Magikoopa) = {
    .height = 34,
    .radius = 24,
    .level = 26,
    .onHit = &EnemyNpcHit,
    .onDefeat = &EnemyNpcDefeat,
};

Vec3f N(RetreatPath_Magikoopa)[] = {
    {  -55.0,    15.0,   35.0 },
    { -155.0,    35.0,   35.0 },
    { -255.0,    75.0,   35.0 },
    { -355.0,   155.0,   35.0 },
    { -455.0,   315.0,   35.0 },
};

Vec3f N(RetreatPath_Lakitu_01)[] = {
    {  -20.0,    15.0,   30.0 },
    { -120.0,    35.0,   30.0 },
    { -220.0,    75.0,   30.0 },
    { -320.0,   155.0,   30.0 },
    { -420.0,   315.0,   30.0 },
};

Vec3f N(RetreatPath_Lakitu_02)[] = {
    {   65.0,    15.0,   30.0 },
    {  -35.0,    35.0,   30.0 },
    { -135.0,    75.0,   30.0 },
    { -235.0,   155.0,   30.0 },
    { -335.0,   315.0,   30.0 },
};

Vec3f N(RetreatPath_Lakitu_03)[] = {
    {  120.0,    15.0,   30.0 },
    {   20.0,    35.0,   30.0 },
    {  -80.0,    75.0,   30.0 },
    { -180.0,   155.0,   30.0 },
    { -280.0,   315.0,   30.0 },
};

EvtScript N(EVS_Scene_LakilesterLikesBeingGood) = {
    EVT_CALL(DisablePlayerInput, TRUE)
    EVT_CALL(DisablePartnerAI, 0)
    EVT_CALL(SetPlayerPos, 30, 0, 50)
    EVT_CALL(InterpPlayerYaw, 90, 0)
    EVT_CALL(SetNpcPos, NPC_PARTNER, 65, 0, 50)
    EVT_WAIT(30)
    EVT_CALL(AdjustCam, CAM_DEFAULT, EVT_FLOAT(8.0), 0, 300, EVT_FLOAT(19.0), EVT_FLOAT(-8.5))
    EVT_CALL(GetCurrentPartnerID, LVar0)
    EVT_CALL(BringPartnerOut, PARTNER_LAKILESTER)
    EVT_IF_NE(LVar0, PARTNER_LAKILESTER)
        EVT_CALL(SetNpcJumpscale, NPC_PARTNER, EVT_FLOAT(0.0))
        EVT_CALL(GetPlayerPos, LVar1, LVar2, LVar3)
        EVT_ADD(LVar1, 20)
        EVT_ADD(LVar2, 20)
        EVT_ADD(LVar3, 20)
        EVT_CALL(NpcJump0, NPC_PARTNER, LVar1, LVar2, LVar3, 30)
    EVT_END_IF
    EVT_CALL(PlayerFaceNpc, NPC_PARTNER, FALSE)
    EVT_CALL(NpcFacePlayer, NPC_PARTNER, 0)
    EVT_CALL(SpeakToPlayer, NPC_PARTNER, ANIM_WorldLakilester_Talk, ANIM_WorldLakilester_Idle, 5, MSG_CH6_00C9)
    EVT_CALL(SetPlayerAnimation, ANIM_Mario_NodYes)
    EVT_WAIT(10)
    EVT_CALL(SetPlayerAnimation, ANIM_Mario_StandStill)
    EVT_WAIT(20)
    EVT_CALL(EnablePartnerAI)
    EVT_CALL(PutPartnerAway)
    EVT_CALL(ResetCam, CAM_DEFAULT, EVT_FLOAT(4.0))
    EVT_CALL(DisablePlayerInput, FALSE)
    EVT_RETURN
    EVT_END
};

EvtScript N(EVS_GangRetreat) = {
    EVT_THREAD
        EVT_CALL(PlaySoundAtNpc, NPC_FlyingMagikoopa, SOUND_19E, 0)
        EVT_CALL(SetNpcFlagBits, NPC_FlyingMagikoopa, NPC_FLAG_100, TRUE)
        EVT_CALL(InterpNpcYaw, NPC_FlyingMagikoopa, 270, 0)
        EVT_CALL(LoadPath, 60, EVT_PTR(N(RetreatPath_Magikoopa)), ARRAY_COUNT(N(RetreatPath_Magikoopa)), EASING_LINEAR)
        EVT_LOOP(0)
            EVT_CALL(GetNextPathPos)
            EVT_CALL(SetNpcPos, NPC_FlyingMagikoopa, LVar1, LVar2, LVar3)
            EVT_WAIT(1)
            EVT_IF_NE(LVar0, 1)
                EVT_BREAK_LOOP
            EVT_END_IF
        EVT_END_LOOP
    EVT_END_THREAD
    EVT_WAIT(15)
    EVT_THREAD
        EVT_CALL(PlaySoundAtNpc, NPC_Lakitu_01, SOUND_19F, 0)
        EVT_CALL(SetNpcFlagBits, NPC_Lakitu_01, NPC_FLAG_100, TRUE)
        EVT_CALL(InterpNpcYaw, NPC_Lakitu_01, 270, 0)
        EVT_CALL(LoadPath, 60, EVT_PTR(N(RetreatPath_Lakitu_01)), ARRAY_COUNT(N(RetreatPath_Lakitu_01)), EASING_LINEAR)
        EVT_LOOP(0)
            EVT_CALL(GetNextPathPos)
            EVT_CALL(SetNpcPos, NPC_Lakitu_01, LVar1, LVar2, LVar3)
            EVT_WAIT(1)
            EVT_IF_NE(LVar0, 1)
                EVT_BREAK_LOOP
            EVT_END_IF
        EVT_END_LOOP
    EVT_END_THREAD
    EVT_THREAD
        EVT_CALL(SetNpcFlagBits, NPC_Lakitu_02, NPC_FLAG_100, TRUE)
        EVT_CALL(InterpNpcYaw, NPC_Lakitu_02, 270, 0)
        EVT_CALL(LoadPath, 70, EVT_PTR(N(RetreatPath_Lakitu_02)), ARRAY_COUNT(N(RetreatPath_Lakitu_02)), EASING_LINEAR)
        EVT_LOOP(0)
            EVT_CALL(GetNextPathPos)
            EVT_CALL(SetNpcPos, NPC_Lakitu_02, LVar1, LVar2, LVar3)
            EVT_WAIT(1)
            EVT_IF_NE(LVar0, 1)
                EVT_BREAK_LOOP
            EVT_END_IF
        EVT_END_LOOP
    EVT_END_THREAD
    EVT_CALL(PlaySoundAtNpc, NPC_Lakitu_03, SOUND_19F, 0)
    EVT_CALL(SetNpcFlagBits, NPC_Lakitu_03, NPC_FLAG_100, TRUE)
    EVT_CALL(InterpNpcYaw, NPC_Lakitu_03, 270, 0)
    EVT_CALL(LoadPath, 80, EVT_PTR(N(RetreatPath_Lakitu_03)), ARRAY_COUNT(N(RetreatPath_Lakitu_03)), EASING_LINEAR)
    EVT_LOOP(0)
        EVT_CALL(GetNextPathPos)
        EVT_CALL(SetNpcPos, NPC_Lakitu_03, LVar1, LVar2, LVar3)
        EVT_WAIT(1)
        EVT_IF_NE(LVar0, 1)
            EVT_BREAK_LOOP
        EVT_END_IF
    EVT_END_LOOP
    EVT_RETURN
    EVT_END
};

EvtScript N(EVS_ChargeAtPlayer) = {
    EVT_WAIT(5)
    EVT_CALL(IsPlayerWithin, 40, 0, 200, LVar0)
    EVT_IF_EQ(LVar0, 0)
        EVT_SET(LVar3, 45)
    EVT_ELSE
        EVT_SET(LVar3, 25)
    EVT_END_IF
    EVT_SET(LVar4, LVar3)
    EVT_ADD(LVar4, -5)
    EVT_CALL(GetPlayerPos, LVar0, LVar1, LVar2)
    EVT_IF_GT(LVar2, -61)
        EVT_CHILD_THREAD
            EVT_CALL(SetNpcFlagBits, NPC_Lakitu_01, NPC_FLAG_100, TRUE)
            EVT_CALL(NpcMoveTo, NPC_Lakitu_01, LVar0, 55, LVar3)
        EVT_END_CHILD_THREAD
        EVT_CHILD_THREAD
            EVT_CALL(SetNpcFlagBits, NPC_Lakitu_02, NPC_FLAG_100, TRUE)
            EVT_CALL(NpcMoveTo, NPC_Lakitu_02, LVar0, 55, LVar3)
        EVT_END_CHILD_THREAD
        EVT_CHILD_THREAD
            EVT_CALL(SetNpcFlagBits, NPC_Lakitu_03, NPC_FLAG_100, TRUE)
            EVT_CALL(NpcMoveTo, NPC_Lakitu_03, LVar0, 55, LVar3)
        EVT_END_CHILD_THREAD
        EVT_WAIT(LVar4)
    EVT_END_IF
    EVT_RETURN
    EVT_END
};

EvtScript N(EVS_Scene_GangDefeated) = {
    EVT_CALL(DisablePlayerInput, TRUE)
    EVT_CALL(DisablePartnerAI, 0)
    EVT_CALL(GetNpcPos, NPC_PARTNER, LVar0, LVar1, LVar2)
    EVT_CALL(SetNpcPos, NPC_PARTNER, 65, LVar1, 80)
    EVT_CALL(SetNpcYaw, NPC_PARTNER, 270)
    EVT_CALL(AdjustCam, CAM_DEFAULT, EVT_FLOAT(8.0), 0, 450, EVT_FLOAT(17.0), EVT_FLOAT(-6.0))
    EVT_CALL(SpeakToPlayer, NPC_FlyingMagikoopa, ANIM_FlyingMagikoopa_Yellow_Anim09, ANIM_FlyingMagikoopa_Yellow_Anim01, 0, MSG_CH6_00BB)
    EVT_WAIT(20)
    EVT_EXEC(N(EVS_GangRetreat))
    EVT_WAIT(80)
    EVT_CALL(AdjustCam, CAM_DEFAULT, EVT_FLOAT(8.0), 0, 300, EVT_FLOAT(19.0), EVT_FLOAT(-8.5))
    EVT_CALL(GetCurrentPartnerID, LVar0)
    EVT_CALL(BringPartnerOut, PARTNER_LAKILESTER)
    EVT_IF_NE(LVar0, PARTNER_LAKILESTER)
        EVT_CALL(SetNpcJumpscale, NPC_PARTNER, EVT_FLOAT(0.0))
        EVT_CALL(GetPlayerPos, LVar1, LVar2, LVar3)
        EVT_ADD(LVar1, 20)
        EVT_ADD(LVar2, 20)
        EVT_ADD(LVar3, 20)
        EVT_CALL(NpcJump0, NPC_PARTNER, LVar1, LVar2, LVar3, 30)
    EVT_END_IF
    EVT_CALL(NpcFacePlayer, NPC_PARTNER, 0)
    EVT_CALL(DisablePartnerAI, 0)
    EVT_CALL(SpeakToPlayer, NPC_PARTNER, ANIM_WorldLakilester_Talk, ANIM_WorldLakilester_Idle, 5, MSG_CH6_00C1)
    EVT_CALL(EnablePartnerAI)
    EVT_WAIT(20)
    EVT_CALL(PutPartnerAway)
    EVT_CALL(ResetCam, CAM_DEFAULT, EVT_FLOAT(4.0))
    EVT_SET(GB_StoryProgress, STORY_CH6_DEFEATED_PUFF_PUFF_GUARDS)
    EVT_CALL(DisablePlayerInput, FALSE)
    EVT_CALL(AwaitPlayerApproach, -250, 0, 50)
    EVT_CALL(DisablePlayerInput, TRUE)
    EVT_CALL(GetCurrentPartnerID, LVar0)
    EVT_CALL(BringPartnerOut, PARTNER_LAKILESTER)
    EVT_IF_NE(LVar0, PARTNER_LAKILESTER)
        EVT_CALL(SetNpcJumpscale, NPC_PARTNER, EVT_FLOAT(0.0))
        EVT_CALL(GetPlayerPos, LVar1, LVar2, LVar3)
        EVT_ADD(LVar1, 20)
        EVT_ADD(LVar2, 20)
        EVT_ADD(LVar3, 20)
        EVT_CALL(NpcJump0, NPC_PARTNER, LVar1, LVar2, LVar3, 30)
    EVT_END_IF
    EVT_CALL(PlayerFaceNpc, NPC_PARTNER, FALSE)
    EVT_CALL(NpcFacePlayer, NPC_PARTNER, 0)
    EVT_CALL(DisablePartnerAI, 0)
    EVT_CALL(SpeakToPlayer, NPC_PARTNER, ANIM_WorldLakilester_Talk, ANIM_WorldLakilester_Idle, 5, MSG_CH6_00C2)
    EVT_CALL(EnablePartnerAI)
    EVT_CALL(PutPartnerAway)
    EVT_CALL(ResetCam, CAM_DEFAULT, EVT_FLOAT(4.0))
    EVT_CALL(DisablePlayerInput, FALSE)
    EVT_RETURN
    EVT_END
};

EvtScript N(EVS_NpcIdle_Magikoopa) = {
    EVT_LOOP(0)
        EVT_CALL(GetSelfVar, 0, LVar0)
        EVT_IF_NE(LVar0, 0)
            EVT_BREAK_LOOP
        EVT_END_IF
        EVT_WAIT(1)
    EVT_END_LOOP
    EVT_CALL(DisablePlayerInput, TRUE)
    EVT_WAIT(10)
    EVT_CALL(GetPlayerPos, LVar0, LVar1, LVar2)
    EVT_CALL(UseSettingsFrom, CAM_DEFAULT, LVar0, LVar1, LVar2)
    EVT_CALL(SetPanTarget, CAM_DEFAULT, LVar0, LVar1, LVar2)
    EVT_CALL(SetCamDistance, CAM_DEFAULT, 1000)
    EVT_CALL(SetCamPitch, CAM_DEFAULT, EVT_FLOAT(17.0), EVT_FLOAT(-6.0))
    EVT_CALL(SetCamSpeed, CAM_DEFAULT, EVT_FLOAT(4.0))
    EVT_CALL(PanToTarget, CAM_DEFAULT, 0, 1)
    EVT_CALL(DisablePlayerInput, FALSE)
    EVT_CALL(StartBossBattle, SONG_SPECIAL_BATTLE)
    EVT_RETURN
    EVT_END
};

EvtScript N(EVS_NpcDefeat_Lakitu) = {
    EVT_CALL(GetBattleOutcome, LVar0)
    EVT_SWITCH(LVar0)
        EVT_CASE_EQ(OUTCOME_PLAYER_WON)
            EVT_CALL(GetSelfNpcID, LVar0)
            EVT_IF_EQ(LVar0, 3)
                EVT_CALL(SetNpcPos, NPC_Magikoopa, NPC_DISPOSE_LOCATION)
                EVT_CALL(SetNpcPos, NPC_FlyingMagikoopa, -55, 15, 35)
                EVT_CALL(GetNpcYaw, NPC_Magikoopa, LVar0)
                EVT_CALL(SetNpcYaw, NPC_FlyingMagikoopa, 90)
                EVT_CALL(InterpPlayerYaw, 180, 0)
                EVT_CALL(SetPlayerPos, 30, 0, 80)
                EVT_CALL(SetNpcYaw, NPC_Lakitu_01, 90)
                EVT_CALL(SetNpcPos, NPC_Lakitu_01, -20, 15, 30)
                EVT_CALL(SetNpcYaw, NPC_Lakitu_02, 270)
                EVT_CALL(SetNpcPos, NPC_Lakitu_02, 65, 15, 30)
                EVT_CALL(SetNpcYaw, NPC_Lakitu_03, 270)
                EVT_CALL(SetNpcPos, NPC_Lakitu_03, 120, 15, 30)
                EVT_EXEC(N(EVS_Scene_GangDefeated))
            EVT_END_IF
        EVT_CASE_EQ(OUTCOME_PLAYER_LOST)
        EVT_CASE_EQ(OUTCOME_PLAYER_FLED)
    EVT_END_SWITCH
    EVT_RETURN
    EVT_END
};

EvtScript N(EVS_ReactionFacePlayer) = {
    EVT_SWITCH(MV_ReactingNpc)
        EVT_CASE_EQ(0)
            EVT_CALL(NpcFacePlayer, NPC_Magikoopa, 1)
        EVT_CASE_EQ(1)
            EVT_CALL(NpcFacePlayer, NPC_Lakitu_01, 1)
        EVT_CASE_EQ(2)
            EVT_CALL(NpcFacePlayer, NPC_Lakitu_02, 1)
        EVT_CASE_EQ(3)
            EVT_CALL(NpcFacePlayer, NPC_Lakitu_03, 1)
    EVT_END_SWITCH
    EVT_RETURN
    EVT_END
};

EvtScript N(EVS_FirstReactionDialogue) = {
    EVT_SWITCH(MV_ReactingNpc)
        EVT_CASE_EQ(0)
            EVT_CALL(SpeakToPlayer, NPC_Magikoopa, ANIM_Magikoopa_Yellow_Anim02, ANIM_Magikoopa_Yellow_Anim01, 16, MSG_CH6_00B9)
            EVT_CALL(InterpNpcYaw, NPC_Magikoopa, 90, 0)
        EVT_CASE_EQ(1)
            EVT_CALL(SpeakToPlayer, NPC_Lakitu_01, ANIM_Lakitu_Anim16, ANIM_Lakitu_Anim01, 16, MSG_CH6_00BF)
            EVT_CALL(InterpNpcYaw, NPC_Lakitu_01, 90, 0)
        EVT_CASE_EQ(2)
            EVT_CALL(SpeakToPlayer, NPC_Lakitu_02, ANIM_Lakitu_Anim16, ANIM_Lakitu_Anim01, 16, MSG_CH6_00BF)
            EVT_CALL(InterpNpcYaw, NPC_Lakitu_02, 270, 0)
        EVT_CASE_EQ(3)
            EVT_CALL(SpeakToPlayer, NPC_Lakitu_03, ANIM_Lakitu_Anim16, ANIM_Lakitu_Anim01, 16, MSG_CH6_00BF)
            EVT_CALL(InterpNpcYaw, NPC_Lakitu_03, 270, 0)
    EVT_END_SWITCH
    EVT_RETURN
    EVT_END
};

EvtScript N(EVS_SecondReactionDialogue) = {
    EVT_SWITCH(MV_ReactingNpc)
        EVT_CASE_EQ(0)
            EVT_CALL(SpeakToPlayer, NPC_Magikoopa, ANIM_Magikoopa_Yellow_Anim02, ANIM_Magikoopa_Yellow_Anim01, 16, MSG_CH6_00BA)
        EVT_CASE_EQ(1)
            EVT_CALL(SpeakToPlayer, NPC_Lakitu_01, ANIM_Lakitu_Anim16, ANIM_Lakitu_Anim01, 16, MSG_CH6_00C0)
        EVT_CASE_EQ(2)
            EVT_CALL(SpeakToPlayer, NPC_Lakitu_02, ANIM_Lakitu_Anim16, ANIM_Lakitu_Anim01, 16, MSG_CH6_00C0)
        EVT_CASE_EQ(3)
            EVT_CALL(SpeakToPlayer, NPC_Lakitu_03, ANIM_Lakitu_Anim16, ANIM_Lakitu_Anim01, 16, MSG_CH6_00C0)
    EVT_END_SWITCH
    EVT_CALL(SetNpcVar, NPC_Magikoopa, 0, 1)
    EVT_WAIT(5)
    EVT_EXEC(N(EVS_ChargeAtPlayer))
    EVT_RETURN
    EVT_END
};

EvtScript N(EVS_GenericHitReaction) = {
    EVT_IF_GE(GB_StoryProgress, STORY_CH6_DEFEATED_PUFF_PUFF_GUARDS)
        EVT_RETURN
    EVT_END_IF
    EVT_CALL(DisablePlayerInput, TRUE)
    EVT_CALL(func_802D2C14, 1)
    EVT_CALL(SetNpcFlagBits, NPC_PARTNER, NPC_FLAG_100, TRUE)
    EVT_CALL(AdjustCam, CAM_DEFAULT, EVT_FLOAT(8.0), 0, 300, EVT_FLOAT(17.0), EVT_FLOAT(-6.0))
    EVT_EXEC_WAIT(N(EVS_ReactionFacePlayer))
    EVT_SWITCH(AB_FLO_GuardedMachineHitCount)
        EVT_CASE_EQ(0)
            EVT_EXEC_WAIT(N(EVS_FirstReactionDialogue))
            EVT_ADD(AB_FLO_GuardedMachineHitCount, 1)
            EVT_CALL(ResetCam, CAM_DEFAULT, EVT_FLOAT(4.0))
        EVT_CASE_EQ(1)
            EVT_EXEC_WAIT(N(EVS_SecondReactionDialogue))
    EVT_END_SWITCH
    EVT_CALL(func_802D2C14, 0)
    EVT_CALL(DisablePlayerInput, FALSE)
    EVT_RETURN
    EVT_END
};

EvtScript N(EVS_HitReaction_Magikoopa) = {
    EVT_IF_EQ(MV_ReactingNpc, -1)
        EVT_SET(MV_ReactingNpc, 0)
        EVT_EXEC_WAIT(N(EVS_GenericHitReaction))
        EVT_SET(MV_ReactingNpc, -1)
    EVT_END_IF
    EVT_RETURN
    EVT_END
};

EvtScript N(EVS_HitReaction_Lakitu_01) = {
    EVT_IF_EQ(MV_ReactingNpc, -1)
        EVT_SET(MV_ReactingNpc, 1)
        EVT_EXEC_WAIT(N(EVS_GenericHitReaction))
        EVT_SET(MV_ReactingNpc, -1)
    EVT_END_IF
    EVT_RETURN
    EVT_END
};

EvtScript N(EVS_HitReaction_Lakitu_02) = {
    EVT_IF_EQ(MV_ReactingNpc, -1)
        EVT_SET(MV_ReactingNpc, 2)
        EVT_EXEC_WAIT(N(EVS_GenericHitReaction))
        EVT_SET(MV_ReactingNpc, -1)
    EVT_END_IF
    EVT_RETURN
    EVT_END
};

EvtScript N(EVS_HitReaction_Lakitu_03) = {
    EVT_IF_EQ(MV_ReactingNpc, -1)
        EVT_SET(MV_ReactingNpc, 3)
        EVT_EXEC_WAIT(N(EVS_GenericHitReaction))
        EVT_SET(MV_ReactingNpc, -1)
    EVT_END_IF
    EVT_RETURN
    EVT_END
};

EvtScript N(EVS_GenericBombReaction) = {
    EVT_IF_GE(GB_StoryProgress, STORY_CH6_DEFEATED_PUFF_PUFF_GUARDS)
        EVT_RETURN
    EVT_END_IF
    EVT_CALL(DisablePlayerInput, TRUE)
    EVT_CALL(UseSettingsFrom, CAM_DEFAULT, LVar0, LVar1, LVar2)
    EVT_CALL(SetPanTarget, CAM_DEFAULT, LVar0, LVar1, LVar2)
    EVT_CALL(SetCamSpeed, CAM_DEFAULT, EVT_FLOAT(8.0))
    EVT_CALL(SetCamPitch, CAM_DEFAULT, EVT_FLOAT(17.0), EVT_FLOAT(-6.0))
    EVT_CALL(SetCamDistance, CAM_DEFAULT, 300)
    EVT_CALL(PanToTarget, CAM_DEFAULT, 0, 1)
    EVT_CALL(WaitForCam, CAM_DEFAULT, EVT_FLOAT(1.0))
    EVT_EXEC_WAIT(N(EVS_ReactionFacePlayer))
    EVT_IF_EQ(AB_FLO_GuardedMachineHitCount, 0)
        EVT_EXEC_WAIT(N(EVS_FirstReactionDialogue))
        EVT_ADD(AB_FLO_GuardedMachineHitCount, 1)
        EVT_CALL(ResetCam, CAM_DEFAULT, EVT_FLOAT(4.0))
    EVT_ELSE
        EVT_EXEC_WAIT(N(EVS_SecondReactionDialogue))
    EVT_END_IF
    EVT_CALL(DisablePlayerInput, FALSE)
    EVT_RETURN
    EVT_END
};

EvtScript N(EVS_BombReaction_Magikoopa) = {
    EVT_IF_EQ(MV_ReactingNpc, -1)
        EVT_SET(MV_ReactingNpc, 0)
        EVT_CALL(GetNpcPos, NPC_Magikoopa, LVar0, LVar1, LVar2)
        EVT_EXEC_WAIT(N(EVS_GenericBombReaction))
        EVT_SET(MV_ReactingNpc, -1)
    EVT_END_IF
    EVT_RETURN
    EVT_END
};

EvtScript N(EVS_BombReaction_Lakitu_01) = {
    EVT_IF_EQ(MV_ReactingNpc, -1)
        EVT_SET(MV_ReactingNpc, 1)
        EVT_CALL(GetNpcPos, NPC_Lakitu_01, LVar0, LVar1, LVar2)
        EVT_EXEC_WAIT(N(EVS_GenericBombReaction))
        EVT_SET(MV_ReactingNpc, -1)
    EVT_END_IF
    EVT_RETURN
    EVT_END
};

EvtScript N(EVS_BombReaction_Lakitu_02) = {
    EVT_IF_EQ(MV_ReactingNpc, -1)
        EVT_SET(MV_ReactingNpc, 2)
        EVT_CALL(GetNpcPos, NPC_Lakitu_02, LVar0, LVar1, LVar2)
        EVT_EXEC_WAIT(N(EVS_GenericBombReaction))
        EVT_SET(MV_ReactingNpc, -1)
    EVT_END_IF
    EVT_RETURN
    EVT_END
};

EvtScript N(EVS_BombReaction_Lakitu_03) = {
    EVT_IF_EQ(MV_ReactingNpc, -1)
        EVT_SET(MV_ReactingNpc, 3)
        EVT_CALL(GetNpcPos, NPC_Lakitu_03, LVar0, LVar1, LVar2)
        EVT_EXEC_WAIT(N(EVS_GenericBombReaction))
        EVT_SET(MV_ReactingNpc, -1)
    EVT_END_IF
    EVT_RETURN
    EVT_END
};

BombTrigger N(Npc_BombTrigger_01) = {
    .pos = { 5.0f, 0.0f, -10.0f },
    .radius = 0.0f
};

BombTrigger N(Npc_BombTrigger_02) = {
    .pos = { -5.0f, 0.0f, -20.0f },
    .radius = 0.0f
};

BombTrigger N(Npc_BombTrigger_03) = {
    .pos = { 50.0f, 0.0f, -10.0f },
    .radius = 0.0f
};

BombTrigger N(Npc_BombTrigger_04) = {
    .pos = { 105.0f, 0.0f, -10.0f },
    .radius = 0.0f
};

EvtScript N(EVS_SetupMachineDamageReactions) = {
    EVT_SET(MV_ReactingNpc, -1)
    EVT_BIND_TRIGGER(EVT_PTR(N(EVS_HitReaction_Magikoopa)),  TRIGGER_WALL_HAMMER, COLLIDER_o174, 1, 0)
    EVT_BIND_TRIGGER(EVT_PTR(N(EVS_HitReaction_Magikoopa)),  TRIGGER_WALL_HAMMER, COLLIDER_o130, 1, 0)
    EVT_BIND_TRIGGER(EVT_PTR(N(EVS_BombReaction_Magikoopa)), TRIGGER_POINT_BOMB,  EVT_PTR(N(Npc_BombTrigger_02)), 1, 0)
    EVT_BIND_TRIGGER(EVT_PTR(N(EVS_BombReaction_Lakitu_01)), TRIGGER_POINT_BOMB,  EVT_PTR(N(Npc_BombTrigger_01)), 1, 0)
    EVT_BIND_TRIGGER(EVT_PTR(N(EVS_HitReaction_Lakitu_02)),  TRIGGER_WALL_HAMMER, COLLIDER_o127, 1, 0)
    EVT_BIND_TRIGGER(EVT_PTR(N(EVS_BombReaction_Lakitu_02)), TRIGGER_POINT_BOMB,  EVT_PTR(N(Npc_BombTrigger_03)), 1, 0)
    EVT_BIND_TRIGGER(EVT_PTR(N(EVS_HitReaction_Lakitu_03)),  TRIGGER_WALL_HAMMER, COLLIDER_o131, 1, 0)
    EVT_BIND_TRIGGER(EVT_PTR(N(EVS_BombReaction_Lakitu_03)), TRIGGER_POINT_BOMB,  EVT_PTR(N(Npc_BombTrigger_04)), 1, 0)
    EVT_RETURN
    EVT_END
};

EvtScript N(EVS_NpcInteract_Lakitu) = {
    EVT_SWITCH(AB_FLO_GuardLakituTalkCount)
        EVT_CASE_EQ(0)
            EVT_CALL(GetSelfNpcID, LVar0)
            EVT_IF_EQ(LVar0, 3)
                EVT_CALL(SpeakToPlayer, NPC_SELF, ANIM_Magikoopa_Yellow_Anim02, ANIM_Magikoopa_Yellow_Anim01, 5, MSG_CH6_00B6)
            EVT_ELSE
                EVT_CALL(SpeakToPlayer, NPC_SELF, ANIM_Lakitu_Anim16, ANIM_Lakitu_Anim01, 5, MSG_CH6_00BC)
            EVT_END_IF
            EVT_ADD(AB_FLO_GuardLakituTalkCount, 1)
        EVT_CASE_EQ(1)
            EVT_CALL(GetSelfNpcID, LVar0)
            EVT_IF_EQ(LVar0, 3)
                EVT_CALL(SpeakToPlayer, NPC_SELF, ANIM_Magikoopa_Yellow_Anim02, ANIM_Magikoopa_Yellow_Anim01, 5, MSG_CH6_00B7)
            EVT_ELSE
                EVT_CALL(SpeakToPlayer, NPC_SELF, ANIM_Lakitu_Anim16, ANIM_Lakitu_Anim01, 5, MSG_CH6_00BD)
            EVT_END_IF
            EVT_ADD(AB_FLO_GuardLakituTalkCount, 1)
        EVT_CASE_EQ(2)
            EVT_CALL(AdjustCam, CAM_DEFAULT, EVT_FLOAT(8.0), 0, 300, EVT_FLOAT(19.0), EVT_FLOAT(-9.0))
            EVT_CALL(GetSelfNpcID, LVar0)
            EVT_IF_EQ(LVar0, 3)
                EVT_CALL(SpeakToPlayer, NPC_SELF, ANIM_Magikoopa_Yellow_Anim02, ANIM_Magikoopa_Yellow_Anim01, 5, MSG_CH6_00B8)
                EVT_CALL(NpcFacePlayer, NPC_SELF, 0)
                EVT_WAIT(15)
                EVT_CALL(EndSpeech, NPC_SELF, ANIM_Magikoopa_Yellow_Anim02, ANIM_Magikoopa_Yellow_Anim01, 0)
            EVT_ELSE
                EVT_CALL(SpeakToPlayer, NPC_SELF, ANIM_Lakitu_Anim16, ANIM_Lakitu_Anim01, 5, MSG_CH6_00BE)
                EVT_CALL(NpcFacePlayer, NPC_SELF, 0)
                EVT_WAIT(15)
                EVT_CALL(EndSpeech, NPC_SELF, ANIM_Lakitu_Anim16, ANIM_Lakitu_Anim01, 0)
            EVT_END_IF
            EVT_CALL(SetNpcVar, NPC_Magikoopa, 0, 1)
            EVT_WAIT(5)
            EVT_EXEC(N(EVS_ChargeAtPlayer))
            EVT_CALL(BindNpcInteract, NPC_Lakitu_01, 0)
            EVT_CALL(BindNpcInteract, NPC_Lakitu_02, 0)
            EVT_CALL(BindNpcInteract, NPC_Lakitu_03, 0)
            EVT_CALL(BindNpcInteract, NPC_Magikoopa, 0)
    EVT_END_SWITCH
    EVT_RETURN
    EVT_END
};

EvtScript N(EVS_NpcInit_Magikoopa) = {
    EVT_IF_LT(GB_StoryProgress, STORY_CH6_DEFEATED_PUFF_PUFF_GUARDS)
        EVT_CALL(BindNpcIdle, NPC_SELF, EVT_PTR(N(EVS_NpcIdle_Magikoopa)))
        EVT_CALL(BindNpcInteract, NPC_SELF, EVT_PTR(N(EVS_NpcInteract_Lakitu)))
        EVT_CALL(BindNpcDefeat, NPC_SELF, EVT_PTR(N(EVS_NpcDefeat_Lakitu)))
    EVT_ELSE
        EVT_CALL(SetNpcPos, NPC_SELF, NPC_DISPOSE_LOCATION)
    EVT_END_IF
    EVT_RETURN
    EVT_END
};

EvtScript N(EVS_NpcInit_FlyingMagikoopa) = {
    EVT_IF_LT(GB_StoryProgress, STORY_CH6_DEFEATED_PUFF_PUFF_GUARDS)
        EVT_CALL(BindNpcDefeat, NPC_SELF, EVT_PTR(N(EVS_NpcDefeat_Lakitu)))
    EVT_ELSE
        EVT_CALL(SetNpcPos, NPC_SELF, NPC_DISPOSE_LOCATION)
    EVT_END_IF
    EVT_RETURN
    EVT_END
};

EvtScript N(EVS_NpcInit_Lakitu_01) = {
    EVT_IF_LT(GB_StoryProgress, STORY_CH6_DEFEATED_PUFF_PUFF_GUARDS)
        EVT_CALL(BindNpcInteract, NPC_SELF, EVT_PTR(N(EVS_NpcInteract_Lakitu)))
        EVT_CALL(BindNpcDefeat, NPC_SELF, EVT_PTR(N(EVS_NpcDefeat_Lakitu)))
    EVT_ELSE
        EVT_CALL(SetNpcPos, NPC_SELF, NPC_DISPOSE_LOCATION)
    EVT_END_IF
    EVT_RETURN
    EVT_END
};

EvtScript N(EVS_NpcInit_Lakitu_02) = {
    EVT_IF_LT(GB_StoryProgress, STORY_CH6_DEFEATED_PUFF_PUFF_GUARDS)
        EVT_CALL(BindNpcInteract, NPC_SELF, EVT_PTR(N(EVS_NpcInteract_Lakitu)))
        EVT_CALL(BindNpcDefeat, NPC_SELF, EVT_PTR(N(EVS_NpcDefeat_Lakitu)))
    EVT_ELSE
        EVT_CALL(SetNpcPos, NPC_SELF, NPC_DISPOSE_LOCATION)
    EVT_END_IF
    EVT_RETURN
    EVT_END
};

EvtScript N(EVS_NpcInit_Lakitu_03) = {
    EVT_IF_LT(GB_StoryProgress, STORY_CH6_DEFEATED_PUFF_PUFF_GUARDS)
        EVT_CALL(BindNpcInteract, NPC_SELF, EVT_PTR(N(EVS_NpcInteract_Lakitu)))
        EVT_CALL(BindNpcDefeat, NPC_SELF, EVT_PTR(N(EVS_NpcDefeat_Lakitu)))
    EVT_ELSE
        EVT_CALL(SetNpcPos, NPC_SELF, NPC_DISPOSE_LOCATION)
    EVT_END_IF
    EVT_RETURN
    EVT_END
};

StaticNpc N(NpcData_MachineGang)[] = {
    {
        .id = NPC_Lakitu_01,
        .settings = &N(NpcSettings_Lakitu),
        .pos = { 0.0f, 15.0f, 60.0f },
        .yaw = 90,
        .flags = ENEMY_FLAGS_1 | ENEMY_FLAGS_4 | ENEMY_FLAGS_100 | ENEMY_FLAGS_400 | ENEMY_FLAGS_800 | ENEMY_FLAGS_40000 | ENEMY_FLAGS_400000,
        .init = &N(EVS_NpcInit_Lakitu_01),
        .drops = LAKITU_DROPS,
        .animations = LAKITU_ANIMS,
        .tattle = MSG_NpcTattle_PuffPuffOperator,
    },
    {
        .id = NPC_Lakitu_02,
        .settings = &N(NpcSettings_Lakitu),
        .pos = { 65.0f, 15.0f, 60.0f },
        .yaw = 270,
        .flags = ENEMY_FLAGS_1 | ENEMY_FLAGS_4 | ENEMY_FLAGS_100 | ENEMY_FLAGS_400 | ENEMY_FLAGS_800 | ENEMY_FLAGS_40000 | ENEMY_FLAGS_400000,
        .init = &N(EVS_NpcInit_Lakitu_02),
        .drops = LAKITU_DROPS,
        .animations = LAKITU_ANIMS,
        .tattle = MSG_NpcTattle_PuffPuffOperator,
    },
    {
        .id = NPC_Lakitu_03,
        .settings = &N(NpcSettings_Lakitu),
        .pos = { 135.0f, 15.0f, 35.0f },
        .yaw = 270,
        .flags = ENEMY_FLAGS_1 | ENEMY_FLAGS_4 | ENEMY_FLAGS_100 | ENEMY_FLAGS_400 | ENEMY_FLAGS_800 | ENEMY_FLAGS_40000 | ENEMY_FLAGS_400000,
        .init = &N(EVS_NpcInit_Lakitu_03),
        .drops = LAKITU_DROPS,
        .animations = LAKITU_ANIMS,
        .tattle = MSG_NpcTattle_PuffPuffOperator,
    },
    {
        .id = NPC_Magikoopa,
        .settings = &N(NpcSettings_Magikoopa),
        .pos = { -60.0f, 0.0f, 50.0f },
        .yaw = 90,
        .flags = ENEMY_FLAGS_1 | ENEMY_FLAGS_4 | ENEMY_FLAGS_100 | ENEMY_FLAGS_400 | ENEMY_FLAGS_800 | ENEMY_FLAGS_40000 | ENEMY_FLAGS_400000,
        .init = &N(EVS_NpcInit_Magikoopa),
        .drops = MAGIKOOPA_DROPS,
        .animations = MAGIKOOPA_YELLOW_ANIMS,
        .tattle = MSG_NpcTattle_PuffPuffOperator,
    },
    {
        .id = NPC_FlyingMagikoopa,
        .settings = &N(NpcSettings_Magikoopa),
        .pos = { NPC_DISPOSE_LOCATION },
        .yaw = 270,
        .flags = ENEMY_FLAGS_1 | ENEMY_FLAGS_4 | ENEMY_FLAGS_100 | ENEMY_FLAGS_400 | ENEMY_FLAGS_800 | ENEMY_FLAGS_40000 | ENEMY_FLAGS_400000,
        .init = &N(EVS_NpcInit_FlyingMagikoopa),
        .drops = MAGIKOOPA_DROPS,
        .animations = FLYING_MAGIKOOPA_YELLOW_ANIMS,
        .tattle = MSG_NpcTattle_PuffPuffOperator,
    },
};

NpcGroupList N(DefaultNPCs) = {
    NPC_GROUP(N(NpcData_MachineGang), 0x1A0B, BTL_FLO_STAGE_06),
    {}
};
