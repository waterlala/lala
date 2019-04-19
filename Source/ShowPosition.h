namespace game_framework {
	class ShowPosition
	{
	public:
		void getHeroPosition(int inX,int inY);
		void getBossPosition(int inX, int inY);
		void getMapPosition(int inX, int inY);
		void getArrowPosition(int inX, int inY);
		void Initialize();
		void LoadBitmap();
		void OnMove();
		void OnShow();
		void OnShowNumber(int inX, int inY, int inNumber);
		void OnShowChangShow(int inX, int inY, int inNumber);
	protected:
		CMovingBitmap number[11];
		int bossX, bossY;
		int heroX, heroY;
		int mapX, mapY;
		int arrowX, arrowY;
	};
}