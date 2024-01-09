#pragma once
#include "IScene/IScene.h"
#include "Input/Input.h"
#include "Sprite/Sprite.h"

class TitleScene : public IScene {
public:
	TitleScene();
	~TitleScene();

	void Initialize()override;

	void Update()override;

	void Draw()override;

private:
	Camera camera_;
	WorldTransform worldTransform_;
	std::unique_ptr<Sprite> sprite_;
	uint32_t texHandle_ = 0;
};