#include "GameScene.h"

GameScene::GameScene() {}

GameScene::~GameScene() {
	
	//delete particle_;
	
}

// 初期化
void GameScene::Initialize() {
	
	texHandle_ = TextureManager::Load("resources/uvChecker.png");
	particle_ = new ParticleSystem;
	particle_->Initialize("cube.obj");
	particle_->SetTexHandle(texHandle_);

	for (uint32_t index = 0; index < 10; index++) {
		trans_[index].Initialize();
	}
	
	view_.Initialize();
	
}

// 更新
void GameScene::Update() {

	view_.UpdateMatrix();
	
	for (uint32_t index = 0; index < 10; index++) {
		trans_[index].UpdateMatrix();
	}
	
}

// 描画
void GameScene::Draw(){
	for (uint32_t index = 0; index < 10; index++) {
		trans_[index].translate = { index * 0.1f,index * 0.1f,index * 0.1f };
	}

	particle_->Draw(trans_, view_);

}