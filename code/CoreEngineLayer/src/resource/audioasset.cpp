#include <resource/audioasset.hpp>
#include <memory>
#include <iostream>

namespace Engine {

bool Music::Load(const FString path) {
    _data = FSharedPointer<Mix_Music>(Mix_LoadMUS(path.c_str()), 
    [](Mix_Music* ptr) {
        if (ptr) {
            Mix_FreeMusic(ptr);
            }
            });
    
    if (_data == nullptr) {
        std::cerr << "Music::Load: Failed to load music file: " << path  << ", SDL_mixer Error: " << SDL_GetError() << '\n';
        return false;
    }
    return true;
} 

void Music::Play(const FReal64 volume) const {
    Mix_PlayMusic(_data.get(), -1);
    Mix_VolumeMusic((int)(volume * 128));
}

void Music::Pause() const {
    Mix_PauseMusic();
}

void Music::resume() const {
    Mix_ResumeMusic();
}

void Music::stop() const {
    Mix_HaltMusic();
}

void Music::SetVolume(const FReal64 volume) const {
    Mix_VolumeMusic((int)(volume * 128));
}

bool Sound::Load(const FString path) {
    _data = FSharedPointer<Mix_Chunk>(Mix_LoadWAV(path.c_str()),
    [](Mix_Chunk* ptr) {
        if (ptr) {
            Mix_FreeChunk(ptr);
            }
            });

    if (_data == nullptr) {
        std::cerr << "Sound::Load: Failed to load sound file: " << path  << ", SDL_mixer Error: " << SDL_GetError() << '\n';
        return false;
    }
    return true;
} 

void Sound::Play(const FInt32 leftVolume, const FInt32 rightVolume, const int loops) const {
    Mix_VolumeChunk(_data.get(), (int)(leftVolume * 128));
    Mix_SetPanning(Mix_PlayChannel(-1, _data.get(), loops), leftVolume, rightVolume);
};

FReal64 AudioManager::_soundVolumeFactor = 1.0;
FReal64 AudioManager::_musicVolumeFactor = 1.0;

bool AudioManager::Initialize() {

    //Initialize SDL_mixer
    int flags = MIX_INIT_MP3;
    int initted = Mix_Init(flags);
    if ((initted & flags) != flags) {
        std::cerr << "AudioManager::Initialize: Failed to init! SDL_mixer Error: " << SDL_GetError() << '\n';
        return false;
    }
    //stereo, 48000 Hz
    SDL_AudioSpec spec = {MIX_DEFAULT_FORMAT, 2, 48000};

    if (Mix_OpenAudio(0, &spec) == 0) {
        std::cerr << "AudioManager::Initialize: SDL_mixer could not initialize! SDL_mixer Error: " << SDL_GetError() << '\n';
        return false;
    }
    Mix_AllocateChannels(32);
    return true;
}

FSharedPointer<const Asset> AudioManager::RequestAsset(EAssetType type, FString path) {
    if (_assetTable.find(path) != _assetTable.end()) {
            return _assetTable[path];
        }

    if (type == EAssetType::Music) {
        auto music = std::make_shared<Music>();
        if (music->Load(path)) {
            _assetTable[path] = music;
            return music;
        }
    } 
    else if (type == EAssetType::Sound) {
        auto sound = std::make_shared<Sound>();
        if (sound->Load(path)) {
            _assetTable[path] = sound;
            return sound;
        }
    }
    else {
        std::cerr << "AudioManager::LoadAsset: Unknown asset type: " << (int)type << '\n';
        return nullptr;
    }
    return nullptr;
}

void AudioManager::StopAllSounds() {
    Mix_HaltChannel(-1);
}

void AudioManager::StopMusic() {
    Mix_HaltMusic();
}

void AudioManager::PauseMusic() {
    Mix_PauseMusic();
}

void AudioManager::ResumeMusic() {
    Mix_ResumeMusic();
}

void AudioComponent::LoadSound(const FString path) {
    auto sound = AudioManager::RequestAsset(EAssetType::Sound, path);
}

void AudioComponent::PlaySound(const FString filepath, FInt32 leftVolume, FInt32 rightVolume, int loops) {
    auto sound = std::dynamic_pointer_cast<const Sound>(AudioManager::RequestAsset(EAssetType::Sound, 
    AssetManager::projectFolder + AssetManager::assetFolder + filepath));
    sound->Play(leftVolume, rightVolume, loops);
}
}