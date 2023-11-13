#pragma once
#include "GraphicsPipeline/GraphicsPipeline.h"
#include "CreateResource/CreateResource.h"
#include "Transform/WorldTransform.h"
#include "ViewProjection/ViewProjection.h"
#include "TextureManager/TextureManager.h"
#include "Model/Model.h"

class ParticleSystem{
public:

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	void CreateResource(ModelData modelData);

	void CreateInstancingSrv();

	void Draw(WorldTransform worldTransform[], ViewProjection viewprojection);

private:
	Resource resource_ = {};
	const uint32_t kNumInstance = 10;
	descSize size_ = {};
	ModelData modelData_;
	Model* model_;
	D3D12_VERTEX_BUFFER_VIEW VertexBufferView_{};
	
};

