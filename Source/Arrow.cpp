#include "stdafx.h"
#include "resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "Arrow.h"
#include <math.h>
#include "CMap.h"

namespace game_framework
{
	Arrow::Arrow()
	{
		Initialize();
	}

	void Arrow::Initialize()
	{
		shootSpeed = 40;
		shootTime = 0;
		holdTime = 0;
		isShoot = false;
	}

	int Arrow::GetX() {
		return arrowX;
	}

	int Arrow::GetY() {
		return arrowY;
	}

	bool Arrow::IsShooted() {
		return isShoot;
	}

	void Arrow::SetShoot(bool flag)
	{
		isShoot = flag;
	}

	void Arrow::SetShootDirection(const int DIRECTION) {
		shootDirection = DIRECTION;
	}

	int Arrow::GetHoldTime() {
		return holdTime;
	}

	int Arrow::GetShootTime() {
		return shootTime;
	}

	void Arrow::LoadBitmap()
	{
		arrow.LoadBitmap(IDB_ARROW_0, RGB(255, 255, 255));

		moveArrow.AddBitmap(IDB_ARROW_0, RGB(255, 255, 255));
		moveArrow.AddBitmap(IDB_ARROW_1, RGB(255, 255, 255));
		moveArrow.AddBitmap(IDB_ARROW_2, RGB(255, 255, 255));
		moveArrow.AddBitmap(IDB_ARROW_3, RGB(255, 255, 255));

	}

	void Arrow::ShootMode(int& arrowMode, const int DIRECTION, map<string, int>& position) {
		switch (arrowMode) {
			case 1:
				break;
			case 2:
				OnShoot(DIRECTION, position);
				if(isShoot){
					if (holdTime <= 3) {
						Initialize();
						arrowMode = 1;
					}
					else {
						arrowMode = 3;
					}
				}
				break;
			case 3:
				Shooting();
				if (shootTime == 0) {
					isShoot = false;
					arrowMode = 4;
				}
				break;
			case 4:
				if (isShoot) {
					if (OnReturn(position)) {
						Initialize();
						waitTime = 10;
						arrowMode = 5;
					}
				}
				break;
			case 5:
				if (!IsCD()) {
					//Initialize();
					arrowMode = 1;
				}
		}
	}

	void Arrow::OnShoot(const int DIRECTION, map<string, int>& position)
	{
		moveArrow.OnMove();

		if (holdTime <= 39) {
			holdTime += 1;
			shootTime = 5 * holdTime / 20;
		}

		int START = 5;
		switch (DIRECTION)
		{
		case 0:
			arrowX = position["heroX"] + START;
			arrowY = position["heroY"];
			break;

		case 1:
			arrowX = position["heroX"] + (START / 1.414);
			arrowY = position["heroY"] + (START / 1.414);
			break;

		case 2:
			arrowX = position["heroX"];
			arrowY = position["heroY"] + START;
			break;

		case 3:
			arrowX = position["heroX"] - (START / 1.414);
			arrowY = position["heroY"] + (START / 1.414);
			break;

		case 4:
			arrowX = position["heroX"] - START;
			arrowY = position["heroY"];
			break;

		case 5:
			arrowX = position["heroX"] - (START / 1.414);
			arrowY = position["heroY"] - (START / 1.414);
			break;

		case 6:
			arrowX = position["heroX"];
			arrowY = position["heroY"] - START;
			break;

		case 7:
			arrowX = position["heroX"] + (START / 1.414);
			arrowY = position["heroY"] - (START / 1.414);
			break;
		}
		
	}

	void Arrow::Shooting() {
		//collisionwithwall
		switch (shootDirection)
		{
		case 0:
			arrowY -= shootSpeed;
			break;

		case 1:
			arrowX += shootSpeed / 1.414;
			arrowY -= shootSpeed / 1.414;
			break;

		case 2:
			arrowX += shootSpeed;
			break;

		case 3:
			arrowX += shootSpeed / 1.414;
			arrowY += shootSpeed / 1.414;
			break;

		case 4:
			arrowY += shootSpeed;
			break;

		case 5:
			arrowX -= shootSpeed / 1.414;
			arrowY += shootSpeed / 1.414;
			break;

		case 6:
			arrowX -= shootSpeed;
			break;

		case 7:
			arrowX -= shootSpeed / 1.414;
			arrowY -= shootSpeed / 1.414;
			break;
		}
		shootTime -= 1;
		shootSpeed -= 4;
	}

	bool Arrow::OnReturn(map<string, int>& position)
	{
		if (isShoot)
		{
			int dx = arrowX - position["heroX"], dy = arrowY - position["heroY"];
			moveArrow.OnMove();
			arrowX -= BACK_SPEED * (dx) / (sqrt((dx) * (dx) + (dy) * (dy)));
			arrowY -= BACK_SPEED * (dy) / (sqrt((dx) * (dx) + (dy) * (dy)));
			if (arrowX - position["heroX"] >= -1 && arrowX - position["heroX"] <= 17 && arrowY - position["heroY"] >= -1 && arrowY - position["heroY"] <= 17){
				isShoot = false;
				return true;
			}
		}
		return false;
	}

	bool Arrow::IsCD() {
		if (waitTime <= 0) {
			return false;
		}
		waitTime -= 1;
		return true;
	}

	void Arrow::OnShow(int& arrowMode, map<string, int>& position)
	{
		int mapX = SCREEN_SIZE_X / 2 - position["heroX"], mapY = SCREEN_SIZE_Y / 2 - position["heroY"];
		switch (arrowMode)
		{
		case 2: case 3:
				moveArrow.SetTopLeft(arrowX + mapX, arrowY + mapY);
				moveArrow.OnShow();
				break;
			case 4:
				if (isShoot) {
					moveArrow.SetTopLeft(arrowX + mapX, arrowY + mapY);
					moveArrow.OnShow();
				}
				else {
					arrow.SetTopLeft(arrowX + mapX, arrowY + mapY);
					arrow.ShowBitmap();
				}
				break;
			default:
				break;
		}
	}
}
