#include "GameScene.h"

GameScene::GameScene() {}

GameScene::~GameScene() {
	
}

// 初期化
void GameScene::Initialize() {

	// 乱数生成器
	/*randomEngine_ = particle_->random();
	
	emit.count = 3;
	emit.frequency = 0.5f;
	emit.frequencyTime = 0.0f;
	
	texHandle_ = TextureManager::Load("resources/circle.png");
	texHandle2_ = TextureManager::Load("resources/uvChecker.png");
	particle2_ = std::make_unique<ParticleSystem>();
	particle2_->Initialize("cube.obj");
	particle2_->SetTexHandle(texHandle2_);
	particle_ = std::make_unique<ParticleSystem>();
	particle_->Initialize("plane.obj");
	particle_->SetTexHandle(texHandle_);
	accelerationField.acceleration = { 15.0f, 0.0f,0.0f };
	accelerationField.area.min = { -1.0f,-1.0f,-1.0f };
	accelerationField.area.max = { 1.0f,1.0f,1.0f };
	viewProjection_.Initialize();
	*/
}

// 更新
void GameScene::Update() {

	/*viewProjection_.UpdateMatrix();

	ImGui::Begin("camera");
	ImGui::DragFloat3("translate", &viewProjection_.translate.x, 0.01f, -100.0f, 100.0f);
	ImGui::DragFloat3("rotate", &viewProjection_.rotate.x, 0.01f, -100.0f, 100.0f);
	ImGui::End();
	
	emit.frequencyTime += dt;
	if (emit.frequency <= emit.frequencyTime) {
		particles_.splice(particles_.end(), particle_->Emission(emit, randomEngine_));
		particles2_.splice(particles2_.end(), particle2_->Emission(emit, randomEngine_));
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

	for (std::list<Particle>::iterator particleItr2 = particles2_.begin();
		particleItr2 != particles2_.end(); ++particleItr2) {

		if (particle2_->IsCollision(accelerationField.area, (*particleItr2).worldTransform.translate)) {
			(*particleItr2).velocity = Add((*particleItr2).velocity, Multiply(dt, accelerationField.acceleration));
		}

		(*particleItr2).worldTransform.translate = Add((*particleItr2).worldTransform.translate, Multiply(dt, (*particleItr2).velocity));
		(*particleItr2).worldTransform.UpdateMatrix();

	}

	

	ImGui::Begin("Particle");
	if (ImGui::Button("Add Particle")) {
		particles_.splice(particles_.end(), particle_->Emission(emit, randomEngine_));
	}
	ImGui::End();*/
	
}

// 描画
void GameScene::Draw(){

	//particle_->Draw(particles_, viewProjection_);
	//particle2_->Draw(particles2_, viewProjection_);
	//
}