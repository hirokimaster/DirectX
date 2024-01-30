
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
	std::unique_ptr<Sprite> sprite_;
	std::unique_ptr<Sprite> spritePushA_;
	uint32_t texHandle_ = 0;
	uint32_t texHandlePushA_ = 0;
	uint32_t pushATimer_ = 0;
	std::unique_ptr<Sprite> spriteBlack_;
	uint32_t texHandleBlack_ = 0;
	uint32_t sceneTimer_ = 0;
	bool timerFlag_ = false;
	Vector4 color_ = {};
};
