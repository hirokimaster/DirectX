#include "GameScene.h"

GameScene::GameScene() {}

GameScene::~GameScene() {

}

// 初期化
void GameScene::Initialize() {
	texHandlePlayer_ = TextureManager::Load("resources/uvChecker.png");
	modelPlayer_.reset(Model::CreateObj("cube.obj"));
	player_ = std::make_unique<Player>();
	player_->Initialize(modelPlayer_.get(), texHandlePlayer_);
	camera_.Initialize();
}

// 更新
void GameScene::Update() {
	player_->Update();
	camera_.UpdateMatrix();
}

// 描画						  
void GameScene::Draw(){
	player_->Draw(camera_);
}