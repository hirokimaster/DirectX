#include "Sprite.h"
#include "engine/Math/Vector4.h"


Sprite::~Sprite()
{
	
}

/// <summary>
/// 初期化
/// </summary>
void Sprite::Initialize(uint32_t texHandle) {

#pragma region // Sprite頂点データ

	sResource_.vertexResource = CreateResource::CreateBufferResource(sizeof(VertexData) * 6);

	sVBV_ = CreateResource::CreateVertexBufferView(sResource_.vertexResource, sizeof(VertexData) * 6, 6);

	sResource_.wvpResource = CreateResource::CreateBufferResource(sizeof(TransformationMatrix));

	// 頂点データの設定
	VertexData* vertexDataSprite = nullptr;
	sResource_.vertexResource->Map(0, nullptr, reinterpret_cast<void**>(&vertexDataSprite));

	float left = 0.0f - anchorPoint_.x;
	float right = 1.0f - anchorPoint_.x;
	float top = 0.0f - anchorPoint_.y;
	float bottom = 1.0f - anchorPoint_.y;

	texHandle_ = texHandle;

	AdjustTextureSize(texHandle_);

	// 1枚目の三角形
	vertexDataSprite[0].position = { 0.0f,size_.y,0.0f, 1.0f }; // 左下
	vertexDataSprite[0].texcoord = { left, bottom };
	vertexDataSprite[1].position = { 0.0f,0.0f,0.0f, 1.0f }; // 左上
	vertexDataSprite[1].texcoord = { left, top, };
	vertexDataSprite[2].position = { size_.x, size_.y, 0.0f,1.0f }; // 右下
	vertexDataSprite[2].texcoord = { right,bottom };
	// 2枚目の三角形
	vertexDataSprite[3].position = { 0.0f,0.0f, 0.0f, 1.0f }; // 左上
	vertexDataSprite[3].texcoord = { left, top };
	vertexDataSprite[4].position = { size_.x,0.0f, 0.0f, 1.0f }; // 右上
	vertexDataSprite[4].texcoord = { right, top };
	vertexDataSprite[5].position = { size_.x, size_.y,0.0f,1.0f }; // 右下
	vertexDataSprite[5].texcoord = { right, bottom, };

#pragma endregion

	sResource_.materialResource = CreateResource::CreateBufferResource(sizeof(Vector4));
	// データを書き込む
	// アドレスを取得
	sResource_.materialResource->Map(0, nullptr, reinterpret_cast<void**>(&materialData_));
	// 赤
	*materialData_ = Vector4(1.0f,1.0f,1.0f,1.0f);

	sResource_.wvpResource = CreateResource::CreateBufferResource(sizeof(TransformationMatrix));
	
}

/// <summary>
/// スプライト生成
/// </summary>
/// <param name="position"></param>
/// <returns></returns>
Sprite* Sprite::Create(Vector2 position, uint32_t texHandle, Vector4 color)
{
	Sprite* sprite = new Sprite;
	sprite->Initialize(texHandle);
    sprite->SetPosition(position);
	sprite->SetColor(color);

	return sprite;
}

void Sprite::AdjustTextureSize(uint32_t texIndex)
{
	const DirectX::TexMetadata& metadata = TextureManager::GetInstance()->GetMetaData(texIndex);

	size_.x = static_cast<float>(metadata.width);
	size_.y = static_cast<float>(metadata.height);

}

/// <summary>
/// 描画
/// </summary>
/// <param name="v"></param>
/// <param name="t"></param>
void Sprite::Draw(Camera camera)
{
	
	worldTransform_.STransferMatrix(sResource_.wvpResource, camera);
	worldTransform_.translate.x = GetPosition().x;
	worldTransform_.translate.y = GetPosition().y;
	worldTransform_.UpdateMatrix();

	Property property = GraphicsPipeline::GetInstance()->GetPSO().Sprite2D;

	// Rootsignatureを設定。PSOに設定してるけど別途設定が必要
	DirectXCommon::GetCommandList()->SetGraphicsRootSignature(property.rootSignature_.Get());
	DirectXCommon::GetCommandList()->SetPipelineState(property.graphicsPipelineState_.Get()); // PSOを設定
	DirectXCommon::GetCommandList()->IASetVertexBuffers(0, 1, &sVBV_); // VBVを設定
	// 形状を設定。PSOに設定しているものとはまた別。同じものを設定すると考えておけば良い
	DirectXCommon::GetCommandList()->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	// マテリアルCBufferの場所を設定
	DirectXCommon::GetCommandList()->SetGraphicsRootConstantBufferView(0, sResource_.materialResource->GetGPUVirtualAddress());
	// wvp用のCBufferの場所を設定
	DirectXCommon::GetCommandList()->SetGraphicsRootConstantBufferView(1, sResource_.wvpResource->GetGPUVirtualAddress());
	DirectXCommon::GetCommandList()->SetGraphicsRootDescriptorTable(2, TextureManager::GetInstance()->GetGPUHandle(texHandle_));
	// 描画。(DrawCall/ドローコール)。3頂点で1つのインスタンス。インスタンスについては今後
	DirectXCommon::GetCommandList()->DrawInstanced(6, 1, 0, 0);

}
