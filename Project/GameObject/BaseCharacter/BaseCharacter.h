#pragma once
#include <vector>
#include "Model/Model.h"

class BaseCharacter {
public: // メンバ関数
	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="models"></param>
	virtual void Initialize(const std::vector<Model*>& models, uint32_t texHandle);

	/// <summary>
	/// 更新
	/// </summary>
	virtual void Update();

	/// <summary>
	/// 描画
	/// </summary>
	/// <param name="camera"></param>
	virtual void Draw(const Camera& camera);

#pragma region getter
	/// <summary>
	/// ワールドトランスフォームを取得
	/// </summary>
	/// <returns></returns>
	const WorldTransform& GetWorldTransform() { return worldTransform_; }

#pragma endregion


protected:
	std::vector<Model*> models_; // モデルデータの配列
	std::vector<Model*>::iterator modelsItr_;
	WorldTransform worldTransform_;
};
