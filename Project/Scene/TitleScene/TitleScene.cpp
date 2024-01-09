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
	texHandle_ = TextureManager::Load("resources/Title.png");
	sprite_.reset(Sprite::Create({ 640.0f,360.0f }, { 1280.0f,720.0f }, { 0.5f,0.5f }));

}

void TitleScene::Update()
{
	// ゲームパッドの状態を得る変数(XINPUT)
	XINPUT_STATE joyState{};

	if (joyState.Gamepad.wButtons & XINPUT_GAMEPAD_A) {
		sceneNo_ = GAME;
	}

	camera_.UpdateMatrix();
}

void TitleScene::Draw()
{
	sprite_->Draw(camera_, texHandle_);
}
