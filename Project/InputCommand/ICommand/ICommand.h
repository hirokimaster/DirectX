#pragma once

class Player;

class ICommand{
public:
	virtual ~ICommand();
	virtual void Exec(Player& player) = 0;
};