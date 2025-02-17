#include "mac_00.h"

#define NAME_SUFFIX _Shared
#include "world/common/npc/Toad_Wander.inc.c"
#include "world/common/npc/Toad_Patrol.inc.c"
#include "world/common/npc/Toad_Stationary.inc.c"
#include "world/common/complete/LetterDelivery.inc.c"
#define NAME_SUFFIX

s32 N(LetterList_MissT)[] = {
    ITEM_LETTER18,
    ITEM_NONE
};

EvtScript N(EVS_LetterPrompt_MissT) = {
    EVT_CALL(N(LetterDelivery_Init_Shared),
        NPC_MissT, ANIM_Toadette_Orange_Talk, ANIM_Toadette_Orange_Idle,
        ITEM_LETTER18, ITEM_LETTER19,
        MSG_MAC_Gate_00FF, MSG_MAC_Gate_0100, MSG_MAC_Gate_0101, MSG_MAC_Gate_0102,
        EVT_PTR(N(LetterList_MissT)))
    EVT_EXEC_WAIT(N(EVS_DoLetterDelivery_Shared))
    EVT_RETURN
    EVT_END
};

EvtScript N(EVS_Scene_ToadTownGreeting) = {
    EVT_CALL(DisablePlayerInput, TRUE)
    EVT_CALL(UseSettingsFrom, CAM_DEFAULT, -225, 0, -300)
    EVT_CALL(SetPanTarget, CAM_DEFAULT, -225, 0, -300)
    EVT_CALL(SetCamDistance, CAM_DEFAULT, EVT_FLOAT(800.0))
    EVT_CALL(SetCamSpeed, CAM_DEFAULT, EVT_FLOAT(90.0))
    EVT_CALL(PanToTarget, CAM_DEFAULT, 0, 1)
    EVT_THREAD
        EVT_WAIT(35)
        EVT_CALL(SetCamSpeed, CAM_DEFAULT, EVT_FLOAT(2.1))
        EVT_CALL(UseSettingsFrom, CAM_DEFAULT, -225, 0, -300)
        EVT_CALL(SetCamDistance, CAM_DEFAULT, EVT_FLOAT(300.0))
        EVT_CALL(PanToTarget, CAM_DEFAULT, 0, 1)
        EVT_CALL(WaitForCam, CAM_DEFAULT, EVT_FLOAT(1.0))
        EVT_WAIT(10)
        EVT_CALL(InterpNpcYaw, NPC_Toad_04, 230, 0)
        EVT_CALL(SetNpcJumpscale, NPC_Toad_04, EVT_FLOAT(1.5))
        EVT_CALL(GetNpcPos, NPC_Toad_04, LVar0, LVar1, LVar2)
        EVT_CALL(NpcJump0, NPC_Toad_04, LVar0, LVar1, LVar2, 5)
        EVT_WAIT(10)
        EVT_CALL(SetNpcAnimation, NPC_Toad_04, ANIM_Toad_Red_Run)
        EVT_CALL(NpcMoveTo, NPC_Toad_04, -185, -295, 15)
        EVT_CALL(SetNpcAnimation, NPC_Toad_04, ANIM_Toad_Red_Idle)
    EVT_END_THREAD
    EVT_WAIT(2)
    EVT_CALL(PlayerMoveTo, -225, -300, 80)
    EVT_CALL(SetPlayerPos, -225, 0, -300)
    EVT_WAIT(50)
    EVT_THREAD
        EVT_WAIT(20)
        EVT_CALL(SetPlayerAnimation, ANIM_Mario_80007)
    EVT_END_THREAD
    EVT_CALL(SpeakToPlayer, NPC_Toad_04, ANIM_Toad_Red_Talk, ANIM_Toad_Red_Idle, 0, MSG_MAC_Gate_007E)
    EVT_CALL(DisablePlayerInput, FALSE)
    EVT_CALL(SetCamDistance, CAM_DEFAULT, EVT_FLOAT(400.0))
    EVT_CALL(SetCamSpeed, CAM_DEFAULT, EVT_FLOAT(4.0))
    EVT_CALL(PanToTarget, CAM_DEFAULT, 0, 1)
    EVT_CALL(WaitForCam, CAM_DEFAULT, EVT_FLOAT(1.0))
    EVT_CALL(PanToTarget, CAM_DEFAULT, 0, 0)
    EVT_RETURN
    EVT_END
};

EvtScript N(EVS_NpcInteract_Toad_04) = {
    EVT_SWITCH(GB_StoryProgress)
        EVT_CASE_LT(STORY_CH0_MET_STAR_SPIRITS)
            EVT_SET(LVar0, MSG_MAC_Gate_007F)
        EVT_CASE_LT(STORY_CH1_MERLIN_REVEALED_KOOPA_BROS)
            EVT_SET(LVar0, MSG_MAC_Gate_0080)
        EVT_CASE_LT(STORY_CH1_STAR_SPRIT_DEPARTED)
            EVT_SET(LVar0, MSG_MAC_Gate_0081)
        EVT_CASE_LT(STORY_CH2_STAR_SPRIT_DEPARTED)
            EVT_IF_EQ(GF_MAC03_BombedRock, FALSE)
                EVT_SET(LVar0, MSG_MAC_Gate_0082)
            EVT_ELSE
                EVT_SET(LVar0, MSG_MAC_Gate_0083)
            EVT_END_IF
        EVT_CASE_LT(STORY_CH3_STAR_SPIRIT_RESCUED)
            EVT_SET(LVar0, MSG_MAC_Gate_0084)
        EVT_CASE_LT(STORY_CH4_STAR_SPRIT_DEPARTED)
            EVT_IF_EQ(GF_MAC00_DictionaryStolen, FALSE)
                EVT_SET(LVar0, MSG_MAC_Gate_0085)
            EVT_ELSE
                EVT_IF_EQ(GF_MAC00_DictionaryReturned, FALSE)
                    EVT_SET(LVar0, MSG_MAC_Gate_0086)
                EVT_ELSE
                    EVT_SET(LVar0, MSG_MAC_Gate_0087)
                EVT_END_IF
            EVT_END_IF
        EVT_CASE_LT(STORY_CH5_DEFEATED_FUZZIPEDE)
            EVT_SET(LVar0, MSG_MAC_Gate_0088)
        EVT_CASE_LT(STORY_CH5_STAR_SPRIT_DEPARTED)
            EVT_SET(LVar0, MSG_MAC_Gate_0089)
        EVT_CASE_LT(STORY_CH6_ARRIVED_AT_FLOWER_FIELDS)
            EVT_SET(LVar0, MSG_MAC_Gate_008A)
        EVT_CASE_LT(STORY_CH6_STAR_SPIRIT_RESCUED)
            EVT_SET(LVar0, MSG_MAC_Gate_008B)
        EVT_CASE_LT(STORY_CH7_INVITED_TO_STARBORN_VALLEY)
            EVT_SET(LVar0, MSG_MAC_Gate_008C)
        EVT_CASE_LT(STORY_CH7_STAR_SPRIT_DEPARTED)
            EVT_SET(LVar0, MSG_MAC_Gate_008D)
        EVT_CASE_LT(STORY_EPILOGUE)
            EVT_SET(LVar0, MSG_MAC_Gate_008E)
        EVT_CASE_GE(STORY_EPILOGUE)
            EVT_SET(LVar0, MSG_Outro_002C)
    EVT_END_SWITCH
    EVT_CALL(SpeakToPlayer, NPC_SELF, ANIM_Toad_Red_Talk, ANIM_Toad_Red_Idle, 0, LVar0)
    EVT_RETURN
    EVT_END
};

EvtScript N(EVS_Scene_CantLeaveTown) = {
    EVT_CALL(DisablePlayerInput, TRUE)
    EVT_CALL(NpcFacePlayer, NPC_Toad_04, 0)
    EVT_WAIT(5)
    EVT_CALL(SpeakToPlayer, NPC_Toad_04, ANIM_Toad_Red_Talk, ANIM_Toad_Red_Idle, 0, MSG_Outro_002D)
    EVT_WAIT(10)
    EVT_CALL(SetPlayerSpeed, EVT_FLOAT(4.0))
    EVT_CALL(PlayerMoveTo, -220, -250, 0)
    EVT_CALL(DisablePlayerInput, FALSE)
    EVT_RETURN
    EVT_END
};

EvtScript N(EVS_BlockExitToGoomaRoad) = {
    EVT_BIND_TRIGGER(EVT_PTR(N(EVS_Scene_CantLeaveTown)), TRIGGER_FLOOR_TOUCH, COLLIDER_o484, 1, 0)
    EVT_RETURN
    EVT_END
};

EvtScript N(EVS_NpcInteract_Toad_05) = {
    EVT_SWITCH(GB_StoryProgress)
        EVT_CASE_LT(STORY_CH0_MET_STAR_SPIRITS)
            EVT_SET(LVar0, MSG_MAC_Gate_008F)
        EVT_CASE_LT(STORY_CH1_MERLIN_REVEALED_KOOPA_BROS)
            EVT_SET(LVar0, MSG_MAC_Gate_0090)
        EVT_CASE_LT(STORY_CH1_STAR_SPRIT_DEPARTED)
            EVT_SET(LVar0, MSG_MAC_Gate_0091)
        EVT_CASE_LT(STORY_CH2_STAR_SPRIT_DEPARTED)
            EVT_IF_EQ(GF_MAC03_BombedRock, FALSE)
                EVT_SET(LVar0, MSG_MAC_Gate_0092)
            EVT_ELSE
                EVT_SET(LVar0, MSG_MAC_Gate_0093)
            EVT_END_IF
        EVT_CASE_LT(STORY_CH3_STAR_SPIRIT_RESCUED)
            EVT_SET(LVar0, MSG_MAC_Gate_0094)
        EVT_CASE_LT(STORY_CH4_STAR_SPRIT_DEPARTED)
            EVT_IF_EQ(GF_MAC00_DictionaryStolen, FALSE)
                EVT_SET(LVar0, MSG_MAC_Gate_0095)
            EVT_ELSE
                EVT_IF_EQ(GF_MAC00_DictionaryReturned, FALSE)
                    EVT_SET(LVar0, MSG_MAC_Gate_0096)
                EVT_ELSE
                    EVT_SET(LVar0, MSG_MAC_Gate_0097)
                EVT_END_IF
            EVT_END_IF
        EVT_CASE_LT(STORY_CH5_DEFEATED_FUZZIPEDE)
            EVT_SET(LVar0, MSG_MAC_Gate_0098)
        EVT_CASE_LT(STORY_CH5_STAR_SPRIT_DEPARTED)
            EVT_SET(LVar0, MSG_MAC_Gate_0099)
        EVT_CASE_LT(STORY_CH6_ARRIVED_AT_FLOWER_FIELDS)
            EVT_SET(LVar0, MSG_MAC_Gate_009A)
        EVT_CASE_LT(STORY_CH6_STAR_SPIRIT_RESCUED)
            EVT_SET(LVar0, MSG_MAC_Gate_009B)
        EVT_CASE_LT(STORY_CH7_INVITED_TO_STARBORN_VALLEY)
            EVT_SET(LVar0, MSG_MAC_Gate_009C)
        EVT_CASE_LT(STORY_CH7_STAR_SPRIT_DEPARTED)
            EVT_SET(LVar0, MSG_MAC_Gate_009D)
        EVT_CASE_LT(STORY_EPILOGUE)
            EVT_SET(LVar0, MSG_MAC_Gate_009E)
        EVT_CASE_GE(STORY_EPILOGUE)
            EVT_SET(LVar0, MSG_Outro_002E)
    EVT_END_SWITCH
    EVT_CALL(SpeakToPlayer, NPC_SELF, ANIM_Toad_Red_Talk, ANIM_Toad_Red_Idle, 0, LVar0)
    EVT_RETURN
    EVT_END
};

EvtScript N(EVS_NpcInteract_Toad_06) = {
    EVT_SWITCH(GB_StoryProgress)
        EVT_CASE_LT(STORY_CH0_MET_STAR_SPIRITS)
            EVT_SET(LVar0, MSG_MAC_Gate_009F)
        EVT_CASE_LT(STORY_CH1_MERLIN_REVEALED_KOOPA_BROS)
            EVT_SET(LVar0, MSG_MAC_Gate_00A0)
        EVT_CASE_LT(STORY_CH1_STAR_SPRIT_DEPARTED)
            EVT_SET(LVar0, MSG_MAC_Gate_00A1)
        EVT_CASE_LT(STORY_CH2_STAR_SPRIT_DEPARTED)
            EVT_IF_EQ(GF_MAC03_BombedRock, FALSE)
                EVT_SET(LVar0, MSG_MAC_Gate_00A2)
            EVT_ELSE
                EVT_SET(LVar0, MSG_MAC_Gate_00A3)
            EVT_END_IF
        EVT_CASE_LT(STORY_CH3_STAR_SPIRIT_RESCUED)
            EVT_SET(LVar0, MSG_MAC_Gate_00A4)
        EVT_CASE_LT(STORY_CH4_STAR_SPRIT_DEPARTED)
            EVT_IF_EQ(GF_MAC00_DictionaryStolen, FALSE)
                EVT_SET(LVar0, MSG_MAC_Gate_00A5)
            EVT_ELSE
                EVT_IF_EQ(GF_MAC00_DictionaryReturned, FALSE)
                    EVT_SET(LVar0, MSG_MAC_Gate_00A6)
                EVT_ELSE
                    EVT_SET(LVar0, MSG_MAC_Gate_00A7)
                EVT_END_IF
            EVT_END_IF
        EVT_CASE_LT(STORY_CH5_DEFEATED_FUZZIPEDE)
            EVT_SET(LVar0, MSG_MAC_Gate_00A8)
        EVT_CASE_LT(STORY_CH5_STAR_SPRIT_DEPARTED)
            EVT_SET(LVar0, MSG_MAC_Gate_00A9)
        EVT_CASE_LT(STORY_CH6_ARRIVED_AT_FLOWER_FIELDS)
            EVT_SET(LVar0, MSG_MAC_Gate_00AA)
        EVT_CASE_LT(STORY_CH6_STAR_SPIRIT_RESCUED)
            EVT_SET(LVar0, MSG_MAC_Gate_00AB)
        EVT_CASE_LT(STORY_CH7_INVITED_TO_STARBORN_VALLEY)
            EVT_SET(LVar0, MSG_MAC_Gate_00AC)
        EVT_CASE_LT(STORY_CH7_STAR_SPRIT_DEPARTED)
            EVT_SET(LVar0, MSG_MAC_Gate_00AD)
        EVT_CASE_LT(STORY_EPILOGUE)
            EVT_SET(LVar0, MSG_MAC_Gate_00AE)
        EVT_CASE_GE(STORY_EPILOGUE)
            EVT_SET(LVar0, MSG_Outro_002F)
    EVT_END_SWITCH
    EVT_CALL(SpeakToPlayer, NPC_SELF, ANIM_Toad_Yellow_Talk, ANIM_Toad_Yellow_Idle, 0, LVar0)
    EVT_RETURN
    EVT_END
};

EvtScript N(EVS_NpcInteract_Lovers) = {
    EVT_SWITCH(GB_StoryProgress)
        EVT_CASE_LT(STORY_CH0_MET_STAR_SPIRITS)
            EVT_SET(LVar0, MSG_MAC_Gate_00AF)
            EVT_SET(LVar1, MSG_MAC_Gate_00B0)
        EVT_CASE_LT(STORY_CH1_MERLIN_REVEALED_KOOPA_BROS)
            EVT_SET(LVar0, MSG_MAC_Gate_00B1)
            EVT_SET(LVar1, MSG_MAC_Gate_00B2)
        EVT_CASE_LT(STORY_CH1_STAR_SPRIT_DEPARTED)
            EVT_SET(LVar0, MSG_MAC_Gate_00B3)
            EVT_SET(LVar1, MSG_MAC_Gate_00B4)
        EVT_CASE_LT(STORY_CH2_STAR_SPRIT_DEPARTED)
            EVT_IF_EQ(GF_MAC03_BombedRock, FALSE)
                EVT_SET(LVar0, MSG_MAC_Gate_00B5)
                EVT_SET(LVar1, MSG_MAC_Gate_00B6)
            EVT_ELSE
                EVT_SET(LVar0, MSG_MAC_Gate_00B7)
                EVT_SET(LVar1, MSG_MAC_Gate_00B8)
            EVT_END_IF
        EVT_CASE_LT(STORY_CH3_STAR_SPIRIT_RESCUED)
            EVT_SET(LVar0, MSG_MAC_Gate_00B9)
            EVT_SET(LVar1, MSG_MAC_Gate_00BA)
        EVT_CASE_LT(STORY_CH4_STAR_SPRIT_DEPARTED)
            EVT_IF_EQ(GF_MAC03_ShyGuyBlockingTracks, FALSE)
                EVT_SET(LVar0, MSG_MAC_Gate_00BB)
                EVT_SET(LVar1, MSG_MAC_Gate_00BC)
            EVT_ELSE
                EVT_IF_EQ(GF_MAC03_ShyGuyChasedOff, FALSE)
                    EVT_SET(LVar0, MSG_MAC_Gate_00BD)
                    EVT_SET(LVar1, MSG_MAC_Gate_00BE)
                EVT_ELSE
                    EVT_SET(LVar0, MSG_MAC_Gate_00BF)
                    EVT_SET(LVar1, MSG_MAC_Gate_00C0)
                EVT_END_IF
            EVT_END_IF
        EVT_CASE_LT(STORY_CH5_DEFEATED_FUZZIPEDE)
            EVT_SET(LVar0, MSG_MAC_Gate_00C1)
            EVT_SET(LVar1, MSG_MAC_Gate_00C2)
        EVT_CASE_LT(STORY_CH5_STAR_SPRIT_DEPARTED)
            EVT_SET(LVar0, MSG_MAC_Gate_00C3)
            EVT_SET(LVar1, MSG_MAC_Gate_00C4)
        EVT_CASE_LT(STORY_CH6_ARRIVED_AT_FLOWER_FIELDS)
            EVT_SET(LVar0, MSG_MAC_Gate_00C5)
            EVT_SET(LVar1, MSG_MAC_Gate_00C6)
        EVT_CASE_LT(STORY_CH6_STAR_SPIRIT_RESCUED)
            EVT_SET(LVar0, MSG_MAC_Gate_00C7)
            EVT_SET(LVar1, MSG_MAC_Gate_00C8)
        EVT_CASE_LT(STORY_CH7_INVITED_TO_STARBORN_VALLEY)
            EVT_SET(LVar0, MSG_MAC_Gate_00C9)
            EVT_SET(LVar1, MSG_MAC_Gate_00CA)
        EVT_CASE_LT(STORY_CH7_STAR_SPRIT_DEPARTED)
            EVT_SET(LVar0, MSG_MAC_Gate_00CB)
            EVT_SET(LVar1, MSG_MAC_Gate_00CC)
        EVT_CASE_LT(STORY_EPILOGUE)
            EVT_SET(LVar0, MSG_MAC_Gate_00CD)
            EVT_SET(LVar1, MSG_MAC_Gate_00CE)
        EVT_CASE_GE(STORY_EPILOGUE)
            EVT_SET(LVar0, MSG_Outro_0030)
            EVT_SET(LVar1, MSG_Outro_0031)
    EVT_END_SWITCH
    EVT_CALL(SpeakToPlayer, NPC_FickleLover, ANIM_Toad_Blue_Talk, ANIM_Toad_Blue_Idle, 5, LVar0)
    EVT_CALL(SpeakToPlayer, NPC_ShamelessLover, ANIM_Toadette_Pink_Talk, ANIM_Toadette_Pink_Idle, 5, LVar1)
    EVT_RETURN
    EVT_END
};

EvtScript N(EVS_NpcInteract_ThreeSisters) = {
    EVT_SWITCH(GB_StoryProgress)
        EVT_CASE_LT(STORY_CH0_MET_STAR_SPIRITS)
            EVT_SET(LVar0, MSG_MAC_Gate_00CF)
            EVT_SET(LVar1, MSG_MAC_Gate_00D0)
            EVT_SET(LVar2, MSG_MAC_Gate_00D1)
        EVT_CASE_LT(STORY_CH1_MERLIN_REVEALED_KOOPA_BROS)
            EVT_SET(LVar0, MSG_MAC_Gate_00D2)
            EVT_SET(LVar1, MSG_MAC_Gate_00D3)
            EVT_SET(LVar2, MSG_MAC_Gate_00D4)
        EVT_CASE_LT(STORY_CH1_STAR_SPRIT_DEPARTED)
            EVT_SET(LVar0, MSG_MAC_Gate_00D5)
            EVT_SET(LVar1, MSG_MAC_Gate_00D6)
            EVT_SET(LVar2, MSG_MAC_Gate_00D7)
        EVT_CASE_LT(STORY_CH2_STAR_SPRIT_DEPARTED)
            EVT_IF_EQ(GF_MAC03_BombedRock, FALSE)
                EVT_SET(LVar0, MSG_MAC_Gate_00D8)
                EVT_SET(LVar1, MSG_MAC_Gate_00D9)
                EVT_SET(LVar2, MSG_MAC_Gate_00DA)
            EVT_ELSE
                EVT_SET(LVar0, MSG_MAC_Gate_00DB)
                EVT_SET(LVar1, MSG_MAC_Gate_00DC)
                EVT_SET(LVar2, MSG_MAC_Gate_00DD)
            EVT_END_IF
        EVT_CASE_LT(STORY_CH3_STAR_SPIRIT_RESCUED)
            EVT_SET(LVar0, MSG_MAC_Gate_00DE)
            EVT_SET(LVar1, MSG_MAC_Gate_00DF)
            EVT_SET(LVar2, MSG_MAC_Gate_00E0)
        EVT_CASE_LT(STORY_CH4_RETURNED_STOREROOM_KEY)
            EVT_IF_EQ(GF_MAC04_StoreroomKeyStolen, FALSE)
                EVT_SET(LVar0, MSG_MAC_Gate_00E1)
                EVT_SET(LVar1, MSG_MAC_Gate_00E2)
                EVT_SET(LVar2, MSG_MAC_Gate_00E3)
            EVT_ELSE
                EVT_SET(LVar0, MSG_MAC_Gate_00E4)
                EVT_SET(LVar1, MSG_MAC_Gate_00E5)
                EVT_SET(LVar2, MSG_MAC_Gate_00E6)
            EVT_END_IF
        EVT_CASE_LT(STORY_CH4_STAR_SPRIT_DEPARTED)
            EVT_SET(LVar0, MSG_MAC_Gate_00E7)
            EVT_SET(LVar1, MSG_MAC_Gate_00E8)
            EVT_SET(LVar2, MSG_MAC_Gate_00E9)
        EVT_CASE_LT(STORY_CH5_DEFEATED_FUZZIPEDE)
            EVT_SET(LVar0, MSG_MAC_Gate_00EA)
            EVT_SET(LVar1, MSG_MAC_Gate_00EB)
            EVT_SET(LVar2, MSG_MAC_Gate_00EC)
        EVT_CASE_LT(STORY_CH5_STAR_SPRIT_DEPARTED)
            EVT_SET(LVar0, MSG_MAC_Gate_00ED)
            EVT_SET(LVar1, MSG_MAC_Gate_00EE)
            EVT_SET(LVar2, MSG_MAC_Gate_00EF)
        EVT_CASE_LT(STORY_CH6_ARRIVED_AT_FLOWER_FIELDS)
            EVT_SET(LVar0, MSG_MAC_Gate_00F0)
            EVT_SET(LVar1, MSG_MAC_Gate_00F1)
            EVT_SET(LVar2, MSG_MAC_Gate_00F2)
        EVT_CASE_LT(STORY_CH6_STAR_SPIRIT_RESCUED)
            EVT_SET(LVar0, MSG_MAC_Gate_00F3)
            EVT_SET(LVar1, MSG_MAC_Gate_00F4)
            EVT_SET(LVar2, MSG_MAC_Gate_00F5)
        EVT_CASE_LT(STORY_CH7_INVITED_TO_STARBORN_VALLEY)
            EVT_SET(LVar0, MSG_MAC_Gate_00F6)
            EVT_SET(LVar1, MSG_MAC_Gate_00F7)
            EVT_SET(LVar2, MSG_MAC_Gate_00F8)
        EVT_CASE_LT(STORY_CH7_STAR_SPRIT_DEPARTED)
            EVT_SET(LVar0, MSG_MAC_Gate_00F9)
            EVT_SET(LVar1, MSG_MAC_Gate_00FA)
            EVT_SET(LVar2, MSG_MAC_Gate_00FB)
        EVT_CASE_LT(STORY_EPILOGUE)
            EVT_SET(LVar0, MSG_MAC_Gate_00FC)
            EVT_SET(LVar1, MSG_MAC_Gate_00FD)
            EVT_SET(LVar2, MSG_MAC_Gate_00FE)
        EVT_CASE_GE(STORY_EPILOGUE)
            EVT_SET(LVar0, MSG_Outro_0032)
            EVT_SET(LVar1, MSG_Outro_0033)
            EVT_SET(LVar2, MSG_Outro_0034)
    EVT_END_SWITCH
    EVT_CALL(SpeakToPlayer, NPC_KrisT, ANIM_Toadette_Green_Talk, ANIM_Toadette_Green_Idle, 0, LVar0)
    EVT_CALL(SpeakToPlayer, NPC_MissT, ANIM_Toadette_Orange_Talk, ANIM_Toadette_Orange_Idle, 0, LVar1)
    EVT_CALL(SpeakToPlayer, NPC_FelissaT, ANIM_Toadette_Purple_Talk, ANIM_Toadette_Purple_Idle, 0, LVar2)
    EVT_RETURN
    EVT_END
};

EvtScript N(EVS_NpcInteract_MissT) = {
    EVT_EXEC_WAIT(N(EVS_NpcInteract_ThreeSisters))
    EVT_EXEC_WAIT(N(EVS_LetterPrompt_MissT))
    EVT_IF_NE(LVarC, 0)
        EVT_RETURN
    EVT_END_IF
    EVT_RETURN
    EVT_END
};

EvtScript N(EVS_NpcInteract_Toad_08) = {
    EVT_SWITCH(GB_StoryProgress)
        EVT_CASE_LT(STORY_CH0_MET_STAR_SPIRITS)
            EVT_SET(LVar0, MSG_MAC_Gate_0103)
        EVT_CASE_LT(STORY_CH1_MERLIN_REVEALED_KOOPA_BROS)
            EVT_SET(LVar0, MSG_MAC_Gate_0104)
        EVT_CASE_LT(STORY_CH1_STAR_SPRIT_DEPARTED)
            EVT_SET(LVar0, MSG_MAC_Gate_0105)
        EVT_CASE_LT(STORY_CH2_STAR_SPRIT_DEPARTED)
            EVT_IF_EQ(GF_MAC03_BombedRock, FALSE)
                EVT_SET(LVar0, MSG_MAC_Gate_0106)
            EVT_ELSE
                EVT_SET(LVar0, MSG_MAC_Gate_0107)
            EVT_END_IF
        EVT_CASE_LT(STORY_CH3_STAR_SPIRIT_RESCUED)
            EVT_SET(LVar0, MSG_MAC_Gate_0108)
        EVT_CASE_LT(STORY_CH4_STAR_SPRIT_DEPARTED)
            EVT_IF_EQ(GF_MAC00_DictionaryStolen, FALSE)
                EVT_SET(LVar0, MSG_MAC_Gate_0109)
            EVT_ELSE
                EVT_IF_EQ(GF_MAC00_DictionaryReturned, FALSE)
                    EVT_SET(LVar0, MSG_MAC_Gate_010A)
                EVT_ELSE
                    EVT_SET(LVar0, MSG_MAC_Gate_010B)
                EVT_END_IF
            EVT_END_IF
        EVT_CASE_LT(STORY_CH5_DEFEATED_FUZZIPEDE)
            EVT_SET(LVar0, MSG_MAC_Gate_010C)
        EVT_CASE_LT(STORY_CH5_STAR_SPRIT_DEPARTED)
            EVT_SET(LVar0, MSG_MAC_Gate_010D)
        EVT_CASE_LT(STORY_CH6_ARRIVED_AT_FLOWER_FIELDS)
            EVT_SET(LVar0, MSG_MAC_Gate_010E)
        EVT_CASE_LT(STORY_CH6_STAR_SPIRIT_RESCUED)
            EVT_SET(LVar0, MSG_MAC_Gate_010F)
        EVT_CASE_LT(STORY_CH7_INVITED_TO_STARBORN_VALLEY)
            EVT_SET(LVar0, MSG_MAC_Gate_0110)
        EVT_CASE_LT(STORY_CH7_STAR_SPRIT_DEPARTED)
            EVT_SET(LVar0, MSG_MAC_Gate_0111)
        EVT_CASE_LT(STORY_EPILOGUE)
            EVT_SET(LVar0, MSG_MAC_Gate_0112)
        EVT_CASE_GE(STORY_EPILOGUE)
            EVT_SET(LVar0, MSG_Outro_0035)
    EVT_END_SWITCH
    EVT_CALL(SpeakToPlayer, NPC_SELF, ANIM_Toad_Blue_Talk, ANIM_Toad_Blue_Idle, 0, LVar0)
    EVT_RETURN
    EVT_END
};

EvtScript N(EVS_NpcAux_ShamelessLover) = {
    EVT_CALL(SetNpcAnimation, NPC_SELF, ANIM_Toadette_Pink_Still)
    EVT_WAIT(3)
    EVT_CALL(SetNpcAnimation, NPC_SELF, ANIM_Toadette_Pink_Idle)
    EVT_RETURN
    EVT_END
};

EvtScript N(EVS_NpcAux_KrisT) = {
    EVT_CALL(SetNpcAnimation, NPC_SELF, ANIM_Toadette_Green_Still)
    EVT_WAIT(2)
    EVT_CALL(SetNpcAnimation, NPC_SELF, ANIM_Toadette_Green_Idle)
    EVT_RETURN
    EVT_END
};

EvtScript N(EVS_NpcAux_MissT) = {
    EVT_CALL(SetNpcAnimation, NPC_SELF, ANIM_Toadette_Orange_Still)
    EVT_WAIT(6)
    EVT_CALL(SetNpcAnimation, NPC_SELF, ANIM_Toadette_Orange_Idle)
    EVT_RETURN
    EVT_END
};

EvtScript N(EVS_NpcAux_FelissaT) = {
    EVT_CALL(SetNpcAnimation, NPC_SELF, ANIM_Toadette_Purple_Still)
    EVT_WAIT(8)
    EVT_CALL(SetNpcAnimation, NPC_SELF, ANIM_Toadette_Purple_Idle)
    EVT_RETURN
    EVT_END
};

EvtScript N(EVS_NpcInteract_Toad_09) = {
    EVT_CALL(FindKeyItem, ITEM_FIRST_DEGREE_CARD, LVar1)
    EVT_CALL(FindKeyItem, ITEM_SECOND_DEGREE_CARD, LVar2)
    EVT_CALL(FindKeyItem, ITEM_THIRD_DEGREE_CARD, LVar3)
    EVT_CALL(FindKeyItem, ITEM_FOURTH_DEGREE_CARD, LVar4)
    EVT_CALL(FindKeyItem, ITEM_DIPLOMA, LVar5)
    EVT_IF_NE(LVar1, -1)
        EVT_CALL(SpeakToPlayer, NPC_SELF, ANIM_Toad_Yellow_Talk, ANIM_Toad_Yellow_Idle, 0, MSG_MAC_Gate_0114)
        EVT_RETURN
    EVT_END_IF
    EVT_IF_NE(LVar2, -1)
        EVT_CALL(SpeakToPlayer, NPC_SELF, ANIM_Toad_Yellow_Talk, ANIM_Toad_Yellow_Idle, 0, MSG_MAC_Gate_0115)
        EVT_RETURN
    EVT_END_IF
    EVT_IF_NE(LVar3, -1)
        EVT_CALL(SpeakToPlayer, NPC_SELF, ANIM_Toad_Yellow_Talk, ANIM_Toad_Yellow_Idle, 0, MSG_MAC_Gate_0116)
        EVT_RETURN
    EVT_END_IF
    EVT_IF_NE(LVar4, -1)
        EVT_CALL(SpeakToPlayer, NPC_SELF, ANIM_Toad_Yellow_Talk, ANIM_Toad_Yellow_Idle, 0, MSG_MAC_Gate_0117)
        EVT_RETURN
    EVT_END_IF
    EVT_IF_NE(LVar5, -1)
        EVT_CALL(SpeakToPlayer, NPC_SELF, ANIM_Toad_Yellow_Talk, ANIM_Toad_Yellow_Idle, 0, MSG_MAC_Gate_0118)
        EVT_RETURN
    EVT_END_IF
    EVT_CALL(SpeakToPlayer, NPC_SELF, ANIM_Toad_Yellow_Talk, ANIM_Toad_Yellow_Idle, 0, MSG_MAC_Gate_0113)
    EVT_RETURN
    EVT_END
};

EvtScript N(EVS_NpcInit_Toad_04) = {
    EVT_CALL(BindNpcInteract, NPC_SELF, EVT_PTR(N(EVS_NpcInteract_Toad_04)))
    EVT_IF_LT(GB_StoryProgress, STORY_EPILOGUE)
        EVT_RETURN
    EVT_END_IF
    EVT_CALL(GetEntryID, LVar0)
    EVT_IF_NE(LVar0, mac_00_ENTRY_7)
        EVT_EXEC(N(EVS_BlockExitToGoomaRoad))
    EVT_END_IF
    EVT_RETURN
    EVT_END
};

EvtScript N(EVS_NpcInit_Toad_05) = {
    EVT_CALL(BindNpcInteract, NPC_SELF, EVT_PTR(N(EVS_NpcInteract_Toad_05)))
    EVT_RETURN
    EVT_END
};

EvtScript N(EVS_NpcInit_Toad_06) = {
    EVT_CALL(BindNpcInteract, NPC_SELF, EVT_PTR(N(EVS_NpcInteract_Toad_06)))
    EVT_RETURN
    EVT_END
};

EvtScript N(EVS_NpcInit_FickleLover) = {
    EVT_CALL(BindNpcInteract, NPC_SELF, EVT_PTR(N(EVS_NpcInteract_Lovers)))
    EVT_RETURN
    EVT_END
};

EvtScript N(EVS_NpcInit_ShamelessLover) = {
    EVT_CALL(BindNpcInteract, NPC_SELF, EVT_PTR(N(EVS_NpcInteract_Lovers)))
    EVT_CALL(BindNpcAux, NPC_SELF, EVT_PTR(N(EVS_NpcAux_ShamelessLover)))
    EVT_RETURN
    EVT_END
};

EvtScript N(EVS_NpcInit_KrisT) = {
    EVT_CALL(BindNpcInteract, NPC_SELF, EVT_PTR(N(EVS_NpcInteract_ThreeSisters)))
    EVT_CALL(BindNpcAux, NPC_SELF, EVT_PTR(N(EVS_NpcAux_KrisT)))
    EVT_RETURN
    EVT_END
};

EvtScript N(EVS_NpcInit_MissT) = {
    EVT_CALL(BindNpcInteract, NPC_SELF, EVT_PTR(N(EVS_NpcInteract_MissT)))
    EVT_CALL(BindNpcAux, NPC_SELF, EVT_PTR(N(EVS_NpcAux_MissT)))
    EVT_RETURN
    EVT_END
};

EvtScript N(EVS_NpcInit_FelissaT) = {
    EVT_CALL(BindNpcInteract, NPC_SELF, EVT_PTR(N(EVS_NpcInteract_ThreeSisters)))
    EVT_CALL(BindNpcAux, NPC_SELF, EVT_PTR(N(EVS_NpcAux_FelissaT)))
    EVT_RETURN
    EVT_END
};

EvtScript N(EVS_NpcInit_DojoSpectator) = {
    EVT_IF_GE(GB_StoryProgress, STORY_EPILOGUE)
        EVT_CALL(SetNpcPos, NPC_DojoSpectator, 350, 20, -100)
    EVT_END_IF
    EVT_CALL(BindNpcInteract, NPC_SELF, EVT_PTR(N(EVS_NpcInteract_Toad_08)))
    EVT_RETURN
    EVT_END
};

EvtScript N(EVS_NpcInit_DojoFan) = {
    EVT_CALL(BindNpcInteract, NPC_SELF, EVT_PTR(N(EVS_NpcInteract_Toad_09)))
    EVT_RETURN
    EVT_END
};

StaticNpc N(NpcData_SharedTownsfolk)[] = {
    {
        .id = NPC_Toad_04,
        .settings = &N(NpcSettings_Toad_Stationary_Shared),
        .pos = { -150.0f, 0.0f, -275.0f },
        .yaw = 90,
        .flags = ENEMY_FLAGS_1 | ENEMY_FLAGS_8 | ENEMY_FLAGS_100 | ENEMY_FLAGS_400 | ENEMY_FLAGS_800 | ENEMY_FLAGS_2000 | ENEMY_FLAGS_10000 | ENEMY_FLAGS_100000,
        .init = &N(EVS_NpcInit_Toad_04),
        .drops = TOAD_DROPS,
        .animations = TOAD_RED_ANIMS,
        .tattle = MSG_NpcTattle_MAC_GateGuardian,
    },
    {
        .id = NPC_Toad_05,
        .settings = &N(NpcSettings_Toad_Wander_Shared),
        .pos = { 219.0f, 0.0f, -45.0f },
        .yaw = 90,
        .flags = ENEMY_FLAGS_1 | ENEMY_FLAGS_8 | ENEMY_FLAGS_100 | ENEMY_FLAGS_400 | ENEMY_FLAGS_800 | ENEMY_FLAGS_2000 | ENEMY_FLAGS_10000,
        .init = &N(EVS_NpcInit_Toad_05),
        .drops = TOAD_DROPS,
        .territory = {
            .patrol = {
                .isFlying = TRUE,
                .moveSpeedOverride = NO_OVERRIDE_MOVEMENT_SPEED,
                .numPoints  = 5,
                .points  = {
                    { 219, 0, -45 },
                    { 144, 0, -10 },
                    { 163, 0, -50 },
                    { 240, 0, 50 },
                    { 275, 0, 10 },
                },
                .detectShape = SHAPE_CYLINDER,
                .detectPos  = { 0, 0, 0 },
                .detectSize = { 200 },
            }
        },
        .animations = TOAD_RED_ANIMS,
        .tattle = MSG_NpcTattle_MAC_ShopLoiterer,
    },
    {
        .id = NPC_Toad_06,
        .settings = &N(NpcSettings_Toad_Patrol_Shared),
        .pos = { -290.0f, 0.0f, -120.0f },
        .yaw = 90,
        .flags = ENEMY_FLAGS_1 | ENEMY_FLAGS_8 | ENEMY_FLAGS_100 | ENEMY_FLAGS_400 | ENEMY_FLAGS_800 | ENEMY_FLAGS_2000 | ENEMY_FLAGS_10000,
        .init = &N(EVS_NpcInit_Toad_06),
        .drops = TOAD_DROPS,
        .territory = {
            .patrol = {
                .isFlying = TRUE,
                .moveSpeedOverride = NO_OVERRIDE_MOVEMENT_SPEED,
                .numPoints  = 2,
                .points  = {
                    { -290, 0, -120 },
                    { 37, 0, -150 },
                },
                .detectShape = SHAPE_CYLINDER,
                .detectPos  = { 0, 0, 0 },
                .detectSize = { 200 },
            }
        },
        .animations = TOAD_YELLOW_ANIMS,
        .tattle = MSG_NpcTattle_MAC_NewsEnthusiast,
    },
    {
        .id = NPC_FickleLover,
        .settings = &N(NpcSettings_Toad_Stationary_Shared),
        .pos = { -40.0f, 0.0f, 61.0f },
        .yaw = 90,
        .flags = ENEMY_FLAGS_1 | ENEMY_FLAGS_8 | ENEMY_FLAGS_100 | ENEMY_FLAGS_400 | ENEMY_FLAGS_800 | ENEMY_FLAGS_2000 | ENEMY_FLAGS_10000 | ENEMY_FLAGS_400000,
        .init = &N(EVS_NpcInit_FickleLover),
        .drops = TOAD_DROPS,
        .animations = TOAD_BLUE_ANIMS,
        .tattle = MSG_NpcTattle_MAC_FickleLovers,
    },
    {
        .id = NPC_ShamelessLover,
        .settings = &N(NpcSettings_Toad_Stationary_Shared),
        .pos = { -15.0f, 0.0f, 60.0f },
        .yaw = 270,
        .flags = ENEMY_FLAGS_1 | ENEMY_FLAGS_8 | ENEMY_FLAGS_100 | ENEMY_FLAGS_400 | ENEMY_FLAGS_800 | ENEMY_FLAGS_2000 | ENEMY_FLAGS_10000 | ENEMY_FLAGS_400000,
        .init = &N(EVS_NpcInit_ShamelessLover),
        .drops = TOADETTE_DROPS,
        .animations = TOADETTE_PINK_ANIMS,
        .tattle = MSG_NpcTattle_MAC_ShamelessLover,
    },
    {
        .id = NPC_KrisT,
        .settings = &N(NpcSettings_Toad_Stationary_Shared),
        .pos = { 426.0f, 20.0f, 268.0f },
        .yaw = 90,
        .flags = ENEMY_FLAGS_1 | ENEMY_FLAGS_8 | ENEMY_FLAGS_100 | ENEMY_FLAGS_400 | ENEMY_FLAGS_800 | ENEMY_FLAGS_2000 | ENEMY_FLAGS_10000,
        .init = &N(EVS_NpcInit_KrisT),
        .drops = TOADETTE_DROPS,
        .animations = TOADETTE_GREEN_ANIMS,
        .tattle = MSG_NpcTattle_MAC_ThreeSisters_Eldest,
    },
    {
        .id = NPC_MissT,
        .settings = &N(NpcSettings_Toad_Stationary_Shared),
        .pos = { 381.0f, 20.0f, 326.0f },
        .yaw = 180,
        .flags = ENEMY_FLAGS_1 | ENEMY_FLAGS_8 | ENEMY_FLAGS_100 | ENEMY_FLAGS_400 | ENEMY_FLAGS_800 | ENEMY_FLAGS_2000 | ENEMY_FLAGS_10000,
        .init = &N(EVS_NpcInit_MissT),
        .drops = TOADETTE_DROPS,
        .animations = TOADETTE_ORANGE_ANIMS,
        .tattle = MSG_NpcTattle_MAC_ThreeSisters_Middle,
    },
    {
        .id = NPC_FelissaT,
        .settings = &N(NpcSettings_Toad_Stationary_Shared),
        .pos = { 476.0f, 20.0f, 326.0f },
        .yaw = 270,
        .flags = ENEMY_FLAGS_1 | ENEMY_FLAGS_8 | ENEMY_FLAGS_100 | ENEMY_FLAGS_400 | ENEMY_FLAGS_800 | ENEMY_FLAGS_2000 | ENEMY_FLAGS_10000,
        .init = &N(EVS_NpcInit_FelissaT),
        .drops = TOADETTE_DROPS,
        .animations = TOADETTE_PURPLE_ANIMS,
        .tattle = MSG_NpcTattle_MAC_ThreeSisters_Youngest,
    },
    {
        .id = NPC_DojoSpectator,
        .settings = &N(NpcSettings_Toad_Stationary_Shared),
        .pos = { 424.0f, 20.0f, -85.0f },
        .yaw = 270,
        .flags = ENEMY_FLAGS_1 | ENEMY_FLAGS_8 | ENEMY_FLAGS_100 | ENEMY_FLAGS_400 | ENEMY_FLAGS_800 | ENEMY_FLAGS_2000 | ENEMY_FLAGS_10000,
        .init = &N(EVS_NpcInit_DojoSpectator),
        .drops = TOAD_DROPS,
        .animations = TOAD_BLUE_ANIMS,
        .tattle = MSG_NpcTattle_MAC_DojoSpectator,
    },
    {
        .id = NPC_DojoFan,
        .settings = &N(NpcSettings_Toad_Stationary_Shared),
        .pos = { 373.0f, 0.0f, 22.0f },
        .yaw = 270,
        .flags = ENEMY_FLAGS_1 | ENEMY_FLAGS_8 | ENEMY_FLAGS_100 | ENEMY_FLAGS_400 | ENEMY_FLAGS_800 | ENEMY_FLAGS_2000 | ENEMY_FLAGS_10000,
        .init = &N(EVS_NpcInit_DojoFan),
        .drops = TOAD_DROPS,
        .animations = TOAD_YELLOW_ANIMS,
        .tattle = MSG_NpcTattle_MAC_DojoFanToad,
    },
};
