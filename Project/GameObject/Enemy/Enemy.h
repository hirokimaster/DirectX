#pragma once
#include "Model.h"
#include "Enemy/PhaseState/EnemyStateApproach.h"
#include "Enemy/EnemyBullet.h"
#include "Utility/CollisionManager/Collider/Collider.h"

// 行動フェーズ
enum class Phase {
    Approach, // 接近する
    Leave,    // 離脱する

};

class Player;

class Enemy : public Collider{
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

	// 攻撃
	void Fire();

	// 状態変更
	void changeState(IPhaseStateEnemy* newState);

	void OnCollision()override;

	// デスフラグ
	bool IsDead() const { return isDead_; }

	// getter
	Vector3 GetVelocity() { return velocity_; }
	Vector3 GetPosition() { return worldTransform_.translate; }
	Vector3 GetWorldPosition()override;
	// 弾リストを取得
	const std::list<std::unique_ptr<EnemyBullet>>& GetBullets() const { return bullets_; }

	// setter
	void SetVelocity(Vector3 velocity) {velocity_ = velocity; }
	void SetPlayer(Player* player) { player_ = player; }

private:
	WorldTransform worldTransform_;
	Model* model_ = nullptr;
	std::list<std::unique_ptr<EnemyBullet>> bullets_;
	std::list<std::unique_ptr<EnemyBullet>>::iterator bulletsItr_;
	int32_t shotTimer_ = 0;
	Vector3 velocity_{};
	IPhaseStateEnemy* phaseState_;
	Player* player_ = nullptr;
	bool isDead_ = false;
};

