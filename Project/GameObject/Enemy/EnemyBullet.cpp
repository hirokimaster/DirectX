#include "EnemyBullet.h"

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

}

// 更新
void EnemyBullet::Update() {

	worldTransform_.translate = Add(worldTransform_.translate, velocity_);
	// ワールドトランスフォームの更新
	worldTransform_.UpdateMatrix();

	if (--deathTimer_ <= 0) {
		isDead_ = true;
	}

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
	Vector3 worldPos;
	// ワールド行列の平行移動成分を取得（ワールド座標）
	worldPos.x = worldTransform_.matWorld.m[3][0];
	worldPos.y = worldTransform_.matWorld.m[3][1];
	worldPos.z = worldTransform_.matWorld.m[3][2];

	return worldPos;
}
