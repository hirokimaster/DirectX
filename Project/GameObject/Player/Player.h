#include "Model/Model.h"
#include <cassert>
#include "Input.h"
#include "Player/PlayerBullet.h"
#include "Sprite/Sprite.h"

class Player {
public:

	Player();
	~Player();

	void Initialize(Model* model,Vector3 pos, uint32_t texHandle);

	void Update(const Camera& camera);

	void Draw(const Camera& camera);

	void Rotate();

	void Attack();

	void DrawUI(const Camera& camera);

	void OnCollision();

	// 弾リストを取得
	const std::list<std::unique_ptr<PlayerBullet>>& GetBullets() const { return bullets_; }

	Vector3 GetWorldPosition();

	Vector3 GetWorldPosition3DReticle();

	void SetParent(const WorldTransform* parent);

private:

	Model* model_ = nullptr;
	WorldTransform worldTransform_ = {};
	const float moveSpeed = 0.2f;
	std::list<std::unique_ptr<PlayerBullet>> bullets_;
	std::list<std::unique_ptr<PlayerBullet>>::iterator bulletsItr_;
	WorldTransform worldTransform3DReticle_;
    std::unique_ptr<Sprite> sprite2DReticle_;
	uint32_t textureReticle_ = 0;
};