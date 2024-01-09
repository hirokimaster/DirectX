#include "GameOver/GameOverScene.h"

GameOverScene::GameOverScene()
{
}

GameOverScene::~GameOverScene()
{
}

void GameOverScene::Initialize()
{
	camera_.Initialize();
	texHandle_ = TextureManager::Load("resources/gameover.png");
	sprite_.reset(Sprite::Create({ 640.0f,360.0f }, { 1280.0f,720.0f }, { 0.5f,0.5f }));

}

void GameOverScene::Update()
{
	// ゲームパッドの状態を得る変数(XINPUT)
	XINPUT_STATE joyState{};
	if (Input::GetInstance()->GetJoystickState(joyState)) {

		Input::GetInstance()->UpdateButtonState(a_, joyState.Gamepad.wButtons & XINPUT_GAMEPAD_A);

		if (a_.isPressed && !a_.wasPressed) {
			sceneNo_ = TITLE;
		}

	}

	camera_.UpdateMatrix();
}

void GameOverScene::Draw()
{
	sprite_->Draw(camera_, texHandle_);
}
