#pragma once
constexpr int MAP_SIZE_X = 720;
constexpr int MAP_SIZE_Y = 800;
constexpr int BLOCK_SIZE = 16;

namespace game_framework {
	class CMap
	{
	public:
		CMap();
		void Initialize();				// �]�w���l����l��
		void LoadBitmap();				// ���J�ϧ�
		void OnShow(int heroX, int heroY);					// �N���l�ϧζK��e��
		const vector<vector<int>>& GetMap();
	protected:
		CMovingBitmap mapPic[7];
		int mapX, mapY;
		int screenX, screenY;
		const int NUMBER_BLOCK_X = MAP_SIZE_X / BLOCK_SIZE, NUMBER_BLOCK_Y = MAP_SIZE_Y / BLOCK_SIZE;
		vector<vector <int>> map;
	};
}