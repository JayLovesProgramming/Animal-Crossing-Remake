#include "Audio.h"

#include <iostream>
#include <string>
#include <cassert>
#include "Utils/ConsoleOut.h"

using std::cout, std::endl, std::string, std::to_string;

void AudioManager::InitializeAudioDevice()
{
    InitAudioDevice();
    PlayMusicStage1();
    cout << "[AUDIO]: Initalized Audio Device" << endl;
};

void AudioManager::PlayMusicStage1()
{
    if (!MusicEnabled)
        return;

    if (mainMusicFile.frameCount == 0)
        UnloadSound(mainMusicFile);

    mainMusicFile = LoadSound("C:/Users/jayxw/Desktop/AnimalCrossing/src/Assets/Sounds/main.wav");
    assert(mainMusicFile.frameCount > 0);
    SetSoundVolume(mainMusicFile, 0.2f);

    PlaySound(mainMusicFile);

    cout << "[AUDIO]: Playing Main Ambient Music" << endl;
};

void AudioManager::ManageMainMusic()
{
    // If "MainMusic" is not playing, restart it
    if (!IsSoundPlaying(mainMusicFile) && MusicEnabled)
    {
        PlayMusicStage1();
        cout << "[AUDIO]: Restarting Main Music" << endl;
    }
}

void AudioManager::PlayACoolSoundThing(const char *soundEvent)
{
    const char *soundFile = nullptr;

    if (strcmp(soundEvent, "JumpSound") == 0)
    {
        soundFile = ("C:/Users/jayxw/Desktop/AnimalCrossing/src/Assets/Sounds/jump2.wav");
    }
    else if (strcmp(soundEvent, "ShakeTree") == 0)
    {
        soundFile = "C:/Users/jayxw/Desktop/AnimalCrossing/src/Assets/Sounds/buttonfx.wav"; // TODO: Make a relative path
        cout << "[AUDIO]: Playing Shake Tree sound" << endl;
        // Do the shake tree animation here, make the apples drop off the tree etc, etc
    }
    else
    {
        cout << "[AUDIO]: Unrecognized sound event: " << soundEvent << endl;
        return;
    }

    // Load the sound
    // if (usefulSound.frameCount == 0)
    // {
    //     UnloadSound(usefulSound);
    // };

    usefulSound = LoadSound(soundFile);
    assert(usefulSound.frameCount > 0);
    SetSoundVolume(usefulSound, 0.3f);

    bool isSoundReady = IsSoundReady(usefulSound);
    assert(IsSoundReady(usefulSound));

    // Play the loaded sound
    PlaySound(usefulSound);
}

void AudioManager::UnloadAudio()
{
    UnloadSound(mainMusicFile);
    UnloadSound(usefulSound);
    CloseAudioDevice();
    cout << unloadString << "Audio" << endl;
};
