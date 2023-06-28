del o\*.o
del o\*.lst
del o\*.asm
del o\*.sym

C:\gbdk-4.2.0\bin\lcc -Wa-l -Wf-bo3 -c -o o/Level1Map.o Assets/Maps/Levels/Level1Map.c
C:\gbdk-4.2.0\bin\lcc -Wa-l -Wf-bo3 -c -o o/Level1MMap.o Assets/Maps/Levels/Level1MMap.c

C:\gbdk-4.2.0\bin\lcc -Wa-l -Wf-bo2 -c -o o/CrosshairTiles.o Assets/Tiles/CrosshairTiles.c
C:\gbdk-4.2.0\bin\lcc -Wa-l -Wf-bo2 -c -o o/GhostTiles.o Assets/Tiles/GhostTiles.c
C:\gbdk-4.2.0\bin\lcc -Wa-l -Wf-bo2 -c -o o/HUDTiles.o Assets/Tiles/HUD.c
C:\gbdk-4.2.0\bin\lcc -Wa-l -Wf-bo2 -c -o o/TadTiles.o Assets/Tiles/TadTiles.c
C:\gbdk-4.2.0\bin\lcc -Wa-l -Wf-bo2 -c -o o/HouseTiles.o Assets/Tiles/HouseTiles.c
C:\gbdk-4.2.0\bin\lcc -Wa-l -Wf-bo2 -c -o o/YaMetaTiles.o Assets/Tiles/YaMetaTiles.c
C:\gbdk-4.2.0\bin\lcc -Wa-l -Wf-bo2 -c -o o/fontTiles.o Assets/Tiles/fontTiles.c

C:\gbdk-4.2.0\bin\lcc -Wa-l -Wf-bo3 -c -o o/LevelData.o Database/LevelData.c

C:\gbdk-4.2.0\bin\lcc -Wa-l -Wf-bo2 -c -o o/LevelState.o States/LevelState.c

C:\gbdk-4.2.0\bin\lcc -Wa-l -c -o o/common.o Engine/common.c
C:\gbdk-4.2.0\bin\lcc -Wa-l -c -o o/IShareMapData.o Engine/IShareMapData.c

C:\gbdk-4.2.0\bin\lcc -Wa-l -c -o o/main.o main.c
C:\gbdk-4.2.0\bin\lcc -Wl-yt3 -Wl-yoA -Wl-ya4 -o Mirror.gb o/*.o


@REM ######## Bank info
@REM #  0: main
@REM #  1: 
@REM #  2: level state
@REM #  3: level data

@REM Sloppy TODO:
@REM Camera scrolling/level loading
@REM Mirror world transition

