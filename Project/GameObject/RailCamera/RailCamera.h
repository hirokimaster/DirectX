#pragma once
#include "Camera.h"
#include "Model/Model.h"

class RailCamera {
public:
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(const Vector3& position, const Vector3& rotate);

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// viewProjection取得関数
	/// </summary>
	const Camera& GetCamera() { return camera_; }

	/// <summary>
	/// worldTransform取得
	/// </summary>
	const WorldTransform& GetWorldTransform() { return worldTransform_; }

	Vector3 TargetPosition(float t) const;

	Vector3 EyePosition(float t)const;

	void MoveOnRail(float dt);

private:
	// ワールド変換データ
	WorldTransform worldTransform_;
	// ビュープロジェクション
	Camera camera_;
	// 移動速度
	Vector3 velocity_ = { 0.0f, 0.0f, 0.0f };
	// 角度
	Vector3 rotate_ = { 0.0f, 0.0f, 0.0f };
	// 曲線レールカメラ用の点
	std::vector<Vector3> controlPoints_ = {
		{0.0f, 0.0f, 0.0f},
		{1.0f, 1.0f, 1.0f},
		{2.0f, -1.0f, 2.0f},
		{3.0f, 0.0f, 3.0f},
		{4.0f, 1.0f, 4.0f},
		{5.0f, 0.0f, 5.0f},
	};

	Vector3 eye_{};
	Vector3 target_{};
	Vector3 forward_{};
	// カメラの進行時間
	float currentTime_ = 0.0f;
	const float kDeltaTime = 1.0f / 960.0f;
};
