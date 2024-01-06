#include "GameScene.h"

GameScene::GameScene() {}

GameScene::~GameScene() {

}

// 初期化
void GameScene::Initialize() {
	texHandlePlayer_ = TextureManager::Load("resources/uvChecker.png");
	camera_.Initialize();
}

// 更新
void GameScene::Update() {
	camera_.UpdateMatrix();
}

// 描画						  
void GameScene::Draw(){
	player_->Draw(camera_);
}