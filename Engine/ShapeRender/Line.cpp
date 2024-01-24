#include "Line.h"

Line::Line()
{
}

Line::~Line()
{
}

void Line::Initialize()
{

	resource_.vertexResource = CreateResource::CreateBufferResource(sizeof(VertexData) * 2);

	VBV = CreateResource::CreateVertexBufferView(resource_.vertexResource, sizeof(VertexData) * 2, 2);



	resource_.materialResource = CreateResource::CreateBufferResource(sizeof(Vector4));
	// データを書き込む
	Vector4* materialData = nullptr;
	// アドレスを取得
	resource_.materialResource->Map(0, nullptr, reinterpret_cast<void**>(&materialData));
	// 赤
	*materialData = Vector4(1.0f, 1.0f, 1.0f, 1.0f);

	resource_.wvpResource = CreateResource::CreateBufferResource(sizeof(TransformationMatrix));

}

void Line::DrawLine(const Vector3& startPos, const Vector3& endPos, WorldTransform worldTransform, Camera camera)
{
#pragma region	頂点データ

	// 頂点リソースにデータを書き込む
	VertexData* vertexData = nullptr;
	// 書き込むためのアドレスを取得
	resource_.vertexResource->Map(0, nullptr, reinterpret_cast<void**>(&vertexData));

	vertexData[0].position = { start_.x,start_.y, start_.z,1.0f };
	vertexData[1].position = { end_.x,end_.y,end_.z,1.0f };

#pragma endregion

	SetStartPos(startPos);
	SetEndPos(endPos);
	worldTransform.TransferMatrix(resource_.wvpResource, camera);
	
	Property property = GraphicsPipeline::GetInstance()->GetPSO().Line;

	// Rootsignatureを設定。PSOに設定してるけど別途設定が必要
	DirectXCommon::GetCommandList()->SetGraphicsRootSignature(property.rootSignature_.Get());
	DirectXCommon::GetCommandList()->SetPipelineState(property.graphicsPipelineState_.Get()); // PSOを設定
	DirectXCommon::GetCommandList()->IASetVertexBuffers(0, 1, &VBV); // VBVを設定
	// 形状を設定。PSOに設定しているものとはまた別。同じものを設定すると考えておけば良い
	DirectXCommon::GetCommandList()->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_LINELIST);
	// マテリアルCBufferの場所を設定
	DirectXCommon::GetCommandList()->SetGraphicsRootConstantBufferView(0, resource_.materialResource->GetGPUVirtualAddress());
	// wvp用のCBufferの場所を設定
	DirectXCommon::GetCommandList()->SetGraphicsRootConstantBufferView(1, resource_.wvpResource->GetGPUVirtualAddress());
	// 描画。(DrawCall/ドローコール)。2頂点で1つのインスタンス
	DirectXCommon::GetCommandList()->DrawInstanced(2, 1, 0, 0);
}
