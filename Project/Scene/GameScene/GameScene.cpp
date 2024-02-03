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
	texHandleUVChecker_ = TextureManager::Load("resources/uvChecker.png");
	modelGround_.reset(Model::CreateObj("terrain.obj"));
	texHandleGround_ = TextureManager::Load("resources/grass.png");
	modelPlane_.reset(Model::CreateGFTF("Plane.gltf"));
	modelBunny_->SetTexHandle(texHandleUVChecker_);
	modelGround_->SetTexHandle(texHandleGround_);
	modelPlane_->SetTexHandle(texHandleUVChecker_);

	isPlaneDraw_ = false;

	isLightingBunny_ = true;
	materialBunny_.color = { 1.0f,1.0f,1.0f,1.0f };
	materialBunny_.shininess = 70.0f;
	lightingPropertyBunny_.color = { 1.0f,1.0f,1.0f,1.0f };
	lightingPropertyBunny_.direction = { 0.0f,-1.0f,0.0f };
	lightingPropertyBunny_.intensity = 1.0f;

	isLightingGround_ = true;
	materialGround_.color = { 1.0f,1.0f,1.0f,1.0f };
	materialGround_.shininess = 70.0f;
	lightingPropertyGround_.color = { 1.0f,1.0f,1.0f,1.0f };
	lightingPropertyGround_.direction = { 0.0f,-1.0f,0.0f };
	lightingPropertyGround_.intensity = 1.0f;

	lighting_ = BlinnPhong; // ライティングの種類

	pointLight_.color = { 1.0f,1.0f,1.0f,1.0f };
	pointLight_.decay = 0.6f;
	pointLight_.intensity = 1.0f;
	pointLight_.radius = 5.0f;

	spotLight_.color = { 1.0f,1.0f,1.0f,1.0f };
	spotLight_.position = { 2.0f,1.25f,0.0f };
	spotLight_.intensity = 4.0f;
	spotLight_.direction = Normalize({ -1.0f, -1.0f, 0.0f });
	spotLight_.distance = 7.0f;
	spotLight_.cosAngle = std::cos(std::numbers::pi_v<float> / 3.0f);
	spotLight_.cosFallooffStart = 1.0f;
	spotLight_.decay = 2.0f;

	worldTransformBunny_.Initialize();
	worldTransformBunny_.rotate.y = 3.1f;

	worldTransformGround_.Initialize();
	worldTransformPlane_.Initialize();
	worldTransformPlane_.translate.y = 6.0f;
	worldTransformPlane_.translate.z = -20.0f;
}

// 更新
void GameScene::Update() {

	modelBunny_->SetLightingProperty(lightingPropertyBunny_); // ライトの設定
	modelBunny_->SetMaterialProperty(materialBunny_); // マテリアルの設定
	modelBunny_->SetCameraData(camera_.translate);
	modelBunny_->SetPointLightProperty(pointLight_);
	modelBunny_->SetSpotLightProperty(spotLight_);
	materialBunny_.enableLighting = isLightingBunny_;

	modelGround_->SetLightingProperty(lightingPropertyGround_); // ライトの設定
	modelGround_->SetMaterialProperty(materialGround_);
	modelGround_->SetCameraData(camera_.translate);
	modelGround_->SetPointLightProperty(pointLight_);
	modelGround_->SetSpotLightProperty(spotLight_);
	materialGround_.enableLighting = isLightingGround_;

	static int currentItem_ = 0;
	const char* item[3] = { "Billin-Phong", "pointLight", "spotLight" };

	ImGui::Begin("Lighting Type");

	if (ImGui::Combo("LightingType", &currentItem_, item, IM_ARRAYSIZE(item))) {
		if (currentItem_ == 0) {
			lighting_ = BlinnPhong;
			lightingPropertyBunny_.intensity = 1.0f;
			lightingPropertyGround_.intensity = 1.0f;
		}
		else if (currentItem_ == 1) {
			lighting_ = Point;
			lightingPropertyBunny_.intensity = 1.0f;
			lightingPropertyGround_.intensity = 1.0f;
		}
		else if (currentItem_ == 2) {
			lighting_ = Spot;
			lightingPropertyBunny_.intensity = 0.0f;
			lightingPropertyGround_.intensity = 0.0f;
		}
	}

	ImGui::End();

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
		ImGui::Checkbox("isLighting", &isLightingBunny_);
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
		ImGui::Checkbox("isLighting", &isLightingGround_);
		ImGui::ColorEdit3("color", &lightingPropertyGround_.color.x);
		ImGui::DragFloat3("direction", &lightingPropertyGround_.direction.x, 0.01f, -1.0f, 1.0f);
		ImGui::DragFloat("intensity", &lightingPropertyGround_.intensity, 0.01f);
		ImGui::TreePop();
	}

	ImGui::End();

	/*---------------------------
			PointLightの設定
	------------------------------*/
	ImGui::Begin("PointLightSetting");
	if (ImGui::TreeNode("LightProperty")) {
		ImGui::SliderFloat4("color", &pointLight_.color.x, 0.0f, 1.0f);
		ImGui::SliderFloat3("position", &pointLight_.position.x, -100.0f, 100.0f);
		ImGui::SliderFloat("intensity", &pointLight_.intensity, 0.0f, 10.0f);
		ImGui::SliderFloat("radius", &pointLight_.radius, 0.0f, 100.0f);
		ImGui::SliderFloat("decay", &pointLight_.decay, 0.0f, 10.0f);
		ImGui::TreePop();
	}

	ImGui::End();

	/*---------------------------
			SpotLightの設定
	------------------------------*/
	ImGui::Begin("SpotLightSetting");
	if (ImGui::TreeNode("LightProperty")) {
		ImGui::SliderFloat4("color", &spotLight_.color.x, 0.0f, 1.0f);
		ImGui::SliderFloat3("position", &spotLight_.position.x, -100.0f, 100.0f);
		ImGui::SliderFloat("intensity", &spotLight_.intensity, 0.0f, 10.0f);
		ImGui::SliderFloat("distance", &spotLight_.distance, 0.0f, 100.0f);
		ImGui::DragFloat3("direction", &spotLight_.direction.x, 0.01f, -1.0f, 1.0f);
		ImGui::SliderAngle("cosAngle", &spotLight_.cosAngle);
		ImGui::SliderFloat("cosFallooffStart", &spotLight_.cosFallooffStart, 0.0f, 1.0f);
		ImGui::SliderFloat("decay", &spotLight_.decay, 0.0f, 10.0f);
		ImGui::TreePop();
	}

	ImGui::End();

	/*---------------------------
			Planeの設定
	------------------------------*/
	ImGui::Begin("Plane.gltf");
	ImGui::Checkbox("isDraw", &isPlaneDraw_);
	if (ImGui::TreeNode("transform")) {
		ImGui::SliderAngle("rotateX", &worldTransformPlane_.rotate.x);
		ImGui::SliderAngle("rotateY", &worldTransformPlane_.rotate.y);
		ImGui::SliderAngle("rotateZ", &worldTransformPlane_.rotate.z);
		ImGui::DragFloat3("translate", &worldTransformPlane_.translate.x, 0.01f);
		ImGui::DragFloat3("scale", &worldTransformPlane_.scale.x, 0.01f);
		ImGui::TreePop();
	}

	ImGui::End();

	//worldTransformPlane_.rotate.y += 0.03f;

	camera_.UpdateMatrix();
	worldTransformBunny_.UpdateMatrix();
	worldTransformGround_.UpdateMatrix();
	worldTransformPlane_.UpdateMatrix();
}

// 描画						  
void GameScene::Draw(){
	modelBunny_->Draw(worldTransformBunny_, camera_, lighting_);
	modelGround_->Draw(worldTransformGround_, camera_, lighting_);
	if (isPlaneDraw_) {
		modelPlane_->Draw(worldTransformPlane_, camera_);
	}
}