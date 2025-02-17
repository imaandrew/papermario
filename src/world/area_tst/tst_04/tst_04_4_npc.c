#include "tst_04.h"

API_CALLABLE(N(DisableOwnerShadow)) {
    disable_npc_shadow(get_npc_unsafe(script->owner1.enemy->npcID));
    return ApiStatus_DONE2;
}

EvtScript N(EVS_NpcAuxAI_Goompa) = {
    EVT_CALL(N(DisableOwnerShadow))
    EVT_CALL(SetNpcFlagBits, NPC_SELF, NPC_FLAG_40000, TRUE)
    EVT_RETURN
    EVT_END
};

EvtScript N(EVS_NpcAux_Goompa) = {
    EVT_RETURN
    EVT_END
};

EvtScript N(EVS_NpcAI_Goompa) = {
    EVT_RETURN
    EVT_END
};

EvtScript N(EVS_NpcHit_Goompa) = {
    EVT_RETURN
    EVT_END
};

EvtScript N(EVS_NpcInteract_Goompa) = {
    EVT_RETURN
    EVT_END
};

EvtScript N(EVS_NpcDefeat_Goompa) = {
    EVT_RETURN
    EVT_END
};

NpcSettings N(NpcSettings_Goompa) = {
    .defaultAnim = ANIM_Goompa_Talk,
    .height = 24,
    .radius = 24,
    .otherAI = &N(EVS_NpcAuxAI_Goompa),
    .onInteract = &N(EVS_NpcInteract_Goompa),
    .ai = &N(EVS_NpcAI_Goompa),
    .onHit = &N(EVS_NpcHit_Goompa),
    .aux = &N(EVS_NpcAux_Goompa),
    .onDefeat = &N(EVS_NpcDefeat_Goompa),
    .unk_24 = 200,
    .flags = ENEMY_FLAGS_1 | ENEMY_FLAGS_4,
};

StaticNpc N(NpcData_GoombaFamily) = {
    .id = NPC_Goompa,
    .settings = &N(NpcSettings_Goompa),
    .pos = { 80.0f, 40.0f, -84.0f },
    .yaw = 0,
    .flags = ENEMY_FLAGS_GRAVITY,
};

NpcGroupList N(DefaultNPCs) = {
    NPC_GROUP(N(NpcData_GoombaFamily)),
    {}
};
