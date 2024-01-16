#include "GameScene.h"

GameScene::GameScene() {}

GameScene::~GameScene() {

}

// 初期化
void GameScene::Initialize() {
	/*view_.Initialize();
	worldTransform_.Initialize();
	w.Initialize();
	model_.reset(Model::CreateObj("cube.obj"));
	model.reset(Model::CreateObj("terrain.obj"));
	worldTransform_.translate.y = 1.0f;
	t = TextureManager::Load("resources/grass.png");
	tex_ = TextureManager::Load("resources/uvChecker.png");
	model_->SetTexHandle(tex_);
	model->SetTexHandle(t);*/
}

// 更新
void GameScene::Update() {

	//if (Input::GetInstance()->PushKey(DIK_A)) {
	//	worldTransform_.translate.x -= 0.1f;
	//}

	//if (Input::GetInstance()->PushKey(DIK_D)) {
	//	worldTransform_.translate.x += 0.1f;
	//}

	//model->SetPointLightProperty(model->Light_);
	//model_->SetPointLightProperty(model->Light_);
	////model_->SetPointLightProperty(Light_);
	//model->Light_.position.x = worldTransform_.translate.x;
	//model->Light_.position.z = worldTransform_.translate.z;
	//model->Light_.color = { 1.0f,1.0f,1.0f,1.0f };
	//model->Light_.position.y = 4.0f;
	//model->Light_.intensity = 1.0f;
	//model->Light_.radius = 5.0f;
	//model->Light_.decay = 0.6f;
	
	/*ImGui::Begin("Light");
	ImGui::SliderFloat4("color", &Light_.color.x, 0.0f, 1.0f);
	ImGui::SliderFloat3("position", &Light_.position.x, -100.0f, 100.0f);
	ImGui::SliderFloat("intensity", &Light_.intensity, 0.0f, 10.0f);
	ImGui::SliderFloat("radius", &Light_.radius, 0.0f, 100.0f);
	ImGui::SliderFloat("decay", &Light_.decay, 0.0f, 10.0f);
	ImGui::Checkbox("isLighting", &a);
	ImGui::End();

	ImGui::Begin("camera");
	ImGui::DragFloat3("trans", &view_.translate.x, 0.01f, -100.0f, 100.0f);
	ImGui::DragFloat3("rotate", &view_.rotate.x, 0.01f, -100.0f, 100.0f);
	ImGui::End();*/

	/*model->SetEnableLighting(a);
	model_->SetEnableLighting(a);
	ImGui::Begin("Light");
	ImGui::Checkbox("isLighting", &a);
	ImGui::End();

	view_.UpdateMatrix();
	worldTransform_.UpdateMatrix();
	w.UpdateMatrix();*/
}

// 描画
void GameScene::Draw(){
	/*model->Draw(w, view_);
	model_->Draw(worldTransform_, view_);*/
	
}