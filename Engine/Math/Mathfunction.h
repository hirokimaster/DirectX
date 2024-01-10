#pragma once
#include "Matrix4x4.h"
#include "Vector3.h"
#include "ImGuiManager/ImGuiManager.h"
#include <iostream>
#include <cassert>
#include "Vector4.h"

struct Quaternion {
	float x;
	float y;
	float z;
	float w;
};

// 積
Matrix4x4 Multiply(const Matrix4x4& m1, const Matrix4x4& m2);
// 拡大縮小行列
Matrix4x4 MakeScaleMatrix(const Vector3& scale);
// 平行移動
Matrix4x4 MakeTranslateMatrix(const Vector3& translate);

/*---------------------------------
 回転行列
------------------------------------*/

// X軸
Matrix4x4 MakeRotateXMatrix(float radian);
// Y軸
Matrix4x4 MakeRotateYMatrix(float radian);
// Z軸
Matrix4x4 MakeRotateZMatrix(float radian);

// アフィン変換
Matrix4x4 MakeAffineMatrix(const Vector3& scale, const Vector3& rot, const Vector3& translate);

// 透視投影行列
Matrix4x4 MakePerspectiveFovMatrix(float fovY, float aspectRatio, float nearClip, float farClip);

//正射影行列
Matrix4x4 MakeOrthographicMatrix(float left, float top, float right, float bottom, float nearClip, float farClip);

// 逆行列
Matrix4x4 Inverse(const Matrix4x4& m);

// 単位行列
Matrix4x4 MakeIdentityMatrix();

// 正規化
Vector3 Normalize(const Vector3& v);

// 変換
Vector3 Transform(const Vector3& vector, const Matrix4x4& matrix);

Matrix4x4 Add(const Matrix4x4& m1, const Matrix4x4& m2);

Matrix4x4 Subtract(const Matrix4x4& m1, const Matrix4x4& m2);

Vector3 Cross(const Vector3& v1, const Vector3& v2);

float Dot(const Vector3& v1, const Vector3& v2);

// ノルム		  
float Length(const Vector3& v);

Matrix4x4 MakeRotateAxisAngle(const Vector3& axis, float angle);

Matrix4x4 DirectionToDirection(const Vector3& from, const Vector3& to);

// quaternionの積
Quaternion Multiply(const Quaternion& lhs, const Quaternion& rhs);
// 単位quaternion
Quaternion IdentityQuaternion();
// 共役quaternion
Quaternion Conjugate(const Quaternion& quaternion);
// quaternionのnorm
float Norm(const Quaternion& quaternion);
// 正規化したquaternion
Quaternion QNormalize(const Quaternion& quaternion);
// 逆quaternion
Quaternion QInverse(const Quaternion& quaternion);
// 任意軸回転を表すquaternionの生成
Quaternion MakeRotateAxisAngleQuaternion(const Vector3& axis, float angle);
// ベクトルをquaternionで回転させた結果のベクトルを求める
Vector3 RotateVector(const Vector3& vector, const Quaternion& quaternion);
// quaternionから回転行列を求める
Matrix4x4 MakeRotateMatrix(const Quaternion& quaternion);

void MatrixScreenPrintf(Matrix4x4 matrix, const char* name);

void QuaternionScreenPrint(Quaternion q, const char* name);

void Vector3ScreenPrint(Vector3 v, const char* name);

Vector3 operator+(const Vector3& a, const Vector3& b);

Vector3 operator+(const Vector3& a, const float& b);

Vector3 operator-(const Vector3& a, const Vector3& b);

Vector3 operator-(const Vector3& a, const float& b);

Vector3 operator*(const float& a, const Vector3& b);

Vector3 operator/(const Vector3& a, const float& b);

Vector3 operator*(const Vector3& vec, const Matrix4x4& mat);
