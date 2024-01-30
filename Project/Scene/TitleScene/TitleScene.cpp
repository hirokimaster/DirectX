#include "TitleScene.h"

TitleScene::TitleScene()
{
}

TitleScene::~TitleScene()
{
}

void TitleScene::Initialize()
{
	camera_.Initialize();
	texHandle_ = TextureManager::Load("resources/title.png");
	sprite_.reset(Sprite::Create({ 640.0f,360.0f }, { 1280.0f,720.0f }, { 0.5f,0.5f }));
	texHandlePushA_ = TextureManager::Load("resources/pushA.png");
	spritePushA_.reset(Sprite::Create({ 640.0f,500.0f }, { 500.0f,150.0f }, { 0.5f,0.5f }));
	pushATimer_ = 0;
	texHandleBlack_ = TextureManager::Load("resources/black.png");
	spriteBlack_.reset(Sprite::Create({ 640.0f,360.0f }, { 1280.0f,720.0f }, { 0.5f,0.5f }, { 1.0f, 1.0f, 1.0f, 0.0f }));
}

void TitleScene::Update()
{
	++pushATimer_;
	XINPUT_STATE joyState{};
	if (Input::GetInstance()->GetJoystickState(joyState)) {

		if (Input::GetInstance()->PressedButton(joyState, XINPUT_GAMEPAD_A)) {
			timerFlag_ = true;
		}

	}

	if (timerFlag_) {
		sceneTimer_++;

		if (sceneTimer_ >= 10 && sceneTimer_ <= 150) {
			color_.w += 0.008f;
			spriteBlack_->SetColor({ color_ });
		}
		else if (sceneTimer_ >= 150) {
			color_.w -= 0.008f;
			spriteBlack_->SetColor({ color_ });
		}
	}

	if (sceneTimer_ >= 165) {
		sceneNo_ = GAME;
	}

	camera_.UpdateMatrix();
}

void TitleScene::Draw()
{
	if (sceneTimer_ <= 150) {
		sprite_->Draw(camera_, texHandle_);

		if (pushATimer_ % 40 >= 20) {
			spritePushA_->Draw(camera_, texHandlePushA_);
		}
	}
	
	spriteBlack_->Draw(camera_, texHandleBlack_);
	
}