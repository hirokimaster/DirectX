#pragma once
#include "engine/Base/WinApp/WinApp.h"
#include "engine/Base/DX/DirectXCommon.h"
#include "engine/Utility/ShaderCompile.h"
#include "engine/GraphicsPipeline/GraphicsPipeline.h"
#include "engine/Utility/ImGuiManager/ImGuiManager.h"
#include "engine/TextureManager/TextureManager.h"
#include "engine/Input/Input.h"
#include "engine/Audio/Audio.h"

class Engine {
public:
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();
	
	/// <summary>
	/// 更新処理
	/// </summary>
	void Run();

	/// <summary>
	/// 終了
	/// </summary>
	int Finalize();

private:
	WinApp* win_;
	DirectXCommon* dxCommon_;
	Audio* audio_;
	ImGuiManager* imguiManager_;
	
};
