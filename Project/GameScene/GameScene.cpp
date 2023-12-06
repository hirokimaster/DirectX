#include "GameScene.h"

GameScene::GameScene() {}

GameScene::~GameScene() {

}

// 初期化
void GameScene::Initialize() {
	
}

// 更新
void GameScene::Update() {
	Quaternion q1 = { 2.0f,3.0f,4.0f,1.0f };
	Quaternion q2 = { 1.0f,3.0f,5.0f,2.0f };
	identity_ = IdentityQuaternion();
	conj_ = Conjugate(q1);
	inv_ = QInverse(q1);
	normal_ = QNormalize(q1);
	mul1_= Multiply(q1, q2);
	mul2_ = Multiply(q2, q1);
	float norm = Norm(q1);
	ImGui::Begin("norm");
	ImGui::Text("%.3f", norm);
	ImGui::End();
}

// 描画
void GameScene::Draw(){
	QuaternionScreenPrint(identity_,"identity");
	QuaternionScreenPrint(conj_, "conjugate");
	QuaternionScreenPrint(inv_, "inverse");
	QuaternionScreenPrint(normal_, "normal");
	QuaternionScreenPrint(mul1_, "mul1");
	QuaternionScreenPrint(mul2_, "mul2");

}					 