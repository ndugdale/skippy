#include "core/audio.h"

#include <SDL2/SDL_mixer.h>

#include "core/log.h"

AudioEffect load_audio_effect(const char* path) {
    Mix_Chunk* platform_audio_effect = Mix_LoadWAV(path);
    ASSERT(
        platform_audio_effect != NULL, "Failed to load Mix_Chunk from path %s",
        path
    );

    AudioEffect audio_effect = {
        .path = path,
        .platform_audio_effect = platform_audio_effect,
    };

    return audio_effect;
}

void unload_audio_effect(AudioEffect* audio_effect) {
    Mix_FreeChunk(audio_effect->platform_audio_effect);
}

void play_audio_effect(AudioEffect* audio_effect) {
    ASSERT(
        Mix_PlayChannel(-1, audio_effect->platform_audio_effect, 0) != -1,
        "Failed to play audio effect from path %s", audio_effect->path
    );
}
