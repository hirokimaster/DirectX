#pragma once
#include "GraphicsPipeline/GraphicsPipeline.h"
#include "CreateResource/CreateResource.h"
#include "Transform/WorldTransform.h"
#include "ViewProjection/ViewProjection.h"
#include "TextureManager/TextureManager.h"
#include "Model/Model.h"
#include <random>
#include <numbers>
#include "Input/Input.h"

struct ParticleForGPU {
	Matrix4x4 WVP;
	Matrix4x4 World;
	Vector4 color;
};

struct Particle {
	WorldTransform worldTransform;
	Vector3 velocity;
	Vector4 color;
	float lifeTime;
	float currentTime;
};

struct Emitter {
	WorldTransform worldransform; //!<エミッタのtransform
	uint32_t count; //!< 発生数
	float frequency; //!< 発生頻度
	float frequencyTime; //!< 頻度用時刻
};

struct AccelerationField {
	Vector3 acceleration; //!< 加速度
	AABB area; //!< 範囲
};

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
	void Draw(std::list<Particle>& partcles, const ViewProjection& viewprojection);

#pragma region setter

	void SetTexHandle(uint32_t texHandle) { texHandle_ = texHandle; }

	void SetNumInstance(uint32_t kNumMaxInstace) { kNumMaxInstance_ = kNumMaxInstace; }

#pragma endregion

	/// <summary>
	/// particleをランダム発生
	/// </summary>
	/// <param name="randomEngine"></param>
	/// <returns></returns>
	static Particle MakeNewParticle(std::mt19937& randomEngine);

	/// <summary>
	/// emit関数
	/// </summary>
	/// <param name="emitter"></param>
	/// <param name="randomEngine"></param>
	/// <returns></returns>
	std::list<Particle> Emission(const Emitter& emitter, std::mt19937& randomEngine);

	bool IsCollision(const AABB& aabb, const Vector3& point);

	std::mt19937 random();

private:
	Resource resource_ = {};
	uint32_t kNumMaxInstance_ = 100;
	descSize size_ = {};
	ModelData modelData_;
	Model* model_;
	D3D12_VERTEX_BUFFER_VIEW VertexBufferView_{};
	D3D12_GPU_DESCRIPTOR_HANDLE instancingSrvHandleGPU_;
	uint32_t texHandle_ = 0;
	ParticleForGPU* instancingData_ = nullptr;
};

