#include "tik_04.h"

#include "world/common/enemy/complete/SpikedGloomba_Wander.inc.c"

EvtScript N(EVS_NpcIdle_SpikedGloomba) = {
    EVT_CALL(GetEntryID, LVar0)
    EVT_SWITCH(LVar0)
        EVT_CASE_EQ(tik_04_ENTRY_0)
            EVT_CALL(SetNpcPos, NPC_SELF, 280, -10, 0)
        EVT_CASE_EQ(tik_04_ENTRY_1)
            EVT_CALL(BindNpcAI, NPC_SELF, EVT_PTR(N(EVS_NpcAI_SpikedGloomba_Wander)))
            EVT_RETURN
        EVT_CASE_EQ(tik_04_ENTRY_2)
            EVT_CALL(SetNpcPos, NPC_SELF, 280, -10, 0)
        EVT_CASE_EQ(tik_04_ENTRY_3)
            EVT_CALL(SetNpcPos, NPC_SELF, 360, -10, 0)
    EVT_END_SWITCH
    EVT_LABEL(100)
    EVT_CALL(GetPlayerPos, LVar0, LVar1, LVar2)
    EVT_IF_LT(LVar0, -30)
        EVT_WAIT(1)
        EVT_GOTO(100)
    EVT_END_IF
    EVT_CALL(SetNpcAnimation, NPC_SELF, ANIM_SpikedGoomba_Dark_Run)
    EVT_CALL(SetNpcFlagBits, NPC_SELF, NPC_FLAG_ENABLE_HIT_SCRIPT | NPC_FLAG_NO_AI, FALSE)
    EVT_CALL(SetNpcFlagBits, NPC_SELF, NPC_FLAG_GRAVITY, TRUE)
    EVT_CALL(SetNpcSpeed, NPC_SELF, 2)
    EVT_CALL(GetSelfNpcID, LVar0)
    EVT_IF_EQ(LVar0, 0)
        EVT_CALL(NpcMoveTo, NPC_SELF, 55, 0, 0)
    EVT_ELSE
        EVT_WAIT(14)
        EVT_CALL(NpcMoveTo, NPC_SELF, 60, 0, 0)
    EVT_END_IF
    EVT_CALL(SetNpcAnimation, NPC_SELF, ANIM_SpikedGoomba_Dark_Idle)
    EVT_CALL(BindNpcAI, NPC_SELF, EVT_PTR(N(EVS_NpcAI_SpikedGloomba_Wander)))
    EVT_RETURN
    EVT_END
};

EvtScript N(EVS_NpcInit_SpikedGloomba) = {
    EVT_CALL(BindNpcIdle, NPC_SELF, EVT_PTR(N(EVS_NpcIdle_SpikedGloomba)))
    EVT_RETURN
    EVT_END
};

StaticNpc N(NpcData_SpikedGloomba_01) = {
    .id = NPC_SpikedGoomba_01,
    .settings = &N(NpcSettings_SpikedGloomba_Wander),
    .pos = { 40.0f, -135.0f, 10.0f },
    .yaw = 270,
    .flags = ENEMY_FLAGS_400,
    .init = &N(EVS_NpcInit_SpikedGloomba),
    .drops = SPIKED_GLOOMBA_DROPS,
    .territory = {
        .wander = {
            .isFlying = FALSE,
            .moveSpeedOverride = NO_OVERRIDE_MOVEMENT_SPEED,
            .wanderShape = SHAPE_CYLINDER,
            .centerPos  = { 40, -135, 10 },
            .wanderSize = { 30 },
            .detectShape = SHAPE_CYLINDER,
            .detectPos  = { 40, -135, 10 },
            .detectSize = { 200 },
        }
    },
    .animations = SPIKED_GLOOMBA_ANIMS,
};

StaticNpc N(NpcData_SpikedGloomba_02) = {
    .id = NPC_SpikedGoomba_02,
    .settings = &N(NpcSettings_SpikedGloomba_Wander),
    .pos = { 141.0f, -135.0f, 85.0f },
    .yaw = 270,
    .flags = ENEMY_FLAGS_400,
    .init = &N(EVS_NpcInit_SpikedGloomba),
    .drops = SPIKED_GLOOMBA_DROPS,
    .territory = {
        .wander = {
            .isFlying = FALSE,
            .moveSpeedOverride = NO_OVERRIDE_MOVEMENT_SPEED,
            .wanderShape = SHAPE_CYLINDER,
            .centerPos  = { 141, -135, 85 },
            .wanderSize = { 30 },
            .detectShape = SHAPE_CYLINDER,
            .detectPos  = { 141, -135, 85 },
            .detectSize = { 200 },
        }
    },
    .animations = SPIKED_GLOOMBA_ANIMS,
};

NpcGroupList N(DefaultNPCs) = {
    NPC_GROUP(N(NpcData_SpikedGloomba_01), BTL_TIK_FORMATION_0F, BTL_TIK_STAGE_01),
    NPC_GROUP(N(NpcData_SpikedGloomba_02), BTL_TIK_FORMATION_0E, BTL_TIK_STAGE_01),
    {}
};
