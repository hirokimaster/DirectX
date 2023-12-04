#pragma once
#include "ICommand/ICommand.h"
#include "InputPlayer/MoveLeftCommand.h"
#include "InputPlayer/MoveRightCommand.h"
#include "Input/Input.h"

class InputHandler {
public:
	ICommand* HandleInput();

	void AssignMoveLeftCommandToPushKeyA();
	void AssignMoveLeftCommandToPushKeyD();

private:
	ICommand* pushKeyD_;
	ICommand* pushKeyA_;
};
