#pragma once
#include "Model/Model.h"

class EnemyBullet{
public:
	// 初期化
	void Initialize(const Vector3& position, const Vector3& velocity);

	// 更新
	void Update();

	// 描画
	void Draw(const Camera& camera);

	// 弾のデスフラグ
	bool IsDead() const { return isDead_; }

	void OnCollision();

	Vector3 GetWorldPosition();

private:
	WorldTransform worldTransform_;
	std::unique_ptr<Model> model_;
	Vector3 velocity_;
	// 弾の寿命
	static const int32_t kLifeTime = 60 * 5;
	// デスタイマー
	int32_t deathTimer_ = kLifeTime;
	// デスフラグ
	bool isDead_ = false;
};

