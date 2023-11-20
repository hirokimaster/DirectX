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
	void Initialize(const std::string& filename);

	/// <summary>
	/// リソース作成
	/// </summary>
	/// <param name="modelData"></param>
	void CreateResource(ModelData modelData);

	/// <summary>
	/// instancing用のSRVの作成
	/// </summary>
	void CreateInstancingSrv();

	/// <summary>
	/// 描画
	/// </summary>
	/// <param name="worldTransform"></param>
	/// <param name="viewprojection"></param>
	void Draw(WorldTransform worldTransform[], ViewProjection viewprojection);

#pragma region setter

	void SetTexHandle(uint32_t texHandle) { texHandle_ = texHandle; }

	void SetNumInstance(uint32_t kNumInstace) { kNumInstace = kNumInstance_; }

#pragma endregion

private:
	Resource resource_ = {};
	const uint32_t kNumInstance_ = 10;
	descSize size_ = {};
	ModelData modelData_;
	Model* model_;
	D3D12_VERTEX_BUFFER_VIEW VertexBufferView_{};
	D3D12_GPU_DESCRIPTOR_HANDLE instancingSrvHandleGPU_;
	uint32_t texHandle_ = 0;
	TransformationMatrix* instancingData_ = nullptr;
};

