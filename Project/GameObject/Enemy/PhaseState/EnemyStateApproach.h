#pragma once
#include "Enemy/PhaseState/IState/IPhaseStateEnemy.h"
#include"Enemy/PhaseState/EnemyStateLeave.h"

class EnemyStateApproach : public IPhaseStateEnemy{
public:
	void Update(Enemy* pEnemy)override;

private:
	
};

