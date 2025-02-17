#include "common.h"
#include "script_api/battle.h"
#include "battle/action_cmd/jump.h"

#define NAMESPACE battle_move_auto_multibounce

extern EvtScript N(D_802A26A8);
extern EvtScript N(D_802A2EC0);
extern EvtScript N(D_802A372C);

s32 N(D_802A10F0)[] = {
    9, 3, 9, 3, 9, 3, 8, 3,
    7, 3, 6, 2, 5, 2, 4, 2,
};

#include "world/common/todo/UnkMoveFunc1.inc.c"

EvtScript N(CheckForAPress) = {
    EVT_CALL(SetAnimation, ACTOR_PLAYER, 0, ANIM_Mario_BeforeJump)
    EVT_LOOP(5)
        EVT_CALL(CheckButtonPress, BUTTON_A, LVar0)
        EVT_IF_EQ(LVar0, TRUE)
            EVT_BREAK_LOOP
        EVT_END_IF
        EVT_WAIT(1)
    EVT_END_LOOP
    EVT_RETURN
    EVT_END
};

EvtScript N(D_802A11AC) = {
    EVT_CALL(SetGoalToFirstTarget, ACTOR_SELF)
    EVT_CALL(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    EVT_SUB(LVar0, 40)
    EVT_CALL(InitTargetIterator)
    EVT_CALL(SetGoalToTarget, ACTOR_PLAYER)
    EVT_CALL(GetGoalPos, ACTOR_PLAYER, LVar3, LVar4, LVar5)
    EVT_SUB(LVar3, EVT_FLOAT(70.0))
    EVT_IF_LT(LVar0, LVar3)
        EVT_SET(LVar3, LVar0)
    EVT_END_IF
    EVT_CALL(SetGoalPos, ACTOR_PLAYER, LVar3, LVar4, LVar5)
    EVT_CALL(UseBattleCamPreset, BTL_CAM_PRESET_26)
    EVT_CALL(SetActorSpeed, ACTOR_PLAYER, EVT_FLOAT(5.0))
    EVT_CALL(SetAnimation, ACTOR_PLAYER, 0, ANIM_Mario_Running)
    EVT_CALL(CancelablePlayerRunToGoal, 0, LVar0)
    EVT_CALL(SetAnimation, ACTOR_PLAYER, 0, ANIM_Mario_10002)
    EVT_CALL(SetGoalToTarget, ACTOR_PLAYER)
    EVT_EXEC_WAIT(N(CheckForAPress))
    EVT_CALL(SetAnimation, ACTOR_PLAYER, 0, ANIM_Mario_BeforeJump)
    EVT_RETURN
    EVT_END
};

EvtScript N(D_802A1320) = {
    EVT_CALL(SetGoalToTarget, ACTOR_PLAYER)
    EVT_CALL(GetGoalPos, ACTOR_PLAYER, LVar6, LVar7, LVar8)
    EVT_CALL(GetActorPos, ACTOR_PLAYER, LVar7, LVar8, LVar9)
    EVT_IF_GT(LVar6, LVar7)
        EVT_SUB(LVar6, LVar7)
    EVT_ELSE
        EVT_SUB(LVar7, LVar6)
        EVT_SET(LVar6, LVar7)
    EVT_END_IF
    EVT_SUB(LVar6, 20)
    EVT_DIVF(LVar6, EVT_FLOAT(10.5888671875))
    EVT_ADDF(LVar6, 15)
    EVT_SET(LVarA, LVar6)
    EVT_RETURN
    EVT_END
};

EvtScript N(D_802A1408) = {
    EVT_CALL(SetGoalToTarget, ACTOR_PLAYER)
    EVT_CALL(GetGoalPos, ACTOR_PLAYER, LVar6, LVar7, LVar8)
    EVT_CALL(GetActorPos, ACTOR_PLAYER, LVar7, LVar8, LVar9)
    EVT_IF_GT(LVar6, LVar7)
        EVT_SUB(LVar6, LVar7)
    EVT_ELSE
        EVT_SUB(LVar7, LVar6)
        EVT_SET(LVar6, LVar7)
    EVT_END_IF
    EVT_SUB(LVar6, 20)
    EVT_DIVF(LVar6, EVT_FLOAT(22.5))
    EVT_ADDF(LVar6, 15)
    EVT_SET(LVarA, LVar6)
    EVT_RETURN
    EVT_END
};

EvtScript N(D_802A14F0) = {
    EVT_CALL(SetGoalToTarget, ACTOR_PLAYER)
    EVT_CALL(GetGoalPos, ACTOR_PLAYER, LVar6, LVar7, LVar8)
    EVT_CALL(GetActorPos, ACTOR_PLAYER, LVar7, LVar8, LVar9)
    EVT_IF_GT(LVar6, LVar7)
        EVT_SUB(LVar6, LVar7)
    EVT_ELSE
        EVT_SUB(LVar7, LVar6)
        EVT_SET(LVar6, LVar7)
    EVT_END_IF
    EVT_SUB(LVar6, 20)
    EVT_DIVF(LVar6, EVT_FLOAT(18.0))
    EVT_ADDF(LVar6, 22)
    EVT_SET(LVarA, LVar6)
    EVT_RETURN
    EVT_END
};

EvtScript N(D_802A15D8) = {
    EVT_CALL(func_80276EFC)
    EVT_CALL(SetBattleFlagBits, BS_FLAGS1_100, 0)
    EVT_CALL(UseBattleCamPreset, BTL_CAM_PRESET_D)
    EVT_CALL(func_802693F0)
    EVT_CALL(SetGoalToHome, ACTOR_PLAYER)
    EVT_CALL(GetGoalPos, ACTOR_PLAYER, LVar0, LVar1, LVar2)
    EVT_ADD(LVar0, 40)
    EVT_CALL(SetJumpAnimations, ACTOR_PLAYER, 0, ANIM_Mario_AnimMidairStill, ANIM_Mario_AnimMidair, ANIM_Mario_10009)
    EVT_CALL(SetActorJumpGravity, ACTOR_PLAYER, EVT_FLOAT(1.3))
    EVT_CALL(SetGoalPos, ACTOR_PLAYER, LVar0, LVar1, LVar2)
    EVT_CALL(N(UnkMoveFunc1))
    EVT_CALL(func_80273444, LVar0, 0, 0)
    EVT_CALL(SetAnimation, ACTOR_PLAYER, 0, ANIM_Mario_10009)
    EVT_WAIT(1)
    EVT_CALL(AddGoalPos, ACTOR_PLAYER, -20, 0, 0)
    EVT_CALL(func_80273444, 6, 0, 2)
    EVT_CALL(SetAnimation, ACTOR_PLAYER, 0, ANIM_Mario_10009)
    EVT_WAIT(5)
    EVT_CALL(EnablePlayerBlur, -1)
    EVT_CALL(SetGoalToHome, ACTOR_PLAYER)
    EVT_CALL(SetActorSpeed, ACTOR_PLAYER, EVT_FLOAT(8.0))
    EVT_CALL(SetAnimation, ACTOR_PLAYER, 0, ANIM_Mario_Running)
    EVT_CALL(PlayerRunToGoal, 0)
    EVT_CALL(SetAnimation, ACTOR_PLAYER, 0, ANIM_Mario_10002)
    EVT_RETURN
    EVT_END
};

EvtScript N(D_802A17C4) = {
    EVT_CALL(func_80276EFC)
    EVT_CALL(SetBattleFlagBits, BS_FLAGS1_100, 0)
    EVT_CALL(UseBattleCamPreset, BTL_CAM_PRESET_D)
    EVT_CALL(func_802693F0)
    EVT_CALL(GetActorPos, ACTOR_PLAYER, LVar0, LVar1, LVar2)
    EVT_SUB(LVar0, 50)
    EVT_SET(LVar1, 0)
    EVT_CALL(SetGoalPos, ACTOR_PLAYER, LVar0, LVar1, LVar2)
    EVT_CALL(SetJumpAnimations, ACTOR_PLAYER, 0, ANIM_Mario_AnimMidairStill, ANIM_Mario_AnimMidair, ANIM_Mario_10009)
    EVT_CALL(SetActorJumpGravity, ACTOR_PLAYER, EVT_FLOAT(0.8))
    EVT_CALL(N(UnkMoveFunc1))
    EVT_CALL(func_80273444, LVar0, 0, 0)
    EVT_CALL(SetAnimation, ACTOR_PLAYER, 0, ANIM_Mario_10009)
    EVT_WAIT(1)
    EVT_CALL(AddGoalPos, ACTOR_PLAYER, -30, 0, 0)
    EVT_CALL(func_80273444, 6, 0, 2)
    EVT_CALL(SetAnimation, ACTOR_PLAYER, 0, ANIM_Mario_10009)
    EVT_WAIT(2)
    EVT_CALL(EnablePlayerBlur, -1)
    EVT_CALL(SetGoalToHome, ACTOR_PLAYER)
    EVT_CALL(SetActorSpeed, ACTOR_PLAYER, EVT_FLOAT(8.0))
    EVT_CALL(SetAnimation, ACTOR_PLAYER, 0, ANIM_Mario_Running)
    EVT_CALL(PlayerRunToGoal, 0)
    EVT_CALL(SetAnimation, ACTOR_PLAYER, 0, ANIM_Mario_10002)
    EVT_RETURN
    EVT_END
};

EvtScript N(D_802A19B0) = {
    EVT_CALL(func_80276EFC)
    EVT_CALL(SetBattleFlagBits, BS_FLAGS1_100, 0)
    EVT_CALL(UseBattleCamPreset, BTL_CAM_PRESET_29)
    EVT_CALL(func_802693F0)
    EVT_CALL(GetActorPos, ACTOR_PLAYER, LVar0, LVar1, LVar2)
    EVT_SUB(LVar0, 40)
    EVT_SET(LVar1, 0)
    EVT_CALL(SetGoalPos, ACTOR_PLAYER, LVar0, LVar1, LVar2)
    EVT_CALL(SetJumpAnimations, ACTOR_PLAYER, 0, ANIM_Mario_AnimMidairStill, ANIM_Mario_AnimMidair, ANIM_Mario_10009)
    EVT_CALL(SetActorJumpGravity, ACTOR_PLAYER, EVT_FLOAT(1.0))
    EVT_CALL(N(UnkMoveFunc1))
    EVT_CALL(func_80273444, LVar0, 0, 0)
    EVT_CALL(SetAnimation, ACTOR_PLAYER, 0, ANIM_Mario_10009)
    EVT_WAIT(1)
    EVT_CALL(AddGoalPos, ACTOR_PLAYER, -20, 0, 0)
    EVT_CALL(func_80273444, 6, 0, 2)
    EVT_CALL(SetAnimation, ACTOR_PLAYER, 0, ANIM_Mario_10009)
    EVT_WAIT(2)
    EVT_CALL(EnablePlayerBlur, -1)
    EVT_CALL(SetGoalToHome, ACTOR_PLAYER)
    EVT_CALL(SetActorSpeed, ACTOR_PLAYER, EVT_FLOAT(8.0))
    EVT_CALL(SetAnimation, ACTOR_PLAYER, 0, ANIM_Mario_Running)
    EVT_CALL(PlayerRunToGoal, 0)
    EVT_CALL(SetAnimation, ACTOR_PLAYER, 0, ANIM_Mario_10002)
    EVT_RETURN
    EVT_END
};

EvtScript N(D_802A1B9C) = {
    EVT_CALL(func_80276EFC)
    EVT_CALL(SetBattleFlagBits, BS_FLAGS1_100, 0)
    EVT_CALL(UseBattleCamPreset, BTL_CAM_PRESET_D)
    EVT_CALL(func_802693F0)
    EVT_CALL(GetActorPos, ACTOR_PLAYER, LVar0, LVar1, LVar2)
    EVT_SUB(LVar0, 60)
    EVT_SET(LVar1, 0)
    EVT_CALL(SetGoalPos, ACTOR_PLAYER, LVar0, LVar1, LVar2)
    EVT_CALL(SetJumpAnimations, ACTOR_PLAYER, 0, ANIM_Mario_AnimMidairStill, ANIM_Mario_AnimMidair, ANIM_Mario_10009)
    EVT_CALL(SetActorJumpGravity, ACTOR_PLAYER, EVT_FLOAT(0.8))
    EVT_CALL(N(UnkMoveFunc1))
    EVT_CALL(func_80273444, LVar0, 0, 0)
    EVT_CALL(SetAnimation, ACTOR_PLAYER, 0, ANIM_Mario_10009)
    EVT_WAIT(1)
    EVT_CALL(AddGoalPos, ACTOR_PLAYER, -20, 0, 0)
    EVT_CALL(func_80273444, 6, 0, 2)
    EVT_CALL(SetAnimation, ACTOR_PLAYER, 0, ANIM_Mario_10009)
    EVT_WAIT(2)
    EVT_CALL(EnablePlayerBlur, -1)
    EVT_CALL(SetGoalToHome, ACTOR_PLAYER)
    EVT_CALL(SetActorSpeed, ACTOR_PLAYER, EVT_FLOAT(8.0))
    EVT_CALL(SetAnimation, ACTOR_PLAYER, 0, ANIM_Mario_Running)
    EVT_CALL(PlayerRunToGoal, 0)
    EVT_CALL(SetAnimation, ACTOR_PLAYER, 0, ANIM_Mario_10002)
    EVT_RETURN
    EVT_END
};

EvtScript N(D_802A1D88) = {
    EVT_CALL(func_80276EFC)
    EVT_CALL(SetBattleFlagBits, BS_FLAGS1_100, 0)
    EVT_CALL(EnablePlayerBlur, -1)
    EVT_CALL(UseBattleCamPreset, BTL_CAM_PRESET_D)
    EVT_CALL(func_802693F0)
    EVT_CALL(SetGoalToHome, ACTOR_PLAYER)
    EVT_CALL(GetGoalPos, ACTOR_PLAYER, LVar0, LVar1, LVar2)
    EVT_ADD(LVar0, 60)
    EVT_SET(LVar1, 0)
    EVT_CALL(SetGoalPos, ACTOR_PLAYER, LVar0, LVar1, LVar2)
    EVT_CALL(SetActorJumpGravity, ACTOR_PLAYER, EVT_FLOAT(1.0))
    EVT_CALL(SetJumpAnimations, ACTOR_PLAYER, 0, ANIM_Mario_FallBack, ANIM_Mario_FallBack, ANIM_Mario_10009)
    EVT_CALL(N(UnkMoveFunc1))
    EVT_CALL(func_80273444, LVar0, 0, 0)
    EVT_CHILD_THREAD
        EVT_CALL(ShakeCam, 1, 0, 4, EVT_FLOAT(1.0))
    EVT_END_CHILD_THREAD
    EVT_CALL(AddGoalPos, ACTOR_PLAYER, -30, 0, 0)
    EVT_CALL(func_80273444, 8, 0, 2)
    EVT_CHILD_THREAD
        EVT_CALL(ShakeCam, 1, 0, 4, EVT_FLOAT(1.0))
    EVT_END_CHILD_THREAD
    EVT_CALL(AddGoalPos, ACTOR_PLAYER, -20, 0, 0)
    EVT_CALL(SetGoalPos, ACTOR_PLAYER, LVar0, LVar1, LVar2)
    EVT_CALL(func_80273444, 6, 0, 2)
    EVT_CHILD_THREAD
        EVT_CALL(ShakeCam, 1, 0, 4, EVT_FLOAT(1.0))
    EVT_END_CHILD_THREAD
    EVT_CALL(SetGoalToHome, ACTOR_PLAYER)
    EVT_CALL(func_80273444, 4, 0, 2)
    EVT_CALL(SetAnimation, ACTOR_PLAYER, 0, ANIM_Mario_10002)
    EVT_RETURN
    EVT_END
};

EvtScript N(D_802A1FEC) = {
    EVT_CALL(SetJumpAnimations, ACTOR_PLAYER, 0, 0, 0, ANIM_Mario_1000C)
    EVT_CALL(PlayerLandJump)
    EVT_CALL(SetAnimation, ACTOR_PLAYER, 0, ANIM_Mario_1000C)
    EVT_WAIT(2)
    EVT_CHILD_THREAD
        EVT_CALL(ShakeCam, 1, 0, 5, EVT_FLOAT(1.0))
    EVT_END_CHILD_THREAD
    EVT_CALL(PlaySoundAtActor, ACTOR_PLAYER, SOUND_162)
    EVT_CALL(SetAnimation, ACTOR_PLAYER, 0, ANIM_Mario_GetUp)
    EVT_WAIT(10)
    EVT_CALL(SetAnimation, ACTOR_PLAYER, 0, ANIM_Mario_DustOff)
    EVT_WAIT(20)
    EVT_CALL(SetBattleFlagBits, BS_FLAGS1_100, 0)
    EVT_CALL(UseBattleCamPreset, BTL_CAM_PRESET_D)
    EVT_CALL(func_802693F0)
    EVT_CALL(EnablePlayerBlur, -1)
    EVT_CALL(func_80276EFC)
    EVT_CALL(SetGoalToHome, ACTOR_PLAYER)
    EVT_CALL(SetActorSpeed, ACTOR_PLAYER, EVT_FLOAT(8.0))
    EVT_CALL(SetAnimation, ACTOR_PLAYER, 0, ANIM_Mario_Running)
    EVT_CALL(PlayerRunToGoal, 0)
    EVT_CALL(SetAnimation, ACTOR_PLAYER, 0, ANIM_Mario_10002)
    EVT_RETURN
    EVT_END
};

EvtScript N(D_802A2184) = {
    EVT_CALL(LoadActionCommand, ACTION_COMMAND_JUMP)
    EVT_CALL(action_command_jump_init)
    EVT_EXEC_WAIT(N(D_802A11AC))
    EVT_EXEC_WAIT(N(D_802A1320))
    EVT_CALL(action_command_jump_start, LVarA, 3)
    EVT_CALL(UseBattleCamPreset, BTL_CAM_PRESET_34)
    EVT_CALL(SetGoalToTarget, ACTOR_PLAYER)
    EVT_CALL(SetJumpAnimations, ACTOR_PLAYER, 0, ANIM_Mario_AnimMidairStill, ANIM_Mario_AnimMidair, ANIM_Mario_30000 )
    EVT_CALL(func_80274A18, LVarA, 0)
    EVT_RETURN
    EVT_END
};

EvtScript N(D_802A2230) = {
    EVT_CALL(LoadActionCommand, ACTION_COMMAND_JUMP)
    EVT_CALL(action_command_jump_init)
    EVT_EXEC_WAIT(N(D_802A11AC))
    EVT_CALL(InitTargetIterator)
    EVT_EXEC_WAIT(N(D_802A1408))
    EVT_SET(LVarB, LVarA)
    EVT_ADD(LVarB, 14)
    EVT_ADD(LVarB, -3)
    EVT_CALL(action_command_jump_start, LVarB, 3)
    EVT_CALL(UseBattleCamPreset, BTL_CAM_PRESET_37)
    EVT_CALL(SetGoalToTarget, ACTOR_PLAYER)
    EVT_CALL(SetJumpAnimations, ACTOR_PLAYER, 0, ANIM_Mario_AnimMidairStill, ANIM_Mario_1000A, ANIM_Mario_1000B)
    EVT_CALL(func_802752AC, LVarA, 0)
    EVT_WAIT(7)
    EVT_CALL(DidActionSucceed, LVar0)
    EVT_SWITCH(LVar0)
        EVT_CASE_GT(0)
            EVT_CALL(func_802752AC, 3, 1)
        EVT_CASE_DEFAULT
            EVT_CALL(func_802752AC, 5, 1)
    EVT_END_SWITCH
    EVT_RETURN
    EVT_END
};

EvtScript N(D_802A2384) = {
    EVT_CALL(LoadActionCommand, ACTION_COMMAND_JUMP)
    EVT_CALL(action_command_jump_init)
    EVT_EXEC_WAIT(N(D_802A11AC))
    EVT_EXEC_WAIT(N(D_802A14F0))
    EVT_CALL(SetActionDifficultyTable, EVT_PTR(N(D_802A10F0)))
    EVT_SET(LVarB, LVarA)
    EVT_SUB(LVarB, 4)
    EVT_ADD(LVarB, -3)
    EVT_CALL(action_command_jump_start, LVarB, 3)
    EVT_CALL(UseBattleCamPreset, BTL_CAM_PRESET_38)
    EVT_CALL(SetGoalToTarget, ACTOR_PLAYER)
    EVT_CALL(SetJumpAnimations, ACTOR_PLAYER, 0, ANIM_Mario_AnimMidairStill, 524288, 196608)
    EVT_CALL(func_80275F00, LVarA, 0)
    EVT_CALL(CloseActionCommandInfo)
    EVT_SET(LVar9, 0)
    EVT_CALL(DidActionSucceed, LVar0)
    EVT_IF_GT(LVar0, 0)
        EVT_SET(LVar9, 1)
        EVT_CALL(SetAnimation, ACTOR_PLAYER, 0, 0x030000)
        EVT_CALL(SetActorRotation, ACTOR_SELF, 0, 0, 0)
        EVT_CALL(SetActorDispOffset, ACTOR_SELF, 0, -2, 0)
        EVT_WAIT(2)
        EVT_CALL(SetActorDispOffset, ACTOR_SELF, 0, 0, 0)
        EVT_CALL(LoadActionCommand, ACTION_COMMAND_JUMP)
        EVT_CALL(action_command_jump_init)
        EVT_CALL(action_command_jump_start, 13, 3)
        EVT_CALL(UseBattleCamPreset, BTL_CAM_PRESET_39)
        EVT_CALL(func_80275F00, 15, 2)
        EVT_GOTO(10)
    EVT_ELSE
        EVT_CALL(LoadActionCommand, ACTION_COMMAND_JUMP)
        EVT_CALL(action_command_jump_init)
        EVT_CALL(action_command_jump_start, 2, 3)
        EVT_CALL(func_80275F00, 4, 1)
        EVT_GOTO(10)
    EVT_END_IF
    EVT_LABEL(10)
    EVT_RETURN
    EVT_END
};

EvtScript N(main) = {
    EVT_CALL(ShowActionHud, 1)
    EVT_CALL(SetBattleFlagBits, BS_FLAGS1_AUTO_SUCCEED_ACTION, 1)
    EVT_CALL(GetMenuSelection, LVar0, LVar1, LVar2)
    EVT_SWITCH(LVar1)
        EVT_CASE_EQ(0)
            EVT_EXEC_WAIT(N(D_802A26A8))
        EVT_CASE_EQ(1)
            EVT_EXEC_WAIT(N(D_802A2EC0))
        EVT_CASE_EQ(2)
            EVT_EXEC_WAIT(N(D_802A372C))
    EVT_END_SWITCH
    EVT_RETURN
    EVT_END
};

EvtScript N(D_802A26A8) = {
    EVT_EXEC_WAIT(N(D_802A2184))
    EVT_CALL(PlayerTestEnemy, LVar0, 128, 0, 0, 1, 0)
    EVT_IF_EQ(LVar0, 6)
        EVT_EXEC_WAIT(N(D_802A1FEC))
        EVT_RETURN
    EVT_END_IF
    EVT_SET(LocalFlag(0), 0)
    EVT_CALL(GetTargetListLength, LVar0)
    EVT_IF_EQ(LVar0, 1)
        EVT_SET(LocalFlag(0), 1)
    EVT_END_IF
    EVT_WAIT(1)
    EVT_CALL(DidActionSucceed, LVar0)
    EVT_SWITCH(LVar0)
        EVT_CASE_GT(0)
            EVT_IF_EQ(LocalFlag(0), 0)
                EVT_CALL(SetActorSounds, ACTOR_PLAYER, 3, 346, 0)
                EVT_CALL(PlayerDamageEnemy, LVar0, 553648256, 0, 0, 1, BS_FLAGS1_40 | BS_FLAGS1_SP_EVT_ACTIVE | BS_FLAGS1_10)
            EVT_ELSE
                EVT_CALL(SetActorSounds, ACTOR_PLAYER, 3, 346, 0)
                EVT_CALL(PlayerDamageEnemy, LVar0, 553648256, 0, 0, 1, BS_FLAGS1_40 | BS_FLAGS1_SP_EVT_ACTIVE | BS_FLAGS1_10)
            EVT_END_IF
        EVT_CASE_DEFAULT
            EVT_CALL(SetActorSounds, ACTOR_PLAYER, 3, 346, 0)
            EVT_CALL(PlayerDamageEnemy, LVar0, 553648256, 0, 0, 1, BS_FLAGS1_SP_EVT_ACTIVE | BS_FLAGS1_10)
    EVT_END_SWITCH
    EVT_CALL(PlaySoundAtActor, ACTOR_PLAYER, 0x235)
    EVT_SWITCH(LVar0)
        EVT_CASE_OR_EQ(0)
        EVT_CASE_OR_EQ(2)
            EVT_IF_EQ(LocalFlag(0), 1)
                EVT_EXEC_WAIT(N(D_802A15D8))
                EVT_RETURN
            EVT_END_IF
            EVT_EXEC_WAIT(N(D_802A19B0))
            EVT_RETURN
        EVT_END_CASE_GROUP
        EVT_CASE_OR_EQ(1)
        EVT_CASE_OR_EQ(3)
            EVT_IF_EQ(LocalFlag(0), 1)
                EVT_EXEC_WAIT(N(D_802A15D8))
                EVT_RETURN
            EVT_END_IF
        EVT_END_CASE_GROUP
    EVT_END_SWITCH
    EVT_CALL(func_80269524, LVarE)
    EVT_ADD(LVarF, 1)
    EVT_SET(LocalFlag(0), 0)
    EVT_LABEL(10)
    EVT_CALL(UseBattleCamPreset, BTL_CAM_PRESET_40)
    EVT_CALL(GetTargetListLength, LVar0)
    EVT_SUB(LVar0, 1)
    EVT_IF_EQ(LVarF, LVar0)
        EVT_SET(LocalFlag(0), 1)
    EVT_END_IF
    EVT_CALL(CloseActionCommandInfo)
    EVT_CALL(LoadActionCommand, ACTION_COMMAND_JUMP)
    EVT_CALL(action_command_jump_init)
    EVT_IF_EQ(LocalFlag(0), 1)
        EVT_CALL(ShowActionHud, 0)
    EVT_END_IF
    EVT_CALL(ChooseNextTarget, 0, LVar0)
    EVT_CALL(SetGoalToTarget, ACTOR_PLAYER)
    EVT_EXEC_WAIT(N(D_802A1320))
    EVT_ADD(LVarA, 5)
    EVT_CALL(action_command_jump_start, LVarA, 3)
    EVT_CALL(SetGoalToTarget, ACTOR_PLAYER)
    EVT_CALL(SetJumpAnimations, ACTOR_PLAYER, 0, ANIM_Mario_AnimMidairStill, ANIM_Mario_AnimMidair, ANIM_Mario_1000C)
    EVT_IF_EQ(LVarF, 1)
        EVT_CALL(func_80274A18, LVarA, 3)
    EVT_ELSE
        EVT_CALL(func_80274A18, LVarA, 4)
    EVT_END_IF
    EVT_CALL(PlayerTestEnemy, LVar0, 128, 0, 0, 1, 0)
    EVT_IF_EQ(LVar0, 6)
        EVT_EXEC_WAIT(N(D_802A1FEC))
        EVT_RETURN
    EVT_END_IF
    EVT_WAIT(1)
    EVT_CALL(DidActionSucceed, LVar0)
    EVT_SWITCH(LVar0)
        EVT_CASE_GT(0)
            EVT_IF_EQ(LocalFlag(0), 0)
                EVT_CALL(SetActorSounds, ACTOR_PLAYER, 3, 346, 0)
                EVT_CALL(PlayerDamageEnemy, LVar0, 553648256, 0, 0, 1, BS_FLAGS1_40 | BS_FLAGS1_SP_EVT_ACTIVE | BS_FLAGS1_10)
            EVT_ELSE
                EVT_CALL(SetActorSounds, ACTOR_PLAYER, 3, 346, 0)
                EVT_CALL(PlayerDamageEnemy, LVar0, 553648256, 0, 0, 1, BS_FLAGS1_80 | BS_FLAGS1_40 | BS_FLAGS1_SP_EVT_ACTIVE | BS_FLAGS1_10)
            EVT_END_IF
        EVT_CASE_DEFAULT
            EVT_IF_EQ(LocalFlag(0), 0)
                EVT_CALL(SetActorSounds, ACTOR_PLAYER, 3, 346, 0)
                EVT_CALL(PlayerDamageEnemy, LVar0, 553648256, 0, 0, 1, BS_FLAGS1_SP_EVT_ACTIVE | BS_FLAGS1_10)
            EVT_ELSE
                EVT_CALL(SetActorSounds, ACTOR_PLAYER, 3, 346, 0)
                EVT_CALL(PlayerDamageEnemy, LVar0, 553648256, 0, 0, 1, BS_FLAGS1_80 | BS_FLAGS1_40 | BS_FLAGS1_SP_EVT_ACTIVE | BS_FLAGS1_10)
            EVT_END_IF
    EVT_END_SWITCH
    EVT_SWITCH(LVarF)
        EVT_CASE_EQ(0)
            EVT_CALL(PlaySoundAtActor, ACTOR_PLAYER, 0x235)
        EVT_CASE_EQ(1)
            EVT_CALL(PlaySoundAtActor, ACTOR_PLAYER, 0x236)
        EVT_CASE_EQ(2)
            EVT_CALL(PlaySoundAtActor, ACTOR_PLAYER, 0x237)
        EVT_CASE_EQ(3)
            EVT_CALL(PlaySoundAtActor, ACTOR_PLAYER, 0x238)
        EVT_CASE_DEFAULT
            EVT_CALL(PlaySoundAtActor, ACTOR_PLAYER, 0x238)
    EVT_END_SWITCH
    EVT_CALL(func_80269550, LVarE)
    EVT_CALL(DidActionSucceed, LVar0)
    EVT_SWITCH(LVar0)
        EVT_CASE_OR_EQ(0)
        EVT_CASE_OR_EQ(2)
            EVT_IF_EQ(LocalFlag(0), 1)
                EVT_EXEC_WAIT(N(D_802A15D8))
                EVT_RETURN
            EVT_END_IF
            EVT_EXEC_WAIT(N(D_802A19B0))
            EVT_RETURN
        EVT_END_CASE_GROUP
        EVT_CASE_OR_EQ(1)
        EVT_CASE_OR_EQ(3)
            EVT_IF_EQ(LocalFlag(0), 1)
                EVT_EXEC_WAIT(N(D_802A15D8))
                EVT_RETURN
            EVT_END_IF
        EVT_END_CASE_GROUP
    EVT_END_SWITCH
    EVT_ADD(LVarF, 1)
    EVT_CALL(GetTargetListLength, LVar0)
    EVT_IF_GE(LVarF, LVar0)
        EVT_EXEC_WAIT(N(D_802A17C4))
        EVT_RETURN
    EVT_END_IF
    EVT_GOTO(10)
    EVT_RETURN
    EVT_END
};

EvtScript N(D_802A2EC0) = {
    EVT_EXEC_WAIT(N(D_802A2184))
    EVT_CALL(PlayerTestEnemy, LVar0, 128, 0, 0, 1, 0)
    EVT_IF_EQ(LVar0, 6)
        EVT_EXEC_WAIT(N(D_802A1FEC))
        EVT_RETURN
    EVT_END_IF
    EVT_SET(LocalFlag(0), 0)
    EVT_CALL(GetTargetListLength, LVar0)
    EVT_IF_EQ(LVar0, 1)
        EVT_SET(LocalFlag(0), 1)
    EVT_END_IF
    EVT_WAIT(1)
    EVT_CALL(DidActionSucceed, LVar0)
    EVT_SWITCH(LVar0)
        EVT_CASE_GT(0)
            EVT_IF_EQ(LocalFlag(0), 0)
                EVT_CALL(SetActorSounds, ACTOR_PLAYER, 3, 347, 0)
                EVT_CALL(PlayerDamageEnemy, LVar0, 553648256, 0, 0, 2, BS_FLAGS1_40 | BS_FLAGS1_SP_EVT_ACTIVE | BS_FLAGS1_10)
            EVT_ELSE
                EVT_CALL(SetActorSounds, ACTOR_PLAYER, 3, 347, 0)
                EVT_CALL(PlayerDamageEnemy, LVar0, 553648256, 0, 0, 2, BS_FLAGS1_40 | BS_FLAGS1_SP_EVT_ACTIVE | BS_FLAGS1_10)
            EVT_END_IF
        EVT_CASE_DEFAULT
            EVT_CALL(SetActorSounds, ACTOR_PLAYER, 3, 347, 0)
            EVT_CALL(PlayerDamageEnemy, LVar0, 553648256, 0, 0, 2, BS_FLAGS1_SP_EVT_ACTIVE | BS_FLAGS1_10)
    EVT_END_SWITCH
    EVT_CALL(PlaySoundAtActor, ACTOR_PLAYER, 0x235)
    EVT_SWITCH(LVar0)
        EVT_CASE_OR_EQ(0)
        EVT_CASE_OR_EQ(2)
            EVT_IF_EQ(LocalFlag(0), 1)
                EVT_EXEC_WAIT(N(D_802A15D8))
                EVT_RETURN
            EVT_END_IF
            EVT_EXEC_WAIT(N(D_802A19B0))
            EVT_RETURN
        EVT_END_CASE_GROUP
        EVT_CASE_OR_EQ(1)
        EVT_CASE_OR_EQ(3)
            EVT_IF_EQ(LocalFlag(0), 1)
                EVT_EXEC_WAIT(N(D_802A15D8))
                EVT_RETURN
            EVT_END_IF
        EVT_END_CASE_GROUP
    EVT_END_SWITCH
    EVT_CALL(func_80269524, LVarE)
    EVT_SET(LocalFlag(0), 0)
    EVT_SET(LVarF, 0)
    EVT_ADD(LVarF, 1)
    EVT_LABEL(10)
    EVT_CALL(GetTargetListLength, LVar0)
    EVT_SUB(LVar0, 1)
    EVT_IF_EQ(LVarF, LVar0)
        EVT_SET(LocalFlag(0), 1)
    EVT_END_IF
    EVT_CALL(CloseActionCommandInfo)
    EVT_CALL(LoadActionCommand, ACTION_COMMAND_JUMP)
    EVT_CALL(action_command_jump_init)
    EVT_IF_EQ(LocalFlag(0), 1)
        EVT_CALL(ShowActionHud, 0)
    EVT_END_IF
    EVT_CALL(UseBattleCamPreset, BTL_CAM_PRESET_40)
    EVT_CALL(action_command_jump_start, 37, 3)
    EVT_CALL(ChooseNextTarget, 0, LVar0)
    EVT_CALL(SetGoalToTarget, ACTOR_PLAYER)
    EVT_CALL(SetGoalToTarget, ACTOR_PLAYER)
    EVT_CALL(SetJumpAnimations, ACTOR_PLAYER, 0, ANIM_Mario_AnimMidairStill, ANIM_Mario_1000A, ANIM_Mario_1000B)
    EVT_CALL(EnablePlayerBlur, 1)
    EVT_IF_EQ(LVarF, 1)
        EVT_CALL(func_802752AC, 20, 3)
        EVT_WAIT(7)
        EVT_CALL(func_802752AC, 3, 6)
    EVT_ELSE
        EVT_CALL(func_802752AC, 20, 4)
        EVT_WAIT(7)
        EVT_CALL(func_802752AC, 3, 5)
    EVT_END_IF
    EVT_CALL(EnablePlayerBlur, 0)
    EVT_CALL(PlayerTestEnemy, LVar0, 128, 0, 0, 1, 0)
    EVT_IF_EQ(LVar0, 6)
        EVT_EXEC_WAIT(N(D_802A1FEC))
        EVT_RETURN
    EVT_END_IF
    EVT_WAIT(1)
    EVT_CALL(DidActionSucceed, LVar0)
    EVT_SWITCH(LVar0)
        EVT_CASE_GT(0)
            EVT_IF_EQ(LocalFlag(0), 0)
                EVT_CALL(SetActorSounds, ACTOR_PLAYER, 3, 347, 0)
                EVT_CALL(PlayerDamageEnemy, LVar0, 553648256, 0, 0, 2, BS_FLAGS1_40 | BS_FLAGS1_SP_EVT_ACTIVE | BS_FLAGS1_10)
            EVT_ELSE
                EVT_CALL(SetActorSounds, ACTOR_PLAYER, 3, 347, 0)
                EVT_CALL(PlayerDamageEnemy, LVar0, 553648256, 0, 0, 2, BS_FLAGS1_80 | BS_FLAGS1_40 | BS_FLAGS1_SP_EVT_ACTIVE | BS_FLAGS1_10)
            EVT_END_IF
        EVT_CASE_DEFAULT
            EVT_IF_EQ(LocalFlag(0), 0)
                EVT_CALL(SetActorSounds, ACTOR_PLAYER, 3, 347, 0)
                EVT_CALL(PlayerDamageEnemy, LVar0, 553648256, 0, 0, 2, BS_FLAGS1_SP_EVT_ACTIVE | BS_FLAGS1_10)
            EVT_ELSE
                EVT_CALL(SetActorSounds, ACTOR_PLAYER, 3, 347, 0)
                EVT_CALL(PlayerDamageEnemy, LVar0, 553648256, 0, 0, 2, BS_FLAGS1_80 | BS_FLAGS1_40 | BS_FLAGS1_SP_EVT_ACTIVE | BS_FLAGS1_10)
            EVT_END_IF
    EVT_END_SWITCH
    EVT_SWITCH(LVarF)
        EVT_CASE_EQ(0)
            EVT_CALL(PlaySoundAtActor, ACTOR_PLAYER, 0x235)
        EVT_CASE_EQ(1)
            EVT_CALL(PlaySoundAtActor, ACTOR_PLAYER, 0x236)
        EVT_CASE_EQ(2)
            EVT_CALL(PlaySoundAtActor, ACTOR_PLAYER, 0x237)
        EVT_CASE_EQ(3)
            EVT_CALL(PlaySoundAtActor, ACTOR_PLAYER, 0x238)
        EVT_CASE_DEFAULT
            EVT_CALL(PlaySoundAtActor, ACTOR_PLAYER, 0x238)
    EVT_END_SWITCH
    EVT_CALL(func_80269550, LVarE)
    EVT_CALL(DidActionSucceed, LVar0)
    EVT_SWITCH(LVar0)
        EVT_CASE_OR_EQ(0)
        EVT_CASE_OR_EQ(2)
            EVT_IF_EQ(LocalFlag(0), 1)
                EVT_EXEC_WAIT(N(D_802A15D8))
                EVT_RETURN
            EVT_END_IF
            EVT_EXEC_WAIT(N(D_802A19B0))
            EVT_RETURN
        EVT_END_CASE_GROUP
        EVT_CASE_OR_EQ(1)
        EVT_CASE_OR_EQ(3)
            EVT_IF_EQ(LocalFlag(0), 1)
                EVT_EXEC_WAIT(N(D_802A15D8))
                EVT_RETURN
            EVT_END_IF
        EVT_END_CASE_GROUP
    EVT_END_SWITCH
    EVT_ADD(LVarF, 1)
    EVT_CALL(GetTargetListLength, LVar0)
    EVT_IF_GE(LVarF, LVar0)
        EVT_EXEC_WAIT(N(D_802A19B0))
        EVT_RETURN
    EVT_END_IF
    EVT_GOTO(10)
    EVT_RETURN
    EVT_END
};

EvtScript N(D_802A372C) = {
    EVT_EXEC_WAIT(N(D_802A2184))
    EVT_CALL(PlayerTestEnemy, LVar0, 128, 0, 0, 1, 0)
    EVT_IF_EQ(LVar0, 6)
        EVT_EXEC_WAIT(N(D_802A1FEC))
        EVT_RETURN
    EVT_END_IF
    EVT_SET(LocalFlag(0), 0)
    EVT_CALL(GetTargetListLength, LVar0)
    EVT_IF_EQ(LVar0, 1)
        EVT_SET(LocalFlag(0), 1)
    EVT_END_IF
    EVT_WAIT(1)
    EVT_CALL(DidActionSucceed, LVar0)
    EVT_SWITCH(LVar0)
        EVT_CASE_GT(0)
            EVT_IF_EQ(LocalFlag(0), 0)
                EVT_CALL(SetActorSounds, ACTOR_PLAYER, 3, 348, 0)
                EVT_CALL(PlayerDamageEnemy, LVar0, 553648256, 0, 0, 3, BS_FLAGS1_40 | BS_FLAGS1_SP_EVT_ACTIVE | BS_FLAGS1_10)
            EVT_ELSE
                EVT_CALL(SetActorSounds, ACTOR_PLAYER, 3, 348, 0)
                EVT_CALL(PlayerDamageEnemy, LVar0, 553648256, 0, 0, 3, BS_FLAGS1_40 | BS_FLAGS1_SP_EVT_ACTIVE | BS_FLAGS1_10)
            EVT_END_IF
        EVT_CASE_DEFAULT
            EVT_CALL(SetActorSounds, ACTOR_PLAYER, 3, 348, 0)
            EVT_CALL(PlayerDamageEnemy, LVar0, 553648256, 0, 0, 3, BS_FLAGS1_SP_EVT_ACTIVE | BS_FLAGS1_10)
    EVT_END_SWITCH
    EVT_CALL(PlaySoundAtActor, ACTOR_PLAYER, 0x235)
    EVT_SWITCH(LVar0)
        EVT_CASE_OR_EQ(0)
        EVT_CASE_OR_EQ(2)
            EVT_IF_EQ(LocalFlag(0), 1)
                EVT_EXEC_WAIT(N(D_802A15D8))
                EVT_RETURN
            EVT_END_IF
            EVT_EXEC_WAIT(N(D_802A19B0))
            EVT_RETURN
        EVT_END_CASE_GROUP
        EVT_CASE_OR_EQ(1)
        EVT_CASE_OR_EQ(3)
            EVT_IF_EQ(LocalFlag(0), 1)
                EVT_EXEC_WAIT(N(D_802A15D8))
                EVT_RETURN
            EVT_END_IF
        EVT_END_CASE_GROUP
    EVT_END_SWITCH
    EVT_CALL(func_80269524, LVarE)
    EVT_SET(LocalFlag(0), 0)
    EVT_SET(LVarF, 0)
    EVT_ADD(LVarF, 1)
    EVT_LABEL(20)
    EVT_CALL(GetTargetListLength, LVar0)
    EVT_SUB(LVar0, 1)
    EVT_IF_EQ(LVarF, LVar0)
        EVT_SET(LocalFlag(0), 1)
    EVT_END_IF
    EVT_CALL(CloseActionCommandInfo)
    EVT_CALL(LoadActionCommand, ACTION_COMMAND_JUMP)
    EVT_CALL(action_command_jump_init)
    EVT_IF_EQ(LocalFlag(0), 1)
        EVT_CALL(ShowActionHud, 0)
    EVT_END_IF
    EVT_CALL(UseBattleCamPreset, BTL_CAM_PRESET_40)
    EVT_CALL(action_command_jump_start, 25, 3)
    EVT_CALL(ChooseNextTarget, 0, LVar0)
    EVT_CALL(SetGoalToTarget, ACTOR_PLAYER)
    EVT_CALL(SetJumpAnimations, ACTOR_PLAYER, 0, ANIM_Mario_AnimMidairStill, ANIM_Mario_AnimMidairStill, ANIM_Mario_1000C)
    EVT_IF_EQ(LVarF, 1)
        EVT_CALL(func_80275F00, 25, 2)
    EVT_ELSE
        EVT_CALL(func_80275F00, 25, 4)
    EVT_END_IF
    EVT_CALL(PlayerTestEnemy, LVar0, 128, 0, 0, 1, 0)
    EVT_IF_EQ(LVar0, 6)
        EVT_EXEC_WAIT(N(D_802A1FEC))
        EVT_RETURN
    EVT_END_IF
    EVT_WAIT(1)
    EVT_CALL(DidActionSucceed, LVar0)
    EVT_SWITCH(LVar0)
        EVT_CASE_GT(0)
            EVT_IF_EQ(LocalFlag(0), 0)
                EVT_CALL(SetActorSounds, ACTOR_PLAYER, 3, 348, 0)
                EVT_CALL(PlayerDamageEnemy, LVar0, 553648256, 0, 0, 3, BS_FLAGS1_40 | BS_FLAGS1_SP_EVT_ACTIVE | BS_FLAGS1_10)
            EVT_ELSE
                EVT_CALL(SetActorSounds, ACTOR_PLAYER, 3, 348, 0)
                EVT_CALL(PlayerDamageEnemy, LVar0, 553648256, 0, 0, 3, BS_FLAGS1_80 | BS_FLAGS1_40 | BS_FLAGS1_SP_EVT_ACTIVE | BS_FLAGS1_10)
            EVT_END_IF
        EVT_CASE_DEFAULT
            EVT_IF_EQ(LocalFlag(0), 0)
                EVT_CALL(SetActorSounds, ACTOR_PLAYER, 3, 348, 0)
                EVT_CALL(PlayerDamageEnemy, LVar0, 553648256, 0, 0, 3, BS_FLAGS1_SP_EVT_ACTIVE | BS_FLAGS1_10)
            EVT_ELSE
                EVT_CALL(SetActorSounds, ACTOR_PLAYER, 3, 348, 0)
                EVT_CALL(PlayerDamageEnemy, LVar0, 553648256, 0, 0, 3, BS_FLAGS1_80 | BS_FLAGS1_40 | BS_FLAGS1_SP_EVT_ACTIVE | BS_FLAGS1_10)
            EVT_END_IF
    EVT_END_SWITCH
    EVT_SWITCH(LVarF)
        EVT_CASE_EQ(0)
            EVT_CALL(PlaySoundAtActor, ACTOR_PLAYER, 0x235)
        EVT_CASE_EQ(1)
            EVT_CALL(PlaySoundAtActor, ACTOR_PLAYER, 0x236)
        EVT_CASE_EQ(2)
            EVT_CALL(PlaySoundAtActor, ACTOR_PLAYER, 0x237)
        EVT_CASE_EQ(3)
            EVT_CALL(PlaySoundAtActor, ACTOR_PLAYER, 0x238)
        EVT_CASE_DEFAULT
            EVT_CALL(PlaySoundAtActor, ACTOR_PLAYER, 0x238)
    EVT_END_SWITCH
    EVT_CALL(func_80269550, LVarE)
    EVT_CALL(DidActionSucceed, LVar0)
    EVT_SWITCH(LVar0)
        EVT_CASE_OR_EQ(0)
        EVT_CASE_OR_EQ(2)
            EVT_IF_EQ(LocalFlag(0), 1)
                EVT_EXEC_WAIT(N(D_802A15D8))
                EVT_RETURN
            EVT_END_IF
            EVT_EXEC_WAIT(N(D_802A19B0))
            EVT_RETURN
        EVT_END_CASE_GROUP
        EVT_CASE_OR_EQ(1)
        EVT_CASE_OR_EQ(3)
            EVT_IF_EQ(LocalFlag(0), 1)
                EVT_EXEC_WAIT(N(D_802A15D8))
                EVT_RETURN
            EVT_END_IF
        EVT_END_CASE_GROUP
    EVT_END_SWITCH
    EVT_ADD(LVarF, 1)
    EVT_CALL(GetTargetListLength, LVar0)
    EVT_IF_GE(LVarF, LVar0)
        EVT_EXEC_WAIT(N(D_802A19B0))
        EVT_RETURN
    EVT_END_IF
    EVT_GOTO(20)
    EVT_RETURN
    EVT_END
};
