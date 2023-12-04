#pragma once
#include "Sprite.h"
#include "Triangle.h"
#include "Model.h"
#include "ModelSphere.h"
#include "ModelCube.h"
#include "Input.h"
#include "Inputhandler/InputHandler.h"
#include "ImGuiManager/ImGuiManager.h"
#include "IScene/IScene.h"
#include "Player/Player.h"
#include "ICommand/ICommand.h"

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
	ViewProjection viewProjection_;
	std::unique_ptr<Player> player_;
	std::unique_ptr<Model> modelPlayer_;
	uint32_t texHandlePlayer_ = 0;
	InputHandler* inputHandler_ = nullptr;
	ICommand* command_ = nullptr;

};
