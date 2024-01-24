#pragma once
#include "IShape/IShape.h"

class Line {
public:

	Line();
	~Line();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(const Vector3& startPos, const Vector3& endPos);

	/// <summary>
	/// 描画
	/// </summary>
	void DrawLine(WorldTransform worldTransform, Camera camera);

private:
	Vector3 start_{};
	Vector3 end_{};
	D3D12_VERTEX_BUFFER_VIEW VBV{};
	Resource resource_ = {};
};

