#include "RailCamera/RailCamera.h"

/// <summary>
/// 初期化
/// </summary>
void RailCamera::Initialize(const Vector3& position, const Vector3& rotate) {
	// ワールドトランスフォーム
	worldTransform_.translate = position;
	worldTransform_.rotate = rotate;
	worldTransform_.scale = { 1.0f, 1.0f, 1.0f };

	camera_.farZ = 2000;
	// ビュープロジェクションの初期化
	camera_.Initialize();
}

/// <summary>
/// 更新
/// </summary>
void RailCamera::Update() {

	// 移動
	const float cameraSpeed = -0.5f; // 移動スピード
	velocity_.z = cameraSpeed;
	//worldTransform_.translate = Add(worldTransform_.translate, velocity_);

	// 回転
	//const float kRotSpeed = 0.001f; // 回転速さ[ラジアン/frame]
	//rotate_.y = kRotSpeed;
	worldTransform_.rotate = Add(worldTransform_.rotate, rotate_);

	// ワールドトランスフォームのワールド行列再計算
	worldTransform_.matWorld = MakeAffineMatrix(
		worldTransform_.scale, worldTransform_.rotate, worldTransform_.translate);

	// カメラオブジェクトのワールド行列からビュー行列を計算する
	camera_.matView = Inverse(worldTransform_.matWorld);

}