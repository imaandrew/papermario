#include "kmr_30.h"

NpcSettings N(NpcSettings_ParadePeach) = {
    .height = 46,
    .radius = 36,
    .level = 99,
};

StaticNpc N(NpcData_ParadePeach) = {
    .id = NPC_ParadePeach,
    .settings = &N(NpcSettings_ParadePeach),
    .pos = { NPC_DISPOSE_LOCATION },
    .yaw = 270,
    .flags = ENEMY_FLAGS_1 | ENEMY_FLAGS_4 | ENEMY_FLAGS_8 | ENEMY_FLAGS_100 | ENEMY_FLAGS_200 | ENEMY_FLAGS_400 | ENEMY_FLAGS_800,
    .drops = {
        .dropFlags = NPC_DROP_FLAGS_80,
        .heartDrops  = NO_DROPS,
        .flowerDrops = NO_DROPS,
    },
    .animations = {
        .idle   = ANIM_ParadePeach_IdleRaisedArms,
        .walk   = ANIM_ParadePeach_IdleRaisedArms,
        .run    = ANIM_ParadePeach_IdleRaisedArms,
        .chase  = ANIM_ParadePeach_IdleRaisedArms,
        .anim_4 = ANIM_ParadePeach_IdleRaisedArms,
        .anim_5 = ANIM_ParadePeach_IdleRaisedArms,
        .death  = ANIM_ParadePeach_IdleRaisedArms,
        .hit    = ANIM_ParadePeach_IdleRaisedArms,
        .anim_8 = ANIM_ParadePeach_IdleRaisedArms,
        .anim_9 = ANIM_ParadePeach_IdleRaisedArms,
        .anim_A = ANIM_ParadePeach_IdleRaisedArms,
        .anim_B = ANIM_ParadePeach_IdleRaisedArms,
        .anim_C = ANIM_ParadePeach_IdleRaisedArms,
        .anim_D = ANIM_ParadePeach_IdleRaisedArms,
        .anim_E = ANIM_ParadePeach_IdleRaisedArms,
        .anim_F = ANIM_ParadePeach_IdleRaisedArms,
    },
};

NpcGroupList N(DefaultNPCs) = {
    NPC_GROUP(N(NpcData_ParadePeach)),
    {}
};
