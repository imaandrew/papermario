#include "common.h"
#include "script_api/battle.h"
#include "ld_addrs.h"
#include "effects.h"
#include "hud_element.h"
#include "battle/battle.h"
#include "model.h"

extern StageListRow* D_800DC064;

extern s16 D_802809F6;
extern s16 D_802809F8;
extern s32 D_80280A30;
extern EvtScript D_80280EB8[];
extern s32 D_80281454[];
extern EvtScript D_80284A20[];
extern EvtScript D_80284A30[];

BSS s32 D_8029F240;
BSS u8 D_8029F244;
BSS s32 D_8029F248;
BSS s32 D_8029F24C;
BSS s32 D_8029F250;
BSS s32 D_8029F254;
BSS s32 D_8029F258;
BSS s32 D_8029F25C;
BSS s32 D_8029F260;
BSS s32 D_8029F264;

s32 dispatch_damage_event_player_0(s32 damageAmount, s32 event);

void btl_merlee_on_start_turn(void) {
    BattleStatus* battleStatus = &gBattleStatus;
    EncounterStatus* currentEncounter = &gCurrentEncounter;
    PlayerData* playerData = &gPlayerData;

    do {
        if (!(gBattleStatus.flags2 & BS_FLAGS2_PEACH_BATTLE) &&
            battleStatus->nextMerleeSpellType != MERLEE_SPELL_3 &&
            battleStatus->nextMerleeSpellType != MERLEE_SPELL_4 &&
            playerData->merleeCastsLeft > 0)
        {
            if (playerData->merleeTurnCount <= 0) {
                s32 temp = rand_int(100);

                if (currentEncounter->currentEnemy != NULL) {
                    if (currentEncounter->currentEnemy->flags & ACTOR_FLAG_40000) {
                        if (temp <= 45) {
                            playerData->merleeSpellType = MERLEE_SPELL_1;
                        } else if (temp <= 90) {
                            playerData->merleeSpellType = MERLEE_SPELL_2;
                        } else {
                            playerData->merleeSpellType = MERLEE_SPELL_3;
                        }
                    } else if (temp <= 30) {
                        playerData->merleeSpellType = MERLEE_SPELL_1;
                    } else if (temp <= 60) {
                        playerData->merleeSpellType = MERLEE_SPELL_2;
                    } else if (temp <= 80) {
                        playerData->merleeSpellType = MERLEE_SPELL_3;
                    } else {
                        playerData->merleeSpellType = MERLEE_SPELL_4;
                    }
                } else if (temp <= 30) {
                    playerData->merleeSpellType = MERLEE_SPELL_1;
                } else if (temp <= 60) {
                    playerData->merleeSpellType = MERLEE_SPELL_2;
                } else if (temp <= 80) {
                    playerData->merleeSpellType = MERLEE_SPELL_3;
                } else {
                    playerData->merleeSpellType = MERLEE_SPELL_4;
                }

                temp = rand_int(10) + 6;
                playerData->merleeTurnCount = temp;
            }

            if (playerData->merleeTurnCount >= 2) {
                playerData->merleeTurnCount--;
            } else {
                playerData->merleeTurnCount = 0;
                battleStatus->nextMerleeSpellType = playerData->merleeSpellType;
                playerData->merleeCastsLeft--;
            }
        }
    } while (0); // TODO: required to match
}

void btl_merlee_on_first_strike(void) {
    BattleStatus* battleStatus = &gBattleStatus;
    EncounterStatus* currentEncounter = &gCurrentEncounter;
    PlayerData* playerData = &gPlayerData;

    do {
        if (!(gBattleStatus.flags2 & BS_FLAGS2_PEACH_BATTLE) &&
            battleStatus->nextMerleeSpellType != MERLEE_SPELL_3 &&
            battleStatus->nextMerleeSpellType != MERLEE_SPELL_4 &&
            playerData->merleeCastsLeft > 0)
        {
            if (playerData->merleeTurnCount <= 0) {
                s32 temp = rand_int(100);

                if (currentEncounter->currentEnemy != NULL) {
                    if (currentEncounter->currentEnemy->flags & ACTOR_FLAG_40000) {
                        if (temp <= 45) {
                            playerData->merleeSpellType = MERLEE_SPELL_1;
                        } else if (temp <= 90) {
                            playerData->merleeSpellType = MERLEE_SPELL_2;
                        } else {
                            playerData->merleeSpellType = MERLEE_SPELL_3;
                        }
                    } else if (temp <= 30) {
                        playerData->merleeSpellType = MERLEE_SPELL_1;
                    } else if (temp <= 60) {
                        playerData->merleeSpellType = MERLEE_SPELL_2;
                    } else if (temp <= 80) {
                        playerData->merleeSpellType = MERLEE_SPELL_3;
                    } else {
                        playerData->merleeSpellType = MERLEE_SPELL_4;
                    }
                } else if (temp <= 30) {
                    playerData->merleeSpellType = MERLEE_SPELL_1;
                } else if (temp <= 60) {
                    playerData->merleeSpellType = MERLEE_SPELL_2;
                } else if (temp <= 80) {
                    playerData->merleeSpellType = MERLEE_SPELL_3;
                } else {
                    playerData->merleeSpellType = MERLEE_SPELL_4;
                }

                if (playerData->merleeSpellType != MERLEE_SPELL_4) {
                    // same outcome either way. has to be written like this, and the check does exist in the code. bug?
                    if (playerData->merleeTurnCount == -1) {
                        temp = rand_int(5) + 5;
                    } else {
                        temp = rand_int(5) + 5;

                    }
                } else {
                    temp = rand_int(8) + 5;
                }
                playerData->merleeTurnCount = temp;
            }

            if (playerData->merleeSpellType == MERLEE_SPELL_3 || playerData->merleeSpellType == MERLEE_SPELL_4) {
                if (playerData->merleeTurnCount >= 2) {
                    playerData->merleeTurnCount--;
                } else {
                    battleStatus->nextMerleeSpellType = playerData->merleeSpellType;
                    playerData->merleeTurnCount = 0;
                    playerData->merleeCastsLeft--;
                }
            }
        }
    } while (0); // TODO: required to match
}

void btl_set_state(s32 battleState) {
    s32 flags = gBattleStatus.flags2;
    gBattleState = battleState;
    D_800DC4E0 = 1;
    gBattleSubState = BTL_SUBSTATE_INIT;

    flags &= BS_FLAGS2_PEACH_BATTLE;
    if (flags) {
        switch (battleState) {
            case BATTLE_STATE_PARTNER_MENU:
                battleState = BATTLE_STATE_TWINK_MENU;
                break;
            case BATTLE_STATE_PLAYER_MENU:
                battleState = BATTLE_STATE_PEACH_MENU;
                break;
            case BATTLE_STATE_BEGIN_PLAYER_TURN:
                battleState = BATTLE_STATE_BEGIN_PARTNER_TURN;
                break;
            case BATTLE_STATE_BEGIN_PARTNER_TURN:
                battleState = BATTLE_STATE_BEGIN_PLAYER_TURN;
                break;
        }
        gBattleState = battleState;
    }
}

void btl_state_update_normal_start(void) {
    BattleStatus* battleStatus = &gBattleStatus;
    EncounterStatus* currentEncounter = &gCurrentEncounter;
    Battle* battle;
    Stage* stage;
    s32 size;
    void* compressedAsset;
    ModelNode* model;
    s32 textureRom;
    Actor* actor;
    Evt* script;
    s32 cond;
    s32 type;
    s32 i;
    s32 j;

    s32* types;

    battle = (*D_800DC4FC);
    if (D_800DC4F4 != NULL) {
        battle = D_800DC4F4;
    }

    if (D_800DC064 == NULL) {
        stage = battle->stage;
    } else {
        stage = D_800DC064->stage;
    }

    battleStatus->currentStage = stage;
    switch (gBattleSubState) {
        case BTL_SUBSTATE_NORMAL_START_UNK_0:
            D_8029F240 = battle->formationSize;
            set_screen_overlay_params_back(255, -1.0f);
            compressedAsset = load_asset_by_name(stage->shape, &size);
            decode_yay0(compressedAsset, &D_80210000);
            general_heap_free(compressedAsset);

            ASSERT(size <= 0x8000);

            model = D_80210000.root;
            textureRom = get_asset_offset(stage->texture, &size);
            if (model != NULL) {
                load_data_for_models(model, textureRom, size);
            }
            load_battle_hit_asset(stage->hit);

            if (stage->bg != NULL) {
                load_map_bg(stage->bg);
                read_background_size(&gBackgroundImage);
            }

            if (gGameStatusPtr->demoFlags & 1) {
                set_curtain_scale_goal(1.0f);
            }

            battleStatus->controlScript = NULL;
            battleStatus->camMovementScript = NULL;
            battleStatus->unk_90 = 0;
            battleStatus->preUpdateCallback = NULL;
            battleStatus->initBattleCallback = NULL;
            battleStatus->currentSubmenu = 0;
            battleStatus->unk_49 = 0;
            battleStatus->unk_4A = 0;
            battleStatus->unk_4B = 0;
            battleStatus->totalStarPoints = 0;
            battleStatus->pendingStarPoints = 0;
            battleStatus->incrementStarPointDelay = 0;
            battleStatus->damageTaken = 0;
            battleStatus->nextMerleeSpellType = MERLEE_SPELL_0;
            battleStatus->actionCommandMode = ACTION_COMMAND_MODE_NOT_LEARNED;
            gCameras[CAM_DEFAULT].flags |= CAMERA_FLAGS_ENABLED;
            gCameras[CAM_BATTLE].flags |= CAMERA_FLAGS_ENABLED;
            gCameras[CAM_TATTLE].flags |= CAMERA_FLAGS_ENABLED;
            if (is_ability_active(ABILITY_MYSTERY_SCROLL)) {
                battleStatus->actionCommandMode = ACTION_COMMAND_MODE_LEARNED;
            }
            battleStatus->actionSuccess = 0;
            battleStatus->unk_82 = 0;
            battleStatus->menuDisableFlags = -1;
            battleStatus->unk_74 = -1;
            battleStatus->itemUsesLeft = 0;
            battleStatus->hammerCharge = 0;
            battleStatus->jumpCharge = 0;
            battleStatus->unk_98 = 0;
            battleStatus->hpDrainCount = 0;
            gBattleStatus.flags2 |= BS_FLAGS2_CANT_FLEE;
            if (currentEncounter->allowFleeing) {
                gBattleStatus.flags2 &= ~BS_FLAGS2_CANT_FLEE;
            }
            battleStatus->unk_8D = 10;
            battleStatus->unk_95 = 0;
            battleStatus->hammerLossTurns = -1;
            battleStatus->jumpLossTurns = -1;
            battleStatus->itemLossTurns = -1;
            battleStatus->outtaSightActive = 0;
            battleStatus->waterBlockTurnsLeft = 0;
            battleStatus->waterBlockAmount = 0;
            battleStatus->waterBlockEffect = NULL;
            battleStatus->cloudNineTurnsLeft = 0;
            battleStatus->cloudNineDodgeChance = 0;
            battleStatus->cloudNineEffect = NULL;
            battleStatus->unk_92 = 0;
            battleStatus->turboChargeTurnsLeft = 0;
            battleStatus->turboChargeAmount = 0;
            battleStatus->unk_8C = 0;
            battleStatus->merleeAttackBoost = 0;
            battleStatus->merleeDefenseBoost = 0;
            battleStatus->darknessMode = BTL_DARKNESS_STATE_NONE;
            battleStatus->unk_433 = -1;
            battleStatus->hustleTurns = 0;
            battleStatus->unk_93 = 0;
            battleStatus->unk_94 = 0;
            gBattleStatus.flags2 &= ~BS_FLAGS2_2;
            gBattleStatus.flags2 &= ~BS_FLAGS2_4;
            gBattleStatus.flags2 &= ~BS_FLAGS2_8;
            gBattleStatus.flags2 &= ~BS_FLAGS2_10;
            gBattleStatus.flags2 &= ~BS_FLAGS2_100;
            gBattleStatus.flags2 &= ~BS_FLAGS2_200;

            for (i = 0; i < ARRAY_COUNT(battleStatus->varTable); i++) {
                battleStatus->varTable[i] = 0;
            }

            D_80280A30 = 255;
            battleStatus->inputBitmask = 0xFEF3F;
            battleStatus->buffEffect = fx_partner_buff(0, 0.0f, 0.0f, 0.0f, 0.0f, 0);
            func_800E9810();
            gCurrentCameraID = CAM_BATTLE;
            script = start_script(D_80280EB8, EVT_PRIORITY_A, 0);
            battleStatus->camMovementScript = script;
            battleStatus->camMovementScriptID = script->id;
            gBattleSubState = BTL_SUBSTATE_NORMAL_START_UNK_1;
            break;
        case BTL_SUBSTATE_NORMAL_START_UNK_1:
            if (!does_script_exist(battleStatus->camMovementScriptID)) {
                UiStatus* uiStatus = &gUIStatus;

                if (stage->preBattle != NULL) {
                    script = start_script(stage->preBattle, 0xA, 0);
                    battleStatus->controlScript = script;
                    battleStatus->controlScriptID = script->id;
                }

                uiStatus->hidden = FALSE;
                gBattleStatus.flags1 |= BS_FLAGS1_ACTORS_VISIBLE;

                for (i = 0; i < ARRAY_COUNT(battleStatus->enemyActors); i++) {
                    battleStatus->enemyActors[i] = NULL;
                }
                battleStatus->initialEnemyCount = 0;

                for (i = 0; i < D_8029F240; i++) {
                    create_actor(&(*battle->formation)[i]);
                    types = D_80281454;
                    actor = battleStatus->enemyActors[i];

                    while (TRUE) {
                        type = *types;
                        if (type == -1) {
                            battleStatus->initialEnemyCount++;
                            break;
                        } else if (actor->actorType == type) {
                            break;
                        }
                        types++;
                    }

                    actor->unk_208 = 0;
                    if (i == 0) {
                        actor->unk_208 = currentEncounter->unk_10;
                        if (currentEncounter->dizzyAttackStatus == STATUS_DIZZY) {
                            inflict_status_set_duration(actor, STATUS_DIZZY, STATUS_DIZZY_TURN_MOD, currentEncounter->dizzyAttackDuration);
                        }
                    }
                }

                if (stage->specialFormationSize != 0 &&
                    (stage->unk_24 == 0 || (stage->unk_24 > 0 && (rand_int(stage->unk_24) == 0))))
                {
                    D_8029F240 += stage->specialFormationSize;
                    for (j = 0; i < D_8029F240; i++, j++) {
                        create_actor(&(*stage->specialFormation)[j]);
                        actor = battleStatus->enemyActors[i];
                        actor->unk_208 = 0;
                        if (i == 0) {
                            actor->unk_208 = 0;
                            if (currentEncounter->dizzyAttackStatus == STATUS_DIZZY) {
                                inflict_status_set_duration(actor, STATUS_DIZZY, STATUS_DIZZY_TURN_MOD, currentEncounter->dizzyAttackDuration);
                            }
                        }

                    }
                }

                load_player_actor();
                actor = battleStatus->playerActor;
                if (gBattleStatus.flags2 & BS_FLAGS2_PEACH_BATTLE) {
                    script = start_script(D_80284A30, EVT_PRIORITY_A, 0);
                } else {
                    script = start_script(D_80284A20, EVT_PRIORITY_A, 0);
                }
                actor->takeTurnScript = script;
                actor->takeTurnScriptID = script->id;
                script->owner1.actorID = ACTOR_PLAYER;
                load_partner_actor();
                gBattleSubState = BTL_SUBSTATE_NORMAL_START_UNK_4;
            }
            break;
        case BTL_SUBSTATE_NORMAL_START_UNK_4:
            cond = FALSE;
            for (i = 0; i < D_8029F240; i++) {
                actor = battleStatus->enemyActors[i];
                if (does_script_exist(actor->takeTurnScriptID)) {
                    cond = TRUE;
                    break;
                } else {
                    actor->takeTurnScript = NULL;
                }
            }

            if (!cond) {
                actor = battleStatus->playerActor;
                if (!does_script_exist(actor->takeTurnScriptID)) {
                    actor->takeTurnScript = NULL;
                    actor = battleStatus->partnerActor;
                    if (actor != NULL) {
                        if (!does_script_exist(battleStatus->partnerActor->takeTurnScriptID)) {
                            actor->takeTurnScript = NULL;
                        } else {
                            return;
                        }
                    }

                    if (battle->unk_10 != 0) {
                        script = start_script(battle->unk_10, 0xA, 0);
                        battleStatus->controlScript = script;
                        battleStatus->controlScriptID = script->id;
                    }
                    if (battleStatus->darknessMode > BTL_DARKNESS_STATE_NONE) {
                        set_screen_overlay_color(1, 0, 0, 0);
                        set_screen_overlay_params_back(0, 215.0f);
                    }
                    if (is_ability_active(ABILITY_CHILL_OUT) && currentEncounter->firstStrikeType == FIRST_STRIKE_ENEMY) {
                        currentEncounter->firstStrikeType = FIRST_STRIKE_NONE;
                    }

                    switch (currentEncounter->firstStrikeType) {
                        case FIRST_STRIKE_PLAYER:
                            btl_set_state(BATTLE_STATE_FIRST_STRIKE);
                            break;
                        case FIRST_STRIKE_ENEMY:
                            btl_set_state(BATTLE_STATE_ENEMY_FIRST_STRIKE);
                            break;
                        default:
                            if (!(gGameStatusPtr->demoFlags & 1)) {
                                actor = battleStatus->playerActor;
                                if (gBattleStatus.flags2 & BS_FLAGS2_PEACH_BATTLE) {
                                    script = start_script(&PeachEnterStage, EVT_PRIORITY_A, 0);
                                } else {
                                    script = start_script(&MarioEnterStage, EVT_PRIORITY_A, 0);
                                }
                                actor->takeTurnScript = script;
                                actor->takeTurnScriptID = script->id;
                                script->owner1.actorID = ACTOR_PLAYER;
                            }

                            if (currentEncounter->currentEnemy != NULL &&
                                currentEncounter->currentEnemy->encountered == 3 &&
                                is_ability_active(ABILITY_DIZZY_ATTACK))
                            {
                                actor = battleStatus->enemyActors[0];
                                script = start_script(&DoDizzyAttack, EVT_PRIORITY_A, 0);
                                actor->takeTurnScript = script;
                                actor->takeTurnScriptID = script->id;
                                script->owner1.enemyID = ACTOR_ENEMY0;
                            }

                            D_80280A30 = 305;
                            D_8029F248 = 0;
                            gBattleSubState = BTL_SUBSTATE_NORMAL_START_UNK_7;
                            break;
                    }
                }
            }
            break;
        case BTL_SUBSTATE_NORMAL_START_UNK_7:
            if (D_80280A30 == 0) {
                gBattleSubState = BTL_SUBSTATE_NORMAL_START_UNK_8;
                break;
            }

            D_8029F248++;
            if (D_8029F248 == 15) {
                btl_cam_use_preset(BTL_CAM_PRESET_C);
            }

            if (!(gGameStatusPtr->demoFlags & 1)) {
                D_80280A30 -= 10;
            } else {
                D_80280A30 -= 50;
            }

            if (D_80280A30 < 0) {
                D_80280A30 = 0;
            }
            break;
        case BTL_SUBSTATE_NORMAL_START_UNK_8:
            if (battleStatus->unk_8C == 0) {
                set_screen_overlay_params_front(255, -1.0f);
                btl_set_state(BATTLE_STATE_BEGIN_TURN);
            }
            break;
    }
}

void btl_state_draw_normal_start(void) {
    set_screen_overlay_color(0, 0, 0, 0);

    if (D_80280A30 > 255) {
        set_screen_overlay_params_front(0, 255.0f);
    } else {
        set_screen_overlay_params_front(0, D_80280A30);
    }
}

void btl_state_update_begin_turn(void) {
    BattleStatus* battleStatus = &gBattleStatus;
    PlayerData* playerData = &gPlayerData;
    Actor* partner = battleStatus->partnerActor;
    Actor* player = battleStatus->playerActor;
    Actor* enemy;
    Actor* enemy1;
    Actor* enemy2;
    Evt* script;
    Evt* script2;
    s32 cond;
    u16 id1;
    u16 id2;
    s32 numEnemyActors;
    s32 i;
    s32 j;
    s16* enemyIDs;

    if (gBattleSubState == BTL_SUBSTATE_BEGIN_TURN_INIT) {
        battleStatus->flags2 &= ~BS_FLAGS2_2;
        battleStatus->flags2 &= ~BS_FLAGS2_4;
        battleStatus->flags2 &= ~BS_FLAGS2_8;
        battleStatus->flags2 &= ~BS_FLAGS2_10;
        battleStatus->merleeAttackBoost = 0;
        battleStatus->merleeDefenseBoost = 0;
        battleStatus->flags2 &= ~BS_FLAGS2_1000000;

        player->flags |= ACTOR_FLAG_8000000 | ACTOR_FLAG_4000000;
        player->disableDismissTimer = 0;
        if (partner != NULL) {
            player->flags |= ACTOR_FLAG_8000000 | ACTOR_FLAG_4000000;
            partner->disableDismissTimer = 0;
        }

        if (battleStatus->hustleTurns != 0) {
            gBattleStatus.flags1 |= BS_FLAGS1_HUSTLED;
        }

        numEnemyActors = 0;
        for (i = 0; i < ARRAY_COUNT(battleStatus->enemyActors); i++) {
            enemy = battleStatus->enemyActors[i];
            if (enemy != NULL) {
                battleStatus->enemyIDs[numEnemyActors] = i | ACTOR_ENEMY0;
                numEnemyActors++;
            }
        }
        battleStatus->numEnemyActors = numEnemyActors;

        // sort enemies by x-position or turn priority
        enemyIDs = battleStatus->enemyIDs;
        for (i = 0; i < numEnemyActors - 1; i++) {
            for (j = i + 1; j < numEnemyActors; j++) {
                id1 = enemyIDs[i];
                id2 = enemyIDs[j];
                enemy1 = battleStatus->enemyActors[id1 & 0xFF];
                enemy2 = battleStatus->enemyActors[id2 & 0xFF];
                if (gBattleStatus.flags1 & BS_FLAGS1_8000000) {
                    if (enemy1->homePos.x > enemy2->homePos.x) {
                        enemyIDs[i] = id2;
                        enemyIDs[j] = id1;
                    }
                } else if (enemy1->turnPriority < enemy2->turnPriority) {
                    enemyIDs[i] = id2;
                    enemyIDs[j] = id1;
                }
            }
        }
        battleStatus->nextEnemyIndex = 0;

        btl_merlee_on_start_turn();

        battleStatus->rushFlags = RUSH_FLAG_NONE;
        gBattleStatus.flags2 &= ~BS_FLAGS2_HAS_RUSH;

        if (!(gBattleStatus.flags2 & BS_FLAGS2_PEACH_BATTLE)) {
            if (playerData->curHP < 2 && is_ability_active(ABILITY_MEGA_RUSH)) {
                gBattleStatus.flags2 |= BS_FLAGS2_HAS_RUSH;
                battleStatus->rushFlags |= RUSH_FLAG_MEGA;
            }
            if (playerData->curHP < 6 && is_ability_active(ABILITY_POWER_RUSH) && !(battleStatus->rushFlags & RUSH_FLAG_MEGA)) {
                gBattleStatus.flags2 |= BS_FLAGS2_HAS_RUSH;
                battleStatus->rushFlags |= RUSH_FLAG_POWER;
            }
        }

        if (!(gBattleStatus.flags1 & BS_FLAGS1_JUMP_CHARGED)) {
            battleStatus->jumpCharge = 0;
        }

        if (!(gBattleStatus.flags1 & BS_FLAGS1_HAMMER_CHARGED)) {
            battleStatus->hammerCharge = 0;
        }

        if (gGameStatusPtr->debugEnemyContact == DEBUG_CONTACT_AUTO_FLEE) {
            btl_set_state(BATTLE_STATE_RUN_AWAY);
            return;
        }

        if (gGameStatusPtr->debugEnemyContact == DEBUG_CONTACT_DIE_IN_BATTLE) {
            for (i = 0; i < ARRAY_COUNT(battleStatus->enemyActors); i++) {
                enemy = battleStatus->enemyActors[i];
                if (enemy != NULL && enemy->handleEventSource != NULL) {
                    Evt* script = start_script(enemy->handleEventSource, EVT_PRIORITY_A, 0);

                    enemy->handleEventScript = script;
                    script->owner1.actorID = i | ACTOR_ENEMY0;
                    enemy->handleEventScriptID = script->id;
                    enemy->lastEventType = EVENT_DEATH;
                }
            }
            gBattleSubState = BTL_SUBSTATE_BEGIN_TURN_AWAIT_ENEMY_DEATH;
        } else {
            for (i = 0; i < ARRAY_COUNT(battleStatus->enemyActors); i++) {
                enemy = battleStatus->enemyActors[i];
                if (enemy != NULL && enemy->handlePhaseSource != NULL) {
                    battleStatus->battlePhase = PHASE_PLAYER_BEGIN;
                    script = start_script(enemy->handlePhaseSource, EVT_PRIORITY_A, 0);
                    enemy->handlePhaseScript = script;
                    enemy->handleBatttlePhaseScriptID = script->id;
                    script->owner1.actorID = i | ACTOR_ENEMY0;
                }
            }

            partner = battleStatus->partnerActor;
            if (partner != NULL) {
                if (partner->handlePhaseSource != NULL) {
                    battleStatus->battlePhase = PHASE_PLAYER_BEGIN;
                    script = start_script(partner->handlePhaseSource, EVT_PRIORITY_A, 0);
                    partner->handlePhaseScript = script;
                    partner->handleBatttlePhaseScriptID = script->id;
                    script->owner1.actorID = ACTOR_PARTNER;
                }
            }
            gBattleSubState = BTL_SUBSTATE_BEGIN_TURN_AWAIT_ENEMY_SCRIPTS;
        }
    }

    if (gBattleSubState == BTL_SUBSTATE_BEGIN_TURN_AWAIT_ENEMY_SCRIPTS) {
        cond = FALSE;
        for (i = 0; i < ARRAY_COUNT(battleStatus->enemyActors); i++) {
            enemy = battleStatus->enemyActors[i];
            if (enemy != NULL && enemy->handlePhaseSource != NULL && does_script_exist(enemy->handleBatttlePhaseScriptID)) {
                cond = TRUE;
            }
        }
        if (partner != NULL && partner->handlePhaseSource != NULL && does_script_exist(partner->handleBatttlePhaseScriptID)) {
            cond = TRUE;
        }

        if (!cond) {
            if (!btl_check_enemies_defeated()) {
                btl_set_state(BATTLE_STATE_BEGIN_PLAYER_TURN);
            }
            return;
        }
    }

    if (gBattleSubState == BTL_SUBSTATE_BEGIN_TURN_AWAIT_ENEMY_DEATH) {
        cond = FALSE;
        for (i = 0; i < ARRAY_COUNT(battleStatus->enemyActors); i++) {
            enemy = battleStatus->enemyActors[i];
            if (enemy != NULL && enemy->handleEventSource != NULL && does_script_exist(enemy->handleEventScriptID)) {
                cond = TRUE;
            }
        }

        if (!cond) {
            if (!btl_check_enemies_defeated()) {
                btl_set_state(BATTLE_STATE_BEGIN_PLAYER_TURN);
            }
        }
    }
}

void btl_state_draw_begin_turn(void) {
}

void btl_state_update_begin_player_turn(void) {
    BattleStatus* battleStatus = &gBattleStatus;
    PlayerData* playerData = &gPlayerData;
    Actor* player = battleStatus->playerActor;
    Actor* partner = battleStatus->partnerActor;
    ActorPart* part = &player->partsTable[0];
    Evt* script;
    s32 i;

    s8 debuffDuration;
    s32 koDuration;
    s32 temp;

    if (gBattleSubState == BTL_SUBSTATE_BEGIN_PLAYER_TURN_INIT) {
        btl_cam_use_preset(BTL_CAM_PRESET_C);
        btl_cam_move(5);
        gBattleSubState = BTL_SUBSTATE_BEGIN_PLAYER_TURN_RESET_STATE;
    }

    switch (gBattleSubState) {
        case BTL_SUBSTATE_BEGIN_PLAYER_TURN_RESET_STATE:
            if (btl_cam_is_moving_done()) {
                gBattleStatus.flags1 &= ~BS_FLAGS1_80000;
                reset_actor_turn_info();
                battleStatus->unk_86 = 127;
                battleStatus->blockResult = 127;
                battleStatus->selectedMoveID = 0;
                gBattleStatus.flags1 |= BS_FLAGS1_8;
                gBattleStatus.flags2 &= ~BS_FLAGS2_1000000;
                player->disableDismissTimer = 0;
                player->flags |= ACTOR_FLAG_8000000 | ACTOR_FLAG_4000000;

                if (partner != NULL) {
                    player->flags |= ACTOR_FLAG_8000000 | ACTOR_FLAG_4000000;
                    partner->disableDismissTimer = 0;
                }

                battleStatus->unk_8C = 0;
                D_8029F254 = 0;
                D_8029F258 = 0;

                if (battleStatus->outtaSightActive == 0) {
                    gBattleSubState = BTL_SUBSTATE_BEGIN_PLAYER_TURN_CHECK_WATER_BLOCK;
                } else {
                    battleStatus->battlePhase = PHASE_ENEMY_BEGIN;
                    script = start_script(partner->handlePhaseSource, EVT_PRIORITY_A, 0);
                    partner->handlePhaseScript = script;
                    gBattleSubState = BTL_SUBSTATE_BEGIN_PLAYER_TURN_AWAIT_OUTTA_SIGHT;
                    partner->handleBatttlePhaseScriptID = script->id;
                    script->owner1.actorID = ACTOR_PARTNER;
                }
            }
            break;
        case BTL_SUBSTATE_BEGIN_PLAYER_TURN_AWAIT_OUTTA_SIGHT:
            if (!does_script_exist(partner->handleBatttlePhaseScriptID)) {
                battleStatus->outtaSightActive = 0;
                gBattleSubState = BTL_SUBSTATE_BEGIN_PLAYER_TURN_CHECK_WATER_BLOCK;
                gBattleStatus.flags2 |= BS_FLAGS2_4;
            }
            break;
    }

    switch (gBattleSubState) {
        case BTL_SUBSTATE_BEGIN_PLAYER_TURN_CHECK_WATER_BLOCK:
            if (battleStatus->unk_8C == 0) {
                if (battleStatus->waterBlockTurnsLeft != 0) {
                    battleStatus->waterBlockTurnsLeft--;
                    battleStatus->buffEffect->data.partnerBuff->unk_0C[FX_BUFF_DATA_WATER_BLOCK].turnsLeft = battleStatus->waterBlockTurnsLeft;
                    if (battleStatus->waterBlockTurnsLeft <= 0) {
                        battleStatus->waterBlockEffect->flags |= EFFECT_INSTANCE_FLAGS_10;
                        fx_water_block(1, player->currentPos.x, player->currentPos.y + 18.0f, player->currentPos.z + 5.0f, 1.5f, 10);
                        fx_water_splash(0, player->currentPos.x - 10.0f, player->currentPos.y + 5.0f, player->currentPos.z + 5.0f, 1.0f, 24);
                        fx_water_splash(0, player->currentPos.x - 15.0f, player->currentPos.y + 32.0f, player->currentPos.z + 5.0f, 1.0f, 24);
                        fx_water_splash(1, player->currentPos.x + 15.0f, player->currentPos.y + 22.0f, player->currentPos.z + 5.0f, 1.0f, 24);
                        battleStatus->waterBlockEffect = NULL;
                        sfx_play_sound(SOUND_299);
                        btl_show_battle_message(BTL_MSG_27, 60);
                        gBattleSubState = BTL_SUBSTATE_BEGIN_PLAYER_TURN_AWAIT_WATER_BLOCK;
                    } else {
                        gBattleSubState = BTL_SUBSTATE_BEGIN_PLAYER_TURN_CHECK_CLOUD_NINE;
                    }
                } else {
                    gBattleSubState = BTL_SUBSTATE_BEGIN_PLAYER_TURN_CHECK_CLOUD_NINE;
                }
            }
            break;
        case BTL_SUBSTATE_BEGIN_PLAYER_TURN_AWAIT_WATER_BLOCK:
            if (!btl_is_popup_displayed()) {
                gBattleSubState = BTL_SUBSTATE_BEGIN_PLAYER_TURN_CHECK_CLOUD_NINE;
            }
            break;
    }

    switch (gBattleSubState) {
        case BTL_SUBSTATE_BEGIN_PLAYER_TURN_CHECK_CLOUD_NINE:
            if (battleStatus->cloudNineTurnsLeft != 0) {
                battleStatus->cloudNineTurnsLeft--;
                battleStatus->buffEffect->data.partnerBuff->unk_0C[FX_BUFF_DATA_CLOUD_NINE].turnsLeft = battleStatus->cloudNineTurnsLeft;

                if (battleStatus->cloudNineTurnsLeft <= 0) {
                    remove_effect(battleStatus->cloudNineEffect);
                    battleStatus->cloudNineEffect = NULL;
                    btl_show_battle_message(BTL_MSG_29, 60);
                    gBattleSubState = BTL_SUBSTATE_BEGIN_PLAYER_TURN_AWAIT_CLOUD_NINE;
                } else {
                    gBattleSubState = BTL_SUBSTATE_BEGIN_PLAYER_TURN_CHECK_TURBO_CHARGE;
                }
            } else {
                gBattleSubState = BTL_SUBSTATE_BEGIN_PLAYER_TURN_CHECK_TURBO_CHARGE;
            }
            break;
        case BTL_SUBSTATE_BEGIN_PLAYER_TURN_AWAIT_CLOUD_NINE:
            if (!btl_is_popup_displayed()) {
                gBattleSubState = BTL_SUBSTATE_BEGIN_PLAYER_TURN_CHECK_TURBO_CHARGE;
            }
            break;
    }

    switch (gBattleSubState) {
        case BTL_SUBSTATE_BEGIN_PLAYER_TURN_CHECK_TURBO_CHARGE:
            if (battleStatus->turboChargeTurnsLeft != 0) {
                if (gBattleStatus.flags2 & BS_FLAGS2_100) {
                    gBattleStatus.flags2 &= ~BS_FLAGS2_100;
                    gBattleSubState = BTL_SUBSTATE_BEGIN_PLAYER_TURN_TRY_STATUS_DAMAGE;
                } else {
                    battleStatus->turboChargeTurnsLeft--;
                    battleStatus->buffEffect->data.partnerBuff->unk_0C[FX_BUFF_DATA_TURBO_CHARGE].turnsLeft = battleStatus->turboChargeTurnsLeft;
                    if (battleStatus->turboChargeTurnsLeft <= 0) {
                        btl_show_battle_message(BTL_MSG_2B, 60);
                        gBattleSubState = BTL_SUBSTATE_BEGIN_PLAYER_TURN_AWAIT_TURBO_CHARGE;
                    } else {
                        gBattleSubState = BTL_SUBSTATE_BEGIN_PLAYER_TURN_TRY_STATUS_DAMAGE;
                    }
                }
            } else {
                gBattleSubState = BTL_SUBSTATE_BEGIN_PLAYER_TURN_TRY_STATUS_DAMAGE;
            }
            break;
        case BTL_SUBSTATE_BEGIN_PLAYER_TURN_AWAIT_TURBO_CHARGE:
            if (0) { // TODO relocated block - required to match
back:
                player->koStatus = STATUS_DAZE;
                player->disableEffect->data.disableX->koDuration = player->koDuration;
                goto later;
            }
            if (!btl_is_popup_displayed()) {
                gBattleSubState = BTL_SUBSTATE_BEGIN_PLAYER_TURN_TRY_STATUS_DAMAGE;
            }
            break;
    }

    if (gBattleSubState == BTL_SUBSTATE_BEGIN_PLAYER_TURN_TRY_STATUS_DAMAGE) {
        if (player->debuff == STATUS_POISON && player->stoneStatus == 0) {
            gBattleStatus.flags1 |= BS_FLAGS1_SP_EVT_ACTIVE;
            dispatch_damage_event_player_0(1, EVENT_HIT);
        }

        battleStatus->rushFlags = RUSH_FLAG_NONE;
        gBattleStatus.flags2 &= ~BS_FLAGS2_HAS_RUSH;
        if (!(gBattleStatus.flags2 & BS_FLAGS2_PEACH_BATTLE)) {
            if (playerData->curHP <= 1 && is_ability_active(ABILITY_MEGA_RUSH)) {
                gBattleStatus.flags2 |= BS_FLAGS2_HAS_RUSH;
                battleStatus->rushFlags |= RUSH_FLAG_MEGA;
            }
            if (playerData->curHP < 6 && is_ability_active(ABILITY_POWER_RUSH) && !(battleStatus->rushFlags & RUSH_FLAG_MEGA)) {
                gBattleStatus.flags2 |= BS_FLAGS2_HAS_RUSH;
                battleStatus->rushFlags |= RUSH_FLAG_POWER;
            }
        }
        gBattleSubState = BTL_SUBSTATE_BEGIN_PLAYER_TURN_TRY_STATUS_RECOVER;
    }

    if (gBattleSubState == BTL_SUBSTATE_BEGIN_PLAYER_TURN_TRY_STATUS_RECOVER) {
        if (player->handleEventScript == NULL || !does_script_exist(player->handleEventScriptID)) {
            player->handleEventScript = NULL;
            if (btl_check_player_defeated()) {
                return;
            }

            D_8029F254 = 0;
            player->disableDismissTimer = 0;
            player->flags |= ACTOR_FLAG_8000000 | ACTOR_FLAG_4000000;

            if (is_ability_active(ABILITY_FEELING_FINE)) {
                if (player->debuff != 0) {
                    player->debuffDuration = 1;
                }
                if (player->staticStatus != 0) {
                    player->staticDuration = 1;
                }
                if (player->stoneStatus != 0) {
                    player->stoneDuration = 1;
                }
                if (player->koStatus != 0) {
                    player->koDuration = 1;
                }
                if (player->transparentStatus != 0) {
                    player->transparentDuration = 1;
                }
            }

            if (player->stoneStatus != 0) {
                player->stoneDuration--;
                if (player->stoneDuration <= 0) {
                    player->stoneStatus = 0;
                    dispatch_event_player(EVENT_RECOVER_STATUS);
                }
            } else {
                if (!is_ability_active(ABILITY_ZAP_TAP) && player->staticStatus != 0) {
                    player->staticDuration--;
                    if (player->staticDuration <= 0) {
                        player->staticStatus = 0;
                        remove_status_static(player->hudElementDataIndex);
                    }
                }
                if (player->transparentStatus != 0) {
                    player->transparentDuration--;
                    part->flags |= ACTOR_PART_FLAG_100;
                    do {
                        if (player->transparentDuration <= 0) {
                            player->transparentStatus = 0;
                            part->flags &= ~ACTOR_PART_FLAG_100;
                            remove_status_transparent(player->hudElementDataIndex);
                        }
                    } while (0); // TODO required to match
                }

                if (player->debuff != 0) {
                    if (player->debuff < 9) {
                        D_8029F254 = 1;
                    }
                    D_8029F258 = 20;
                    player->debuffDuration--;
                    if (player->debuffDuration <= 0) {
                        if (player->debuff == STATUS_FROZEN) {
                            sfx_play_sound(SOUND_FROZEN_SHATTER);
                            player->icePillarEffect->flags |= 0x10;
                            player->icePillarEffect = NULL;
                            dispatch_event_player(EVENT_32);
                        } else {
                            dispatch_event_player(EVENT_RECOVER_STATUS);
                        }
                        player->debuff = 0;
                        player->debuffDuration = 0;
                        remove_status_debuff(player->hudElementDataIndex);
                    }
                }

                debuffDuration = player->debuffDuration;
                temp = player->koDuration;
                player->koDuration = debuffDuration;
                if (debuffDuration > 0) {
                    goto back;
                } else if (temp != debuffDuration) {
                    player->koStatus = 0;
                    player->koDuration = 0;
                    player->disableEffect->data.disableX->koDuration = 0;
                }
            }
    later:

            for (i = 0; i < ARRAY_COUNT(battleStatus->enemyActors); i++) {
                Actor* enemy = battleStatus->enemyActors[i];

                if (enemy != NULL) {
                    enemy->flags |= ACTOR_FLAG_8000000 | ACTOR_FLAG_4000000;
                    if (enemy->chillOutTurns != 0) {
                        enemy->chillOutTurns--;
                        if (enemy->chillOutTurns == 0) {
                            enemy->chillOutAmount = 0;
                            remove_status_chill_out(enemy->hudElementDataIndex);
                            D_8029F258 = 20;
                        }
                    }
                }
            }
            gBattleSubState = BTL_SUBSTATE_BEGIN_PLAYER_TURN_TRY_COMMAND_RECOVER;
        }
    }

    if (gBattleSubState == BTL_SUBSTATE_BEGIN_PLAYER_TURN_TRY_COMMAND_RECOVER) {
        if (btl_check_enemies_defeated()) {
            return;
        }
        temp = 1;
        battleStatus->unk_8C = 0;
        if (battleStatus->hammerLossTurns >= 0) {
            battleStatus->hammerLossTurns--;
            if (battleStatus->hammerLossTurns == -1) {
                script = start_script(&RegainAbility, EVT_PRIORITY_A, 0);
                player->takeTurnScript = script;
                player->takeTurnScriptID = script->id;
                script->owner1.actorID = ACTOR_PLAYER;
                script->varTable[0] = temp;
                temp += 8;
                script->varTable[10] = 1; // hammer
                battleStatus->unk_8C = 1;
            }
        }

        if (battleStatus->jumpLossTurns >= 0) {
            battleStatus->jumpLossTurns--;
            if (battleStatus->jumpLossTurns == -1) {
                script = start_script(&RegainAbility, EVT_PRIORITY_A, 0);
                player->takeTurnScript = script;
                player->takeTurnScriptID = script->id;
                script->owner1.actorID = ACTOR_PLAYER;
                script->varTable[0] = temp;
                temp += 8;
                script->varTable[10] = 0; // jump
                battleStatus->unk_8C = 1;
            }
        }

        if (battleStatus->itemLossTurns >= 0) {
            battleStatus->itemLossTurns--;
            if (battleStatus->itemLossTurns == -1) {
                script = start_script(&RegainAbility, EVT_PRIORITY_A, 0);
                player->takeTurnScript = script;
                player->takeTurnScriptID = script->id;
                script->owner1.actorID = ACTOR_PLAYER;
                script->varTable[0] = temp;
                temp += 8;
                script->varTable[10] = 2; // item
                battleStatus->unk_8C = 1;
            }
        }
        gBattleSubState = BTL_SUBSTATE_BEGIN_PLAYER_TURN_END_DELAY;
    }

    if (gBattleSubState == BTL_SUBSTATE_BEGIN_PLAYER_TURN_END_DELAY) {
        if (player->handleEventScript == NULL || !does_script_exist(player->handleEventScriptID)) {
            player->handleEventScript = NULL;

            if (btl_check_player_defeated() || btl_check_enemies_defeated()) {
                return;
            }

            if (D_8029F258 != 0) {
                D_8029F258--;
                return;
            }

            if (D_8029F254 == 0) {
                btl_set_state(BATTLE_STATE_SWITCH_TO_PLAYER);
            } else{
                btl_set_state(BATTLE_STATE_BEGIN_PARTNER_TURN);
                gBattleStatus.flags2 |= BS_FLAGS2_2;
            }
        }
    }
}

void btl_state_draw_begin_player_turn(void) {
}

void btl_state_update_switch_to_player(void) {
    Actor* player = gBattleStatus.playerActor;
    Actor* partner = gBattleStatus.partnerActor;
    s32 i;

    if (gBattleSubState == BTL_SUBSTATE_INIT) {
        gBattleStatus.flags1 &= ~BS_FLAGS1_80000;
        reset_actor_turn_info();
        gBattleStatus.selectedMoveID = MOVE_NONE;
        gBattleStatus.unk_86 = 127;
        gBattleStatus.blockResult = 127;
        gBattleStatus.flags1 |= BS_FLAGS1_8;
        player->flags |= ACTOR_FLAG_8000000;
        if (partner != NULL) {
            partner->flags |= (ACTOR_FLAG_8000000 | ACTOR_FLAG_4000000);
        }

        for (i = 0; i < ARRAY_COUNT(gBattleStatus.enemyActors); i++) {
            Actor* enemy = gBattleStatus.enemyActors[i];

            if (enemy != NULL) {
                enemy->flags |= ACTOR_FLAG_80000;
                enemy->flags |= ACTOR_FLAG_8000000;
            }
        }

        btl_set_state(BATTLE_STATE_PREPARE_MENU);
    }
}

void btl_state_draw_switch_to_player(void) {
}

void btl_state_update_begin_partner_turn(void) {
    BattleStatus* battleStatus = &gBattleStatus;
    Actor* partner = battleStatus->partnerActor;
    Actor* enemy;
    Evt* script;
    s32 i;

    if (gBattleSubState == BTL_SUBSTATE_BEGIN_PARTNER_TURN_INIT) {
        if (partner == NULL) {
            D_8029F254 = 1;
            gBattleSubState = BTL_SUBSTATE_BEGIN_PARTNER_TURN_END_DELAY;
        } else if ((battleStatus->flags2 & (BS_FLAGS2_4 | BS_FLAGS2_2)) != (BS_FLAGS2_4 | BS_FLAGS2_2)) {
            if (!(partner->flags & ACTOR_FLAG_NO_ATTACK)) {
                btl_cam_use_preset(BTL_CAM_PRESET_C);
                btl_cam_move(5);
                gBattleSubState = BTL_SUBSTATE_BEGIN_PARTNER_TURN_RESET_STATE;
            } else {
                btl_set_state(BATTLE_STATE_9);
                return;
            }
        } else {
            btl_set_state(BATTLE_STATE_9);
            return;
        }
    }

    if (gBattleSubState == BTL_SUBSTATE_BEGIN_PARTNER_TURN_RESET_STATE) {
        if (btl_cam_is_moving_done()) {
            D_8029F258 = 0;
            reset_actor_turn_info();
            partner = battleStatus->partnerActor;
            battleStatus->unk_86 = 127;
            battleStatus->blockResult = 127;
            D_8029F254 = 0;
            gBattleStatus.flags1 |= BS_FLAGS1_80000;
            gBattleStatus.flags2 |= BS_FLAGS1_100000;
            partner->flags |= ACTOR_FLAG_8000000;

            if (partner->koStatus != 0) {
                partner->koDuration--;
                D_8029F254 = 1;
                D_8029F258 = 20;
                if (partner->koDuration > 0) {
                    partner->disableEffect->data.disableX->koDuration = partner->koDuration;
                } else {
                    partner->koStatus = 0;
                    dispatch_event_partner(EVENT_RECOVER_PARTNER);
                    partner->disableEffect->data.disableX->koDuration = 0;
                    gBattleStatus.flags2 |= BS_FLAGS2_8;
                }
            }

            for (i = 0; i < ARRAY_COUNT(battleStatus->enemyActors); i++) {
                enemy = battleStatus->enemyActors[i];
                if (enemy != NULL) {
                    enemy->flags |= ACTOR_FLAG_8000000 | ACTOR_FLAG_4000000;
                }
            }
            gBattleSubState = BTL_SUBSTATE_BEGIN_PARTNER_TURN_AWAIT_RECOVER_DONE;
        }
    }

    if (gBattleSubState == BTL_SUBSTATE_BEGIN_PARTNER_TURN_AWAIT_RECOVER_DONE) {
        if (partner != NULL) {
            if (partner->handleEventScript == NULL || !does_script_exist(partner->handleEventScriptID)) {
                partner->handleEventScript = NULL;
            } else {
                goto block_27; // TODO find a way to remove
            }
        }

        gBattleStatus.flags2 &= ~BS_FLAGS2_8;
        if (btl_check_player_defeated() || btl_check_enemies_defeated()) {
            return;
        }
        gBattleSubState = BTL_SUBSTATE_BEGIN_PARTNER_TURN_EXEC_TURN_SCRIPT;
    }

block_27:
    if (gBattleSubState == BTL_SUBSTATE_BEGIN_PARTNER_TURN_EXEC_TURN_SCRIPT) {
        if (partner->handlePhaseSource != NULL) {
            battleStatus->battlePhase = PHASE_ENEMY_BEGIN;
            script = start_script(partner->handlePhaseSource, EVT_PRIORITY_A, 0);
            partner->handlePhaseScript = script;
            partner->handleBatttlePhaseScriptID = script->id;
            script->owner1.actorID = ACTOR_PARTNER;
        }
        gBattleSubState = BTL_SUBSTATE_BEGIN_PARTNER_TURN_AWAIT_TURN_SCRIPT;
    }

    if (gBattleSubState == BTL_SUBSTATE_BEGIN_PARTNER_TURN_AWAIT_TURN_SCRIPT) {
        if (partner->handlePhaseSource == NULL || !does_script_exist(partner->handleBatttlePhaseScriptID)) {
            gBattleSubState = BTL_SUBSTATE_BEGIN_PARTNER_TURN_END_DELAY;
        }
    }

    if (gBattleSubState == BTL_SUBSTATE_BEGIN_PARTNER_TURN_END_DELAY) {
        if (D_8029F258 != 0) {
            D_8029F258--;
            return;
        }
        gBattleStatus.flags2 &= ~BS_FLAGS2_100000;
        if (D_8029F254 == 0) {
            btl_set_state(BATTLE_STATE_SWITCH_TO_PARTNER);
        } else {
            gBattleStatus.flags2 |= BS_FLAGS2_4;
            btl_set_state(BATTLE_STATE_9);
        }
    }
}

void btl_state_draw_begin_partner_turn(void) {
}

void btl_state_update_switch_to_partner(void) {
    Actor* player = gBattleStatus.playerActor;
    Actor* partner = gBattleStatus.partnerActor;
    s32 i;

    if (gBattleSubState == BTL_SUBSTATE_INIT) {
        reset_actor_turn_info();
        gBattleStatus.flags1 |= BS_FLAGS1_80000;
        gBattleStatus.selectedMoveID = MOVE_NONE;
        gBattleStatus.unk_86 = 127;
        gBattleStatus.blockResult = 127;
        gBattleStatus.flags1 |= BS_FLAGS1_8;
        player->flags |= (ACTOR_FLAG_8000000 | ACTOR_FLAG_4000000);
        partner->flags |= ACTOR_FLAG_8000000;

        for (i = 0; i < ARRAY_COUNT(gBattleStatus.enemyActors); i++) {
            Actor* enemy = gBattleStatus.enemyActors[i];
            if (enemy != NULL) {
                enemy->flags |= ACTOR_FLAG_80000;
                enemy->flags |= ACTOR_FLAG_8000000;
            }
        }

        btl_set_state(BATTLE_STATE_PREPARE_MENU);
    }
}

void btl_state_draw_switch_to_partner(void) {
}

void btl_state_update_9(void) {
    BattleStatus* battleStatus = &gBattleStatus;
    Actor* player = battleStatus->playerActor;
    Actor* partner = battleStatus->partnerActor;
    Actor* actor;
    ActorState* state;
    Evt* script;
    s32 cond;
    s32 i;

    s32 oldKoDuration;

    if (gBattleSubState == BTL_SUBSTATE_9_INIT) {
        if (gBattleStatus.flags2 & BS_FLAGS2_2) {
            if (partner != NULL) {
                if (!(gBattleStatus.flags2 & BS_FLAGS2_4) && !(partner->flags & ACTOR_FLAG_NO_ATTACK)) {
                    btl_set_state(BATTLE_STATE_SWITCH_TO_PARTNER);
                    return;
                }
            }

            player->flags &= ~ACTOR_FLAG_8000000;
            player->flags |= ACTOR_FLAG_4000000;
            if (partner != NULL) {
                partner->flags &= ~ACTOR_FLAG_8000000;
                partner->flags |= ACTOR_FLAG_4000000;
            }

            gBattleSubState = BTL_SUBSTATE_9_1;
            D_8029F258 = 0;
            gBattleStatus.flags2 &= ~BS_FLAGS2_2;
            gBattleStatus.flags2 &= ~BS_FLAGS2_4;
            gBattleStatus.flags2 &= ~BS_FLAGS2_8;
            gBattleStatus.flags2 &= ~BS_FLAGS2_10;
        } else {
            btl_set_state(BATTLE_STATE_SWITCH_TO_PLAYER);
            return;
        }
    }

    if (gBattleSubState == BTL_SUBSTATE_9_1) {
        cond = FALSE;
        for (i = 0; i < ARRAY_COUNT(battleStatus->enemyActors); i++) {
            actor = battleStatus->enemyActors[i];
            if (actor != NULL && actor->handleEventScript != NULL) {
                if (does_script_exist(actor->handleEventScriptID)) {
                    cond = TRUE;
                } else {
                    actor->handleEventScript = NULL;
                }
            }
        }

        if (!cond) {
            reset_actor_turn_info();

            for (i = 0; i < ARRAY_COUNT(battleStatus->enemyActors); i++) {
                actor = battleStatus->enemyActors[i];
                if (actor != NULL) {
                    actor->flags |= ACTOR_FLAG_4000000 | ACTOR_FLAG_8000000;
                    actor->flags &= ~ACTOR_FLAG_10000;

                    if (actor->debuff != STATUS_END) {
                        if (actor->debuff == STATUS_FEAR ||
                            actor->debuff == STATUS_DIZZY ||
                            actor->debuff == STATUS_PARALYZE ||
                            actor->debuff == STATUS_SLEEP ||
                            actor->debuff == STATUS_FROZEN ||
                            actor->debuff == STATUS_STOP)
                        {
                            actor->flags |= ACTOR_FLAG_10000;
                        }
                        actor->debuffDuration--;
                        if (actor->debuffDuration <= 0) {
                            actor->debuff = 0;
                            remove_status_debuff(actor->hudElementDataIndex);
                            dispatch_event_actor(actor, EVENT_RECOVER_STATUS);
                            D_8029F258 = 20;
                        }
                    }

                    if (actor->staticStatus != 0) {
                        actor->staticDuration--;
                        if (actor->staticDuration <= 0) {
                            actor->staticStatus = 0;
                            remove_status_static(actor->hudElementDataIndex);
                            D_8029F258 = 20;
                        }
                    }

                    if (actor->transparentStatus != 0) {
                        actor->transparentDuration--;
                        if (actor->transparentDuration <= 0) {
                            actor->transparentStatus = 0;
                            remove_status_transparent(actor->hudElementDataIndex);
                            D_8029F258 = 20;
                        }
                    }

                    if (actor->stoneStatus != 0) {
                        actor->stoneDuration--;
                        if (actor->stoneDuration <= 0) {
                            actor->stoneStatus = 0;
                            D_8029F258 = 20;
                        }
                    }

                    oldKoDuration = actor->koDuration;
                    actor->koDuration = actor->debuffDuration;
                    if (actor->koDuration > 0) {
                        actor->koStatus = STATUS_DAZE;
                        actor->disableEffect->data.disableX->koDuration = actor->koDuration;
                    } else if (oldKoDuration != actor->koDuration) {
                        actor->koStatus = 0;
                        actor->disableEffect->data.disableX->koDuration = 0;
                    }
                    if (actor->debuff == STATUS_POISON) {
                        gBattleStatus.flags1 |= BS_FLAGS1_SP_EVT_ACTIVE;
                        dispatch_damage_event_actor_0(actor, 1, EVENT_HIT);
                        D_8029F258 = 20;
                    }
                }
            }
            gBattleSubState = BTL_SUBSTATE_9_2;
        }
    }

    if (gBattleSubState == BTL_SUBSTATE_9_2) {
        if(player->handleEventScript == NULL || !does_script_exist(player->handleEventScriptID)) {
            player->handleEventScript = NULL;
            if (partner != NULL) {
                if (partner->handleEventScript == NULL || !does_script_exist(partner->handleEventScriptID)) {
                    partner->handleEventScript = NULL;
                    goto block_52; // TODO find a way to remove
                }
            } else {
    block_52:
                cond = FALSE;
                for (i = 0; i < ARRAY_COUNT(battleStatus->enemyActors); i++) {
                    actor = battleStatus->enemyActors[i];
                    if ((actor != NULL) && (actor->handleEventScript != NULL)) {
                        if (does_script_exist(actor->handleEventScriptID)) {
                            cond = TRUE;
                        } else {
                            actor->handleEventScript = NULL;
                        }
                    }
                }

                if (!cond) {
                    if (btl_check_player_defeated() || btl_check_enemies_defeated()) {
                        return;
                    }

                    btl_cam_use_preset(BTL_CAM_PRESET_C);
                    if (partner == NULL || !(gBattleStatus.flags1 & BS_FLAGS1_100000)) {
                        gBattleSubState = BTL_SUBSTATE_9_4;
                    } else if (gBattleStatus.flags2 & BS_FLAGS2_PEACH_BATTLE) {
                        gBattleSubState = BTL_SUBSTATE_9_4;
                    } else {
                        player->flags &= ~ACTOR_FLAG_8000000;
                        partner->flags &= ~ACTOR_FLAG_8000000;
                        player->flags |= ACTOR_FLAG_4000000;
                        partner->flags |= ACTOR_FLAG_4000000;
                        state = &partner->state;
                        if (!battleStatus->outtaSightActive) {
                            partner->state.currentPos.x = partner->homePos.x;
                            partner->state.currentPos.z = partner->homePos.z;
                            partner->state.goalPos.x = player->homePos.x;
                            partner->state.goalPos.z = player->homePos.z;
                        } else {
                            partner->state.currentPos.x = partner->homePos.x;
                            partner->state.currentPos.z = partner->homePos.z;
                            partner->state.goalPos.x = partner->homePos.x;
                            partner->state.goalPos.z = partner->homePos.z + 5.0f;
                            partner->homePos.x = player->homePos.x;
                            partner->homePos.z = player->homePos.z;
                        }
                        state->moveTime = 4;
                        state->angle = 0.0f;
                        gBattleSubState = BTL_SUBSTATE_9_3;
                    }
                }
            }
        }
    }

    if (gBattleSubState == BTL_SUBSTATE_9_3) {
        if (partner->state.moveTime != 0) {
            partner->currentPos.x += (partner->state.goalPos.x - partner->currentPos.x) / partner->state.moveTime;
            partner->currentPos.z += (partner->state.goalPos.z - partner->currentPos.z) / partner->state.moveTime;
            player->currentPos.x += (partner->state.currentPos.x - player->currentPos.x) / partner->state.moveTime;
            player->currentPos.z += (partner->state.currentPos.z - player->currentPos.z) / partner->state.moveTime;
        }
        partner->currentPos.z -= sin_rad(DEG_TO_RAD(partner->state.angle)) * 16.0f;
        partner->yaw = clamp_angle(partner->state.angle);
        player->currentPos.z += sin_rad(DEG_TO_RAD(partner->state.angle)) * 16.0f;
        player->yaw = clamp_angle(partner->state.angle);
        partner->state.angle += 90.0f;

        if (partner->state.moveTime != 0) {
            partner->state.moveTime--;
        } else {
            partner->currentPos.x = partner->state.goalPos.x;
            partner->currentPos.z = partner->state.goalPos.z;
            player->currentPos.x = partner->state.currentPos.x;
            player->currentPos.z = partner->state.currentPos.z;
            if (!battleStatus->outtaSightActive) {
                partner->homePos.x = partner->currentPos.x;
                partner->homePos.z = partner->currentPos.z;
                player->homePos.x = player->currentPos.x;
                player->homePos.z = player->currentPos.z;
            } else {
                player->homePos.x = player->currentPos.x;
                player->homePos.z = player->currentPos.z;
            }
            gBattleSubState = BTL_SUBSTATE_9_4;
            gBattleStatus.flags1 &= ~ACTOR_FLAG_100000;
        }
    }

    if (gBattleSubState == BTL_SUBSTATE_9_4) {
        if (D_8029F258 != 0) {
            D_8029F258--;
        } else {
            if (battleStatus->nextMerleeSpellType == MERLEE_SPELL_2) {
                battleStatus->merleeDefenseBoost = 3;
                battleStatus->nextMerleeSpellType = MERLEE_SPELL_0;
                battleStatus->battlePhase = PHASE_MERLEE_DEFENSE_BONUS;
                script = start_script(&PlayerScriptDispatcher, EVT_PRIORITY_A, 0);
                player->takeTurnScript = script;
                player->takeTurnScriptID = script->id;
                script->owner1.actorID = ACTOR_PLAYER;
            }
            gBattleStatus.flags1 &= ~BS_FLAGS1_2;
            player->flags &= ~ACTOR_FLAG_8000000;
            player->flags |= ACTOR_FLAG_4000000;
            if (partner != NULL) {
                partner->flags &= ~ACTOR_FLAG_8000000;
                partner->flags |= ACTOR_FLAG_4000000;
            }
            gBattleSubState = BTL_SUBSTATE_9_5;
            gBattleStatus.flags2 &= ~BS_FLAGS2_2;
            gBattleStatus.flags2 &= ~BS_FLAGS2_4;
            gBattleStatus.flags2 &= ~BS_FLAGS2_8;
            gBattleStatus.flags2 &= ~BS_FLAGS2_10;
        }
    }

    if (gBattleSubState == BTL_SUBSTATE_9_5) {
        if (player->takeTurnScript == NULL || (does_script_exist(player->takeTurnScriptID) == 0)) {
            player->takeTurnScript = NULL;

            for (i = 0; i < ARRAY_COUNT(battleStatus->enemyActors); i++) {
                actor = battleStatus->enemyActors[i];
                if (actor != NULL && actor->handlePhaseSource != NULL) {
                    battleStatus->battlePhase = PHASE_PLAYER_END;
                    script = start_script(actor->handlePhaseSource, EVT_PRIORITY_A, 0);
                    actor->handlePhaseScript = script;
                    actor->handleBatttlePhaseScriptID = script->id;
                    script->owner1.enemyID = i | ACTOR_CLASS_ENEMY;
                }
            }
            gBattleSubState = BTL_SUBSTATE_9_6;
        }
    }

    cond = FALSE;
    if (gBattleSubState == BTL_SUBSTATE_9_6) {
        for (i = 0; i < ARRAY_COUNT(battleStatus->enemyActors); i++) {
            actor = battleStatus->enemyActors[i];
            if (actor != NULL && actor->handlePhaseSource != NULL && does_script_exist(actor->handleBatttlePhaseScriptID)) {
                cond = TRUE;
            }
        }
        if (!cond) {
            gBattleSubState = BTL_SUBSTATE_9_7;
        }
    }

    if (gBattleSubState == BTL_SUBSTATE_9_7) {
        btl_set_state(BATTLE_STATE_NEXT_ENEMY);
    }
}

void btl_state_draw_9(void) {
}

void btl_state_update_prepare_menu(void) {
    BattleStatus* battleStatus = &gBattleStatus;

    battleStatus->unk_4C[1] = -1;
    battleStatus->unk_4C[2] = -1;
    battleStatus->unk_4C[3] = -1;
    battleStatus->unk_4C[4] = -1;
    battleStatus->unk_4C[5] = -1;
    battleStatus->unk_4C[5] = -1;
    battleStatus->unk_4C[6] = -1;
    battleStatus->unk_4C[7] = -1;
    battleStatus->unk_5C[1] = -1;
    battleStatus->unk_5C[6] = -1;
    battleStatus->unk_5C[7] = -1;

    dma_copy(_415D90_ROM_START, _415D90_ROM_END, _415D90_VRAM);

    if (battleStatus->flags1 & BS_FLAGS1_80000) {
        btl_set_state(BATTLE_STATE_PARTNER_MENU);
    } else if (gBattleSubState == BATTLE_SUBSTATE_PREPARE_MENU_UNK_70) {
        btl_set_state(BATTLE_STATE_PLAYER_MENU);
        gBattleSubState = BTL_SUBSTATE_PLAYER_MENU_UNUSED_1;
    } else {
        btl_set_state(BATTLE_STATE_PLAYER_MENU);
    }
}

void btl_state_draw_prepare_menu(void) {
}

void btl_state_update_end_turn(void) {
    BattleStatus* battleStatus = &gBattleStatus;
    PlayerData* playerData = &gPlayerData;
    Actor* player = battleStatus->playerActor;
    Actor* partner = battleStatus->partnerActor;
    Actor* actor;
    Evt* script;
    s32 i;

    if (gBattleSubState == BTL_SUBSTATE_END_TURN_INIT) {
        s32 cond = FALSE;

        for (i = 0; i < ARRAY_COUNT(battleStatus->enemyActors); i++) {
            actor = battleStatus->enemyActors[i];
            if (actor != NULL && actor->handleEventScript != NULL) {
                if (does_script_exist(actor->handleEventScriptID)) {
                    do {
                        cond = TRUE;
                    } while (0); // TODO required to match
                } else {
                    actor->handleEventScript = NULL;
                }
            }
        }

        if (!cond) {
            for (i = 0; i < ARRAY_COUNT(battleStatus->enemyActors); i++) {
                actor = battleStatus->enemyActors[i];
                if (actor != NULL && actor->takeTurnScript != NULL) {
                    if (does_script_exist(actor->takeTurnScriptID)) {
                        cond = TRUE;
                    } else {
                        actor->takeTurnScript = NULL;
                    }
                }
            }

            if (!cond) {
                btl_cam_use_preset(BTL_CAM_PRESET_C);
                gBattleSubState = BTL_SUBSTATE_END_TURN_CHECK_FOR_SWAP;
            }
        }
    }

    if (gBattleSubState == BTL_SUBSTATE_END_TURN_CHECK_FOR_SWAP) {
        if (gBattleStatus.flags2 & BS_FLAGS2_PEACH_BATTLE) {
            gBattleSubState = BTL_SUBSTATE_END_TURN_START_SCRIPTS;
        } else if (!(gBattleStatus.flags1 & BS_FLAGS1_100000)) {
            gBattleSubState = BTL_SUBSTATE_END_TURN_START_SCRIPTS;
        } else {
            player->flags &= ~ACTOR_FLAG_8000000;
            partner->flags &= ~ACTOR_FLAG_8000000;
            player->flags |= ACTOR_FLAG_4000000;
            partner->flags |= ACTOR_FLAG_4000000;
            partner->state.currentPos.x = partner->homePos.x;
            partner->state.currentPos.z = partner->homePos.z;
            partner->state.goalPos.x = player->homePos.x;
            partner->state.goalPos.z = player->homePos.z;
            partner->state.moveTime = 4;
            partner->state.angle = 0.0f;
            gBattleSubState = BTL_SUBSTATE_END_TURN_PERFORM_SWAP;
        }
    }

    if (gBattleSubState == BTL_SUBSTATE_END_TURN_PERFORM_SWAP) {
        if (partner->state.moveTime != 0) {
            partner->currentPos.x += (partner->state.goalPos.x - partner->currentPos.x) / partner->state.moveTime;
            partner->currentPos.z += (partner->state.goalPos.z - partner->currentPos.z) / partner->state.moveTime;
            player->currentPos.x += (partner->state.currentPos.x - player->currentPos.x) / partner->state.moveTime;
            player->currentPos.z += (partner->state.currentPos.z - player->currentPos.z) / partner->state.moveTime;
        }
        partner->currentPos.z -= sin_rad(DEG_TO_RAD(partner->state.angle)) * 16.0f;
        partner->yaw = clamp_angle(partner->state.angle);
        player->currentPos.z += sin_rad(DEG_TO_RAD(partner->state.angle)) * 16.0f;
        player->yaw = clamp_angle(partner->state.angle);
        partner->state.angle += 90.0f;
        if (partner->state.moveTime != 0) {
            partner->state.moveTime--;
        } else {
            partner->currentPos.x = partner->state.goalPos.x;
            partner->currentPos.z = partner->state.goalPos.z;
            player->currentPos.x = partner->state.currentPos.x;
            player->currentPos.z = partner->state.currentPos.z;
            partner->homePos.x = partner->currentPos.x;
            partner->homePos.z = partner->currentPos.z;
            player->homePos.x = player->currentPos.x;
            player->homePos.z = player->currentPos.z;
            player->flags |= ACTOR_FLAG_8000000;
            partner->flags |= ACTOR_FLAG_8000000;
            if (gBattleStatus.flags2 & BS_FLAGS2_PEACH_BATTLE) {
                gBattleStatus.flags1 |= BS_FLAGS1_100000;
            } else {
                gBattleStatus.flags1 &= ~BS_FLAGS1_100000;
            }
            gBattleSubState = BTL_SUBSTATE_END_TURN_START_SCRIPTS;
        }
    }

    if (gBattleSubState == BTL_SUBSTATE_END_TURN_START_SCRIPTS) {
        gBattleStatus.flags2 &= ~BS_FLAGS2_10000;
        player->disableDismissTimer = 0;
        player->flags |= ACTOR_FLAG_8000000 | ACTOR_FLAG_4000000;
        if (partner != NULL) {
            player->flags |= ACTOR_FLAG_8000000 | ACTOR_FLAG_4000000;
            partner->disableDismissTimer = 0;
        }

        func_80260A60();
        gBattleStatus.flags1 &= ~BS_FLAGS1_PLAYER_DEFENDING;
        playerData->specialBarsFilled += 32;
        if (playerData->specialBarsFilled > playerData->maxStarPower * 256) {
            playerData->specialBarsFilled = playerData->maxStarPower * 256;
        }

        for (i = 0; i < ARRAY_COUNT(battleStatus->enemyActors); i++) {
            actor = battleStatus->enemyActors[i];
            if (actor != NULL && actor->handlePhaseSource != NULL) {
                battleStatus->battlePhase = PHASE_ENEMY_END;
                script = start_script(actor->handlePhaseSource, EVT_PRIORITY_A, 0);
                actor->handlePhaseScript = script;
                actor->handleBatttlePhaseScriptID = script->id;
                script->owner1.enemyID = i | ACTOR_ENEMY0;
            }
        }

        if (partner != NULL && partner->handlePhaseSource != NULL) {
            battleStatus->battlePhase = PHASE_ENEMY_END;
            script = start_script(partner->handlePhaseSource, EVT_PRIORITY_A, 0);
            partner->handlePhaseScript = script;
            partner->handleBatttlePhaseScriptID = script->id;
            script->owner1.actorID = ACTOR_PARTNER;
        }
        gBattleSubState = BTL_SUBSTATE_END_TURN_AWAIT_SCRIPTS;
    }

    // wait for all end turn scripts to finish executing
    if (gBattleSubState == BTL_SUBSTATE_END_TURN_AWAIT_SCRIPTS) {
        s32 cond = FALSE;

        for (i = 0; i < ARRAY_COUNT(battleStatus->enemyActors); i++) {
            actor = battleStatus->enemyActors[i];
            if (actor != NULL && actor->handlePhaseSource != NULL && does_script_exist(actor->handleBatttlePhaseScriptID)) {
                cond = TRUE;
            }
        }

        if (partner != NULL && partner->handlePhaseSource != NULL && does_script_exist(partner->handleBatttlePhaseScriptID)) {
            cond = TRUE;
        }

        if (!cond) {
            btl_cam_use_preset(BTL_CAM_PRESET_C);
            gBattleSubState = BTL_SUBSTATE_END_TURN_BEGIN_NEXT;
        }
    }

    // proceed to next to
    switch (gBattleSubState) {
        case BTL_SUBSTATE_END_TURN_BEGIN_NEXT:
        case BTL_SUBSTATE_END_TURN_UNK_4:
            btl_set_state(BATTLE_STATE_BEGIN_TURN);
            break;
    }
}

void btl_state_draw_end_turn(void) {
}

void btl_state_update_1C(void) {
    btl_cam_use_preset(BTL_CAM_PRESET_C);
    btl_set_state(BATTLE_STATE_PREPARE_MENU);
}

void btl_state_draw_1C(void) {
}

void btl_state_update_victory(void) {
    BattleStatus* battleStatus = &gBattleStatus;
    EncounterStatus* currentEncounter = &gCurrentEncounter;
    PlayerData* playerData = &gPlayerData;
    Actor* player = battleStatus->playerActor;
    Actor* partner = battleStatus->partnerActor;
    Evt* script;

    switch (gBattleSubState) {
        case BTL_SUBSTATE_VICTORY_UNK_0:
            player->flags &= ~(ACTOR_FLAG_8000000 | ACTOR_FLAG_4000000);
            if (partner != NULL) {
                partner->flags &= ~(ACTOR_FLAG_8000000 | ACTOR_FLAG_4000000);
            }

            battleStatus->unk_8C = 0;
            if (battleStatus->outtaSightActive == 0) {
                gBattleSubState = BTL_SUBSTATE_VICTORY_UNK_5;
            } else {
                if (battleStatus->outtaSightActive > 0) {
                    D_8029F254 = 1;
                }
                battleStatus->battlePhase = PHASE_ENEMY_BEGIN;
                script = start_script(partner->handlePhaseSource, EVT_PRIORITY_A, 0);
                partner->handlePhaseScript = script;
                partner->handleBatttlePhaseScriptID = script->id;
                script->owner1.actorID = ACTOR_PARTNER;
                gBattleSubState = BTL_SUBSTATE_VICTORY_UNK_1;
            }

            break;
        case BTL_SUBSTATE_VICTORY_UNK_1:
            if (!does_script_exist(partner->handleBatttlePhaseScriptID)) {
                battleStatus->outtaSightActive = 0;
                gBattleSubState = BTL_SUBSTATE_VICTORY_UNK_5;
            }
            break;
    }

    switch (gBattleSubState) {
        case BTL_SUBSTATE_VICTORY_UNK_5:
            player->flags &= ~(ACTOR_FLAG_8000000 | ACTOR_FLAG_4000000);
            if (partner != NULL) {
                partner->flags &= ~(ACTOR_FLAG_8000000 | ACTOR_FLAG_4000000);
            }
            gBattleSubState = BTL_SUBSTATE_VICTORY_UNK_B;
            gBattleStatus.flags2 &= ~BS_FLAGS2_2;
            gBattleStatus.flags2 &= ~BS_FLAGS2_4;
            gBattleStatus.flags2 &= ~BS_FLAGS2_8;
            gBattleStatus.flags2 &= ~BS_FLAGS2_10;

            gBattleStatus.flags1 &= ~BS_FLAGS1_8;
            if (player->koStatus == STATUS_DAZE) {
                dispatch_event_player(EVENT_RECOVER_PARTNER);
                gBattleSubState = BTL_SUBSTATE_VICTORY_UNK_A;
            }
            player->debuff = 0;
            player->staticStatus = 0;
            player->stoneStatus = 0;
            player->transparentStatus = 0;
            player->koStatus = 0;
            player->koDuration = 0;
            player->disableEffect->data.disableX->koDuration = 0;

            if (partner != NULL) {
                if (partner->koStatus == STATUS_DAZE) {
                    dispatch_event_partner(EVENT_RECOVER_PARTNER);
                    gBattleSubState = BTL_SUBSTATE_VICTORY_UNK_A;
                }
                partner->debuff = 0;
                partner->staticStatus = 0;
                partner->stoneStatus = 0;
                partner->transparentStatus = 0;
                partner->koStatus = 0;
                partner->koDuration = 0;
                partner->disableEffect->data.disableX->koDuration = 0;
            }
            break;
        case BTL_SUBSTATE_VICTORY_UNK_A:
            if (player->handleEventScript == NULL || !does_script_exist(player->handleEventScriptID)) {
                player->handleEventScript = NULL;
                if (partner != NULL) {
                    if (partner->handleEventScript == NULL || !does_script_exist(partner->handleEventScriptID)) {
                        partner->handleEventScript = NULL;
                    } else {
                        break;
                    }
                }
                gBattleSubState = BTL_SUBSTATE_VICTORY_UNK_B;
            }
            break;
    }

    if (gBattleSubState == BTL_SUBSTATE_VICTORY_UNK_B) {
        if (partner == NULL || !(gBattleStatus.flags1 & BS_FLAGS1_100000)) {
            gBattleSubState = BTL_SUBSTATE_VICTORY_UNK_2;
        } else {
            partner->state.currentPos.x = partner->currentPos.x;
            partner->state.currentPos.z = partner->currentPos.z;
            partner->state.goalPos.x = player->currentPos.x;
            partner->state.goalPos.z = player->currentPos.z;
            partner->state.moveTime = 4;
            partner->state.angle = 0.0f;
            gBattleSubState = BTL_SUBSTATE_VICTORY_UNK_C;
        }
    }

    if (gBattleSubState == BTL_SUBSTATE_VICTORY_UNK_C) {
        if (partner->state.moveTime != 0) {
            partner->currentPos.x += (partner->state.goalPos.x - partner->currentPos.x)
                                                            / partner->state.moveTime;
            partner->currentPos.z += (partner->state.goalPos.z - partner->currentPos.z)
                                                            / partner->state.moveTime;
            player->currentPos.x += (partner->state.currentPos.x - player->currentPos.x)
                                                            / partner->state.moveTime;
            player->currentPos.z += (partner->state.currentPos.z - player->currentPos.z)
                                                            / partner->state.moveTime;
        }
        partner->currentPos.z += sin_rad(DEG_TO_RAD(partner->state.angle)) * 16.0f;
        partner->yaw = clamp_angle(-partner->state.angle);
        player->currentPos.z -= sin_rad(DEG_TO_RAD(partner->state.angle)) * 16.0f;
        player->yaw = clamp_angle(-partner->state.angle);
        partner->state.angle += 90.0f;

        if (partner->state.moveTime != 0) {
            partner->state.moveTime--;
        } else {
            partner->currentPos.x = partner->state.goalPos.x;
            partner->currentPos.z = partner->state.goalPos.z;
            player->currentPos.x = partner->state.currentPos.x;
            player->currentPos.z = partner->state.currentPos.z;
            partner->homePos.x = partner->currentPos.x;
            partner->homePos.z = partner->currentPos.z;
            player->homePos.x = player->currentPos.x;
            player->homePos.z = player->currentPos.z;
            gBattleSubState = BTL_SUBSTATE_VICTORY_UNK_2;
            gBattleStatus.flags1 &= ~BS_FLAGS1_100000;
        }
    }

    if (gBattleSubState == BTL_SUBSTATE_VICTORY_UNK_2) {
        btl_cam_use_preset(BTL_CAM_PRESET_C);
        if (battleStatus->nextMerleeSpellType == MERLEE_SPELL_3) {
            if (battleStatus->totalStarPoints == 0) {
                battleStatus->nextMerleeSpellType = MERLEE_SPELL_0;
                playerData->merleeTurnCount = 0;
                playerData->merleeCastsLeft++;
            } else {
                battleStatus->battlePhase = PHASE_MERLEE_EXP_BONUS;
                script = start_script(&PlayerScriptDispatcher, EVT_PRIORITY_A, 0);
                player->takeTurnScript = script;
                player->takeTurnScriptID = script->id;
                script->owner1.actorID = ACTOR_PLAYER;
            }
        }
        gBattleSubState = BTL_SUBSTATE_VICTORY_UNK_3;
        D_8029F248 = 0;
        gBattleStatus.flags1 &= ~BS_FLAGS1_2;
    }

    if (gBattleSubState == BTL_SUBSTATE_VICTORY_UNK_3) {
        if (D_8029F248 != 0) {
            D_8029F248--;
        } else if (player->takeTurnScript == NULL || !does_script_exist(player->takeTurnScriptID)) {
            player->takeTurnScript = NULL;
            if (battleStatus->nextMerleeSpellType != MERLEE_SPELL_3) {
                gBattleSubState = BTL_SUBSTATE_VICTORY_UNK_4;
            } else {
                battleStatus->incrementStarPointDelay = 20;
                battleStatus->nextMerleeSpellType = MERLEE_SPELL_0;
                gBattleSubState = BTL_SUBSTATE_VICTORY_UNK_4;
                battleStatus->pendingStarPoints = battleStatus->totalStarPoints
                                        + battleStatus->pendingStarPoints + battleStatus->pendingStarPoints;
            }
        }
    }

    if (gBattleSubState == BTL_SUBSTATE_VICTORY_UNK_4) {
        if (battleStatus->pendingStarPoints <= 0) {
            if (gBattleStatus.flags1 & BS_FLAGS1_STAR_POINTS_DROPPED) {
                gBattleStatus.flags1 &= ~BS_FLAGS1_ENEMY_FLED;
            }
            if (playerData->battlesWon < 9999) {
                playerData->battlesWon++;
            }
            if (gBattleStatus.flags1 & BS_FLAGS1_ENEMY_FLED) {
                currentEncounter->battleOutcome = OUTCOME_ENEMY_FLED;
            } else {
                currentEncounter->battleOutcome = OUTCOME_PLAYER_WON;
            }
            if (gBattleStatus.flags1 & BS_FLAGS1_DISABLE_CELEBRATION) {
                if (!(gBattleStatus.flags2 & BS_FLAGS2_DONT_STOP_MUSIC)) {
                    bgm_set_song(0, -1, 0, 1500, 8);
                }
                btl_set_state(BATTLE_STATE_END_BATTLE);
            } else {
                btl_set_state(BATTLE_STATE_CELEBRATION);
            }
        }
    }
}

void btl_state_draw_victory(void) {
}

void btl_state_update_end_training_battle(void) {
    BattleStatus* battleStatus = &gBattleStatus;
    PlayerData* playerData = &gPlayerData;
    EncounterStatus* encounterStatus = &gCurrentEncounter;
    Actor* player = gBattleStatus.playerActor;
    Actor* partner = gBattleStatus.partnerActor;

    switch (gBattleSubState) {
        case BTL_SUBSTATE_END_TRAINING_UNK_0:
            player->flags &= ~(ACTOR_FLAG_8000000 | ACTOR_FLAG_4000000);
            if (partner != NULL) {
                partner->flags &= ~(ACTOR_FLAG_8000000 | ACTOR_FLAG_4000000);
            }
            gBattleSubState = BTL_SUBSTATE_END_TRAINING_UNK_B;
            gBattleStatus.flags2 &= ~BS_FLAGS2_2;
            gBattleStatus.flags2 &= ~BS_FLAGS2_4;
            gBattleStatus.flags2 &= ~BS_FLAGS2_8;
            gBattleStatus.flags2 &= ~BS_FLAGS2_10;

            if (player->koStatus == STATUS_DAZE) {
                dispatch_event_player(EVENT_RECOVER_PARTNER);
                gBattleSubState = BTL_SUBSTATE_END_TRAINING_UNK_A;
            }
            player->debuff = 0;
            player->staticStatus = 0;
            player->stoneStatus = 0;
            player->transparentStatus = 0;
            player->koStatus = 0;
            player->koDuration = 0;
            player->disableEffect->data.disableX->koDuration = 0;
            if (partner != NULL) {
                if (partner->koStatus == STATUS_DAZE) {
                    dispatch_event_partner(EVENT_RECOVER_PARTNER);
                    gBattleSubState = BTL_SUBSTATE_END_TRAINING_UNK_A;
                }
                partner->debuff = 0;
                partner->staticStatus = 0;
                partner->stoneStatus = 0;
                partner->transparentStatus = 0;
                partner->koStatus = 0;
                partner->koDuration = 0;
                partner->disableEffect->data.disableX->koDuration = 0;
            }
            break;
        case BTL_SUBSTATE_END_TRAINING_UNK_A:
            if (player->handleEventScript == NULL || !does_script_exist(player->handleEventScriptID)) {
                player->handleEventScript = NULL;
                if (partner != NULL) {
                    if (partner->handleEventScript == NULL || !does_script_exist(partner->handleEventScriptID)) {
                        partner->handleEventScript = NULL;
                    } else {
                        break;
                    }
                }
                gBattleSubState = BTL_SUBSTATE_END_TRAINING_UNK_B;
            }
            break;
    }

    switch (gBattleSubState) {
        case BTL_SUBSTATE_END_TRAINING_UNK_B:
            battleStatus->unk_8C = 0;
            gBattleStatus.flags2 &= ~BS_FLAGS2_2;
            gBattleStatus.flags2 &= ~BS_FLAGS2_4;
            gBattleStatus.flags2 &= ~BS_FLAGS2_8;
            gBattleStatus.flags2 &= ~BS_FLAGS2_10;

            if (!battleStatus->outtaSightActive) {
                gBattleSubState = BTL_SUBSTATE_END_TRAINING_UNK_D;
            } else {
                Evt* script;

                battleStatus->battlePhase = PHASE_ENEMY_BEGIN;
                script = start_script(partner->handlePhaseSource, EVT_PRIORITY_A, 0);
                partner->handlePhaseScript = script;
                gBattleSubState = BTL_SUBSTATE_END_TRAINING_UNK_C;
                partner->handleBatttlePhaseScriptID = script->id;
                script->owner1.actorID = ACTOR_PARTNER;
            }
            break;
        case BTL_SUBSTATE_END_TRAINING_UNK_D:
            if (!does_script_exist(partner->handleBatttlePhaseScriptID)) {
                battleStatus->outtaSightActive = FALSE;
                gBattleSubState = BTL_SUBSTATE_END_TRAINING_UNK_D;
            }
            break;
    }

    switch (gBattleSubState) {
        case BTL_SUBSTATE_END_TRAINING_UNK_D:
            btl_cam_use_preset(BTL_CAM_PRESET_C);
            D_8029F248 = 30;
            gBattleSubState = BTL_SUBSTATE_END_TRAINING_UNK_E;
            break;
        case BTL_SUBSTATE_END_TRAINING_UNK_E:
            if (D_8029F248 != 0) {
                D_8029F248--;
                return;
            }
            if (playerData->trainingsDone < 9999) {
                playerData->trainingsDone++;
            }
            encounterStatus->battleOutcome = OUTCOME_ENEMY_FLED;
            if (!(gBattleStatus.flags2 & BS_FLAGS2_DONT_STOP_MUSIC)) {
                bgm_set_song(0, -1, 0, 1500, 8);
            }
            btl_set_state(BATTLE_STATE_END_BATTLE);
            break;
    }
}

void btl_state_draw_end_training_battle(void) {
}

void btl_state_update_end_battle(void) {
    Battle* blah = (*D_800DC4FC);
    EncounterStatus* encounterStatus = &gCurrentEncounter;
    BattleStatus* battleStatus = &gBattleStatus;
    Stage* stage;
    Evt* script;
    s32 i;

    switch (gBattleSubState) {
        case BTL_SUBSTATE_END_BATTLE_UNK_0:
            D_80280A30 = 0;
            if (gGameStatusPtr->debugEnemyContact == DEBUG_CONTACT_DIE_ON_TOUCH) {
                D_80280A30 = 255;
            }
            if (encounterStatus->battleOutcome == OUTCOME_PLAYER_LOST && !(gBattleStatus.flags1 & BS_FLAGS1_NO_GAME_OVER)) {
                btl_cam_unfreeze();
                btl_cam_use_preset(BTL_CAM_PRESET_B);
                set_screen_overlay_color(0, 0, 0, 0);
                set_screen_overlay_center(0, 0, 160, 120);
            }
            gBattleSubState = BTL_SUBSTATE_END_BATTLE_UNK_1;
            break;
        case BTL_SUBSTATE_END_BATTLE_UNK_1:
            if (D_80280A30 == 255) {
                gBattleSubState = BTL_SUBSTATE_END_BATTLE_UNK_2;
                break;
            }
            D_80280A30 += battleStatus->unk_8D;
            if (D_80280A30 > 255) {
                D_80280A30 = 255;
            }
            break;
        case BTL_SUBSTATE_END_BATTLE_UNK_2:
            D_80280A30 = 255;
            gBattleStatus.flags1 &= ~BS_FLAGS1_ACTORS_VISIBLE;
            if (D_800DC064 == NULL) {
                stage = blah->stage;
            } else {
                stage = D_800DC064->stage;;
            }
            if (stage->postBattle == NULL) {
                gBattleSubState = BTL_SUBSTATE_END_BATTLE_CLEANUP;
                return;
            }
            script = start_script(stage->postBattle, EVT_PRIORITY_A, 0);
            battleStatus->controlScript = script;
            battleStatus->controlScriptID = script->id;
            gBattleSubState = BTL_SUBSTATE_END_BATTLE_AWAIT_STAGE_SCRIPT;
            break;
        case BTL_SUBSTATE_END_BATTLE_AWAIT_STAGE_SCRIPT:
            if (!does_script_exist(battleStatus->controlScriptID)) {
                gBattleSubState = BTL_SUBSTATE_END_BATTLE_CLEANUP;
                // fallthrough
            } else {
                break;
            }
        case BTL_SUBSTATE_END_BATTLE_CLEANUP:
            kill_all_scripts();
            for (i = 0; i < ARRAY_COUNT(battleStatus->enemyActors); i++) {
                if (battleStatus->enemyActors[i] != NULL) {
                    btl_delete_actor(battleStatus->enemyActors[i]);
                }
            }
            if (battleStatus->partnerActor != NULL) {
                btl_delete_actor(battleStatus->partnerActor);
            }

            btl_delete_player_actor(battleStatus->playerActor);

            if (battleStatus->nextMerleeSpellType == MERLEE_SPELL_4) {
                encounterStatus->merleeCoinBonus = TRUE;
                battleStatus->nextMerleeSpellType = MERLEE_SPELL_0;
            }

            encounterStatus->damageTaken = battleStatus->damageTaken;

            if (gBattleStatus.flags2 & BS_FLAGS2_DROP_WHACKA_BUMP) {
                encounterStatus->dropWhackaBump = TRUE;
            }

            remove_all_effects();
            set_windows_visible(0);

            if (gBattleStatus.flags2 & BS_FLAGS2_PEACH_BATTLE) {
                decrement_status_menu_disabled();
            }

            if (encounterStatus->battleOutcome == OUTCOME_PLAYER_LOST &&
                !(gBattleStatus.flags1 & BS_FLAGS1_NO_GAME_OVER))
            {
                s16 areaID;
                s16 mapID;

                btl_set_state(BATTLE_STATE_0);
                D_800DC4D0 = gBattleState;
                get_map_IDs_by_name("gv_01", &areaID, &mapID);
                gGameStatusPtr->areaID = areaID;
                gGameStatusPtr->mapID = mapID;
                gGameStatusPtr->entryID = gv_01_ENTRY_0;
                set_game_mode(GAME_MODE_ENTER_WORLD);
            } else {
                btl_set_state(BATTLE_STATE_0);
                D_800DC4D0 = gBattleState;
                func_8003E514(1);
                set_game_mode(GAME_MODE_END_BATTLE);
            }
            break;
    }
}

void btl_state_draw_end_battle(void) {
    Camera* camera = &gCameras[gCurrentCameraID];

    if (gCurrentEncounter.battleOutcome == OUTCOME_PLAYER_LOST && !(gBattleStatus.flags1 & BS_FLAGS1_NO_GAME_OVER)) {
        camera->auxBoomZOffset += 256;
        set_screen_overlay_params_front(7, D_80280A30);
    } else {
        set_screen_overlay_params_front(0, D_80280A30);
    }
}

void btl_state_update_defend(void) {
    Actor* player = gBattleStatus.playerActor;
    Evt* script;

    switch (gBattleSubState) {
        case BTL_SUBSTATE_DEFEND_INIT:
            gBattleStatus.unk_8C = 0;
            gBattleStatus.battlePhase = PHASE_USE_DEFEND;
            player->takeTurnScript = script = start_script(&PlayerScriptDispatcher, EVT_PRIORITY_A, 0);
            player->takeTurnScriptID = script->id;
            gBattleSubState = BTL_SUBSTATE_DEFEND_AWAIT_SCRIPT;
            script->owner1.actorID = ACTOR_PLAYER;
            break;
        case BTL_SUBSTATE_DEFEND_AWAIT_SCRIPT:
            if (!does_script_exist(player->takeTurnScriptID) && gBattleStatus.unk_8C == 0) {
                btl_set_state(BATTLE_STATE_END_PLAYER_TURN);
            }
            break;
    }
}

void btl_state_draw_defend(void) {
}

void btl_state_update_run_away(void) {
    BattleStatus* battleStatus = &gBattleStatus;
    PlayerData* playerData = &gPlayerData;
    EncounterStatus* currentEncounter = &gCurrentEncounter;
    Actor* player = battleStatus->playerActor;
    Actor* partner = battleStatus->partnerActor;
    Actor* enemy;
    s32 var_s0;
    f32 var_f2;
    Evt* script;
    s32 i;

    switch (gBattleSubState) {
        case BTL_SUBSTATE_RUN_AWAY_UNK_0:
            battleStatus->unk_8C = 0;
            gBattleStatus.flags1 &= ~BS_FLAGS1_ENEMY_FLED;
            gBattleStatus.flags2 |= BS_FLAGS2_10 | BS_FLAGS2_8 | BS_FLAGS2_4 | BS_FLAGS2_2;
            playerData->unk_2A6++;
            btl_cam_use_preset(BTL_CAM_PRESET_25);
            var_s0 = 0;
            btl_cam_target_actor(ACTOR_PLAYER);
            var_f2 = 0.0f;

            for (i = 0; i < ARRAY_COUNT(battleStatus->enemyActors); i++) {
                enemy = battleStatus->enemyActors[i];
                if (enemy != NULL) {
                    if (!(enemy->flags & ACTOR_FLAG_TARGET_ONLY)) {
                        if (!(enemy->flags & ACTOR_FLAG_NO_DMG_APPLY)) {
                            f32 escapeChance = enemy->actorBlueprint->escapeChance;

                            var_s0 += 1;
                            if (enemy->debuff == 3 ||
                                enemy->debuff == 4 ||
                                enemy->debuff == 5 ||
                                enemy->debuff == 6 ||
                                enemy->debuff == 7 ||
                                enemy->debuff == 8)
                            {
                                escapeChance = 100.0f;
                            }
                            var_f2 += escapeChance;
                        }
                    }
                }
            }

            player->state.varTable[0] = var_f2 / var_s0;
            if (gGameStatusPtr->debugEnemyContact == DEBUG_CONTACT_AUTO_FLEE) {
                player->state.varTable[0] = 100;
            }
            battleStatus->battlePhase = PHASE_RUN_AWAY_START;
            script = start_script(&PlayerScriptDispatcher, EVT_PRIORITY_A, 0);
            player->takeTurnScript = script;
            player->takeTurnScriptID = script->id;
            script->owner1.actorID = ACTOR_PLAYER;
            if (partner != NULL && partner->koStatus == 0) {
                script = start_script(partner->takeTurnSource, EVT_PRIORITY_A, 0);
                partner->takeTurnScript = script;
                partner->takeTurnScriptID = script->id;
                script->owner1.actorID = ACTOR_PARTNER;
            }
            gBattleSubState = BTL_SUBSTATE_RUN_AWAY_UNK_2;
            break;
        case BTL_SUBSTATE_RUN_AWAY_UNK_2:
            if (!does_script_exist(player->takeTurnScriptID) && battleStatus->unk_8C == 0) {
                if (!(gBattleStatus.flags1 & BS_FLAGS1_ENEMY_FLED)) {
                    gBattleSubState = BTL_SUBSTATE_RUN_AWAY_UNK_3;
                } else {
                    currentEncounter->battleOutcome = OUTCOME_PLAYER_FLED;
                    if (is_ability_active(ABILITY_RUNAWAY_PAY) == 0) {
                        gBattleSubState = BTL_SUBSTATE_RUN_AWAY_UNK_B;
                    } else {
                        status_menu_start_blinking_starpoints();
                        func_8023E104();
                        D_8029F264 = 0;
                        D_8029F24C = 0;
                        D_80280A30 = 0;
                        D_8029F25C = battleStatus->totalStarPoints * 100;
                        D_8029F250 = 20;
                        D_8029F260 = D_8029F25C / D_8029F250;
                        gBattleSubState = BTL_SUBSTATE_RUN_AWAY_UNK_A;
                    }
                }
            }
            break;
    }

    if (gBattleSubState == BTL_SUBSTATE_RUN_AWAY_UNK_A) {
        if (battleStatus->totalStarPoints != 0) {
            s8 temp_v1_4;

            D_8029F25C -= D_8029F260;
            temp_v1_4 = D_8029F25C / 100;
            var_s0 = battleStatus->totalStarPoints - temp_v1_4;
            battleStatus->totalStarPoints = temp_v1_4;

            if (var_s0 > 0) {
                sfx_play_sound(SOUND_211);
            }
            playerData->starPoints += var_s0;
            D_80280A30 += 1;
            if (D_8029F250 == 0 && battleStatus->totalStarPoints != 0) {
                playerData->starPoints++;
            }
        }
        if (playerData->starPoints >= 99) {
            playerData->starPoints = 99;
        }
        if (battleStatus->totalStarPoints == 0) {
            if (D_8029F250 != 0) {
                D_8029F250--;
            } else {
                status_menu_stop_blinking_starpoints();
                func_8023E11C();
                gBattleSubState = BTL_SUBSTATE_RUN_AWAY_UNK_B;
            }
        }
    }

    if (gBattleSubState == BTL_SUBSTATE_RUN_AWAY_UNK_B) {
        playerData->battlesFled++;
        if (!(gBattleStatus.flags2 & BS_FLAGS2_DONT_STOP_MUSIC)) {
            bgm_set_song(0, -1, 0, 1500, 8);
        }
        btl_set_state(BATTLE_STATE_END_BATTLE);
    }

    switch (gBattleSubState) {
        case BTL_SUBSTATE_RUN_AWAY_UNK_3:
            battleStatus->battlePhase = PHASE_RUN_AWAY_FAIL;
            script = start_script(&PlayerScriptDispatcher, EVT_PRIORITY_A, 0);
            player->takeTurnScript = script;
            player->takeTurnScriptID = script->id;
            script->owner1.actorID = ACTOR_PLAYER;
            if (partner != NULL && partner->koStatus == 0) {
                script = start_script(partner->takeTurnSource, EVT_PRIORITY_A, 0);
                partner->takeTurnScript = script;
                partner->takeTurnScriptID = script->id;
                script->owner1.actorID = ACTOR_PARTNER;
            }
            gBattleSubState = BTL_SUBSTATE_RUN_AWAY_UNK_4;
            break;
        case BTL_SUBSTATE_RUN_AWAY_UNK_4:
            if (D_8029F248 != 0) {
                D_8029F248--;
                return;
            }
            if (!does_script_exist(player->takeTurnScriptID) &&
                (partner == NULL || !does_script_exist(partner->takeTurnScriptID)) &&
                battleStatus->unk_8C == 0)
            {
                btl_set_state(BATTLE_STATE_9);
            }
            break;
    }
}

void btl_state_draw_run_away(void) {
}

void btl_state_update_defeat(void) {
    BattleStatus* battleStatus = &gBattleStatus;
    EncounterStatus* currentEncounter = &gCurrentEncounter;
    Actor* player = battleStatus->playerActor;
    Actor* partner = battleStatus->partnerActor;
    Evt* script;

    switch (gBattleSubState) {
        case BTL_SUBSTATE_DEFEAT_UNK_0:
            battleStatus->flags1 &= ~BS_FLAGS1_8;
            gBattleStatus.flags2 &= ~BS_FLAGS2_2;
            gBattleStatus.flags2 &= ~BS_FLAGS2_4;
            gBattleStatus.flags2 &= ~BS_FLAGS2_8;
            gBattleStatus.flags2 &= ~BS_FLAGS2_10;
            battleStatus->unk_8C = 0;

            if (player->debuff != 0) {
                if (player->debuff == 7) {
                    sfx_play_sound(SOUND_FROZEN_SHATTER);
                    player->icePillarEffect->flags |= EFFECT_INSTANCE_FLAGS_10;
                    player->icePillarEffect = NULL;
                }
                player->debuff = 0;
                player->debuffDuration = 0;
                remove_status_debuff(player->hudElementDataIndex);
                player->koStatus = 0;
                player->koDuration = 0;
                player->disableEffect->data.disableX->koDuration = 0;
            }

            btl_cam_use_preset(BTL_CAM_PRESET_25);
            btl_cam_target_actor(0);
            battleStatus->battlePhase = PHASE_RUN_AWAY_RESET;
            script = start_script(&PlayerScriptDispatcher, EVT_PRIORITY_A, 0);
            player->takeTurnScript = script;
            player->takeTurnScriptID = script->id;
            script->owner1.actorID = ACTOR_PLAYER;

            if (partner != NULL) {
                script = start_script(partner->takeTurnSource, EVT_PRIORITY_A, 0);
                partner->takeTurnScript = script;
                partner->takeTurnScriptID = script->id;
                script->owner1.actorID = ACTOR_PARTNER;
            }
            gBattleSubState = BTL_SUBSTATE_DEFEAT_UNK_1;
            break;
        case BTL_SUBSTATE_DEFEAT_UNK_1:
            if (!does_script_exist(player->takeTurnScriptID) && battleStatus->unk_8C == 0) {
                if (find_item(ITEM_LIFE_SHROOM) >= 0) {
                    battleStatus->battlePhase = PHASE_USE_LIFE_SHROOM;
                    script = start_script(&PlayerScriptDispatcher, EVT_PRIORITY_A, 0);
                    player->takeTurnScript = script;
                    player->takeTurnScriptID = script->id;
                    script->owner1.actorID = ACTOR_PLAYER;
                    gBattleSubState = BTL_SUBSTATE_DEFEAT_UNK_2;
                } else {
                    gBattleSubState = BTL_SUBSTATE_DEFEAT_UNK_A;
                }
            }
            break;
        case BTL_SUBSTATE_DEFEAT_UNK_2:
            if (!does_script_exist(player->takeTurnScriptID) && battleStatus->unk_8C == 0) {
                gBattleSubState = BTL_SUBSTATE_DEFEAT_UNK_A;
            }
            break;
    }

    if (gBattleSubState == BTL_SUBSTATE_DEFEAT_UNK_A) {
        currentEncounter->battleOutcome = OUTCOME_PLAYER_LOST;
        if (!(gBattleStatus.flags2 & BS_FLAGS2_DONT_STOP_MUSIC)) {
            bgm_set_song(0, -1, 0, 1500, 8);
        }
        btl_set_state(BATTLE_STATE_END_BATTLE);
    }
}

void btl_state_draw_defeat(void) {
}

ApiStatus EnablePartnerBlur(Evt* script, s32 isInitialCall) {
    enable_partner_blur();
    return ApiStatus_DONE2;
}

ApiStatus DisablePartnerBlur(Evt* script, s32 isInitialCall) {
    disable_partner_blur();
    return ApiStatus_DONE2;
}

void btl_state_update_change_partner(void) {
    BattleStatus* battleStatus = &gBattleStatus;
    Actor* player = battleStatus->playerActor;
    Actor* partner = battleStatus->partnerActor;
    ActorState* state = &player->state;
    PlayerData* playerData = &gPlayerData;
    Actor* enemyActor;
    Evt* script;
    s32 i;

    switch (gBattleSubState) {
        case BTL_SUBSTATE_CHANGE_PARTNER_UNK_0:
            player->flags &= ~ACTOR_FLAG_8000000;
            partner->flags &= ~ACTOR_FLAG_8000000;
            battleStatus->unk_8C = 0;
            gBattleStatus.flags2 |= BS_FLAGS2_10;
            btl_cam_use_preset(BTL_CAM_PRESET_19);
            btl_cam_set_target_pos(-89.0, 40.0, -99.0);
            btl_cam_set_zoom(372);
            btl_cam_set_zoffset(0);
            gBattleStatus.flags1 &= ~BS_FLAGS1_2;

            for (i = 0; i < ARRAY_COUNT(battleStatus->enemyActors); i++) {
                enemyActor = battleStatus->enemyActors[i];
                if (enemyActor != NULL) {
                    enemyActor->flags &= ~ACTOR_FLAG_80000;
                    enemyActor->flags &= ~ACTOR_FLAG_8000000;
                }
            }

            battleStatus->unk_5C[0] = -1;
            D_8029F248 = 10;
            gBattleSubState = BTL_SUBSTATE_CHANGE_PARTNER_UNK_2;

        case BTL_SUBSTATE_CHANGE_PARTNER_UNK_2:
            if (D_8029F248 != 0) {
                D_8029F248--;
                break;
            }
            deduct_current_move_fp();
            script = start_script(&BtlPutPartnerAway, EVT_PRIORITY_A, 0);
            battleStatus->controlScript = script;
            battleStatus->controlScriptID = script->id;
            script->owner1.actorID = ACTOR_PARTNER;
            state->unk_18.x = partner->currentPos.x;
            state->unk_18.y = 0.0f;
            state->unk_18.z = partner->currentPos.z;
            gBattleSubState = BTL_SUBSTATE_CHANGE_PARTNER_UNK_3;
            break;
        case BTL_SUBSTATE_CHANGE_PARTNER_UNK_3:
            if (!does_script_exist(battleStatus->controlScriptID)) {
                btl_delete_actor(partner);
                playerData->currentPartner = battleStatus->unk_1AC;
                load_partner_actor();
                partner = battleStatus->partnerActor;
                partner->scale.x = 0.1f;
                partner->scale.y = 0.1f;
                partner->scale.z = 0.1f;
                partner->state.goalPos.x = state->unk_18.x;
                partner->state.goalPos.y = partner->currentPos.y;
                partner->state.goalPos.z = state->unk_18.z;
                partner->currentPos.x = player->currentPos.x;
                partner->currentPos.y = player->currentPos.y + 25.0f;
                partner->currentPos.z = player->currentPos.z;
                gBattleSubState = BTL_SUBSTATE_CHANGE_PARTNER_UNK_4;
            }
            break;
        case BTL_SUBSTATE_CHANGE_PARTNER_UNK_4:
            partner = battleStatus->partnerActor;
            if (partner != NULL) {
                if (!does_script_exist(partner->takeTurnScriptID)) {
                    partner->takeTurnScript = NULL;
                } else {
                    break;
                }
            }

            script = start_script(&BtlBringPartnerOut, EVT_PRIORITY_A, 0);
            battleStatus->controlScript = script;
            battleStatus->controlScriptID = script->id;
            script->owner1.actorID = ACTOR_PARTNER;
            gBattleSubState = BTL_SUBSTATE_CHANGE_PARTNER_UNK_5;
            break;
        case BTL_SUBSTATE_CHANGE_PARTNER_UNK_5:
            if (!does_script_exist(battleStatus->controlScriptID)) {
                partner = battleStatus->partnerActor;
                if (partner != NULL) {
                    if (partner->handlePhaseSource != NULL) {
                        battleStatus->battlePhase = PHASE_PLAYER_BEGIN;
                        script = start_script(partner->handlePhaseSource, EVT_PRIORITY_A, 0);
                        partner->handlePhaseScript = script;
                        partner->handleBatttlePhaseScriptID = script->id;
                        script->owner1.actorID = ACTOR_PARTNER;
                    }
                }
                gBattleSubState = BTL_SUBSTATE_CHANGE_PARTNER_UNK_6;
            }
            break;
        case BTL_SUBSTATE_CHANGE_PARTNER_UNK_6:
            partner = battleStatus->partnerActor;
            if (partner == NULL || partner->handlePhaseSource == NULL
                                || !does_script_exist(partner->handleBatttlePhaseScriptID)) {
                btl_cam_use_preset(BTL_CAM_PRESET_C);
                gBattleSubState = BTL_SUBSTATE_CHANGE_PARTNER_UNK_7;
            }
            break;
        case BTL_SUBSTATE_CHANGE_PARTNER_UNK_7:
            if (battleStatus->unk_8C == 0) {
                gBattleStatus.flags2 &= ~BS_FLAGS2_10;
                if (!(gBattleStatus.flags1 & BS_FLAGS1_80000)) {
                    if (player_team_is_ability_active(player, ABILITY_QUICK_CHANGE) != FALSE) {
                        btl_set_state(BATTLE_STATE_PREPARE_MENU);
                    } else {
                        btl_set_state(BATTLE_STATE_END_PLAYER_TURN);
                    }
                } else {
                    if (player_team_is_ability_active(player, ABILITY_QUICK_CHANGE) == FALSE) {
                        btl_set_state(BATTLE_STATE_END_PARTNER_TURN);
                    } else {
                        btl_set_state(BATTLE_STATE_PREPARE_MENU);
                    }
                }
            }
            break;
    }
}

void btl_state_draw_change_partner(void) {
}

void btl_state_update_player_move(void) {
    BattleStatus* battleStatus = &gBattleStatus;
    Actor* player = battleStatus->playerActor;
    Actor* partner = battleStatus->partnerActor;
    s32 messageIndex;
    Actor* actor;
    Evt* script;
    s32 foundEnemy;
    s8 tipIndex;
    s32 i;

    if (gBattleSubState == BTL_SUBSTATE_PLAYER_MOVE_INIT) {
        battleStatus->unk_86 = 127;
        battleStatus->blockResult = 127;
        battleStatus->unk_8C = 0;
        battleStatus->lastAttackDamage = 0;
        battleStatus->unk_19A = 0;
        gBattleStatus.flags1 &= ~BS_FLAGS1_AUTO_SUCCEED_ACTION;
        gBattleStatus.flags1 &= ~BS_FLAGS1_2;
        reset_actor_turn_info();
        player->flags &= ~ACTOR_FLAG_8000000;
        if (partner != NULL) {
            partner->flags &= ~ACTOR_FLAG_8000000;
        }
        btl_cam_target_actor(0);
        gBattleStatus.flags1 &= ~BS_FLAGS1_8;
        player->status = 0;
        gBattleStatus.flags2 |= BS_FLAGS2_8;
        gBattleStatus.flags1 &= ~BS_FLAGS1_200000;

        for (i = 0; i < ARRAY_COUNT(battleStatus->enemyActors); i++) {
            actor = battleStatus->enemyActors[i];
            if (actor != NULL) {
                actor->status = 0;
            }
        }

        for (i = 0; i < ARRAY_COUNT(battleStatus->enemyActors); i++) {
            actor = battleStatus->enemyActors[i];
            if (actor != NULL) {
                actor->flags &= ~ACTOR_FLAG_80000;
                actor->flags &= ~ACTOR_FLAG_8000000;
            }
        }

        if (battleStatus->moveCategory == BTL_MENU_TYPE_JUMP || battleStatus->moveCategory == BTL_MENU_TYPE_SMASH) {
            if (battleStatus->nextMerleeSpellType == MERLEE_SPELL_1) {
                battleStatus->merleeAttackBoost = 3;
                battleStatus->nextMerleeSpellType = MERLEE_SPELL_0;
                battleStatus->battlePhase = PHASE_MERLEE_ATTACK_BONUS;
                script = start_script(&PlayerScriptDispatcher, EVT_PRIORITY_A, 0);
                player->takeTurnScript = script;
                player->takeTurnScriptID = script->id;
                script->owner1.actorID = ACTOR_PLAYER;
                gBattleStatus.flags1 |= BS_FLAGS1_10000;
                close_action_command_instruction_popup();
                gBattleSubState = BTL_SUBSTATE_PLAYER_MOVE_BEGIN_SHOW_TIP;
            } else {
                gBattleSubState = BTL_SUBSTATE_PLAYER_MOVE_EXECUTE_MOVE;
                gBattleStatus.flags1 &= ~BS_FLAGS1_2;
            }
        } else {
            gBattleSubState = BTL_SUBSTATE_PLAYER_MOVE_EXECUTE_MOVE;
            gBattleStatus.flags1 &= ~BS_FLAGS1_2;
        }
    }

    switch (gBattleSubState) {
        case BTL_SUBSTATE_PLAYER_MOVE_BEGIN_SHOW_TIP:
            if (player->takeTurnScript == NULL || !does_script_exist(player->takeTurnScriptID)) {
                player->takeTurnScript = NULL;
                if (!is_ability_active(ABILITY_BERSERKER)) {
                    if (battleStatus->selectedMoveID != MOVE_NONE) {
                        tipIndex = gMoveTable[battleStatus->selectedMoveID].actionTip;
                        if (tipIndex >= 0) {
                            btl_show_battle_message(BTL_MSG_2E + tipIndex, 60);
                        }
                    }
                }
                D_8029F248 = 2;
                gBattleSubState = BTL_SUBSTATE_PLAYER_MOVE_SHOW_TIP_DELAY;
            }
            break;
        case BTL_SUBSTATE_PLAYER_MOVE_SHOW_TIP_DELAY:
            if (D_8029F248 != 0) {
                D_8029F248--;
            } else {
                gBattleSubState = BTL_SUBSTATE_PLAYER_MOVE_EXECUTE_MOVE;
            }
            break;
    }

    switch (gBattleSubState) {
        case BTL_SUBSTATE_PLAYER_MOVE_EXECUTE_MOVE:
            gBattleStatus.flags1 &= ~BS_FLAGS1_4000;
            gBattleStatus.flags1 &= ~BS_FLAGS1_10000;
            increment_status_menu_disabled();
            gBattleStatus.flags1 |= BS_FLAGS1_100;
            reset_all_actor_sounds(player);
            battleStatus->battlePhase = PHASE_EXECUTE_ACTION;
            if (gBattleStatus.flags2 & BS_FLAGS2_PEACH_BATTLE) {
                script = start_script(&PeachScriptDispatcher, EVT_PRIORITY_A, 0);
            } else {
                script = start_script(&PlayerScriptDispatcher, EVT_PRIORITY_A, 0);
            }
            player->takeTurnScript = script;
            gBattleSubState = BTL_SUBSTATE_PLAYER_MOVE_HANDLE_RESULTS;
            player->takeTurnScriptID = script->id;
            script->owner1.actorID = ACTOR_PLAYER;
            break;
        case BTL_SUBSTATE_PLAYER_MOVE_HANDLE_RESULTS:
            // wait for player battle phase script to finish
            if (!(gBattleStatus.flags1 & BS_FLAGS1_200000)) {
                if (player->takeTurnScript != NULL && does_script_exist(player->takeTurnScriptID)) {
                    break;
                }
                player->takeTurnScript = NULL;
            }

            gBattleStatus.flags1 &= ~BS_FLAGS1_100;

             // wait for player battle event script to finish
            if (player->handleEventScript != NULL && does_script_exist(player->handleEventScriptID)) {
                break;
            }
            player->handleEventScript = NULL;

            // wait for partner battle event script to finish
            if (partner != NULL) {
                if (partner->handleEventScript != NULL && does_script_exist(partner->handleEventScriptID)) {
                    break;
                }
                partner->handleEventScript = NULL;
            }

            // wait for all enemy battle phase scripts to finish
            foundEnemy = FALSE;
            for (i = 0; i < ARRAY_COUNT(battleStatus->enemyActors); i++) {
                actor = battleStatus->enemyActors[i];
                if (actor != NULL && actor->takeTurnScript != NULL) {
                    if (does_script_exist(actor->takeTurnScriptID)) {
                        foundEnemy = TRUE;
                    } else {
                        actor->takeTurnScript = NULL;
                    }
                }
            }
            if (foundEnemy) {
                break;
            }

            // wait for all enemy battle event scripts to finish
            foundEnemy = FALSE;
            for (i = 0; i < ARRAY_COUNT(battleStatus->enemyActors); i++) {
                actor = battleStatus->enemyActors[i];
                if (actor != NULL && actor->handleEventScript != NULL) {
                    if (does_script_exist(actor->handleEventScriptID)) {
                        foundEnemy = TRUE;
                    } else {
                        actor->handleEventScript = NULL;
                    }
                }
            }
            if (foundEnemy) {
                break;
            }

            for (i = 0; i < ARRAY_COUNT(battleStatus->enemyActors); i++) {
                actor = battleStatus->enemyActors[i];
                if (actor != NULL) {
                    actor->flags &= ~ACTOR_FLAG_80000;
                }
            }

            if (battleStatus->unk_8C != 0) {
                break;
            }
            
            if (gGameStatusPtr->demoFlags & 1) {
                btl_set_state(BATTLE_STATE_END_DEMO_BATTLE);
                break;
            }

            decrement_status_menu_disabled();
            gBattleStatus.flags1 |= BS_FLAGS1_8;
            gBattleStatus.flags2 &= ~BS_FLAGS2_8;
            if (btl_check_player_defeated()) {
                return;
            }

            if (battleStatus->moveCategory == BTL_MENU_TYPE_SMASH) {
                if ((battleStatus->selectedMoveID != MOVE_SMASH_CHARGE0) &&
                    (battleStatus->selectedMoveID != MOVE_SMASH_CHARGE) &&
                    (battleStatus->selectedMoveID != MOVE_SUPER_SMASH_CHARGE))
                {
                    gBattleStatus.flags1 &= ~BS_FLAGS1_HAMMER_CHARGED;
                }
            }
            if (battleStatus->moveCategory == BTL_MENU_TYPE_JUMP) {
                if ((battleStatus->selectedMoveID != MOVE_JUMP_CHARGE0) &&
                    (battleStatus->selectedMoveID != MOVE_JUMP_CHARGE) &&
                    (battleStatus->selectedMoveID != MOVE_SUPER_JUMP_CHARGE))
                {
                    gBattleStatus.flags1 &= ~BS_FLAGS1_JUMP_CHARGED;
                }
            }

            if (!(gBattleStatus.flags1 & BS_FLAGS1_JUMP_CHARGED)) {
                battleStatus->jumpCharge = 0;
            }
            if (!(gBattleStatus.flags1 & BS_FLAGS1_HAMMER_CHARGED)) {
                battleStatus->hammerCharge = 0;
            }

            for (i = 0; i < ARRAY_COUNT(battleStatus->enemyActors); i++) {
                actor = battleStatus->enemyActors[i];
                if (actor != NULL && !(actor->flags & ACTOR_FLAG_NO_DMG_APPLY)) {
                    actor->flags |= ACTOR_FLAG_8000000 | ACTOR_FLAG_4000000;
                }
            }

            btl_update_ko_status();

            foundEnemy = FALSE;
            for (i = 0; i < ARRAY_COUNT(battleStatus->enemyActors); i++) {
                actor = battleStatus->enemyActors[i];
                if (actor != NULL) {
                    if (actor->status != 0) {
                        foundEnemy = TRUE;
                        break;
                    }
                }
            }

            if (!foundEnemy) {
                gBattleSubState = BTL_SUBSTATE_PLAYER_MOVE_CHECK_PLAYER_STATUS;
            } else {
                btl_cam_use_preset(BTL_CAM_PRESET_D);
                switch (actor->status) {
                    case 4:
                        messageIndex = BTL_MSG_12;
                        break;
                    case 6:
                        messageIndex = BTL_MSG_13;
                        break;
                    case 7:
                        messageIndex = BTL_MSG_14;
                        break;
                    case 9:
                        messageIndex = BTL_MSG_15;
                        break;
                    case 10:
                        messageIndex = BTL_MSG_16;
                        break;
                    case 5:
                        messageIndex = BTL_MSG_17;
                        break;
                    case 11:
                        messageIndex = BTL_MSG_18;
                        break;
                    case 8:
                        messageIndex = BTL_MSG_19;
                        break;
                    default:
                        messageIndex = 0;
                        gBattleSubState = BTL_SUBSTATE_PLAYER_MOVE_CHECK_PLAYER_STATUS;
                        break;
                }
                sfx_play_sound(SOUND_2107);
                btl_show_battle_message(messageIndex, 60);
                for (i = 0; i < ARRAY_COUNT(battleStatus->enemyActors); i++) {
                    actor = battleStatus->enemyActors[i];
                    if (actor != NULL) {
                        actor->status = 0;
                    }
                }
                gBattleSubState = BTL_SUBSTATE_PLAYER_MOVE_AWAIT_ENEMY_STATUS_POPUP;
            }
            break;
        case BTL_SUBSTATE_PLAYER_MOVE_AWAIT_ENEMY_STATUS_POPUP:
            if (!btl_is_popup_displayed()) {
                btl_cam_use_preset(BTL_CAM_PRESET_C);
                btl_cam_move(15);
                D_8029F248 = 10;
                gBattleSubState = BTL_SUBSTATE_PLAYER_MOVE_POST_ENEMY_STATUS_POPUP;
            }
            break;
        case BTL_SUBSTATE_PLAYER_MOVE_POST_ENEMY_STATUS_POPUP:
            if (D_8029F248 != 0) {
                D_8029F248--;
            } else {
                gBattleSubState = BTL_SUBSTATE_PLAYER_MOVE_CHECK_PLAYER_STATUS;
            }
            break;
    }

    switch (gBattleSubState) {
        case BTL_SUBSTATE_PLAYER_MOVE_CHECK_PLAYER_STATUS:
            if (player->status != 0) {
                btl_cam_use_preset(BTL_CAM_PRESET_33);
                switch (player->status) {
                    case 4:
                        messageIndex = BTL_MSG_0A;
                        break;
                    case 6:
                        messageIndex = BTL_MSG_0B;
                        break;
                    case 7:
                        messageIndex = BTL_MSG_0C;
                        break;
                    case 9:
                        messageIndex = BTL_MSG_0D;
                        break;
                    case 10:
                        messageIndex = BTL_MSG_0E;
                        break;
                    case 5:
                        messageIndex = BTL_MSG_0F;
                        break;
                    case 11:
                        messageIndex = BTL_MSG_10;
                        break;
                    default:
                        messageIndex = 0;
                        gBattleSubState = BTL_SUBSTATE_PLAYER_MOVE_AWAIT_DONE;
                        break;
                }
                btl_show_battle_message(messageIndex, 60);
                player->status = 0;
                player->disableDismissTimer = 0;
                player->flags |= ACTOR_FLAG_8000000;
                gBattleSubState = BTL_SUBSTATE_PLAYER_MOVE_AWAIT_PLAYER_STATUS_POPUP;
                
            } else {
                gBattleSubState = BTL_SUBSTATE_PLAYER_MOVE_AWAIT_DONE;
            }
            break;
        case BTL_SUBSTATE_PLAYER_MOVE_AWAIT_PLAYER_STATUS_POPUP:
            if (!btl_is_popup_displayed()) {
                btl_cam_use_preset(BTL_CAM_PRESET_C);
                btl_cam_move(15);
                D_8029F248 = 10;
                gBattleSubState = BTL_SUBSTATE_PLAYER_MOVE_POST_PLAYER_STATUS_POPUP;
            }
            break;
        case BTL_SUBSTATE_PLAYER_MOVE_POST_PLAYER_STATUS_POPUP:
            if (D_8029F248 != 0) {
                D_8029F248--;
            } else {
                gBattleSubState = BTL_SUBSTATE_PLAYER_MOVE_AWAIT_DONE;
            }
            break;
    }

    if (gBattleSubState == BTL_SUBSTATE_PLAYER_MOVE_AWAIT_DONE) {
        if (player->takeTurnScript == NULL || !does_script_exist(player->takeTurnScriptID)) {
            player->takeTurnScript = NULL;
            btl_set_state(BATTLE_STATE_END_PLAYER_TURN);
        }
    }
}

void btl_state_draw_player_move(void) {
}

void btl_state_update_end_player_turn(void) {
    BattleStatus* battleStatus = &gBattleStatus;
    Actor* player = battleStatus->playerActor;
    Actor* partner = battleStatus->partnerActor;
    Evt* script;

    if (gBattleSubState == BTL_SUBSTATE_END_PLAYER_TURN_UNK_0) {
        if (battleStatus->moveCategory == BTL_MENU_TYPE_ITEM && battleStatus->itemUsesLeft >= 2) {
            gBattleSubState = BTL_SUBSTATE_END_PLAYER_TURN_UNK_5;
        } else if (
            !(gBattleStatus.flags2 & BS_FLAGS2_HAS_DRAINED_HP) &&
            !is_ability_active(ABILITY_HAPPY_HEART) &&
            !is_ability_active(ABILITY_CRAZY_HEART) &&
            !is_ability_active(ABILITY_HAPPY_FLOWER))
        {
            gBattleSubState = BTL_SUBSTATE_END_PLAYER_TURN_UNK_5;
        } else if (player->stoneStatus == STATUS_STONE || battleStatus->outtaSightActive) {
            gBattleSubState = BTL_SUBSTATE_END_PLAYER_TURN_UNK_5;
        } else {
            s32 prevHPDrainCount = 0;
            s32 hpRecovery = 0;
            s32 fpRecovery = 0;

            if (gBattleStatus.flags2 & BS_FLAGS2_HAS_DRAINED_HP) {
                prevHPDrainCount = battleStatus->hpDrainCount;
                battleStatus->hpDrainCount = 0;
            }

            if (rand_int(100) < 50) {
                hpRecovery = is_ability_active(ABILITY_CRAZY_HEART) * 3;
            }
            if (rand_int(100) < 50) {
                hpRecovery += is_ability_active(ABILITY_HAPPY_HEART);
            }
            if (rand_int(100) < 50) {
                fpRecovery = is_ability_active(ABILITY_HAPPY_FLOWER);
            }

            if (prevHPDrainCount + hpRecovery + fpRecovery == 0) {
                gBattleSubState = BTL_SUBSTATE_END_PLAYER_TURN_UNK_5;
            } else {
                battleStatus->battlePhase = PHASE_PLAYER_HAPPY;
                script = start_script(&PlayerScriptDispatcher, EVT_PRIORITY_A, 0);
                player->takeTurnScript = script;
                player->takeTurnScriptID = script->id;
                script->owner1.actorID = ACTOR_PLAYER;
                if (gBattleStatus.flags2 & BS_FLAGS2_HAS_DRAINED_HP) {
                    script->varTable[10] += battleStatus->hpDrainCount;
                    battleStatus->hpDrainCount = 0;
                }
                script->varTable[10] = prevHPDrainCount;
                script->varTable[11] = hpRecovery;
                script->varTable[12] = fpRecovery;

                if (script->varTable[10] > 99) {
                    script->varTable[10] = 99;
                }
                if (script->varTable[11] > 99) {
                    script->varTable[11] = 99;
                }
                if (script->varTable[12] > 99) {
                    script->varTable[12] = 99;
                }

                gBattleStatus.flags2 &= ~BS_FLAGS2_HAS_DRAINED_HP;
                gBattleSubState = BTL_SUBSTATE_END_PLAYER_TURN_UNK_5;
            }
        }
    }

    if (gBattleSubState == BTL_SUBSTATE_END_PLAYER_TURN_UNK_5) {
        if ((player->takeTurnScript == NULL) || !does_script_exist(player->takeTurnScriptID)) {
            player->takeTurnScript = NULL;
            if (!(gBattleStatus.flags2 & BS_FLAGS2_PEACH_BATTLE) || (gBattleStatus.flags1 & BS_FLAGS1_100000)) {
                gBattleSubState = BTL_SUBSTATE_END_PLAYER_TURN_UNK_A;
            } else {
                player->state.currentPos.x = player->homePos.x;
                player->state.currentPos.z = player->homePos.z;
                player->state.goalPos.x = partner->homePos.x;
                player->state.goalPos.z = partner->homePos.z;
                player->state.moveTime = 4;
                player->state.angle = 0.0f;
                gBattleSubState = BTL_SUBSTATE_END_PLAYER_TURN_UNK_6;
            }
        }
    }

    if (gBattleSubState == BTL_SUBSTATE_END_PLAYER_TURN_UNK_6) {
        if (player->state.moveTime != 0) {
            player->currentPos.x += (player->state.goalPos.x - player->currentPos.x) / player->state.moveTime;
            player->currentPos.z += (player->state.goalPos.z - player->currentPos.z) / player->state.moveTime;
            partner->currentPos.x += (player->state.currentPos.x - partner->currentPos.x) / player->state.moveTime;
            partner->currentPos.z += (player->state.currentPos.z - partner->currentPos.z) / player->state.moveTime;
        }
        player->currentPos.z += sin_rad((player->state.angle * TAU) / 360.0f) * 16.0f;
        player->yaw = clamp_angle(-player->state.angle);
        partner->currentPos.z -= sin_rad((player->state.angle * TAU) / 360.0f) * 16.0f;
        partner->yaw = clamp_angle(-player->state.angle);
        player->state.angle += 90.0f;

        if (player->state.moveTime != 0) {
            player->state.moveTime--;
        } else {
            player->currentPos.x = player->state.goalPos.x;
            player->currentPos.z = player->state.goalPos.z;
            partner->currentPos.x = player->state.currentPos.x;
            partner->currentPos.z = player->state.currentPos.z;
            player->homePos.x = player->currentPos.x;
            player->homePos.z = player->currentPos.z;
            partner->homePos.x = partner->currentPos.x;
            partner->homePos.z = partner->currentPos.z;
            gBattleStatus.flags1 |= BS_FLAGS1_100000;
            gBattleSubState = BTL_SUBSTATE_END_PLAYER_TURN_UNK_A;
        }
    }

    if (gBattleSubState == BTL_SUBSTATE_END_PLAYER_TURN_UNK_A) {
        if(!btl_check_enemies_defeated()) {
            if (battleStatus->moveCategory == BTL_MENU_TYPE_ITEM && battleStatus->itemUsesLeft >= 2) {
                btl_cam_use_preset(BTL_CAM_PRESET_C);
                btl_cam_move(10);
                gBattleStatus.flags2 &= ~BS_FLAGS2_2;
            } else {
                gBattleStatus.flags2 |= BS_FLAGS2_2;
            }

            if (battleStatus->unk_94 < 0) {
                battleStatus->unk_94 = 0;
                battleStatus->itemUsesLeft = 0;
                btl_set_state(BATTLE_STATE_END_TURN);
                return;
            }

            if (battleStatus->itemUsesLeft != 0) {
                battleStatus->itemUsesLeft--;
                if (battleStatus->itemUsesLeft != 0) {
                    btl_set_state(BATTLE_STATE_PREPARE_MENU);
                    gBattleSubState = BATTLE_SUBSTATE_PREPARE_MENU_UNK_70;
                    return;
                }

                if (gBattleStatus.flags1 & BS_FLAGS1_HUSTLED) {
                    if (battleStatus->hustleTurns != 0) {
                        battleStatus->hustleTurns--;
                    }
                }

                if (battleStatus->hustleTurns != 0 && (gBattleStatus.flags1 & BS_FLAGS1_HUSTLED)) {
                    gBattleStatus.flags2 &= ~BS_FLAGS2_2;

                    btl_set_state(BATTLE_STATE_PREPARE_MENU);
                } else {
                    gBattleStatus.flags1 &= ~BS_FLAGS1_HUSTLED;
                    btl_set_state(BATTLE_STATE_BEGIN_PARTNER_TURN);
                }
                return;
            }

            if (gBattleStatus.flags1 & BS_FLAGS1_HUSTLED) {
                if (battleStatus->hustleTurns != 0) {
                    battleStatus->hustleTurns--;
                }
            }

            if (battleStatus->hustleTurns != 0 && (gBattleStatus.flags1 & BS_FLAGS1_HUSTLED)) {
                gBattleStatus.flags2 &= ~BS_FLAGS2_2;
                btl_set_state(BATTLE_STATE_PREPARE_MENU);
            } else {
                gBattleStatus.flags1 &= ~BS_FLAGS2_HAS_DRAINED_HP;
                if (!(gBattleStatus.flags2 & BS_FLAGS2_PEACH_BATTLE)) {
                    btl_set_state(BATTLE_STATE_BEGIN_PARTNER_TURN);
                } else {
                    btl_set_state(BATTLE_STATE_9);
                }
            }
        }
    }
}

void btl_state_draw_end_player_turn(void) {
}

void btl_state_update_partner_move(void) {
    BattleStatus* battleStatus = &gBattleStatus;
    PlayerData* playerData = &gPlayerData;
    Actor* player = battleStatus->playerActor;
    Actor* partner = battleStatus->partnerActor;
    Actor* enemyActor;
    Evt* script;
    s8 switchCondition;
    s32 phi_s3;
    s32 messageIndex;
    s32 i;

    switch (gBattleSubState) {
        case BTL_SUBSTATE_PARTNER_MOVE_UNK_0:
            if (partner == NULL) {
                btl_set_state(BATTLE_STATE_9);
            } else {
                battleStatus->unk_8C = 0;
                battleStatus->unk_86 = 127;
                battleStatus->blockResult = 127;
                battleStatus->unk_19A = 0;
                gBattleStatus.flags1 &= ~BS_FLAGS1_AUTO_SUCCEED_ACTION;
                gBattleStatus.flags1 &= ~BS_FLAGS1_2;
                reset_actor_turn_info();
                partner->status = 0;
                partner->flags &= ~ACTOR_FLAG_8000000;
                player->flags &= ~ACTOR_FLAG_8000000;
                deduct_current_move_fp();
                btl_cam_target_actor(ACTOR_PARTNER);
                gBattleStatus.flags2 |= BS_FLAGS2_10;
                gBattleStatus.flags1 &= ~BS_FLAGS1_200000;

                for (i = 0; i < ARRAY_COUNT(battleStatus->enemyActors); i++) {
                    enemyActor = battleStatus->enemyActors[i];
                    if (enemyActor != NULL) {
                        enemyActor->status = 0;
                    }
                }
                btl_cam_use_preset(BTL_CAM_PRESET_C);
                gBattleSubState = BTL_SUBSTATE_PARTNER_MOVE_UNK_2;
            }
            break;
        case BTL_SUBSTATE_PARTNER_MOVE_UNK_2:
            for (i = 0; i < ARRAY_COUNT(battleStatus->enemyActors); i++) {
                enemyActor = battleStatus->enemyActors[i];
                if (enemyActor != NULL) {
                    enemyActor->flags &= ~ACTOR_FLAG_80000;
                    enemyActor->flags &= ~ACTOR_FLAG_8000000;
                }
            }

            increment_status_menu_disabled();
            gBattleStatus.flags1 |= BS_FLAGS1_100;
            reset_actor_turn_info();
            reset_all_actor_sounds(partner);
            battleStatus->battlePhase = PHASE_EXECUTE_ACTION;
            script = start_script(partner->takeTurnSource, EVT_PRIORITY_A, 0);
            partner->takeTurnScript = script;
            partner->takeTurnScriptID = script->id;
            script->owner1.actorID = ACTOR_PARTNER;
            gBattleSubState = BTL_SUBSTATE_PARTNER_MOVE_UNK_3;
            break;
        case BTL_SUBSTATE_PARTNER_MOVE_UNK_3:
            if (!(gBattleStatus.flags1 & BS_FLAGS1_200000)) {
                if (partner->takeTurnScript == NULL || !does_script_exist(partner->takeTurnScriptID)) {
                    partner->takeTurnScript = NULL;
                } else {
                    break;
                }
            }
            gBattleStatus.flags1 &= ~BS_FLAGS1_100;

            if ((partner->handleEventScript == NULL || !does_script_exist(partner->handleEventScriptID))
                && ((partner->handleEventScript = NULL, player->handleEventScript == NULL)
                    || !does_script_exist(player->handleEventScriptID))) {

                player->handleEventScript = NULL;
                for (phi_s3 = FALSE, i = 0; i < ARRAY_COUNT(battleStatus->enemyActors); i++) {
                    enemyActor = battleStatus->enemyActors[i];
                    if (enemyActor != NULL && enemyActor->takeTurnScript != NULL) {
                        if (does_script_exist(enemyActor->takeTurnScriptID)) {
                            phi_s3 = TRUE;
                        } else {
                            enemyActor->takeTurnScript = NULL;
                        }
                    }
                }

                if (phi_s3 == FALSE) {
                    for (i = 0; i < ARRAY_COUNT(battleStatus->enemyActors); i++) {
                        enemyActor = battleStatus->enemyActors[i];
                        if (enemyActor != NULL && enemyActor->handleEventScript != NULL) {
                            if (does_script_exist(enemyActor->handleEventScriptID)) {
                                phi_s3 = TRUE;
                            } else {
                                enemyActor->handleEventScript = NULL;
                            }
                        }
                    }

                    if (phi_s3 == FALSE) {
                        for (i = 0; i < ARRAY_COUNT(battleStatus->enemyActors); i++) {
                            enemyActor = battleStatus->enemyActors[i];
                            if (enemyActor != NULL) {
                                enemyActor->flags &= ~ACTOR_FLAG_80000;
                            }
                        }
                        if (battleStatus->unk_8C == 0) {
                            if (gGameStatusPtr->demoFlags & 1) {
                                btl_set_state(BATTLE_STATE_END_DEMO_BATTLE);
                                break;
                            }
                            decrement_status_menu_disabled();
                            if (playerData->currentPartner == PARTNER_GOOMBARIO && battleStatus->moveCategory == BTL_MENU_TYPE_5
                                                                && battleStatus->selectedMoveID != MOVE_CHARGE) {
                                partner->isGlowing = 0;
                                gBattleStatus.flags1 &= ~BS_FLAGS1_40000000;
                            }
                            if (btl_check_player_defeated()) {
                                return;
                            }

                            for (i = 0; i < ARRAY_COUNT(battleStatus->enemyActors); i++) {
                                enemyActor = battleStatus->enemyActors[i];
                                if (enemyActor != NULL) {
                                    if (!(enemyActor->flags & ACTOR_FLAG_NO_DMG_APPLY)) {
                                        enemyActor->flags |= (ACTOR_FLAG_8000000 | ACTOR_FLAG_4000000);
                                    }
                                }
                            }

                            btl_update_ko_status();

                            if (partner->status == 0xD && !btl_are_all_enemies_defeated()) {
                                btl_cam_use_preset(BTL_CAM_PRESET_54);
                                btl_show_battle_message(BTL_MSG_23, 60);
                                partner->status = 0;
                                partner->disableDismissTimer = 0;
                                gBattleSubState = BTL_SUBSTATE_PARTNER_MOVE_UNK_B;
                                partner->flags |= ACTOR_FLAG_8000000;
                            } else {
                                gBattleSubState = BTL_SUBSTATE_PARTNER_MOVE_UNK_14;
                            }
                        }
                    }
                }
            }
            break;
        case BTL_SUBSTATE_PARTNER_MOVE_UNK_B:
            if (btl_is_popup_displayed() == FALSE) {
                btl_cam_use_preset(BTL_CAM_PRESET_C);
                btl_cam_move(15);
                D_8029F248 = 10;
                gBattleSubState = BTL_SUBSTATE_PARTNER_MOVE_UNK_C;
            }
            break;
        case BTL_SUBSTATE_PARTNER_MOVE_UNK_C:
            if (D_8029F248 != 0) {
                D_8029F248--;
            } else {
                gBattleSubState = BTL_SUBSTATE_PARTNER_MOVE_UNK_14;
            }
            break;
    }

    switch (gBattleSubState) {
        case BTL_SUBSTATE_PARTNER_MOVE_UNK_14:
            for (phi_s3 = FALSE, i = 0; i < ARRAY_COUNT(battleStatus->enemyActors); i++) {
                enemyActor = battleStatus->enemyActors[i];
                if (enemyActor != NULL) {
                    if ((s8)enemyActor->status != 0) {
                        phi_s3 = TRUE;
                        break;
                    }
                }
            }

            if (phi_s3 == FALSE) {
                gBattleSubState = BTL_SUBSTATE_PARTNER_MOVE_UNK_1E;
            } else {
                btl_cam_use_preset(BTL_CAM_PRESET_D);
                switchCondition = enemyActor->status - 4;
                switch (switchCondition) {
                    case 0:
                        messageIndex = BTL_MSG_12;
                        break;
                    case 2:
                        messageIndex = BTL_MSG_13;
                        break;
                    case 3:
                        messageIndex = BTL_MSG_14;
                        break;
                    case 5:
                        messageIndex = BTL_MSG_15;
                        break;
                    case 6:
                        messageIndex = BTL_MSG_16;
                        break;
                    case 1:
                        messageIndex = BTL_MSG_17;
                        break;
                    case 7:
                        messageIndex = BTL_MSG_18;
                        break;
                    case 4:
                        messageIndex = BTL_MSG_19;
                        break;
                    default:
                        messageIndex = 0;
                        gBattleSubState = BTL_SUBSTATE_PARTNER_MOVE_UNK_14;
                        break;
                }

                sfx_play_sound(SOUND_2107);
                btl_show_battle_message(messageIndex, 60);

                for (i = 0; i < ARRAY_COUNT(battleStatus->enemyActors); i++) {
                    enemyActor = battleStatus->enemyActors[i];
                    if (enemyActor != NULL) {
                        enemyActor->status = 0;
                    }
                }
                gBattleSubState = BTL_SUBSTATE_PARTNER_MOVE_UNK_15;
            }
            break;
        case BTL_SUBSTATE_PARTNER_MOVE_UNK_15:
            if (btl_is_popup_displayed() == FALSE) {
                btl_cam_use_preset(BTL_CAM_PRESET_C);
                btl_cam_move(15);
                D_8029F248 = 10;
                gBattleSubState = BTL_SUBSTATE_PARTNER_MOVE_UNK_16;
            }
            break;
        case BTL_SUBSTATE_PARTNER_MOVE_UNK_16:
            if (D_8029F248 != 0) {
                D_8029F248--;
            } else {
                gBattleSubState = BTL_SUBSTATE_PARTNER_MOVE_UNK_1E;
            }
            break;
    }

    if (gBattleSubState == BTL_SUBSTATE_PARTNER_MOVE_UNK_1E) {
        if (partner->takeTurnScript != NULL && does_script_exist(partner->takeTurnScriptID)) {
            return;
        }
        partner->takeTurnScript = NULL;
        btl_set_state(BATTLE_STATE_END_PARTNER_TURN);
    }
}

void btl_state_draw_partner_move(void) {
}

void btl_state_update_end_partner_turn(void) {
    BattleStatus* battleStatus = &gBattleStatus;

    if (gBattleSubState == BTL_SUBSTATE_INIT) {
        battleStatus->flags2 |= BS_FLAGS2_4;
        if (btl_check_enemies_defeated()) {
            return;
        }
        battleStatus->flags1 &= ~BS_FLAGS1_80000;
        battleStatus->flags2 &= ~BS_FLAGS2_10;

        if (battleStatus->unk_94 < 0) {
            battleStatus->unk_94 = 0;
            btl_set_state(BATTLE_STATE_END_TURN);
        } else {
            btl_set_state(BATTLE_STATE_9);
        }
    }
}

void btl_state_draw_end_partner_turn(void) {
}

void btl_state_update_next_enemy(void) {
    BattleStatus* battleStatus = &gBattleStatus;
    Actor* player = gBattleStatus.playerActor;
    Actor* partner = gBattleStatus.partnerActor;
    Actor* enemy;
    s32 skipEnemy;
    s32 i;

    switch (gBattleSubState) {
        case BTL_SUBSTATE_NEXT_ENEMY_INIT:
        case BTL_SUBSTATE_NEXT_ENEMY_UNK_1:
            i = battleStatus->nextEnemyIndex;
            if (i >= battleStatus->numEnemyActors) {
                // all enemies have been exhausted
                battleStatus->nextEnemyIndex = 0;
                btl_set_state(BATTLE_STATE_END_TURN);
                return;
            }

            // find the next eligible enemy
            while (TRUE) {
                if (battleStatus->enemyIDs[i] >= 0) {
                    u16 enemyID = battleStatus->enemyIDs[i];

                    enemy = battleStatus->enemyActors[enemyID & 0xFF];
                    if (enemy != NULL) {
                        if (!(enemy->flags & (ACTOR_FLAG_NO_ATTACK | ACTOR_FLAG_TARGET_ONLY))) {
                            break;
                        }
                    }
                }
                i++;
                if (i >= battleStatus->numEnemyActors) {
                    i = 0;
                }
                if (i == 0) {
                    battleStatus->nextEnemyIndex = 0;
                    btl_set_state(BATTLE_STATE_END_TURN);
                    return;
                }
            }

            battleStatus->activeEnemyActorID = battleStatus->enemyIDs[i++];
            battleStatus->currentTurnEnemy = enemy;
            battleStatus->nextEnemyIndex = i;

            skipEnemy = FALSE;
            
            if (enemy->debuff == STATUS_SLEEP) {
                skipEnemy = TRUE;
            }
            if (enemy->debuff == STATUS_FEAR) {
                skipEnemy = TRUE;
            }
            if (enemy->debuff == STATUS_DIZZY) {
                skipEnemy = TRUE;
            }
            if (enemy->debuff == STATUS_PARALYZE) {
                skipEnemy = TRUE;
            }
            if (enemy->debuff == STATUS_FROZEN) {
                skipEnemy = TRUE;
            }
            if (enemy->debuff == STATUS_STOP) {
                skipEnemy = TRUE;
            }
            if (enemy->stoneStatus == STATUS_STONE) {
                skipEnemy = TRUE;
            }
            if (enemy->flags & ACTOR_FLAG_10000) {
                skipEnemy = TRUE;
            }

            if (skipEnemy) {
                // reset state to fetch next enemy
                gBattleSubState = BTL_SUBSTATE_NEXT_ENEMY_INIT;
                return;
            }

            battleStatus->unk_8C = 0;
            gBattleStatus.flags1 &= ~BS_FLAGS1_2;
            gBattleStatus.flags1 &= ~BS_FLAGS1_ENEMY_FLED;
            gBattleStatus.flags1 &= ~BS_FLAGS1_AUTO_SUCCEED_ACTION;
            gBattleStatus.flags1 &= ~BS_FLAGS1_80000;

            player->flags &= ~ACTOR_FLAG_8000000;
            player->flags |= ACTOR_FLAG_4000000;

            if (partner != NULL) {
                partner->flags &= ~ACTOR_FLAG_8000000;
                partner->flags |= ACTOR_FLAG_4000000;
            }

            gBattleStatus.flags2 &= ~BS_FLAGS2_2;
            gBattleStatus.flags2 &= ~BS_FLAGS2_4;
            gBattleStatus.flags2 |= BS_FLAGS2_10000;

            D_8029F244 = enemy->unk_134;
            if (enemy->handlePhaseSource != NULL) {
                Evt* onTurnChanceScript;

                battleStatus->battlePhase = PHASE_ENEMY_BEGIN;
                onTurnChanceScript = start_script(enemy->handlePhaseSource, EVT_PRIORITY_A, 0);
                enemy->handlePhaseScript = onTurnChanceScript;
                enemy->handleBatttlePhaseScriptID = onTurnChanceScript->id;
                onTurnChanceScript->owner1.actorID = battleStatus->activeEnemyActorID;
            }
            gBattleSubState = BTL_SUBSTATE_NEXT_ENEMY_DONE;
            break;
        case BTL_SUBSTATE_NEXT_ENEMY_DONE:
            if (battleStatus->unk_8C == 0) {
                enemy = get_actor(battleStatus->activeEnemyActorID);

                if (enemy == NULL || enemy->unk_134 != D_8029F244) {
                    btl_set_state(BATTLE_STATE_NEXT_ENEMY);
                } else {
                    if (enemy->handlePhaseSource == NULL || !does_script_exist(enemy->handleBatttlePhaseScriptID)) {
                        if (battleStatus->unk_94 < 0) {
                            battleStatus->unk_94 = 0;
                            btl_set_state(BATTLE_STATE_END_TURN);
                        } else {
                            btl_set_state(BATTLE_STATE_ENEMY_MOVE);
                        }
                    }
                }
            }
            break;
    }
}

void btl_state_draw_next_enemy(void) {
}

void btl_state_update_enemy_move(void) {
    BattleStatus* battleStatus = &gBattleStatus;
    Actor* player = gBattleStatus.playerActor;
    Actor* partner = gBattleStatus.partnerActor;
    Actor* enemy;
    s32 i;

    Evt* script;
    s32 messageIndex;
    s32 waitingForEnemyScript;

    switch (gBattleSubState) {
        case BTL_SUBSTATE_ENEMY_MOVE_EXECUTE:
        case BTL_SUBSTATE_ENEMY_MOVE_UNK_1:
            gBattleStatus.flags1 &= ~BS_FLAGS1_2;
            gBattleStatus.flags1 &= ~BS_FLAGS1_200000;
            player->flags &= ~ACTOR_FLAG_8000000;
            if (partner != NULL) {
                partner->flags &= ~ACTOR_FLAG_8000000;
            }
            battleStatus->unk_8C = 0;
            battleStatus->lastAttackDamage = 0;
            battleStatus->actionSuccess = 0;
            battleStatus->unk_86 = 127;
            battleStatus->blockResult = 127;
            battleStatus->unk_19A = 0;
            reset_actor_turn_info();
            gBattleStatus.flags1 |= BS_FLAGS1_100;
            player->status = 0;
            if (partner != NULL) {
                partner->status = 0;
            }

            gBattleStatus.flags2 |= BS_FLAGS2_4000;
            for (i = 0; i < ARRAY_COUNT(battleStatus->enemyActors); i++) {
                enemy = battleStatus->enemyActors[i];
                if (enemy != NULL) {
                    enemy->flags &= ~ACTOR_FLAG_80000;
                }
            }

            for (i = 0; i < ARRAY_COUNT(battleStatus->enemyActors); i++) {
                enemy = battleStatus->enemyActors[i];
                if (enemy != NULL) {
                    if (!(enemy->flags & ACTOR_FLAG_NO_DMG_APPLY)) {
                        enemy->flags &= ~ACTOR_FLAG_8000000;
                    }
                }
            }

            enemy = battleStatus->currentTurnEnemy;
            if (!(enemy->flags & ACTOR_FLAG_NO_ATTACK)) {
                reset_all_actor_sounds(enemy);
                battleStatus->battlePhase = PHASE_EXECUTE_ACTION;
                script = start_script(enemy->takeTurnSource, EVT_PRIORITY_A, 0);
                enemy->takeTurnScript = script;
                enemy->takeTurnScriptID = script->id;
                script->owner1.actorID = battleStatus->activeEnemyActorID;
            }
            gBattleSubState = BTL_SUBSTATE_ENEMY_MOVE_AWAIT_SCRIPTS;
            break;
        case BTL_SUBSTATE_ENEMY_MOVE_AWAIT_SCRIPTS:
            if (player->takeTurnScript != NULL && does_script_exist(player->takeTurnScriptID)) {
                break;
            }
            player->takeTurnScript = NULL;

            if (player->handleEventScript != NULL && does_script_exist(player->handleEventScriptID)) {
                break;
            }
            player->handleEventScript = NULL;

            if (partner != NULL) {
                if (partner->handleEventScript != NULL && does_script_exist(partner->handleEventScriptID)) {
                    break;
                }
                partner->handleEventScript = NULL;
            }

            waitingForEnemyScript = FALSE;
            for (i = 0; i < ARRAY_COUNT(battleStatus->enemyActors); i++) {
                enemy = battleStatus->enemyActors[i];
                if (enemy != NULL && enemy->handleEventScript != NULL) {
                    if (does_script_exist(enemy->handleEventScriptID)) {
                        waitingForEnemyScript = TRUE;
                    } else {
                        enemy->handleEventScript = NULL;
                    }
                }
            }

            if (waitingForEnemyScript) {
                break;
            }
            
            if (btl_check_player_defeated()) {
                return;
            }

            for (i = 0; i < ARRAY_COUNT(battleStatus->enemyActors); i++) {
                enemy = battleStatus->enemyActors[i];
                if (enemy != NULL && enemy->takeTurnScript != NULL) {
                    if (does_script_exist(enemy->takeTurnScriptID)) {
                        waitingForEnemyScript = TRUE;
                    } else {
                        enemy->takeTurnScript = NULL;
                    }
                }
            }

            if (!waitingForEnemyScript || (gBattleStatus.flags1 & BS_FLAGS1_200000)) {
                gBattleStatus.flags1 &= ~BS_FLAGS1_100;
                gBattleStatus.flags2 &= ~BS_FLAGS2_4000;
                if (btl_check_enemies_defeated()) {
                    return;
                }

                if (battleStatus->unk_8C == 0) {
                    if (gGameStatusPtr->demoFlags & 1) {
                        btl_set_state(BATTLE_STATE_END_DEMO_BATTLE);
                    } else {
                        btl_update_ko_status();
                        if (player->status != 0) {
                            player->flags |= ACTOR_FLAG_8000000 | ACTOR_FLAG_4000000;
                            if (partner != NULL) {
                                partner->flags |= ACTOR_FLAG_8000000 | ACTOR_FLAG_4000000;
                            }
                            btl_cam_use_preset(BTL_CAM_PRESET_33);

                            switch (player->status) {
                                case STATUS_DIZZY:
                                    messageIndex = BTL_MSG_0A;
                                    break;
                                case STATUS_SLEEP:
                                    messageIndex = BTL_MSG_0B;
                                    break;
                                case STATUS_FROZEN:
                                    messageIndex = BTL_MSG_0C;
                                    break;
                                case STATUS_POISON:
                                    messageIndex = BTL_MSG_0D;
                                    break;
                                case STATUS_SHRINK:
                                    messageIndex = BTL_MSG_0E;
                                    break;
                                case STATUS_PARALYZE:
                                    messageIndex = BTL_MSG_0F;
                                    break;
                                default:
                                    messageIndex = 0;
                                    gBattleSubState = BTL_SUBSTATE_ENEMY_MOVE_CHECK_PARTNER;
                                    break;
                            }
                            btl_show_battle_message(messageIndex, 60);
                            player->status = 0;
                            gBattleSubState = BTL_SUBSTATE_ENEMY_MOVE_AWAIT_PLAYER_POPUP_DONE;
                            break;
                        } else {
                            gBattleSubState = BTL_SUBSTATE_ENEMY_MOVE_CHECK_PARTNER;
                            break;
                        }
                    }
                }
            }
            break;
        case BTL_SUBSTATE_ENEMY_MOVE_AWAIT_PLAYER_POPUP_DONE:
            if (!btl_is_popup_displayed()) {
                btl_cam_use_preset(BTL_CAM_PRESET_C);
                btl_cam_move(15);
                D_8029F248 = 10;
                gBattleSubState = BTL_SUBSTATE_ENEMY_MOVE_POST_PLAYER_POPUP_DELAY;
            }
            break;
        case BTL_SUBSTATE_ENEMY_MOVE_POST_PLAYER_POPUP_DELAY:
            if (D_8029F248 != 0) {
                D_8029F248--;
            } else {
                gBattleSubState = BTL_SUBSTATE_ENEMY_MOVE_CHECK_PARTNER;
                break;
            }
            break;
    }

    switch (gBattleSubState) {
        case BTL_SUBSTATE_ENEMY_MOVE_CHECK_PARTNER:
            if (partner != NULL) {
                if (partner->status == STATUS_DAZE) {
                    player->flags |= ACTOR_FLAG_8000000 | ACTOR_FLAG_4000000;
                    partner->flags |= ACTOR_FLAG_8000000 | ACTOR_FLAG_4000000;
                    btl_cam_use_preset(BTL_CAM_PRESET_54);
                    btl_show_battle_message(BTL_MSG_23, 60);
                    partner->status = 0;
                    gBattleSubState = BTL_SUBSTATE_ENEMY_MOVE_AWAIT_PARTNER_POPUP_DONE;
                } else {
                    gBattleSubState = BTL_SUBSTATE_ENEMY_MOVE_DONE;
                }
            } else {
                gBattleSubState = BTL_SUBSTATE_ENEMY_MOVE_DONE;
            }
            break;
        case BTL_SUBSTATE_ENEMY_MOVE_AWAIT_PARTNER_POPUP_DONE:
            if (!btl_is_popup_displayed()) {
                btl_cam_use_preset(BTL_CAM_PRESET_C);
                btl_cam_move(15);
                D_8029F248 = 10;
                gBattleSubState = BTL_SUBSTATE_ENEMY_MOVE_POST_PARTNER_POPUP_DELAY;
            }
            break;
        case BTL_SUBSTATE_ENEMY_MOVE_POST_PARTNER_POPUP_DELAY:
            if (D_8029F248 != 0) {
                D_8029F248--;
            } else {
                gBattleSubState = BTL_SUBSTATE_ENEMY_MOVE_DONE;
            }
            break;
    }

    if (gBattleSubState == BTL_SUBSTATE_ENEMY_MOVE_DONE) {
        btl_set_state(BATTLE_STATE_NEXT_ENEMY);
    }
}

void btl_state_draw_enemy_move(void) {
}

void btl_state_update_first_strike(void) {
    PlayerData* playerData = &gPlayerData;
    BattleStatus* battleStatus = &gBattleStatus;
    EncounterStatus* encounterStatus = &gCurrentEncounter;
    Actor* player = gBattleStatus.playerActor;
    Actor* partner = gBattleStatus.partnerActor;
    Evt* script;
    Actor* enemy;
    s32 enemyNotDone;
    s32 i;

    switch (gBattleSubState) {
        case BTL_SUBSTATE_FIRST_STRIKE_INIT:
            D_8029F254 = 0;
            btl_merlee_on_first_strike();
            if (playerData->playerFirstStrikes < 9999) {
                playerData->playerFirstStrikes++;
            }
            battleStatus->rushFlags = RUSH_FLAG_NONE;
            gBattleStatus.flags2 &= ~BS_FLAGS2_HAS_RUSH;

            if (!(gBattleStatus.flags2 & BS_FLAGS2_PEACH_BATTLE)) {
                if (playerData->curHP < 2 && is_ability_active(ABILITY_MEGA_RUSH)) {
                    gBattleStatus.flags2 |= BS_FLAGS2_HAS_RUSH;
                    battleStatus->rushFlags |= RUSH_FLAG_MEGA;
                }
                if (playerData->curHP < 6 && is_ability_active(ABILITY_POWER_RUSH) &&
                    !(battleStatus->rushFlags & RUSH_FLAG_MEGA))
                {
                    gBattleStatus.flags2 |= BS_FLAGS2_HAS_RUSH;
                    battleStatus->rushFlags |= RUSH_FLAG_POWER;
                }
            }

            // setup dummy 'menu selection' for player move
            switch (encounterStatus->hitType) {
                case ENCOUNTER_TRIGGER_JUMP:
                    battleStatus->moveCategory = BTL_MENU_TYPE_JUMP;
                    battleStatus->selectedMoveID = MOVE_UNUSED_JUMP4;
                    battleStatus->selectedItemID = encounterStatus->hitTier;
                    battleStatus->currentTargetListFlags = gMoveTable[MOVE_UNUSED_JUMP4].flags;
                    break;
                case ENCOUNTER_TRIGGER_HAMMER:
                    battleStatus->moveCategory = BTL_MENU_TYPE_SMASH;
                    battleStatus->selectedMoveID = MOVE_UNUSED_HAMMER4;
                    battleStatus->selectedItemID = encounterStatus->hitTier;
                    battleStatus->currentTargetListFlags = gMoveTable[MOVE_UNUSED_HAMMER4].flags;
                    break;
                case ENCOUNTER_TRIGGER_PARTNER:
                    btl_set_state(BATTLE_STATE_PARTNER_FIRST_STRIKE);
                    return;
            }
            // let the enemy know a first strike is coming
            enemy = get_actor(ACTOR_ENEMY0);
            if (enemy->handleEventSource != NULL) {
                enemy->lastEventType = EVENT_BEGIN_FIRST_STRIKE;
                script = start_script(enemy->handleEventSource, EVT_PRIORITY_A, EVT_FLAG_RUN_IMMEDIATELY);
                enemy->handleEventScript = script;
                enemy->handleEventScriptID = script->id;
                script->owner1.actorID = enemy->actorID;
            }
            gBattleSubState = BTL_SUBSTATE_FIRST_STRIKE_AWAIT_ENEMY_READY;
            break;
        case BTL_SUBSTATE_FIRST_STRIKE_AWAIT_ENEMY_READY:
            enemy = get_actor(ACTOR_ENEMY0);
            if (enemy->handleEventSource != NULL) {
                if (does_script_exist(enemy->handleEventScriptID)) {
                    break;
                } else {
                    enemy->handleEventScript = NULL;
                }
            }

            func_80263230(player, enemy);
            battleStatus->unk_8C = 0;
            battleStatus->lastAttackDamage = 0;
            battleStatus->unk_19A = 0;
            gBattleStatus.flags1 &= ~BS_FLAGS1_2;
            gBattleStatus.flags2 |= BS_FLAGS2_1000000;
            gBattleStatus.flags1 &= ~BS_FLAGS1_80000;
            increment_status_menu_disabled();
            btl_cam_use_preset(BTL_CAM_PRESET_10);
            btl_cam_target_actor(0);
            reset_actor_turn_info();
            // begin the partner turn script
            battleStatus->battlePhase = PHASE_FIRST_STRIKE;
            script = start_script(&PlayerScriptDispatcher, EVT_PRIORITY_A, 0);
            player->takeTurnScript = script;
            player->takeTurnScriptID = script->id;
            script->owner1.actorID = ACTOR_PLAYER;
            D_8029F248 = 3;
            gBattleSubState = BTL_SUBSTATE_FIRST_STRIKE_AWAIT_SCRIPTS;
            break;
        case BTL_SUBSTATE_FIRST_STRIKE_AWAIT_SCRIPTS:
            if (D_8029F248 != 0) {
                D_8029F248--;
            } else {
                D_8029F254 = 1;
            }

            // wait for player move script
            if (!(gBattleStatus.flags1 & BS_FLAGS1_200000)) {
                if (player->takeTurnScript != NULL && does_script_exist(player->takeTurnScriptID)) {
                    break;
                }
                player->takeTurnScript = NULL;
            }

            gBattleStatus.flags1 &= ~BS_FLAGS1_100;

            // wait for player handle event script
            if (player->handleEventScript != NULL && does_script_exist(player->handleEventScriptID)) {
                break;
            }
            player->handleEventScript = NULL;

            // wait for partner handle event script
            if (partner != NULL) {
                if (partner->handleEventScript != NULL && does_script_exist(partner->handleEventScriptID)) {
                    break;
                }
                partner->handleEventScript = NULL;
            }

            // wait for all enemy turn scripts
            enemyNotDone = FALSE;
            for (i = 0; i < ARRAY_COUNT(battleStatus->enemyActors); i++) {
                enemy = battleStatus->enemyActors[i];
                if (enemy != NULL && enemy->takeTurnScript != NULL) {
                    if (does_script_exist(enemy->takeTurnScriptID)) {
                        enemyNotDone = TRUE;
                    } else {
                        enemy->takeTurnScript = NULL;
                    }
                }
            }
            if (enemyNotDone) {
                break;
            }

            // wait for all enemy handle event scripts
            enemyNotDone = FALSE;
            for (i = 0; i < ARRAY_COUNT(battleStatus->enemyActors); i++) {
                enemy = battleStatus->enemyActors[i];
                if (enemy != NULL && enemy->handleEventScript != NULL) {
                    if (does_script_exist(enemy->handleEventScriptID)) {
                        enemyNotDone = TRUE;
                    } else {
                        enemy->handleEventScript = NULL;
                    }
                }
            }
            if (enemyNotDone) {
                break;
            }

            for (i = 0; i < ARRAY_COUNT(battleStatus->enemyActors); i++) {
                enemy = battleStatus->enemyActors[i];
                if (enemy != NULL) {
                    enemy->flags &= ~ACTOR_FLAG_80000;
                }
            }

            if (battleStatus->unk_8C == 0) {
                decrement_status_menu_disabled();
                if (!(gGameStatusPtr->demoFlags & 1)) {
                    Actor* target;

                    if (btl_check_player_defeated() || btl_check_enemies_defeated()) {
                        return;
                    }

                    target = get_actor(player->targetActorID);
                    if (target != NULL) {
                        if (target->handleEventSource != NULL) {
                            target->lastEventType = EVENT_END_FIRST_STRIKE;
                            script = start_script(target->handleEventSource, EVT_PRIORITY_A, EVT_FLAG_RUN_IMMEDIATELY);
                            target->handleEventScript = script;
                            target->handleEventScriptID = script->id;
                            script->owner1.actorID = target->actorID;
                        }
                    }
                    gBattleSubState = BTL_SUBSTATE_FIRST_STRIKE_AWAIT_ENEMY_DONE;
                } else {
                    btl_set_state(BATTLE_STATE_END_DEMO_BATTLE);
                }
            }
            break;
        case BTL_SUBSTATE_FIRST_STRIKE_AWAIT_ENEMY_DONE:
            enemyNotDone = FALSE;
            for (i = 0; i < ARRAY_COUNT(battleStatus->enemyActors); i++) {
                enemy = battleStatus->enemyActors[i];
                if (enemy != NULL && enemy->handleEventScript != NULL) {
                    if (does_script_exist(enemy->handleEventScriptID)) {
                        enemyNotDone = TRUE;
                    } else {
                        enemy->handleEventScript = NULL;
                    }
                }
            }
            if (enemyNotDone) {
                break;
            }
            if (player->takeTurnScript == NULL || !does_script_exist(player->takeTurnScriptID)) {
                player->takeTurnScript = NULL;
                btl_set_state(BATTLE_STATE_BEGIN_TURN);
            }
            break;
    }
}

void btl_state_draw_first_stike(void) {
    if (D_802809F6 == -1 && D_8029F254 != 0) {
        if (D_80280A30 == 0) {
            set_screen_overlay_params_front(255, -1.0f);
        } else {
            if (!(gGameStatusPtr->demoFlags & 1)) {
                D_80280A30 -= 20;
            } else {
                D_80280A30 -= 50;
            }

            if (D_80280A30 < 0) {
                D_80280A30 = 0;
            }
            set_screen_overlay_params_front(0, D_80280A30);
        }
    }
}

void btl_state_update_partner_striking_first(void) {
    PlayerData* playerData = &gPlayerData;
    BattleStatus* battleStatus = &gBattleStatus;
    Actor* player = battleStatus->playerActor;
    Actor* partner = battleStatus->partnerActor;
    Actor* actor;
    s32 enemyNotDone;
    SelectableTarget* target;
    Evt* script;
    s32 level;
    s32 i;

    switch (gBattleSubState) {
        case BTL_SUBSTATE_PARTNER_FIRST_STRIKE_INIT:
            D_8029F254 = 0;
            // setup dummy 'menu selection' for partner move
            level = partner->actorBlueprint->level;
            switch (playerData->currentPartner) {
                case PARTNER_KOOPER:
                    battleStatus->moveCategory = BTL_MENU_TYPE_5;
                    battleStatus->selectedItemID = ITEM_NONE;
                    battleStatus->selectedMoveID = level + MOVE_SHELL_TOSS1;
                    battleStatus->currentTargetListFlags = gMoveTable[battleStatus->selectedMoveID].flags;
                    break;
                case PARTNER_BOMBETTE:
                    battleStatus->moveCategory = BTL_MENU_TYPE_5;
                    battleStatus->selectedItemID = ITEM_NONE;
                    battleStatus->selectedMoveID = level + MOVE_BODY_SLAM1;
                    battleStatus->currentTargetListFlags = gMoveTable[battleStatus->selectedMoveID].flags;
                    break;
            }
            // let the enemy know a first strike is coming
            actor = get_actor(ACTOR_ENEMY0);
            if (actor->handleEventSource != NULL) {
                actor->lastEventType = EVENT_BEGIN_FIRST_STRIKE;
                script = start_script(actor->handleEventSource, EVT_PRIORITY_A, EVT_FLAG_RUN_IMMEDIATELY);
                actor->handleEventScript = script;
                actor->handleEventScriptID = script->id;
                script->owner1.actorID = actor->actorID;
            }
            gBattleSubState = BTL_SUBSTATE_PARTNER_FIRST_STRIKE_AWAIT_ENEMY_READY;
            break;
        case BTL_SUBSTATE_PARTNER_FIRST_STRIKE_AWAIT_ENEMY_READY:
            player_create_target_list(partner);
            target = &partner->targetData[partner->targetIndexList[0]];
            partner->targetActorID = target->actorID;
            partner->targetPartIndex = target->partID;
            battleStatus->unk_8C = 0;
            battleStatus->lastAttackDamage = 0;
            battleStatus->unk_19A = 0;
            gBattleStatus.flags1 &= ~BS_FLAGS1_2;
            gBattleStatus.flags2 |= BS_FLAGS2_1000000;
            gBattleStatus.flags1 |= BS_FLAGS1_80000;
            increment_status_menu_disabled();
            btl_cam_use_preset(BTL_CAM_PRESET_10);
            btl_cam_target_actor(ACTOR_PARTNER);
            reset_actor_turn_info();
            // begin the partner turn script
            battleStatus->battlePhase = PHASE_FIRST_STRIKE;
            script = start_script(partner->takeTurnSource, EVT_PRIORITY_A, 0);
            partner->takeTurnScript = script;
            partner->takeTurnScriptID = script->id;
            script->owner1.actorID = ACTOR_PARTNER;
            D_8029F248 = 3;
            gBattleSubState = BTL_SUBSTATE_PARTNER_FIRST_STRIKE_AWAIT_SCRIPTS;
            break;
        case BTL_SUBSTATE_PARTNER_FIRST_STRIKE_AWAIT_SCRIPTS:
            if (D_8029F248 != 0) {
                D_8029F248--;
            } else {
                D_8029F254 = 1;
            }
            // wait for partner move script
            if (partner->takeTurnScript != NULL && does_script_exist(partner->takeTurnScriptID)) {
                break;
            }
            partner->takeTurnScript = NULL;
            // wait for partner handle event script
            if (partner->handleEventScript != NULL && does_script_exist(partner->handleEventScriptID)) {
                break;
            }
            partner->handleEventScript = NULL;
            // wait for player handle event script
            if (player->handleEventScript != NULL && does_script_exist(player->handleEventScriptID)) {
                break;
            }
            player->handleEventScript = NULL;

            // wait for all enemy turn scripts
            enemyNotDone = FALSE;
            for (i = 0; i < ARRAY_COUNT(battleStatus->enemyActors); i++) {
                actor = battleStatus->enemyActors[i];
                if (actor != NULL && actor->takeTurnScript != NULL) {
                    if (does_script_exist(actor->takeTurnScriptID)) {
                        enemyNotDone = TRUE;
                    } else {
                        actor->takeTurnScript = NULL;
                    }
                }
            }
            if (enemyNotDone) {
                break;
            }

            // wait for all enemy handle event scripts
            enemyNotDone = FALSE;
            for (i = 0; i < ARRAY_COUNT(battleStatus->enemyActors); i++) {
                actor = battleStatus->enemyActors[i];
                if (actor != NULL && actor->handleEventScript != NULL) {
                    if (does_script_exist(actor->handleEventScriptID)) {
                        enemyNotDone = TRUE;
                    } else {
                        actor->handleEventScript = NULL;
                    }
                }
            }
            if (enemyNotDone) {
                break;
            }

            for (i = 0; i < ARRAY_COUNT(battleStatus->enemyActors); i++) {
                actor = battleStatus->enemyActors[i];
                if (actor != NULL) {
                    actor->flags &= ~ACTOR_FLAG_80000;
                }
            }

            if (battleStatus->unk_8C == 0) {
                decrement_status_menu_disabled();
                if (btl_check_player_defeated() || btl_check_enemies_defeated()) {
                    return;
                }

                actor = get_actor(partner->targetActorID);
                if (actor != NULL) {
                    if (actor->handleEventSource != NULL) {
                        actor->lastEventType = EVENT_END_FIRST_STRIKE;
                        script = start_script(actor->handleEventSource, EVT_PRIORITY_A, EVT_FLAG_RUN_IMMEDIATELY);
                        actor->handleEventScript = script;
                        actor->handleEventScriptID = script->id;
                        script->owner1.actorID = actor->actorID;
                    }
                }
                gBattleSubState = BTL_SUBSTATE_PARTNER_FIRST_STRIKE_AWAIT_ENEMY_DONE;
            }
            break;
        case BTL_SUBSTATE_PARTNER_FIRST_STRIKE_AWAIT_ENEMY_DONE:
            enemyNotDone = FALSE;
            for (i = 0; i < ARRAY_COUNT(battleStatus->enemyActors); i++) {
                actor = battleStatus->enemyActors[i];
                if (actor != NULL && actor->handleEventScript != NULL) {
                    if (does_script_exist(actor->handleEventScriptID)) {
                        enemyNotDone = TRUE;
                    } else {
                        actor->handleEventScript = NULL;
                    }
                }
            }
            if (!enemyNotDone) {
                btl_set_state(BATTLE_STATE_BEGIN_TURN);
            }
            break;
    }
}

void btl_state_draw_partner_striking_first(void) {
    if (D_8029F254 != 0) {
        if (D_80280A30 == 0) {
            set_screen_overlay_params_front(255, -1.0f);
        } else {
            D_80280A30 -= 20;
            if (D_80280A30 < 0) {
                D_80280A30 = 0;
            }

            set_screen_overlay_params_front(0, D_80280A30);
        }
    }
}

void btl_state_update_enemy_striking_first(void) {
    PlayerData* playerData = &gPlayerData;
    BattleStatus* battleStatus = &gBattleStatus;
    Actor* player = battleStatus->playerActor;
    Actor* partner = battleStatus->partnerActor;
    Evt* script;
    Actor* actor;
    u16* enemyIDs;
    s16 activeEnemyActorID;
    s32 nextEnemyIdx;
    s32 count;
    s32 flags;
    s32 cond;
    s32 i;
    s32 j;

    switch (gBattleSubState) {
        case BTL_SUBSTATE_ENEMY_FIRST_STRIKE_INIT:
            battleStatus->unk_8C = 0;
            battleStatus->lastAttackDamage = 0;
            battleStatus->unk_19A = 0;
            playerData->enemyFirstStrikes++;
            battleStatus->flags1 &= ~BS_FLAGS1_2;
            D_8029F254 = 0;
            player->flags &= ~ACTOR_FLAG_8000000;
            if (partner != NULL) {
                partner->flags &= ~ACTOR_FLAG_8000000;
            }
            battleStatus->flags2 |= BS_FLAGS2_1000000;
            battleStatus->flags2 |= BS_FLAGS2_4000;
            count = 0;

            for (i = 0; i < ARRAY_COUNT(battleStatus->enemyActors); i++) {
                actor = battleStatus->enemyActors[i];
                if (actor != NULL) {
                    battleStatus->enemyIDs[count] = i | ACTOR_ENEMY0;
                    count++;
                }
            }

            battleStatus->numEnemyActors = count;

            enemyIDs = battleStatus->enemyIDs;
            for (i = 0; i < count - 1; i++) {
                for (j = i + 1; j < count; j++) {
                    s32 iVal = enemyIDs[i];
                    s32 jVal = enemyIDs[j];

                    if (battleStatus->enemyActors[iVal & 0xFF]->turnPriority <
                        battleStatus->enemyActors[jVal & 0xFF]->turnPriority)
                    {
                        enemyIDs[i] = jVal;
                        enemyIDs[j] = iVal;
                    }
                }
            }

            battleStatus->nextEnemyIndex = 0;
            nextEnemyIdx = 0;
            flags = ACTOR_FLAG_NO_ATTACK | ACTOR_FLAG_TARGET_ONLY;

            while (TRUE) {
                actor = battleStatus->enemyActors[battleStatus->enemyIDs[nextEnemyIdx] & 0xFF];
                if (actor == NULL || (actor->flags & flags)) {
                    nextEnemyIdx++;
                    if (nextEnemyIdx >= battleStatus->numEnemyActors) {
                        nextEnemyIdx = 0;
                    }
                } else {
                    break;
                }
            }

            activeEnemyActorID = battleStatus->enemyIDs[nextEnemyIdx];
            nextEnemyIdx++;
            battleStatus->currentTurnEnemy = actor;
            battleStatus->activeEnemyActorID = activeEnemyActorID;
            if (nextEnemyIdx >= battleStatus->numEnemyActors) {
                nextEnemyIdx = 0;
            }
            battleStatus->nextEnemyIndex = nextEnemyIdx;
            btl_cam_target_actor(battleStatus->activeEnemyActorID);
            actor = battleStatus->currentTurnEnemy;
            reset_actor_turn_info();
            battleStatus->battlePhase = PHASE_FIRST_STRIKE;
            script = start_script(actor->takeTurnSource, EVT_PRIORITY_A, 0);
            actor->takeTurnScript = script;
            D_8029F248 = 3;
            actor->takeTurnScriptID = script->id;
            gBattleSubState = BTL_SUBSTATE_ENEMY_FIRST_STRIKE_AWAIT_SCRIPTS;
            script->owner1.actorID = battleStatus->activeEnemyActorID;
            break;
        case BTL_SUBSTATE_ENEMY_FIRST_STRIKE_AWAIT_SCRIPTS:
            if (D_8029F248 != 0) {
                D_8029F248--;
            } else {
                D_8029F254 = 1;
            }

            actor = battleStatus->currentTurnEnemy;
            if (actor->takeTurnScript == NULL || !does_script_exist(actor->takeTurnScriptID)) {
                actor->takeTurnScript = NULL;

                if (player->handleEventScript == NULL || !does_script_exist(player->handleEventScriptID)) {
                    player->handleEventScript = NULL;

                    if (partner != NULL) {
                        if (partner->handleEventScript == NULL || !does_script_exist(partner->handleEventScriptID)) {
                            partner->handleEventScript = NULL;
                        } else {
                            return;
                        }
                    }

                    cond = FALSE;

                    for (i = 0; i < ARRAY_COUNT(battleStatus->enemyActors); i++) {
                        actor = battleStatus->enemyActors[i];
                        if (actor != NULL && actor->takeTurnScript != NULL) {
                            if (does_script_exist(actor->takeTurnScriptID)) {
                                cond = TRUE;
                            } else {
                                actor->takeTurnScript = NULL;
                            }
                        }
                    }

                    if (!cond) {
                        for (i = 0; i < ARRAY_COUNT(battleStatus->enemyActors); i++) {
                            actor = battleStatus->enemyActors[i];
                            if (actor != NULL && actor->handleEventScript != NULL) {
                                if (does_script_exist(actor->handleEventScriptID)) {
                                    cond = TRUE;
                                } else {
                                    actor->handleEventScript = NULL;
                                }
                            }
                        }

                        if (!cond) {
                            gBattleStatus.flags2 &= ~BS_FLAGS2_4000;
                            for (i = 0; i < ARRAY_COUNT(battleStatus->enemyActors); i++) {
                                actor = battleStatus->enemyActors[i];
                                if (actor != NULL) {
                                    actor->flags &= ~ACTOR_FLAG_80000;
                                }
                            }

                            if (battleStatus->unk_8C == 0) {
                                if (btl_check_player_defeated() || btl_check_enemies_defeated()) {
                                    return;
                                }
                                btl_set_state(BATTLE_STATE_BEGIN_TURN);
                            }
                        }
                    }
                }
            }
            break;
    }
}

void btl_state_draw_enemy_striking_first(void) {
    if (D_8029F254 != 0) {
        if (D_80280A30 == 0) {
            set_screen_overlay_params_front(255, -1.0f);
        } else {
            D_80280A30 -= 20;
            if (D_80280A30 < 0) {
                D_80280A30 = 0;
            }

            set_screen_overlay_params_front(0, D_80280A30);
        }
    }
}

void btl_state_update_end_demo_battle(void) {
    BattleStatus* battleStatus = &gBattleStatus;
    Battle* blah = (*D_800DC4FC);
    Stage* stage;
    s32 i;

    switch (gBattleSubState) {
        case BTL_SUBSTATE_END_DEMO_BATTLE_UNK_0:
            D_80280A30 = 0;
            if (D_802809F6 == -1) {
                if (D_802809F8 != 0) {
                    D_802809F8--;
                    break;
                }
            }
            gBattleSubState = BTL_SUBSTATE_END_DEMO_BATTLE_UNK_1;
            break;
        case BTL_SUBSTATE_END_DEMO_BATTLE_UNK_1:
            switch (D_802809F6) {
                case 255:
                    gBattleSubState = BTL_SUBSTATE_END_DEMO_BATTLE_UNK_2;
                    return;
                case -1:
                    if (D_80280A30 == 255) {
                        gBattleSubState = BTL_SUBSTATE_END_DEMO_BATTLE_UNK_2;
                        return;
                    }
                    D_80280A30 += 50;
                    if (D_80280A30 > 255) {
                        D_80280A30 = 255;
                    }
                    return;
            }
            break;
        case BTL_SUBSTATE_END_DEMO_BATTLE_UNK_2:
            D_80280A30 = 255;
            gBattleStatus.flags1 &= ~BS_FLAGS1_ACTORS_VISIBLE;
            if (D_800DC064 == NULL) {
                stage = blah->stage;
            } else {
                stage = D_800DC064->stage;
            }

            if (stage->postBattle == NULL) {
                gBattleSubState = BTL_SUBSTATE_END_DEMO_BATTLE_UNK_4;
            } else {
                battleStatus->controlScript = start_script(stage->postBattle, EVT_PRIORITY_A, 0);
                battleStatus->controlScriptID = battleStatus->controlScript->id;
                gBattleSubState = BTL_SUBSTATE_END_DEMO_BATTLE_UNK_3;
            }
            break;
        case BTL_SUBSTATE_END_DEMO_BATTLE_UNK_3:
            if (does_script_exist(battleStatus->controlScriptID)) {
                break;
            }
            gBattleSubState = BTL_SUBSTATE_END_DEMO_BATTLE_UNK_4;
            //fallthrough
        case BTL_SUBSTATE_END_DEMO_BATTLE_UNK_4:
            kill_all_scripts();

            for (i = 0; i < ARRAY_COUNT(battleStatus->enemyActors); i++) {
                Actor* enemy = battleStatus->enemyActors[i];

                if (enemy != NULL) {
                    btl_delete_actor(enemy);
                }
            }

            if (battleStatus->partnerActor != NULL) {
                btl_delete_actor(battleStatus->partnerActor);
            }

            btl_delete_player_actor(battleStatus->playerActor);
            remove_all_effects();
            set_windows_visible(WINDOW_GROUP_ALL);

            if (gBattleStatus.flags2 & BS_FLAGS2_PEACH_BATTLE) {
                decrement_status_menu_disabled();
            }

            if (D_802809F6 != -1) {
                gGameStatusPtr->nextDemoScene = 0x12;
            }

            btl_set_state(BATTLE_STATE_0);
            D_800DC4D0 = gBattleState;
            set_game_mode(GAME_MODE_END_BATTLE);
            break;
    }
}

const static f32 padding[] = { 0.0f, 0.0f, 0.0f };

void btl_state_draw_end_demo_battle(void) {
    if (D_802809F6 == -1) {
        set_screen_overlay_color(0, 0, 0, 0);
        set_screen_overlay_params_front(0, D_80280A30);
    }
}
