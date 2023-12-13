#pragma once
#include "Enemy/PhaseState/IState/IPhaseStateEnemy.h"
#include"Enemy/PhaseState/EnemyStateLeave.h"

class EnemyStateApproach : public IPhaseStateEnemy{
public:
	void Update(Enemy* pEnemy)override;

	// 発射間隔
	static const int kFireInterval_ = 60;

private:
	int fireTimer_ = 60;
};

