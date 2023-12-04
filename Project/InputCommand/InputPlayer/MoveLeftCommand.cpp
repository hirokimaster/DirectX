#include "MoveLeftCommand.h"
#include "Player/Player.h"

void MoveLeftCommand::Exec(Player& player)
{
	player.MoveLeft();
}