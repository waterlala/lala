#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include <vector>
#include "audio.h"
#include "gamelib.h"
#include "CMap.h"

namespace game_framework {
	CMap::CMap()
	{
		Initialize();
	}

	void CMap::LoadBitmap()
	{
		mapPic[0].LoadBitmap(IDB_FLOOR, RGB(255, 255, 255));
		mapPic[1].LoadBitmap(IDB_WALL, RGB(255, 255, 255));
		mapPic[2].LoadBitmap(IDB_TOPWALL, RGB(255, 255, 255));
		mapPic[3].LoadBitmap(IDB_DOWNWALL, RGB(255, 255, 255));
		mapPic[4].LoadBitmap(IDB_TOPDOWNWALL, RGB(255, 255, 255));
		mapPic[5].LoadBitmap(IDB_WALLONWALL, RGB(255, 255, 255));
		mapPic[6].LoadBitmap(IDB_WALLDOWNWALL, RGB(255, 255, 255));
	}

	void CMap::Initialize()
	{	
		map.resize(MAP_SIZE_Y / BLOCK_SIZE);
		for (int i = 0; i < NUMBER_BLOCK_Y; i++)
		{
			map[i].resize(MAP_SIZE_X / BLOCK_SIZE);
		}
		for (int i = 0; i < NUMBER_BLOCK_Y; i++)
		{
			map[i][0] = 2;
			map[i][NUMBER_BLOCK_X - 1] = 2;
			if (i > BLOCK_SIZE)
			{
				if (i % 2 == 1 && ((NUMBER_BLOCK_Y - 1) % 2 == 0 || i != NUMBER_BLOCK_Y - 1))
				{
					for (int j = 0; j < NUMBER_BLOCK_X; j++)
					{
						map[0][j] = 4;
						map[NUMBER_BLOCK_Y - 1][j] = 4;
						if (j % 2 == 1 && ((NUMBER_BLOCK_X - 1) % 2 == 0 || j != NUMBER_BLOCK_X - 1))
							map[i][j] = 1;
					}
				}
			}
		}
		for (int i = 1; i <= BLOCK_SIZE; i++) {
			for (int j = 1; j < NUMBER_BLOCK_X - 1; j++) {
				if (j % 12 == 0) {
					if (i == BLOCK_SIZE)
						map[i][j] = 7;
					else
						map[i][j] = 6;
				}
				else {
					if (i == BLOCK_SIZE)
						map[i][j] = 5;
					else
					{
						map[i][j] = 3;
					}
				}
			}
		}
	}

	void CMap::OnShow(int heroX, int heroY) {
		mapX = SCREEN_SIZE_X / 2 - heroX;
		mapY = SCREEN_SIZE_Y / 2 - heroY;
		for (int i = 0; i < NUMBER_BLOCK_Y; i++) {
			for (int j = 0; j < NUMBER_BLOCK_X; j++) {
				if (map[i][j] != 0)
				{
					mapPic[map[i][j] - 1].SetTopLeft(mapX + j * BLOCK_SIZE, mapY + i * BLOCK_SIZE);
					mapPic[map[i][j] - 1].ShowBitmap();
				}		
			}
		}
	}
	
	const vector<vector <int>>& CMap::GetMap()
	{
		return map;
	}
}