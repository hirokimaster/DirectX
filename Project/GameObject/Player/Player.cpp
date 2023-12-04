#include "Player.h"

Player::Player(){}

Player::~Player(){}

void Player::Initialize(Model* model, uint32_t texHandle)
{
	worldTransform_.Initialize();
	model_ = model;
	model_->SetTexHandle(texHandle);
	
}

void Player::Update()
{
	worldTransform_.UpdateMatrix();
}

void Player::Draw(const ViewProjection& viewProjection)
{
	model_->Draw(worldTransform_, viewProjection);
}

void Player::MoveRight()
{
	this->worldTransform_.translate.x += this->MoveSpeed_;
}

void Player::MoveLeft()
{
	this->worldTransform_.translate.x -= this->MoveSpeed_;
}
