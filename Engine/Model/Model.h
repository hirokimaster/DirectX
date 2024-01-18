#pragma once
#include "IModelState.h"
#include "ModelSphere.h"
#include "Vector2.h"
#include <fstream>
#include <sstream>
#include "ImGuiManager/ImGuiManager.h"
#include "Camera/Camera.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
	

struct Node {
	Matrix4x4 localMatrix;
	std::string name;
	std::vector<Node> children;
};

struct MaterialData {
	std::string textureFilePath;
};

struct ModelData {
	std::vector<VertexData> vertices;
	MaterialData material;
	Node rootNode;
};

struct AnimationData {
	std::vector<std::vector<Matrix4x4>> keyframeTransforms;
	float animationDuration;
	float currentTime;
};

struct Bone {
	std::string name;
	Matrix4x4 offsetMatrix;
	Matrix4x4 currentTransfrom;
};

class Model {
public:

	~Model();
	
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(IModelState* state);

	void InitializeObj(const std::string& filename);

	void InitializeGLTF(const std::string& filename);

	/// <summary>
	/// モデル生成
	/// </summary>
	/// <returns></returns>
	static Model* Create(IModelState* state);

	/// <summary>
	/// Obj
	/// </summary>
	/// <param name="filename"></param>
	/// <returns></returns>
	static Model* CreateObj(const std::string& filename);

	static Model* CreateGFTF(const std::string& filename);

	Node ReadNode(aiNode* node);

	/// <summary>
	/// 描画
	/// </summary>
	void Draw(WorldTransform worldTransform, Camera camera, uint32_t texHandle);

	/// <summary>
	/// Objの描画
	/// </summary>
	void Draw(WorldTransform worldTransform, Camera camera);

	void DrawGLTF(WorldTransform worldTransform, Camera camera);

	// setter
	void SetTexHandle(uint32_t texHandle) { texHandle_ = texHandle; }

	// ライティングのsetter
	int32_t SetEnableLighting(int32_t enableLighting) { return materialData_->enableLighting = enableLighting; }
	// 色のsetter
	Vector4 SetColor(Vector4 color) { return materialData_->color = color; }
	// lightの設定
	PointLight SetPointLightProperty(PointLight pointLight) { return *pointLightData_ = pointLight; }
	// cameradataの設定
	Vector3 SetCameraData(Vector3 camera) { return cameraData_->worldPosition = camera; }


	/// <summary>
	/// Objファイルを読む
	/// </summary>
	/// <param name="directoryPath"></param>
	/// <param name="filename"></param>
	/// <returns></returns>
	ModelData LoadObjFile(const std::string& directoryPath, const std::string& filename);

	/// <summary>
	/// GLTFファイルを読む
	/// </summary>
	/// <param name="directoryPath"></param>
	/// <param name="filename"></param>
	/// <returns></returns>
	ModelData LoadGLTFFile(const std::string& directoryPath, const std::string& filename);

	void InitializeAnimation(const aiAnimation* animation);

	void UpdateAnimation(float deltaTime);

	void UpdateBoneTransform(const aiNode* node, const Matrix4x4& parentTransform);

	/// <summary>
	/// mtlファイルを読む
	/// </summary>
	/// <param name="directoryPath"></param>
	/// <param name="filename"></param>
	/// <returns></returns>
	MaterialData LoadMaterialTemplateFile(const std::string& directoryPath, const std::string& filename);

	AnimationData animationData_;

	std::vector<Bone> bones_;

private: // メンバ変数

	IModelState* state_ = nullptr; // モデルのパターン
	ModelData modelData_;
	Resource resource_ = {};
	D3D12_VERTEX_BUFFER_VIEW objVertexBufferView_{};
	Material* materialData_ = nullptr;
	DirectionalLight* directionalLightData_ = nullptr;
	uint32_t texHandle_ = 0;
	PointLight* pointLightData_ = nullptr;
	CameraData* cameraData_ = nullptr;
};


