#include <gb/gb.h>
#include "hUGEDriver.h"

#include "common.h"
#include "enums.h"

extern const hUGESong_t Level01Song;
extern const hUGESong_t Level02Song;
extern const hUGESong_t Level03Song;
extern const hUGESong_t YouDiedSong;
extern const hUGESong_t WinSong;
extern const hUGESong_t CGSceneSong;
extern const hUGESong_t IntroSong;
extern const hUGESong_t MainMenuSong;

extern UINT8 curSongBank;
static UINT8 nextBank;

void songPlayerVblFn()
{
    nextBank = CURRENT_BANK;
    SWITCH_ROM(curSongBank);
    hUGE_dosound();
    SWITCH_ROM(nextBank);
}

void playSong(const hUGESong_t * song)
{
    NR12_REG = NR22_REG = NR32_REG = NR42_REG = 0;
    remove_VBL(songPlayerVblFn);
    add_VBL(songPlayerVblFn);

    curSongBank = CURRENT_BANK;
    
    hUGE_init(song);
}

void playOutsideSong(UINT8 songName)
{
    switch (songName)
    {
        default:
        case SONG_LEVEL01:
            nextBank = CURRENT_BANK;
            curSongBank = 6U;
            SWITCH_ROM(curSongBank);
            playSong(&Level01Song);
            SWITCH_ROM(nextBank);
            break;
        case SONG_LEVEL02:
            nextBank = CURRENT_BANK;
            curSongBank = 6U;
            SWITCH_ROM(curSongBank);
            playSong(&Level02Song);
            SWITCH_ROM(nextBank);
            break;        
        case SONG_LEVEL03:
            nextBank = CURRENT_BANK;
            curSongBank = 6U;
            SWITCH_ROM(curSongBank);
            playSong(&Level03Song);
            SWITCH_ROM(nextBank);
            break;
        case SONG_YOUDIED:
            nextBank = CURRENT_BANK;
            curSongBank = 6U;
            SWITCH_ROM(curSongBank);
            playSong(&YouDiedSong);
            SWITCH_ROM(nextBank);
            break;
        case SONG_WIN:
            nextBank = CURRENT_BANK;
            curSongBank = 6U;
            SWITCH_ROM(curSongBank);
            playSong(&WinSong);
            SWITCH_ROM(nextBank);
            break;
        case SONG_CGSCENE:
            nextBank = CURRENT_BANK;
            curSongBank = 7U;
            SWITCH_ROM(curSongBank);
            playSong(&CGSceneSong);
            SWITCH_ROM(nextBank);
            break;
        case SONG_INTRO:
            nextBank = CURRENT_BANK;
            curSongBank = 7U;
            SWITCH_ROM(curSongBank);
            playSong(&IntroSong);
            SWITCH_ROM(nextBank);
            break;        
        case SONG_MAINMENU:
            nextBank = CURRENT_BANK;
            curSongBank = 7U;
            SWITCH_ROM(curSongBank);
            playSong(&MainMenuSong);
            SWITCH_ROM(nextBank);
            break;
    }
}

void stopSong()
{
    NR12_REG = NR22_REG = NR32_REG = NR42_REG = 0;
    remove_VBL(songPlayerVblFn);
}
