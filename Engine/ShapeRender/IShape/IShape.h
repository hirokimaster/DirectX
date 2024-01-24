#pragma once
#include "CreateResource/CreateResource.h"
#include "GraphicsPipeline/GraphicsPipeline.h"
#include "TextureManager/TextureManager.h"
#include "WorldTransform.h"

class IShape {
public:
	IShape() = default;
	virtual ~IShape() = 0;

	/// <summary>
	/// 初期化
	/// </summary>
	/// <returns></returns>
	virtual void Initialize(IShape* state) = 0;

	virtual void Draw(Vector3 startPos, Vector3 endPos, uint32_t texHandle);

protected:

	D3D12_VERTEX_BUFFER_VIEW VBV{};
	Resource resource_ = {};
};
