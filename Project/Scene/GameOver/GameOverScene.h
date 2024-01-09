#pragma once

#include "IScene/IScene.h"
#include "Input/Input.h"
#include "Sprite/Sprite.h"

class GameOverScene : public IScene {
public:
	GameOverScene();
	~GameOverScene();

	void Initialize()override;

	void Update()override;

	void Draw()override;

private:
	Camera camera_;
	WorldTransform worldTransform_;
	std::unique_ptr<Sprite> sprite_;
	uint32_t texHandle_ = 0;
	Input::ButtonState a_{};
};
