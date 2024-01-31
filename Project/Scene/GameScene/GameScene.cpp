#include "GameScene.h"

GameScene::GameScene() {}

GameScene::~GameScene() {

}

// 初期化
void GameScene::Initialize() {
	camera_.Initialize();

	modelBunny_.reset(Model::CreateObj("bunny.obj"));
	texHandleBunny_ = TextureManager::Load("resources/uvChecker.png");
	modelBunny_->SetTexHandle(texHandleBunny_);
	material_.enableLighting = true;
	material_.color = { 1.0f,1.0f,1.0f,1.0f };
	material_.shininess = 70.0f;
	lightingProperty_.color = { 1.0f,1.0f,1.0f,1.0f };
	lightingProperty_.intensity = 1.0f;
	lighting_ = BlinnPhong; // ライティングの種類

	worldTransformBunny_.Initialize();
	worldTransformBunny_.translate.z = -50.0f;
	worldTransformBunny_.rotate.y = 3.1f;

	worldTransformGround_.Initialize();
}

// 更新
void GameScene::Update() {

	modelBunny_->SetLightingProperty(lightingProperty_);	 // ライトの設定
	modelBunny_->SetMaterialProperty(material_);		// マテリアルの設定
	material_.enableLighting = isLighting_;

	ImGui::Begin("BunnySetting");

	if (ImGui::TreeNode("transform")) {
		ImGui::SliderAngle("rotateX", &worldTransformBunny_.rotate.x);
		ImGui::SliderAngle("rotateY", &worldTransformBunny_.rotate.y);
		ImGui::SliderAngle("rotateZ", &worldTransformBunny_.rotate.z);
		ImGui::DragFloat3("translate", &worldTransformBunny_.translate.x, 0.01f);
		ImGui::DragFloat3("scale", &worldTransformBunny_.scale.x, 0.01f);
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
	worldTransformBunny_.UpdateMatrix();
	worldTransformGround_.UpdateMatrix();
}

// 描画						  
void GameScene::Draw(){
	modelBunny_->Draw(worldTransformBunny_, camera_, lighting_);
}