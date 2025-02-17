#include "common.h"
#include "battle/battle.h"
#include "script_api/battle.h"
#include "battle/action_cmd/jump.h"
#include "battle/action_cmd.h"
#include "sprite/npc/BattleGoombario.h"

#define NAMESPACE b_area_hos_goombario_tutor

s32 N(idleAnimations_80219010)[] = {
    STATUS_NORMAL,    ANIM_BattleGoombario_Idle,
    STATUS_STONE,     ANIM_BattleGoombario_Still,
    STATUS_SLEEP,     ANIM_BattleGoombario_Still,
    STATUS_POISON,    ANIM_BattleGoombario_Idle,
    STATUS_STOP,      ANIM_BattleGoombario_Still,
    STATUS_STATIC,    ANIM_BattleGoombario_Still,
    STATUS_PARALYZE,  ANIM_BattleGoombario_Still,
    STATUS_DIZZY,     ANIM_BattleGoombario_Still,
    STATUS_DIZZY,     ANIM_BattleGoombario_Still,
    STATUS_END,
};

s32 N(defenseTable_8021905C)[] = {
    ELEMENT_NORMAL, 0,
    ELEMENT_END,
};

s32 N(statusTable_80219068)[] = {
    STATUS_NORMAL, 0,
    STATUS_DEFAULT, 0,
    STATUS_SLEEP, 0,
    STATUS_POISON, 0,
    STATUS_FROZEN, 0,
    STATUS_DIZZY, 0,
    STATUS_FEAR, 0,
    STATUS_STATIC, 0,
    STATUS_PARALYZE, 0,
    STATUS_SHRINK, 0,
    STATUS_STOP, 0,
    STATUS_DEFAULT_TURN_MOD, 0,
    STATUS_SLEEP_TURN_MOD, 0,
    STATUS_POISON_TURN_MOD, 0,
    STATUS_FROZEN_TURN_MOD, 0,
    STATUS_DIZZY_TURN_MOD, 0,
    STATUS_FEAR_TURN_MOD, 0,
    STATUS_STATIC_TURN_MOD, 0,
    STATUS_PARALYZE_TURN_MOD, 0,
    STATUS_SHRINK_TURN_MOD, 0,
    STATUS_STOP_TURN_MOD, 0,
    STATUS_END,
};

ActorPartBlueprint N(partsTable_80219114)[] = {
    {
        .flags = ACTOR_PART_FLAG_MULTI_TARGET,
        .index = 1,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { -4, 24 },
        .opacity = 255,
        .idleAnimations = N(idleAnimations_80219010),
        .defenseTable = N(defenseTable_8021905C),
        .eventFlags = ACTOR_EVENT_FLAG_0,
        .elementImmunityFlags = 0,
        .unk_1D = 0,
    },
};

extern EvtScript N(init_80219160);

ActorBlueprint NAMESPACE = {
    .flags = ACTOR_FLAG_40000,
    .type = ACTOR_TYPE_GOOMBARIO_TUTOR1,
    .level = 99,
    .maxHP = 99,
    .partCount = ARRAY_COUNT(N(partsTable_80219114)),
    .partsData = N(partsTable_80219114),
    .takeTurnScript = &N(init_80219160),
    .statusTable = N(statusTable_80219068),
    .escapeChance = 0,
    .airLiftChance = 0,
    .hurricaneChance = 0,
    .spookChance = 0,
    .upAndAwayChance = 0,
    .spinSmashReq = 0,
    .powerBounceChance = 100,
    .coinReward = 0,
    .size = { 24, 32 },
    .hpBarOffset = { 0, 0 },
    .statusIconOffset = { -10, 20 },
    .statusMessageOffset = { 10, 20 },
};

extern EvtScript N(takeTurn_80219444);
extern EvtScript N(idle_802191D0);
extern EvtScript N(handleEvent_802191E0);
extern EvtScript N(80219C74);

EvtScript N(init_80219160) = {
    EVT_CALL(BindTakeTurn, ACTOR_SELF, EVT_PTR(N(takeTurn_80219444)))
    EVT_CALL(BindIdle, ACTOR_SELF, EVT_PTR(N(idle_802191D0)))
    EVT_CALL(BindHandleEvent, ACTOR_SELF, EVT_PTR(N(handleEvent_802191E0)))
    EVT_CALL(SetActorVar, -127, 0, 1)
    EVT_EXEC(N(80219C74))
    EVT_RETURN
    EVT_END
};

EvtScript N(idle_802191D0) = {
    EVT_RETURN
    EVT_END
};

EvtScript N(handleEvent_802191E0) = {
    EVT_CALL(UseIdleAnimation, ACTOR_SELF, FALSE)
    EVT_THREAD
        EVT_CALL(func_8026BF48, 1)
        EVT_CALL(GetLastEvent, ACTOR_SELF, LVar0)
        EVT_SWITCH(LVar0)
            EVT_CASE_EQ(10)
                EVT_CALL(GetActorVar, -127, 0, LVar0)
                EVT_IF_EQ(LVar0, 0)
                    EVT_CALL(RandInt, 2, LVar0)
                    EVT_SWITCH(LVar0)
                        EVT_CASE_EQ(0)
                            EVT_CALL(ActorSpeak, MSG_HOS_002D, -127, 1, 589834, 589826)
                        EVT_CASE_EQ(1)
                            EVT_CALL(ActorSpeak, MSG_HOS_002E, -127, 1, 589834, 589826)
                        EVT_CASE_EQ(2)
                    EVT_END_SWITCH
                EVT_END_IF
        EVT_END_SWITCH
        EVT_CALL(func_8026BF48, 0)
    EVT_END_THREAD
    EVT_CALL(GetLastEvent, ACTOR_SELF, LVar0)
    EVT_SWITCH(LVar0)
        EVT_CASE_OR_EQ(9)
        EVT_CASE_OR_EQ(10)
            EVT_SET_CONST(LVar0, 0x00000001)
            EVT_SET_CONST(LVar1, ANIM_BattleGoombario_HurtStill)
            EVT_EXEC_WAIT(DoNormalHit)
        EVT_END_CASE_GROUP
        EVT_CASE_OR_EQ(23)
        EVT_CASE_OR_EQ(25)
            EVT_SET_CONST(LVar0, 0x00000001)
            EVT_SET_CONST(LVar1, ANIM_BattleGoombario_Idle)
            EVT_EXEC_WAIT(DoImmune)
        EVT_END_CASE_GROUP
        EVT_CASE_EQ(48)
            EVT_SET_CONST(LVar0, 0x00000001)
            EVT_SET_CONST(LVar1, ANIM_BattleGoombario_HurtStill)
            EVT_EXEC_WAIT(DoNormalHit)
            EVT_WAIT(1000)
        EVT_CASE_DEFAULT
    EVT_END_SWITCH
    EVT_CALL(UseIdleAnimation, ACTOR_SELF, TRUE)
    EVT_RETURN
    EVT_END
};

EvtScript N(takeTurn_80219444) = {
    EVT_CALL(UseIdleAnimation, ACTOR_SELF, FALSE)
    EVT_CALL(EnableIdleScript, ACTOR_SELF, 0)
    EVT_CALL(SetTargetActor, ACTOR_SELF, ACTOR_PLAYER)
    EVT_CALL(UseBattleCamPreset, BTL_CAM_PRESET_63)
    EVT_CALL(SetBattleCamZoom, 400)
    EVT_CALL(SetBattleCamOffsetZ, 40)
    EVT_CALL(BattleCamTargetActor, ACTOR_SELF)
    EVT_CALL(SetAnimation, ACTOR_SELF, 1, ANIM_BattleGoombario_Run)
    EVT_CALL(SetGoalToTarget, ACTOR_SELF)
    EVT_CALL(AddGoalPos, ACTOR_SELF, 50, 0, 0)
    EVT_CALL(SetActorSpeed, ACTOR_SELF, EVT_FLOAT(6.0))
    EVT_CALL(RunToGoal, ACTOR_SELF, 0, FALSE)
    EVT_CALL(SetAnimation, ACTOR_SELF, 1, ANIM_BattleGoombario_Idle)
    EVT_CALL(SetActorDispOffset, ACTOR_SELF, 0, -1, 0)
    EVT_WAIT(1)
    EVT_CALL(SetActorDispOffset, ACTOR_SELF, 0, -2, 0)
    EVT_WAIT(5)
    EVT_CALL(SetActorDispOffset, ACTOR_SELF, 0, 10, 0)
    EVT_CALL(SetAnimation, ACTOR_SELF, 1, ANIM_BattleGoombario_Headbonk)
    EVT_CALL(UseBattleCamPreset, BTL_CAM_PRESET_66)
    EVT_CALL(SetBattleCamZoom, 400)
    EVT_CALL(SetBattleCamOffsetZ, 40)
    EVT_CALL(func_8024ECF8, -1, 1, 0)
    EVT_CALL(BattleCamTargetActor, ACTOR_SELF)
    EVT_CALL(SetGoalToTarget, ACTOR_SELF)
    EVT_CALL(AddGoalPos, ACTOR_SELF, -10, 0, 0)
    EVT_CALL(GetBattleFlags2, LVar0)
    EVT_IF_FLAG(LVar0, 0x200)
        EVT_CALL(AddGoalPos, ACTOR_SELF, 5, 10, 0)
    EVT_END_IF
    EVT_CALL(SetActorJumpGravity, ACTOR_SELF, EVT_FLOAT(1.1))
    EVT_THREAD
        EVT_WAIT(4)
        EVT_SET(LVar0, 0)
        EVT_LOOP(4)
            EVT_ADD(LVar0, 45)
            EVT_CALL(SetActorRotation, ACTOR_SELF, 0, 0, LVar0)
            EVT_WAIT(1)
        EVT_END_LOOP
        EVT_CALL(SetAnimation, ACTOR_SELF, 1, ANIM_BattleGoombario_Headbonk)
    EVT_END_THREAD
    EVT_THREAD
        EVT_CALL(LoadActionCommand, ACTION_COMMAND_JUMP)
        EVT_CALL(action_command_jump_init)
        EVT_CALL(ShowActionHud, 1)
        EVT_WAIT(10)
        EVT_CALL(action_command_jump_start, 12, 3)
    EVT_END_THREAD
    EVT_CALL(PlaySound, SOUND_JUMP_3E2)
    EVT_CALL(JumpToGoal, ACTOR_SELF, 22, FALSE, TRUE, FALSE)
    EVT_CALL(SetAnimation, ACTOR_SELF, 1, ANIM_BattleGoombario_Headbonk)
    EVT_CALL(SetActorScale, ACTOR_SELF, EVT_FLOAT(1.1), EVT_FLOAT(0.8), EVT_FLOAT(1.0))
    EVT_WAIT(1)
    EVT_CALL(SetActorScale, ACTOR_SELF, EVT_FLOAT(1.3), EVT_FLOAT(0.5), EVT_FLOAT(1.0))
    EVT_WAIT(1)
    EVT_CALL(GetActionCommandMode, LVar0)
    EVT_IF_EQ(LVar0, ACTION_COMMAND_MODE_TUTORIAL)
        EVT_CALL(SetActionCommandMode, ACTION_COMMAND_MODE_TUTORIAL_WAIT_INPUT)
        EVT_LOOP(0)
            EVT_CALL(GetActionCommandMode, LVar0)
            EVT_IF_LT(LVar0, ACTION_COMMAND_MODE_TUTORIAL)
                EVT_BREAK_LOOP
            EVT_END_IF
            EVT_WAIT(1)
        EVT_END_LOOP
    EVT_END_IF
    EVT_CALL(GetActorVar, -127, 0, LVar0)
    EVT_IF_EQ(LVar0, 1)
        EVT_CALL(func_80269EAC, 5)
    EVT_END_IF
    EVT_WAIT(2)
    EVT_CALL(EnemyDamageTarget, ACTOR_SELF, LVar0, 0, 0, 0, 1, BS_FLAGS1_SP_EVT_ACTIVE)
    EVT_CALL(CloseActionCommandInfo)
    EVT_SET(LVarF, LVar0)
    EVT_SWITCH(LVarF)
        EVT_CASE_OR_EQ(0)
        EVT_CASE_OR_EQ(2)
        EVT_CASE_OR_EQ(10)
            EVT_CALL(SetActorScale, ACTOR_SELF, EVT_FLOAT(1.1), EVT_FLOAT(0.8), EVT_FLOAT(1.0))
            EVT_WAIT(1)
            EVT_CALL(SetActorScale, ACTOR_SELF, EVT_FLOAT(1.0), EVT_FLOAT(1.0), EVT_FLOAT(1.0))
            EVT_WAIT(1)
            EVT_CALL(SetActorRotation, ACTOR_SELF, 0, 0, 0)
            EVT_CALL(SetActorDispOffset, ACTOR_SELF, 0, 0, 0)
            EVT_CALL(SetAnimation, ACTOR_SELF, 1, ANIM_BattleGoombario_Idle)
            EVT_CALL(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            EVT_ADD(LVar0, 40)
            EVT_SET(LVar1, 0)
            EVT_CALL(SetActorJumpGravity, ACTOR_SELF, EVT_FLOAT(1.8))
            EVT_CALL(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            EVT_CALL(JumpToGoal, ACTOR_SELF, 10, FALSE, TRUE, FALSE)
            EVT_ADD(LVar0, 30)
            EVT_CALL(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            EVT_CALL(JumpToGoal, ACTOR_SELF, 8, FALSE, TRUE, FALSE)
            EVT_ADD(LVar0, 20)
            EVT_CALL(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            EVT_CALL(JumpToGoal, ACTOR_SELF, 6, FALSE, TRUE, FALSE)
            EVT_SUB(LVar0, 10)
            EVT_CALL(JumpToGoal, ACTOR_SELF, 4, FALSE, TRUE, FALSE)
            EVT_CALL(SetAnimation, ACTOR_SELF, 1, ANIM_BattleGoombario_Idle)
            EVT_WAIT(8)
            EVT_CALL(UseBattleCamPreset, BTL_CAM_PRESET_C)
            EVT_CALL(YieldTurn)
            EVT_CALL(SetAnimation, ACTOR_SELF, 1, ANIM_BattleGoombario_Idle)
            EVT_CALL(SetGoalToHome, ACTOR_SELF)
            EVT_CALL(SetActorSpeed, ACTOR_SELF, EVT_FLOAT(4.0))
            EVT_CALL(SetAnimation, ACTOR_SELF, 1, ANIM_BattleGoombario_Run)
            EVT_CALL(RunToGoal, ACTOR_SELF, 0, FALSE)
            EVT_CALL(SetAnimation, ACTOR_SELF, 1, ANIM_BattleGoombario_Idle)
        EVT_END_CASE_GROUP
    EVT_END_SWITCH
    EVT_CALL(EnableIdleScript, ACTOR_SELF, 1)
    EVT_CALL(UseIdleAnimation, ACTOR_SELF, TRUE)
    EVT_RETURN
    EVT_END
};

ApiStatus func_80218000_47F0B0(Evt* script, s32 isInitialCall) {
    PlayerData* playerData = &gPlayerData;

    playerData->currentPartner = PARTNER_GOOMBARIO;
    return ApiStatus_DONE2;
}

EvtScript N(80219C74) = {
    EVT_CALL(SetBattleFlagBits, BS_FLAGS1_2000000, 1)
    EVT_CALL(func_802535B4, 0)
    EVT_CALL(WaitForState, BATTLE_STATE_PLAYER_MENU)
    EVT_WAIT(15)
    EVT_CALL(UseIdleAnimation, ACTOR_PARTNER, FALSE)
    EVT_CALL(EnableIdleScript, ACTOR_PARTNER, 0)
    EVT_CALL(SetActorJumpGravity, ACTOR_PARTNER, EVT_FLOAT(1.0))
    EVT_CALL(GetActorPos, ACTOR_PARTNER, LVar0, LVar1, LVar2)
    EVT_CALL(SetGoalPos, ACTOR_PARTNER, LVar0, LVar1, LVar2)
    EVT_CALL(JumpToGoal, ACTOR_PARTNER, 10, FALSE, FALSE, FALSE)
    EVT_CALL(UseIdleAnimation, ACTOR_PARTNER, FALSE)
    EVT_CALL(ActorSpeak, MSG_HOS_0019, 256, 1, 2097161, 2097157)
    EVT_CALL(UseIdleAnimation, ACTOR_PARTNER, TRUE)
    EVT_CALL(func_8026E020, 1)
    EVT_CALL(SetActionCommandMode, ACTION_COMMAND_MODE_TUTORIAL)
    EVT_CALL(WaitForState, BATTLE_STATE_PLAYER_MOVE)
    EVT_CALL(UseBattleCamPreset, BTL_CAM_PRESET_C)
    EVT_WAIT(15)
    EVT_CALL(SetGoalPos, ACTOR_PARTNER, -73, 40, 202)
    EVT_CALL(FlyToGoal, ACTOR_PARTNER, 20, 20, 10)
    EVT_CALL(UseIdleAnimation, ACTOR_PARTNER, FALSE)
    EVT_CALL(ActorSpeak, MSG_HOS_001A, 256, 1, 2097161, 2097157)
    EVT_CALL(UseIdleAnimation, ACTOR_PARTNER, TRUE)
    EVT_CALL(SetActionCommandMode, ACTION_COMMAND_MODE_LEARNED)
    EVT_CALL(SetBattleFlagBits, BS_FLAGS1_4000, 0)
    EVT_CALL(SetMessageBoxDuration, -1)
    EVT_THREAD
        EVT_LOOP(15)
            EVT_CALL(SetMessageBoxDuration, 35)
            EVT_WAIT(1)
        EVT_END_LOOP
    EVT_END_THREAD
    EVT_WAIT(15)
    EVT_CALL(SetGoalToHome, ACTOR_PARTNER)
    EVT_CALL(FlyToGoal, ACTOR_PARTNER, 20, 20, 10)
    EVT_CALL(SetActionCommandMode, ACTION_COMMAND_MODE_TUTORIAL)
    EVT_CALL(WaitForState, BATTLE_STATE_0)
    EVT_CALL(SetBattleFlagBits2, 512, 1)
    EVT_LOOP(0)
        EVT_CALL(GetActionCommandMode, LVar0)
        EVT_IF_NE(LVar0, ACTION_COMMAND_MODE_TUTORIAL)
            EVT_BREAK_LOOP
        EVT_END_IF
        EVT_WAIT(1)
    EVT_END_LOOP
    EVT_CALL(UseIdleAnimation, ACTOR_PARTNER, FALSE)
    EVT_CALL(ActorSpeak, MSG_HOS_001B, 256, 1, 2097161, 2097157)
    EVT_LOOP(0)
        EVT_CALL(CheckButtonDown, 32768, LVar0)
        EVT_IF_EQ(LVar0, 0)
            EVT_BREAK_LOOP
        EVT_END_IF
        EVT_WAIT(1)
    EVT_END_LOOP
    EVT_LOOP(0)
        EVT_CALL(CheckButtonPress, 32768, LVar0)
        EVT_IF_EQ(LVar0, 1)
            EVT_BREAK_LOOP
        EVT_END_IF
        EVT_WAIT(1)
    EVT_END_LOOP
    EVT_CALL(EndActorSpeech, 256, 1, 2097161, 2097157)
    EVT_CALL(UseIdleAnimation, ACTOR_PARTNER, TRUE)
    EVT_CALL(SetActionSuccess, 1)
    EVT_CALL(SetActionCommandMode, ACTION_COMMAND_MODE_LEARNED)
    EVT_CALL(WaitForState, BATTLE_STATE_BEGIN_PARTNER_TURN)
    EVT_CALL(UseBattleCamPreset, BTL_CAM_PRESET_C)
    EVT_WAIT(15)
    EVT_CALL(UseIdleAnimation, ACTOR_PARTNER, FALSE)
    EVT_CALL(ActorSpeak, MSG_HOS_001D, 256, 1, 2097161, 2097157)
    EVT_CALL(UseIdleAnimation, ACTOR_PARTNER, TRUE)
    EVT_CALL(WaitForState, BATTLE_STATE_9)
    EVT_CALL(UseBattleCamPreset, BTL_CAM_PRESET_C)
    EVT_WAIT(15)
    EVT_CALL(UseIdleAnimation, ACTOR_PARTNER, FALSE)
    EVT_CALL(ActorSpeak, MSG_HOS_001E, 512, 1, 589839, 589825)
    EVT_CALL(UseIdleAnimation, ACTOR_PARTNER, TRUE)
    EVT_CALL(SetActionCommandMode, ACTION_COMMAND_MODE_TUTORIAL)
    EVT_CALL(WaitForState, BATTLE_STATE_0)
    EVT_LOOP(0)
        EVT_CALL(GetActionCommandMode, LVar0)
        EVT_IF_NE(LVar0, ACTION_COMMAND_MODE_TUTORIAL)
            EVT_BREAK_LOOP
        EVT_END_IF
        EVT_WAIT(1)
    EVT_END_LOOP
    EVT_CALL(UseIdleAnimation, ACTOR_PARTNER, FALSE)
    EVT_CALL(ActorSpeak, MSG_HOS_001F, 256, 1, 2097161, 2097157)
    EVT_LOOP(0)
        EVT_CALL(CheckButtonDown, 32768, LVar0)
        EVT_IF_EQ(LVar0, 0)
            EVT_BREAK_LOOP
        EVT_END_IF
        EVT_WAIT(1)
    EVT_END_LOOP
    EVT_LOOP(0)
        EVT_CALL(CheckButtonPress, 32768, LVar0)
        EVT_IF_EQ(LVar0, 1)
            EVT_BREAK_LOOP
        EVT_END_IF
        EVT_WAIT(1)
    EVT_END_LOOP
    EVT_CALL(EndActorSpeech, 256, 1, 2097161, 2097157)
    EVT_CALL(UseIdleAnimation, ACTOR_PARTNER, TRUE)
    EVT_CALL(SetActionSuccess, 1)
    EVT_CALL(SetActionCommandMode, ACTION_COMMAND_MODE_TUTORIAL_BLOCK)
    EVT_CALL(WaitForState, BATTLE_STATE_END_TURN)
    EVT_CALL(UseBattleCamPreset, BTL_CAM_PRESET_C)
    EVT_WAIT(15)
    EVT_CALL(SetActionCommandMode, ACTION_COMMAND_MODE_LEARNED)
    EVT_CALL(UseIdleAnimation, ACTOR_PARTNER, FALSE)
    EVT_CALL(ActorSpeak, MSG_HOS_0020, 256, 1, 2097161, 2097157)
    EVT_CALL(UseIdleAnimation, ACTOR_PARTNER, TRUE)
    EVT_CALL(WaitForState, BATTLE_STATE_PLAYER_MENU)
    EVT_CALL(func_8026E020, 2)
    EVT_CALL(SetActionCommandMode, ACTION_COMMAND_MODE_TUTORIAL)
    EVT_CALL(WaitForState, BATTLE_STATE_PLAYER_MOVE)
    EVT_CALL(UseIdleAnimation, ACTOR_PARTNER, FALSE)
    EVT_CALL(ActorSpeak, MSG_HOS_0022, 256, 1, 2097161, 2097157)
    EVT_LOOP(0)
        EVT_CALL(CheckButtonDown, 262144, LVar0)
        EVT_IF_EQ(LVar0, 0)
            EVT_BREAK_LOOP
        EVT_END_IF
        EVT_WAIT(1)
    EVT_END_LOOP
    EVT_LOOP(0)
        EVT_CALL(CheckButtonPress, 262144, LVar0)
        EVT_IF_EQ(LVar0, 1)
            EVT_BREAK_LOOP
        EVT_END_IF
        EVT_WAIT(1)
    EVT_END_LOOP
    EVT_CALL(EndActorSpeech, 256, 1, 2097161, 2097157)
    EVT_CALL(UseIdleAnimation, ACTOR_PARTNER, TRUE)
    EVT_CALL(SetActionCommandMode, ACTION_COMMAND_MODE_LEARNED)
    EVT_CALL(WaitForState, BATTLE_STATE_0)
    EVT_WAIT(5)
    EVT_CALL(SetActionCommandMode, ACTION_COMMAND_MODE_TUTORIAL)
    EVT_LOOP(0)
        EVT_CALL(GetActionCommandMode, LVar0)
        EVT_IF_NE(LVar0, ACTION_COMMAND_MODE_TUTORIAL)
            EVT_BREAK_LOOP
        EVT_END_IF
        EVT_CALL(CheckButtonDown, 262144, LVar0)
        EVT_IF_EQ(LVar0, 0)
            EVT_CALL(SetActionCommandMode, ACTION_COMMAND_MODE_TUTORIAL_BLOCK)
            EVT_CALL(PauseTakeTurn, 0)
            EVT_CALL(UseIdleAnimation, ACTOR_PARTNER, FALSE)
            EVT_CALL(ActorSpeak, MSG_HOS_0023, 256, 1, 2097161, 2097157)
            EVT_LOOP(0)
                EVT_CALL(CheckButtonPress, 262144, LVar0)
                EVT_IF_EQ(LVar0, 1)
                    EVT_BREAK_LOOP
                EVT_END_IF
                EVT_WAIT(1)
            EVT_END_LOOP
            EVT_CALL(EndActorSpeech, 256, 1, 2097161, 2097157)
            EVT_CALL(UseIdleAnimation, ACTOR_PARTNER, TRUE)
            EVT_CALL(SetActionCommandMode, ACTION_COMMAND_MODE_TUTORIAL)
            EVT_CALL(ResumeTakeTurn, 0)
        EVT_END_IF
        EVT_WAIT(1)
    EVT_END_LOOP
    EVT_LOOP(0)
        EVT_CALL(GetActionResult, LVar0)
        EVT_IF_EQ(LVar0, 3)
            EVT_BREAK_LOOP
        EVT_END_IF
        EVT_WAIT(1)
    EVT_END_LOOP
    EVT_CALL(UseIdleAnimation, ACTOR_PARTNER, FALSE)
    EVT_CALL(ActorSpeak, MSG_HOS_0024, 256, 1, 2097161, 2097157)
    EVT_LOOP(0)
        EVT_CALL(CheckButtonDown, 262144, LVar0)
        EVT_IF_EQ(LVar0, 0)
            EVT_BREAK_LOOP
        EVT_END_IF
        EVT_WAIT(1)
    EVT_END_LOOP
    EVT_CALL(EndActorSpeech, 256, 1, 2097161, 2097157)
    EVT_CALL(UseIdleAnimation, ACTOR_PARTNER, TRUE)
    EVT_CALL(SetActionSuccess, 1)
    EVT_CALL(SetActionCommandMode, ACTION_COMMAND_MODE_LEARNED)
    EVT_CALL(WaitForState, BATTLE_STATE_BEGIN_PARTNER_TURN)
    EVT_CALL(UseBattleCamPreset, BTL_CAM_PRESET_C)
    EVT_WAIT(15)
    EVT_CALL(UseIdleAnimation, ACTOR_PARTNER, FALSE)
    EVT_CALL(ActorSpeak, MSG_HOS_0025, 256, 1, 2097161, 2097157)
    EVT_CALL(UseIdleAnimation, ACTOR_PARTNER, TRUE)
    EVT_CALL(SetActorFlagBits, ACTOR_ENEMY0, ACTOR_FLAG_NO_ATTACK, 1)
    EVT_CALL(WaitForState, BATTLE_STATE_0)
    EVT_CALL(WaitForState, BATTLE_STATE_PLAYER_MENU)
    EVT_CALL(ShowBattleChoice, 1966109)
    EVT_CALL(EndActorSpeech, 256, 1, 2097161, 2097157)
    EVT_IF_EQ(LVar0, 1)
        EVT_CALL(ActorSpeak, MSG_HOS_0027, 256, 1, 2097161, 2097157)
        EVT_GOTO(100)
    EVT_END_IF
    EVT_CALL(UseIdleAnimation, ACTOR_PARTNER, FALSE)
    EVT_CALL(ActorSpeak, MSG_HOS_0028, 256, 1, 2097161, 2097157)
    EVT_CALL(UseIdleAnimation, ACTOR_PARTNER, TRUE)
    EVT_CALL(SetActorVar, -127, 0, 0)
    EVT_CALL(SetBattleFlagBits2, 512, 0)
    EVT_LABEL(10)
    EVT_CALL(func_8026E020, 131)
    EVT_CALL(SetActionCommandMode, ACTION_COMMAND_MODE_TUTORIAL)
    EVT_CALL(WaitForState, BATTLE_STATE_PLAYER_MOVE)
    EVT_CALL(GetMenuSelection, LVar0, LVar1, LVar2)
    EVT_IF_EQ(LVar0, 7)
        EVT_GOTO(99)
    EVT_END_IF
    EVT_CALL(SetActionCommandMode, ACTION_COMMAND_MODE_LEARNED)
    EVT_CALL(WaitForState, BATTLE_STATE_BEGIN_PARTNER_TURN)
    EVT_CALL(UseIdleAnimation, ACTOR_PARTNER, FALSE)
    EVT_CALL(func_80269524, LVar0)
    EVT_SWITCH(LVar0)
        EVT_CASE_EQ(-1)
            EVT_CALL(ActorSpeak, MSG_HOS_002A, 256, 1, 2097161, 2097157)
        EVT_CASE_EQ(0)
            EVT_CALL(ActorSpeak, MSG_HOS_002B, 256, 1, 2097161, 2097157)
        EVT_CASE_EQ(1)
            EVT_CALL(ActorSpeak, MSG_HOS_0029, 256, 1, 2097161, 2097157)
    EVT_END_SWITCH
    EVT_CALL(UseIdleAnimation, ACTOR_PARTNER, TRUE)
    EVT_CALL(SetEnemyHP, 512, 99)
    EVT_CALL(SetActorFlagBits, ACTOR_ENEMY0, ACTOR_FLAG_NO_ATTACK, 0)
    EVT_CALL(SetActionCommandMode, ACTION_COMMAND_MODE_LEARNED)
    EVT_CALL(WaitForState, BATTLE_STATE_END_TURN)
    EVT_CALL(UseIdleAnimation, ACTOR_PARTNER, FALSE)
    EVT_CALL(GetBlockResult, LVar0)
    EVT_SWITCH(LVar0)
        EVT_CASE_EQ(-1)
            EVT_CALL(ActorSpeak, MSG_HOS_002A, 256, 1, 2097161, 2097157)
        EVT_CASE_EQ(0)
            EVT_CALL(ActorSpeak, MSG_HOS_002B, 256, 1, 2097161, 2097157)
        EVT_CASE_EQ(1)
            EVT_CALL(ActorSpeak, MSG_HOS_0029, 256, 1, 2097161, 2097157)
    EVT_END_SWITCH
    EVT_CALL(UseIdleAnimation, ACTOR_PARTNER, TRUE)
    EVT_CALL(WaitForState, BATTLE_STATE_PLAYER_MENU)
    EVT_GOTO(10)
    EVT_LABEL(99)
    EVT_CALL(UseIdleAnimation, ACTOR_PARTNER, FALSE)
    EVT_CALL(ActorSpeak, MSG_HOS_002C, 256, 1, 2097161, 2097157)
    EVT_LABEL(100)
    EVT_CALL(WaitForState, BATTLE_STATE_0)
    EVT_CALL(SetBattleState, 30)
    EVT_CALL(func_80218000_47F0B0)
    EVT_WAIT(10000)
    EVT_RETURN
    EVT_END
};
