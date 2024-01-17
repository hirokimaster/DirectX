#include "PlayerBullet.h"

void PlayerBullet::Initialize(const Vector3& position, const Vector3& velocity) {

	worldTransform_.Initialize();
	model_.reset(Model::CreateObj("cube.obj"));
	uint32_t texHandle = TextureManager::Load("resources/monsterBall.png");
	model_->SetTexHandle(texHandle);

	// 初期座標をセット
	worldTransform_.translate = position;
	// 速度セット
	velocity_ = velocity;

	SetCollosionAttribute(kCollisionAttributePlayer);
	SetCollisionMask(kCollisionAttributeEnemy);

}

// 更新
void PlayerBullet::Update() {

	//移動
	worldTransform_.translate = Add(worldTransform_.translate, velocity_);
	// 時間で消滅
	if (--deathTimer_ <= 0) {
		isDead_ = true;
	}
	// 行列を定数バッファに転送
	worldTransform_.UpdateMatrix();

}

// 描画
void PlayerBullet::Draw(const Camera& camera) {
	// モデルの描画
	model_->Draw(worldTransform_, camera);
}

Vector3 PlayerBullet::GetWorldPosition()
{
	// ワールド座標を入れる変数
	Vector3 worldPos;
	// ワールド行列の平行移動成分を取得（ワールド座標）
	worldPos.x = worldTransform_.matWorld.m[3][0];
	worldPos.y = worldTransform_.matWorld.m[3][1];
	worldPos.z = worldTransform_.matWorld.m[3][2];

	return worldPos;
}

void PlayerBullet::OnCollision()
{
	isDead_ = true;
}


