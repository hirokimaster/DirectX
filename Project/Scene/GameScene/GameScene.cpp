#include "GameScene.h"

GameScene::GameScene() {}

GameScene::~GameScene() {

}

// 初期化
void GameScene::Initialize() {
	t = TextureManager::Load("resources/AnimatedCube_BaseColor.png");
	m.reset(Model::CreateGFTF("AnimatedCube.gltf"));
	m->SetTexHandle(t);
	w.Initialize();
	c.Initialize();
	
}

// 更新
void GameScene::Update() {
	w.UpdateMatrix();
	c.UpdateMatrix();
}

// 描画						  
void GameScene::Draw(){
	m->DrawGLTF(w, c);
}