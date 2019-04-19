namespace game_framework
{
	class Arrow
	{
	public:
		Arrow();
		void Initialize();
		void LoadBitmap();
		int GetX();
		int GetY();
		
		void SetShoot(bool flag);
		bool IsShooted();
		int GetHoldTime();
		int GetShootTime();

		void ShootMode(int& arrowMode, const int DIRECTION, map<string, int>& position);
		void SetShootDirection(const int direction);
		bool IsCD();

		void OnShow(int& arrowMode, map<string, int>& position);
	private:
		void OnShoot(const int DIRECTION, map<string, int>& position);
		void Shooting();
		bool OnReturn(map<string, int>& position);

		CMovingBitmap arrow;
		int shootDirection;

		CAnimation moveArrow = CAnimation(1);
		int arrowX = 0, arrowY = 0;
		int waitTime = 0;
		const int BACK_SPEED = 5;
		int shootSpeed = 40;
		int shootTime = 0;
		int holdTime = 0;
		bool isShoot = false;
	};
}
