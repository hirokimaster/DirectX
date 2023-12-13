#include "Model/Model.h"
#include <cassert>
#include "Input.h"
#include "Player/PlayerBullet.h"

class Player {
public:

	Player();
	~Player();

	void Initialize(Model* model, uint32_t texHandle);

	void Update();

	void Draw(const Camera& camera);

	void Rotate();

	void Attack();

private:

	Model* model_ = nullptr;
	WorldTransform worldTransform_ = {};
	const float moveSpeed = 0.2f;
	std::list<std::unique_ptr<PlayerBullet>> bullets_;
	std::list<std::unique_ptr<PlayerBullet>>::iterator bulletsItr_;

};