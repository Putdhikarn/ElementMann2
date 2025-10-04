#include "audio.h"

Sound sfxCursor;
Sound sfxJump;
Sound sfxAttack;
Sound sfxPlayerDead;

Music bgmStream;

void LoadAudio(){
    sfxCursor = LoadSound("data/audio/sfx_cursor.ogg");
    sfxJump = LoadSound("data/audio/sfx_jump.ogg");
    sfxAttack = LoadSound("data/audio/sfx_attack.ogg");
    sfxPlayerDead = LoadSound("data/audio/sfx_player_dead.ogg");

    bgmStream = LoadMusicStream("data/audio/bgm_main.ogg");
}

void ProcessAudioUpdate(){
    UpdateMusicStream(bgmStream);
}

void UnloadAudio(){
    UnloadSound(sfxCursor);
    UnloadSound(sfxJump);
    UnloadSound(sfxAttack);
    UnloadSound(sfxPlayerDead);
    UnloadMusicStream(bgmStream);
}

void PlayBGM(GAME_SOUND bgm){
    switch (bgm){
        case BGM_MAIN:
            StopBGM();
            bgmStream = LoadMusicStream("data/audio/bgm_main.ogg");
            PlayMusicStream(bgmStream);
            break;
    }
}

void StopBGM(){
    StopMusicStream(bgmStream);
}

void PlaySFX(GAME_SOUND sfx){
    switch (sfx){
        case SFX_CURSOR:
            PlaySound(sfxCursor);
            break;
        case SFX_JUMP:
            PlaySound(sfxJump);
            break;
        case SFX_ATTACK:
            PlaySound(sfxAttack);
            break;
        case SFX_PLAYER_DEAD:
            PlaySound(sfxPlayerDead);
            break;
    }
    
}