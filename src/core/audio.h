#pragma once

#define AUDIO_EFFECT_CHUNK_SIZE 1024

typedef struct {
    const char* path;
    void* platform_audio_effect;
} AudioEffect;

AudioEffect load_audio_effect(const char* path);
void unload_audio_effect(AudioEffect* audio_effect);
void play_audio_effect(AudioEffect* audio_effect);
