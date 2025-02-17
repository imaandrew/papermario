#include "dgb_09.h"

#define INCLUDE_CLUBBA_WANDER
#define INCLUDE_CLUBBA_NAPPING
#include "world/common/enemy/complete/Clubba_Multi.inc.c"

#define AI_SENTINEL_FIRST_NPC NPC_Sentinel
#define AI_SENTINEL_LAST_NPC  NPC_Sentinel
#include "world/common/enemy/complete/Sentinel.inc.c"

StaticNpc N(NpcData_Clubba_Wander)[] = {
    {
        .id = NPC_Clubba_Wander,
        .settings = &N(NpcSettings_Clubba_Wander),
        .pos = { -350.0f, 0.0f, 180.0f },
        .yaw = 270,
        .flags = ENEMY_FLAGS_100 | ENEMY_FLAGS_400 | ENEMY_FLAGS_800,
        .drops = CLUBBA_DROPS,
        .territory = {
            .wander = {
                .isFlying = TRUE,
                .moveSpeedOverride = NO_OVERRIDE_MOVEMENT_SPEED,
                .wanderShape = SHAPE_CYLINDER,
                .centerPos  = { -350, 0, 180 },
                .wanderSize = { 40 },
                .detectShape = SHAPE_RECT,
                .detectPos  = { 0, 0, 50 },
                .detectSize = { 600, 250 },
            }
        },
        .animations = CLUBBA_ANIMS,
        .extraAnimations = N(ExtraAnims_Clubba),
        .aiDetectFlags = AI_DETECT_SENSITIVE_MOTION,
    },
    CLUBBA_MACE_HITBOX(NPC_Clubba_Wander_Hitbox),
};

EvtScript N(EVS_NpcInit_Clubba_Napping) = {
    EVT_CALL(GetEntryID, LVar0)
    EVT_IF_EQ(LVar0, dgb_09_ENTRY_3)
        EVT_CALL(SetNpcPos, NPC_SELF, 240, 0, 88)
        EVT_CALL(InterpNpcYaw, NPC_SELF, 270, 0)
    EVT_END_IF
    EVT_RETURN
    EVT_END
};

StaticNpc N(NpcData_Clubba_Napping)[] = {
    {
        .id = NPC_Clubba_Napping,
        .settings = &N(NpcSettings_Clubba_Napping),
        .pos = { 310.0f, 0.0f, 88.0f },
        .yaw = 270,
        .flags = ENEMY_FLAGS_100 | ENEMY_FLAGS_400 | ENEMY_FLAGS_800,
        .init = &N(EVS_NpcInit_Clubba_Napping),
        .drops = CLUBBA_DROPS,
        .territory = {
            .wander = {
                .isFlying = TRUE,
                .moveSpeedOverride = NO_OVERRIDE_MOVEMENT_SPEED,
                .wanderShape = SHAPE_CYLINDER,
                .centerPos  = { 310, 0, 88 },
                .wanderSize = { 40 },
                .detectShape = SHAPE_RECT,
                .detectPos  = { 0, 0, 50 },
                .detectSize = { 600, 250 },
            }
        },
        .animations = CLUBBA_ANIMS,
        .extraAnimations = N(ExtraAnims_Clubba),
        .aiDetectFlags = AI_DETECT_SENSITIVE_MOTION,
    },
    CLUBBA_MACE_HITBOX(NPC_Clubba_Napping_Hitbox),
};

StaticNpc N(NpcData_Sentinel) = {
    .id = NPC_Sentinel,
    .settings = &N(NpcSettings_Sentinel),
    .pos = { -20.0f, 100.0f, 180.0f },
    .yaw = 90,
    .flags = ENEMY_FLAGS_400,
    .drops = SENTINEL_DROPS,
    .territory = {
        .wander = {
            .isFlying = TRUE,
            .moveSpeedOverride = NO_OVERRIDE_MOVEMENT_SPEED,
            .wanderShape = SHAPE_CYLINDER,
            .centerPos  = { -20, 100, 180 },
            .wanderSize = { 40 },
            .detectShape = SHAPE_CYLINDER,
            .detectPos  = { -20, 100, 180 },
            .detectSize = { 250 },
        }
    },
    .animations = SENTINEL_ANIMS,
};

NpcGroupList N(DefaultNPCs) = {
    NPC_GROUP(N(NpcData_Clubba_Wander), BTL_DGB_FORMATION_03, BTL_DGB_STAGE_00),
    NPC_GROUP(N(NpcData_Clubba_Napping), BTL_DGB_FORMATION_01, BTL_DGB_STAGE_00),
    NPC_GROUP(N(NpcData_Sentinel)),
    {}
};
