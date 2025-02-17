#include "kpa_16.h"

EvtScript N(EVS_SetupMusic) = {
    EVT_CALL(SetMusicTrack, 0, SONG_BOWSERS_CASTLE, 0, 8)
    EVT_CALL(UseDoorSounds, DOOR_SOUNDS_METAL)
    EVT_IF_EQ(GF_KPA16_ShutOffLava, FALSE)
        EVT_CALL(PlayAmbientSounds, AMBIENT_UNDER_SEA6)
    EVT_END_IF
    EVT_THREAD
        EVT_WAIT(30)
        EVT_CALL(SetMusicTrackVolumes, TRACK_VOLS_KPA_1)
    EVT_END_THREAD
    EVT_RETURN
    EVT_END
};
