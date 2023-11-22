#include "GameScene.h"

GameScene::GameScene() {}

GameScene::~GameScene() {

}

// 初期化
void GameScene::Initialize() {
	
}

// 更新
void GameScene::Update() {
	axis_ = Normalize({ 1.0f,1.0f,1.0f });
	rotateMatrix = MakeRotateAxisAngle(axis_, angle_);
}

// 描画
void GameScene::Draw(){
	MatrixScreenPrintf(rotateMatrix, "Matrix");
}