del o\*.o
del o\*.lst
del o\*.asm
del o\*.sym

C:\gbdk-4.2.0\bin\png2asset Assets/Sprites/HUDTeeth.png -pw 0 -ph 0 -b 2 -sw 32 -sh 16 -keep_duplicate_tiles -noflip
C:\gbdk-4.2.0\bin\png2asset Assets/Sprites/MC.png -pw 0 -ph 0 -b 2 -sw 16 -sh 16 -spr8x8
C:\gbdk-4.2.0\bin\png2asset Assets/Sprites/NPCgirl.png -pw 0 -ph 0 -b 5 -sw 16 -sh 16 -spr8x8

C:\gbdk-4.2.0\bin\lcc -Wa-l -Wf-bo3 -c -o o/HouseRMap.o Assets/Maps/Levels/HouseRMap.c
C:\gbdk-4.2.0\bin\lcc -Wa-l -Wf-bo3 -c -o o/HouseMMap.o Assets/Maps/Levels/HouseMMap.c

C:\gbdk-4.2.0\bin\lcc -Wa-l -Wf-bo2 -c -o o/BloodstainTiles.o Assets/Tiles/BloodstainTiles.c
C:\gbdk-4.2.0\bin\lcc -Wa-l -Wf-bo2 -c -o o/ExclamationTiles.o Assets/Tiles/ExclamationTiles.c
C:\gbdk-4.2.0\bin\lcc -Wa-l -Wf-bo2 -c -o o/HUDTiles.o Assets/Tiles/HUD.c
C:\gbdk-4.2.0\bin\lcc -Wa-l -Wf-bo2 -c -o o/fontTiles.o Assets/Tiles/fontTiles.c
C:\gbdk-4.2.0\bin\lcc -Wa-l -Wf-bo4 -c -o o/HouseTiles.o Assets/Tiles/HouseTiles.c
C:\gbdk-4.2.0\bin\lcc -Wa-l -Wf-bo4 -c -o o/HouseMTiles.o Assets/Tiles/HouseMTiles.c

C:\gbdk-4.2.0\bin\lcc -Wa-l -Wf-bo3 -c -o o/RoomData.o Database/RoomData.c
C:\gbdk-4.2.0\bin\lcc -Wa-l -Wf-bo4 -c -o o/LevelData.o Database/LevelData.c
C:\gbdk-4.2.0\bin\lcc -Wa-l -Wf-bo4 -c -o o/MetatilesData.o Database/MetatilesData.c
C:\gbdk-4.2.0\bin\lcc -Wa-l -Wf-bo4 -c -o o/NPCData.o Database/NPCData.c
C:\gbdk-4.2.0\bin\lcc -Wa-l -Wf-bo4 -c -o o/RoutineData.o Database/RoutineData.c

C:\gbdk-4.2.0\bin\lcc -Wa-l -Wf-bo2 -c -o o/LevelState.o States/LevelState.c

C:\gbdk-4.2.0\bin\lcc -Wa-l -c -o o/common.o Engine/common.c
C:\gbdk-4.2.0\bin\lcc -Wa-l -c -o o/fade.o Engine/fade.c
C:\gbdk-4.2.0\bin\lcc -Wa-l -c -o o/IShareLevelData.o Engine/IShareLevelData.c
C:\gbdk-4.2.0\bin\lcc -Wa-l -c -o o/ILoadMapTileData.o Engine/ILoadMapTileData.c
C:\gbdk-4.2.0\bin\lcc -Wa-l -c -o o/IShareMapData.o Engine/IShareMapData.c
C:\gbdk-4.2.0\bin\lcc -Wa-l -c -o o/IShareNPCData.o Engine/IShareNPCData.c
C:\gbdk-4.2.0\bin\lcc -Wa-l -c -o o/IShareNPCGraphics.o Engine/IShareNPCGraphics.c
C:\gbdk-4.2.0\bin\lcc -Wa-l -c -o o/IShareRoutineData.o Engine/IShareRoutineData.c

C:\gbdk-4.2.0\bin\lcc -Wa-l -c -o o/main.o main.c
C:\gbdk-4.2.0\bin\lcc -Wl-yt3 -Wl-yoA -Wl-ya4 -o Banished.gb o/*.o Assets/Sprites/*.c


@REM ######## Bank info
@REM #  0: main
@REM #  1: 
@REM #  2: level state
@REM #  3: room data
@REM #  4: level data; npc data; routine data; metatiles data
@REM #  5: npc graphics
