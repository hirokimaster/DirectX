#pragma once
#include "Model/Model.h"
#include "CollisionManager/Collider/Collider.h"

class PlayerBullet : public Collider{
public:

	void Initialize(const Vector3& position, const Vector3& velocity);

	void Update();

	void Draw(const Camera& camera);

	bool IsDead() const { return isDead_; }

	Vector3 GetWorldPosition()override;

	void OnCollision()override;

private:

	WorldTransform worldTransform_{};
	std::unique_ptr<Model> model_;
	Vector3 velocity_ = {};
	static const int32_t kLifeTime_ = 60 * 5;
	int32_t deathTimer_ = kLifeTime_;
	bool isDead_ = false;
};

