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
		 レールカメラ
	------------------------------*/
	railCamera_ = std::make_unique<RailCamera>();
	railCamera_->Initialize({ 0,0,0 }, { 0,0,0 });
	/*----------------------------
		      プレイヤー
	------------------------------*/
	modelPlayer_.reset(Model::CreateObj("cube.obj"));
	player_ = std::make_unique<Player>();
	Vector3 playerPos = { 0,0,0 };
	player_->Initialize(modelPlayer_.get(),playerPos, texHandlePlayer_);
	player_->SetParent(&railCamera_->GetWorldTransform());
	/*----------------------------
			   エネミー
	------------------------------*/
	std::unique_ptr<Enemy> enemy = std::make_unique<Enemy>();
	modelEnemy_.reset(Model::CreateObj("cube.obj"));
	enemy->Initialize(modelEnemy_.get(), texHandleEnemy_);
	enemy->SetPlayer(player_.get());
	enemys_.push_back(std::move(enemy));
}

// 更新
void GameScene::Update() {
	
	player_->Update(camera_);

	for (enemysItr_ = enemys_.begin(); enemysItr_ != enemys_.end(); ++enemysItr_) {
		(*enemysItr_)->Update();
	}
	
	CheckAllCollisions();
	railCamera_->Update();
	camera_.UpdateMatrix();

}

// 描画						  
void GameScene::Draw(){
	
	player_->Draw(camera_);

	for (enemysItr_ = enemys_.begin(); enemysItr_ != enemys_.end(); ++enemysItr_) {
		(*enemysItr_)->Draw(camera_);
	}

	player_->DrawUI(camera_);
}

void GameScene::CheckAllCollisions()
{
	// 判定対象AとBの座標
	Vector3 posA, posB;

	// 自弾リストの取得
	const std::list<std::unique_ptr<PlayerBullet>>& playerBullets = player_->GetBullets();


#pragma region 自キャラと敵弾の当たり判定
	// 自キャラの座標
	posA = player_->GetWorldPosition();

	// 自キャラと敵弾すべての当たり判定
	for (enemysItr_ = enemys_.begin(); enemysItr_ != enemys_.end(); ++enemysItr_) {

		for (auto enemyBulletsItr = (*enemysItr_)->GetBullets().begin();
			enemyBulletsItr != (*enemysItr_)->GetBullets().end(); ++enemyBulletsItr) {

			// 敵弾の座標
			posB = (*enemyBulletsItr)->GetWorldPosition();

			// AとBの距離
			float distance = (posB.x - posA.x) * (posB.x - posA.x) +
				(posB.y - posA.y) * (posB.y - posA.y) +
				(posB.z - posA.z) * (posB.z - posA.z);

			// 半径
			float R1 = 1.0f;
			float R2 = 1.0f;


			// 球と球の交差判定
			if (distance <= (R1 + R2) * (R1 + R2)) {
				// 自キャラの衝突時コールバックを呼び出す
				player_->OnCollision();
				// 敵弾の衝突時コールバックを呼び出す
				(*enemyBulletsItr)->OnCollision();
			}
		}
	}
	
#pragma endregion

#pragma region 自弾とすべての敵キャラの当たり判定

	// 敵キャラの座標
	for (enemysItr_ = enemys_.begin(); enemysItr_ != enemys_.end(); ++enemysItr_) {
		posA = (*enemysItr_)->GetWorldPosition();

		// 自弾と敵すべての当たり判定
		for (auto playerBulletsItr = player_->GetBullets().begin();
			playerBulletsItr != player_->GetBullets().end(); ++playerBulletsItr) {
			// 自弾の座標
			posB = (*playerBulletsItr)->GetWorldPosition();

			// AとBの距離
			float distance = (posB.x - posA.x) * (posB.x - posA.x) +
				(posB.y - posA.y) * (posB.y - posA.y) +
				(posB.z - posA.z) * (posB.z - posA.z);

			// 半径
			float R1 = 1.0f;
			float R2 = 1.0f;

			// 球と球の交差判定
			if (distance <= (R1 + R2) * (R1 + R2)) {
				// 敵キャラの衝突時コールバックを呼び出す
				(*enemysItr_)->OnCollision();
				// 自弾の衝突時コールバックを呼び出す
				(*playerBulletsItr)->OnCollision();
			}
		}
	}

#pragma endregion

#pragma region 自弾と敵弾の当たり判定

	// 自弾と敵すべての当たり判定
	for (enemysItr_ = enemys_.begin(); enemysItr_ != enemys_.end(); ++enemysItr_) {

		for (auto playerBulletsItr = player_->GetBullets().begin();
			playerBulletsItr != player_->GetBullets().end(); ++playerBulletsItr) {
			// 自キャラの座標
			posA = (*playerBulletsItr)->GetWorldPosition();

			for (auto enemyBulletsItr = (*enemysItr_)->GetBullets().begin();
				enemyBulletsItr != (*enemysItr_)->GetBullets().end(); ++enemyBulletsItr) {
				// 敵弾の座標
				posB = (*enemyBulletsItr)->GetWorldPosition();

				// AとBの距離
				float distance = (posB.x - posA.x) * (posB.x - posA.x) +
					(posB.y - posA.y) * (posB.y - posA.y) +
					(posB.z - posA.z) * (posB.z - posA.z);

				// 半径
				float R1 = 1.0f;
				float R2 = 1.0f;

				// 球と球の交差判定
				if (distance <= (R1 + R2) * (R1 + R2)) {
					// 自キャラの衝突時コールバックを呼び出す
					(*playerBulletsItr)->OnCollision();
					// 敵弾の衝突時コールバックを呼び出す
					(*enemyBulletsItr)->OnCollision();
				}
			}
		}

	}
	

#pragma endregion

}

