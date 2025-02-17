#include "flo_18.h"

EvtScript N(EVS_SetupMusic) = {
    EVT_SWITCH(GB_StoryProgress)
        EVT_CASE_LT(STORY_CH6_DESTROYED_PUFF_PUFF_MACHINE)
            EVT_CALL(SetMusicTrack, 0, SONG_PUFF_PUFF_MACHINE, 0, 8)
            EVT_CALL(PlaySoundAtCollider, COLLIDER_o126, SOUND_80000025, 0)
        EVT_CASE_DEFAULT
            EVT_CALL(SetMusicTrack, 0, SONG_FLOWER_FIELDS_SUNNY, 0, 8)
    EVT_END_SWITCH
    EVT_RETURN
    EVT_END
};
