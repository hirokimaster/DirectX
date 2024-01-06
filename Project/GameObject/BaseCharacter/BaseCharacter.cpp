#include "BaseCharacter.h"

void BaseCharacter::Initialize(Model* model, uint32_t texHandle)
{
	model_ = model;
	model_->SetTexHandle(texHandle);
	worldTransform_.Initialize();
}

void BaseCharacter::Update()
{
	worldTransform_.UpdateMatrix();
}

void BaseCharacter::Draw(const Camera& camera)
{
	model_->Draw(worldTransform_, camera);
}
