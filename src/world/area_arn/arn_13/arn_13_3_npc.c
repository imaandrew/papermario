#include "arn_13.h"

#include "world/common/npc/TubbasHeart.inc.c"
#include "world/common/enemy/complete/HyperGoomba_Wander.inc.c"

EvtScript N(EVS_NpcIdle_TubbasHeart) = {
    EVT_CALL(SetNpcAnimation, NPC_SELF, ANIM_TubbasHeart_Anim13)
    EVT_CALL(SetNpcJumpscale, NPC_SELF, EVT_FLOAT(3.0))
    EVT_CALL(GetNpcPos, NPC_SELF, LVar0, LVar1, LVar2)
    EVT_SUB(LVar0, 30)
    EVT_CALL(PlaySoundAtNpc, NPC_SELF, SOUND_20C8, 0)
    EVT_CALL(NpcJump0, NPC_SELF, LVar0, 0, LVar2, 8)
    EVT_CALL(SetNpcAnimation, NPC_SELF, ANIM_TubbasHeart_Anim14)
    EVT_WAIT(1)
    EVT_CALL(SetNpcAnimation, NPC_SELF, ANIM_TubbasHeart_Anim13)
    EVT_SUB(LVar0, 80)
    EVT_CALL(SetNpcJumpscale, NPC_SELF, EVT_FLOAT(2.5))
    EVT_CALL(PlaySoundAtNpc, NPC_SELF, SOUND_20C8, 0)
    EVT_CALL(NpcJump0, NPC_SELF, LVar0, 0, LVar2, 12)
    EVT_CALL(SetNpcAnimation, NPC_SELF, ANIM_TubbasHeart_Anim14)
    EVT_WAIT(1)
    EVT_CALL(SetNpcAnimation, NPC_SELF, ANIM_TubbasHeart_Anim13)
    EVT_SUB(LVar0, 80)
    EVT_CALL(SetNpcJumpscale, NPC_SELF, EVT_FLOAT(2.5))
    EVT_CALL(PlaySoundAtNpc, NPC_SELF, SOUND_20C8, 0)
    EVT_CALL(NpcJump0, NPC_SELF, LVar0, 0, LVar2, 12)
    EVT_CALL(EnableNpcShadow, NPC_SELF, FALSE)
    EVT_CALL(SetNpcPos, NPC_SELF, 0, -1000, 0)
    EVT_SET(GB_StoryProgress, STORY_CH3_HEART_FLED_SECOND_TUNNEL)
    EVT_RETURN
    EVT_END
};

EvtScript N(EVS_NpcDefeat_HyperGoomba) = {
    EVT_SET(GF_ARN13_Defeated_Goomba, TRUE)
    EVT_CALL(DoNpcDefeat)
    EVT_RETURN
    EVT_END
};

EvtScript N(EVS_NpcInit_TubbasHeart) = {
    EVT_CALL(BindNpcIdle, NPC_SELF, EVT_PTR(N(EVS_NpcIdle_TubbasHeart)))
    EVT_IF_NE(GB_StoryProgress, STORY_CH3_HEART_FLED_FIRST_TUNNEL)
        EVT_CALL(RemoveNpc, NPC_SELF)
    EVT_END_IF
    EVT_RETURN
    EVT_END
};

EvtScript N(EVS_NpcInit_HyperGoomba) = {
    EVT_IF_LT(GB_StoryProgress, STORY_CH4_FRYING_PAN_STOLEN)
        EVT_IF_EQ(GF_ARN13_Defeated_Goomba, TRUE)
            EVT_CALL(RemoveNpc, NPC_SELF)
            EVT_RETURN
        EVT_END_IF
        EVT_CALL(BindNpcDefeat, NPC_SELF, EVT_PTR(N(EVS_NpcDefeat_HyperGoomba)))
    EVT_END_IF
    EVT_CALL(BindNpcDefeat, NPC_SELF, EVT_PTR(N(EVS_NpcDefeat_HyperGoomba)))
    EVT_RETURN
    EVT_END
};

StaticNpc N(NpcData_TubbasHeart) = {
    .id = NPC_TubbasHeart,
    .settings = &N(NpcSettings_TubbasHeart),
    .pos = { 80.0f, 50.0f, 0.0f },
    .yaw = 270,
    .flags = ENEMY_FLAGS_1 | ENEMY_FLAGS_4 | ENEMY_FLAGS_100 | ENEMY_FLAGS_400 | ENEMY_FLAGS_800,
    .init = &N(EVS_NpcInit_TubbasHeart),
    .drops = TUBBAS_HEART_DROPS,
    .animations = TUBBAS_HEART_ANIMS,
};

StaticNpc N(NpcData_HyperGoomba) = {
    .id = NPC_HyperGoomba,
    .settings = &N(NpcSettings_HyperGoomba),
    .pos = { 0.0f, 0.0f, 0.0f },
    .yaw = 270,
    .flags = ENEMY_FLAGS_400 | ENEMY_FLAGS_800,
    .init = &N(EVS_NpcInit_HyperGoomba),
    .drops = HYPER_GOOMBA_DROPS,
    .territory = {
        .wander = {
            .isFlying = TRUE,
            .moveSpeedOverride = NO_OVERRIDE_MOVEMENT_SPEED,
            .wanderShape = SHAPE_CYLINDER,
            .centerPos  = { 0, 0, 0 },
            .wanderSize = { 20 },
            .detectShape = SHAPE_CYLINDER,
            .detectPos  = { 0, 0, 0 },
            .detectSize = { 150 },
        }
    },
    .animations = HYPER_GOOMBA_ANIMS,
    .aiDetectFlags = AI_DETECT_SIGHT,
};

NpcGroupList N(DefaultNPCs) = {
    NPC_GROUP(N(NpcData_TubbasHeart)),
    NPC_GROUP(N(NpcData_HyperGoomba), BTL_ARN_FORMATION_02, BTL_ARN_STAGE_04),
    {}
};
