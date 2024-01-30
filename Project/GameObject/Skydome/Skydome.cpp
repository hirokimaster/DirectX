#include "Skydome/Skydome.h"
#include <cassert>

/// <summary>
/// 初期化
/// </summary>
void Skydome::Initialize(Model* model, uint32_t texHandle) {
	model_ = model;
	model_->SetTexHandle(texHandle);
	// ワールドトランスフォームの初期化
	worldTransform_.Initialize();

	// 敵の初期座標
	worldTransform_.translate = { 0.0f, 0.0f, 0.0f };
	worldTransform_.scale = { 300.0f, 300.0f, 300.0f };

};


/// <summary>
/// 更新
/// </summary>
void Skydome::Update() {

	// 行列の更新
	worldTransform_.UpdateMatrix();
};

/// <summary>
/// 描画
/// </summary>
void Skydome::Draw(const Camera& camera) {
	model_->Draw(worldTransform_, camera);
};