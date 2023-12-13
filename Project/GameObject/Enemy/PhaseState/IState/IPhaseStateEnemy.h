#pragma once

class Enemy;

class IPhaseStateEnemy{
public :
	virtual void Update(Enemy* pEnemy) = 0;
};

