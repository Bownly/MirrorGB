#include <gb/gb.h>
#include <stdio.h>
#include <string.h>

#include "../Assets/Illustrations/Intro1Illustration1.h"
#include "../Assets/Illustrations/Intro1Illustration2.h"
#include "../Assets/Illustrations/Intro2Illustration1.h"
#include "../Assets/Illustrations/Intro2Illustration2.h"
#include "../Assets/Illustrations/Intro3Illustration.h"
#include "../Assets/Illustrations/Intro4Illustration.h"
#include "../Assets/Illustrations/TutorialIllustration1.h"
#include "../Assets/Illustrations/TutorialIllustration2.h"

extern UINT8 metaTiles[256U][4U];
static UINT8 nextBank;

void loadIllustrationData(UINT8 illustrationId)
{
    nextBank = CURRENT_BANK;

    switch (illustrationId)
    {
        case 0U:
            SWITCH_ROM(7U);
            set_bkg_data(0U, Intro1Illustration1_TILE_COUNT, Intro1Illustration1_tiles);
            set_bkg_tiles(0U, 0U, 20U, 9U, Intro1Illustration1_map);
            set_bkg_data(Intro1Illustration1_TILE_COUNT, Intro1Illustration2_TILE_COUNT, Intro1Illustration2_tiles);
            set_win_tiles(0U, 0U, 20U, 9U, Intro1Illustration2_map);
            break;
        case 1U:
            SWITCH_ROM(8U);
            set_bkg_data(0U, Intro2Illustration1_TILE_COUNT, Intro2Illustration1_tiles);
            set_bkg_tiles(0U, 7U, 20U, 3U, Intro2Illustration1_map);
            set_bkg_data(Intro2Illustration1_TILE_COUNT, Intro2Illustration2_TILE_COUNT, Intro2Illustration2_tiles);
            set_win_tiles(0U, 0U, 20U, 18U, Intro2Illustration2_map);
            break;
        case 2U:
            SWITCH_ROM(8U);
            set_bkg_data(0U, Intro3Illustration_TILE_COUNT, Intro3Illustration_tiles);
            set_bkg_tiles(0U, 0U, 20U, 18U, Intro3Illustration_map);
            break;
        case 3U:
            SWITCH_ROM(8U);
            set_bkg_data(0U, Intro4Illustration_TILE_COUNT, Intro4Illustration_tiles);
            set_bkg_tiles(0U, 0U, 20U, 18U, Intro4Illustration_map);
            break;
        case 4U:
            SWITCH_ROM(8U);
            set_bkg_data(0U, TutorialIllustration1_TILE_COUNT, TutorialIllustration1_tiles);
            set_bkg_tiles(0U, 9U, 20U, 9U, TutorialIllustration1_map);
            set_bkg_data(TutorialIllustration1_TILE_COUNT, TutorialIllustration2_TILE_COUNT, TutorialIllustration2_tiles);
            set_win_tiles(0U, 0U, 20U, 18U, TutorialIllustration2_map);
            break;
    }
    SWITCH_ROM(nextBank);
}
