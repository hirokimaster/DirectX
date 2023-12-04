#pragma once
#include "WorldTransform.h"
#include "Model/Model.h"
#include "TextureManager/TextureManager.h"

class Player{
public:

	Player();
	~Player();

	void Initialize(Model* model, uint32_t texHandle);

	void Update();

	void Draw(const ViewProjection& viewProjection);

	//キーごとのコマンド
	void MoveRight();
	void MoveLeft();

private:
	WorldTransform worldTransform_;
	Model* model_ = nullptr;
	const float MoveSpeed_ = 0.1f;
};

