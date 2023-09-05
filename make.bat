del o\*.o
del o\*.lst
del o\*.asm
del o\*.sym

C:\gbdk-4.2.0\bin\lcc -Wa-l -Wf-bo6 -c -o o/Level01Song.o Assets/Music/Level01Song.c
C:\gbdk-4.2.0\bin\lcc -Wa-l -Wf-bo6 -c -o o/Level02Song.o Assets/Music/Level02Song.c
C:\gbdk-4.2.0\bin\lcc -Wa-l -Wf-bo6 -c -o o/Level03Song.o Assets/Music/Level03Song.c
C:\gbdk-4.2.0\bin\lcc -Wa-l -Wf-bo6 -c -o o/YouDiedSong.o Assets/Music/YouDiedSong.c
C:\gbdk-4.2.0\bin\lcc -Wa-l -Wf-bo6 -c -o o/WinSong.o Assets/Music/WinSong.c
C:\gbdk-4.2.0\bin\lcc -Wa-l -Wf-bo7 -c -o o/CGSceneSong.o Assets/Music/CGSceneSong.c
C:\gbdk-4.2.0\bin\lcc -Wa-l -Wf-bo7 -c -o o/IntroSong.o Assets/Music/IntroSong.c
C:\gbdk-4.2.0\bin\lcc -Wa-l -Wf-bo7 -c -o o/MainMenuSong.o Assets/Music/MainMenuSong.c

C:\gbdk-4.2.0\bin\png2asset Assets/Illustrations/Intro1Illustration1.png -b 7 -map -tile_origin 0 -noflip
C:\gbdk-4.2.0\bin\png2asset Assets/Illustrations/Intro1Illustration2.png -b 7 -map -tile_origin 67 -noflip
C:\gbdk-4.2.0\bin\png2asset Assets/Illustrations/Intro2Illustration1.png -b 8 -map -tile_origin 0 -noflip
C:\gbdk-4.2.0\bin\png2asset Assets/Illustrations/Intro2Illustration2.png -b 8 -map -tile_origin 32 -noflip
C:\gbdk-4.2.0\bin\png2asset Assets/Illustrations/Intro3Illustration.png -b 8 -map -tile_origin 0 -noflip
C:\gbdk-4.2.0\bin\png2asset Assets/Illustrations/Intro4Illustration.png -b 8 -map -tile_origin 0 -noflip
C:\gbdk-4.2.0\bin\png2asset Assets/Illustrations/TutorialIllustration.png -b 8 -map -tile_origin 0 -noflip
C:\gbdk-4.2.0\bin\png2asset Assets/Illustrations/TitleScreenIllustration.png -spr8x8 -sw 8 -sh 8 -b 1 -map -tile_origin 0 -noflip
C:\gbdk-4.2.0\bin\png2asset Assets/Illustrations/GameOverIllustration.png -spr8x8 -sw 8 -sh 8 -b 1 -map -tile_origin 0 -noflip
C:\gbdk-4.2.0\bin\png2asset Assets/Illustrations/BeatGameIllustration.png -spr8x8 -sw 8 -sh 8 -b 1 -map -tile_origin 64 -noflip
C:\gbdk-4.2.0\bin\png2asset Assets/Illustrations/BeatLevelIllustration.png -spr8x8 -sw 8 -sh 8 -b 1 -map -tile_origin 64 -noflip

C:\gbdk-4.2.0\bin\png2asset Assets/Sprites/PressSprite.png -pw 0 -ph 0 -b 1 -sw 40 -sh 16 -spr8x8
C:\gbdk-4.2.0\bin\png2asset Assets/Sprites/StartSprite.png -pw 0 -ph 0 -b 1 -sw 40 -sh 16 -spr8x8 -tile_origin 10
C:\gbdk-4.2.0\bin\png2asset Assets/Sprites/HUDTeeth.png -pw 0 -ph 0 -b 2 -sw 32 -sh 16 -keep_duplicate_tiles -noflip
C:\gbdk-4.2.0\bin\png2asset Assets/Sprites/MC.png -pw 0 -ph 0 -b 2 -sw 16 -sh 16 -spr8x8
C:\gbdk-4.2.0\bin\png2asset Assets/Sprites/NPCBald.png -pw 0 -ph 0 -b 5 -sw 16 -sh 16 -spr8x8
C:\gbdk-4.2.0\bin\png2asset Assets/Sprites/NPCBoy.png -pw 0 -ph 0 -b 5 -sw 16 -sh 16 -spr8x8
C:\gbdk-4.2.0\bin\png2asset Assets/Sprites/NPCgirl.png -pw 0 -ph 0 -b 5 -sw 16 -sh 16 -spr8x8
C:\gbdk-4.2.0\bin\png2asset Assets/Sprites/NPCGuy.png -pw 0 -ph 0 -b 5 -sw 16 -sh 16 -spr8x8
C:\gbdk-4.2.0\bin\png2asset Assets/Sprites/NPCNun.png -pw 0 -ph 0 -b 5 -sw 16 -sh 16 -spr8x8
C:\gbdk-4.2.0\bin\png2asset Assets/Sprites/NPCScientist.png -pw 0 -ph 0 -b 5 -sw 16 -sh 16 -spr8x8

C:\gbdk-4.2.0\bin\lcc -Wa-l -Wf-bo3 -c -o o/TutorialRMap.o Assets/Maps/Levels/TutorialRMap.c
C:\gbdk-4.2.0\bin\lcc -Wa-l -Wf-bo3 -c -o o/TutorialMMap.o Assets/Maps/Levels/TutorialMMap.c
C:\gbdk-4.2.0\bin\lcc -Wa-l -Wf-bo3 -c -o o/HouseRMap.o Assets/Maps/Levels/HouseRMap.c
C:\gbdk-4.2.0\bin\lcc -Wa-l -Wf-bo3 -c -o o/HouseMMap.o Assets/Maps/Levels/HouseMMap.c

C:\gbdk-4.2.0\bin\lcc -Wa-l -Wf-bo2 -c -o o/BloodstainTiles.o Assets/Tiles/BloodstainTiles.c
C:\gbdk-4.2.0\bin\lcc -Wa-l -Wf-bo2 -c -o o/ExclamationTiles.o Assets/Tiles/ExclamationTiles.c
C:\gbdk-4.2.0\bin\lcc -Wa-l -Wf-bo2 -c -o o/HUDTiles.o Assets/Tiles/HUD.c
C:\gbdk-4.2.0\bin\lcc -Wa-l -Wf-bo2 -c -o o/fontTiles.o Assets/Tiles/fontTiles.c
C:\gbdk-4.2.0\bin\lcc -Wa-l -Wf-bo4 -c -o o/HouseTiles.o Assets/Tiles/HouseTiles.c
C:\gbdk-4.2.0\bin\lcc -Wa-l -Wf-bo4 -c -o o/HouseMTiles.o Assets/Tiles/HouseMTiles.c
C:\gbdk-4.2.0\bin\lcc -Wa-l -Wf-bo4 -c -o o/LabRTiles.o Assets/Tiles/LabRTiles.c
C:\gbdk-4.2.0\bin\lcc -Wa-l -Wf-bo4 -c -o o/LabMTiles.o Assets/Tiles/LabMTiles.c

C:\gbdk-4.2.0\bin\lcc -Wa-l -c -o o/SFX_00.o Assets/Sfx/SFX_00.c
C:\gbdk-4.2.0\bin\lcc -Wa-l -c -o o/SFX_01.o Assets/Sfx/SFX_01.c
C:\gbdk-4.2.0\bin\lcc -Wa-l -c -o o/SFX_02.o Assets/Sfx/SFX_02.c
C:\gbdk-4.2.0\bin\lcc -Wa-l -c -o o/SFX_03.o Assets/Sfx/SFX_03.c
C:\gbdk-4.2.0\bin\lcc -Wa-l -c -o o/SFX_04.o Assets/Sfx/SFX_04.c
C:\gbdk-4.2.0\bin\lcc -Wa-l -c -o o/SFX_05.o Assets/Sfx/SFX_05.c
C:\gbdk-4.2.0\bin\lcc -Wa-l -c -o o/SFX_06.o Assets/Sfx/SFX_06.c
C:\gbdk-4.2.0\bin\lcc -Wa-l -c -o o/SFX_07.o Assets/Sfx/SFX_07.c
C:\gbdk-4.2.0\bin\lcc -Wa-l -c -o o/SFX_08.o Assets/Sfx/SFX_08.c
C:\gbdk-4.2.0\bin\lcc -Wa-l -c -o o/SFX_09.o Assets/Sfx/SFX_09.c

C:\gbdk-4.2.0\bin\lcc -Wa-l -Wf-bo3 -c -o o/RoomData.o Database/RoomData.c
C:\gbdk-4.2.0\bin\lcc -Wa-l -Wf-bo4 -c -o o/LevelData.o Database/LevelData.c
C:\gbdk-4.2.0\bin\lcc -Wa-l -Wf-bo4 -c -o o/MetatilesData.o Database/MetatilesData.c
C:\gbdk-4.2.0\bin\lcc -Wa-l -Wf-bo4 -c -o o/NPCData.o Database/NPCData.c
C:\gbdk-4.2.0\bin\lcc -Wa-l -Wf-bo4 -c -o o/RoutineData.o Database/RoutineData.c

/gbdk-4.2.0/bin/lcc -Wa-l -Wf-bo1 -c -o o/BeatGameState.o States/BeatGameState.c
/gbdk-4.2.0/bin/lcc -Wa-l -Wf-bo1 -c -o o/BeatLevelState.o States/BeatLevelState.c
/gbdk-4.2.0/bin/lcc -Wa-l -Wf-bo1 -c -o o/GameOverState.o States/GameOverState.c
/gbdk-4.2.0/bin/lcc -Wa-l -Wf-bo1 -c -o o/TitleState.o States/TitleState.c
/gbdk-4.2.0/bin/lcc -Wa-l -Wf-bo2 -c -o o/LevelState.o States/LevelState.c
/gbdk-4.2.0/bin/lcc -Wa-l -Wf-bo7 -c -o o/IntroState.o States/IntroState.c

C:\gbdk-4.2.0\bin\lcc -Wa-l -c -o o/cbtfx.o Engine/cbtfx.c
C:\gbdk-4.2.0\bin\lcc -Wa-l -c -o o/common.o Engine/common.c
C:\gbdk-4.2.0\bin\lcc -Wa-l -c -o o/fade.o Engine/fade.c
C:\gbdk-4.2.0\bin\lcc -Wa-l -c -o o/IShareLevelData.o Engine/IShareLevelData.c
C:\gbdk-4.2.0\bin\lcc -Wa-l -c -o o/ILoadIllustrationData.o Engine/ILoadIllustrationData.c
C:\gbdk-4.2.0\bin\lcc -Wa-l -c -o o/ILoadMapTileData.o Engine/ILoadMapTileData.c
C:\gbdk-4.2.0\bin\lcc -Wa-l -c -o o/IShareMapData.o Engine/IShareMapData.c
C:\gbdk-4.2.0\bin\lcc -Wa-l -c -o o/IShareNPCData.o Engine/IShareNPCData.c
C:\gbdk-4.2.0\bin\lcc -Wa-l -c -o o/IShareNPCGraphics.o Engine/IShareNPCGraphics.c
C:\gbdk-4.2.0\bin\lcc -Wa-l -c -o o/IShareRoutineData.o Engine/IShareRoutineData.c
C:\gbdk-4.2.0\bin\lcc -Wa-l -c -o o/songPlayer.o Engine/songPlayer.c

C:\gbdk-4.2.0\bin\lcc -Wa-l -c -o o/main.o main.c
C:\gbdk-4.2.0\bin\lcc -Wl-yt3 -Wl-yoA -Wl-ya4 -o Banished.gb o/*.o Assets/Sprites/*.c Assets/Illustrations/*.c Engine/hUGEDriver.obj.o


@REM ######## Bank info
@REM #  0: main
@REM #  1: title; game over; beat level; beat game
@REM #  2: level state
@REM #  3: room data
@REM #  4: level data; npc data; routine data; metatiles data
@REM #  5: npc graphics
@REM #  6: songs
@REM #  7: songs continued; some intro
@REM #  8: intro continued