#include "kzn_11.h"

#include "world/common/enemy/complete/LavaBubble.inc.c"

#include "sprite/npc/Fire.h"
#include "world/common/enemy/ai/FireBarAI.inc.c"

s32 N(FireBar_Sounds)[] = {
    SOUND_FIRE_BAR_0, SOUND_FIRE_BAR_1, SOUND_FIRE_BAR_2, SOUND_FIRE_BAR_3,
    SOUND_FIRE_BAR_4, SOUND_FIRE_BAR_5, SOUND_FIRE_BAR_6, SOUND_FIRE_BAR_7,
    SOUND_FIRE_BAR_8, SOUND_FIRE_BAR_9, SOUND_FIRE_BAR_9,
};

EvtScript N(EVS_FireBar_Defeated) = {
    EVT_SET(LVarA, LVar0)
    EVT_SET(LVarB, LVar1)
    EVT_LOOP(15)
        EVT_LOOP(LVar1)
            EVT_CALL(SetNpcFlagBits, LVar0, NPC_FLAG_2, TRUE)
            EVT_ADD(LVar0, 1)
        EVT_END_LOOP
        EVT_WAIT(1)
        EVT_SET(LVar0, LVarA)
        EVT_SET(LVar1, LVarB)
        EVT_LOOP(LVar1)
            EVT_CALL(SetNpcFlagBits, LVar0, NPC_FLAG_2, FALSE)
            EVT_ADD(LVar0, 1)
        EVT_END_LOOP
        EVT_WAIT(1)
        EVT_SET(LVar0, LVarA)
        EVT_SET(LVar1, LVarB)
    EVT_END_LOOP
    EVT_CALL(GetNpcPos, LVar0, LVar1, LVar2, LVar3)
    EVT_CALL(PlaySoundAt, SOUND_B000000A, 0, LVar1, LVar2, LVar3)
    EVT_LOOP(10)
        EVT_CALL(GetNpcPos, LVar0, LVar1, LVar2, LVar3)
        EVT_CALL(RandInt, 50, LVar4)
        EVT_SUB(LVar4, 25)
        EVT_CALL(RandInt, 30, LVar5)
        EVT_ADD(LVar1, LVar4)
        EVT_ADD(LVar2, LVar5)
        EVT_PLAY_EFFECT(EFFECT_00, LVar1, LVar2, LVar3, 1, 20, 3, 2)
    EVT_END_LOOP
    EVT_IF_EQ(LVarA, NPC_FireBar_1A)
        EVT_IF_EQ(AF_KZN11_FireBar1_Coins, FALSE)
            EVT_SET(AF_KZN11_FireBar1_Coins, TRUE)
            EVT_LOOP(10)
                EVT_CALL(MakeItemEntity, ITEM_COIN, LVar1, LVar2, LVar3, ITEM_SPAWN_MODE_TOSS_SPAWN_ALWAYS, 0)
            EVT_END_LOOP
        EVT_END_IF
    EVT_END_IF
    EVT_IF_EQ(LVarA, NPC_FireBar_2A)
        EVT_IF_EQ(AF_KZN11_FireBar2_Coins, FALSE)
            EVT_SET(AF_KZN11_FireBar2_Coins, TRUE)
            EVT_LOOP(10)
                EVT_CALL(MakeItemEntity, ITEM_COIN, LVar1, LVar2, LVar3, ITEM_SPAWN_MODE_TOSS_SPAWN_ALWAYS, 0)
            EVT_END_LOOP
        EVT_END_IF
    EVT_END_IF
    EVT_IF_EQ(LVarA, NPC_FireBar_3A)
        EVT_IF_EQ(AF_KZN11_FireBar3_Coins, FALSE)
            EVT_SET(AF_KZN11_FireBar3_Coins, TRUE)
            EVT_LOOP(10)
                EVT_CALL(MakeItemEntity, ITEM_COIN, LVar1, LVar2, LVar3, ITEM_SPAWN_MODE_TOSS_SPAWN_ALWAYS, 0)
            EVT_END_LOOP
        EVT_END_IF
    EVT_END_IF
    EVT_CALL(RemoveEncounter, LVarA)
    EVT_RETURN
    EVT_END
};

FireBarAISettings N(AISettings_FireBar_01) = {
    .centerPos = { -300, 20, 15 },
    .rotationRate = 8,
    .firstNpc = NPC_FireBar_1A,
    .npcCount = 4,
    .callback = N(FireBarAI_Callback),
};

FireBarAISettings N(AISettings_FireBar_02) = {
    .centerPos = { 0, 20, 15 },
    .rotationRate = -8,
    .firstNpc = NPC_FireBar_2A,
    .npcCount = 4,
    .callback = N(FireBarAI_Callback),
};

FireBarAISettings N(AISettings_FireBar_03) = {
    .centerPos = { 325, 20, 15 },
    .rotationRate = -8,
    .firstNpc = NPC_FireBar_3A,
    .npcCount = 4,
    .callback = N(FireBarAI_Callback),
};

EvtScript N(EVS_NpcAI_FireBar_01) = {
    EVT_CALL(N(FireBarAI_Main), EVT_PTR(N(AISettings_FireBar_01)))
    EVT_RETURN
    EVT_END
};

EvtScript N(EVS_NpcAI_FireBar_02) = {
    EVT_CALL(N(FireBarAI_Main), EVT_PTR(N(AISettings_FireBar_02)))
    EVT_RETURN
    EVT_END
};

EvtScript N(EVS_NpcAI_FireBar_03) = {
    EVT_CALL(N(FireBarAI_Main), EVT_PTR(N(AISettings_FireBar_03)))
    EVT_RETURN
    EVT_END
};

NpcSettings N(NpcSettings_FireBar_01) = {
    .defaultAnim = ANIM_Fire_Brighest_Burn,
    .height = 12,
    .radius = 20,
    .ai = &N(EVS_NpcAI_FireBar_01),
    .flags = ENEMY_FLAGS_100 | ENEMY_FLAGS_200 | ENEMY_FLAGS_400 | ENEMY_FLAGS_800,
};

NpcSettings N(NpcSettings_FireBar_02) = {
    .defaultAnim = ANIM_Fire_Brighest_Burn,
    .height = 12,
    .radius = 20,
    .ai = &N(EVS_NpcAI_FireBar_02),
    .flags = ENEMY_FLAGS_100 | ENEMY_FLAGS_200 | ENEMY_FLAGS_400 | ENEMY_FLAGS_800,
};

NpcSettings N(NpcSettings_FireBar_03) = {
    .defaultAnim = ANIM_Fire_Brighest_Burn,
    .height = 12,
    .radius = 20,
    .ai = &N(EVS_NpcAI_FireBar_03),
    .flags = ENEMY_FLAGS_100 | ENEMY_FLAGS_200 | ENEMY_FLAGS_400 | ENEMY_FLAGS_800,
};

NpcSettings N(NpcSettings_FireBar_Extra) = {
    .defaultAnim = ANIM_Fire_Brighest_Burn,
    .height = 12,
    .radius = 20,
    .flags = ENEMY_FLAGS_100 | ENEMY_FLAGS_200 | ENEMY_FLAGS_400 | ENEMY_FLAGS_800,
};

StaticNpc N(NpcData_FireBar_01)[] = {
    {
        .id = NPC_FireBar_1A,
        .settings = &N(NpcSettings_FireBar_01),
        .pos = { 0.0f, 0.0f, 0.0f },
        .yaw = 0,
        .flags = ENEMY_FLAGS_1,
        .init = (void*) 0x00004003,
        .animations = {
        },
    },
    {
        .id = NPC_FireBar_1B,
        .settings = &N(NpcSettings_FireBar_Extra),
        .pos = { 0.0f, 0.0f, 0.0f },
        .yaw = 0,
        .flags = ENEMY_FLAGS_1,
        .init = (void*) 0x00004003,
        .animations = {
        },
    },
    {
        .id = NPC_FireBar_1C,
        .settings = &N(NpcSettings_FireBar_Extra),
        .pos = { 0.0f, 0.0f, 0.0f },
        .yaw = 0,
        .flags = ENEMY_FLAGS_1,
        .init = (void*) 0x00004003,
        .animations = {
        },
    },
    {
        .id = NPC_FireBar_1D,
        .settings = &N(NpcSettings_FireBar_Extra),
        .pos = { 0.0f, 0.0f, 0.0f },
        .yaw = 0,
        .flags = ENEMY_FLAGS_1,
        .init = (void*) 0x00004003,
        .animations = {
        },
    },
};

StaticNpc N(NpcData_FireBar_02)[] = {
    {
        .id = NPC_FireBar_2A,
        .settings = &N(NpcSettings_FireBar_02),
        .pos = { 0.0f, 0.0f, 0.0f },
        .yaw = 0,
        .flags = ENEMY_FLAGS_1,
        .init = (void*) 0x00004003,
        .animations = {
        },
    },
    {
        .id = NPC_FireBar_2B,
        .settings = &N(NpcSettings_FireBar_Extra),
        .pos = { 0.0f, 0.0f, 0.0f },
        .yaw = 0,
        .flags = ENEMY_FLAGS_1,
        .init = (void*) 0x00004003,
        .animations = {
        },
    },
    {
        .id = NPC_FireBar_2C,
        .settings = &N(NpcSettings_FireBar_Extra),
        .pos = { 0.0f, 0.0f, 0.0f },
        .yaw = 0,
        .flags = ENEMY_FLAGS_1,
        .init = (void*) 0x00004003,
        .animations = {
        },
    },
    {
        .id = NPC_FireBar_2D,
        .settings = &N(NpcSettings_FireBar_Extra),
        .pos = { 0.0f, 0.0f, 0.0f },
        .yaw = 0,
        .flags = ENEMY_FLAGS_1,
        .init = (void*) 0x00004003,
        .animations = {
        },
    },
};

StaticNpc N(NpcData_FireBar_03)[] = {
    {
        .id = NPC_FireBar_3A,
        .settings = &N(NpcSettings_FireBar_03),
        .pos = { 0.0f, 0.0f, 0.0f },
        .yaw = 0,
        .flags = ENEMY_FLAGS_1,
        .init = (void*) 0x00004003,
        .animations = {
        },
    },
    {
        .id = NPC_FireBar_3B,
        .settings = &N(NpcSettings_FireBar_Extra),
        .pos = { 0.0f, 0.0f, 0.0f },
        .yaw = 0,
        .flags = ENEMY_FLAGS_1,
        .init = (void*) 0x00004003,
        .animations = {
        },
    },
    {
        .id = NPC_FireBar_3C,
        .settings = &N(NpcSettings_FireBar_Extra),
        .pos = { 0.0f, 0.0f, 0.0f },
        .yaw = 0,
        .flags = ENEMY_FLAGS_1,
        .init = (void*) 0x00004003,
        .animations = {
        },
    },
    {
        .id = NPC_FireBar_3D,
        .settings = &N(NpcSettings_FireBar_Extra),
        .pos = { 0.0f, 0.0f, 0.0f },
        .yaw = 0,
        .flags = ENEMY_FLAGS_1,
        .init = (void*) 0x00004003,
        .animations = {
        },
    },
};

StaticNpc N(NpcData_Bubble_01) = {
    .id = NPC_Bubble_01,
    .settings = &N(NpcSettings_LavaBubble),
    .pos = { -150.0f, 50.0f, 10.0f },
    .yaw = 90,
    .flags = ENEMY_FLAGS_400 | ENEMY_FLAGS_800,
    .drops = LAVA_BUBBLE_DROPS,
    .territory = {
        .wander = {
            .isFlying = TRUE,
            .moveSpeedOverride = NO_OVERRIDE_MOVEMENT_SPEED,
            .wanderShape = SHAPE_CYLINDER,
            .centerPos  = { -150, 50, 10 },
            .wanderSize = { 30 },
            .detectShape = SHAPE_CYLINDER,
            .detectPos  = { -150, 50, 10 },
            .detectSize = { 150 },
        }
    },
    .animations = LAVA_BUBBLE_ANIMS,
    .aiDetectFlags = AI_DETECT_SENSITIVE_MOTION,
};

StaticNpc N(NpcData_Bubble_02) = {
    .id = NPC_Bubble_02,
    .settings = &N(NpcSettings_LavaBubble),
    .pos = { 150.0f, 50.0f, 10.0f },
    .yaw = 270,
    .flags = ENEMY_FLAGS_400 | ENEMY_FLAGS_800,
    .drops = LAVA_BUBBLE_DROPS,
    .territory = {
        .wander = {
            .isFlying = TRUE,
            .moveSpeedOverride = NO_OVERRIDE_MOVEMENT_SPEED,
            .wanderShape = SHAPE_CYLINDER,
            .centerPos  = { 150, 50, 10 },
            .wanderSize = { 30 },
            .detectShape = SHAPE_CYLINDER,
            .detectPos  = { 150, 50, 10 },
            .detectSize = { 150 },
        }
    },
    .animations = LAVA_BUBBLE_ANIMS,
    .aiDetectFlags = AI_DETECT_SENSITIVE_MOTION,
};

NpcGroupList N(DefaultNPCs) = {
    NPC_GROUP(N(NpcData_FireBar_01)),
    NPC_GROUP(N(NpcData_FireBar_02)),
    NPC_GROUP(N(NpcData_FireBar_03)),
    NPC_GROUP(N(NpcData_Bubble_01), 0x1800, BTL_KZN_STAGE_02),
    NPC_GROUP(N(NpcData_Bubble_02), 0x1807, BTL_KZN_STAGE_02),
    {}
};
