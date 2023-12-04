#include "InputHandler.h"

ICommand* InputHandler::HandleInput()
{
    if (Input::GetInstance()->PushKey(DIK_A)) {
        return pushKeyA_;
    }

    if (Input::GetInstance()->PushKey(DIK_D)) {
        return pushKeyD_;
    }

    return nullptr;
}

void InputHandler::AssignMoveLeftCommandToPushKeyA()
{
    ICommand* command = new MoveLeftCommand();
    this->pushKeyA_ = command;
}

void InputHandler::AssignMoveLeftCommandToPushKeyD()
{
    ICommand* command = new MoveRightCommand();
    this->pushKeyD_ = command;
}
