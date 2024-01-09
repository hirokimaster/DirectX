#pragma once
#include "IScene/IScene.h"
#include <memory>

class GameManager
{
private:

	std::unique_ptr<IScene> sceneArr_[2];

	int currentSceneNo_; // 現在のシーン
	int prevSceneNo_; // 前のシーン


public:
	GameManager();
	~GameManager();

	void Run(); // ゲームループを呼び出す

	void Initialize(); // 初期化

	void Draw();
};
