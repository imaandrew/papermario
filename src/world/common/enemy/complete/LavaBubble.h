#include "common.h"
#include "sprite/npc/LavaBubble.h"

#define LAVA_BUBBLE_DROPS \
{ \
    .dropFlags = NPC_DROP_FLAGS_80, \
    .itemDropChance = 5, \
    .itemDrops = { \
        { ITEM_SUPER_SHROOM, 10, 0 }, \
    }, \
    .heartDrops  = STANDARD_HEART_DROPS(2), \
    .flowerDrops = STANDARD_FLOWER_DROPS(2), \
    .minCoinBonus = 0, \
    .maxCoinBonus = 3, \
}

#define LAVA_BUBBLE_ANIMS \
{ \
    .idle   = ANIM_LavaBubble_Anim01, \
    .walk   = ANIM_LavaBubble_Anim02, \
    .run    = ANIM_LavaBubble_Anim03, \
    .chase  = ANIM_LavaBubble_Anim03, \
    .anim_4 = ANIM_LavaBubble_Anim01, \
    .anim_5 = ANIM_LavaBubble_Anim01, \
    .death  = ANIM_LavaBubble_Anim07, \
    .hit    = ANIM_LavaBubble_Anim07, \
    .anim_8 = ANIM_LavaBubble_Anim04, \
    .anim_9 = ANIM_LavaBubble_Anim01, \
    .anim_A = ANIM_LavaBubble_Anim01, \
    .anim_B = ANIM_LavaBubble_Anim01, \
    .anim_C = ANIM_LavaBubble_Anim01, \
    .anim_D = ANIM_LavaBubble_Anim01, \
    .anim_E = ANIM_LavaBubble_Anim01, \
    .anim_F = ANIM_LavaBubble_Anim01, \
}
