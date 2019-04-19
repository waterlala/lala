namespace game_framework {
	class ShowPosition
	{
	public:
		void LoadBitmap();
		void OnShow(map<string, int> position, int& arrowMode, int holdTime, int shootTime);
		void OnShowNumber(int inX, int inY, int inNumber);
		void OnShowChangShow(int inX, int inY, int inNumber);
	protected:
		CMovingBitmap number[11];
		int mapX, mapY;
	};
}