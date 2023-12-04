#include "MoveRightCommand.h"
#include "Player/Player.h"

void MoveRightCommand::Exec(Player& player)
{
	player.MoveRight();
}