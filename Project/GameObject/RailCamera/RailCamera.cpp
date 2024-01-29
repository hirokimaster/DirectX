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

	camera_.farZ = 1000.0f;
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
	return CatmullRomPosition({ controlPoints_[1],controlPoints_[2],controlPoints_[3],controlPoints_[4] }, t);
}

Vector3 RailCamera::EyePosition(float t) const
{
	return CatmullRomPosition({ controlPoints_[0],controlPoints_[1],controlPoints_[2],controlPoints_[3] }, t);
}

void RailCamera::MoveOnRail(float dt)
{
	currentTime_ += dt;

	// 現在の位置を保存
	Vector3 oldEye = eye_;

	// 視点と注視点を更新
	eye_ = EyePosition(currentTime_);
	target_ = TargetPosition(currentTime_);
	// 移動ベクトル
	Vector3 moveForward_ = Normalize(Subtract(target_, oldEye));
	// 移動
	worldTransform_.translate = Add(worldTransform_.translate, moveForward_);

	forward_ = Normalize(Subtract(target_, eye_));
	worldTransform_.rotate.x = std::atan2(forward_.y, forward_.z);
	worldTransform_.rotate.y = std::atan2(forward_.z, forward_.x);
	worldTransform_.rotate.z = std::atan2(forward_.x, forward_.y);

	// ワールドトランスフォームのワールド行列再計算
	worldTransform_.matWorld = MakeAffineMatrix(
		worldTransform_.scale, worldTransform_.rotate, worldTransform_.translate);

	// ビュー行列を計算する
	camera_.matView = Inverse(worldTransform_.matWorld);
	worldTransform_.ParentUpdateMatrix();
	
}
