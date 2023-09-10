#include <gb/gb.h>

#include "cbtfx.h"
#include "common.h"
#include "enums.h"
#include "hUGEDriver.h"

#include "../Assets/Sfx/outSFX_00.h"
#include "../Assets/Sfx/outSFX_01.h"
#include "../Assets/Sfx/outSFX_02.h"
#include "../Assets/Sfx/outSFX_03.h"
#include "../Assets/Sfx/outSFX_04.h"
#include "../Assets/Sfx/outSFX_05.h"
#include "../Assets/Sfx/outSFX_06.h"
#include "../Assets/Sfx/outSFX_07.h"
#include "../Assets/Sfx/outSFX_08.h"
#include "../Assets/Sfx/outSFX_09.h"
#include "../Assets/Sfx/outSFX_0A.h"
#include "../Assets/Sfx/outSFX_0B.h"

extern const hUGESong_t Level01Song;
extern const hUGESong_t Level02Song;
extern const hUGESong_t Level03Song;
extern const hUGESong_t YouDiedSong;
extern const hUGESong_t WinSong;
extern const hUGESong_t CGSceneSong;
extern const hUGESong_t IntroSong;
extern const hUGESong_t MainMenuSong;
extern const hUGESong_t PreMenuSong;

const unsigned char * SFX_list[] = { &SFX_00[0], &SFX_01[0], &SFX_02[0], &SFX_03[0], &SFX_04[0], &SFX_05[0], &SFX_06[0], &SFX_07[0], &SFX_08[0], &SFX_09[0], &SFX_0A[0], &SFX_0B[0] };

extern UINT8 curSongBank;
static UINT8 nextBank;

void songPlayerVblFn()
{
    nextBank = CURRENT_BANK;
    SWITCH_ROM(curSongBank);
    hUGE_dosound();
	CBTFX_update();
    SWITCH_ROM(nextBank);
}

void playSfx(SFX sfxName)
{
	CBTFX_init(SFX_list[sfxName]);
}

void playSong(const hUGESong_t * song)
{
    NR12_REG = NR22_REG = NR32_REG = NR42_REG = 0;
    remove_VBL(songPlayerVblFn);
    add_VBL(songPlayerVblFn);

    curSongBank = CURRENT_BANK;
    
    hUGE_init(song);
}

void playOutsideSong(SONGS songName)
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
            curSongBank = 5U;
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
        case SONG_PREMENU:
            nextBank = CURRENT_BANK;
            curSongBank = 5U;
            SWITCH_ROM(curSongBank);
            playSong(&PreMenuSong);
            SWITCH_ROM(nextBank);
            break;
    }
}

void stopSong()
{
    NR12_REG = NR22_REG = NR32_REG = NR42_REG = 0;
    remove_VBL(songPlayerVblFn);
}
