#include "audio.h"

Sound sfxCursor;
Sound sfxJump;
Sound sfxAttack;
Sound sfxPlayerDead;

Sound sfxWin;
Sound sfxWinEnd;

Music bgmStream;

void LoadAudio(){
    sfxCursor = LoadSound("data/audio/sfx_cursor.ogg");
    sfxJump = LoadSound("data/audio/sfx_jump.ogg");
    sfxAttack = LoadSound("data/audio/sfx_attack.ogg");
    sfxPlayerDead = LoadSound("data/audio/sfx_player_dead.ogg");

    sfxWin = LoadSound("data/audio/sfx_win.ogg");
    sfxWinEnd = LoadSound("data/audio/sfx_win_end.ogg");

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
    UnloadSound(sfxWin);
    UnloadSound(sfxWinEnd);
    UnloadMusicStream(bgmStream);
}

void PlayBGM(GAME_SOUND bgm){
    switch (bgm){
        case BGM_MAIN:
            StopBGM();
            bgmStream = LoadMusicStream("data/audio/bgm_main.ogg");
            PlayMusicStream(bgmStream);
            break;
        case BGM_PASSWORD:
            StopBGM();
            bgmStream = LoadMusicStream("data/audio/bgm_password.ogg");
            PlayMusicStream(bgmStream);
            break;
        case BGM_SELECT:
            StopBGM();
            bgmStream = LoadMusicStream("data/audio/bgm_select.ogg");
            PlayMusicStream(bgmStream);
            break;
        case BGM_BOSS1:
            StopBGM();
            bgmStream = LoadMusicStream("data/audio/bgm_boss.ogg");
            PlayMusicStream(bgmStream);
            break;
        case BGM_BOSS2:
            StopBGM();
            bgmStream = LoadMusicStream("data/audio/bgm_boss.ogg");
            PlayMusicStream(bgmStream);
            break;
        case BGM_BOSS3:
            StopBGM();
            bgmStream = LoadMusicStream("data/audio/bgm_boss.ogg");
            PlayMusicStream(bgmStream);
            break;
        case BGM_BOSS4:
            StopBGM();
            bgmStream = LoadMusicStream("data/audio/bgm_boss4.ogg");
            PlayMusicStream(bgmStream);
            break;
        case BGM_WIN:
            StopBGM();
            bgmStream = LoadMusicStream("data/audio/bgm_win.ogg");
            PlayMusicStream(bgmStream);
            break;
        case BGM_END:
            StopBGM();
            bgmStream = LoadMusicStream("data/audio/bgm_end.ogg");
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
            if (!IsSoundPlaying(sfxJump)){
                PlaySound(sfxJump);
            }
            break;
        case SFX_ATTACK:
            PlaySound(sfxAttack);
            break;
        case SFX_PLAYER_DEAD:
            PlaySound(sfxPlayerDead);
            break;
        case SFX_WIN:
            PlaySound(sfxWin);
            break;
        case SFX_WIN_END:
            PlaySound(sfxWinEnd);
            break;
    }
    
}