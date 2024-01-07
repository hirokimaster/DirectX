#include "Player.h"

void Player::Initialize(Model* model, uint32_t texHandle)
{
	BaseCharacter::Initialize(model, texHandle);
	worldTransform_.Initialize();
}

void Player::Update()
{
	BaseCharacter::Update();
	Move();
	worldTransform_.UpdateMatrix();
}

void Player::Draw(const Camera& camera)
{
	model_->Draw(worldTransform_, camera);
}

void Player::Move()
{
	//ゲームパッドの状態を得る変数（XINPUT）
	XINPUT_STATE joyState{};
	//キャラクターの移動ベクトル
	Vector3 move = { 0, 0, 0 };
	//キャラクターの移動の速さ
	const float kCharacterSpeed = 0.2f;

	//ゲームパッド状態取得
	if (Input::GetInstance()->GetJoystickState(joyState)) {
		move.x += (float)joyState.Gamepad.sThumbLX / SHRT_MAX * kCharacterSpeed;
		move.z += (float)joyState.Gamepad.sThumbLY / SHRT_MAX * kCharacterSpeed;
	}

	if (Input::GetInstance()->GetJoystickState(joyState)) {
		worldTransform_.rotate.y += (float)joyState.Gamepad.sThumbRX / SHRT_MAX * 0.03f;
	}

	move = TransformNormal(move, worldTransform_.matWorld);

	//押した方向で移動ベクトルを変更(左右)
	if (Input::GetInstance()->PushKey(DIK_LEFT)) {
		move.x -= kCharacterSpeed;
	}
	else if (Input::GetInstance()->PushKey(DIK_RIGHT)) {
		move.x += kCharacterSpeed;
	}

	// 押した方向で移動ベクトルを変更(前後)
	if (Input::GetInstance()->PushKey(DIK_UP)) {
		move.z += kCharacterSpeed;
	}
	else if (Input::GetInstance()->PushKey(DIK_DOWN)) {
		move.z -= kCharacterSpeed;
	}
 
	worldTransform_.translate = Add(worldTransform_.translate, move);

}
