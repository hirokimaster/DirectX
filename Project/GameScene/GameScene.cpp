#include "GameScene.h"

GameScene::GameScene() {}

GameScene::~GameScene() {

}

// 初期化
void GameScene::Initialize() {
	
}

// 更新
void GameScene::Update() {
	Vector3 from0 = Normalize(Vector3{ 1.0f,0.7f,0.5f });
	Vector3 to0 = { -from0.x,-from0.y,-from0.z };
	Vector3 from1 = Normalize(Vector3{ -0.6f,0.9f,0.2f });
	Vector3 to1 = Normalize(Vector3{ 0.4f,0.7f,-0.5f });

	rotateMatrix0_ = DirectionToDirection(Normalize(Vector3{ 1.0f,0.0f,0.0f }), Normalize(Vector3{ -1.0f,0.0f,0.0f }));
	rotateMatrix1_ = DirectionToDirection(from0, to0);
	rotateMatrix2_ = DirectionToDirection(from1, to1);

}

// 描画
void GameScene::Draw(){
	MatrixScreenPrintf(rotateMatrix0_, "rotateMatrix0");
	MatrixScreenPrintf(rotateMatrix1_, "rotateMatrix1");
	MatrixScreenPrintf(rotateMatrix2_, "rotateMatrix2");
}