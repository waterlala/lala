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

	void ShowPosition::OnShow(map<string, int> position,int& arrowMode, int holdTime, int shootTime) {
		OnShowChangShow(0, 0, SCREEN_SIZE_X / 2 - position["heroX"]);
		OnShowChangShow(40, 0, SCREEN_SIZE_Y / 2 - position["heroY"]);
		OnShowChangShow(0, 20, position["heroX"]);
		OnShowChangShow(40, 20, position["heroY"]);
		OnShowChangShow(0, 40, position["arrowX"]);
		OnShowChangShow(40, 40, position["arrowY"]);
		OnShowChangShow(0, 60, position["bossX"]);
		OnShowChangShow(40, 60, position["bossY"]);
		OnShowChangShow(0, 80, holdTime);
		OnShowChangShow(40, 80, arrowMode);
		OnShowChangShow(0, 100, shootTime);
	}
}