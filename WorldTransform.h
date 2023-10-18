#pragma once
#include "Vector3.h"
#include "Matrix4x4.h"
#include "DirectXCommon.h"
#include "Mathfunction.h"
#include "CreateResource.h"


struct TransformationMatrix {
	Matrix4x4 WVP;
};

struct WorldTransform {

	Microsoft::WRL::ComPtr<ID3D12Resource> wvp;
	Vector3 scale = { 1.0f,1.0f,1.0f };
	Vector3 rotate = { 0.0f,0.0f,0.0f };
	Vector3 translate = { 0.0f,0.0f,0.0f };

	Matrix4x4 matWorld;

	const WorldTransform* parent = nullptr;

	void Initialize();

	void TransferMatrix(Microsoft::WRL::ComPtr<ID3D12Resource>& wvpResource);

	void UpdateMatrix();
	
};
