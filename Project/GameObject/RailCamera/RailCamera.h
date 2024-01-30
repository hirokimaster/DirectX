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

	/// <summary>
	/// レールカメラを動かす計算をする所
	/// </summary>
	void MoveOnRail();

	/// <summary>
	/// 注視点の更新
	/// </summary>
	/// <param name="dt"></param>
	void UpdateTargetPosition(float dt);

	/// <summary>
	/// 視点の更新
	/// </summary>
	/// <param name="dt"></param>
	void UpdateEyePosition(float dt);


private:
	// ワールド変換データ
	WorldTransform worldTransform_;
	// ビュープロジェクション
	Camera camera_;
	// 移動速度
	Vector3 velocity_ = { 0.0f, 0.0f, 0.0f };
	// 角度
	Vector3 rotate_ = { 0.0f, 0.0f, 0.0f };
	// 曲線レールカメラ用の制御点
	std::vector<Vector3> controlPoints_{};
	Vector3 eye_{};
	Vector3 target_{};
	Vector3 forward_{};
	// カメラの進行時間
	float currentTimeEye_ = 0.0f; // 視点用
	float currentTimeTarget_ = 0.2f;// 注視点用で経過時間を0.2早くしてずらす
	const float kDeltaTime = 1.0f / 1200.0f;
};
