#include "ParticleSystem.h"

/// <summary>
/// 初期化
/// </summary>
/// <param name="filename"></param>
void ParticleSystem::Initialize(const std::string& filename){

	size_.SRV = DirectXCommon::GetInstance()->GetDevice()->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);
	modelData_ = Model::LoadObjFile("resources", filename);
	// リソース作成
	CreateResource(modelData_);
	// instancing用のSRV作成
	CreateInstancingSrv();

}

/// <summary>
/// リソース作成
/// </summary>
/// <param name="modelData"></param>
void ParticleSystem::CreateResource(ModelData modelData){
	
	// Instancing用のTransformationMatrixResourceを作る
	resource_.instancingResource = CreateResource::CreateBufferResource(sizeof(ParticleForGPU) * kNumMaxInstance_);
	// 書き込むためのアドレスを取得
	resource_.instancingResource->Map(0, nullptr, reinterpret_cast<void**>(&instancingData_));
	// 単位行列を書き込む
	for (uint32_t index = 0; index < kNumMaxInstance_; ++index) {
		instancingData_[index].WVP = MakeIdentityMatrix();
		instancingData_[index].World = MakeIdentityMatrix();
		instancingData_[index].color = Vector4(1.0f, 1.0f, 1.0f, 1.0f);
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

/// <summary>
/// instancing用のSRV作成
/// </summary>
void ParticleSystem::CreateInstancingSrv(){
	D3D12_SHADER_RESOURCE_VIEW_DESC instancingSrvDesc{};
	instancingSrvDesc.Format = DXGI_FORMAT_UNKNOWN;
	instancingSrvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
	instancingSrvDesc.ViewDimension = D3D12_SRV_DIMENSION_BUFFER;
	instancingSrvDesc.Buffer.FirstElement = 0;
	instancingSrvDesc.Buffer.Flags = D3D12_BUFFER_SRV_FLAG_NONE;
	instancingSrvDesc.Buffer.NumElements = kNumMaxInstance_;
	instancingSrvDesc.Buffer.StructureByteStride = sizeof(ParticleForGPU);
	D3D12_CPU_DESCRIPTOR_HANDLE instancingSrvHandleCPU = TextureManager::GetCPUDescriptorHandle(DirectXCommon::GetInstance()->GetSRV(), size_.SRV, 3);
	instancingSrvHandleGPU_ = TextureManager::GetGPUDescriptorHandle(DirectXCommon::GetInstance()->GetSRV(), size_.SRV, 3);
	DirectXCommon::GetInstance()->GetDevice()->CreateShaderResourceView(resource_.instancingResource.Get(), &instancingSrvDesc, instancingSrvHandleCPU);

}

/// <summary>
/// 描画
/// </summary>
/// <param name="worldTransform"></param>
/// <param name="viewprojection"></param>
void ParticleSystem::Draw(Particle particle[], ViewProjection viewprojection) {

	uint32_t  numInstance = 0; // 描画すべきインスタンス数

	for (uint32_t index = 0; index < kNumMaxInstance_; ++index) {
		if (particle[index].lifeTime <= particle[index].currentTime) {
			continue;
		}

		Matrix4x4 worldMatrix = MakeAffineMatrix(particle[index].worldTransform.scale, particle[index].worldTransform.rotate,
			particle[index].worldTransform.translate);
		Matrix4x4 worldViewProjectionMatrix = Multiply(worldMatrix,Multiply(viewprojection.matView,viewprojection.matProjection));
		particle[index].currentTime += 1.0f / 60.0f;
		instancingData_[index].WVP = worldViewProjectionMatrix;
		instancingData_[index].World = worldMatrix;
		instancingData_[index].color = particle[index].color;
		++numInstance;
	}
	
	Property property = GraphicsPipeline::GetInstance()->GetPSO().Particle;

	// Rootsignatureを設定。PSOに設定してるけど別途設定が必要
	DirectXCommon::GetCommandList()->SetGraphicsRootSignature(property.rootSignature_.Get());
	DirectXCommon::GetCommandList()->SetPipelineState(property.graphicsPipelineState_.Get()); // PSOを設定
	DirectXCommon::GetCommandList()->IASetVertexBuffers(0, 1, &VertexBufferView_); // VBVを設定
	// 形状を設定。PSOに設定しているものとはまた別。同じものを設定すると考えておけば良い
	DirectXCommon::GetCommandList()->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	// マテリアルCBufferの場所を設定
	DirectXCommon::GetCommandList()->SetGraphicsRootConstantBufferView(0, resource_.materialResource->GetGPUVirtualAddress());
	// instancing用のCBufferの場所を設定
	DirectXCommon::GetCommandList()->SetGraphicsRootDescriptorTable(1,instancingSrvHandleGPU_);
	DirectXCommon::GetCommandList()->SetGraphicsRootDescriptorTable(2, TextureManager::GetInstance()->GetGPUHandle(texHandle_));
	// 描画。(DrawCall/ドローコール)。
	DirectXCommon::GetCommandList()->DrawInstanced(UINT(modelData_.vertices.size()), numInstance, 0, 0);
}

/// <summary>
/// particleをランダムで発生
/// </summary>
/// <param name="randomEngine"></param>
/// <returns></returns>
Particle ParticleSystem::MakeNewParticle(std::mt19937& randomEngine) {
	std::uniform_real_distribution<float> distribution(-1.0f, 1.0f);
	std::uniform_real_distribution<float> distColor(0.0f, 1.0f);
	std::uniform_real_distribution<float> distTime(1.0f, 3.0f);
	Particle particle;
	particle.worldTransform.Initialize();
	particle.worldTransform.scale = { 1.0f, 1.0f, 1.0f };
	particle.worldTransform.rotate = { 0.0f,0.0f,0.0f };
	particle.velocity = { distribution(randomEngine) , distribution(randomEngine) , distribution(randomEngine) };
	particle.color = { distColor(randomEngine) , distColor(randomEngine) , distColor(randomEngine), 1.0f };
	particle.lifeTime = distTime(randomEngine);
	particle.currentTime = 0;
	particle.worldTransform.translate = { distribution(randomEngine),  distribution(randomEngine) , distribution(randomEngine) };
	return particle;
}
