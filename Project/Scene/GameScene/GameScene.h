#pragma once
#include "Sprite.h"
#include "Model.h"
#include "Input.h"
#include "ImGuiManager/ImGuiManager.h"
#include "IScene/IScene.h"
#include "Player/Player.h"
#include "Enemy/Enemy.h"

/// <summary>
/// ゲームシーン
/// </summary>
class GameScene : public IScene {

public: // メンバ関数
	/// <summary>
	/// コンストクラタ
	/// </summary>
	GameScene();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~GameScene();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize()override;

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update()override;

	/// <summary>
	/// 描画
	/// </summary>
	void Draw()override;

	void CheckAllCollisions();

private: // メンバ変数
	Camera camera_ = {};
	std::unique_ptr<Model> modelPlayer_;
	std::unique_ptr<Player> player_;
	std::unique_ptr<Model> modelEnemy_;
	std::unique_ptr<Enemy> enemy_;
	std::list<std::unique_ptr<Enemy>>::iterator enemysItr_;
	std::list<std::unique_ptr<EnemyBullet>> enemyBullets_;
	uint32_t texHandlePlayer_ = 0;
	uint32_t texHandleEnemy_ = 0;
};
