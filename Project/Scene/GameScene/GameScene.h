#pragma once
#include "Sprite.h"
#include "Model.h"
#include "Input.h"
#include "ImGuiManager/ImGuiManager.h"
#include "IScene/IScene.h"
#include "Player/Player.h"
#include "Enemy/Enemy.h"
#include "RailCamera/RailCamera.h"
#include "Skydome/Skydome.h"
#include <random>

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

	void RandomSpawn();

private: // メンバ変数
	Camera camera_ = {};
	std::unique_ptr<Model> modelPlayer_;
	std::unique_ptr<Player> player_;
	std::unique_ptr<Model> modelEnemy_;
	std::list<std::unique_ptr<Enemy>> enemys_;
	std::list<std::unique_ptr<Enemy>>::iterator enemysItr_;
	std::list<std::unique_ptr<EnemyBullet>> enemyBullets_;
	std::unique_ptr<Skydome> skydome_;
	std::unique_ptr<Model> modelSkydome_;
	std::unique_ptr<RailCamera> railCamera_;
	std::unique_ptr<Sprite> hp_[3];
	std::unique_ptr<Sprite>	Ui_;
	uint32_t texHandlePlayer_ = 0;
	uint32_t texHandleEnemy_ = 0;
	uint32_t texHandleSkydome_ = 0;
	uint32_t texHandleUi_ = 0;
	uint32_t spawnTimer_ = 0;
	uint32_t playerLife_ = 3;
};
