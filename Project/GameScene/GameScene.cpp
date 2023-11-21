#include "GameScene.h"

GameScene::GameScene() {}

GameScene::~GameScene() {

}

// 初期化
void GameScene::Initialize() {
	view_.Initialize();
	worldTransform_.Initialize();
	model_ = std::make_unique<Model>();
	model_.reset(Model::Create(new ModelSphere));
	tex_ = TextureManager::Load("resources/uvChecker.png");
}

// 更新
void GameScene::Update() {
	view_.UpdateMatrix();
	worldTransform_.UpdateMatrix();
}

// 描画
void GameScene::Draw(){
	model_->Draw(worldTransform_, view_, tex_);
}