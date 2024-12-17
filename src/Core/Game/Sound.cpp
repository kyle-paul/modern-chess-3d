#include "Core/Game/Sound.h"
#include "Core/Debug/Logging.h"
#include <fstream>
#include <thread>
#include <chrono>
#include <stdexcept>

Sound::Sound()
{
}

Sound::~Sound()
{
    if (context) {
        alcDestroyContext(context);
    }
    if (device) {
        alcCloseDevice(device);
    }
}

void Sound::Init()
{
    // Open the default OpenAL device
    device = alcOpenDevice(NULL);
    if (!device) {
        ERROR("Failed to open OpenAL device.");
        return;
    }

    // Create and activate an OpenAL context
    context = alcCreateContext(device, NULL);
    if (!context || !alcMakeContextCurrent(context)) {
        ERROR("Failed to create or activate OpenAL context.");
        alcCloseDevice(device);
        device = nullptr;
        return;
    }

    INFO("OpenAL initialized successfully!");
}

std::vector<char> Sound::LoadWav(const std::string &filename, ALenum &format, ALsizei &freq)
{
    std::ifstream file(filename, std::ios::binary);
    if (!file) {
        throw std::runtime_error("Failed to open WAV file: " + filename);
    }

    // Read WAV header (simplified for PCM WAV files only)
    char header[44];
    file.read(header, 44);
    if (std::strncmp(header, "RIFF", 4) || std::strncmp(header + 8, "WAVE", 4)) {
        throw std::runtime_error("Invalid WAV file: " + filename);
    }

    // Determine format
    short audioFormat = *reinterpret_cast<short*>(header + 20);
    short numChannels = *reinterpret_cast<short*>(header + 22);
    int sampleRate = *reinterpret_cast<int*>(header + 24);
    short bitsPerSample = *reinterpret_cast<short*>(header + 34);

    if (audioFormat != 1) { // PCM format
        throw std::runtime_error("Unsupported WAV format (must be PCM): " + filename);
    }

    if (numChannels == 1 && bitsPerSample == 16) {
        format = AL_FORMAT_MONO16;
    } else if (numChannels == 2 && bitsPerSample == 16) {
        format = AL_FORMAT_STEREO16;
    } else {
        throw std::runtime_error("Unsupported WAV channels or bit depth in: " + filename);
    }

    freq = sampleRate;

    // Read audio data
    std::vector<char> data(std::istreambuf_iterator<char>(file), {});
    return data;
}

void Sound::Play(const std::string &filename)
{
    ALenum format;
    ALsizei freq;

    try 
    {
        auto data = LoadWav(filename, format, freq);

        // Create buffer and source
        ALuint buffer, source;
        alGenBuffers(1, &buffer);
        alBufferData(buffer, format, data.data(), data.size(), freq);

        alGenSources(1, &source);
        alSourcei(source, AL_BUFFER, buffer);
        alSourcePlay(source);

        // Wait until the audio finishes playing
        ALint state;
        do {
            alGetSourcei(source, AL_SOURCE_STATE, &state);
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        } while (state == AL_PLAYING);

        // Clean up
        alDeleteSources(1, &source);
        alDeleteBuffers(1, &buffer);
    } 
    catch (const std::exception &e) 
    {
        ERROR(std::string("Error while playing sound: ") + e.what());
    }
}

void Sound::Pause()
{

}

void Sound::Stop()
{
    
}
