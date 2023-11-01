#pragma once
#include <math.h>
#define _USE_MATH_DEFINES
#include "Model.h"
#include "ModelState.h"

class ModelSphere : public ModelState{
public:

	void Initialize(Model* state)override;

	void Draw(WorldTransform worldTransform, ViewProjection viewProjection, uint32_t texHandle)override;

private:

	D3D12_VERTEX_BUFFER_VIEW VBV{};
	Resource resource_ = {};
	WorldTransform worldTransform_ = {};
	// 分割数
	uint32_t kSubdivision = 16;
public:

	ModelSphere() = default;
};