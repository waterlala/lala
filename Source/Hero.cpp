#include "stdafx.h"
#include "resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "Hero.h"
#include "CMap.h"

namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// Hero: Eraser class
	/////////////////////////////////////////////////////////////////////////////

	Hero::Hero()
	{
		Initialize();
	}

	int Hero::GetX1()
	{
		return heroX;
	}

	int Hero::GetY1()
	{
		return heroY;
	}

	int Hero::GetX2()
	{
		return heroX + heroMoving[direction].Width();
	}

	int Hero::GetY2()
	{
		return heroY + heroMoving[direction].Height();
	}

	int Hero::GetDirection()
	{
		return direction;
	}

	bool Hero::IsRolling()
	{
		return isRolling;
	}

	bool Hero::IsShooting()
	{
		return isShooting;
	}

	void Hero::Initialize()
	{
		heroX = MAP_SIZE_X / 2, heroY = MAP_SIZE_Y / 2;
		direction = 0;
		isMovingLeft = isMovingRight = isMovingUp = isMovingDown = isRolling = isShooting = false;
	}

	void Hero::LoadBitmap()
	{
		hero[0].LoadBitmap(IDB_HERO_UP, RGB(255, 255, 255));		//Clock	// 0-> down		1->up right
		hero[1].LoadBitmap(IDB_HERO_UP_RIGHT, RGB(255, 255, 255));			// 2-> right	3->down right
		hero[2].LoadBitmap(IDB_HERO_RIGHT, RGB(255, 255, 255));			// 4-> up       5->down left
		hero[3].LoadBitmap(IDB_HERO_DOWN_RIGHT, RGB(255, 255, 255));		// 6-> left     7->up left
		hero[4].LoadBitmap(IDB_HERO_DOWN, RGB(255, 255, 255));
		hero[5].LoadBitmap(IDB_HERO_DOWN_LEFT, RGB(255, 255, 255));
		hero[6].LoadBitmap(IDB_HERO_LEFT, RGB(255, 255, 255));
		hero[7].LoadBitmap(IDB_HERO_UP_LEFT, RGB(255, 255, 255));


		heroMoving[0].AddBitmap(IDB_HERO_UP, RGB(255, 255, 255));
		heroMoving[0].AddBitmap(IDB_HERO_UP2, RGB(255, 255, 255));
		heroMoving[0].AddBitmap(IDB_HERO_UP3, RGB(255, 255, 255));
		heroMoving[0].AddBitmap(IDB_HERO_UP4, RGB(255, 255, 255));
		heroMoving[0].AddBitmap(IDB_HERO_UP5, RGB(255, 255, 255));
		heroMoving[0].AddBitmap(IDB_HERO_UP, RGB(255, 255, 255));

		heroMoving[1].AddBitmap(IDB_HERO_UP_RIGHT, RGB(255, 255, 255));
		heroMoving[1].AddBitmap(IDB_HERO_UP_RIGHT2, RGB(255, 255, 255));
		heroMoving[1].AddBitmap(IDB_HERO_UP_RIGHT3, RGB(255, 255, 255));
		heroMoving[1].AddBitmap(IDB_HERO_UP_RIGHT4, RGB(255, 255, 255));
		heroMoving[1].AddBitmap(IDB_HERO_UP_RIGHT5, RGB(255, 255, 255));
		heroMoving[1].AddBitmap(IDB_HERO_UP_RIGHT, RGB(255, 255, 255));

		heroMoving[2].AddBitmap(IDB_HERO_RIGHT, RGB(255, 255, 255));
		heroMoving[2].AddBitmap(IDB_HERO_RIGHT2, RGB(255, 255, 255));
		heroMoving[2].AddBitmap(IDB_HERO_RIGHT3, RGB(255, 255, 255));
		heroMoving[2].AddBitmap(IDB_HERO_RIGHT4, RGB(255, 255, 255));
		heroMoving[2].AddBitmap(IDB_HERO_RIGHT5, RGB(255, 255, 255));
		heroMoving[2].AddBitmap(IDB_HERO_RIGHT, RGB(255, 255, 255));

		heroMoving[3].AddBitmap(IDB_HERO_DOWN_RIGHT, RGB(255, 255, 255));
		heroMoving[3].AddBitmap(IDB_HERO_DOWN_RIGHT2, RGB(255, 255, 255));
		heroMoving[3].AddBitmap(IDB_HERO_DOWN_RIGHT3, RGB(255, 255, 255));
		heroMoving[3].AddBitmap(IDB_HERO_DOWN_RIGHT4, RGB(255, 255, 255));
		heroMoving[3].AddBitmap(IDB_HERO_DOWN_RIGHT5, RGB(255, 255, 255));
		heroMoving[3].AddBitmap(IDB_HERO_DOWN_RIGHT, RGB(255, 255, 255));

		heroMoving[4].AddBitmap(IDB_HERO_DOWN, RGB(255, 255, 255));
		heroMoving[4].AddBitmap(IDB_HERO_DOWN2, RGB(255, 255, 255));
		heroMoving[4].AddBitmap(IDB_HERO_DOWN3, RGB(255, 255, 255));
		heroMoving[4].AddBitmap(IDB_HERO_DOWN4, RGB(255, 255, 255));
		heroMoving[4].AddBitmap(IDB_HERO_DOWN5, RGB(255, 255, 255));
		heroMoving[4].AddBitmap(IDB_HERO_DOWN, RGB(255, 255, 255));

		heroMoving[5].AddBitmap(IDB_HERO_DOWN_LEFT, RGB(255, 255, 255));
		heroMoving[5].AddBitmap(IDB_HERO_DOWN_LEFT2, RGB(255, 255, 255));
		heroMoving[5].AddBitmap(IDB_HERO_DOWN_LEFT3, RGB(255, 255, 255));
		heroMoving[5].AddBitmap(IDB_HERO_DOWN_LEFT4, RGB(255, 255, 255));
		heroMoving[5].AddBitmap(IDB_HERO_DOWN_LEFT5, RGB(255, 255, 255));
		heroMoving[5].AddBitmap(IDB_HERO_DOWN_LEFT, RGB(255, 255, 255));

		heroMoving[6].AddBitmap(IDB_HERO_LEFT, RGB(255, 255, 255));
		heroMoving[6].AddBitmap(IDB_HERO_LEFT2, RGB(255, 255, 255));
		heroMoving[6].AddBitmap(IDB_HERO_LEFT3, RGB(255, 255, 255));
		heroMoving[6].AddBitmap(IDB_HERO_LEFT4, RGB(255, 255, 255));
		heroMoving[6].AddBitmap(IDB_HERO_LEFT5, RGB(255, 255, 255));
		heroMoving[6].AddBitmap(IDB_HERO_LEFT, RGB(255, 255, 255));

		heroMoving[7].AddBitmap(IDB_HERO_UP_LEFT, RGB(255, 255, 255));
		heroMoving[7].AddBitmap(IDB_HERO_UP_LEFT2, RGB(255, 255, 255));
		heroMoving[7].AddBitmap(IDB_HERO_UP_LEFT3, RGB(255, 255, 255));
		heroMoving[7].AddBitmap(IDB_HERO_UP_LEFT4, RGB(255, 255, 255));
		heroMoving[7].AddBitmap(IDB_HERO_UP_LEFT5, RGB(255, 255, 255));
		heroMoving[7].AddBitmap(IDB_HERO_UP_LEFT, RGB(255, 255, 255));


		heroRolling[0].AddBitmap(IDB_HERO_ROLL_UP1, RGB(255, 255, 255));
		heroRolling[0].AddBitmap(IDB_HERO_ROLL_UP2, RGB(255, 255, 255));
		heroRolling[0].AddBitmap(IDB_HERO_ROLL_UP3, RGB(255, 255, 255));
		heroRolling[0].AddBitmap(IDB_HERO_ROLL_UP4, RGB(255, 255, 255));
		heroRolling[0].AddBitmap(IDB_HERO_ROLL_UP5, RGB(255, 255, 255));
		heroRolling[0].AddBitmap(IDB_HERO_ROLL_UP6, RGB(255, 255, 255));
		heroRolling[0].AddBitmap(IDB_HERO_UP, RGB(255, 255, 255));

		heroRolling[1].AddBitmap(IDB_HERO_ROLL_TOP_RIGHT1, RGB(255, 255, 255));
		heroRolling[1].AddBitmap(IDB_HERO_ROLL_TOP_RIGHT2, RGB(255, 255, 255));
		heroRolling[1].AddBitmap(IDB_HERO_ROLL_TOP_RIGHT3, RGB(255, 255, 255));
		heroRolling[1].AddBitmap(IDB_HERO_ROLL_TOP_RIGHT4, RGB(255, 255, 255));
		heroRolling[1].AddBitmap(IDB_HERO_ROLL_TOP_RIGHT5, RGB(255, 255, 255));
		heroRolling[1].AddBitmap(IDB_HERO_ROLL_TOP_RIGHT6, RGB(255, 255, 255));
		heroRolling[1].AddBitmap(IDB_HERO_UP_RIGHT, RGB(255, 255, 255));

		heroRolling[2].AddBitmap(IDB_HERO_ROLL_RIGHT1, RGB(255, 255, 255));
		heroRolling[2].AddBitmap(IDB_HERO_ROLL_RIGHT2, RGB(255, 255, 255));
		heroRolling[2].AddBitmap(IDB_HERO_ROLL_RIGHT3, RGB(255, 255, 255));
		heroRolling[2].AddBitmap(IDB_HERO_ROLL_RIGHT4, RGB(255, 255, 255));
		heroRolling[2].AddBitmap(IDB_HERO_ROLL_RIGHT5, RGB(255, 255, 255));
		heroRolling[2].AddBitmap(IDB_HERO_ROLL_RIGHT6, RGB(255, 255, 255));
		heroRolling[2].AddBitmap(IDB_HERO_RIGHT, RGB(255, 255, 255));

		heroRolling[3].AddBitmap(IDB_HERO_ROLL_DOWN_RIGHT1, RGB(255, 255, 255));
		heroRolling[3].AddBitmap(IDB_HERO_ROLL_DOWN_RIGHT2, RGB(255, 255, 255));
		heroRolling[3].AddBitmap(IDB_HERO_ROLL_DOWN_RIGHT3, RGB(255, 255, 255));
		heroRolling[3].AddBitmap(IDB_HERO_ROLL_DOWN_RIGHT4, RGB(255, 255, 255));
		heroRolling[3].AddBitmap(IDB_HERO_ROLL_DOWN_RIGHT5, RGB(255, 255, 255));
		heroRolling[3].AddBitmap(IDB_HERO_ROLL_DOWN_RIGHT6, RGB(255, 255, 255));
		heroRolling[3].AddBitmap(IDB_HERO_DOWN_RIGHT, RGB(255, 255, 255));

		heroRolling[4].AddBitmap(IDB_HERO_ROLL_DOWN1, RGB(255, 255, 255));
		heroRolling[4].AddBitmap(IDB_HERO_ROLL_DOWN2, RGB(255, 255, 255));
		heroRolling[4].AddBitmap(IDB_HERO_ROLL_DOWN3, RGB(255, 255, 255));
		heroRolling[4].AddBitmap(IDB_HERO_ROLL_DOWN4, RGB(255, 255, 255));
		heroRolling[4].AddBitmap(IDB_HERO_ROLL_DOWN5, RGB(255, 255, 255));
		heroRolling[4].AddBitmap(IDB_HERO_ROLL_DOWN6, RGB(255, 255, 255));
		heroRolling[4].AddBitmap(IDB_HERO_DOWN, RGB(255, 255, 255));

		heroRolling[5].AddBitmap(IDB_HERO_ROLL_DOWN_LEFT1, RGB(255, 255, 255));
		heroRolling[5].AddBitmap(IDB_HERO_ROLL_DOWN_LEFT2, RGB(255, 255, 255));
		heroRolling[5].AddBitmap(IDB_HERO_ROLL_DOWN_LEFT3, RGB(255, 255, 255));
		heroRolling[5].AddBitmap(IDB_HERO_ROLL_DOWN_LEFT4, RGB(255, 255, 255));
		heroRolling[5].AddBitmap(IDB_HERO_ROLL_DOWN_LEFT5, RGB(255, 255, 255));
		heroRolling[5].AddBitmap(IDB_HERO_ROLL_DOWN_LEFT6, RGB(255, 255, 255));
		heroRolling[5].AddBitmap(IDB_HERO_DOWN_LEFT, RGB(255, 255, 255));

		heroRolling[6].AddBitmap(IDB_HERO_ROLL_LEFT1, RGB(255, 255, 255));
		heroRolling[6].AddBitmap(IDB_HERO_ROLL_LEFT2, RGB(255, 255, 255));
		heroRolling[6].AddBitmap(IDB_HERO_ROLL_LEFT3, RGB(255, 255, 255));
		heroRolling[6].AddBitmap(IDB_HERO_ROLL_LEFT4, RGB(255, 255, 255));
		heroRolling[6].AddBitmap(IDB_HERO_ROLL_LEFT5, RGB(255, 255, 255));
		heroRolling[6].AddBitmap(IDB_HERO_ROLL_LEFT6, RGB(255, 255, 255));
		heroRolling[6].AddBitmap(IDB_HERO_LEFT, RGB(255, 255, 255));

		heroRolling[7].AddBitmap(IDB_HERO_ROLL_TOP_LEFT1, RGB(255, 255, 255));
		heroRolling[7].AddBitmap(IDB_HERO_ROLL_TOP_LEFT2, RGB(255, 255, 255));
		heroRolling[7].AddBitmap(IDB_HERO_ROLL_TOP_LEFT3, RGB(255, 255, 255));
		heroRolling[7].AddBitmap(IDB_HERO_ROLL_TOP_LEFT4, RGB(255, 255, 255));
		heroRolling[7].AddBitmap(IDB_HERO_ROLL_TOP_LEFT5, RGB(255, 255, 255));
		heroRolling[7].AddBitmap(IDB_HERO_ROLL_TOP_LEFT6, RGB(255, 255, 255));
		heroRolling[7].AddBitmap(IDB_HERO_UP_LEFT, RGB(255, 255, 255));

		heroShooting[0].LoadBitmap(IDB_HERO_UP, RGB(255, 255, 255));		
		heroShooting[1].LoadBitmap(IDB_HERO_UP_RIGHT, RGB(255, 255, 255));			
		heroShooting[2].LoadBitmap(IDB_HERO_RIGHT, RGB(255, 255, 255));			
		heroShooting[3].LoadBitmap(IDB_HERO_DOWN_RIGHT, RGB(255, 255, 255));
		heroShooting[4].LoadBitmap(IDB_HERO_DOWN, RGB(255, 255, 255));
		heroShooting[5].LoadBitmap(IDB_HERO_DOWN_LEFT, RGB(255, 255, 255));
		heroShooting[6].LoadBitmap(IDB_HERO_LEFT, RGB(255, 255, 255));
		heroShooting[7].LoadBitmap(IDB_HERO_UP_LEFT, RGB(255, 255, 255));
	}

	void Hero::CollisionWithWall(int speed, vector<vector <int>>& map)
	{
		for (int i = 0; i < speed; i++)
		{
			switch (direction)
			{
			case 0:
				if (map[(heroY - 3) / BLOCK_SIZE][(heroX + 3) / BLOCK_SIZE] != 3 && map[(heroY - 3) / BLOCK_SIZE][(heroX + 3) / BLOCK_SIZE] != 6)
				{
					heroY -= 1;
				}
				break;
			case 1:
				if (map[(heroY - 3) / BLOCK_SIZE][(heroX + 3) / BLOCK_SIZE] != 3 && map[(heroY - 3) / BLOCK_SIZE][(heroX + 3) / BLOCK_SIZE] != 6)
				{
					heroY -= 1;
				}
				if (map[(heroY) / BLOCK_SIZE][(heroX + heroMoving[direction].Width() - 3) / BLOCK_SIZE] != 2)
				{
					heroX += 1;
				}
				break;
			case 2:
				if (map[(heroY) / BLOCK_SIZE][(heroX + heroMoving[direction].Width() - 3) / BLOCK_SIZE] != 2)
				{
					heroX += 1;
				}
				break;
			case 3:
				if (map[(heroY) / BLOCK_SIZE][(heroX + heroMoving[direction].Width() - 3) / BLOCK_SIZE] != 2)
				{
					heroX += 1;
				}
				if (map[(heroY + heroMoving[direction].Height()) / BLOCK_SIZE][(heroX + STEP_SIZE) / BLOCK_SIZE] != 4)
				{
					heroY += 1;
				}
				break;
			case 4:
				if (map[(heroY + heroMoving[direction].Height()) / BLOCK_SIZE][(heroX + 3) / BLOCK_SIZE] != 4)
				{
					heroY += 1;
				}
				break;
			case 5:
				if (map[(heroY + heroMoving[direction].Height()) / BLOCK_SIZE][(heroX + 3) / BLOCK_SIZE] != 4)
				{
					heroY += 1;
				}
				if (map[heroY / BLOCK_SIZE][(heroX + 2) / BLOCK_SIZE] != 2)
				{
					heroX -= 1;
				}
				break;
			case 6:
				if (map[heroY / BLOCK_SIZE][(heroX + 2) / BLOCK_SIZE] != 2)
				{
					heroX -= 1;
				}
				break;
			case 7:
				if (map[heroY / BLOCK_SIZE][(heroX + 2) / BLOCK_SIZE] != 2)
				{
					heroX -= 1;
				}
				if (map[(heroY - 3) / BLOCK_SIZE][(heroX + 3) / BLOCK_SIZE] != 3 && map[(heroY - 3) / BLOCK_SIZE][(heroX + 3) / BLOCK_SIZE] != 6)
				{
					heroY -= 1;
				}
				break;
			}
		}
	}

	void Hero::OnRoll(vector<vector <int>> map)
	{
		for (int i = 0; i < 7; i++)
		{
			heroRolling[direction].OnMove();
		}
		CollisionWithWall(STEP_SIZE * 2, map);
	}

	void Hero::OnMove(vector<vector <int>> map)
	{
		heroMoving[direction].OnMove();
		if(isMovingUp || isMovingRight || isMovingDown || isMovingLeft)
			CollisionWithWall(STEP_SIZE, map);
	}

	void Hero::SetDirection()
	{
		if (isMovingUp == true && isMovingRight == true)
			direction = 1;
		else if (isMovingDown == true && isMovingRight == true)
			direction = 3;
		else if (isMovingDown == true && isMovingLeft == true)
			direction = 5;
		else if (isMovingUp == true && isMovingLeft == true)
			direction = 7;
		else if (isMovingUp)
			direction = 0;
		else if (isMovingRight)
			direction = 2;
		else if (isMovingDown)
			direction = 4;
		else if (isMovingLeft)
			direction = 6;
	}

	void Hero::SetMovingDown(bool flag)
	{
		isMovingDown = flag;
	}

	void Hero::SetMovingLeft(bool flag)
	{
		isMovingLeft = flag;
	}

	void Hero::SetMovingRight(bool flag)
	{
		isMovingRight = flag;
	}

	void Hero::SetMovingUp(bool flag)
	{
		isMovingUp = flag;
	}

	void Hero::SetRolling(bool flag)
	{
		isRolling = flag;
	}

	void Hero::SetShooting(bool flag)
	{
		isShooting = flag;
	}

	void Hero::SetXY(int nx, int ny)
	{
		heroX = nx; heroY = ny;
	}

	void Hero::OnShow()
	{
		if (isShooting)
		{
			heroShooting[direction].SetTopLeft(SCREEN_SIZE_X / 2, SCREEN_SIZE_Y / 2);
			heroShooting[direction].ShowBitmap();
		}
		else if (isRolling)
		{
			heroRolling[direction].SetTopLeft(SCREEN_SIZE_X / 2, SCREEN_SIZE_Y / 2);
			heroRolling[direction].OnShow();
			if (heroRolling[direction].IsFinalBitmap())
			{
				isRolling = false;
			}
		}
		else if (isMovingUp || isMovingRight || isMovingDown || isMovingLeft)
		{
			heroMoving[direction].SetTopLeft(SCREEN_SIZE_X / 2, SCREEN_SIZE_Y / 2);
			heroMoving[direction].OnShow();
		}
		else
		{
			hero[direction].SetTopLeft(SCREEN_SIZE_X / 2, SCREEN_SIZE_Y / 2);
			hero[direction].ShowBitmap();
		}
	}
}