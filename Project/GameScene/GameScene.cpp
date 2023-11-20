#include "GameScene.h"

GameScene::GameScene() {}

GameScene::~GameScene() {
	
	//delete particle_;
	
}

// 初期化
void GameScene::Initialize() {

	// 乱数生成器
	std::random_device seed;
	std::mt19937 randomEngine(seed());
	
	texHandle_ = TextureManager::Load("resources/uvChecker.png");
	particle_ = new ParticleSystem;
	particle_->Initialize("plane.obj");
	particle_->SetTexHandle(texHandle_);

	for (uint32_t index = 0; index < 10; index++) {
		particles_[index] = ParticleSystem::MakeNewParticle(randomEngine);
	}
	
	view_.Initialize();
	
}

// 更新
void GameScene::Update() {

	view_.UpdateMatrix();
	
	for (uint32_t index = 0; index < 10; index++) {
		particles_[index].worldTransform.translate = Add(particles_[index].worldTransform.translate, Multiply(dt, particles_[index].velocity));
		particles_[index].worldTransform.UpdateMatrix();
		
	}
	
}

// 描画
void GameScene::Draw(){
	

	particle_->Draw(particles_, view_);
	

}