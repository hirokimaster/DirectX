#include "GameScene.h"

GameScene::GameScene() {}

GameScene::~GameScene() {

}

// 初期化
void GameScene::Initialize() {
	camera_.Initialize();

	model_.reset(Model::CreateObj("sphere.obj"));
	texHandle_ = TextureManager::Load("resources/uvChecker.png");
	model_->SetTexHandle(texHandle_);
	isLighting_ = true;
	material_.enableLighting = isLighting_;
	model_->SetEnableLighting(isLighting_); // ライティングのオンオフ
	material_.color = { 1.0f,1.0f,1.0f,1.0f };
	material_.shininess = 70.0f;
	lightingProperty_.color = { 1.0f,1.0f,1.0f,1.0f };
	lightingProperty_.intensity = 1.0f;
	lighting_ = BlinnPhong; // ライティングの種類

	worldTransform_.Initialize();
	worldTransform_.translate.z = -50.0f;
}

// 更新
void GameScene::Update() {

	model_->SetEnableLighting(isLighting_); // ライトのオンオフ
	model_->SetLightingProperty(lightingProperty_);	 // ライトの設定
	model_->SetMaterialProperty(material_);		// マテリアルの設定

	ImGui::Begin("Setting");

	if (ImGui::TreeNode("transform")) {

		ImGui::SliderAngle("rotateX", &worldTransform_.rotate.x);
		ImGui::SliderAngle("rotateY", &worldTransform_.rotate.y);
		ImGui::SliderAngle("rotateZ", &worldTransform_.rotate.z);
		ImGui::DragFloat3("translate", &worldTransform_.translate.x, 0.01f);
		ImGui::DragFloat3("scale", &worldTransform_.scale.x, 0.01f);
		ImGui::TreePop();
	}

	if (ImGui::TreeNode("material")) {
		ImGui::ColorEdit4("color", &material_.color.x);
		ImGui::DragFloat("shininess", &material_.shininess, 0.01f);
		ImGui::TreePop();
	}

	if (ImGui::TreeNode("Light")) {
		ImGui::Checkbox("isLighting", &isLighting_);
		ImGui::ColorEdit3("color", &lightingProperty_.color.x);
		ImGui::DragFloat3("direction", &lightingProperty_.direction.x, 0.01f, -1.0f, 1.0f);
		ImGui::DragFloat("intensity", &lightingProperty_.intensity, 0.01f);
		ImGui::TreePop();
	}

	ImGui::End();

	camera_.UpdateMatrix();
	worldTransform_.UpdateMatrix();
}

// 描画						  
void GameScene::Draw(){
	model_->Draw(worldTransform_, camera_, lighting_);
}