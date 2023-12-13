#include "Enemy.h"

Enemy::Enemy(){}

Enemy::~Enemy(){}

void Enemy::Initialize(Model* model, uint32_t textureHandle)
{
	assert(model);
	model_ = model;
	model_->SetTexHandle(textureHandle);
	worldTransform_.Initialize();
	// 敵の初期座標
	worldTransform_.translate = { 0.0f, 5.0f, 50.0f };
	// 最初の状態
	phaseState_ = new EnemyStateApproach();

}

void Enemy::Update()
{
	phaseState_->Update(this);

	// 弾更新
	for (bulletsItr_ = bullets_.begin();
		bulletsItr_ != bullets_.end(); ++bulletsItr_) {
		(*bulletsItr_)->Update();
	}

	// デスフラグの立ったやつを消す
	bullets_.remove_if([](std::unique_ptr<EnemyBullet>& bullet) {
		if (bullet->IsDead()) {
			return true;
		}
		return false;
	});

	// 行列の更新
	worldTransform_.UpdateMatrix();
}

void Enemy::Draw(const Camera& camera)
{
	model_->Draw(worldTransform_, camera);

	// 弾の描画
	for (bulletsItr_ = bullets_.begin();
		bulletsItr_ != bullets_.end(); ++bulletsItr_) {
		(*bulletsItr_)->Draw(camera);
	}

}

void Enemy::Move()
{
	worldTransform_.translate = Add(worldTransform_.translate, velocity_);
}

void Enemy::Fire()
{
	// 弾の速度
	const float kBulletSpeed = -1.0f;
	Vector3 velocity(0, 0, kBulletSpeed);

	// 弾を生成して初期化
	std::unique_ptr<EnemyBullet> bullet = std::make_unique<EnemyBullet>();
	bullet->Initialize(worldTransform_.translate, velocity);
	// 弾をセット
	bullets_.push_back(std::move(bullet));
}

void Enemy::changeState(IPhaseStateEnemy* newState)
{
	phaseState_ = newState;
}
