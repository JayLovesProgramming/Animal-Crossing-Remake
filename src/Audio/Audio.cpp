#include "Audio.h"

#include <iostream>

using std::cout, std::endl;

void AudioManager::InitializeAudioDevice()
{
    InitAudioDevice();
    cout << "[AUDIO]: Initalized Audio Device" << endl;
};

void AudioManager::LoadButtonSound()
{
};
