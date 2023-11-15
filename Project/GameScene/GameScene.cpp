#include "GameScene.h"

GameScene::GameScene() {}

GameScene::~GameScene() {
	for (uint32_t index = 0; index < 10; index++) {
		delete particle_[index];
	}
	
}

// 初期化
void GameScene::Initialize() {
	
	texHandle_ = TextureManager::Load("resources/uvChecker.png");

	for (uint32_t index =0; index < 10; index++) {
		particle_[index] = new ParticleSystem;
		particle_[index]->Initialize("cube.obj");
		particle_[index]->SetTexHandle(texHandle_);
		trans_[index].Initialize();
	}
	
	view_.Initialize();
	
}

// 更新
void GameScene::Update() {

	view_.UpdateMatrix();
	
	for (uint32_t index = 0; index < 10; index++) {
		trans_[index].UpdateMatrix();
		trans_[index].translate = { index * 0.1f,index * 0.1f,index * 0.1f };
		
	}
	
}

// 描画
void GameScene::Draw(){
	for (uint32_t index = 0; index < 10; index++) {
		particle_[index]->Draw(trans_[index], view_);
	}

}