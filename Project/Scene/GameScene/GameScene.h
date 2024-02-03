#pragma once
#include "Sprite.h"
#include "Triangle.h"
#include "Model.h"
#include "ModelSphere.h"
#include "ModelCube.h"
#include "Input.h"
#include "ImGuiManager/ImGuiManager.h"
#include "IScene/IScene.h"

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
	Camera camera_{};
	WorldTransform worldTransformBunny_{};
	WorldTransform worldTransformGround_{};
	WorldTransform worldTransformPlane_{};
	std::unique_ptr<Model> modelBunny_;
	std::unique_ptr<Model> modelGround_;
	std::unique_ptr<Model> modelPlane_;
	uint32_t texHandleGround_ = 0;
	uint32_t texHandleUVChecker_ = 0;
	bool isLightingBunny_;
	bool isLightingGround_;
	Lightng lighting_{};
	PointLight pointLight_{};
	SpotLight spotLight_{};
	Material materialBunny_{};
	Material materialGround_{};
	DirectionalLight lightingPropertyBunny_{};
	DirectionalLight lightingPropertyGround_{};
	bool isPlaneDraw_;
};
