#ifndef AUDIO_H
#define AUDIO_H

#include "include/raylib.h"

typedef enum {
    BGM_MAIN,
    SFX_CURSOR,
    SFX_JUMP,
    SFX_ATTACK,
    SFX_PLAYER_DEAD,
    SFX_WIN,
    SFX_WIN_END
} GAME_SOUND;

void LoadAudio();
void ProcessAudioUpdate();
void UnloadAudio();
void PlayBGM(GAME_SOUND bgm);
void StopBGM();
void PlaySFX(GAME_SOUND sfx);

#endif