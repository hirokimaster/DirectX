#include "Enemy.h"
#include "Player/Player.h"

Enemy::Enemy(){}

Enemy::~Enemy(){}

void Enemy::Initialize(Model* model, uint32_t textureHandle)
{
	assert(model);
	model_ = model;
	model_->SetTexHandle(textureHandle);
	worldTransform_.Initialize();
	// 敵の初期座標
	worldTransform_.translate = { 0.0f, 5.0f, 80.0f };
	// 最初の状態
	phaseState_ = new EnemyStateApproach();
	SetCollosionAttribute(kCollisionAttributeEnemy);
	SetCollisionMask(kCollisionAttributePlayer);

}

void Enemy::Update()
{
	phaseState_->Update(this);

	// 弾更新
	for (bulletsItr_ = bullets_.begin();
		bulletsItr_ != bullets_.end(); ++bulletsItr_) {
		(*bulletsItr_)->SetPlayer(player_);
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
	assert(player_);

	// 弾の速度
	const float kBulletSpeed = 0.05f;

	Vector3 playerWorldPos = player_->GetWorldPosition(); // 自キャラのワールド座標を取得
	Vector3 enemyWorldPos = GetWorldPosition(); // 敵キャラのワールド座標を取得
	Vector3 diff = Subtract(playerWorldPos, enemyWorldPos); // 差分ベクトルを求める
	Normalize(diff); // 正規化
	Vector3 velocity = Multiply(kBulletSpeed, diff); // ベクトルの速度

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

void Enemy::OnCollision()
{
	isDead_ = true;
}

Vector3 Enemy::GetWorldPosition()
{
	// ワールド座標を入れる変数
	Vector3 worldPos;
	// ワールド行列の平行移動成分を取得（ワールド座標）
	worldPos.x = worldTransform_.matWorld.m[3][0];
	worldPos.y = worldTransform_.matWorld.m[3][1];
	worldPos.z = worldTransform_.matWorld.m[3][2];

	return worldPos;
}
