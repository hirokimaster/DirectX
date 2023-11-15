#include "ParticleSystem.h"

void ParticleSystem::Initialize(const std::string& filename){

	size_.SRV = DirectXCommon::GetInstance()->GetDevice()->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);
	modelData_ = Model::LoadObjFile("resources", filename);
	// リソース作成
	CreateResource(modelData_);
	// instancing用のSRV作成
	CreateInstancingSrv();

}

void ParticleSystem::CreateResource(ModelData modelData){
	
	// Instancing用のTransformationMatrixResourceを作る
	resource_.instancingResource = CreateResource::CreateBufferResource(sizeof(TransformationMatrix) * kNumInstance);
	// 書き込むためのアドレスを取得
	TransformationMatrix* instancingData = nullptr;
	resource_.instancingResource->Map(0, nullptr, reinterpret_cast<void**>(&instancingData));
	// 単位行列を書き込む
	for (uint32_t index = 0; index < kNumInstance; ++index) {
		instancingData[index].WVP = MakeIdentityMatrix();
		instancingData[index].World = MakeIdentityMatrix();
	}

	// VertexResource
	resource_.vertexResource = CreateResource::CreateBufferResource(sizeof(VertexData) * modelData.vertices.size());
	// VertexBufferView
	VertexBufferView_.BufferLocation = resource_.vertexResource->GetGPUVirtualAddress();
	// 使用するリソースのサイズは頂点サイズ
	VertexBufferView_.SizeInBytes = UINT(sizeof(VertexData) * modelData.vertices.size());
	// 1頂点あたりのサイズ
	VertexBufferView_.StrideInBytes = sizeof(VertexData);

	// 頂点リソースにデータを書き込む
	VertexData* vertexData = nullptr;
	// 書き込むためのアドレスを取得
	resource_.vertexResource->Map(0, nullptr, reinterpret_cast<void**>(&vertexData));
	std::memcpy(vertexData, modelData.vertices.data(), sizeof(VertexData) * modelData.vertices.size()); // 頂点データをリソースにコピー
	resource_.materialResource = CreateResource::CreateBufferResource(sizeof(Material));
	// データを書き込む
	Material* materialData = nullptr;
	// アドレスを取得
	resource_.materialResource->Map(0, nullptr, reinterpret_cast<void**>(&materialData));
	materialData->color = { 1.0f,1.0f,1.0f,1.0f };

	resource_.wvpResource = CreateResource::CreateBufferResource(sizeof(TransformationMatrix));
}

void ParticleSystem::CreateInstancingSrv(){
	D3D12_SHADER_RESOURCE_VIEW_DESC instancingSrvDesc{};
	instancingSrvDesc.Format = DXGI_FORMAT_UNKNOWN;
	instancingSrvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
	instancingSrvDesc.ViewDimension = D3D12_SRV_DIMENSION_BUFFER;
	instancingSrvDesc.Buffer.FirstElement = 0;
	instancingSrvDesc.Buffer.Flags = D3D12_BUFFER_SRV_FLAG_NONE;
	instancingSrvDesc.Buffer.NumElements = kNumInstance;
	instancingSrvDesc.Buffer.StructureByteStride = sizeof(TransformationMatrix);
	D3D12_CPU_DESCRIPTOR_HANDLE instancingSrvHandleCPU = TextureManager::GetCPUDescriptorHandle(DirectXCommon::GetInstance()->GetSRV(), size_.SRV, 5);
	instancingSrvHandleGPU_ = TextureManager::GetGPUDescriptorHandle(DirectXCommon::GetInstance()->GetSRV(), size_.SRV, 5);
	DirectXCommon::GetInstance()->GetDevice()->CreateShaderResourceView(resource_.instancingResource.Get(), &instancingSrvDesc, instancingSrvHandleCPU);

}

void ParticleSystem::Draw(WorldTransform worldTransform, ViewProjection viewprojection) {

	
	worldTransform.TransferMatrix(resource_.wvpResource, viewprojection);
	
	Property property = GraphicsPipeline::GetInstance()->GetPSO().Particle;

	// Rootsignatureを設定。PSOに設定してるけど別途設定が必要
	DirectXCommon::GetCommandList()->SetGraphicsRootSignature(property.rootSignature_.Get());
	DirectXCommon::GetCommandList()->SetPipelineState(property.graphicsPipelineState_.Get()); // PSOを設定
	DirectXCommon::GetCommandList()->IASetVertexBuffers(0, 1, &VertexBufferView_); // VBVを設定
	// 形状を設定。PSOに設定しているものとはまた別。同じものを設定すると考えておけば良い
	DirectXCommon::GetCommandList()->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	// マテリアルCBufferの場所を設定
	DirectXCommon::GetCommandList()->SetGraphicsRootConstantBufferView(0, resource_.materialResource->GetGPUVirtualAddress());
	// wvp用のCBufferの場所を設定
	DirectXCommon::GetCommandList()->SetGraphicsRootConstantBufferView(1, resource_.wvpResource->GetGPUVirtualAddress());
	DirectXCommon::GetCommandList()->SetGraphicsRootDescriptorTable(2,instancingSrvHandleGPU_);
	DirectXCommon::GetCommandList()->SetGraphicsRootDescriptorTable(3, TextureManager::GetInstance()->GetGPUHandle(texHandle_));
	// 描画。(DrawCall/ドローコール)。
	DirectXCommon::GetCommandList()->DrawInstanced(UINT(modelData_.vertices.size()), kNumInstance, 0, 0);
}
