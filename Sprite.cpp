#include "Sprite.h"
#include "Vector4.h"

Sprite* Sprite::GetInstance() {
	static Sprite instance;
	return &instance;
}

/// <summary>
/// 初期化
/// </summary>
void Sprite::Initialize() {
	
	resource_.vertexResource = CreateResource::CreateBufferResource(sizeof(VertexData) * 3);

	VBV = CreateResource::CreateVertexBufferView(resource_.vertexResource, sizeof(VertexData) * 3, 3);

	//materialResource_ = Material::CreateMaterial(resource_.vertexResource);


	// 頂点リソースにデータを書き込む
	VertexData* vertexData = nullptr;
	// 書き込むためのアドレスを取得
	resource_.vertexResource->Map(0, nullptr, reinterpret_cast<void**>(&vertexData));

#pragma region

	// 左下
	vertexData[0].position = { -0.5f, -0.5f, 0.0f, 1.0f };
	vertexData[0].texcoord = { 0.0f, 1.0f };
	// 上
	vertexData[1].position = { 0.0f, 0.5f, 0.0f, 1.0f };
	vertexData[1].texcoord = { 0.5f, 0.0f };
	// 右下
	vertexData[2].position = { 0.5f, -0.5f, 0.0f, 1.0f };
	vertexData[2].texcoord = { 1.0f,1.0f };

#pragma endregion

	resource_.materialResource = CreateResource::CreateBufferResource(sizeof(Vector4));
	// データを書き込む
	Vector4* materialData = nullptr;
	// アドレスを取得
	resource_.materialResource->Map(0, nullptr, reinterpret_cast<void**>(&materialData));
	// 赤
	*materialData = Vector4(1.0f, 0.0f, 0.0f, 1.0f);

	resource_.wvpResource = CreateResource::CreateBufferResource(sizeof(TransformationMatrix));

	
}


// 三角形描画
void Sprite::DrawTriangle(WorldTransform worldTransform, ViewProjection viewProjection, uint32_t texHandle){

	worldTransform.TransferMatrix(resource_.wvpResource, viewProjection);

	Property property = GraphicsPipeline::GetInstance()->GetPs().triangle;

	// 三角形描画コマンド
	// Rootsignatureを設定。PSOに設定してるけど別途設定が必要
	DirectXCommon::GetCommandList()->SetGraphicsRootSignature(property.rootSignature_.Get());
	DirectXCommon::GetCommandList()->SetPipelineState(property.graphicsPipelineState_.Get()); // PSOを設定
	DirectXCommon::GetCommandList()->IASetVertexBuffers(0, 1, &VBV); // VBVを設定
	// 形状を設定。PSOに設定しているものとはまた別。同じものを設定すると考えておけば良い
	DirectXCommon::GetCommandList()->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	// マテリアルCBufferの場所を設定
	DirectXCommon::GetCommandList()->SetGraphicsRootConstantBufferView(0,resource_.materialResource->GetGPUVirtualAddress());
	// wvp用のCBufferの場所を設定
	DirectXCommon::GetCommandList()->SetGraphicsRootConstantBufferView(1, resource_.wvpResource->GetGPUVirtualAddress());
	DirectXCommon::GetCommandList()->SetGraphicsRootDescriptorTable(2, TextureManager::GetInstance()->GetGPUHandle(0));
	// 描画。(DrawCall/ドローコール)。3頂点で1つのインスタンス。インスタンスについては今後
	DirectXCommon::GetCommandList()->DrawInstanced(3, 1, 0, 0);

}
