#include "GameScene.h"

GameScene::GameScene() {}

GameScene::~GameScene() {

}

// 初期化
void GameScene::Initialize() {
	/*------------------------
		    プレイヤー
	--------------------------*/
	texHandlePlayer_ = TextureManager::Load("resources/uvChecker.png");
	modelPlayer_.reset(Model::CreateObj("cube.obj"));
	player_ = std::make_unique<Player>();
	player_->Initialize(modelPlayer_.get(), texHandlePlayer_);
	player_->SetCamera(&camera_);
	/*------------------------
			エネミー
	--------------------------*/
	texHandleEnemy_ = TextureManager::Load("resources/uvChecker.png");
	/*------------------------
			天球
	--------------------------*/
	texHandleSkydome_ = TextureManager::Load("resources/uvChecker.png");
	modelSkydome_.reset(Model::CreateObj("skydome.obj"));
	skydome_ = std::make_unique<Skydome>();
	skydome_->Initialize(modelSkydome_.get(), texHandleSkydome_);
	/*------------------------
			追従カメラ
	--------------------------*/
	followCamera_ = std::make_unique<FollowCamera>();
	followCamera_->Initialize();
	followCamera_->SetTarget(&player_->GetWorldTransform());
	
	camera_.Initialize();
}

// 更新
void GameScene::Update() {
	player_->Update();
	followCamera_->Update();
	camera_.matView = followCamera_->GetCamera().matView;
	camera_.matProjection = followCamera_->GetCamera().matProjection;
	skydome_->Update();
	//camera_.UpdateMatrix();
}

// 描画						  
void GameScene::Draw(){
	player_->Draw(camera_);
	skydome_->Draw(camera_);	
}