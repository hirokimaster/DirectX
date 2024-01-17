#include "GameScene.h"

GameScene::GameScene() {}

GameScene::~GameScene() {
}

// 初期化
void GameScene::Initialize() {
	camera_.Initialize();
	camera_.farZ = 500.0f;
	/*----------------------------
		 テクスチャ読み込み
	------------------------------*/
	texHandlePlayer_ = TextureManager::Load("resources/uvChecker.png");
	texHandleEnemy_ = TextureManager::Load("resources/circle.png");
	texHandleSkydome_ = TextureManager::Load("resources/bg.jpg");
	/*----------------------------
		      プレイヤー
	------------------------------*/
	modelPlayer_.reset(Model::CreateObj("cube.obj"));
	player_ = std::make_unique<Player>();
	Vector3 playerPos = { 0,0,0 };
	player_->Initialize(modelPlayer_.get(), playerPos, texHandlePlayer_);
	player_->SetParent(&railCamera_->GetWorldTransform());
	/*----------------------------
			   エネミー
	------------------------------*/
	modelEnemy_.reset(Model::CreateObj("cube.obj"));
	enemy_ = std::make_unique<Enemy>();
	enemy_->Initialize(modelEnemy_.get(), texHandleEnemy_);
	enemy_->SetPlayer(player_.get());
	/*------------------------
			   天球
	--------------------------*/
	modelSkydome_.reset(Model::CreateObj("skydome.obj"));
	skydome_ = std::make_unique<Skydome>();
	skydome_->Initialize(modelSkydome_.get(), texHandleSkydome_);
	/*----------------------------
			   collision
	------------------------------*/
	collisionManager_ = std::make_unique<CollisionManager>();
	/*----------------------------
		      レールカメラ
	------------------------------*/
	railCamera_ = std::make_unique<RailCamera>();
	railCamera_->Initialize({ 0,0,0 }, { 0,0,0 });
}

// 更新
void GameScene::Update() {
	
	player_->Update();
	enemy_->Update();
	Collision();
	skydome_->Update();
	railCamera_->Update();
	camera_.matView = railCamera_->GetCamera().matView;
	camera_.matProjection = railCamera_->GetCamera().matProjection;
	camera_.UpdateMatrix();

}

// 描画						  
void GameScene::Draw(){
	
	player_->Draw(camera_);
	enemy_->Draw(camera_);
	skydome_->Draw(camera_);

	ImGui::Begin("Camera2");
	ImGui::SliderFloat3("CmeraTranslation2 ", &camera_.translate.x, -50.0f, 50.0f);
	ImGui::SliderFloat3("CmeraRotate2 ", &camera_.rotate.x, 0.0f, 10.0f);
	ImGui::End();
}

void GameScene::Collision()
{
	collisionManager_->ColliderClear();

	collisionManager_->ColliderPush(player_.get());
	collisionManager_->ColliderPush(enemy_.get());
	for (auto playerBulletsItr = player_->GetBullets().begin();
		playerBulletsItr != player_->GetBullets().end(); ++playerBulletsItr) {
		collisionManager_->ColliderPush((*playerBulletsItr).get());
	}

	for (auto enemyBulletsItr = enemy_->GetBullets().begin();
		enemyBulletsItr != enemy_->GetBullets().end(); ++enemyBulletsItr) {
		collisionManager_->ColliderPush((*enemyBulletsItr).get());
	}

	collisionManager_->CheckAllCollision();
}
