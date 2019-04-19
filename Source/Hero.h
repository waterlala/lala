namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// 這個class提供可以用鍵盤或滑鼠控制的擦子
	// 看懂就可以改寫成自己的程式了
	/////////////////////////////////////////////////////////////////////////////

	class Hero
	{
	public:
		Hero();
		int  GetX1();					// 擦子左上角 x 座標
		int  GetY1();					// 擦子左上角 y 座標
		int  GetX2();					// 擦子右下角 x 座標
		int  GetY2();					// 擦子右下角 y 座標
		int  GetDirection();
		bool IsRolling();
		bool IsShooting();
		void Initialize();				// 設定擦子為初始值
		void LoadBitmap();				// 載入圖形
		void CollisionWithWall(int speed, vector<vector <int>>& map);
		void OnMove(vector<vector <int>> map);					// 移動擦子
		void OnRoll(vector<vector <int>> map);
		void OnShow();
		void SetDirection();
		void SetMovingDown(bool flag);	// 設定是否正在往下移動
		void SetMovingLeft(bool flag);	// 設定是否正在往左移動
		void SetMovingRight(bool flag); // 設定是否正在往右移動
		void SetMovingUp(bool flag);	// 設定是否正在往上移動
		void SetRolling(bool flag);
		void SetShooting(bool flag);
		void SetXY(int nx, int ny);		// 設定擦子左上角座標
	protected:
		const int NUMBER_DIRECTION = 8;
		const int STEP_SIZE = 5;
		CMovingBitmap hero[8];		// 擦子的動畫
		CMovingBitmap heroShooting[8];
		CAnimation heroMoving[8] = { 3,3,3,3,3,3,3,3 };
		CAnimation heroRolling[8];
		int direction;					// 擦子左上角座標
		int heroX, heroY;
		bool isMovingDown;			// 是否正在往下移動
		bool isMovingLeft;			// 是否正在往左移動
		bool isMovingRight;			// 是否正在往右移動
		bool isMovingUp;			// 是否正在往上移動
		bool isRolling;
		bool isShooting;
	};
}
