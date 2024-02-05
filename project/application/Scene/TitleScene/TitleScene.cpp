#include "application/Scene/TitleScene/TitleScene.h"

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
	sprite_.reset(Sprite::Create({ 0.0f,0.0f }, texHandle_));
	texHandlePushA_ = TextureManager::Load("resources/pushA.png");
	spritePushA_.reset(Sprite::Create({ 640.0f,500.0f }, texHandlePushA_));
}

void TitleScene::Update()
{
	XINPUT_STATE joyState{};
	if (Input::GetInstance()->GetJoystickState(joyState)) {

		if (Input::GetInstance()->PressedButton(joyState, XINPUT_GAMEPAD_A)) {
			gameManager_->ChangeScene("GAME");
		}

	}

	if (Input::GetInstance()->PressedKey(DIK_A)) {
		gameManager_->ChangeScene("GAME");
	}

	camera_.UpdateMatrix();
}

void TitleScene::Draw()
{

	sprite_->Draw(camera_);
	spritePushA_->Draw(camera_);


}