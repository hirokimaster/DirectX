#include "GameScene.h"

GameScene::GameScene() {}

GameScene::~GameScene() {
	//delete particle_;
}

// 初期化
void GameScene::Initialize() {
	
	for (uint32_t index =0; index < 10; index++) {
		particle_[index] = new ParticleSystem;
		trans_[index].Initialize();
		particle_[index]->Initialize("plane.obj");
	}
	
	view_.Initialize();
	
}

// 更新
void GameScene::Update() {
	view_.UpdateMatrix();
	
	for (uint32_t index = 0; index < 10; index++) {
		trans_[index].UpdateMatrix();
		trans_[index].scale = { 1.0f,1.0f,1.0f };
		trans_[index].rotate = { 0.0f,1.0f,0.0f };
		trans_[index].translate = { index * 0.1f,index * 0.1f,index * 0.1f };
	}


}

// 描画
void GameScene::Draw(){
	for (uint32_t index = 0; index < 10; index++) {
		particle_[index]->Draw(&trans_[index], view_);
	}

}