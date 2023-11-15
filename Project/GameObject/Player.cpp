#include "Player.h"

void Player::Initialize(Model* model, uint32_t texHandle)
{
	model_ = model;
	model_->SetTexHandle(texHandle);
	worldTransform_.Initialize();

}

void Player::Update()
{
	Vector3 move{ 0,0,0 }; // 移動ベクトル

	if (Input::GetInstance()->PushKey(DIK_A)) {
		move.x -= moveSpeed;
	}
	else if (Input::GetInstance()->PushKey(DIK_D)) {
		move.x += moveSpeed;
	}

	if (Input::GetInstance()->PushKey(DIK_W)) {
		move.y += moveSpeed;
	}
	else if (Input::GetInstance()->PushKey(DIK_S)) {
		move.y -= moveSpeed;
	}

	worldTransform_.translate = Add(worldTransform_.translate, move);

	// 移動限界
	const float kMoveLimitX = 23.0f;
	const float kMoveLimitY = 12.5f;

	// 範囲を超えない処理
	worldTransform_.translate.x = max(worldTransform_.translate.x, -kMoveLimitX);
	worldTransform_.translate.x = min(worldTransform_.translate.x, kMoveLimitX);
	worldTransform_.translate.y = max(worldTransform_.translate.y, -kMoveLimitY);
	worldTransform_.translate.y = min(worldTransform_.translate.y, kMoveLimitY);

	// ImGui
	ImGui::Begin("Player");
	ImGui::Text(
		"Player X[%.03f].Y[%.03f].Z[%.03f]", worldTransform_.translate.x,
		worldTransform_.translate.y, worldTransform_.translate.z);
	ImGui::End();

	worldTransform_.UpdateMatrix();
}

void Player::Rotate() {
	// 回転速さ[ラジアン/frame]
	const float kRotSpeed = 0.02f;

	// 押した方向で移動ベクトルを変更
	if (Input::GetInstance()->PushKey(DIK_LEFT)) {
		worldTransform_.rotate.y -= kRotSpeed;

	}
	else if (Input::GetInstance()->PushKey(DIK_RIGHT)) {
		worldTransform_.rotate.y += kRotSpeed;
	}
}

// 攻撃
void Player::Attack() {

	// 処理
	if (Input::GetInstance()->PushKeyPressed(DIK_SPACE)) {
		// 弾を生成し、初期化
		unique_ptr<PlayerBullet> newBullet;
		newBullet = make_unique<PlayerBullet>();
		newBullet->Initialize(model_, worldTransform_.translate,);

		// 弾をセット
		bullet_ = newBullet;
	}

}

void Player::Draw(const ViewProjection& viewProjection)
{
	model_->Draw(worldTransform_,viewProjection);
}
