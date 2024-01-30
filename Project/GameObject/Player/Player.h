#include "Model/Model.h"
#include <cassert>
#include "Input.h"
#include "Player/PlayerBullet.h"
#include "Utility/CollisionManager/Collider/Collider.h"
#include "Sprite.h"

class Player : public Collider {
public:

	Player();
	~Player();

	void Initialize(Model* model, Vector3 position, uint32_t texHandle);

	void Update(const Camera& camera);

	void Draw(const Camera& camera);

	void Rotate();

	void Attack();

	void OnCollision()override;

	void Reticle(const Camera& camera, const Vector2& pos);

	void DrawUI(const Camera& camera);


	// getter
	Vector3 GetWorldPosition()override;
	const std::list<std::unique_ptr<PlayerBullet>>& GetBullets() const { return bullets_; }
	Vector3 GetWorldPosition3DReticle();

	// setter
	void SetParent(const WorldTransform* parent) { worldTransform_.parent = parent; }
	void SetParentPuropera(const WorldTransform* parent) { worldTransformPropera_.parent = parent; }

private:

	Model* model_ = nullptr;
	WorldTransform worldTransform_ = {};
	const float moveSpeed = 0.2f;
	std::list<std::unique_ptr<PlayerBullet>> bullets_;
	std::list<std::unique_ptr<PlayerBullet>>::iterator bulletsItr_;
	WorldTransform worldTransform3DReticle_;
	std::unique_ptr<Sprite> sprite2DReticle_;
	uint32_t textureReticle_ = 0;
	uint32_t texHandlePropera_ = 0;
	std::unique_ptr<Model> properaModel_;
	WorldTransform worldTransformPropera_{};

};