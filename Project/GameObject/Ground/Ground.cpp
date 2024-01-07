#include "Ground/Ground.h"

/// <summary>
/// 初期化
/// </summary>
void Ground::Initialize(Model* model, uint32_t texHandle) {
	model_ = model;
	model_->SetTexHandle(texHandle);
	// ワールドトランスフォームの初期化
	worldTransform_.Initialize();

	// 敵の初期座標
	worldTransform_.translate = { 0.0f, -5.0f, 0.0f };	
	worldTransform_.scale = { 50.0f, 1.0f, 50.0f };

};


/// <summary>
/// 更新
/// </summary>
void Ground::Update() {

	// 行列の更新
	worldTransform_.UpdateMatrix();
};

/// <summary>
/// 描画
/// </summary>
void Ground::Draw(const Camera& camera) {
	model_->Draw(worldTransform_, camera);
};