#include "GameScene.h"

GameScene::GameScene() {}

GameScene::~GameScene() {

}

// 初期化
void GameScene::Initialize() {
	camera_.Initialize();
	camera_.rotate.x = 0.28f;
	camera_.translate = { 0,10.0f,-30.0f };

	modelBunny_.reset(Model::CreateObj("bunny.obj"));
	texHandleBunny_ = TextureManager::Load("resources/uvChecker.png");
	modelGround_.reset(Model::CreateObj("terrain.obj"));
	texHandleGround_ = TextureManager::Load("resources/grass.png");
	modelBunny_->SetTexHandle(texHandleBunny_);
	modelGround_->SetTexHandle(texHandleGround_);

	materialBunny_.enableLighting = true;
	materialBunny_.color = { 1.0f,1.0f,1.0f,1.0f };
	materialBunny_.shininess = 70.0f;
	lightingPropertyBunny_.color = { 1.0f,1.0f,1.0f,1.0f };
	lightingPropertyBunny_.intensity = 1.0f;

	materialGround_.enableLighting = true;
	materialGround_.color = { 1.0f,1.0f,1.0f,1.0f };
	materialGround_.shininess = 70.0f;
	lightingPropertyGround_.color = { 1.0f,1.0f,1.0f,1.0f };
	lightingPropertyGround_.intensity = 1.0f;

	lighting_ = BlinnPhong; // ライティングの種類

	pointLight_.color = { 1.0f,1.0f,1.0f,1.0f };
	pointLight_.decay = 0.6f;
	pointLight_.intensity = 1.0f;
	pointLight_.radius = 5.0f;

	worldTransformBunny_.Initialize();
	worldTransformBunny_.rotate.y = 3.1f;

	worldTransformGround_.Initialize();
}

// 更新
void GameScene::Update() {

	modelBunny_->SetLightingProperty(lightingPropertyBunny_); // ライトの設定
	modelBunny_->SetMaterialProperty(materialBunny_); // マテリアルの設定
	modelBunny_->SetCameraData(camera_.translate);

	modelGround_->SetLightingProperty(lightingPropertyGround_); // ライトの設定
	modelGround_->SetMaterialProperty(materialGround_);
	modelGround_->SetCameraData(camera_.translate);
	materialBunny_.enableLighting = isLighting_;

	/*-----------------------------
		    bunnyの設定
	-------------------------------*/
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
		ImGui::ColorEdit4("color", &materialBunny_.color.x);
		ImGui::DragFloat("shininess", &materialBunny_.shininess, 0.01f);
		ImGui::TreePop();
	}

	if (ImGui::TreeNode("Light")) {
		ImGui::Checkbox("isLighting", &isLighting_);
		ImGui::ColorEdit3("color", &lightingPropertyBunny_.color.x);
		ImGui::DragFloat3("direction", &lightingPropertyBunny_.direction.x, 0.01f, -1.0f, 1.0f);
		ImGui::DragFloat("intensity", &lightingPropertyBunny_.intensity, 0.01f);
		ImGui::TreePop();
	}

	ImGui::End();

	/*--------------------------
			地面の設定
	-----------------------------*/
	ImGui::Begin("groundSetting");

	if (ImGui::TreeNode("transform")) {
		ImGui::SliderAngle("rotateX", &worldTransformGround_.rotate.x);
		ImGui::SliderAngle("rotateY", &worldTransformGround_.rotate.y);
		ImGui::SliderAngle("rotateZ", &worldTransformGround_.rotate.z);
		ImGui::DragFloat3("translate", &worldTransformGround_.translate.x, 0.01f);
		ImGui::DragFloat3("scale", &worldTransformGround_.scale.x, 0.01f);
		ImGui::TreePop();
	}

	if (ImGui::TreeNode("material")) {
		ImGui::ColorEdit4("color", &materialGround_.color.x);
		ImGui::DragFloat("shininess", &materialGround_.shininess, 0.01f);
		ImGui::TreePop();
	}

	if (ImGui::TreeNode("Light")) {
		ImGui::Checkbox("isLighting", &isLighting_);
		ImGui::ColorEdit3("color", &lightingPropertyGround_.color.x);
		ImGui::DragFloat3("direction", &lightingPropertyGround_.direction.x, 0.01f, -1.0f, 1.0f);
		ImGui::DragFloat("intensity", &lightingPropertyGround_.intensity, 0.01f);
		ImGui::TreePop();
	}

	ImGui::End();

	/*---------------------------
			点光源の設定
	------------------------------*/
	ImGui::Begin("PointLightSetting");
	if (ImGui::TreeNode("LightProperty")) {

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
	modelGround_->Draw(worldTransformGround_, camera_, lighting_);
}