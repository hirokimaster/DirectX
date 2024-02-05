#pragma once
#include "application/Scene/IScene/IScene.h"
#include "engine/Sprite/Sprite.h"
#include "engine/Model/Model.h"

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

private:
	Camera camera_{};
	WorldTransform worldTransformBunny_{};
	WorldTransform worldTransformGround_{};
	std::unique_ptr<Model> modelBunny_;
	std::unique_ptr<Model> modelGround_;
	uint32_t texHandleGround_ = 0;
	uint32_t texHandleUVChecker_ = 0;
	bool isLightingBunny_;
	bool isLightingGround_;
	Light light_{};
	PointLight pointLight_{};
	SpotLight spotLight_{};
	Material materialBunny_{};
	Material materialGround_{};
	DirectionalLight lightingPropertyBunny_{};
	DirectionalLight lightingPropertyGround_{};
};
