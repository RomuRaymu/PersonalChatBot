#include "MineMap.h"

MineMap::MineMap() {
    map = NULL;
    maxMapSize = 0;
    mapSize = 0;
    mineSize = 0;
}

MineMap::~MineMap() {
    if (mapSize > 0) {
        free(map);
    }
}

int *&MineMap::Map() { return map; }

int MineMap::MaxMapSize() { return maxMapSize; }
int MineMap::MapSize() { return mapSize; }
int MineMap::MineSize() { return mineSize; }

void MineMap::CreateMap(int mapSize, int minePercent) {

    SetMap(mapSize);

    srand((unsigned)time(NULL));
    SetMineSize(mapSize,minePercent);
    for (int i = 0; i < mineSize;) {
        int x = rand() % mapSize;
        int y = rand() % mapSize;
        int index = y * mapSize + x;
        if (map[index] != 9) {
            map[index] = 9;
            i++;

            for (int yy = -1; yy <= 1; yy++) {
                for (int xx = -1; xx <= 1; xx++) {
                    int xxx = xx + x;
                    int yyy = yy + y;
                    if (xxx == x && yyy == y)
                        continue;

                    if (0 <= xxx && xxx < mapSize && 0 <= yyy && yyy < mapSize) {
                        int index2 = yyy * mapSize + xxx;
                        if (map[index2] != 9)
                            map[index2]++;
                    }
                }
            }
        }
    }
}

void MineMap::SetMap(int mapSize) {
    if (mapSize == 0) {
        this->mapSize = maxMapSize = mapSize;
        map = (int *)calloc(mapSize * mapSize, sizeof(int));
        return;
    } else if (maxMapSize < mapSize) {
        maxMapSize = mapSize;
        map = (int *)realloc(map, mapSize * mapSize * sizeof(int));
    }
    this->mapSize = mapSize;
    for (int i = 0; i < mapSize * mapSize; i++) {
        map[i] = 0;
    }
}

void MineMap::SetMineSize(int mapSize, int minePercent) {
    mineSize = mapSize * mapSize * minePercent / 100;
}

int &MineMap::GetData(int x, int y) { return map[y * mapSize + x]; }
