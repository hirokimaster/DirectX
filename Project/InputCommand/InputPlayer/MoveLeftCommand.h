#pragma once
#include "ICommand/ICommand.h"

class MoveLeftCommand : public ICommand{
public:
	void Exec(Player& player)override;
};

