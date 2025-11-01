#ifndef AUDIO_H
#define AUDIO_H

#include "include/raylib.h"

typedef enum {
    BGM_MAIN,
    BGM_PASSWORD,
    BGM_SELECT,
    BGM_BOSS1,
    BGM_BOSS2,
    BGM_BOSS3,
    BGM_BOSS4,
    BGM_WIN,
    BGM_END,
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