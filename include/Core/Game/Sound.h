#pragma once

#include <AL/al.h>
#include <AL/alc.h>
#include <string>
#include <vector>

class Sound
{
public:
    Sound();
    ~Sound();

    void Init();
    void Play(const std::string &filename);
    void Pause();
    void Stop();

private:
    ALCdevice *device = nullptr;
    ALCcontext *context = nullptr;

    std::vector<char> LoadWav(const std::string &filename, ALenum &format, ALsizei &freq);
};
