namespace game_framework
{
	class Arrow
	{
	public:
		Arrow();
		void Initialize();
		void LoadBitmap();
		void LoadHeroPosition(int inX, int inY, int direction);
		int returnArrowX();
		int returnArrowY();
		bool IsShooted();
		int returnShootStyle();
		void OnMove();
		void OnShow();
		void SetShoot(bool flag);
	protected:
		const int SHOOT_TIME = 12;
		int BACK_SPEED = 5;
		CMovingBitmap arrow;
		CAnimation moveArrow = CAnimation(1);
		int shootSpeed;
		int shootTime;
		double dx, dy;
		double changX, changY;
		bool isShoot;
		int direction, shootdirection;

		int waitTime;
		int shootStyle;
		int arrowX, arrowY;
		int heroX, heroY;
	};
}
