#include "Player.h"

void Player::Initialize(Model* model, uint32_t texHandle)
{
	BaseCharacter::Initialize(model, texHandle);
	worldTransform_.Initialize();
}

void Player::Update()
{
	BaseCharacter::Update();
	worldTransform_.UpdateMatrix();
}

void Player::Draw(const Camera& camera)
{
	model_->Draw(worldTransform_, camera);
}
