#include "flo_25.h"

#include "common/foliage.inc.c"

FoliageModelList N(Tree1_LeafModels) = {
    .count = 3,
    .models = {
        MODEL_o43,
        MODEL_o44,
        MODEL_o45,
    }
};

FoliageModelList N(Tree1_TrunkModels) = {
    .count = 1,
    .models = {
        MODEL_o42,
    }
};

FoliageDropList N(Tree1_Drops) = {
    .count = 2, 
    .drops = {
        {
            .itemID = ITEM_YELLOW_BERRY,
            .pos = { -432, 84, -44 },
            .spawnMode = ITEM_SPAWN_MODE_FALL_SPAWN_ALWAYS,
            .spawnFlag = AF_FLO_TreeDrop_YellowBerry1,
        },
        {
            .itemID = ITEM_YELLOW_BERRY,
            .pos = { -346, 72, -114 },
            .spawnMode = ITEM_SPAWN_MODE_FALL_SPAWN_ALWAYS,
            .spawnFlag = AF_FLO_TreeDrop_YellowBerry2,
        },
    }
};

ShakeTreeConfig N(ShakeTree_Tree1) = {
    .leaves = &N(Tree1_LeafModels),
    .trunk = &N(Tree1_TrunkModels),
    .drops = &N(Tree1_Drops),
};

BombTrigger N(BombPos_Tree1) = {
    .pos = { -388.0f, 0.0f, -92.0f },
    .radius = 0.0f
};

EvtScript N(EVS_SetupFoliage) = {
    EVT_SET(AF_FLO_TreeDrop_YellowBerry1, FALSE)
    EVT_SET(AF_FLO_TreeDrop_YellowBerry2, FALSE)
    EVT_SET(LVar0, EVT_PTR(N(ShakeTree_Tree1)))
    EVT_BIND_TRIGGER(EVT_PTR(N(EVS_ShakeTree)), TRIGGER_WALL_HAMMER, COLLIDER_o42, 1, 0)
    EVT_BIND_TRIGGER(EVT_PTR(N(EVS_ShakeTree)), TRIGGER_POINT_BOMB, EVT_PTR(N(BombPos_Tree1)), 1, 0)
    EVT_RETURN
    EVT_END
};
