#include "EnemyStateApproach.h"
#include "Enemy/Enemy.h"

void EnemyStateApproach::Update(Enemy* pEnemy)
{
	// 移動量
	pEnemy->SetVelocity({ 0.0f, 0.0f, -0.2f });
	// 移動処理
	pEnemy->Move();

	// 規定の位置に到達したら離脱
	if (pEnemy->GetPosition().z < 20.0f) {
		pEnemy->ChangeState(std::make_unique<EnemyStateLeave>());
	}

}
