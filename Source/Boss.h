namespace game_framework {

	class Boss
	{
	public:
		Boss();
		void LoadMapPosition(int mapX, int mapY);
		void LoadArrowPosition(int arrowX, int arrowY,int shootStyle);
		void Initialize();				
		void LoadBitmap();

		int returnBossX();
		int returnBossY();
		void OnMove();				
		void OnShow();
		void shadowOnShow();
		void Fire();

		void bossUp(int speedChangTime);
		void bossDown(int speedChangTime);
		bool arrowHitBody();
		bool arrowHitTop();
		
	protected:
		CAnimation bossBodyMove = CAnimation(5);
		CMovingBitmap bossBody;		
		CMovingBitmap bossTop;
		CMovingBitmap bossShadow;
		CMovingBitmap bossFire[20];
		int bossFireX[20],bossFireY[20];
		bool isFire[20];
		int FireTime[20];
		int FireNumber;
		int time;
		int shootStyle;
		int bossTopX, bossTopY;
		int bossBodyX, bossBodyY;
		int bossShadowX, bossShadowY;
		int heroX, heroY;
		int speed;
		int skillThree;
		int nowBossX, nowBossY;
		bool skill;
		int skilltime;
		bool death;
		bool isSleep=true;
		bool wakeup;
		int jumpWaitTime;
		int waitSleep;
		int deathTime;
		int arrowX, arrowY;
		int bossX, bossY;
		int mapX, mapY;
		int killX, killY;
		int moveStyle;
		double dx, dy;
		double changX, changY;
		
	};
}