#pragma once
#include "IShape/IShape.h"

class Line {
public:

	Line();
	~Line();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 描画
	/// </summary>
	void DrawLine(const Vector3& startPos, const Vector3& endPos, WorldTransform worldTransform, Camera camera);

	void SetStartPos(Vector3 pos) { start_ = pos; }
	void SetEndPos(Vector3 pos) { end_ = pos; }

private:
	Vector3 start_{};
	Vector3 end_{};
	D3D12_VERTEX_BUFFER_VIEW VBV{};
	Resource resource_ = {};
};

