// 2BF90.c
void au_mseq_manager_init(AuAmbienceManager* arg0, s8 arg1, s8 reverbType, AuGlobals* arg3);
AuResult func_80050C30(u32 arg0);
void func_80050C54(s32 arg0, s32 arg1);
void au_mseq_set_disabled(s32 arg0, s32 arg1);
AuResult func_80050CA0(s32 arg0, s32 arg1);
void func_80050D50(AuAmbPlayer* arg0);
void func_80050EF0_fade_out_unk(s32 arg0, s32 arg1);
void func_80050EF0_fade_in_unk(s32 arg0, s32 arg1);
void func_80050EF0_fade_out_quick(s32 arg0);
void func_80050EF0_fade_out_slow(s32 arg0, s32 arg1);
void au_mseq_set_volume(s32 arg0, s32 arg1, s32 arg2);
AuResult func_80051050(s32 arg0);
void func_800510A4(AuAmbienceManager* arg0, MSEQHeader* mseq, s32 index);
void snd_ambient_manager_update(AuAmbienceManager* arg0);
void func_80051334(AuAmbienceManager* manager, AuAmbPlayer* lambda);
void func_80051434(AuAmbienceManager* manager, AuAmbPlayer* lambda);
s32 au_mseq_read_next(AuAmbPlayer* arg0);
void au_mseq_player_stop(AuAmbienceManager* arg0, AuAmbPlayer* arg1);
void func_800522A8(AuAmbienceManager* arg0, AuAmbPlayer* lambda);
void func_8005232C(AuAmbienceManager* manager, AuAmbPlayer* lambda);

// 2d9a0_len_890.c
void func_800525A0(AuGlobals* globals);
void func_80052614(AuGlobals* globals);
void func_80052660(AuGlobals* globals);
void func_80052B44(AlUnkVoice* arg0);
s32 func_80052BC0(s32 arg0);
void func_80052BF8(AlUnkVoice* voice, AlUnkInstrumentData* arg1);
u8 func_80052CFC(AlUnkVoice* voice);
void func_80052E18(AlUnkVoice* arg0);

//2e230_len_2190.c
void func_80052E30(u8 index);
void au_engine_init(s32 outputRate);
static void au_reset_instrument(Instrument* instrument);
static void au_reset_drum_entry(BGMDrumInfo* arg0);
static void au_reset_instrument_entry(BGMInstrumentInfo* arg0);
void au_update_clients_2(void);
void au_update_players_main(void);
void func_80053654(AuGlobals* globals);
void func_80053888(AlUnkVoice* arg0, u8 arg1);
void au_reset_voice(AlUnkVoice* arg0, u8 arg1);
f32 au_compute_pitch_ratio(s32 arg0);
void au_fade_init(Fade* fade, s32 time, s32 startValue, s32 endValue);
void au_fade_clear(Fade* fade);
void au_fade_update(Fade* fade);
void func_80053A98(u8 arg0, u16 arg1, s32 arg2);
void func_80053AC8(Fade* fade);
void au_fade_set_vol_scale(Fade* fade, s16 value);
void func_80053B04(Fade* fade, u32 arg1, s32 target);
void func_80053BA8(Fade* fade);
Instrument* au_get_instrument(AuGlobals* globals, u32 bank, u32 patch, AlUnkInstrumentData* arg3);
void au_get_bgm_player_and_file(u32 playerIndex, BGMHeader** outCurrentTrackData, BGMPlayer** outPlayer);
void au_get_bgm_player(u32 playerIndex, BGMPlayer** outPlayer);
AuResult au_load_song_files(u32 arg0, BGMHeader* arg1, BGMPlayer* arg2);
AuResult func_80053E58(s32 arg0, BGMHeader* arg1);
BGMPlayer* func_80053F64(s32 arg0);
AuResult func_80053F80(u32 arg0);
BGMPlayer* func_80054248(u8 arg0);
void au_load_INIT(AuGlobals* arg0, s32 romAddr, ALHeap* heap);
AuResult au_fetch_SBN_file(u32 fileIdx, AuFileFormat format, SBNFileEntry* arg2);
void au_load_PER(AuGlobals* globals, s32 romAddr);
void au_load_PRG(AuGlobals* arg0, s32 romAddr);
// INCLUDE_ASM(s32, "audio/2e230_len_2190", snd_load_BGM);
InstrumentGroup* au_get_BK_instruments(s32 bankGroup, u32 bankIndex);
SoundBank* au_load_BK_to_bank(s32 bkFileOffset, SoundBank* bank, s32 bankIndex, s32 bankGroup);
void au_swizzle_BK_instruments(s32 bkFileOffset, SoundBank* bank, InstrumentGroup instruments, u32 instrumentCount, u8 arg4);
s32* func_80054AA0(s32* bkFileOffset, void* vaddr, s32 bankIndex, s32 bankGroup);
s32 snd_load_BK(s32 bkFileOffset, s32 bankIndex);
void func_80054C84(s32 bankIndex, s32 bankGroup);
void func_80054CE0(s32 arg0, u32 idx);
s32 func_80054D74(s32 arg0, s32 arg1);
void func_80054DA8(u32 arg0);
void au_read_rom(s32 romAddr, void* buffer, u32 size);
void au_memset(void* dst, s32 size, u8 value);
void au_copy_bytes(s8* src, s8* dest, s32 size);
void au_copy_words(void* src, void* dst, s32 size);

// 25f00_len_940.c
void create_audio_system(void);
//void nuAuPreNMIFuncSet(NUAuPreNMIFunc func);
void nuAuMgr(void* arg);
s32 nuAuDmaCallBack(s32 addr, s32 len, void *state, u8 arg3);
//ALDMAproc nuAuDmaNew(NUDMAState** state);
//void nuAuCleanDMABuffers(void);
void func_8004B328(NUScMsg mesg_type, u32 frameCounter);
//void alLink(ALLink* element, ALLink* after);
//void alUnlink(ALLink* element);

// 303c0_len_3e10.c
void au_load_BK_headers(AuGlobals* arg0, ALHeap*);

// sfx_player.c
void au_sfx_init(SoundManager* manager, u8 arg1, u8 arg2, AuGlobals* arg3, u8 arg4);
void au_sfx_load_groups_from_SEF(SoundManager* sndMgr);
void au_sfx_clear_queue(SoundManager* manager);
void au_sfx_enqueue_event(SoundManager* manager, u32 soundID, s16 volume, s16 pitchShift, u8 pan);
void au_sfx_update_main(SoundManager* manager);
s32 func_8004B9E4(SoundManager* manager, s32 arg1);
void func_8004BA54(SoundManager* manager, s32 arg1);
void func_8004BA74(SoundManager* manager, SoundSFXEntry* entry, SoundManagerA0*);
s16 au_sfx_manager_update(SoundManager* manager);

// 28910_len_5090.c
void au_bgm_update_main(BGMPlayer* player);
BGMPlayer* au_bgm_get_player_with_song_name(s32 songString);
AuResult au_bgm_dispatch_player_event(SongUpdateEvent* event);
AuResult au_bgm_stop_song(s32 songName);
void au_bgm_stop_all(void);
AuResult au_bgm_is_song_playing(s32 songName);
s32 func_8004DB28(BGMPlayer* player);
AuResult func_8004DB4C(SongUpdateEvent* s);
AuResult func_8004DC80(s32 songName);
AuResult func_8004DCB8(SongUpdateEvent* update, s32 clearChanged);
AuResult func_8004DE2C(SongUpdateEvent* update);
void func_8004DFD4(AuGlobals* globals);
AuResult func_8004E0F4(SongUpdateEvent* update);
void au_bgm_player_init(BGMPlayer* player, s32 arg1, s32 arg2, AuGlobals* arg3);
void au_bgm_set_effect_indices(BGMPlayer* player, u8* list);
void au_bgm_update_fade(BGMPlayer* player);
void func_8004E444(BGMPlayer* arg0);
s32 au_bgm_player_update_main(BGMPlayer* player);
void au_bgm_player_initialize(BGMPlayer* player);
void func_8004E844(BGMPlayer* player, s32 arg1);
void func_8004E880(BGMPlayer* player, s32 sampleRate, s32 divisor);
void au_bgm_player_read_segment(BGMPlayer* player);
void au_bgm_end_segment_loop(BGMPlayer* player, u32 cmd);
void au_bgm_load_subsegment(BGMPlayer* player, u32 cmd);
void au_bgm_player_update_stop(BGMPlayer* player);
void au_bgm_player_update_playing(BGMPlayer *player);
void au_BGMCmd_E0_MasterTempo(BGMPlayer* player, BGMPlayerTrack* track);
void au_BGMCmd_E1_MasterVolume(BGMPlayer* player, BGMPlayerTrack* track);
void au_BGMCmd_E2_MasterPitchShift(BGMPlayer* player, BGMPlayerTrack* track);
void au_BGMCmd_E3(BGMPlayer* player, BGMPlayerTrack* track);
void au_BGMCmd_E6_MasterEffect(BGMPlayer* player, BGMPlayerTrack* track);
void au_BGMCmd_E4_MasterTempoFade(BGMPlayer* player, BGMPlayerTrack* track);
void au_BGMCmd_E5_MasterVolumeFade(BGMPlayer* player, BGMPlayerTrack* track);
void au_BGMCmd_E8_TrackOverridePatch(BGMPlayer* player, BGMPlayerTrack* track);
void au_BGMCmd_E9_SubTrackVolume(BGMPlayer* arg0, BGMPlayerTrack* track);
void au_BGMCmd_F6_TrackVolumeFade(BGMPlayer* player, BGMPlayerTrack* track);
void au_BGMCmd_EA_SubTrackPan(BGMPlayer* player, BGMPlayerTrack* track);
void au_BGMCmd_EB_SubTrackReverb(BGMPlayer* player, BGMPlayerTrack* track);
void au_BGMCmd_EC_SegTrackVolume(BGMPlayer* player, BGMPlayerTrack* track);
void au_BGMCmd_ED_SubTrackCoarseTune(BGMPlayer* player, BGMPlayerTrack* track);
void au_BGMCmd_EE_SubTrackFineTune(BGMPlayer* player, BGMPlayerTrack* track);
void au_BGMCmd_EF_SegTrackTune(BGMPlayer* player, BGMPlayerTrack* track);
void au_BGMCmd_F0_TrackTremolo(BGMPlayer* player, BGMPlayerTrack* track);
void au_BGMCmd_F1_TrackTremoloSpeed(BGMPlayer* player, BGMPlayerTrack* track);
void au_BGMCmd_F2_TrackTremoloTime(BGMPlayer* player, BGMPlayerTrack* track);
void au_BGMCmd_F3_TrackTremoloStop(BGMPlayer* player, BGMPlayerTrack* track);
void au_BGMCmd_F4(BGMPlayer* player, BGMPlayerTrack* track);
void au_BGMCmd_F5_TrackVoice(BGMPlayer* player, BGMPlayerTrack* track);
void au_BGMCmd_F7_SubTrackReverbType(BGMPlayer* player, BGMPlayerTrack* track);
void au_BGMCmd_FD_EventTrigger(BGMPlayer* player, BGMPlayerTrack* track);
void au_BGMCmd_FE_Detour(BGMPlayer* player, BGMPlayerTrack* track);
void au_BGMCmd_FC_Jump(BGMPlayer* player, BGMPlayerTrack* track);
void au_BGMCmd_FF(BGMPlayer* player, BGMPlayerTrack* track);
void au_BGMCmd_NOP(BGMPlayer* player, BGMPlayerTrack* track);
void au_bgm_set_proximity_mix(s32 songName, u32 mix);
void au_bgm_set_playback_rate(BGMPlayer* player, f32 arg1);
void au_bgm_player_set_detune(BGMPlayer* player, s32 arg1);
void au_bgm_change_track_volume(BGMPlayer* player, s32 trackIdx, s16 arg2, u8 arg3);
void au_bgm_set_track_volumes(BGMPlayer* player, u8* arg1, s32 arg2);
void func_80050888(BGMPlayer* player, BGMPlayerTrack* track, s32 target, s32 duration);
void func_80050900(BGMPlayer* player);
AuResult func_80050970(SongUpdateEvent* arg0);

// 30450.c
/*
void func_80055050(ALHeap* heap);
void func_80055068(u32 arg0);
*/
void func_80055110(BGMPlayer* player);
/*
void func_8005513C(u32 arg0);
void snd_start_sound(s32 soundID, u8 volume, u8 pan);
void snd_start_sound_with_shift(s32 soundID, u8 volume, u8 pan, s16 pitchShift);
void snd_adjust_sound(s32 soundID, u8 volume, u8 pan);
void snd_adjust_sound_with_shift(s32 soundID, u8 volume, u8 pan, s16 pitchShift);
void snd_stop_sound(s32 soundID);
void func_800553F4(void);
void snd_start_sound_raw(s32 soundID, s16 volume, s16 pitchShift, s32 pan);
AuResult snd_ambient_80055448(s32 arg0);
AuResult snd_ambient_80055464(s32 arg0, s32 arg1);
AuResult snd_ambient_quick_fade_out(s32 arg0);
AuResult snd_ambient_slow_fade_out(s32 arg0, s32 arg1);
AuResult snd_ambient_8005553C(s32 arg0, s32 arg1);
AuResult snd_ambient_80055590(s32 arg0, s32 arg1);
AuResult snd_ambient_800555E4(s32 arg0);
AuResult snd_ambient_80055618(s32 arg0, s32 arg1);
AuResult au_ambience_set_volume(s32 arg0, s32 arg1, s32 arg2);
AuResult au_ambience_disable(s32 arg0);
AuResult au_ambience_enable(s32 arg0);
void snd_ambient_80055760(s32 arg0);
AuResult snd_ambient_800557CC(s32 arg0);
AuResult snd_ambient_80055848(s32 arg0);
AuResult au_song_load(s32 songID, s32 playerIndex);
AuResult au_song_start(s32 songName);
AuResult au_song_start_variation(s32 songName, s32 variation);
AuResult au_song_stop(s32 songName);
void au_stop_songs(void);
AuResult au_song_is_playing(s32 songName);
AuResult snd_set_song_variation_fade(s32 songName, s32 variation, s32 fadeInTime, s32 startVolume, s32 endVolume);
AuResult snd_set_song_fade(s32 songName, s32 fadeInTime, s32 startVolume, s32 endVolume);
AuResult snd_set_song_variation_fade_time(s32 songName, s32 fadeTime, s32 variation);
AuResult func_80055AF0(s32 songName);
AuResult func_80055B28(s32 songName);
AuResult func_80055B80(s32 songName);
AuResult func_80055BB8(s32 songName, s32 fadeTime);
AuResult func_80055BF0(s32 songName);
AuResult func_80055C2C(s32 songName);
AuResult func_80055C64(s32 songName);
AuResult func_80055C94(s32 songName);
AuResult snd_set_song_variation(s32 songName, s32 variation);
*/
AuResult snd_song_get_playing_info(s32 songName, BGMHeader** outTrackData, BGMPlayer** outPlayer);
/*
AuResult snd_song_set_playback_rate(s32 songName, f32 arg1);
AuResult snd_song_set_detune(s32 songName, s32 arg1);
AuResult func_80055DDC(s32 songName, s32 arg1);
AuResult snd_song_clear_track_volumes(s32 songName, MusicTrackVols arg1);
u8* func_80055EB4(MusicTrackVols arg0);
static AuResult snd_song_change_track_volume(s32 arg0, u32 arg1, u32 arg2);
AuResult snd_song_set_track_vol_mute(s32 arg0, s32 arg1);
AuResult snd_song_set_track_vol_quiet(s32 arg0, s32 arg1);
AuResult snd_song_set_track_vol_full(s32 arg0, s32 arg1);
void bgm_set_proximity_mix_far(s32 songName, s32 mix);
void bgm_set_proximity_mix_near(s32 songName, s32 mix);
void bgm_set_proximity_mix_full(s32 songName, s32 mix);
void bgm_poll_music_events(u32** arg0, s32* arg1);
void bgm_flush_music_events(void);
void music_event_trigger(s32 arg0, s32 arg1, s32 arg2);
void func_8005610C(void);
*/
void au_register_callback(AuCallback arg0, s32 arg1);
/*
void audio_set_stereo(void);
void audio_set_mono(void);
void func_800561A4(s32 arg0);
void func_800561C4(s32 arg0);
void func_800561E4(s32 arg0);
void func_80056204(void);
void func_80056228(void);
*/

// 31650.c
void au_driver_init(AuSynDriver* driver, ALConfig* config);
void au_driver_release(void);
//Acmd* alAudioFrame(Acmd* cmdList, s32* cmdLen, s16* outBuf, s32 outLen);
void func_80056D34(void);
void func_80056D44(s16 arg0);
s16 func_80056D50(void);
void func_80056D5C(u8 arg0);
void func_80056D78(u8 arg0, u16 arg1);
u16 func_80056DA4(u8 arg0, u16 arg1);
void func_80056DCC(u8 arg0, u8 effectID);
void func_80056E34(u8 arg0, s16 arg1, s16 arg2, s32 arg3);
void func_80056EC0(u8 arg0, s8 arg1);
void au_pvoice_reset_filter(u8 voiceIdx);
void au_pvoice_set_playing(u8 index);
void au_pvoice_set_filter(u8 index, u8 reverbType, Instrument* table, f32 pitchRatio, s16 arg4, u8 pan, u8 reverb, s32 arg7);
void au_pvoice_set_filter_wavetable(u8 voiceIdx, Instrument* table);
void au_pvoice_set_pitch_ratio(u8 voiceIdx, f32 pitchRatio);
void func_8005736C(u8 voiceIdx, s16 volume, s32 arg2, u8 arg3, u8 arg4);
void func_80057548(u8 voiceIdx, u8 arg1, u8 arg2);
void func_800576EC(u8 voiceIdx, s16 arg1, s32 arg2);
void func_80057874(u8 voiceIdx, u8 pan);
void func_800579D8(u8 voiceIdx, u8 dryAmt);
s32 func_80057B64(u8 voiceIdx);
s32 func_80057B8C(u8 voiceIdx);
f32 func_80057BB4(u8 voiceIdx);
u8 func_80057BDC(u8 voiceIdx);
s16 func_80057C04(u8 voiceIdx);
s16 func_80057C2C(u8 voiceIdx);
s32 func_80057C54(u8 voiceIdx);
s32 func_80057D0C(u8 voiceIdx);
void func_80057DC8(s32 arg0);
void func_80057E08(u8 arg0);
void func_80057E5C(u8 arg0);
void func_80057EB0(void);
void func_80057ED0(s16 arg0);
//void alHeapInit(ALHeap* hp, u8* base, s32 len);
//void alCopy(void* src, void* dst, s32 size);
#undef alHeapAlloc
void* alHeapAlloc(ALHeap* heap, s32 arg1, s32 size);

// 33450.c
Acmd* func_80058050(AuPVoice* pvoice, Acmd* cmdBufPos);

// reverb.c
void func_80058E84(AuFX* fx, u8 mode, ALHeap* heap);
void func_80058F88(AlUnkKappa* kappa, ALHeap* heap);
void func_80059008(AlUnkKappa* kappa, s16 arg1, s16 arg2, s16 fc);
void func_8005904C(AuFX* fx, u8 effectType);
Acmd* func_80059310(AuFX* fx, Acmd* cmdBusPos, s16, s16);
s32 au_fx_param_hdl(AuFX* fx, s16 index, s16 paramID, s32 value);

// sfx.c
/*
void sfx_reset_door_sounds(void);
void sfx_clear_sounds(void);
void sfx_clear_env_sounds(s16 playSounds);
void sfx_update_looping_sound_params(void);
void sfx_set_reverb_mode(s32 arg0);
s32 sfx_get_reverb_mode(void);
void sfx_stop_env_sounds(void);
*/
SoundInstance* sfx_get_env_sound_instance(s32 soundID);
/*
void sfx_play_sound_looping(s32 soundId, u8 volume, u8 pan, s16 pitchShift);
void sfx_register_looping_sound_at_position(s32 soundID, s32 flags, f32 x, f32 y, f32 z);
s32 sfx_adjust_env_sound_pos(s32 soundID, s32 sourceFlags, f32 x, f32 y, f32 z);
void func_80149A6C(s32 soundID, s32 keepPlaying);
void sfx_play_sound_with_params(s32 soundID, u8 volume, u8 pan, s16 pitchShift);
void sfx_adjust_env_sound_params(s32 soundID, u8 volume, u8 pan, s16 pitchShift);
void sfx_stop_sound(s32 soundID);
void sfx_play_sound(s32 soundID);
void sfx_play_sound_at_player(s32 soundID, s32 arg1);
void sfx_play_sound_at_npc(s32 soundID, s32 arg1, s32 npcID);
void sfx_play_sound_at_position(s32 soundID, s32 flags, f32 posX, f32 posY, f32 posZ);
void sfx_get_spatialized_sound_params(f32 x, f32 y, f32 z, s16* volume, s16* pan, s32 flags);
void sfx_compute_spatialized_sound_params_0(f32 x, f32 y, f32 z, s16* volume, s16* pan);
void sfx_compute_spatialized_sound_params_1(f32 x, f32 y, f32 z, s16* volume, s16* pan);
void sfx_compute_spatialized_sound_params_full(f32 x, f32 y, f32 z, s16* volume, s16* pan, s32 flags);
*/
