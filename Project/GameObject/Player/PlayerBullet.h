#pragma once
#include "Model/Model.h"

class PlayerBullet{
public:

	void Initialize(const Vector3& position, const Vector3& velocity);

	void Update();

	void Draw(const Camera& camera);

	bool IsDead() const { return isDead_; }

	void OnCollision();

	Vector3 GetWorldPosition();

private:

	WorldTransform worldTransform_{};
	std::unique_ptr<Model> model_;
	Vector3 velocity_ = {};
	static const int32_t kLifeTime_ = 60 * 5;
	int32_t deathTimer_ = kLifeTime_;
	bool isDead_ = false;
};

