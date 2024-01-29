#include "RailCamera/RailCamera.h"

/// <summary>
/// 初期化
/// </summary>
void RailCamera::Initialize(const Vector3& position, const Vector3& rotate) {

	//worldTransform_.Initialize();
	// ワールドトランスフォーム
	worldTransform_.translate = position;
	worldTransform_.rotate = rotate;
	worldTransform_.scale = { 1.0f, 1.0f, 1.0f };

	controlPoints_ = {
		{0,0,0},
		{10.0f,10.0f,0},
		{10.0f,15.0f,0},
		{20.0f,15.0f,0},
		{20.0f,0,0},
		{30.0f,0,0}
	};

	camera_.farZ = 2000;
	// ビュープロジェクションの初期化
	camera_.Initialize();
}

/// <summary>
/// 更新
/// </summary>
void RailCamera::Update() {

	//std::vector<Vector3> points;
	//const size_t segmentCount = 100;
	//for (size_t i = 0; i < segmentCount + 1; ++i) {
	//	float t = 1.0f / segmentCount * i;
	//	Vector3 pos = CatmullRomPosition(controlPoints_, t);
	//}

	//for (size_t i = 0; i < points.size() - 1; ++i) {
	//	//eye_ = controlPoints_[0];
	//	//target_ = controlPoints_[1];
	//}

	worldTransform_.translate = eye_;
	forward_ = Subtract(target_, eye_);

	worldTransform_.rotate.x = std::atan2(forward_.y, forward_.z);
	worldTransform_.rotate.y = std::atan2(forward_.z, forward_.x);
	worldTransform_.rotate.z = std::atan2(forward_.x, forward_.y);

	// ビュー行列を計算する
	camera_.matView = Inverse(worldTransform_.matWorld);

	worldTransform_.UpdateMatrix();

	// 移動
	const float cameraSpeed = -0.5f; // 移動スピード
	worldTransform_.translate = Add(worldTransform_.translate, velocity_);

	// 回転
	const float kRotSpeed = 0.03f; // 回転速さ[ラジアン/frame]
	worldTransform_.rotate = Add(worldTransform_.rotate, rotate_);

	// カメラの座標を画面表示する処理
	ImGui::Begin("Camera");
	ImGui::SliderFloat3("CmeraTranslation ", &worldTransform_.translate.x, -50.0f, 50.0f);
	ImGui::SliderFloat3("CmeraRotate ", &worldTransform_.rotate.x, 0.0f, 10.0f);
	ImGui::End();

}