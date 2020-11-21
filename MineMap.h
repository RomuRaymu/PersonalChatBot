#ifndef __MINEMAP_H__
#define __MINEMAP_H__

#include <cstdlib>
#include <time.h>
#include <vector>

using namespace std;

class MineMap {
  public:
    static const int MINE = 9;
    static const int OPENED_MINE = 90;
    static const int FLAGED_NONE = -100;
    static const int NONE = 0;
    static const int OPENED_NONE = 100;

  public:
    MineMap();
    ~MineMap();

    int *&Map();
    int MaxMapSize();
    int MapSize();
    int MineSize();

    void CreateMap(int mapSize, int minePercent);

    void SetMap(int mapSize);
    void SetMineSize(int mapSize, int minePercent);

    int &GetData(int x, int y);

  private:
    int *map;
    int maxMapSize;
    int mapSize;
    int mineSize; // Total Mine Size
};

#endif
