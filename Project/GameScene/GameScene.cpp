#include "GameScene.h"

GameScene::GameScene() {}

GameScene::~GameScene() {

}

// 初期化
void GameScene::Initialize() {
	view_.Initialize();
	//worldTransform_.Initialize();
	w.Initialize();
	/*model_ = std::make_unique<Model>();
	model_.reset(Model::Create(new ModelSphere));*/
	model.reset(Model::CreateObj("terrain.obj"));
	t = TextureManager::Load("resources/grass.png");
	//tex_ = TextureManager::Load("resources/uvChecker.png");
	model->SetTexHandle(t);
}

// 更新
void GameScene::Update() {

	/*if (Input::GetInstance()->PushKey(DIK_A)) {
		worldTransform_.translate.x -= 0.1f;
	}*/

	ImGui::Begin("camera");
	ImGui::DragFloat3("trans", &view_.translate.x, 0.01f, -100.0f, 100.0f);
	ImGui::DragFloat3("rotate", &view_.rotate.x, 0.01f, -100.0f, 100.0f);
	ImGui::End();

	model->SetEnableLighting(a);
	ImGui::Begin("Light");
	ImGui::Checkbox("isLighting", &a);
	ImGui::End();

	view_.UpdateMatrix();
	//worldTransform_.UpdateMatrix();
	w.UpdateMatrix();
}

// 描画
void GameScene::Draw(){
	model->Draw(w, view_);
	//model_->Draw(worldTransform_, view_, tex_);
	
}