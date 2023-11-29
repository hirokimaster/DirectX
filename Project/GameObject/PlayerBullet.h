#pragma once
#include "Model/Model.h"

class PlayerBullet{
public:

	void Initialize(Model* model, const Vector3& position);

	void Update();

	void Draw(const ViewProjection& viewProjection);

private:

	WorldTransform worldTransform_{};
	Model* model_ = nullptr;
};

