#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "audio.h"
#include "gamelib.h"
#include "Boss.h"


namespace game_framework
{
Boss::Boss()
{
    Initialize();
}

void Boss::Initialize()
{
    nowBossX = 360;
    nowBossY = 400;
    bossTopX = -(int)(128 * 0.5);
    bossTopY = -(int)(96);
    bossBodyX = -(int)(48 * 0.5);
    bossBodyY = -(int)(88);
    bossShadowX = -(int)(64 * 0.5);
    bossShadowY = -( int)(40);
    time = 0;
    moveStyle = 0;
    FireNumber = 0;
    jumpWaitTime = 0;
    waitSleep = 15;
    deathTime = 100;
    death = false;
    skill = false;
    wakeup = false;
    skilltime = 0;

    for (int i = 0; i < 20; i++)
    {
        isFire[i] = false;
        FireTime[i] = 100;
    }
}
void Boss::LoadMapPosition(int inX, int inY)
{
    heroX = inX;
    heroY = inY;
    mapX = SCREEN_SIZE_X / 2 - inX;
    mapY = SCREEN_SIZE_Y / 2 - inY;
}
void Boss::LoadArrowPosition(int inX, int inY, int inS)
{
    arrowX = inX;
    arrowY = inY;
    shootStyle = inS;
}
void Boss::LoadBitmap()
{
    bossTop.LoadBitmap(IDB_BOSS_TOP, RGB(255, 255, 255));
    bossBody.LoadBitmap(IDB_BOSS_BODDY_1, RGB(255, 255, 255));
    bossShadow.LoadBitmap(IDB_BOSS_SHADOW, RGB(255, 255, 255));

    for (int i = 0; i < 20; i++)
    {
        bossFire[i].LoadBitmap(IDB_FIRE_BALL, RGB(255, 255, 255));
    }
}

int Boss::returnBossX()
{
    return nowBossX;
}
int Boss::returnBossY()
{
    return nowBossY;
}

void Boss::bossUp(int speedChangTime)
{
    bossTopY -= (int)((speedChangTime - time) * 1.2);
    bossBodyY -= (int)((speedChangTime - time) * 0.9);
    time += 1;

    if (time == speedChangTime)
    {
        time = 0;
        moveStyle = 1;
    }
}
void Boss::bossDown(int speedChangTime)
{
    bossTopY += (int)(time * 1.2);
    bossBodyY += (int)(time * 0.9);
    time += 1;

    if (time == speedChangTime + 1)
    {
        time = 0;
        moveStyle = 2;
    }
}

bool Boss::arrowHitBody()
{
    if (arrowX >= nowBossX + bossBodyX + 5 && arrowX <= nowBossX + bossBodyX + bossBody.Width() - 5 && arrowY >= nowBossY + bossBodyY + 5 && arrowY <= nowBossY + bossBodyY + bossBody.Height() - 5)
    {
        return true;
    }
    else
    {
        return false;
    }
}
bool Boss::arrowHitTop()
{
    if (arrowX >= nowBossX + bossTopX + 10 && arrowX <= nowBossX + bossTopX + bossTop.Width() - 10 && arrowY >= nowBossY + bossTopY + 10 && arrowY <= nowBossY + bossTopY + bossTop.Height() - 10)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void Boss::Fire()
{
    for (int i = 0; i < 4; i++)
    {
        isFire[FireNumber + i] = true;
        bossFireX[FireNumber + i] = nowBossX - (int)(bossFire[0].Height() * 0.5);
        bossFireY[FireNumber + i] = nowBossY - (int)(bossShadow.Height() * 0.5) - (int)(bossFire[0].Height() * 0.5);
    }

    FireNumber += 4;

    if (FireNumber == 20)
    {
        FireNumber = 0;
    }
}



void Boss::OnMove()
{
    if (isSleep)
    {
        if (arrowHitTop())
        {
            wakeup = true;
        }

        if (wakeup)
        {
            waitSleep--;

            if (waitSleep <= 0)
            {
                bossTopY -= 15;
                isSleep = false;
            }
        }
    }
    else
    {
        if (death)
        {
            nowBossX = 360;
            nowBossY = 400;
            bossTopX = -(int)(128 * 0.5);
            bossTopY = -(int)(96);
            bossBodyX = -(int)(48 * 0.5);
            bossBodyY = -(int)(88);
            bossShadowX = -(int)(64 * 0.5);
            bossShadowY = -(int)(40);
            time = 0;
            moveStyle = 0;
            FireNumber = 0;
            jumpWaitTime = 0;
            waitSleep = 15;
            deathTime = 100;
            death = false;
            skill = false;
            wakeup = false;
            skilltime = 0;
            bossTopY -= 15;

            for (int i = 0; i < 20; i++)
            {
                isFire[i] = false;
                FireTime[i] = 100;
            }

            if (deathTime <= 0)
            {
                death = false;
            }

            deathTime--;
        }
        else
        {
            switch (moveStyle)
            {
                case 0:
                    dx = nowBossX - heroX;
                    dy = nowBossY - (int)(bossShadow.Height() * 0.5) - heroY;

                    if (abs(dx) >= 10 || abs(dy) >= 10)
                    {
                        changX = 5 * (dx / (sqrt(dx * dx + dy * dy)));
                        changY = 5 * (dy / (sqrt(dx * dx + dy * dy)));
                    }

                    nowBossX -= (int)changX;
                    nowBossY -= (int)changY;
                    jumpWaitTime = 0;
                    bossUp(20);
                    break;

                case 1:
                    dx = nowBossX - heroX;
                    dy = nowBossY - (int)(bossShadow.Height() * 0.5) - heroY;

                    if (abs(dx) >= 10 || abs(dy) >= 10)
                    {
                        changX = 5 * (dx / (sqrt(dx * dx + dy * dy)));
                        changY = 5 * (dy / (sqrt(dx * dx + dy * dy)));
                    }

                    nowBossX -= (int)changX;
                    nowBossY -= (int)changY;
                    bossDown(20);
                    break;

                case 2:
                    if (arrowHitBody())
                    {
                        death = true;
                        deathTime = 100;
                    }

                    if (jumpWaitTime < 5)
                        bossTopY += 2;
                    else if (jumpWaitTime < 10)
                    {
                        bossTopY -= 2;
                    }
                    else if (jumpWaitTime == 10)
                    {
                        Fire();
                        moveStyle = 0;
                    }

                    jumpWaitTime++;
                    break;
            }

            for (int i = 0; i < 20; i = i + 4)
            {
                if (isFire[i])
                {
                    if (i == 4 || i == 12)
                    {
                        bossFireX[i] += 5;
                        bossFireY[i] += 0;
                        bossFireX[i + 1] += (-5);
                        bossFireY[i + 1] += 0;
                        bossFireX[i + 2] += 0;
                        bossFireY[i + 2] += 5;
                        bossFireX[i + 3] += 0;
                        bossFireY[i + 3] += (-5);
                    }
                    else if (i == 0 || i == 8 || i == 16)
                    {
                        bossFireX[i] += (int)(5 / 1.414);
                        bossFireY[i] += (int)(5 / 1.414);
                        bossFireX[i + 1] += (int)(-5 / 1.414);
                        bossFireY[i + 1] += (int)(-5 / 1.414);
                        bossFireX[i + 2] += (int)(5 / 1.414);
                        bossFireY[i + 2] += (int)(-5 / 1.414);
                        bossFireX[i + 3] += (int)(-5 / 1.414);
                        bossFireY[i + 3] += (int)(5 / 1.414);
                    }
                }
            }

            for (int i = 0; i < 20; i++)
            {
                if (isFire[i])
                {
                    FireTime[i]--;

                    if (FireTime[i] == 0)
                    {
                        isFire[i] = false;
                        FireTime[i] = 100;
                    }
                }
            }
        }
    }
}

void Boss::OnShow()
{
    double dspeedtime;
    dspeedtime = time;

    if (!death)
    {
        for (int i = 0; i < 20; i = i + 4)
        {
            if (isFire[i])
            {
                bossFire[i].SetTopLeft(bossFireX[i] + mapX, bossFireY[i] + mapY);
                bossFire[i].ShowBitmap();
                bossFire[i + 1].SetTopLeft(bossFireX[i + 1] + mapX, bossFireY[i + 1] + mapY);
                bossFire[i + 1].ShowBitmap();
                bossFire[i + 2].SetTopLeft(bossFireX[i + 2] + mapX, bossFireY[i + 2] + mapY);
                bossFire[i + 2].ShowBitmap();
                bossFire[i + 3].SetTopLeft(bossFireX[i + 3] + mapX, bossFireY[i + 3] + mapY);
                bossFire[i + 3].ShowBitmap();
            }
        }

        bossTop.SetTopLeft(nowBossX + bossTopX + mapX, nowBossY + bossTopY + mapY);
        bossBody.SetTopLeft(nowBossX + bossBodyX + mapX, nowBossY + bossBodyY + mapY);
        bossBody.ShowBitmap();
        bossTop.ShowBitmap();
    }
}
void Boss::shadowOnShow()
{
    double dspeedtime;
    dspeedtime = time;

    if (!death)
    {
        bossShadow.SetTopLeft(nowBossX + bossShadowX + mapX, nowBossY + bossShadowY + mapY);
        bossShadow.ShowBitmap();
    }
}
}