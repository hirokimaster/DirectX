#pragma once
#include "Enemy/PhaseState/IState/IPhaseStateEnemy.h"

class EnemyStateLeave : public IPhaseStateEnemy{
public:

	void Update(Enemy* pEnemy)override;
};

