#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "CEraser.h"

namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// CEraser: Eraser class
	/////////////////////////////////////////////////////////////////////////////

	CEraser::CEraser()
	{
		Initialize();
	}

	int CEraser::GetX1()
	{
		return x;
	}

	int CEraser::GetY1()
	{
		return y;
	}

	int CEraser::GetX2()
	{
		return x + animation.Width();
	}

	int CEraser::GetY2()
	{
		return y + animation.Height();
	}

	void CEraser::Initialize()
	{
		const int X_POS = 280;
		const int Y_POS = 400;
		x = X_POS;
		y = Y_POS;
		direction = 1;
		isMovingLeft = isMovingRight = isMovingUp = isMovingDown = false;
	}

	void CEraser::LoadBitmap()
	{

		switch (direction)
		{
		case 1 :
			animation.AddBitmap(IDB_HEROFRONT, RGB(255, 255, 255));
			break;
		case 2 :
			animation.AddBitmap(IDB_HEROBACK, RGB(255, 255, 255));
			break;
		case 3 :
			animation.AddBitmap(IDB_HEROLEFT, RGB(255, 255, 255));
			break;
		case 4 :
			animation.AddBitmap(IDB_HERORIGHT, RGB(255, 255, 255));
			break;
		}
	}

	void CEraser::OnMove()
	{
		const int STEP_SIZE = 2;
		animation.OnMove();
		if (isMovingLeft) {
			//animation.AddBitmap(IDB_HEROLEFT, RGB(255, 255, 255));
			//direction = 3;
			x -= STEP_SIZE;
		}
		if (isMovingRight) {
			//animation.AddBitmap(IDB_HERORIGHT, RGB(255, 255, 255));
			//direction = 4;
			x += STEP_SIZE;
		}
		if (isMovingUp) {
			//animation.AddBitmap(IDB_HEROBACK, RGB(255, 255, 255));
			//direction = 2;
			y -= STEP_SIZE;
		}
		if (isMovingDown) {
			//animation.AddBitmap(IDB_HEROFRONT, RGB(255, 255, 255));
			//direction = 1;
			y += STEP_SIZE;
		}
	}

	void CEraser::SetMovingDown(bool flag,int indirection)
	{
		direction = indirection;
		isMovingDown = flag;
	}

	void CEraser::SetMovingLeft(bool flag, int indirection)
	{
		direction = indirection;
		isMovingLeft = flag;
	}

	void CEraser::SetMovingRight(bool flag, int indirection)
	{
		direction = indirection;
		isMovingRight = flag;
	}

	void CEraser::SetMovingUp(bool flag, int indirection)
	{
		direction = indirection;
		isMovingUp = flag;
	}

	void CEraser::SetXY(int nx, int ny)
	{
		x = nx; y = ny;
	}

	void CEraser::OnShow()
	{
		animation.SetTopLeft(x, y);
		animation.OnShow();
	}
}