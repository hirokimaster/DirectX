#include "EnemyBullet.h"
#include "Player/Player.h"

// 初期化
void EnemyBullet::Initialize(const Vector3& position, const Vector3& velocity) {
	
	model_.reset(Model::CreateObj("cube.obj"));
	// テクスチャ読み込み
	uint32_t textureHandle = TextureManager::Load("resources/circle.png");
	model_->SetTexHandle(textureHandle);

	// ワールドトランスフォームの初期化
	worldTransform_.Initialize();
	// 初期座標をセット
	worldTransform_.translate = position;
	// 速度
	velocity_ = velocity;

	worldTransform_.rotate.y = std::atan2(velocity_.x, velocity_.z);

	Vector3 velocityXZ = { velocity_.x, 0.0f,velocity_.z };

	float veloXZ = Length(velocityXZ);

	worldTransform_.rotate.z = std::atan2(-velocity_.y, veloXZ);

	SetCollosionAttribute(kCollisionAttributeEnemy);
	SetCollisionMask(kCollisionAttributePlayer);

}

// 更新
void EnemyBullet::Update() {

	worldTransform_.translate = Add(worldTransform_.translate, velocity_);
	// ワールドトランスフォームの更新
	worldTransform_.UpdateMatrix();

	if (--deathTimer_ <= 0) {
		isDead_ = true;
	}

	Vector3 toPlayer;
	toPlayer = Subtract(player_->GetWorldPosition(), GetWorldPosition());

	float t = 0.01f;

	// 正規化
	Normalize(toPlayer);
	Normalize(velocity_);

	velocity_ = SLerp(toPlayer, GetWorldPosition(), t);

	worldTransform_.rotate.y = std::atan2(velocity_.x, velocity_.z);

	Vector3 velocityXZ = { velocity_.x, 0.0f, velocity_.z };

	float veloXZ = Length(velocityXZ);

	worldTransform_.rotate.z = std::atan2(-velocity_.y, veloXZ);


}

// 描画
void EnemyBullet::Draw(const Camera& camera) {
	// モデルの描画
	model_->Draw(worldTransform_, camera);

}

void EnemyBullet::OnCollision()
{
	isDead_ = true;
}

Vector3 EnemyBullet::GetWorldPosition()
{
	// ワールド座標を入れる変数
	Vector3 worldPos;
	// ワールド行列の平行移動成分を取得（ワールド座標）
	worldPos.x = worldTransform_.matWorld.m[3][0];
	worldPos.y = worldTransform_.matWorld.m[3][1];
	worldPos.z = worldTransform_.matWorld.m[3][2];

	return worldPos;
}
