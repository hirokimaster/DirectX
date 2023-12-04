#include "GameScene.h"

GameScene::GameScene() {}

GameScene::~GameScene() {

}

// 初期化
void GameScene::Initialize() {
	inputHandler_ = new InputHandler();
	// Assige command
	inputHandler_->AssignMoveLeftCommandToPushKeyA();
	inputHandler_->AssignMoveLeftCommandToPushKeyD();
	// player
	player_ = std::make_unique<Player>();
	modelPlayer_ = std::make_unique<Model>();
	modelPlayer_.reset(Model::CreateObj("cube.obj"));
	texHandlePlayer_ = TextureManager::Load("resources/uvChecker.png");
	player_->Initialize(modelPlayer_.get(), texHandlePlayer_);
	viewProjection_.Initialize();
}

// 更新
void GameScene::Update() {
	command_ = inputHandler_->HandleInput();
	if (this->command_) {
		command_->Exec(*player_.get());
	}

	player_->Update();
	viewProjection_.UpdateMatrix();
}

// 描画						  
void GameScene::Draw(){
	player_->Draw(viewProjection_);
}