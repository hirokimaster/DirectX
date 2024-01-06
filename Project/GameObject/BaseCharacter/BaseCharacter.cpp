#include "BaseCharacter.h"

void BaseCharacter::Initialize(const std::vector<Model*>& models, uint32_t texHandle)
{
	models_ = models;
	for (modelsItr_ = models_.begin(); modelsItr_ != models_.end(); ++modelsItr_) {
		(*modelsItr_)->SetTexHandle(texHandle);
	}
	worldTransform_.Initialize();
}

void BaseCharacter::Update()
{
	worldTransform_.UpdateMatrix();
}

void BaseCharacter::Draw(const Camera& camera)
{
	for (modelsItr_ = models_.begin(); modelsItr_ != models_.end(); ++modelsItr_) {
		(*modelsItr_)->Draw(worldTransform_, camera);
	}
}
