#include "common.h"
#include "npc.h"
#include "effects.h"

extern s32 D_8014B7F0;

void spawn_drops(Enemy* enemy) {
    PlayerData* playerData = &gPlayerData;
    EncounterStatus* encounter = &gCurrentEncounter;
    EnemyDropsFlat* drops = (EnemyDropsFlat*) enemy->drops; // TODO: unify EnemyDrops / EnemyDropsFlat
    Npc* npc = get_npc_unsafe(enemy->npcID);
    Camera* camera = &gCameras[gCurrentCameraID];
    s32 pickupDelay;
    s32 sp28;
    s32 numShadowSpaces;
    s32 itemToDrop;
    f32 x, y, z;
    f32 temp_f20;
    f32 chance;
    f32 attempts;
    f32 temp_f24;
    s32 maxCoinBonus;
    s32 minCoinBonus;
    s32 tempMax;
    s32 var_fp;
    s32 var_s1;
    s32 totalWeight;
    s32 facingAngleSign;
    s32 angleMult;
    s32 i, j;
    s32 flags;

    numShadowSpaces = 0;
    for (i = 0; i < MAX_SHADOWS; i++) {
        if (get_shadow_by_index(i) == NULL) {
            numShadowSpaces++;
        }
    }

    var_fp = 0;
    sp28 = 246 - D_8014B7F0;
    facingAngleSign = clamp_angle(camera->currentYaw + 90.0f);
    x = npc->pos.x;
    y = npc->pos.y + (npc->collisionHeight / 2);
    z = npc->pos.z;

    angleMult = 0;
    pickupDelay = 0;

    var_s1 = drops->itemDropChance;
    if (drops->itemDropChance > rand_int(100)) {
        tempMax = 0;

        for (i = 0; i < 8; i++) {
            if (drops->itemDrops[3 * i] != 0) {
                tempMax += drops->itemDrops[3 * i + 1];
            } else {
                break;
            }
        }

        totalWeight = 0;
        var_s1 = rand_int(tempMax);
        itemToDrop = ITEM_NONE;

        for (i = 0; i < 8; i++) {
            if (drops->itemDrops[3 * i] == 0) {
                break;
            }

            totalWeight += drops->itemDrops[3 * i + 1];
            if (drops->itemDrops[3 * i + 2] > 0) {
                if (get_global_flag(drops->itemDrops[3 * i + 2] + 0x714) != 0) {
                    continue;
                }
            }

            if (totalWeight >= var_s1) {
                itemToDrop = drops->itemDrops[3 * i];
                do { } while (0); // TODO required to match
                break;
            }
        }

        // TODO this bullshit is required to match
        flags = enemy->flags;
        if (flags) {
            flags = 0;
        }

        if (itemToDrop != ITEM_NONE) {
            make_item_entity(itemToDrop, x, y, z, 4, pickupDelay, facingAngleSign + angleMult * 360, 0);
            var_fp++;
            pickupDelay += 2;
            facingAngleSign += 30.0;
            if (var_fp >= 12) {
                angleMult++;
                facingAngleSign = angleMult * 8;
                var_fp = 0;
            }

            if (drops->itemDrops[3 * i + 2] >= 0) {
                set_global_flag(drops->itemDrops[3 * i + 2] + 0x715);
            }
        }
    }

    if (encounter->dropWhackaBump) {
        encounter->dropWhackaBump = FALSE;
        make_item_entity(ITEM_WHACKAS_BUMP, x, y, z, 4, pickupDelay, facingAngleSign + angleMult * 360, 0);
        var_fp++;
        pickupDelay += 2;
        facingAngleSign += 30.0;
        if (var_fp >= 12) {
            angleMult++;
            facingAngleSign = angleMult * 8;
            var_fp = 0;
        }
    }

    var_s1 = 0;
    temp_f24 = playerData->curHP / (f32) playerData->curMaxHP;
    itemToDrop = ITEM_NONE;

    for (i = 0; i < 8; i++) {
        attempts = drops->heartDrops[4 * i];
        temp_f20 = drops->heartDrops[4 * i + 1];
        attempts /= 32767.0f;
        temp_f20 /= 32767.0f;

        if (temp_f24 <= attempts &&
            rand_int(100) <= temp_f20 * 100.0f)
        {
            attempts = drops->heartDrops[4 * i + 2];
            chance = drops->heartDrops[4 * i + 3];
            chance /= 32767.0f;
            for (j = 0; j < attempts; j++) {
                if (rand_int(100) <= chance * 100.0f) {
                    var_s1++;
                }
            }
            break;
        }
    }

    if (is_ability_active(ABILITY_HEART_FINDER) != 0) {
        s32 temp = var_s1 + 1;
        var_s1 = temp + rand_int(2);
    }
    if (enemy->flags & ENEMY_FLAGS_800000) {
        var_s1 = 0;
    }
    if (var_s1 != 0) {
        itemToDrop = ITEM_HEART;
    }
    if (var_s1 * 2 > sp28) {
        var_s1 = sp28 / 2;
    }
    sp28 -= 2 * var_s1;
    if (var_s1 > numShadowSpaces) {
        var_s1 = numShadowSpaces;
    }

    numShadowSpaces -= var_s1;

    for (i = 0; i < var_s1; i++) {
        make_item_entity(itemToDrop, x, y, z, 4, pickupDelay, facingAngleSign + (angleMult * 360), 0);
        var_fp++;
        pickupDelay += 2;
        facingAngleSign += 30.0;
        if (var_fp >= 12) {
            var_fp = 0;
            angleMult++;
            facingAngleSign = angleMult * 8;
        }
    }

    var_s1 = 0;
    itemToDrop = ITEM_NONE;
    temp_f24 = playerData->curFP / (f32) playerData->curMaxFP;

    for (i = 0; i < 8; i++) {
        attempts = drops->flowerDrops[4 * i + 0];
        temp_f20 = drops->flowerDrops[4 * i + 1];
        attempts /= 32767.0f;
        temp_f20 /= 32767.0f;

        if (temp_f24 <= attempts &&
            rand_int(100) <= temp_f20 * 100.0f)
        {
            attempts = drops->flowerDrops[4 * i + 2];
            chance = drops->flowerDrops[4 * i + 3];
            chance /= 32767.0f;
            for (j = 0; j < attempts; j++) {
                if (rand_int(100) <= chance * 100.0f) {
                    var_s1++;
                }
            }
            break;
        }
    }

    if (is_ability_active(ABILITY_FLOWER_FINDER) != 0) {
        s32 temp = var_s1 + 1;
        var_s1 = temp + rand_int(2);
    }
    if (enemy->flags & ENEMY_FLAGS_800000) {
        var_s1 = 0;
    }
    if (var_s1 != 0) {
        itemToDrop = ITEM_FLOWER_POINT;
    }
    if (var_s1 * 2 > sp28) {
        var_s1 = sp28 / 2;
    }
    sp28 -= 2 * var_s1;
    if (var_s1 > numShadowSpaces) {
        var_s1 = numShadowSpaces;
    }

    numShadowSpaces -= var_s1;

    for (i = 0; i < var_s1; i++) {
        make_item_entity(itemToDrop, x, y, z, 4, pickupDelay, facingAngleSign + (angleMult * 360), 0);
        var_fp++;
        pickupDelay += 2;
        facingAngleSign += 30.0;
        if (var_fp >= 12) {
            var_fp = 0;
            angleMult++;
            facingAngleSign = angleMult * 8;
        }
    }

    itemToDrop = ITEM_COIN;
    do {} while (0);
    minCoinBonus = drops->minCoinBonus;
    tempMax = drops->maxCoinBonus;

    if (drops->maxCoinBonus < drops->minCoinBonus) {
        var_s1 = minCoinBonus;
        minCoinBonus = tempMax;
        tempMax = var_s1;
    }

    if (minCoinBonus < 0) {
        var_s1 = rand_int(tempMax - minCoinBonus) + minCoinBonus;
    } else {
        var_s1 = tempMax - minCoinBonus;
        if (var_s1 != 0) {
            var_s1 = rand_int(var_s1) + minCoinBonus;
        } else {
            var_s1 = minCoinBonus;
        }
    }

    if (var_s1 < 0) {
        var_s1 = 0;
    }
    var_s1 = var_s1 + encounter->coinsEarned;


    if (is_ability_active(ABILITY_PAY_OFF) != 0) {
        var_s1 += encounter->damageTaken / 2;
        encounter->damageTaken = 0;
    }
    if (encounter->merleeCoinBonus != 0) {
        encounter->merleeCoinBonus = 0;
        var_s1 *= 3;
    }
    if (is_ability_active(ABILITY_MONEY_MONEY) != 0) {
        var_s1 *= 2;
    }
    if (var_s1 > 20) {
        var_s1 = 20;
    }
    if (enemy->flags & ENEMY_FLAGS_800000) {
        var_s1 = 0;
    }
    if (var_s1 * 2 > sp28) {
        var_s1 = sp28 / 2;
    }
    sp28 -= 2 * var_s1;

    if (var_s1 > numShadowSpaces) {
        var_s1 = numShadowSpaces;
    }

    for (i = 0; i < var_s1; i++) {
        make_item_entity(itemToDrop, x, y, z, 4, pickupDelay, facingAngleSign + (angleMult * 360), 0);
        var_fp++;
        pickupDelay += 2;
        facingAngleSign = facingAngleSign + 30.0;
        if (var_fp >= 12) {
            var_fp = 0;
            angleMult++;
            facingAngleSign = angleMult * 8;
        }
    }
}

s32 get_coin_drop_amount(Enemy* enemy) {
    EncounterStatus* currentEncounter = &gCurrentEncounter;
    EnemyDrops* enemyDrops = enemy->drops;
    s32 maxCoinBonus = enemyDrops->maxCoinBonus;
    s32 amt = enemyDrops->minCoinBonus;
    s32 minTemp = enemyDrops->minCoinBonus;

    if (maxCoinBonus < amt) {
        amt = enemyDrops->maxCoinBonus;
        maxCoinBonus = enemyDrops->minCoinBonus;
    }

    minTemp = maxCoinBonus - amt;
    if ((amt < 0) || (minTemp != 0)) {
        amt = rand_int(minTemp) - -amt;
    }

    if (amt < 0) {
        amt = 0;
    }

    if (is_ability_active(ABILITY_PAY_OFF)) {
        amt += currentEncounter->damageTaken / 2;
    }

    if (currentEncounter->merleeCoinBonus) {
        amt *= 3;
    }

    if (is_ability_active(ABILITY_MONEY_MONEY)) {
        amt *= 2;
    }

    amt += currentEncounter->coinsEarned;

    if (enemy->flags & (ENEMY_FLAGS_800000 | ENEMY_FLAGS_40000)) {
        amt = 0;
    }

    if (amt > 20) {
        amt = 20;
    }

    return amt;
}

void func_80048E34(Enemy* enemy, s32 arg1, s32 arg2) {
    Evt* newScript;

    if (enemy->aiScript != NULL) {
        kill_script_by_ID(enemy->aiScriptID);
        enemy->aiScript = NULL;
    }

    if (enemy->unk_BC != NULL) {
        kill_script_by_ID(enemy->unk_C0);
        enemy->unk_BC = NULL;
    }

    if (enemy->aiBytecode != NULL) {
        enemy->unk_C8 = arg2;
        newScript = start_script(enemy->aiBytecode, EVT_PRIORITY_A, EVT_FLAG_RUN_IMMEDIATELY);
        enemy->aiScript = newScript;
        enemy->aiScriptID = newScript->id;
        newScript->owner2.npcID = enemy->npcID;
        newScript->owner1.enemy = enemy;
    }

    if (enemy->unk_B8 != NULL) {
        enemy->unk_C4 = arg1;
        newScript = start_script(enemy->unk_B8, EVT_PRIORITY_A, EVT_FLAG_RUN_IMMEDIATELY);
        enemy->unk_BC = newScript;
        enemy->unk_C0 = newScript->id;
        newScript->owner2.npcID = enemy->npcID;
        newScript->owner1.enemy = enemy;
    }
}

s32 func_80048F0C(void) {
    EncounterStatus* currentEncounter = &gCurrentEncounter;
    s32 i;
    s32 j;

    for (i = 0; i < currentEncounter->numEncounters; i++) {
        Encounter* encounter = currentEncounter->encounterList[i];

        if (encounter != NULL) {
            for (j = 0; j < encounter->count; j++) {
                Enemy* enemy = encounter->enemy[j];

                if (enemy != NULL && !(enemy->flags & ENEMY_FLAGS_20)) {
                    get_npc_unsafe(enemy->npcID);
                }
            }
        }
    }

    return 0;
}

s32 is_point_within_region(s32 shape, f32 pointX, f32 pointY, f32 centerX, f32 centerY, f32 sizeX, f32 sizeZ) {
    f32 dist1;
    f32 dist2;

    switch (shape) {
        case 0:
            dist1 = dist2D(pointX, pointY, centerX, centerY);
            return (sizeX < dist1);
        case 1:
            dist1 = dist2D(pointX, 0, centerX, 0);
            dist2 = dist2D(0, pointY, 0, centerY);
            return ((sizeX < dist1) || (sizeZ < dist2));
        default:
            return FALSE;
    }
}

s32 basic_ai_check_player_dist(EnemyDetectVolume* territory, Enemy* enemy, f32 radius, f32 fwdPosOffset, s8 useWorldYaw) {
    Npc* npc = get_npc_unsafe(enemy->npcID);
    PlayerStatus* playerStatus = &gPlayerStatus;
    PartnerActionStatus* partnerActionStatus;
    f32 x, y, z;
    f32 dist;
    s32 skipCheckForPlayer;

    if (enemy->aiFlags & ENEMY_AI_FLAGS_2) {
        return FALSE;
    }

    partnerActionStatus = &gPartnerActionStatus;
    if (partnerActionStatus->actingPartner == PARTNER_BOW && partnerActionStatus->partnerActionState
            && !(territory->detectFlags & AI_TERRITORY_IGNORE_HIDING)) {
        return FALSE;
    }

    if (partnerActionStatus->actingPartner == PARTNER_SUSHIE && partnerActionStatus->partnerActionState
            && !(territory->detectFlags & AI_TERRITORY_IGNORE_HIDING)) {
        return FALSE;
    }

    if (territory->skipPlayerDetectChance < 0) {
        return FALSE;
    }

    if (territory->halfHeight <= fabsf(npc->pos.y - playerStatus->position.y)
            && !(territory->detectFlags & AI_TERRITORY_IGNORE_ELEVATION)) {
        return FALSE;
    }

    if (territory->sizeX | territory->sizeZ && is_point_within_region(territory->shape,
            territory->pointX, territory->pointZ,
            playerStatus->position.x, playerStatus->position.z,
            territory->sizeX, territory->sizeZ)) {
        return FALSE;
    }

    if ((playerStatus->actionState == ACTION_STATE_USE_SPINNING_FLOWER)) {
        return FALSE;
    }

    // check for unbroken line of sight
    if (enemy->aiDetectFlags & AI_DETECT_SIGHT) {
        x = npc->pos.x;
        y = npc->pos.y + npc->collisionHeight * 0.5;
        z = npc->pos.z;
        dist = dist2D(npc->pos.x, npc->pos.z, playerStatus->position.x, playerStatus->position.z);
        if (npc_test_move_simple_with_slipping(0x50000,
                &x, &y, &z,
                dist, atan2(npc->pos.x, npc->pos.z, playerStatus->position.x, playerStatus->position.z),
                0.1f, 0.1f)) {
            return FALSE;
        }
    }

    if (territory->skipPlayerDetectChance == 0) {
        skipCheckForPlayer = 0;
    } else {
        skipCheckForPlayer = rand_int(territory->skipPlayerDetectChance + 1);
    }

    if (skipCheckForPlayer == 0) {
        if (enemy->aiDetectFlags & AI_DETECT_SENSITIVE_MOTION) {
            if (playerStatus->actionState == ACTION_STATE_WALK) {
                radius *= 1.15;
            } else if (playerStatus->actionState == ACTION_STATE_RUN) {
                radius *= 1.3;
            }
        }
        x = npc->pos.x;
        z = npc->pos.z;
        if (useWorldYaw & 0xFF) {
            add_vec2D_polar(&x, &z, fwdPosOffset, npc->yaw);
        } else {
            add_vec2D_polar(&x, &z, fwdPosOffset, 270.0f - npc->renderYaw);
        }
        if (dist2D(x, z, playerStatus->position.x, playerStatus->position.z) <= radius) {
            return TRUE;
        }
    }

    return FALSE;
}

s32 ai_check_player_dist(Enemy* enemy, s32 chance, f32 radius, f32 moveSpeed) {
    PlayerStatus* playerStatus = &gPlayerStatus;
    Npc* npc = get_npc_unsafe(enemy->npcID);
    f32 posX, posZ;

    if (chance >= 0) {
        s32 skipCheckForPlayer;

        if (chance != 0) {
            skipCheckForPlayer = rand_int(chance + 1);
        } else {
            skipCheckForPlayer = 0;
        }

        if (skipCheckForPlayer == 0) {
            posX = npc->pos.x;
            posZ = npc->pos.z;
            add_vec2D_polar(&posX, &posZ, moveSpeed, 270.0f - npc->renderYaw);

            if (dist2D(posX, posZ, playerStatus->position.x, playerStatus->position.z) <= radius) {
                return TRUE;
            }
        }
    }

    return FALSE;
}

void ai_enemy_play_sound(Npc* npc, s32 soundID, s32 upperSoundFlags) {
    Enemy* enemy = get_enemy(npc->npcID);
    s32 soundFlags = (upperSoundFlags & 0xFFFF0000) | 2;

    if (upperSoundFlags & 1) {
        soundFlags |= 0x10000;
    }

    if (enemy->npcSettings->actionFlags & AI_ACTION_20) {
        soundFlags |= 0x20000;
    }

    sfx_play_sound_at_position(soundID, soundFlags, npc->pos.x, npc->pos.y, npc->pos.z);
}

void ai_try_set_state(Evt* script, s32 state) {
    Npc* npc = get_npc_unsafe(script->owner1.enemy->npcID);

    npc->duration--;
    if (npc->duration <= 0) {
        script->AI_TEMP_STATE = state;
    }
}

void basic_ai_wander_init(Evt* script, MobileAISettings* npcAISettings, EnemyDetectVolume* territory) {
    Enemy* enemy = script->owner1.enemy;
    Npc* npc = get_npc_unsafe(enemy->npcID);

    // chose a random direction and move time
    npc->duration = (npcAISettings->moveTime / 2) + rand_int((npcAISettings->moveTime / 2) + 1);
    npc->yaw = clamp_angle(npc->yaw + rand_int(60) - 30.0f);
    npc->currentAnim = enemy->animList[ENEMY_ANIM_INDEX_WALK];
    script->functionTemp[1] = 0;

    if (enemy->territory->wander.moveSpeedOverride < 0) {
        npc->moveSpeed = npcAISettings->moveSpeed;
    } else {
        npc->moveSpeed = enemy->territory->wander.moveSpeedOverride / 32767.0;
    }

    enemy->aiFlags &= ~ENEMY_AI_FLAGS_40;
    enemy->aiFlags &= ~ENEMY_AI_FLAGS_20;
    script->AI_TEMP_STATE = AI_STATE_WANDER;
}

void basic_ai_wander(Evt* script, MobileAISettings* aiSettings, EnemyDetectVolume* territory) {
    Enemy* enemy = script->owner1.enemy;
    Npc* npc = get_npc_unsafe(enemy->npcID);
    s32 stillWithinTerritory = FALSE;
    f32 x, y, z;
    s32 sp34;
    f32 yaw;

    if (aiSettings->playerSearchInterval >= 0) {
        if (script->functionTemp[1] <= 0) {
            script->functionTemp[1] = aiSettings->playerSearchInterval;
            if (basic_ai_check_player_dist(territory, enemy, aiSettings->alertRadius, aiSettings->alertOffsetDist, 0)) {
                x = npc->pos.x;
                y = npc->pos.y;
                z = npc->pos.z;
                yaw = atan2(npc->pos.x, npc->pos.z, gPlayerStatusPtr->position.x, gPlayerStatusPtr->position.z);
                if (!npc_test_move_simple_with_slipping(npc->collisionChannel, &x, &y, &z, aiSettings->chaseSpeed, yaw, npc->collisionHeight, npc->collisionRadius)) {
                    npc->yaw = yaw;
                    ai_enemy_play_sound(npc, SOUND_2F4, 0x200000);
                    fx_emote(EMOTE_EXCLAMATION, npc, 0, npc->collisionHeight, 1.0f, 2.0f, -20.0f, 15, &sp34);
                    enemy->aiFlags &= ~ENEMY_AI_FLAGS_40;
                    enemy->aiFlags &= ~ENEMY_AI_FLAGS_20;

                    if (enemy->npcSettings->actionFlags & AI_ACTION_JUMP_WHEN_SEE_PLAYER) {
                        script->AI_TEMP_STATE = AI_STATE_ALERT_INIT;
                    } else {
                        script->AI_TEMP_STATE = AI_STATE_CHASE_INIT;
                    }
                    return;
                }
            }
        }
        script->functionTemp[1]--;
    }

    // check if the wander we've reached the boundary of the territory
    if (is_point_within_region(enemy->territory->wander.wanderShape,
                               enemy->territory->wander.centerPos.x,
                               enemy->territory->wander.centerPos.z,
                               npc->pos.x,
                               npc->pos.z,
                               enemy->territory->wander.wanderSize.x,
                               enemy->territory->wander.wanderSize.z)
        && npc->moveSpeed < dist2D(enemy->territory->wander.centerPos.x, enemy->territory->wander.centerPos.z, npc->pos.x, npc->pos.z)) {
        if (!(enemy->aiFlags & ENEMY_AI_FLAGS_20)) {
            enemy->aiFlags |= (ENEMY_AI_FLAGS_20 | ENEMY_AI_FLAGS_40);
        }

        if (enemy->aiFlags & ENEMY_AI_FLAGS_40) {
            npc->yaw = clamp_angle(atan2(npc->pos.x, npc->pos.z, enemy->territory->wander.centerPos.x, enemy->territory->wander.centerPos.z));
            enemy->aiFlags &= ~ENEMY_AI_FLAGS_40;
        }

        x = npc->pos.x;
        y = npc->pos.y;
        z = npc->pos.z;
        if (npc_test_move_simple_with_slipping(npc->collisionChannel, &x, &y, &z, 2.0 * npc->moveSpeed, npc->yaw, npc->collisionHeight, npc->collisionRadius)) {
            yaw = clamp_angle(atan2(npc->pos.x, npc->pos.z, enemy->territory->wander.centerPos.x, enemy->territory->wander.centerPos.z));
            enemy->aiFlags &= ~ENEMY_AI_FLAGS_40;
            ai_check_fwd_collisions(npc, 5.0f, &yaw, NULL, NULL, NULL);
            npc->yaw = yaw;
        }
        stillWithinTerritory = TRUE;
    } else if (enemy->aiFlags & ENEMY_AI_FLAGS_20) {
        enemy->aiFlags &= ~ENEMY_AI_FLAGS_20;
        enemy->aiFlags &= ~ENEMY_AI_FLAGS_40;
    }

    // perform the motion
    if (enemy->territory->wander.wanderSize.x | enemy->territory->wander.wanderSize.z | stillWithinTerritory) {
        if (!npc->turnAroundYawAdjustment) {
            npc_move_heading(npc, npc->moveSpeed, npc->yaw);
        } else {
            return;
        }
    }

    // decide to loiter or continue wandering
    if (aiSettings->moveTime > 0) {
        npc->duration--;
        if (npc->duration <= 0) {
            script->AI_TEMP_STATE = AI_STATE_LOITER_INIT;
            script->functionTemp[1] = rand_int(1000) % 3 + 2;
            if (aiSettings->unk_AI_2C <= 0 || aiSettings->waitTime <= 0) {
                script->AI_TEMP_STATE = AI_STATE_WANDER_INIT;
            }
        }
    }
}

void basic_ai_loiter_init(Evt* script, MobileAISettings* aiSettings, EnemyDetectVolume* territory) {
    Enemy* enemy = script->owner1.enemy;
    Npc* npc = get_npc_unsafe(enemy->npcID);

    npc->duration = (aiSettings->waitTime / 2) + rand_int((aiSettings->waitTime / 2) + 1);
    npc->yaw = clamp_angle(npc->yaw + rand_int(180) - 90.0f);
    npc->currentAnim = enemy->animList[ENEMY_ANIM_INDEX_IDLE];
    script->AI_TEMP_STATE = AI_STATE_LOITER;
}

void basic_ai_loiter(Evt* script, MobileAISettings* aiSettings, EnemyDetectVolume* territory) {
    Enemy* enemy = script->owner1.enemy;
    Npc* npc = get_npc_unsafe(enemy->npcID);
    f32 x, y, z;
    f32 yaw;
    s32 emoteTemp;

    if (aiSettings->playerSearchInterval >= 0 && basic_ai_check_player_dist(territory, enemy, aiSettings->chaseRadius, aiSettings->chaseOffsetDist, 0)) {
        x = npc->pos.x;
        y = npc->pos.y;
        z = npc->pos.z;
        yaw = atan2(npc->pos.x, npc->pos.z, gPlayerStatusPtr->position.x, gPlayerStatusPtr->position.z);
        if (!npc_test_move_simple_with_slipping(npc->collisionChannel, &x, &y, &z, aiSettings->chaseSpeed, yaw, npc->collisionHeight, npc->collisionRadius)) {
            npc->yaw = yaw;
            ai_enemy_play_sound(npc, SOUND_2F4, 0x200000);
            fx_emote(EMOTE_EXCLAMATION, npc, 0, npc->collisionHeight, 1.0f, 2.0f, -20.0f, 15, &emoteTemp);
            if (enemy->npcSettings->actionFlags & AI_ACTION_JUMP_WHEN_SEE_PLAYER) {
                script->AI_TEMP_STATE = AI_STATE_ALERT_INIT;
            } else {
                script->AI_TEMP_STATE = AI_STATE_CHASE_INIT;
            }
            return;
        }
    }

    // look around randomly
    if (npc->turnAroundYawAdjustment == 0) {
        npc->duration--;
        if (npc->duration <= 0) {
            script->functionTemp[1]--;
            if (script->functionTemp[1]) {
                if (!(enemy->npcSettings->actionFlags & AI_ACTION_LOOK_AROUND_DURING_LOITER)) {
                    npc->yaw = clamp_angle(npc->yaw + 180.0f);
                }
                npc->duration = (aiSettings->waitTime / 2) + rand_int(aiSettings->waitTime / 2 + 1);
                return;
            }
            script->AI_TEMP_STATE = AI_STATE_WANDER_INIT;
        }
    }
}

void basic_ai_found_player_jump_init(Evt* script, MobileAISettings* npcAISettings, EnemyDetectVolume* territory) {
    Enemy* enemy = script->owner1.enemy;
    Npc* npc = get_npc_unsafe(enemy->npcID);

    ai_enemy_play_sound(npc, SOUND_3E1, 0);
    npc->currentAnim = enemy->animList[ENEMY_ANIM_INDEX_JUMP];
    npc->jumpVelocity = 10.0f;
    npc->jumpScale = 2.5f;
    npc->moveToPos.y = npc->pos.y;
    npc->flags |= NPC_FLAG_JUMPING;
    script->AI_TEMP_STATE = AI_STATE_ALERT;
}

void basic_ai_found_player_jump(Evt* script, MobileAISettings* npcAISettings, EnemyDetectVolume* territory) {
    Npc* npc = get_npc_unsafe(script->owner1.enemy->npcID);
    s32 done = FALSE;

    if (npc->jumpVelocity <= 0.0) {
        if (npc->pos.y <= npc->moveToPos.y) {
            npc->pos.y = npc->moveToPos.y;
            done = TRUE;
        }
    }

    if (!done) {
        npc->pos.y += npc->jumpVelocity;
        npc->jumpVelocity -= npc->jumpScale;
    } else {
        npc->jumpVelocity = 0.0f;
        npc->flags &= ~NPC_FLAG_JUMPING;
        script->AI_TEMP_STATE = AI_STATE_CHASE_INIT;
    }
}

void basic_ai_chase_init(Evt* script, MobileAISettings* npcAISettings, EnemyDetectVolume* territory) {
    Enemy* enemy = script->owner1.enemy;
    Npc* npc = get_npc_unsafe(enemy->npcID);
    s32 skipTurnAround = FALSE;

    if ((gPlayerStatusPtr->actionState == ACTION_STATE_JUMP || gPlayerStatusPtr->actionState == ACTION_STATE_BOUNCE ||
        gPlayerStatusPtr->actionState == ACTION_STATE_HOP || gPlayerStatusPtr->actionState == ACTION_STATE_FALLING) &&
        (f64)dist2D(npc->pos.x, npc->pos.z, gPlayerStatusPtr->position.x, gPlayerStatusPtr->position.z) < npc->collisionRadius)
    {
        skipTurnAround = TRUE;
    }

    if (!skipTurnAround) {
        f32 angle = atan2(npc->pos.x, npc->pos.z, gPlayerStatusPtr->position.x, gPlayerStatusPtr->position.z);
        f32 deltaAngleToPlayer = get_clamped_angle_diff(npc->yaw, angle);

        if (npcAISettings->chaseTurnRate < fabsf(deltaAngleToPlayer)) {
            angle = npc->yaw;
            if (deltaAngleToPlayer < 0.0f) {
                angle += -npcAISettings->chaseTurnRate;
            } else {
                angle += npcAISettings->chaseTurnRate;
            }
        }
        npc->yaw = clamp_angle(angle);
        npc->duration = (npcAISettings->chaseUpdateInterval / 2) + rand_int((npcAISettings->chaseUpdateInterval / 2) + 1);
    } else {
        npc->duration = 0;
    }

    npc->currentAnim = enemy->animList[ENEMY_ANIM_INDEX_CHASE];
    npc->moveSpeed = npcAISettings->chaseSpeed;
    script->AI_TEMP_STATE = AI_STATE_CHASE;
}

void basic_ai_chase(Evt* script, MobileAISettings* aiSettings, EnemyDetectVolume* territory) {
    Enemy* enemy = script->owner1.enemy;
    Npc* npc = get_npc_unsafe(enemy->npcID);
    s32 sp28;
    f32 x, y, z;

    if (!basic_ai_check_player_dist(territory, enemy, aiSettings->chaseRadius, aiSettings->chaseOffsetDist, 1)) {
        fx_emote(EMOTE_QUESTION, npc, 0, npc->collisionHeight, 1.0f, 2.0f, -20.0f, 15, &sp28);
        npc->currentAnim = enemy->animList[ENEMY_ANIM_INDEX_IDLE];
        npc->duration = 20;
        script->AI_TEMP_STATE = AI_STATE_LOSE_PLAYER;
        return;
    }

    if (enemy->npcSettings->actionFlags & AI_ACTION_04) {
        if (dist2D(npc->pos.x, npc->pos.z, gPlayerStatusPtr->position.x, gPlayerStatusPtr->position.z) > (npc->moveSpeed * 5.0)) {
            x = npc->pos.x;
            y = npc->pos.y;
            z = npc->pos.z;
            if (npc_test_move_simple_with_slipping(npc->collisionChannel, &x, &y, &z, 1.0f, npc->yaw, npc->collisionHeight, npc->collisionRadius)) {
                fx_emote(EMOTE_QUESTION, npc, 0, npc->collisionHeight, 1.0f, 2.0f, -20.0f, 0xC, &sp28);
                npc->currentAnim = enemy->animList[ENEMY_ANIM_INDEX_IDLE];
                npc->duration = 15;
                script->AI_TEMP_STATE = AI_STATE_LOSE_PLAYER;
                return;
            }
        }
    }

    func_8003D660(npc, 1);
    npc_move_heading(npc, npc->moveSpeed, npc->yaw);

    if (npc->moveSpeed > 8.0 && !(gGameStatusPtr->frameCounter % 5)) {
        ai_enemy_play_sound(npc, SOUND_20C1, 0);
    }

    if (npc->duration > 0) {
        npc->duration--;
    } else {
        script->AI_TEMP_STATE = AI_STATE_CHASE_INIT;
    }
}

void basic_ai_lose_player(Evt* script, MobileAISettings* npcAISettings, EnemyDetectVolume* territory) {
    Enemy* enemy = script->owner1.enemy;
    Npc* npc = get_npc_unsafe(enemy->npcID);

    npc->duration--;
    if (npc->duration == 0) {
        // turn to face home position
        npc->yaw = clamp_angle(atan2(npc->pos.x, npc->pos.z, enemy->territory->wander.centerPos.x, enemy->territory->wander.centerPos.z));
        script->AI_TEMP_STATE = AI_STATE_WANDER_INIT;
    }
}

ApiStatus BasicAI_Main(Evt* script, s32 isInitialCall) {
    Enemy* enemy = script->owner1.enemy;
    Npc* npc = get_npc_unsafe(enemy->npcID);
    Bytecode* args = script->ptrReadPos;
    EnemyDetectVolume territory;
    EnemyDetectVolume* pTerritory = &territory;
    MobileAISettings* aiSettings = (MobileAISettings*) evt_get_variable(script, *args++);

    territory.skipPlayerDetectChance = 0;
    territory.shape = enemy->territory->wander.detectShape;
    territory.pointX = enemy->territory->wander.detectPos.x;
    territory.pointZ = enemy->territory->wander.detectPos.z;
    territory.sizeX = enemy->territory->wander.detectSize.x;
    territory.sizeZ = enemy->territory->wander.detectSize.z;
    territory.halfHeight = 65.0f;
    territory.detectFlags = 0;

    if (isInitialCall || enemy->aiFlags & ENEMY_AI_FLAGS_4) {
        script->AI_TEMP_STATE = AI_STATE_WANDER_INIT;
        npc->duration = 0;

        npc->currentAnim = enemy->animList[ENEMY_ANIM_INDEX_IDLE];

        npc->flags &= ~NPC_FLAG_JUMPING;
        if (!enemy->territory->wander.isFlying) {
            npc->flags |= NPC_FLAG_GRAVITY;
            npc->flags &= ~NPC_FLAG_ENABLE_HIT_SCRIPT;
        } else {
            npc->flags &= ~NPC_FLAG_GRAVITY;
            npc->flags |= NPC_FLAG_ENABLE_HIT_SCRIPT;
        }

        if (enemy->aiFlags & ENEMY_AI_FLAGS_4) {
            script->AI_TEMP_STATE = AI_STATE_SUSPEND;
            script->functionTemp[1] = AI_STATE_WANDER_INIT;
        } else if (enemy->flags & ENEMY_FLAGS_40000000) {
            script->AI_TEMP_STATE = AI_STATE_CHASE_INIT;
        }

        enemy->aiFlags &= ~ENEMY_AI_FLAGS_4;
        enemy->flags &= ~ENEMY_FLAGS_40000000;
    }

    switch (script->AI_TEMP_STATE) {
        case AI_STATE_WANDER_INIT:
            basic_ai_wander_init(script, aiSettings, pTerritory);
        case AI_STATE_WANDER:
            basic_ai_wander(script, aiSettings, pTerritory);
            break;

        case AI_STATE_LOITER_INIT:
            basic_ai_loiter_init(script, aiSettings, pTerritory);
        case AI_STATE_LOITER:
            basic_ai_loiter(script, aiSettings, pTerritory);
            break;

        case AI_STATE_ALERT_INIT:
            basic_ai_found_player_jump_init(script, aiSettings, pTerritory);
        case AI_STATE_ALERT:
            basic_ai_found_player_jump(script, aiSettings, pTerritory);
            break;

        case AI_STATE_CHASE_INIT:
            basic_ai_chase_init(script, aiSettings, pTerritory);
        case AI_STATE_CHASE:
            basic_ai_chase(script, aiSettings, pTerritory);
            if (script->AI_TEMP_STATE != AI_STATE_LOSE_PLAYER) {
                break;
            }

        case AI_STATE_LOSE_PLAYER:
            basic_ai_lose_player(script, aiSettings, pTerritory);
            break;
        case AI_STATE_SUSPEND:
            basic_ai_suspend(script);
            break;
    }
    return ApiStatus_BLOCK;
}
