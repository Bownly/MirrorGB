#include <gb/gb.h>
#include "hUGEDriver.h"

#include "common.h"
#include "enums.h"

extern const hUGESong_t level01;

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
    
    // // All this just to increase the tempo. Is there a better way to do this? Probably.
    // hUGESong_t modifiedSong;
    // modifiedSong.tempo = song->tempo - mgSpeed;
    // modifiedSong.order_cnt = song->order_cnt;
    // modifiedSong.order1 = song->order1;
    // modifiedSong.order2 = song->order2;
    // modifiedSong.order3 = song->order3;
    // modifiedSong.order4 = song->order4;
    // modifiedSong.duty_instruments = song->duty_instruments;
    // modifiedSong.wave_instruments = song->wave_instruments;
    // modifiedSong.noise_instruments = song->noise_instruments;
    // modifiedSong.routines = song->routines;
    // modifiedSong.waves = song->waves;

    // hUGE_init(&modifiedSong);
    hUGE_init(song);
}

void playOutsideSong(UINT8 songName)
{
    switch (songName)
    {
        default:
        case SONG_HOUSE:
            nextBank = CURRENT_BANK;
            curSongBank = 6U;
            SWITCH_ROM(curSongBank);
            playSong(&level01);
            SWITCH_ROM(nextBank);
            break;
    }
}

// void stopSong()
// {
//     NR12_REG = NR22_REG = NR32_REG = NR42_REG = 0;
//     remove_VBL(songPlayerVblFn);
// }
