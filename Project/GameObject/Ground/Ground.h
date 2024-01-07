#pragma once
#include "Model/Model.h"

class Ground {
public:
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(Model* model, uint32_t texHandle);

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw(const Camera& camera);
private:
	WorldTransform worldTransform_;
	Model* model_ = nullptr;

};
