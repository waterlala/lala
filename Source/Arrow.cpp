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
		arrowX = MAP_SIZE_X / 2, arrowY = MAP_SIZE_Y / 2;
		shootStyle = 0;
		isShoot = false;
	}
	int Arrow::returnArrowX() {
		return arrowX;
	}
	int Arrow::returnArrowY() {
		return arrowY;
	}
	bool Arrow::IsShooted() {
		return isShoot;
	}
	int Arrow::returnShootStyle() {
		return shootStyle;
	}
	void Arrow::LoadHeroPosition(int inX, int inY, int ind)
	{
		heroX = inX;
		heroY = inY;
		direction = ind;
	}

	void Arrow::LoadBitmap()
	{
		arrow.LoadBitmap(IDB_ARROW_0, RGB(255, 255, 255));
		moveArrow.AddBitmap(IDB_ARROW_0, RGB(255, 255, 255));
		moveArrow.AddBitmap(IDB_ARROW_1, RGB(255, 255, 255));
		moveArrow.AddBitmap(IDB_ARROW_2, RGB(255, 255, 255));
		moveArrow.AddBitmap(IDB_ARROW_3, RGB(255, 255, 255));
	}
	void Arrow::SetShoot(bool flag)
	{
		isShoot = flag;
	}

	void Arrow::OnMove()
	{
		moveArrow.OnMove();
		switch (shootStyle)
		{
			case 0: // is Shooting 
				if (isShoot)
				{
					shootStyle = 1;
					shootSpeed = 36;
					shootdirection = direction;
					arrowX = heroX;
					arrowY = heroY;
					shootTime = SHOOT_TIME;
				}
				break;
			case 1: //Shooted
					shootSpeed -= 3;
					switch (shootdirection)
					{
					case 0:
						arrowY -= (int)(shootSpeed);
						break;

					case 1:
						arrowX +=(int) (shootSpeed / 1.414);
						arrowY -= (int)(shootSpeed / 1.414);
						break;

					case 2:
						arrowX += (int)(shootSpeed);
						break;

					case 3:
						arrowX += (int)(shootSpeed / 1.414);
						arrowY += (int)(shootSpeed / 1.414);
						break;

					case 4:
						arrowY += (int)(shootSpeed);
						break;

					case 5:
						arrowX -= (int)(shootSpeed / 1.414);
						arrowY += (int)(shootSpeed / 1.414);
						break;

					case 6:
						arrowX -= (int)(shootSpeed);
						break;

					case 7:
						arrowX -= (int)(shootSpeed / 1.414);
						arrowY -= (int)(shootSpeed / 1.414);
						break;
					}
				if (shootSpeed==0)
					shootStyle = 2;
				
				if (arrowX <= BLOCK_SIZE * 2 || arrowX >= MAP_SIZE_X - BLOCK_SIZE * 2 ||
					arrowY <= BLOCK_SIZE * BLOCK_SIZE || arrowY >= MAP_SIZE_Y - BLOCK_SIZE * 3)
				{
					shootStyle = 2;
					isShoot = false;
				}
				break;
			case 2:
				dx = arrowX - heroX;
				dy = arrowY - heroY;
				if (dx != 0 || dy != 0) {
					changX = BACK_SPEED * (dx / (sqrt(dx*dx + dy * dy)));
					changY = BACK_SPEED * (dy / (sqrt(dx*dx + dy * dy)));
				}

				if (isShoot)
				{
					arrowX -= (int)changX;
					arrowY -= (int)changY;
				}
				if (arrowX - heroX >= -1 && arrowX - heroX <= 17 && arrowY - heroY >= -1 && arrowY - heroY <= 17)
				{
					shootStyle = 3;
					waitTime = 10;
				}

				break;
			case 3:
				waitTime -= 1;
				arrowX = heroX;
				arrowY = heroY;
				if (waitTime == 0)
				{
					shootStyle = 0;
					isShoot = false;
				}
		}
	}
	void Arrow::OnShow()
	{
		int mapX = SCREEN_SIZE_X / 2 - heroX;
		int mapY = SCREEN_SIZE_Y / 2 - heroY;
		switch (shootStyle)
		{
			case 1:
				moveArrow.SetTopLeft(arrowX + mapX, arrowY + mapY);
				moveArrow.OnShow();
				break;
			case 2:
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
