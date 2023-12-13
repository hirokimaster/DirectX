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
	// 行列の更新
	worldTransform_.UpdateMatrix();
}

void Enemy::Draw(const Camera& camera)
{
	model_->Draw(worldTransform_, camera);
}

void Enemy::Move()
{
	worldTransform_.translate = Add(worldTransform_.translate, velocity_);
}

void Enemy::changeState(IPhaseStateEnemy* newState)
{
	phaseState_ = newState;
}
