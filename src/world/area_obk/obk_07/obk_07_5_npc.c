#include "obk_07.h"

#include "world/common/npc/Boo.inc.c"

#define TRAFFIC_BOO_START_Y 80.0f
#define TRAFFIC_BOO_START_Z -300.0f
#include "../TrafficBoos.inc.c"

EvtScript N(EVS_NpcInit_TrafficBoo1) = {
    EVT_CALL(BindNpcIdle, NPC_SELF, EVT_PTR(N(EVS_NpcIdle_TrafficBoo)))
    EVT_RETURN
    EVT_END
};

StaticNpc N(NpcData_TrafficBoo1) = {
    .id = NPC_TrafficBoo1,
    .settings = &N(NpcSettings_Boo),
    .pos = { 523.0f, -139.0f, 193.0f },
    .yaw = 0,
    .flags = ENEMY_FLAGS_1 | ENEMY_FLAGS_100 | ENEMY_FLAGS_200 | ENEMY_FLAGS_400 | ENEMY_FLAGS_800,
    .init = &N(EVS_NpcInit_TrafficBoo1),
    .drops = BOO_DROPS,
    .animations = NORMAL_BOO_ANIMS,
};

EvtScript N(EVS_NpcInit_TrafficBoo2) = {
    EVT_CALL(BindNpcIdle, NPC_SELF, EVT_PTR(N(EVS_NpcIdle_TrafficBoo)))
    EVT_RETURN
    EVT_END
};

StaticNpc N(NpcData_TrafficBoo2) = {
    .id = NPC_TrafficBoo2,
    .settings = &N(NpcSettings_Boo),
    .pos = { 473.0f, -122.0f, 247.0f },
    .yaw = 0,
    .flags = ENEMY_FLAGS_1 | ENEMY_FLAGS_100 | ENEMY_FLAGS_200 | ENEMY_FLAGS_400 | ENEMY_FLAGS_800,
    .init = &N(EVS_NpcInit_TrafficBoo2),
    .drops = BOO_DROPS,
    .animations = NORMAL_BOO_ANIMS,
};

EvtScript N(EVS_NpcInit_GuardBoo) = {
    EVT_IF_GE(GB_StoryProgress, STORY_CH3_GOT_WEIGHT)
        EVT_SET(MV_GuardDeparted, TRUE)
        EVT_CALL(RemoveNpc, NPC_SELF)
    EVT_ELSE
        EVT_EXEC_WAIT(N(EVS_SetupGuardBoo))
    EVT_END_IF
    EVT_RETURN
    EVT_END
};

StaticNpc N(NpcData_GuardBoo) = {
    .id = NPC_GuardBoo,
    .settings = &N(NpcSettings_Boo),
    .pos = { 168.0f, 0.0f, -161.0f },
    .yaw = 270,
    .flags = ENEMY_FLAGS_1 | ENEMY_FLAGS_100 | ENEMY_FLAGS_400 | ENEMY_FLAGS_800 | ENEMY_FLAGS_400000,
    .init = &N(EVS_NpcInit_GuardBoo),
    .drops = BOO_DROPS,
    .animations = NORMAL_BOO_ANIMS,
    .tattle = MSG_NpcTattle_OBK_GuardingChest,
};

NpcGroupList N(DefaultNPCs) = {
    NPC_GROUP(N(NpcData_TrafficBoo1)),
    NPC_GROUP(N(NpcData_TrafficBoo2)),
    NPC_GROUP(N(NpcData_GuardBoo)),
    {}
};
