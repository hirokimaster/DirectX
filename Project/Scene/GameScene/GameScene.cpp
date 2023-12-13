#include "GameScene.h"

GameScene::GameScene() {}

GameScene::~GameScene() {
}

// 初期化
void GameScene::Initialize() {
	camera_.Initialize();
	/*----------------------------
		 テクスチャ読み込み
	------------------------------*/
	texHandlePlayer_ = TextureManager::Load("resources/uvChecker.png");
	texHandleEnemy_ = TextureManager::Load("resources/circle.png");
	/*----------------------------
		      プレイヤー
	------------------------------*/
	modelPlayer_.reset(Model::CreateObj("cube.obj"));
	player_ = std::make_unique<Player>();
	player_->Initialize(modelPlayer_.get(), texHandlePlayer_);
	/*----------------------------
			   エネミー
	------------------------------*/
	modelEnemy_.reset(Model::CreateObj("cube.obj"));
	enemy_ = std::make_unique<Enemy>();
	enemy_->Initialize(modelEnemy_.get(), texHandleEnemy_);
}

// 更新
void GameScene::Update() {
	
	player_->Update();
	enemy_->Update();
	camera_.UpdateMatrix();

}

// 描画						  
void GameScene::Draw(){
	
	player_->Draw(camera_);
	enemy_->Draw(camera_);

}