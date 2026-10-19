#ifndef OJ_BOARDS
#define OJ_BOARDS
#include "ojDefs.h"
#include "ojUnits.h"

#define DIR_N {true, false, false, false}
#define DIR_W {false, true, false, false}
#define DIR_S {false, false, true, false}
#define DIR_E {false, false, false, true}

#define DIR_NW {true, true, false, false}
#define DIR_WS {false, true, true, false}
#define DIR_SE {false, false, true, true}
#define DIR_EN {true, false, false, true}

#define DIR_NWS {true, true, true, false}
#define DIR_WSE {false, true, true, true}
#define DIR_SEN {true, false, true, true}
#define DIR_ENW {true, true, false, true}

#define DIR_NWSE {true, true, true, true}

class PuddingChase: public Board{
	int boardSize[2] = {9, 9};
	
	vector<Tile> tiles = {Tile(TILE_BONUS, 4, 0, DIR_S), Tile(TILE_DROP, 5, 0, DIR_E), Tile(TILE_ENEMY, 6, 0, DIR_E), Tile(TILE_BONUS, 7, 0, DIR_E),
		Tile(TILE_DRAW, 4, 1, DIR_S), Tile(TILE_WARP, 7, 1, DIR_N), Tile(TILE_DRAW, 8, 1, DIR_E), Tile(TILE_BONUS, 9, 1, DIR_E),
		Tile(TILE_BONUS, 3, 2, DIR_S), Tile(TILE_HOME, 4, 2, DIR_E, 1), Tile(TILE_ENEMY, 5, 2, DIR_E), Tile(TILE_DROP, 6, 2, DIR_E), Tile(TILE_WARP, 7, 2, DIR_EN), Tile(TILE_ENEMY, 9, 2, DIR_N),
		Tile(TILE_DRAW, 3, 3, DIR_S), Tile(TILE_BONUS, 7, 3, DIR_N), Tile(TILE_ENEMY, 9, 3, DIR_N),
		Tile(TILE_BONUS, 1, 4, DIR_S), Tile(TILE_DRAW, 2, 4, DIR_E), Tile(TILE_HOME, 3, 4, DIR_SE, 2), Tile(TILE_HOME, 7, 4, DIR_NW, 3), Tile(TILE_DRAW, 8, 4, DIR_W), Tile(TILE_BONUS, 9, 4, DIR_N),
		Tile(TILE_ENEMY, 1, 5, DIR_S), Tile(TILE_BONUS, 3, 5, DIR_S), Tile(TILE_DRAW, 7, 8, DIR_N),
		Tile(TILE_ENEMY, 1, 6, DIR_W), Tile(TILE_WARP, 3, 6, DIR_WS), Tile(TILE_DROP, 4, 6, DIR_W), Tile(TILE_ENEMY, 5, 8, DIR_W), Tile(TILE_HOME, 6, 8, DIR_W, 4), Tile(TILE_BONUS, 7, 8, DIR_N),
		Tile(TILE_BONUS, 1, 7, DIR_W), Tile(TILE_DRAW, 2, 8, DIR_W), Tile(TILE_WARP, 3, 8, DIR_S), Tile(TILE_DRAW, 6, 8, DIR_N),
		Tile(TILE_BONUS, 3, 9, DIR_W), Tile(TILE_ENEMY, 4, 9, DIR_W), Tile(TILE_DROP, 5, 4, DIR_W), Tile(TILE_BONUS, 6, 9, DIR_N),};
	
	EUnit boss = Manager();
};

#endif