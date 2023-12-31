#include "../../Engine/hUGEDriver.h"
#include <stddef.h>

static const unsigned char order_cnt = 2;

static const unsigned char P0[] = {
    DN(Fs3,8,0xC05),
    DN(___,0,0x000),
    DN(Fs3,8,0xC05),
    DN(___,0,0x000),
    DN(As3,8,0xC05),
    DN(___,0,0x000),
    DN(Cs4,8,0xC05),
    DN(___,0,0x000),
    DN(E_4,8,0xC05),
    DN(___,0,0x000),
    DN(E_4,8,0xC05),
    DN(___,0,0x000),
    DN(Ds4,8,0xC05),
    DN(___,0,0x000),
    DN(Cs4,8,0xC05),
    DN(___,0,0x000),
    DN(Fs3,8,0xC05),
    DN(___,0,0x000),
    DN(Fs3,8,0xC05),
    DN(___,0,0x000),
    DN(As3,8,0xC05),
    DN(___,0,0x000),
    DN(Cs4,8,0xC05),
    DN(___,0,0x000),
    DN(Fs3,8,0xC05),
    DN(___,0,0x000),
    DN(Fs3,8,0xC05),
    DN(___,0,0x000),
    DN(E_4,8,0xC05),
    DN(___,0,0x000),
    DN(Ds4,8,0xC05),
    DN(___,0,0x000),
    DN(Cs4,8,0xC05),
    DN(___,0,0x000),
    DN(Cs4,8,0xC05),
    DN(___,0,0x000),
    DN(E_4,8,0xC05),
    DN(___,0,0x000),
    DN(Gs4,8,0xC05),
    DN(___,0,0x000),
    DN(B_4,8,0xC05),
    DN(___,0,0x000),
    DN(B_4,8,0xC05),
    DN(___,0,0x000),
    DN(As4,8,0xC05),
    DN(___,0,0x000),
    DN(Gs4,8,0xC05),
    DN(___,0,0x000),
    DN(Cs4,8,0xC05),
    DN(___,0,0x000),
    DN(Cs4,8,0xC05),
    DN(___,0,0x000),
    DN(E_4,8,0xC05),
    DN(___,0,0x000),
    DN(Gs4,8,0xC05),
    DN(___,0,0x000),
    DN(Cs4,8,0xC05),
    DN(___,0,0x000),
    DN(Gs4,8,0xC05),
    DN(___,0,0x000),
    DN(B_3,8,0xC05),
    DN(___,0,0x000),
    DN(Gs4,8,0xC05),
    DN(___,0,0x000),
};
static const unsigned char P1[] = {
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
};

static const unsigned char* const order1[] = {P0};
static const unsigned char* const order2[] = {P1};
static const unsigned char* const order3[] = {P1};
static const unsigned char* const order4[] = {P1};

static const hUGEDutyInstr_t duty_instruments[] = {
    {8,0,240,0,128},
    {8,64,240,0,128},
    {8,128,240,0,128},
    {8,192,240,0,128},
    {8,0,241,0,128},
    {8,64,241,0,128},
    {8,128,241,0,128},
    {8,192,241,0,128},
    {8,128,240,0,128},
    {8,128,240,0,128},
    {8,128,240,0,128},
    {8,128,240,0,128},
    {8,128,240,0,128},
    {8,128,240,0,128},
    {8,128,240,0,128},
};
static const hUGEWaveInstr_t wave_instruments[] = {
    {0,32,0,0,128},
    {0,32,1,0,128},
    {0,32,2,0,128},
    {0,32,3,0,128},
    {0,32,4,0,128},
    {0,32,5,0,128},
    {0,32,6,0,128},
    {0,32,7,0,128},
    {0,32,8,0,128},
    {0,32,9,0,128},
    {0,32,10,0,128},
    {0,32,11,0,128},
    {0,32,12,0,128},
    {0,32,13,0,128},
    {0,32,14,0,128},
};
static const hUGENoiseInstr_t noise_instruments[] = {
    {240,0,0,0,0},
    {240,0,0,0,0},
    {240,0,0,0,0},
    {240,0,0,0,0},
    {240,0,0,0,0},
    {240,0,0,0,0},
    {240,0,0,0,0},
    {240,0,0,0,0},
    {240,0,0,0,0},
    {240,0,0,0,0},
    {240,0,0,0,0},
    {240,0,0,0,0},
    {240,0,0,0,0},
    {240,0,0,0,0},
    {240,0,0,0,0},
};

static const unsigned char waves[] = {
    0,0,255,255,255,255,255,255,255,255,255,255,255,255,255,255,
    0,0,0,0,255,255,255,255,255,255,255,255,255,255,255,255,
    0,0,0,0,0,0,0,0,255,255,255,255,255,255,255,255,
    0,0,0,0,0,0,0,0,0,0,0,0,255,255,255,255,
    0,1,18,35,52,69,86,103,120,137,154,171,188,205,222,239,
    254,220,186,152,118,84,50,16,18,52,86,120,154,188,222,255,
    122,205,219,117,33,19,104,189,220,151,65,1,71,156,221,184,
    15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,
    254,252,250,248,246,244,242,240,242,244,246,248,250,252,254,255,
    254,221,204,187,170,153,136,119,138,189,241,36,87,138,189,238,
    132,17,97,237,87,71,90,173,206,163,23,121,221,32,3,71,
    184,132,88,35,219,19,210,197,113,219,221,216,183,23,203,50,
    184,168,37,97,231,101,116,190,128,114,44,164,141,141,121,216,
    196,189,233,114,179,107,61,42,60,222,98,162,98,203,9,14,
    88,4,133,43,224,201,153,117,120,36,23,7,20,141,229,187,
    39,138,36,176,1,92,161,166,167,169,64,10,181,130,232,93,
};

const hUGESong_t PreMenuSong = {10, &order_cnt, order1, order2, order3,order4, duty_instruments, wave_instruments, noise_instruments, NULL, waves};
