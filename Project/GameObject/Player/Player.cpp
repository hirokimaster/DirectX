#include "Player.h"

void Player::Initialize(const std::vector<Model*>& models, uint32_t texHandle)
{
	BaseCharacter::Initialize(models, texHandle);
	
}

void Player::Update()
{
	BaseCharacter::Update();
}

void Player::Draw(const Camera& camera)
{
	for (modelsItr_ = models_.begin(); modelsItr_ != models_.end(); ++modelsItr_) {
		(*modelsItr_)->Draw(worldTransform_, camera);
	}
}
