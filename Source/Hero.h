namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// �o��class���ѥi�H����L�ηƹ�������l
	// �����N�i�H��g���ۤv���{���F
	/////////////////////////////////////////////////////////////////////////////

	class Hero
	{
	public:
		Hero();
		int  GetX1();					// ���l���W�� x �y��
		int  GetY1();					// ���l���W�� y �y��
		int  GetX2();					// ���l�k�U�� x �y��
		int  GetY2();					// ���l�k�U�� y �y��
		int  GetDirection();
		bool IsRolling();
		bool IsShooting();
		void Initialize();				// �]�w���l����l��
		void LoadBitmap();				// ���J�ϧ�
		void CollisionWithWall(int speed, vector<vector <int>>& map);
		void OnMove(vector<vector <int>> map);					// �������l
		void OnRoll(vector<vector <int>> map);
		void OnShow();
		void SetDirection();
		void SetMovingDown(bool flag);	// �]�w�O�_���b���U����
		void SetMovingLeft(bool flag);	// �]�w�O�_���b��������
		void SetMovingRight(bool flag); // �]�w�O�_���b���k����
		void SetMovingUp(bool flag);	// �]�w�O�_���b���W����
		void SetRolling(bool flag);
		void SetShooting(bool flag);
		void SetXY(int nx, int ny);		// �]�w���l���W���y��
	protected:
		const int NUMBER_DIRECTION = 8;
		const int STEP_SIZE = 5;
		CMovingBitmap hero[8];		// ���l���ʵe
		CMovingBitmap heroShooting[8];
		CAnimation heroMoving[8] = { 3,3,3,3,3,3,3,3 };
		CAnimation heroRolling[8];
		int direction;					// ���l���W���y��
		int heroX, heroY;
		bool isMovingDown;			// �O�_���b���U����
		bool isMovingLeft;			// �O�_���b��������
		bool isMovingRight;			// �O�_���b���k����
		bool isMovingUp;			// �O�_���b���W����
		bool isRolling;
		bool isShooting;
	};
}
