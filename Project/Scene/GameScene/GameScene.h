#pragma once
#include "Sprite.h"
#include "Triangle.h"
#include "Model.h"
#include "ModelSphere.h"
#include "ModelCube.h"
#include "Input.h"
#include "ImGuiManager/ImGuiManager.h"
#include "IScene/IScene.h"
#include "Player/Player.h"
#include "Skydome/Skydome.h"
#include "FollowCamera/FollowCamera.h"
#include "Ground/Ground.h"

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

private: // メンバ変数
	uint32_t texHandlePlayer_ = 0;
	uint32_t texHandleEnemy_ = 0;
	uint32_t texHandleSkydome_ = 0;
	uint32_t texHandleGround_ = 0;
	std::unique_ptr<Player> player_;
	std::unique_ptr<Model> modelPlayer_;
	std::unique_ptr<Skydome> skydome_;
	std::unique_ptr<Model> modelSkydome_;
	std::unique_ptr<FollowCamera> followCamera_;
	std::unique_ptr<Ground> ground_;
	std::unique_ptr<Model> modelGround_;
	Camera camera_;
};
