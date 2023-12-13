#pragma once
#include "Model.h"
#include "Enemy/PhaseState/EnemyStateApproach.h"

// 行動フェーズ
enum class Phase {
    Approach, // 接近する
    Leave,    // 離脱する

};

class Enemy{
public:

	// コンストラクタ
	Enemy();

	// デストラクタ
	~Enemy();

	// 初期化
	void Initialize(Model* model, uint32_t textureHandle);

	// 更新
	void Update();

	// 描画
	void Draw(const Camera& camera);

	// 移動
	void Move();

	// 状態変更
	void changeState(IPhaseStateEnemy* newState);

	// getter
	Vector3 GetVelocity() { return velocity_; }
	Vector3 GetPosition() { return worldTransform_.translate; }

	// setter
	void SetVelocity(Vector3 velocity) {velocity_ = velocity; }

private:
	WorldTransform worldTransform_;
	Model* model_ = nullptr;
	Vector3 velocity_{};
	IPhaseStateEnemy* phaseState_;

};

