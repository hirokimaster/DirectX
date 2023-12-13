#pragma once
#include "Enemy/PhaseState/IState/IPhaseStateEnemy.h"

class EnemyStateApproach : public IPhaseStateEnemy{
public:

	void Update(Enemy* pEnemy)override;
};

