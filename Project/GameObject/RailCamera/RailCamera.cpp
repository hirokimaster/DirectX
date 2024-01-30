#include "RailCamera/RailCamera.h"

/// <summary>
/// 初期化
/// </summary>
void RailCamera::Initialize(const Vector3& position, const Vector3& rotate) {

	worldTransform_.Initialize();
	// ワールドトランスフォーム
	worldTransform_.translate = position;
	worldTransform_.rotate = rotate;
	worldTransform_.scale = { 1.0f, 1.0f, 1.0f };

	// ビュープロジェクションの初期化
	camera_.Initialize();
}

/// <summary>
/// 更新
/// </summary>
void RailCamera::Update() {

	MoveOnRail(kDeltaTime);

	// カメラの座標を画面表示する処理
	ImGui::Begin("Camera");
	ImGui::SliderFloat3("CmeraTranslation ", &worldTransform_.translate.x, -50.0f, 50.0f);
	ImGui::SliderFloat3("CmeraRotate ", &worldTransform_.rotate.x, 0.0f, 10.0f);
	ImGui::End();

}

Vector3 RailCamera::TargetPosition(float t) const
{
	return CatmullRomPosition(controlPoints_,t + 0.3f);
}

Vector3 RailCamera::EyePosition(float t) const
{
	return CatmullRomPosition(controlPoints_, t);
}

void RailCamera::MoveOnRail(float dt)
{
	currentTime_ += dt;
	
	// 視点と注視点を更新
	eye_ = EyePosition(currentTime_);
	target_ = TargetPosition(currentTime_);

	// 移動
	worldTransform_.translate = eye_;

	forward_ = Normalize(Subtract(target_, eye_));

	float velocityXZ = sqrt(forward_.x * forward_.x + forward_.z * forward_.z);

	worldTransform_.rotate.y = std::atan2(forward_.x, forward_.z);
	worldTransform_.rotate.x = std::atan2(-forward_.y, velocityXZ);


	// ワールドトランスフォームのワールド行列再計算
	worldTransform_.matWorld = MakeAffineMatrix(
		worldTransform_.scale, worldTransform_.rotate, worldTransform_.translate);


	ImGui::Begin("視点");
	ImGui::Text("eye_ = %f %f %f", eye_.x, eye_.y, eye_.z);
	ImGui::Text("target_ = %f %f %f", target_.x, target_.y, target_.z);
	ImGui::End();

	// ビュー行列を計算する
	camera_.matView = Inverse(worldTransform_.matWorld);
	worldTransform_.ParentUpdateMatrix();
	
}
