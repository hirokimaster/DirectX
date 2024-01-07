#pragma once
#include "Camera/Camera.h"
#include "WorldTransform.h"
#include "ImGuiManager/ImGuiManager.h"
#include "Input/Input.h"

class FollowCamera {
public:
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

#pragma region setter

	void SetTarget(const WorldTransform* target) { target_ = target; }

#pragma endregion

#pragma region getter

	Camera GetCamera() { return camera_; }

#pragma endregion

private:
	Camera camera_;
	const WorldTransform* target_ = nullptr;
};