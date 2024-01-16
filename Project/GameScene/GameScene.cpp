#include "GameScene.h"

GameScene::GameScene() {}

GameScene::~GameScene() {

}

// 初期化
void GameScene::Initialize() {
	
}

// 更新
void GameScene::Update() {
	Quaternion rotation0_ = MakeRotateAxisAngleQuaternion({ 0.71f,0.71f,0.0f }, 0.3f);
	Quaternion rotation1_ = MakeRotateAxisAngleQuaternion({ 0.71f,0.0f,0.71f }, 3.141592f);
	Quaternion interpolate0 = Slerp(rotation0_, rotation1_, 0.0f);
	Quaternion interpolate1 = Slerp(rotation0_, rotation1_, 0.3f);
	Quaternion interpolate2 = Slerp(rotation0_, rotation1_, 0.5f);
	Quaternion interpolate3 = Slerp(rotation0_, rotation1_, 0.7f);
	Quaternion interpolate4 = Slerp(rotation0_, rotation1_, 1.0f);

	QuaternionScreenPrint(interpolate0, "interpolate0");
	QuaternionScreenPrint(interpolate1, "interpolate1");
	QuaternionScreenPrint(interpolate2, "interpolate2");
	QuaternionScreenPrint(interpolate3, "interpolate3");
	QuaternionScreenPrint(interpolate4, "interpolate4");
}

// 描画
void GameScene::Draw(){

}					 