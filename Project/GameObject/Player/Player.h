#include "Model/Model.h"
#include <cassert>
#include "Input.h"
#include "Player/PlayerBullet.h"
#include "Utility/CollisionManager/Collider/Collider.h"

class Player : public Collider {
public:

	Player();
	~Player();

	void Initialize(Model* model, Vector3 position, uint32_t texHandle);

	void Update();

	void Draw(const Camera& camera);

	void Rotate();

	void Attack();

	void OnCollision()override;

	// getter
	Vector3 GetWorldPosition()override;
	const std::list<std::unique_ptr<PlayerBullet>>& GetBullets() const { return bullets_; }

	// setter
	void SetParent(const WorldTransform* parent) { worldTransform_.parent = parent; }

private:

	Model* model_ = nullptr;
	WorldTransform worldTransform_ = {};
	const float moveSpeed = 0.2f;
	std::list<std::unique_ptr<PlayerBullet>> bullets_;
	std::list<std::unique_ptr<PlayerBullet>>::iterator bulletsItr_;

};