#include "EnemyStateApproach.h"
#include "Enemy/Enemy.h"

void EnemyStateApproach::Update(Enemy* pEnemy)
{
	// 移動量
	pEnemy->SetVelocity({ 0.0f, 0.0f, -0.2f });
	// 移動処理
	pEnemy->Move();

	//発射タイマーをデクリメント
	--fireTimer_;

	if (fireTimer_ <= 0) {
		// 弾を発射
		pEnemy->Fire();
		// 発射タイマーの初期化
		fireTimer_ = kFireInterval_;
	}

	// 規定の位置に到達したら離脱
	if (pEnemy->GetPosition().z < 20.0f) {
		pEnemy->changeState(new EnemyStateLeave);
	}

}
