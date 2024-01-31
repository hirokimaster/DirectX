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
	// 曲線レールカメラ用の制御点
	controlPoints_ = {

		{0,0,2},
		{0,0,4},
		{0,0,8},
		{0,5,16},
		{0,0,32},
		{0,5,64},
		{0,10,96},
		{-0,5,128},
		{-0,0,0},

	};

	// ビュープロジェクションの初期化
	camera_.Initialize();
}

/// <summary>
/// 更新
/// </summary>
void RailCamera::Update() {

	UpdateEyePosition(kDeltaTime);
	UpdateTargetPosition(kDeltaTime);
	MoveOnRail();

#ifdef _DEBUG
	// カメラの座標を画面表示する処理
	ImGui::Begin("Camera");
	ImGui::SliderFloat3("CmeraTranslation ", &worldTransform_.translate.x, -50.0f, 50.0f);
	ImGui::SliderFloat3("CmeraRotate ", &worldTransform_.rotate.x, 0.0f, 10.0f);
	ImGui::End();
#endif // _DEBUG

}

void RailCamera::MoveOnRail()
{
	worldTransform_.translate = eye_;

	forward_ = Normalize(Subtract(target_, eye_));

	float velocityXZ = sqrt(forward_.x * forward_.x + forward_.z * forward_.z);

	worldTransform_.rotate.y = std::atan2(forward_.x, forward_.z);
	worldTransform_.rotate.x = std::atan2(-forward_.y, velocityXZ);

	// 行列再計算
	worldTransform_.matWorld = MakeAffineMatrix(
		worldTransform_.scale, worldTransform_.rotate, worldTransform_.translate);

	Matrix4x4 rotateX = MakeRotateXMatrix(worldTransform_.rotate.x);
	Matrix4x4 rotateY = MakeRotateXMatrix(worldTransform_.rotate.y);
	Matrix4x4 rotateZ = MakeRotateXMatrix(worldTransform_.rotate.z);

	Matrix4x4 rotateMatrix = Multiply(Multiply(rotateX, rotateY), rotateZ);
	Matrix4x4 scale = MakeScaleMatrix(worldTransform_.scale);
	Matrix4x4 translate = MakeTranslateMatrix(worldTransform_.translate);

	worldTransform_.matWorld = Multiply(scale, Multiply(rotateMatrix, translate));
	
	// ビュー行列を計算する
	camera_.matView = Inverse(worldTransform_.matWorld);
	worldTransform_.ParentUpdateMatrix();

#ifdef _DEBUG
	ImGui::Begin("視点");
	ImGui::Text("eye_ = %f %f %f", eye_.x, eye_.y, eye_.z);
	ImGui::Text("target_ = %f %f %f", target_.x, target_.y, target_.z);
	ImGui::End();
#endif // _DEBUG
	
}

void RailCamera::UpdateTargetPosition(float dt)
{
	currentTimeTarget_ += dt;
	target_ = CatmullRomPosition(controlPoints_, currentTimeTarget_); // 注視点を更新
}

void RailCamera::UpdateEyePosition(float dt)
{
	currentTimeEye_ += dt;
	eye_ = CatmullRomPosition(controlPoints_, currentTimeEye_); // 視点を更新
}
