#include "GameScene.h"

GameScene::GameScene() {}

GameScene::~GameScene() {

}

// 初期化
void GameScene::Initialize() {
	
}

// 更新
void GameScene::Update() {
	rotation_ = MakeRotateAxisAngleQuaternion(Normalize(Vector3{ 1.0f,0.4f,-0.2f }), 0.45f);
	Vector3 pointY = { 2.1f,-0.9f,1.3f };
	rotateMatrix_ = MakeRotateMatrix(rotation_);
	rotateByQuaternion_ = RotateVector(pointY, rotation_);
	rotateByMatrix_ = Transform(pointY, rotateMatrix_);
}

// 描画
void GameScene::Draw(){
	QuaternionScreenPrint(rotation_,"rotation");
	MatrixScreenPrintf(rotateMatrix_, "rotateMatrix");
	Vector3ScreenPrint(rotateByMatrix_, "rotateByMatrix");
	Vector3ScreenPrint(rotateByQuaternion_, "rotateByQuaternion");
}					 