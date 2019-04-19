#include "stdafx.h"
#include "resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "ShowPosition.h"
#include <math.h>


namespace game_framework
{
	void ShowPosition::getArrowPosition(int inX,int inY) {
		arrowX = inX;
		arrowY = inY;
	}
	void ShowPosition::getHeroPosition(int inX, int inY) {
		heroX = inX;
		heroY = inY;
	}
	void ShowPosition::getMapPosition(int inX, int inY) {
		mapX = SCREEN_SIZE_X / 2 - inX;
		mapY = SCREEN_SIZE_Y / 2 - inY;
	}
	void ShowPosition::getBossPosition(int inX, int inY) {
		bossX = inX;
		bossY = inY;
	}
	void ShowPosition::LoadBitmap() {
		number[0].LoadBitmap(IDB_0, (0, 0, 0));
		number[1].LoadBitmap(IDB_1, (0, 0, 0));
		number[2].LoadBitmap(IDB_2, (0, 0, 0));
		number[3].LoadBitmap(IDB_3, (0, 0, 0));
		number[4].LoadBitmap(IDB_4, (0, 0, 0));
		number[5].LoadBitmap(IDB_5, (0, 0, 0));
		number[6].LoadBitmap(IDB_6, (0, 0, 0));
		number[7].LoadBitmap(IDB_7, (0, 0, 0));
		number[8].LoadBitmap(IDB_8, (0, 0, 0));
		number[9].LoadBitmap(IDB_9, (0, 0, 0));
		number[10].LoadBitmap(IDB_NEGATIVE, (0, 0, 0));
	}
	void ShowPosition::OnShowNumber(int inX, int inY, int inNumber) {
		number[inNumber].SetTopLeft(inX, inY);
		number[inNumber].ShowBitmap();
	}

	void ShowPosition::OnShowChangShow(int inX,int inY,int inNumber) {
		if (inNumber < 0) {
			OnShowNumber(inX, inY, 10);
			inNumber = -inNumber;
		}
		if (abs(inNumber) < 10) {
			OnShowNumber(inX + 30, inY , inNumber);
		}
		else if (abs(inNumber) < 100) {
			OnShowNumber(inX+20, inY , inNumber % 100 / 10);
			OnShowNumber(inX+30, inY , inNumber % 10);
		}
		else {
			OnShowNumber(inX+10, inY , inNumber % 1000 / 100);
			OnShowNumber(inX+20, inY , inNumber % 100 / 10);
			OnShowNumber(inX+30, inY , inNumber % 10);
		}
	}

	void ShowPosition::OnShow() {
		OnShowChangShow(0, 0, mapX);
		OnShowChangShow(40, 0, mapY);
		OnShowChangShow(0, 20, heroX);
		OnShowChangShow(40, 20, heroY);
		OnShowChangShow(0, 40, arrowX);
		OnShowChangShow(40, 40, arrowY);
		OnShowChangShow(0, 60, bossX);
		OnShowChangShow(40, 60, bossY);
	}
}