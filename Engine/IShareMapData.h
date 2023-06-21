#ifndef ISHAREMAPDATA_H
#define ISHAREMAPDATA_H

void loadMapDataFromDatabase(UINT8, UINT8, UINT8);
// UINT8 loadTileDataForMap(UINT8);  // Returns walkableBlockCount
UINT8 getOwMapHeight(UINT8);
UINT8 getOwMapWidth(UINT8);

#endif