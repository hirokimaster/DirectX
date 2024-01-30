#include "GameScene.h"

GameScene::GameScene() {}

GameScene::~GameScene() {
}

// 初期化
void GameScene::Initialize() {
	camera_.farZ = 1000.0f;
	camera_.Initialize();
	camera_.UpdateMatrix();
	/*----------------------------
		 テクスチャ読み込み
	------------------------------*/
	texHandlePlayer_ = TextureManager::Load("resources/uvChecker.png");
	texHandleEnemy_ = TextureManager::Load("resources/circle.png");
	texHandleSkydome_ = TextureManager::Load("resources/uvChecker.png");
	/*----------------------------
		      プレイヤー
	------------------------------*/
	modelPlayer_.reset(Model::CreateObj("cube.obj"));
	player_ = std::make_unique<Player>();
	Vector3 playerPos = { 0,0,40.0f };
	player_->Initialize(modelPlayer_.get(), playerPos, texHandlePlayer_);
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
	railCamera_->Initialize(player_->GetWorldPosition(), { 0,0,0 });
	player_->SetParent(&railCamera_->GetWorldTransform());

	controlPoints_ = {
		{0,0,0},
		{10.0f,10.0f,0},
		{10.0f,15.0f,0},
		{20.0f,15.0f,0},
		{20.0f,0,0},
		{30.0f,0,0}
	};

	/*----------------------------
		  レールカメラ用の曲線
	-------------------------------*/
	for (int i = 0; i < 100; ++i) {
		line_[i] = std::make_unique<Line>();
		line_[i]->Initialize();
		worldTransformLine_[i].Initialize();
		worldTransformLine_[i].scale = { 0.3f,0.3f,0.3f };
	}
	
	
}

// 更新
void GameScene::Update() {

	for (int i = 0; i < 100; ++i) {
		worldTransformLine_[i].UpdateMatrix();
	}

	player_->Update(camera_);

	EnemyRandomSpawn();
	for (enemysItr_ = enemys_.begin(); enemysItr_ != enemys_.end(); ++enemysItr_) {
		(*enemysItr_)->Update();
	}


	enemys_.remove_if([](std::unique_ptr<Enemy>& enemy) {
		if (enemy->IsDead()) {
			enemy.reset();
			return true;
		}
		return false;
		});

	Collision();
	skydome_->Update();
	if (activeRailCamera_) {
		railCamera_->Update();
	}
	
	camera_.matView = railCamera_->GetCamera().matView;
	camera_.matProjection = railCamera_->GetCamera().matProjection;
	camera_.TransferMatrix();

}

// 描画						  
void GameScene::Draw(){
	
	player_->Draw(camera_);
	for (enemysItr_ = enemys_.begin(); enemysItr_ != enemys_.end(); ++enemysItr_) {
		(*enemysItr_)->Draw(camera_);
	}

	skydome_->Draw(camera_);
	player_->DrawUI(camera_);

	std::vector<Vector3> pointsDrawing;
	const size_t segmentCount = 100;
	for (size_t i = 0; i < segmentCount + 1; ++i) {
		float t = 1.0f / segmentCount * i;
		Vector3 pos = CatmullRomPosition(controlPoints_, t);
		pointsDrawing.push_back(pos);
	}

	// 先頭から二点ずつ取り出してライン描画
	for (size_t i = 0; i < pointsDrawing.size() - 1; ++i) {

		line_[i]->DrawLine({ pointsDrawing[i] }, { pointsDrawing[i + 1] }, worldTransformLine_[i], camera_);
	}


	ImGui::Begin("Camera2");
	ImGui::SliderFloat3("CmeraTranslation2 ", &camera_.translate.x, -50.0f, 50.0f);
	ImGui::SliderFloat3("CmeraRotate2 ", &camera_.rotate.x, 0.0f, 10.0f);
	ImGui::End();
}

void GameScene::Collision()
{
	collisionManager_->ColliderClear();

	collisionManager_->ColliderPush(player_.get());

	for (enemysItr_ = enemys_.begin(); enemysItr_ != enemys_.end(); ++enemysItr_) {
		collisionManager_->ColliderPush((*enemysItr_).get());

		for (auto enemyBulletsItr = (*enemysItr_)->GetBullets().begin();
			enemyBulletsItr != (*enemysItr_)->GetBullets().end(); ++enemyBulletsItr) {
			collisionManager_->ColliderPush((*enemyBulletsItr).get());
		}
	}

	for (auto playerBulletsItr = player_->GetBullets().begin();
		playerBulletsItr != player_->GetBullets().end(); ++playerBulletsItr) {
		collisionManager_->ColliderPush((*playerBulletsItr).get());
	}

	

	collisionManager_->CheckAllCollision();
}

void GameScene::EnemyRandomSpawn()
{
	spawnTimer_++;
	std::random_device seed;

	if (spawnTimer_ >= 90) {
		std::mt19937 randomEngine(seed());
		std::uniform_real_distribution<float>distribution(-20.0f, 20.0f);
		std::unique_ptr<Enemy> enemy = nullptr;
		enemy = std::make_unique<Enemy>();
		enemy->Initialize(
			{ float(distribution(randomEngine)), float(distribution(randomEngine)), 50.0f }, texHandleEnemy_);
		enemy->SetPlayer(player_.get());
		enemys_.push_back(std::move(enemy));
		spawnTimer_ = 0;
	}
}

