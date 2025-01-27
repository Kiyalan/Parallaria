#ifndef ENGINE_AUDIO_INCLUDED
#define ENGINE_AUDIO_INCLUDED

#include <unordered_map>
#include <memory>
#include <resource/asset.hpp>
#include <resource/assetmanager.hpp>
#include <GLFW/glfw3.h>
#include <SDL3/SDL.h>
#include <SDL3_mixer/SDL3_mixer.h>
#include <env.hpp>

namespace Engine {

class AudioAsset : public Asset {
};

class Music : public AudioAsset {
public:
    bool Load(const FString) override;
    void Unload() override {};
    void Play(const FReal64 volume) const;
    void Pause() const;
    void resume() const;
    void stop() const;
    void SetVolume(const FReal64 volume) const;

private:
    FSharedPointer<Mix_Music> _data;
};

class Sound : public AudioAsset {
public:
    bool Load(const FString) override;
    void Unload() override {};
    void Play(const FInt32 leftVolume = 255, const FInt32 rightVolume = 255, const int loops = 0) const ;

private:
    FSharedPointer<Mix_Chunk> _data;
};


class AudioManager : public AssetManager {
public:
    static bool Initialize();
    static FSharedPointer<const Asset> RequestAsset(EAssetType, FString);

    void StopAllSounds();
    void StopMusic();
    void PauseMusic();
    void ResumeMusic();

private:
    static FReal64 _soundVolumeFactor;
    static FReal64 _musicVolumeFactor;
};

class AudioComponent {
public:

    void LoadSound(const FString filepath);
    void PlaySound(const FString filepath, FInt32 leftVolume = 255, FInt32 rightVolume = 255, int loops = 0);
};

}

#endif