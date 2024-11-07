#pragma once

class AudioManager
{
public:
    inline static Sound usefulSound;
    inline static Sound mainMusicFile;

    inline static void InitializeAudioDevice();

    inline static void ManageMainMusic();

    inline static void PlayACoolSoundThing(const char *soundEvent);

    inline static void UnloadAudio();

    inline static void PlayMusicStage1();

};
