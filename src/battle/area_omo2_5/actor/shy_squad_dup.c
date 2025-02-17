#include "common.h"
#include "battle/battle.h"
#include "script_api/battle.h"
#include "effects.h"
#include "sprite/npc/TankGuy.h"

#define NAMESPACE b_area_omo2_5_shy_squad_dup

extern s32 N(idleAnimations)[];
extern EvtScript N(init);
extern EvtScript N(takeTurn);
extern EvtScript N(idle);
extern EvtScript N(handleEvent);
extern EvtScript N(nextTurn);
extern EvtScript N(move_guy_to_pos);
extern EvtScript N(displace_guy);
extern EvtScript N(displace_guy_2);
extern EvtScript N(onHit);
extern EvtScript N(set_squad_animation);
extern EvtScript N(onDeath);
extern EvtScript N(next_phase);
extern EvtScript N(run_away);
extern EvtScript N(attack);
extern EvtScript N(run_squad_to_pos);

s32 N(defenseTable)[] = {
    ELEMENT_NORMAL, 0,
    ELEMENT_END,
};

s32 N(statusTable)[] = {
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

ActorPartBlueprint N(parts)[] = {
    {
        .flags = ACTOR_PART_FLAG_INVISIBLE | ACTOR_PART_FLAG_4 | ACTOR_PART_FLAG_MULTI_TARGET,
        .index = 1,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { 0, 24 },
        .opacity = 255,
        .idleAnimations = N(idleAnimations),
        .defenseTable = N(defenseTable),
        .eventFlags = 0,
        .elementImmunityFlags = 0,
        .unk_1C = 0,
        .unk_1D = 0,
    },
    {
        .flags = ACTOR_PART_FLAG_2 | ACTOR_PART_FLAG_NO_TARGET | ACTOR_PART_FLAG_USE_ABSOLUTE_POSITION,
        .index = 2,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { 0, 24 },
        .opacity = 255,
        .idleAnimations = N(idleAnimations),
        .defenseTable = N(defenseTable),
        .eventFlags = 0,
        .elementImmunityFlags = 0,
        .unk_1C = 0,
        .unk_1D = 0,
    },
    {
        .flags = ACTOR_PART_FLAG_2 | ACTOR_PART_FLAG_NO_TARGET | ACTOR_PART_FLAG_USE_ABSOLUTE_POSITION,
        .index = 3,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { 0, 24 },
        .opacity = 255,
        .idleAnimations = N(idleAnimations),
        .defenseTable = N(defenseTable),
        .eventFlags = 0,
        .elementImmunityFlags = 0,
        .unk_1C = 0,
        .unk_1D = 0,
    },
    {
        .flags = ACTOR_PART_FLAG_2 | ACTOR_PART_FLAG_NO_TARGET | ACTOR_PART_FLAG_USE_ABSOLUTE_POSITION,
        .index = 4,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { 0, 24 },
        .opacity = 255,
        .idleAnimations = N(idleAnimations),
        .defenseTable = N(defenseTable),
        .eventFlags = 0,
        .elementImmunityFlags = 0,
        .unk_1C = 0,
        .unk_1D = 0,
    },
    {
        .flags = ACTOR_PART_FLAG_2 | ACTOR_PART_FLAG_NO_TARGET | ACTOR_PART_FLAG_USE_ABSOLUTE_POSITION,
        .index = 5,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { 0, 24 },
        .opacity = 255,
        .idleAnimations = N(idleAnimations),
        .defenseTable = N(defenseTable),
        .eventFlags = 0,
        .elementImmunityFlags = 0,
        .unk_1C = 0,
        .unk_1D = 0,
    },
    {
        .flags = ACTOR_PART_FLAG_2 | ACTOR_PART_FLAG_NO_TARGET | ACTOR_PART_FLAG_USE_ABSOLUTE_POSITION,
        .index = 6,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { 0, 24 },
        .opacity = 255,
        .idleAnimations = N(idleAnimations),
        .defenseTable = N(defenseTable),
        .eventFlags = 0,
        .elementImmunityFlags = 0,
        .unk_1C = 0,
        .unk_1D = 0,
    },
    {
        .flags = ACTOR_PART_FLAG_2 | ACTOR_PART_FLAG_NO_TARGET | ACTOR_PART_FLAG_USE_ABSOLUTE_POSITION,
        .index = 7,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { 0, 24 },
        .opacity = 255,
        .idleAnimations = N(idleAnimations),
        .defenseTable = N(defenseTable),
        .eventFlags = 0,
        .elementImmunityFlags = 0,
        .unk_1C = 0,
        .unk_1D = 0,
    },
    {
        .flags = ACTOR_PART_FLAG_2 | ACTOR_PART_FLAG_NO_TARGET | ACTOR_PART_FLAG_USE_ABSOLUTE_POSITION,
        .index = 8,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { 0, 24 },
        .opacity = 255,
        .idleAnimations = N(idleAnimations),
        .defenseTable = N(defenseTable),
        .eventFlags = 0,
        .elementImmunityFlags = 0,
        .unk_1C = 0,
        .unk_1D = 0,
    },
    {
        .flags = ACTOR_PART_FLAG_2 | ACTOR_PART_FLAG_NO_TARGET | ACTOR_PART_FLAG_USE_ABSOLUTE_POSITION,
        .index = 9,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { 0, 24 },
        .opacity = 255,
        .idleAnimations = N(idleAnimations),
        .defenseTable = N(defenseTable),
        .eventFlags = 0,
        .elementImmunityFlags = 0,
        .unk_1C = 0,
        .unk_1D = 0,
    },
    {
        .flags = ACTOR_PART_FLAG_2 | ACTOR_PART_FLAG_NO_TARGET | ACTOR_PART_FLAG_USE_ABSOLUTE_POSITION,
        .index = 10,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { 0, 24 },
        .opacity = 255,
        .idleAnimations = N(idleAnimations),
        .defenseTable = N(defenseTable),
        .eventFlags = 0,
        .elementImmunityFlags = 0,
        .unk_1C = 0,
        .unk_1D = 0,
    },
    {
        .flags = ACTOR_PART_FLAG_2 | ACTOR_PART_FLAG_NO_TARGET | ACTOR_PART_FLAG_USE_ABSOLUTE_POSITION,
        .index = 11,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { 0, 24 },
        .opacity = 255,
        .idleAnimations = N(idleAnimations),
        .defenseTable = N(defenseTable),
        .eventFlags = 0,
        .elementImmunityFlags = 0,
        .unk_1C = 0,
        .unk_1D = 0,
    },
    {
        .flags = ACTOR_PART_FLAG_2 | ACTOR_PART_FLAG_NO_TARGET | ACTOR_PART_FLAG_USE_ABSOLUTE_POSITION,
        .index = 12,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { 0, 24 },
        .opacity = 255,
        .idleAnimations = N(idleAnimations),
        .defenseTable = N(defenseTable),
        .eventFlags = 0,
        .elementImmunityFlags = 0,
        .unk_1C = 0,
        .unk_1D = 0,
    },
    {
        .flags = ACTOR_PART_FLAG_2 | ACTOR_PART_FLAG_NO_TARGET | ACTOR_PART_FLAG_USE_ABSOLUTE_POSITION,
        .index = 13,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { 0, 24 },
        .opacity = 255,
        .idleAnimations = N(idleAnimations),
        .defenseTable = N(defenseTable),
        .eventFlags = 0,
        .elementImmunityFlags = 0,
        .unk_1C = 0,
        .unk_1D = 0,
    },
    {
        .flags = ACTOR_PART_FLAG_2 | ACTOR_PART_FLAG_NO_TARGET | ACTOR_PART_FLAG_USE_ABSOLUTE_POSITION,
        .index = 14,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { 0, 24 },
        .opacity = 255,
        .idleAnimations = N(idleAnimations),
        .defenseTable = N(defenseTable),
        .eventFlags = 0,
        .elementImmunityFlags = 0,
        .unk_1C = 0,
        .unk_1D = 0,
    },
    {
        .flags = ACTOR_PART_FLAG_2 | ACTOR_PART_FLAG_NO_TARGET | ACTOR_PART_FLAG_USE_ABSOLUTE_POSITION,
        .index = 15,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { 0, 24 },
        .opacity = 255,
        .idleAnimations = N(idleAnimations),
        .defenseTable = N(defenseTable),
        .eventFlags = 0,
        .elementImmunityFlags = 0,
        .unk_1C = 0,
        .unk_1D = 0,
    },
    {
        .flags = ACTOR_PART_FLAG_2 | ACTOR_PART_FLAG_NO_TARGET | ACTOR_PART_FLAG_USE_ABSOLUTE_POSITION,
        .index = 16,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { 0, 24 },
        .opacity = 255,
        .idleAnimations = N(idleAnimations),
        .defenseTable = N(defenseTable),
        .eventFlags = 0,
        .elementImmunityFlags = 0,
        .unk_1C = 0,
        .unk_1D = 0,
    },
};

ActorBlueprint NAMESPACE = {
    .flags = ACTOR_FLAG_NO_SHADOW,
    .type = ACTOR_TYPE_SHY_SQUAD_DUP,
    .level = 0,
    .maxHP = 15,
    .partCount = ARRAY_COUNT(N(parts)),
    .partsData = N(parts),
    .takeTurnScript = &N(init),
    .statusTable = N(statusTable),
    .escapeChance = 0,
    .airLiftChance = 0,
    .hurricaneChance = 0,
    .spookChance = 0,
    .upAndAwayChance = 0,
    .spinSmashReq = 4,
    .powerBounceChance = 80,
    .coinReward = 0,
    .size = { 30, 30 },
    .hpBarOffset = { 0, 0 },
    .statusIconOffset = { -10, 20 },
    .statusMessageOffset = { 10, 20 },
};

s32 N(idleAnimations)[] = {
    STATUS_NORMAL, ANIM_TankGuy_Anim01,
    STATUS_STOP, ANIM_TankGuy_Anim00,
    STATUS_END,
};

s32 N(idleAnimations_watt)[] = {
    STATUS_NORMAL, ANIM_TankGuy_Anim07,
    STATUS_STOP, ANIM_TankGuy_Anim00,
    STATUS_END,
};

EvtScript N(init) = {
    EVT_CALL(BindTakeTurn, ACTOR_SELF, EVT_PTR(N(takeTurn)))
    EVT_CALL(BindIdle, ACTOR_SELF, EVT_PTR(N(idle)))
    EVT_CALL(BindHandleEvent, ACTOR_SELF, EVT_PTR(N(handleEvent)))
    EVT_CALL(BindNextTurn, ACTOR_SELF, EVT_PTR(N(nextTurn)))
    EVT_CALL(SetActorVar, ACTOR_SELF, 3, 0)
    EVT_CALL(SetActorVar, ACTOR_SELF, 4, 0)
    EVT_CALL(SetActorVar, ACTOR_SELF, 15, 0)
    EVT_CALL(SetPartMovementVar, ACTOR_SELF, 2, 0, -20)
    EVT_CALL(SetPartMovementVar, ACTOR_SELF, 2, 1, -10)
    EVT_CALL(SetPartMovementVar, ACTOR_SELF, 3, 0, -10)
    EVT_CALL(SetPartMovementVar, ACTOR_SELF, 3, 1, 20)
    EVT_CALL(SetPartMovementVar, ACTOR_SELF, 4, 0, -10)
    EVT_CALL(SetPartMovementVar, ACTOR_SELF, 4, 1, -40)
    EVT_CALL(SetPartMovementVar, ACTOR_SELF, 5, 0, 0)
    EVT_CALL(SetPartMovementVar, ACTOR_SELF, 5, 1, 40)
    EVT_CALL(SetPartMovementVar, ACTOR_SELF, 6, 0, 0)
    EVT_CALL(SetPartMovementVar, ACTOR_SELF, 6, 1, -10)
    EVT_CALL(SetPartMovementVar, ACTOR_SELF, 7, 0, 10)
    EVT_CALL(SetPartMovementVar, ACTOR_SELF, 7, 1, 20)
    EVT_CALL(SetPartMovementVar, ACTOR_SELF, 8, 0, 10)
    EVT_CALL(SetPartMovementVar, ACTOR_SELF, 8, 1, -40)
    EVT_CALL(SetPartMovementVar, ACTOR_SELF, 9, 0, 20)
    EVT_CALL(SetPartMovementVar, ACTOR_SELF, 9, 1, 40)
    EVT_CALL(SetPartMovementVar, ACTOR_SELF, 10, 0, 40)
    EVT_CALL(SetPartMovementVar, ACTOR_SELF, 10, 1, 40)
    EVT_CALL(SetPartMovementVar, ACTOR_SELF, 11, 0, 50)
    EVT_CALL(SetPartMovementVar, ACTOR_SELF, 11, 1, 20)
    EVT_CALL(SetPartMovementVar, ACTOR_SELF, 12, 0, 50)
    EVT_CALL(SetPartMovementVar, ACTOR_SELF, 12, 1, -40)
    EVT_CALL(SetPartMovementVar, ACTOR_SELF, 13, 0, 30)
    EVT_CALL(SetPartMovementVar, ACTOR_SELF, 13, 1, -40)
    EVT_CALL(SetPartMovementVar, ACTOR_SELF, 14, 0, 40)
    EVT_CALL(SetPartMovementVar, ACTOR_SELF, 14, 1, -10)
    EVT_CALL(SetPartMovementVar, ACTOR_SELF, 15, 0, 30)
    EVT_CALL(SetPartMovementVar, ACTOR_SELF, 15, 1, 20)
    EVT_CALL(SetPartMovementVar, ACTOR_SELF, 16, 0, 20)
    EVT_CALL(SetPartMovementVar, ACTOR_SELF, 16, 1, -10)
    EVT_CALL(SetPartMovementVar, ACTOR_SELF, 2, 2, -30)
    EVT_CALL(SetPartMovementVar, ACTOR_SELF, 2, 3, 0)
    EVT_CALL(SetPartMovementVar, ACTOR_SELF, 3, 2, -20)
    EVT_CALL(SetPartMovementVar, ACTOR_SELF, 3, 3, 20)
    EVT_CALL(SetPartMovementVar, ACTOR_SELF, 4, 2, -20)
    EVT_CALL(SetPartMovementVar, ACTOR_SELF, 4, 3, -10)
    EVT_CALL(SetPartMovementVar, ACTOR_SELF, 5, 2, -20)
    EVT_CALL(SetPartMovementVar, ACTOR_SELF, 5, 3, 10)
    EVT_CALL(SetPartMovementVar, ACTOR_SELF, 6, 2, -30)
    EVT_CALL(SetPartMovementVar, ACTOR_SELF, 6, 3, 0)
    EVT_CALL(SetPartMovementVar, ACTOR_SELF, 7, 2, -20)
    EVT_CALL(SetPartMovementVar, ACTOR_SELF, 7, 3, 20)
    EVT_CALL(SetPartMovementVar, ACTOR_SELF, 8, 2, -20)
    EVT_CALL(SetPartMovementVar, ACTOR_SELF, 8, 3, -10)
    EVT_CALL(SetPartMovementVar, ACTOR_SELF, 9, 2, 0)
    EVT_CALL(SetPartMovementVar, ACTOR_SELF, 9, 3, 10)
    EVT_CALL(SetPartMovementVar, ACTOR_SELF, 10, 2, 20)
    EVT_CALL(SetPartMovementVar, ACTOR_SELF, 10, 3, 10)
    EVT_CALL(SetPartMovementVar, ACTOR_SELF, 11, 2, 20)
    EVT_CALL(SetPartMovementVar, ACTOR_SELF, 11, 3, 20)
    EVT_CALL(SetPartMovementVar, ACTOR_SELF, 12, 2, 20)
    EVT_CALL(SetPartMovementVar, ACTOR_SELF, 12, 3, -10)
    EVT_CALL(SetPartMovementVar, ACTOR_SELF, 13, 2, 20)
    EVT_CALL(SetPartMovementVar, ACTOR_SELF, 13, 3, -10)
    EVT_CALL(SetPartMovementVar, ACTOR_SELF, 14, 2, 30)
    EVT_CALL(SetPartMovementVar, ACTOR_SELF, 14, 3, 0)
    EVT_CALL(SetPartMovementVar, ACTOR_SELF, 15, 2, 20)
    EVT_CALL(SetPartMovementVar, ACTOR_SELF, 15, 3, 20)
    EVT_CALL(SetPartMovementVar, ACTOR_SELF, 16, 2, 0)
    EVT_CALL(SetPartMovementVar, ACTOR_SELF, 16, 3, 0)
    EVT_CALL(SetPartMovementVar, ACTOR_SELF, 2, 4, -30)
    EVT_CALL(SetPartMovementVar, ACTOR_SELF, 2, 5, 10)
    EVT_CALL(SetPartMovementVar, ACTOR_SELF, 3, 4, -30)
    EVT_CALL(SetPartMovementVar, ACTOR_SELF, 3, 5, -10)
    EVT_CALL(SetPartMovementVar, ACTOR_SELF, 4, 4, 30)
    EVT_CALL(SetPartMovementVar, ACTOR_SELF, 4, 5, 10)
    EVT_CALL(SetPartMovementVar, ACTOR_SELF, 5, 4, 30)
    EVT_CALL(SetPartMovementVar, ACTOR_SELF, 5, 5, -10)
    EVT_CALL(SetPartMovementVar, ACTOR_SELF, 6, 4, -20)
    EVT_CALL(SetPartMovementVar, ACTOR_SELF, 6, 5, 20)
    EVT_CALL(SetPartMovementVar, ACTOR_SELF, 7, 4, -20)
    EVT_CALL(SetPartMovementVar, ACTOR_SELF, 7, 5, -20)
    EVT_CALL(SetPartMovementVar, ACTOR_SELF, 8, 4, 20)
    EVT_CALL(SetPartMovementVar, ACTOR_SELF, 8, 5, 20)
    EVT_CALL(SetPartMovementVar, ACTOR_SELF, 9, 4, 0)
    EVT_CALL(SetPartMovementVar, ACTOR_SELF, 9, 5, 20)
    EVT_CALL(SetPartMovementVar, ACTOR_SELF, 10, 4, 0)
    EVT_CALL(SetPartMovementVar, ACTOR_SELF, 10, 5, -20)
    EVT_CALL(SetPartMovementVar, ACTOR_SELF, 11, 4, -20)
    EVT_CALL(SetPartMovementVar, ACTOR_SELF, 11, 5, 0)
    EVT_CALL(SetPartMovementVar, ACTOR_SELF, 12, 4, 10)
    EVT_CALL(SetPartMovementVar, ACTOR_SELF, 12, 5, -10)
    EVT_CALL(SetPartMovementVar, ACTOR_SELF, 13, 4, 10)
    EVT_CALL(SetPartMovementVar, ACTOR_SELF, 13, 5, 10)
    EVT_CALL(SetPartMovementVar, ACTOR_SELF, 14, 4, -10)
    EVT_CALL(SetPartMovementVar, ACTOR_SELF, 14, 5, -10)
    EVT_CALL(SetPartMovementVar, ACTOR_SELF, 15, 4, -10)
    EVT_CALL(SetPartMovementVar, ACTOR_SELF, 15, 5, 10)
    EVT_CALL(SetPartMovementVar, ACTOR_SELF, 16, 4, 20)
    EVT_CALL(SetPartMovementVar, ACTOR_SELF, 16, 5, 0)
    EVT_SET(LVar0, 2)
    EVT_LOOP(15)
        EVT_CALL(SetPartPos, ACTOR_SELF, LVar0, 185, 0, 47)
        EVT_ADD(LVar0, 1)
    EVT_END_LOOP
    EVT_CALL(ForceHomePos, ACTOR_SELF, 20, 0, -10)
    EVT_CALL(HPBarToHome, ACTOR_SELF)
    EVT_SET(LVar0, 2)
    EVT_LOOP(15)
        EVT_CALL(CreatePartShadow, ACTOR_SELF, LVar0)
        EVT_ADD(LVar0, 1)
    EVT_END_LOOP
    EVT_SET(LVar0, 2)
    EVT_SET(LVar1, ANIM_TankGuy_Anim03)
    EVT_SET(LVar2, 55)
    EVT_SET(LVar3, 47)
    EVT_SET(LVar4, EVT_FLOAT(4.0))
    EVT_SET(LVar5, 30)
    EVT_SET(LVarF, 0)
    EVT_LOOP(15)
        EVT_THREAD
            EVT_WAIT(LVarF)
            EVT_EXEC_WAIT(N(move_guy_to_pos))
            EVT_CALL(GetPartMovementVar, ACTOR_SELF, LVar0, 0, LVar2)
            EVT_CALL(GetPartMovementVar, ACTOR_SELF, LVar0, 1, LVar3)
            EVT_SET(LVar5, 20)
            EVT_EXEC_WAIT(N(move_guy_to_pos))
            EVT_CALL(SetAnimation, ACTOR_SELF, LVar0, ANIM_TankGuy_Anim01)
        EVT_END_THREAD
        EVT_ADD(LVar0, 1)
        EVT_ADD(LVarF, 5)
    EVT_END_LOOP
    EVT_RETURN
    EVT_END
};

EvtScript N(nextTurn) = {
    EVT_RETURN
    EVT_END
};

EvtScript N(idle) = {
    EVT_LABEL(0)
    EVT_CALL(GetCurrentPartnerID, LVar0)
    EVT_IF_EQ(LVar0, PARTNER_WATT)
        EVT_CALL(SetIdleAnimations, ACTOR_SELF, 1, EVT_PTR(N(idleAnimations_watt)))
        EVT_SET(LVar0, 2)
        EVT_LOOP(15)
            EVT_CALL(SetIdleAnimations, ACTOR_SELF, LVar0, EVT_PTR(N(idleAnimations_watt)))
            EVT_ADD(LVar0, 1)
        EVT_END_LOOP
    EVT_ELSE
        EVT_CALL(SetIdleAnimations, ACTOR_SELF, 1, EVT_PTR(N(idleAnimations)))
        EVT_SET(LVar0, 2)
        EVT_LOOP(15)
            EVT_CALL(SetIdleAnimations, ACTOR_SELF, LVar0, EVT_PTR(N(idleAnimations)))
            EVT_ADD(LVar0, 1)
        EVT_END_LOOP
    EVT_END_IF
    EVT_WAIT(1)
    EVT_GOTO(0)
    EVT_RETURN
    EVT_END
};

EvtScript N(move_guy_to_pos) = {
    EVT_SET(LVarA, 2)
    EVT_CALL(GetActorVar, ACTOR_SELF, 3, LVarB)
    EVT_ADD(LVarA, LVarB)
    EVT_IF_LT(LVar0, LVarA)
        EVT_RETURN
    EVT_END_IF
    EVT_CALL(GetPartOffset, ACTOR_SELF, LVar0, LVar6, 0, LVar7)
    EVT_IF_LT(LVar6, LVar2)
        EVT_CALL(SetPartYaw, ACTOR_SELF, LVar0, 180)
    EVT_ELSE
        EVT_CALL(SetPartYaw, ACTOR_SELF, LVar0, 0)
    EVT_END_IF
    EVT_CALL(GetDist2D, LVar9, LVar6, LVar7, LVar2, LVar3)
    EVT_IF_GE(LVar9, LVar4)
        EVT_CALL(SetAnimation, ACTOR_SELF, LVar0, LVar1)
        EVT_CALL(SetPartMoveSpeed, ACTOR_SELF, LVar0, LVar4)
        EVT_CALL(RunPartTo, ACTOR_SELF, LVar0, LVar2, 0, LVar3, LVar5)
    EVT_END_IF
    EVT_RETURN
    EVT_END
};

EvtScript N(onSpinSmash) = {
    EVT_SET_CONST(LVar0, 2)
    EVT_LOOP(15)
        EVT_CALL(GetActorVar, ACTOR_SELF, 3, LVarD)
        EVT_CALL(GetActorVar, ACTOR_SELF, 4, LVarE)
        EVT_ADD(LVarD, 2)
        EVT_ADD(LVarD, LVarE)
        EVT_IF_GE(LVar0, LVarD)
            EVT_THREAD
                EVT_EXEC_WAIT(N(displace_guy))
            EVT_END_THREAD
        EVT_END_IF
        EVT_ADD(LVar0, 1)
    EVT_END_LOOP
    EVT_WAIT(30)
    EVT_RETURN
    EVT_END
};

EvtScript N(displace_guy) = {
    EVT_CALL(SetAnimation, ACTOR_SELF, LVar0, LVar1)
    EVT_SET(LVar2, LVar0)
    EVT_CALL(GetDamageIntensity)
    EVT_SWITCH(LVar0)
        EVT_CASE_EQ(0)
            EVT_CALL(SetPartDispOffset, ACTOR_SELF, LVar2, 0, 1, 0)
            EVT_WAIT(1)
            EVT_CALL(SetPartDispOffset, ACTOR_SELF, LVar2, 0, 3, 0)
            EVT_WAIT(1)
            EVT_CALL(SetPartDispOffset, ACTOR_SELF, LVar2, 0, 8, 0)
            EVT_WAIT(1)
            EVT_CALL(SetPartDispOffset, ACTOR_SELF, LVar2, 0, 4, 0)
            EVT_WAIT(1)
            EVT_CALL(SetPartDispOffset, ACTOR_SELF, LVar2, 0, 10, 0)
            EVT_WAIT(1)
            EVT_CALL(SetPartDispOffset, ACTOR_SELF, LVar2, 0, 4, 0)
            EVT_WAIT(1)
            EVT_CALL(SetPartDispOffset, ACTOR_SELF, LVar2, 0, 5, 0)
            EVT_WAIT(1)
            EVT_LOOP(2)
                EVT_CALL(SetPartDispOffset, ACTOR_SELF, LVar2, 0, 3, 0)
                EVT_WAIT(1)
                EVT_CALL(SetPartDispOffset, ACTOR_SELF, LVar2, 0, 0, 0)
                EVT_WAIT(1)
            EVT_END_LOOP
            EVT_LOOP(4)
                EVT_CALL(SetPartDispOffset, ACTOR_SELF, LVar2, 0, 1, 0)
                EVT_WAIT(1)
                EVT_CALL(SetPartDispOffset, ACTOR_SELF, LVar2, 0, 0, 0)
                EVT_WAIT(1)
            EVT_END_LOOP
            EVT_CALL(SetPartDispOffset, ACTOR_SELF, LVar2, 0, 0, 0)
            EVT_WAIT(10)
        EVT_CASE_EQ(1)
            EVT_CALL(SetPartDispOffset, ACTOR_SELF, LVar2, 0, 1, 0)
            EVT_WAIT(1)
            EVT_CALL(SetPartDispOffset, ACTOR_SELF, LVar2, 0, 4, 0)
            EVT_WAIT(1)
            EVT_CALL(SetPartDispOffset, ACTOR_SELF, LVar2, 0, 20, 0)
            EVT_WAIT(1)
            EVT_CALL(SetPartDispOffset, ACTOR_SELF, LVar2, 0, 10, 0)
            EVT_WAIT(1)
            EVT_CALL(SetPartDispOffset, ACTOR_SELF, LVar2, 0, 22, 0)
            EVT_WAIT(1)
            EVT_CALL(SetPartDispOffset, ACTOR_SELF, LVar2, 0, 10, 0)
            EVT_WAIT(1)
            EVT_CALL(SetPartDispOffset, ACTOR_SELF, LVar2, 0, 14, 0)
            EVT_WAIT(1)
            EVT_LOOP(2)
                EVT_CALL(SetPartDispOffset, ACTOR_SELF, LVar2, 0, 7, 0)
                EVT_WAIT(1)
                EVT_CALL(SetPartDispOffset, ACTOR_SELF, LVar2, 0, 0, 0)
                EVT_WAIT(1)
            EVT_END_LOOP
            EVT_LOOP(6)
                EVT_CALL(SetPartDispOffset, ACTOR_SELF, LVar2, 0, 3, 0)
                EVT_WAIT(1)
                EVT_CALL(SetPartDispOffset, ACTOR_SELF, LVar2, 0, 0, 0)
                EVT_WAIT(1)
            EVT_END_LOOP
            EVT_CALL(SetPartDispOffset, ACTOR_SELF, LVar2, 0, 0, 0)
            EVT_WAIT(10)
        EVT_CASE_EQ(2)
            EVT_CALL(SetPartDispOffset, ACTOR_SELF, LVar2, 0, 1, 0)
            EVT_WAIT(1)
            EVT_CALL(SetPartDispOffset, ACTOR_SELF, LVar2, 0, 6, 0)
            EVT_WAIT(1)
            EVT_CALL(SetPartDispOffset, ACTOR_SELF, LVar2, 0, 22, 0)
            EVT_WAIT(1)
            EVT_CALL(SetPartDispOffset, ACTOR_SELF, LVar2, 0, 12, 0)
            EVT_WAIT(1)
            EVT_CALL(SetPartDispOffset, ACTOR_SELF, LVar2, 0, 25, 0)
            EVT_WAIT(1)
            EVT_CALL(SetPartDispOffset, ACTOR_SELF, LVar2, 0, 12, 0)
            EVT_WAIT(1)
            EVT_CALL(SetPartDispOffset, ACTOR_SELF, LVar2, 0, 17, 0)
            EVT_WAIT(1)
            EVT_LOOP(2)
                EVT_CALL(SetPartDispOffset, ACTOR_SELF, LVar2, 0, 10, 0)
                EVT_WAIT(1)
                EVT_CALL(SetPartDispOffset, ACTOR_SELF, LVar2, 0, 0, 0)
                EVT_WAIT(1)
            EVT_END_LOOP
            EVT_LOOP(6)
                EVT_CALL(SetPartDispOffset, ACTOR_SELF, LVar2, 0, 4, 0)
                EVT_WAIT(1)
                EVT_CALL(SetPartDispOffset, ACTOR_SELF, LVar2, 0, 0, 0)
                EVT_WAIT(1)
            EVT_END_LOOP
            EVT_CALL(SetPartDispOffset, ACTOR_SELF, LVar2, 0, 0, 0)
            EVT_WAIT(10)
        EVT_CASE_EQ(3)
            EVT_CALL(SetPartDispOffset, ACTOR_SELF, LVar2, 0, 3, 0)
            EVT_WAIT(1)
            EVT_CALL(SetPartDispOffset, ACTOR_SELF, LVar2, 0, 8, 0)
            EVT_WAIT(1)
            EVT_CALL(SetPartDispOffset, ACTOR_SELF, LVar2, 0, 24, 0)
            EVT_WAIT(1)
            EVT_CALL(SetPartDispOffset, ACTOR_SELF, LVar2, 0, 14, 0)
            EVT_WAIT(1)
            EVT_CALL(SetPartDispOffset, ACTOR_SELF, LVar2, 0, 28, 0)
            EVT_WAIT(1)
            EVT_CALL(SetPartDispOffset, ACTOR_SELF, LVar2, 0, 14, 0)
            EVT_WAIT(1)
            EVT_CALL(SetPartDispOffset, ACTOR_SELF, LVar2, 0, 19, 0)
            EVT_WAIT(1)
            EVT_LOOP(2)
                EVT_CALL(SetPartDispOffset, ACTOR_SELF, LVar2, 0, 14, 0)
                EVT_WAIT(1)
                EVT_CALL(SetPartDispOffset, ACTOR_SELF, LVar2, 0, 0, 0)
                EVT_WAIT(1)
            EVT_END_LOOP
            EVT_LOOP(6)
                EVT_CALL(SetPartDispOffset, ACTOR_SELF, LVar2, 0, 5, 0)
                EVT_WAIT(1)
                EVT_CALL(SetPartDispOffset, ACTOR_SELF, LVar2, 0, 0, 0)
                EVT_WAIT(1)
            EVT_END_LOOP
            EVT_LOOP(2)
                EVT_CALL(SetPartDispOffset, ACTOR_SELF, LVar2, 0, 2, 0)
                EVT_WAIT(1)
                EVT_CALL(SetPartDispOffset, ACTOR_SELF, LVar2, 0, 0, 0)
                EVT_WAIT(1)
            EVT_END_LOOP
            EVT_CALL(SetPartDispOffset, ACTOR_SELF, LVar2, 0, 0, 0)
            EVT_WAIT(10)
        EVT_CASE_EQ(4)
            EVT_CALL(SetPartDispOffset, ACTOR_SELF, LVar2, 0, 5, 0)
            EVT_WAIT(1)
            EVT_CALL(SetPartDispOffset, ACTOR_SELF, LVar2, 0, 10, 0)
            EVT_WAIT(1)
            EVT_CALL(SetPartDispOffset, ACTOR_SELF, LVar2, 0, 28, 0)
            EVT_WAIT(1)
            EVT_CALL(SetPartDispOffset, ACTOR_SELF, LVar2, 0, 16, 0)
            EVT_WAIT(1)
            EVT_CALL(SetPartDispOffset, ACTOR_SELF, LVar2, 0, 32, 0)
            EVT_WAIT(1)
            EVT_CALL(SetPartDispOffset, ACTOR_SELF, LVar2, 0, 16, 0)
            EVT_WAIT(1)
            EVT_CALL(SetPartDispOffset, ACTOR_SELF, LVar2, 0, 21, 0)
            EVT_WAIT(1)
            EVT_LOOP(2)
                EVT_CALL(SetPartDispOffset, ACTOR_SELF, LVar2, 0, 16, 0)
                EVT_WAIT(1)
                EVT_CALL(SetPartDispOffset, ACTOR_SELF, LVar2, 0, 0, 0)
                EVT_WAIT(1)
            EVT_END_LOOP
            EVT_LOOP(6)
                EVT_CALL(SetPartDispOffset, ACTOR_SELF, LVar2, 0, 7, 0)
                EVT_WAIT(1)
                EVT_CALL(SetPartDispOffset, ACTOR_SELF, LVar2, 0, 0, 0)
                EVT_WAIT(1)
            EVT_END_LOOP
            EVT_LOOP(2)
                EVT_CALL(SetPartDispOffset, ACTOR_SELF, LVar2, 0, 3, 0)
                EVT_WAIT(1)
                EVT_CALL(SetPartDispOffset, ACTOR_SELF, LVar2, 0, 0, 0)
                EVT_WAIT(1)
            EVT_END_LOOP
            EVT_CALL(SetPartDispOffset, ACTOR_SELF, LVar2, 0, 0, 0)
            EVT_WAIT(10)
    EVT_END_SWITCH
    EVT_RETURN
    EVT_END
};

EvtScript N(onShock) = {
    EVT_SET_CONST(LVar0, 2)
    EVT_LOOP(15)
        EVT_CALL(GetActorVar, ACTOR_SELF, 3, LVarD)
        EVT_CALL(GetActorVar, ACTOR_SELF, 4, LVarE)
        EVT_ADD(LVarD, 2)
        EVT_ADD(LVarD, LVarE)
        EVT_IF_GE(LVar0, LVarD)
            EVT_THREAD
                EVT_EXEC_WAIT(N(displace_guy_2))
            EVT_END_THREAD
        EVT_END_IF
        EVT_ADD(LVar0, 1)
    EVT_END_LOOP
    EVT_RETURN
    EVT_END
};

EvtScript N(displace_guy_2) = {
    EVT_CALL(SetAnimation, ACTOR_SELF, LVar0, LVar1)
    EVT_CALL(GetPartOffset, ACTOR_SELF, LVar0, LVar1, LVar2, LVar3)
    EVT_CALL(GetActorSize, ACTOR_SELF, LVar4, LVar5)
    EVT_CALL(PlayEffect, EFFECT_FLASHING_BOX_SHOCKWAVE, 0, LVar1, LVar2, LVar3, LVar5, LVar4, 0, 0, 0, 0, 0, 0, 0)
    EVT_CALL(SetPartDispOffset, ACTOR_SELF, LVar0, 0, 0, 0)
    EVT_CALL(SetPartDispOffset, ACTOR_SELF, LVar0, 0, 1, 0)
    EVT_WAIT(1)
    EVT_CALL(SetPartDispOffset, ACTOR_SELF, LVar0, 0, 4, 0)
    EVT_WAIT(1)
    EVT_CALL(SetPartDispOffset, ACTOR_SELF, LVar0, 0, 16, 0)
    EVT_WAIT(1)
    EVT_CALL(SetPartDispOffset, ACTOR_SELF, LVar0, 0, 8, 0)
    EVT_WAIT(1)
    EVT_CALL(SetPartDispOffset, ACTOR_SELF, LVar0, 0, 20, 0)
    EVT_WAIT(1)
    EVT_CALL(SetPartDispOffset, ACTOR_SELF, LVar0, 0, 8, 0)
    EVT_WAIT(1)
    EVT_CALL(SetPartDispOffset, ACTOR_SELF, LVar0, 0, 12, 0)
    EVT_WAIT(1)
    EVT_LOOP(2)
        EVT_CALL(SetPartDispOffset, ACTOR_SELF, LVar0, 0, 6, 0)
        EVT_WAIT(1)
        EVT_CALL(SetPartDispOffset, ACTOR_SELF, LVar0, 0, 0, 0)
        EVT_WAIT(1)
    EVT_END_LOOP
    EVT_LOOP(6)
        EVT_CALL(SetPartDispOffset, ACTOR_SELF, LVar0, 0, 2, 0)
        EVT_WAIT(1)
        EVT_CALL(SetPartDispOffset, ACTOR_SELF, LVar0, 0, 0, 0)
        EVT_WAIT(1)
    EVT_END_LOOP
    EVT_CALL(SetPartDispOffset, ACTOR_SELF, LVar0, 0, 0, 0)
    EVT_WAIT(10)
    EVT_RETURN
    EVT_END
};

EvtScript N(handleEvent) = {
    EVT_CALL(UseIdleAnimation, ACTOR_SELF, FALSE)
    EVT_CALL(GetLastEvent, ACTOR_SELF, LVar0)
    EVT_SWITCH(LVar0)
        EVT_CASE_EQ(EVENT_BEGIN_FIRST_STRIKE)
        EVT_CASE_OR_EQ(EVENT_HIT_COMBO)
        EVT_CASE_OR_EQ(EVENT_HIT)
            EVT_SET_CONST(LVar1, ANIM_TankGuy_Anim04)
            EVT_EXEC_WAIT(N(onHit))
            EVT_SET_CONST(LVar1, ANIM_TankGuy_Anim04)
            EVT_EXEC_WAIT(N(onSpinSmash))
        EVT_END_CASE_GROUP
        EVT_CASE_EQ(EVENT_DEATH)
            EVT_SET_CONST(LVar1, ANIM_TankGuy_Anim04)
            EVT_EXEC_WAIT(N(onHit))
            EVT_SET_CONST(LVar1, ANIM_TankGuy_Anim04)
            EVT_EXEC_WAIT(N(onSpinSmash))
            EVT_WAIT(10)
            EVT_SET_CONST(LVar1, ANIM_TankGuy_Anim04)
            EVT_EXEC_WAIT(N(onDeath))
            EVT_RETURN
        EVT_CASE_OR_EQ(EVENT_BURN_HIT)
        EVT_CASE_OR_EQ(EVENT_BURN_DEATH)
            EVT_SET_CONST(LVar1, ANIM_TankGuy_Anim05)
            EVT_EXEC_WAIT(N(onHit))
            EVT_SET(LVar0, 2)
            EVT_LOOP(15)
                EVT_CALL(SetAnimation, ACTOR_SELF, LVar0, ANIM_TankGuy_Anim05)
                EVT_ADD(LVar0, 1)
            EVT_END_LOOP
            EVT_WAIT(20)
            EVT_SET(LVar0, 2)
            EVT_LOOP(15)
                EVT_CALL(SetAnimation, ACTOR_SELF, LVar0, ANIM_TankGuy_Anim05)
                EVT_ADD(LVar0, 1)
            EVT_END_LOOP
            EVT_WAIT(15)
            EVT_IF_EQ(LVar0, 36)
                EVT_WAIT(10)
                EVT_SET_CONST(LVar1, ANIM_TankGuy_Anim05)
                EVT_EXEC_WAIT(N(onDeath))
                EVT_RETURN
            EVT_END_IF
        EVT_END_CASE_GROUP
        EVT_CASE_EQ(EVENT_SPIN_SMASH_HIT)
            EVT_SET_CONST(LVar1, ANIM_TankGuy_Anim04)
            EVT_EXEC_WAIT(N(onHit))
            EVT_SET_CONST(LVar1, ANIM_TankGuy_Anim04)
            EVT_EXEC_WAIT(N(onSpinSmash))
        EVT_CASE_EQ(EVENT_SPIN_SMASH_DEATH)
            EVT_SET_CONST(LVar1, ANIM_TankGuy_Anim04)
            EVT_EXEC_WAIT(N(onHit))
            EVT_SET_CONST(LVar1, ANIM_TankGuy_Anim04)
            EVT_EXEC_WAIT(N(onSpinSmash))
            EVT_SET_CONST(LVar1, ANIM_TankGuy_Anim04)
            EVT_EXEC_WAIT(N(onDeath))
            EVT_RETURN
        EVT_CASE_EQ(EVENT_SHOCK_HIT)
            EVT_SET_CONST(LVar1, ANIM_TankGuy_Anim04)
            EVT_EXEC_WAIT(N(onHit))
            EVT_SET_CONST(LVar1, ANIM_TankGuy_Anim04)
            EVT_EXEC_WAIT(N(onShock))
            EVT_WAIT(40)
            EVT_CALL(UseBattleCamPreset, BTL_CAM_PRESET_C)
            EVT_CALL(MoveBattleCamOver, 20)
            EVT_EXEC_WAIT(N(run_squad_to_pos))
        EVT_CASE_EQ(EVENT_SHOCK_DEATH)
            EVT_SET_CONST(LVar1, ANIM_TankGuy_Anim04)
            EVT_EXEC_WAIT(N(onHit))
            EVT_SET_CONST(LVar1, ANIM_TankGuy_Anim04)
            EVT_EXEC_WAIT(N(onShock))
            EVT_WAIT(40)
            EVT_SET_CONST(LVar1, ANIM_TankGuy_Anim04)
            EVT_EXEC_WAIT(N(onDeath))
            EVT_RETURN
        EVT_CASE_OR_EQ(EVENT_SCRIPTED_IMMUNE)
        EVT_CASE_OR_EQ(EVENT_IMMUNE)
        EVT_CASE_OR_EQ(EVENT_SPIKE_TAUNT)
            EVT_SET_CONST(LVar0, 1)
            EVT_SET_CONST(LVar1, ANIM_TankGuy_Anim01)
            EVT_EXEC_WAIT(N(onSpinSmash))
        EVT_END_CASE_GROUP
        EVT_CASE_EQ(EVENT_BEGIN_AIR_LIFT)
            EVT_SET(LVar1, ANIM_TankGuy_Anim04)
            EVT_EXEC_WAIT(N(set_squad_animation))
            EVT_WAIT(1000)
        EVT_CASE_EQ(EVENT_AIR_LIFT_FAILED)
            EVT_SET_CONST(LVar0, 1)
            EVT_SET_CONST(LVar1, ANIM_TankGuy_Anim01)
            EVT_EXEC_WAIT(N(onSpinSmash))
        EVT_CASE_EQ(EVENT_END_FIRST_STRIKE)
            EVT_CALL(SetActorSpeed, ACTOR_SELF, EVT_FLOAT(4.0))
            EVT_CALL(HPBarToHome, ACTOR_SELF)
        EVT_CASE_EQ(EVENT_RECOVER_STATUS)
            EVT_SET_CONST(LVar0, 1)
            EVT_SET_CONST(LVar1, ANIM_TankGuy_Anim01)
            EVT_EXEC_WAIT(DoRecover)
        EVT_CASE_EQ(EVENT_30)
            EVT_SET_CONST(LVar0, 1)
            EVT_SET_CONST(LVar1, ANIM_TankGuy_Anim04)
            EVT_EXEC_WAIT(DoNormalHit)
            EVT_WAIT(1000)
        EVT_CASE_EQ(EVENT_SCARE_AWAY)
        EVT_CASE_DEFAULT
    EVT_END_SWITCH
    EVT_SET(LVar1, ANIM_TankGuy_Anim01)
    EVT_EXEC_WAIT(N(set_squad_animation))
    EVT_CALL(UseIdleAnimation, ACTOR_SELF, TRUE)
    EVT_RETURN
    EVT_END
};

EvtScript N(onHit) = {
    EVT_SET(LVar1, LVar1)
    EVT_EXEC_WAIT(N(set_squad_animation))
    EVT_CALL(GetActorVar, ACTOR_SELF, 4, LVar0)
    EVT_CALL(GetLastDamage, ACTOR_SELF, LVar1)
    EVT_ADD(LVar0, LVar1)
    EVT_CALL(SetActorVar, ACTOR_SELF, 4, LVar0)
    EVT_LABEL(0)
    EVT_CALL(GetActorVar, ACTOR_SELF, 4, LVar0)
    EVT_IF_EQ(LVar0, 0)
        EVT_RETURN
    EVT_END_IF
    EVT_CALL(GetActorVar, ACTOR_SELF, 3, LVar1)
    EVT_IF_GE(LVar1, 15)
        EVT_RETURN
    EVT_END_IF
    EVT_SET(LVar0, 2)
    EVT_ADD(LVar0, LVar1)
    EVT_IF_NE(LVar0, 16)
        EVT_THREAD
            EVT_CALL(SetPartFlagBits, ACTOR_SELF, LVar0, ACTOR_PART_FLAG_20000000, 1)
            EVT_CALL(GetPartOffset, ACTOR_SELF, LVar0, LVar1, LVar2, LVar3)
            EVT_CALL(GetPartMovementVar, ACTOR_SELF, LVar0, 2, LVar7)
            EVT_CALL(GetPartMovementVar, ACTOR_SELF, LVar0, 3, LVar8)
            EVT_ADD(LVar1, LVar7)
            EVT_ADD(LVar3, LVar8)
            EVT_CALL(SetPartJumpGravity, ACTOR_SELF, LVar0, EVT_FLOAT(0.5))
            EVT_CALL(JumpPartTo, ACTOR_SELF, LVar0, LVar1, 0, LVar3, 15, 1)
            EVT_CALL(func_80269E80, LVar5)
            EVT_SWITCH(LVar5)
                EVT_CASE_OR_EQ(10)
                EVT_CASE_OR_EQ(14)
                EVT_CASE_OR_EQ(12)
                EVT_CASE_OR_EQ(16)
                EVT_CASE_OR_EQ(11)
                EVT_CASE_OR_EQ(15)
                EVT_CASE_OR_EQ(13)
                EVT_CASE_OR_EQ(17)
                EVT_CASE_OR_EQ(2)
                EVT_END_CASE_GROUP
                EVT_CASE_DEFAULT
                    EVT_SET(LVar7, 0)
                    EVT_LOOP(24)
                        EVT_CALL(SetPartRotation, ACTOR_SELF, LVar0, 0, LVar7, 0)
                        EVT_ADD(LVar7, 30)
                        EVT_WAIT(1)
                    EVT_END_LOOP
            EVT_END_SWITCH
            EVT_CALL(PlayEffect, EFFECT_BIG_SMOKE_PUFF, LVar1, LVar2, LVar3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)
            EVT_SET(LVar8, 0)
            EVT_LOOP(12)
                EVT_CALL(SetPartRotation, ACTOR_SELF, LVar0, LVar8, 0, 0)
                EVT_ADD(LVar8, 8)
                EVT_WAIT(1)
            EVT_END_LOOP
            EVT_CALL(SetPartFlagBits, ACTOR_SELF, LVar0, ACTOR_PART_FLAG_INVISIBLE, 1)
            EVT_CALL(RemovePartShadow, ACTOR_SELF, LVar0)
        EVT_END_THREAD
    EVT_END_IF
    EVT_CALL(GetActorVar, ACTOR_SELF, 4, LVar0)
    EVT_SUB(LVar0, 1)
    EVT_CALL(SetActorVar, ACTOR_SELF, 4, LVar0)
    EVT_CALL(GetActorVar, ACTOR_SELF, 3, LVar0)
    EVT_ADD(LVar0, 1)
    EVT_CALL(SetActorVar, ACTOR_SELF, 3, LVar0)
    EVT_GOTO(0)
    EVT_RETURN
    EVT_END
};

EvtScript N(set_squad_animation) = {
    EVT_SET(LVar2, 2)
    EVT_CALL(GetActorVar, ACTOR_SELF, 3, LVar0)
    EVT_LOOP(15)
        EVT_IF_EQ(LVar0, 0)
            EVT_CALL(SetAnimation, ACTOR_SELF, LVar2, LVar1)
        EVT_ELSE
            EVT_SUB(LVar0, 1)
        EVT_END_IF
        EVT_ADD(LVar2, 1)
    EVT_END_LOOP
    EVT_RETURN
    EVT_END
};

EvtScript N(80233E48) = {
    EVT_IF_NE(LVar1, -1)
        EVT_CALL(SetAnimation, ACTOR_SELF, LVar0, LVar1)
        EVT_WAIT(10)
    EVT_END_IF
    EVT_CALL(func_80269E80, LVar5)
    EVT_SWITCH(LVar5)
        EVT_CASE_OR_EQ(10)
        EVT_CASE_OR_EQ(14)
        EVT_CASE_OR_EQ(12)
        EVT_CASE_OR_EQ(16)
        EVT_CASE_OR_EQ(11)
        EVT_CASE_OR_EQ(15)
        EVT_CASE_OR_EQ(13)
        EVT_CASE_OR_EQ(17)
        EVT_CASE_OR_EQ(2)
        EVT_END_CASE_GROUP
        EVT_CASE_DEFAULT
            EVT_SET(LVar2, 0)
            EVT_LOOP(24)
                EVT_CALL(SetPartRotation, ACTOR_SELF, LVar0, 0, LVar2, 0)
                EVT_ADD(LVar2, 30)
                EVT_WAIT(1)
            EVT_END_LOOP
    EVT_END_SWITCH
    EVT_SET(LVar3, 0)
    EVT_LOOP(12)
        EVT_CALL(SetPartRotation, ACTOR_SELF, LVar0, LVar3, 0, 0)
        EVT_ADD(LVar3, 8)
        EVT_WAIT(1)
    EVT_END_LOOP
    EVT_CALL(SetPartFlagBits, ACTOR_SELF, LVar0, ACTOR_PART_FLAG_INVISIBLE, 1)
    EVT_CALL(RemovePartShadow, ACTOR_SELF, LVar0)
    EVT_RETURN
    EVT_END
};

EvtScript N(onDeath) = {
    EVT_SET_CONST(LVar0, 2)
    EVT_LOOP(14)
        EVT_CALL(GetActorVar, ACTOR_SELF, 3, LVar2)
        EVT_CALL(GetActorVar, ACTOR_SELF, 4, LVar3)
        EVT_ADD(LVar2, 2)
        EVT_ADD(LVar2, LVar3)
        EVT_IF_GE(LVar0, LVar2)
            EVT_THREAD
                EVT_EXEC_WAIT(N(80233E48))
            EVT_END_THREAD
        EVT_END_IF
        EVT_ADD(LVar0, 1)
    EVT_END_LOOP
    EVT_SET(LVar0, 16)
    EVT_CALL(SetAnimation, ACTOR_SELF, LVar0, LVar1)
    EVT_SET(LVar2, 0)
    EVT_LOOP(24)
        EVT_CALL(SetPartRotation, ACTOR_SELF, LVar0, 0, LVar2, 0)
        EVT_ADD(LVar2, 30)
        EVT_WAIT(1)
    EVT_END_LOOP
    EVT_CALL(GetPartOffset, ACTOR_SELF, LVar0, LVar1, LVar2, LVar3)
    EVT_CALL(PlayEffect, EFFECT_BIG_SMOKE_PUFF, LVar1, LVar2, LVar3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)
    EVT_CALL(DropStarPoints, ACTOR_SELF)
    EVT_SET(LVar3, 0)
    EVT_LOOP(12)
        EVT_CALL(SetPartRotation, ACTOR_SELF, LVar0, LVar3, 0, 0)
        EVT_ADD(LVar3, 8)
        EVT_WAIT(1)
    EVT_END_LOOP
    EVT_CALL(SetPartFlagBits, ACTOR_SELF, LVar0, ACTOR_PART_FLAG_INVISIBLE, 1)
    EVT_CALL(RemovePartShadow, ACTOR_SELF, LVar0)
    EVT_WAIT(30)
    EVT_EXEC_WAIT(N(next_phase))
    EVT_CALL(RemoveActor, ACTOR_SELF)
    EVT_RETURN
    EVT_END
};

EvtScript N(takeTurn) = {
    EVT_CALL(GetCurrentPartnerID, LVar0)
    EVT_IF_EQ(LVar0, PARTNER_WATT)
        EVT_CALL(GetEnemyMaxHP, ACTOR_SELF, LVar0)
        EVT_CALL(GetActorHP, ACTOR_SELF, LVar1)
        EVT_IF_EQ(LVar0, LVar1)
            EVT_EXEC_WAIT(N(attack))
        EVT_ELSE
            EVT_EXEC_WAIT(N(run_away))
            EVT_EXEC_WAIT(N(next_phase))
            EVT_CALL(RemoveActor, ACTOR_SELF)
            EVT_RETURN
        EVT_END_IF
    EVT_ELSE
        EVT_EXEC_WAIT(N(attack))
    EVT_END_IF
    EVT_RETURN
    EVT_END
};

EvtScript N(next_phase) = {
    EVT_CALL(func_8026BF48, 1)
    EVT_CALL(SetActorVar, ACTOR_ENEMY1, 4, 1)
    EVT_RETURN
    EVT_END
};

EvtScript N(run_away) = {
    EVT_CALL(SetActorVar, ACTOR_SELF, 15, 0)
    EVT_CALL(UseIdleAnimation, ACTOR_SELF, FALSE)
    EVT_CALL(UseBattleCamPreset, BTL_CAM_PRESET_C)
    EVT_CALL(MoveBattleCamOver, 40)
    EVT_SET(LVar0, 2)
    EVT_SET(LVar1, 0)
    EVT_LOOP(15)
        EVT_CALL(GetActorVar, ACTOR_SELF, 3, LVar2)
        EVT_ADD(LVar2, 2)
        EVT_IF_GE(LVar0, LVar2)
            EVT_CALL(SetActorVar, ACTOR_SELF, 15, 1)
            EVT_THREAD
                EVT_WAIT(LVar1)
                EVT_CALL(SetAnimation, ACTOR_SELF, LVar0, ANIM_TankGuy_Anim03)
                EVT_CALL(SetPartYaw, ACTOR_SELF, LVar0, 180)
                EVT_CALL(RunPartTo, ACTOR_SELF, LVar0, 55, 0, 47, 20)
                EVT_CALL(RunPartTo, ACTOR_SELF, LVar0, 185, 0, 47, 30)
                EVT_IF_EQ(LVar0, 16)
                    EVT_CALL(SetActorVar, ACTOR_SELF, 15, 2)
                EVT_END_IF
            EVT_END_THREAD
            EVT_ADD(LVar1, 5)
        EVT_END_IF
        EVT_ADD(LVar0, 1)
    EVT_END_LOOP
    EVT_CALL(GetActorVar, ACTOR_SELF, 15, LVar0)
    EVT_IF_EQ(LVar0, 0)
        EVT_CALL(SetActorVar, ACTOR_SELF, 15, 2)
    EVT_END_IF
    EVT_SET(LVar0, 15)
    EVT_LOOP(0)
        EVT_CALL(GetActorVar, ACTOR_SELF, 15, LVar0)
        EVT_IF_EQ(LVar0, 2)
            EVT_BREAK_LOOP
        EVT_END_IF
        EVT_WAIT(1)
    EVT_END_LOOP
    EVT_RETURN
    EVT_END
};

EvtScript N(attack) = {
    EVT_CALL(UseIdleAnimation, ACTOR_SELF, FALSE)
    EVT_CALL(EnableIdleScript, ACTOR_SELF, 0)
    EVT_CALL(SetTargetActor, ACTOR_SELF, ACTOR_PLAYER)
    EVT_CALL(SetGoalToTarget, ACTOR_SELF)
    EVT_CALL(UseBattleCamPreset, BTL_CAM_PRESET_63)
    EVT_CALL(SetBattleCamZoom, 300)
    EVT_CALL(BattleCamTargetActor, ACTOR_SELF)
    EVT_CALL(MoveBattleCamOver, 30)
    EVT_SET(LVar0, 2)
    EVT_SET(LVar1, ANIM_TankGuy_Anim03)
    EVT_LOOP(15)
        EVT_THREAD
            EVT_CALL(GetActorPos, ACTOR_PLAYER, LVar2, LVar5, LVar3)
            EVT_CALL(GetPartMovementVar, ACTOR_SELF, LVar0, 4, LVar5)
            EVT_ADD(LVar2, LVar5)
            EVT_CALL(GetPartMovementVar, ACTOR_SELF, LVar0, 5, LVar5)
            EVT_ADD(LVar3, LVar5)
            EVT_SETF(LVar4, EVT_FLOAT(6.0))
            EVT_SET(LVar5, 30)
            EVT_EXEC_WAIT(N(move_guy_to_pos))
        EVT_END_THREAD
        EVT_ADD(LVar0, 1)
    EVT_END_LOOP
    EVT_CALL(SetActorSpeed, ACTOR_SELF, EVT_FLOAT(6.0))
    EVT_CALL(GetGoalPos, ACTOR_PLAYER, LVar2, LVar5, LVar3)
    EVT_CALL(GetPartMovementVar, ACTOR_SELF, 2, 4, LVar5)
    EVT_ADD(LVar2, LVar5)
    EVT_CALL(GetPartMovementVar, ACTOR_SELF, 2, 5, LVar5)
    EVT_ADD(LVar3, LVar5)
    EVT_CALL(SetGoalPos, ACTOR_SELF, LVar2, 0, LVar3)
    EVT_CALL(RunToGoal, ACTOR_SELF, 30, FALSE)
    EVT_SET(LVar0, 2)
    EVT_LOOP(15)
        EVT_CALL(GetActorPos, ACTOR_PLAYER, LVar4, LVar5, LVar6)
        EVT_CALL(GetPartOffset, ACTOR_SELF, LVar0, LVar1, LVar2, LVar3)
        EVT_IF_LT(LVar1, LVar4)
            EVT_CALL(SetPartYaw, ACTOR_SELF, LVar0, 180)
        EVT_ELSE
            EVT_CALL(SetPartYaw, ACTOR_SELF, LVar0, 0)
        EVT_END_IF
        EVT_CALL(RandInt, 100, LVar7)
        EVT_IF_LT(LVar7, 50)
            EVT_SET(LVar7, ANIM_TankGuy_Anim04)
        EVT_ELSE
            EVT_SET(LVar7, ANIM_TankGuy_Anim07)
        EVT_END_IF
        EVT_CALL(SetAnimation, ACTOR_SELF, LVar0, LVar7)
        EVT_ADD(LVar0, 1)
    EVT_END_LOOP
    EVT_CALL(EnemyTestTarget, ACTOR_SELF, LVarA, 0, 0, 1, BS_FLAGS1_10)
    EVT_SWITCH(LVarA)
        EVT_CASE_OR_EQ(HIT_RESULT_MISS)
        EVT_CASE_OR_EQ(HIT_RESULT_LUCKY)
            EVT_IF_EQ(LVarA, HIT_RESULT_LUCKY)
                EVT_CALL(EnemyTestTarget, ACTOR_SELF, LVar0, DAMAGE_TYPE_TRIGGER_LUCKY, 0, 0, 0)
            EVT_END_IF
            EVT_CALL(GetActorVar, ACTOR_SELF, 3, LVar0)
            EVT_IF_LT(LVar0, 14)
                EVT_CALL(GetActorPos, ACTOR_PLAYER, LVar0, LVar1, LVar2)
                EVT_CALL(PlayEffect, EFFECT_LANDING_DUST, 3, LVar0, LVar1, LVar2, 0, 0, 0, 0, 0, 0, 0, 0, 0)
                EVT_THREAD
                    EVT_LOOP(7)
                        EVT_CALL(PlayEffect, EFFECT_LANDING_DUST, 0, LVar0, LVar1, LVar2, 0, 0, 0, 0, 0, 0, 0, 0, 0)
                        EVT_WAIT(2)
                        EVT_CALL(PlayEffect, EFFECT_LANDING_DUST, 1, LVar0, LVar1, LVar2, 0, 0, 0, 0, 0, 0, 0, 0, 0)
                        EVT_WAIT(2)
                    EVT_END_LOOP
                EVT_END_THREAD
            EVT_END_IF
            EVT_WAIT(36)
            EVT_CALL(UseBattleCamPreset, BTL_CAM_PRESET_C)
            EVT_CALL(MoveBattleCamOver, 30)
            EVT_EXEC_WAIT(N(run_squad_to_pos))
            EVT_SET(LVar1, ANIM_TankGuy_Anim01)
            EVT_EXEC_WAIT(N(set_squad_animation))
            EVT_CALL(EnableIdleScript, ACTOR_SELF, 1)
            EVT_CALL(UseIdleAnimation, ACTOR_SELF, TRUE)
            EVT_RETURN
        EVT_END_CASE_GROUP
        EVT_CASE_EQ(HIT_RESULT_HIT_STATIC)
            EVT_CALL(EnemyDamageTarget, ACTOR_SELF, LVarF, 0, 0, 0, 1, BS_FLAGS1_SP_EVT_ACTIVE)
    EVT_END_SWITCH
    EVT_SET(LVarE, 15)
    EVT_CALL(GetActorVar, ACTOR_SELF, 3, LVar0)
    EVT_SUB(LVarE, LVar0)
    EVT_SET(LVarD, LVarE)
    EVT_LOOP(LVarD)
        EVT_IF_GT(LVarE, 1)
            EVT_SET(LVar0, BS_FLAGS1_40)
        EVT_ELSE
            EVT_SET(LVar0, BS_FLAGS1_SP_EVT_ACTIVE)
        EVT_END_IF
        EVT_CALL(SetGoalToTarget, ACTOR_SELF)
        EVT_CALL(EnemyDamageTarget, ACTOR_SELF, LVarF, 0, 0, 0, 1, LVar0)
        EVT_THREAD
            EVT_CALL(GetActorPos, ACTOR_PLAYER, LVar1, LVar2, LVar3)
            EVT_CALL(PlayEffect, EFFECT_LANDING_DUST, 0, LVar1, LVar2, LVar3, 0, 0, 0, 0, 0, 0, 0, 0, 0)
            EVT_WAIT(2)
            EVT_CALL(PlayEffect, EFFECT_LANDING_DUST, 1, LVar1, LVar2, LVar3, 0, 0, 0, 0, 0, 0, 0, 0, 0)
            EVT_WAIT(2)
        EVT_END_THREAD
        EVT_CALL(GetPlayerHP, LVar0)
        EVT_IF_EQ(LVar0, 0)
            EVT_BREAK_LOOP
        EVT_END_IF
        EVT_SUB(LVarE, 1)
        EVT_IF_EQ(LVarE, 0)
            EVT_BREAK_LOOP
        EVT_END_IF
        EVT_WAIT(10)
    EVT_END_LOOP
    EVT_CALL(UseBattleCamPreset, BTL_CAM_PRESET_C)
    EVT_CALL(MoveBattleCamOver, 30)
    EVT_WAIT(20)
    EVT_EXEC_WAIT(N(run_squad_to_pos))
    EVT_SET(LVar1, ANIM_TankGuy_Anim01)
    EVT_EXEC_WAIT(N(set_squad_animation))
    EVT_CALL(EnableIdleScript, ACTOR_SELF, 1)
    EVT_CALL(UseIdleAnimation, ACTOR_SELF, TRUE)
    EVT_RETURN
    EVT_END
};

EvtScript N(run_squad_to_pos) = {
    EVT_SET(LVar0, 2)
    EVT_SET(LVar1, ANIM_TankGuy_Anim03)
    EVT_LOOP(15)
        EVT_THREAD
            EVT_CALL(SetGoalToHome, ACTOR_SELF)
            EVT_CALL(GetGoalPos, ACTOR_SELF, LVar2, LVar5, LVar3)
            EVT_CALL(GetPartMovementVar, ACTOR_SELF, LVar0, 4, LVar5)
            EVT_ADD(LVar2, LVar5)
            EVT_CALL(GetPartMovementVar, ACTOR_SELF, LVar0, 5, LVar5)
            EVT_ADD(LVar3, LVar5)
            EVT_SETF(LVar4, EVT_FLOAT(6.0))
            EVT_SET(LVar5, 30)
            EVT_EXEC_WAIT(N(move_guy_to_pos))
            EVT_CALL(SetAnimation, ACTOR_SELF, LVar0, ANIM_TankGuy_Anim01)
            EVT_CALL(SetPartYaw, ACTOR_SELF, LVar0, 0)
        EVT_END_THREAD
        EVT_ADD(LVar0, 1)
    EVT_END_LOOP
    EVT_CALL(SetActorSpeed, ACTOR_SELF, EVT_FLOAT(6.0))
    EVT_CALL(SetGoalToHome, ACTOR_SELF)
    EVT_CALL(GetGoalPos, ACTOR_SELF, LVar2, LVar5, LVar3)
    EVT_CALL(GetPartMovementVar, ACTOR_SELF, 2, 4, LVar5)
    EVT_ADD(LVar2, LVar5)
    EVT_CALL(GetPartMovementVar, ACTOR_SELF, 2, 5, LVar5)
    EVT_ADD(LVar3, LVar5)
    EVT_CALL(SetGoalPos, ACTOR_SELF, LVar2, 0, LVar3)
    EVT_CALL(RunToGoal, ACTOR_SELF, 30, FALSE)
    EVT_RETURN
    EVT_END
};
