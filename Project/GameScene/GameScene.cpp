#include "GameScene.h"

GameScene::GameScene() {}

GameScene::~GameScene() {
	
}

// 初期化
void GameScene::Initialize() {

	// 乱数生成器
	randomEngine_ = particle_->random();
	
	emit.count = 3;
	emit.frequency = 0.5f;
	emit.frequencyTime = 0.0f;
	
	texHandle_ = TextureManager::Load("resources/circle.png");
	particle_ = std::make_unique<ParticleSystem>();
	particle_->Initialize("plane.obj");
	particle_->SetTexHandle(texHandle_);
	accelerationField.acceleration = { 15.0f, 0.0f,0.0f };
	accelerationField.area.min = { -1.0f,-1.0f,-1.0f };
	accelerationField.area.max = { 1.0f,1.0f,1.0f };
	viewProjection_.Initialize();
	
}

// 更新
void GameScene::Update() {

	viewProjection_.UpdateMatrix();

	ImGui::Begin("camera");
	ImGui::DragFloat3("translate", &viewProjection_.translate.x, 0.01f, -100.0f, 100.0f);
	ImGui::DragFloat3("rotate", &viewProjection_.rotate.x, 0.01f, -100.0f, 100.0f);
	ImGui::End();
	
	emit.frequencyTime += dt;
	if (emit.frequency <= emit.frequencyTime) {
		particles_.splice(particles_.end(), particle_->Emission(emit, randomEngine_));
		emit.frequencyTime -= emit.frequency;
	}

	for (std::list<Particle>::iterator particleItr = particles_.begin();
		particleItr != particles_.end(); ++particleItr) {

		if (particle_->IsCollision(accelerationField.area, (*particleItr).worldTransform.translate)) {
			(*particleItr).velocity = Add((*particleItr).velocity, Multiply(dt, accelerationField.acceleration));
		}
	
		(*particleItr).worldTransform.translate = Add((*particleItr).worldTransform.translate, Multiply(dt, (*particleItr).velocity));
		(*particleItr).worldTransform.UpdateMatrix();
		
	}

	

	ImGui::Begin("Particle");
	if (ImGui::Button("Add Particle")) {
		particles_.splice(particles_.end(), particle_->Emission(emit, randomEngine_));
	}
	ImGui::End();
	
}

// 描画
void GameScene::Draw(){

	particle_->Draw(particles_, viewProjection_);
	
}