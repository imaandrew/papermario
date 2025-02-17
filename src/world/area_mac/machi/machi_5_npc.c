#include "machi.h"

s32 N(GoombariaAnims)[] = {
    ANIM_Goombaria_Walk,
    ANIM_Goombaria_Jump,
    ANIM_Goombaria_Fall,
    ANIM_Goombaria_Idle,
    ANIM_Goombaria_Idle,
    ANIM_Goombaria_Run, 
};

API_CALLABLE(N(func_802401B0_7E7550)) {
    Npc* npc = get_npc_unsafe(script->owner1.enemy->npcID);

    if (rand_int(1000) < 500) {
        func_8005DECC(npc, -1, N(GoombariaAnims),
            rand_int(4) + 1,
            rand_int(3) + 5,
            rand_int(50) + 50,
            rand_int(100) + 100);
    } else {
        func_8005DECC(npc, rand_int(3) + 10, N(GoombariaAnims),
            rand_int(4) + 1,
            rand_int(3) + 5,
            rand_int(50) + 50,
            rand_int(100) + 10);
    }
    return ApiStatus_DONE2;
}

API_CALLABLE(N(func_802402EC_7E768C)) {
    Npc* npc = get_npc_unsafe(script->owner1.enemy->npcID);

    func_8005DFD4(npc);
    return ApiStatus_DONE2;
}

API_CALLABLE(N(func_80240318_7E76B8)) {
    Npc* npc = get_npc_unsafe(script->owner1.enemy->npcID);

    func_8005E12C(npc);
    return ApiStatus_DONE2;
}

API_CALLABLE(N(SetupChapter0)) {
    PlayerData* playerData = &gPlayerData;
    s32 i;

    playerData->curHP = 5;
    playerData->curMaxHP = 5;
    playerData->bootsLevel = 0;
    playerData->hammerLevel = -1;
    playerData->fortressKeyCount = 0;

    for (i = 0; i < ARRAY_COUNT(playerData->partners); i++) {
        playerData->partners[i].enabled = FALSE;
    }
    switch_to_partner(PARTNER_NONE);
    return ApiStatus_DONE2;
}

API_CALLABLE(N(SetupStarRodPaletteCycling)) {
    Npc* npc = get_npc_unsafe(script->owner1.enemy->npcID);

    npc_set_palswap_mode_A(npc, 3);
    npc_set_palswap_1(npc, 0, 1, 30, 10);
    npc_set_palswap_2(npc, 60, 20, 0, 0);
    return ApiStatus_DONE2;
}

API_CALLABLE(N(SetupChapter1)) {
    PlayerData* playerData = &gPlayerData;
    s32 i;

    playerData->curHP = 8;
    playerData->curMaxHP = 8;
    playerData->bootsLevel = 0;
    playerData->hammerLevel = 0;
    playerData->fortressKeyCount = 0;
    playerData->partners[PARTNER_NONE].enabled = TRUE;

    for (i = 1; i < ARRAY_COUNT(playerData->partners); i++) {
        playerData->partners[i].enabled = FALSE;
    }
    return ApiStatus_DONE2;
}

API_CALLABLE(N(SetupChapter2)) {
    PlayerData* playerData = &gPlayerData;
    s32 i;

    playerData->curHP = 11;
    playerData->curMaxHP = 11;
    playerData->bootsLevel = 0;
    playerData->hammerLevel = 0;
    playerData->fortressKeyCount = 0;

    for (i = 0; i < ARRAY_COUNT(playerData->partners); i++) {
        playerData->partners[i].enabled = FALSE;
    }

    playerData->partners[PARTNER_NONE].enabled = TRUE;
    playerData->partners[PARTNER_GOOMBARIO].enabled = TRUE;
    playerData->partners[PARTNER_BOMBETTE].enabled = TRUE;
    return ApiStatus_DONE2;
}

EvtScript N(EVS_NpcAuxAI_Goompa) = {
    EVT_RETURN
    EVT_END
};

EvtScript N(EVS_802411A8) = {
    EVT_CALL(N(func_802401B0_7E7550))
    EVT_LABEL(0)
        EVT_CALL(N(func_802402EC_7E768C))
        EVT_CALL(N(func_80240318_7E76B8))
        EVT_WAIT(1)
        EVT_GOTO(0)
    EVT_RETURN
    EVT_END
};

EvtScript N(EVS_NpcInteract_Goompa) = {
    EVT_RETURN
    EVT_END
};

EvtScript N(EVS_NpcHit_Goompa) = {
    EVT_RETURN
    EVT_END
};

EvtScript N(EVS_NpcDefeat_Goompa) = {
    EVT_RETURN
    EVT_END
};

EvtScript N(EVS_NpcAI_Unused) = {
    EVT_RETURN
    EVT_END
};

EvtScript N(EVS_NpcAuxAI_Unused) = {
    EVT_RETURN
    EVT_END
};

EvtScript N(EVS_NpcInteract_Unused) = {
    EVT_RETURN
    EVT_END
};

EvtScript N(EVS_NpcHit_Unused) = {
    EVT_CALL(StartBattle)
    EVT_RETURN
    EVT_END
};

EvtScript N(EVS_NpcDefeat_Unused) = {
    EVT_CALL(GetBattleOutcome, LVar0)
    EVT_SWITCH(LVar0)
        EVT_CASE_EQ(OUTCOME_PLAYER_WON)
            EVT_CALL(DoNpcDefeat)
        EVT_CASE_EQ(OUTCOME_PLAYER_LOST)
        EVT_CASE_EQ(OUTCOME_PLAYER_FLED)
    EVT_END_SWITCH
    EVT_RETURN
    EVT_END
};

EvtScript N(EVS_NpcInteract_StarRod) = {
    EVT_CALL(BringPartnerOut, PARTNER_PARAKARRY)
    EVT_WAIT(200)
    EVT_CALL(PutPartnerAway)
    EVT_RETURN
    EVT_END
};

EvtScript N(EVS_NpcAI_StarRod) = {
    EVT_RETURN
    EVT_END
};

EvtScript N(EVS_NpcAuxAI_StarRod) = {
    EVT_CALL(N(SetupStarRodPaletteCycling))
    EVT_RETURN
    EVT_END
};

EvtScript N(EVS_NpcInteract_Koopa) = {
    EVT_CALL(N(SetupChapter1))
    EVT_RETURN
    EVT_END
};

EvtScript N(EVS_NpcAI_Koopa) = {
    EVT_RETURN
    EVT_END
};

EvtScript N(EVS_NpcInteract_Kolorado) = {
    EVT_CALL(N(SetupChapter2))
    EVT_RETURN
    EVT_END
};

EvtScript N(EVS_NpcAI_Kolorado) = {
    EVT_RETURN
    EVT_END
};

NpcSettings N(NpcSettings_StarRod) = {
    .defaultAnim = ANIM_StarRod_Still,
    .height = 24,
    .radius = 24,
    .otherAI = &N(EVS_NpcAuxAI_StarRod),
    .onInteract = &N(EVS_NpcInteract_StarRod),
    .ai = &N(EVS_NpcAI_StarRod),
    .flags = ENEMY_FLAGS_1,
};

NpcSettings N(NpcSettings_Koopa) = {
    .defaultAnim = ANIM_Koopa_Walk,
    .height = 24,
    .radius = 24,
    .onInteract = &N(EVS_NpcInteract_Koopa),
    .ai = &N(EVS_NpcAI_Koopa),
    .flags = ENEMY_FLAGS_1,
};

NpcSettings N(NpcSettings_Kolorado) = {
    .defaultAnim = ANIM_Kolorado_Walk,
    .height = 24,
    .radius = 24,
    .onInteract = &N(EVS_NpcInteract_Kolorado),
    .ai = &N(EVS_NpcAI_Kolorado),
    .flags = ENEMY_FLAGS_1,
};

NpcSettings N(NpcSettings_Goompa) = {
    .defaultAnim = ANIM_Goompa_Walk,
    .height = 24,
    .radius = 24,
    .otherAI = &N(EVS_NpcAuxAI_Goompa),
    .onInteract = &N(EVS_NpcInteract_Goompa),
    .onHit = &N(EVS_NpcHit_Goompa),
    .flags = ENEMY_FLAGS_100 | ENEMY_FLAGS_200 | ENEMY_FLAGS_400 | ENEMY_FLAGS_800 | ENEMY_FLAGS_100000,
};

StaticNpc N(NpcData_05)[] = {
    {
        .id = NPC_05,
        .settings = &N(NpcSettings_StarRod),
        .pos = { 16.0f, 0.0f, -411.0f },
        .yaw = 0,
        .flags = 0,
        .init = (void*) 0x1F64,
        .animations = {},
    },
    {
        .id = NPC_06,
        .settings = &N(NpcSettings_Koopa),
        .pos = { 389.0f, 0.0f, -278.0f },
        .yaw = 0,
        .flags = 0,
        .init = (void*) 0x1F64,
        .animations = {},
    },
    {
        .id = NPC_07,
        .settings = &N(NpcSettings_Kolorado),
        .pos = { 481.0f, 0.0f, -44.0f },
        .yaw = 0,
        .flags = 0,
        .init = (void*) 0x1F64,
        .animations = {},
    },
};

StaticNpc N(NpcData_GoombaFamily) = {
    .id = NPC_Goompa,
    .settings = &N(NpcSettings_Goompa),
    .pos = { 0.0f, 0.0f, 0.0f },
    .yaw = 0,
    .flags = ENEMY_FLAGS_8,
    .init = (void*) 0x1F64,
    .animations = {
    },
};

StaticNpc N(NpcData_0B)[] = {
    {
        .id = NPC_0B,
        .settings = &N(NpcSettings_Goompa),
        .pos = { 0.0f, 0.0f, 0.0f },
        .yaw = 0,
        .flags = ENEMY_FLAGS_8,
        .init = (void*) 0x1F64,
        .animations = {},
    },
    {
        .id = NPC_0C,
        .settings = &N(NpcSettings_Goompa),
        .pos = { 0.0f, 0.0f, 0.0f },
        .yaw = 0,
        .flags = ENEMY_FLAGS_8,
        .init = (void*) 0x1F64,
        .animations = {},
    },
    {
        .id = NPC_0D,
        .settings = &N(NpcSettings_Goompa),
        .pos = { 0.0f, 0.0f, 0.0f },
        .yaw = 0,
        .flags = ENEMY_FLAGS_8,
        .init = (void*) 0x1F64,
        .animations = {},
    },
    {
        .id = NPC_0E,
        .settings = &N(NpcSettings_Goompa),
        .pos = { 0.0f, 0.0f, 0.0f },
        .yaw = 0,
        .flags = ENEMY_FLAGS_8,
        .init = (void*) 0x1F64,
        .animations = {},
    },
    {
        .id = NPC_0F,
        .settings = &N(NpcSettings_Goompa),
        .pos = { 0.0f, 0.0f, 0.0f },
        .yaw = 0,
        .flags = ENEMY_FLAGS_8,
        .init = (void*) 0x1F64,
        .animations = {},
    },
    {
        .id = NPC_10,
        .settings = &N(NpcSettings_Goompa),
        .pos = { 0.0f, 0.0f, 0.0f },
        .yaw = 0,
        .flags = ENEMY_FLAGS_8,
        .init = (void*) 0x1F64,
        .animations = {},
    },
    {
        .id = NPC_11,
        .settings = &N(NpcSettings_Goompa),
        .pos = { 0.0f, 0.0f, 0.0f },
        .yaw = 0,
        .flags = ENEMY_FLAGS_8,
        .init = (void*) 0x1F64,
        .animations = {},
    },
    {
        .id = NPC_12,
        .settings = &N(NpcSettings_Goompa),
        .pos = { 0.0f, 0.0f, 0.0f },
        .yaw = 0,
        .flags = ENEMY_FLAGS_8,
        .init = (void*) 0x1F64,
        .animations = {},
    },
    {
        .id = NPC_13,
        .settings = &N(NpcSettings_Goompa),
        .pos = { 0.0f, 0.0f, 0.0f },
        .yaw = 0,
        .flags = ENEMY_FLAGS_8,
        .init = (void*) 0x1F64,
        .animations = {},
    },
};

StaticNpc N(NpcData_GoombaKing) = {
    .id = NPC_GoombaKing,
    .settings = &N(NpcSettings_GoombaKing),
    .pos = { 12.0f, 0.0f, -13.0f },
    .yaw = 0,
    .flags = 0,
    .init = (void*) 0x4003,
    .animations = {}
};

NpcGroupList N(DefaultNPCs) = {
    NPC_GROUP(N(NpcData_05), BTL_KMR_PART_1_FORMATION_08),
    NPC_GROUP(N(NpcData_GoombaFamily), BTL_KMR_PART_1_FORMATION_08),
    NPC_GROUP(N(NpcData_Misstar)),
    {}
};
