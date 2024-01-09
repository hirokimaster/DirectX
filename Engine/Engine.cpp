#include "Engine.h"

/// <summary>
/// 初期化
/// </summary>
void Engine::Initialize(){

	// COMの初期化
	CoInitializeEx(0, COINIT_MULTITHREADED);

	win_ = WinApp::GetInstance();
	dxCommon_ = DirectXCommon::GetInstance();
	audio_ = Audio::GetInstance();


	// ウィンドウの作成
	win_->CreateGameWindow(L"LE2B_15_ニヘイ_リュウダイ_STG");
	// DirectX初期化
	dxCommon_->Initialize(win_);
	Input::Initialize();
	audio_->Initialize();
	GraphicsPipeline::Initialize();
	TextureManager::GetInstance()->Initialize();

	// シーンの初期化
	gameManager_ = std::make_unique<GameManager>();
	gameManager_->Initialize();

	// ImGuiの初期化
	imguiManager_ = ImGuiManager::GetInstance();
	imguiManager_->Initialize(win_, dxCommon_);
}

/// <summary>
/// 更新処理
/// </summary>
void Engine::Run(){

	// メインループ
	while (true) {
		// メッセージ処理
		if (win_->ProcessMessage()) {
			break;
		}

		// input
		Input::Update();
		//imgui受付開始
		imguiManager_->Begin();

		// ゲームの処理
		gameManager_->Run();

		//imguiManager_->End();

		// 描画前処理
		dxCommon_->PreDraw();

		// ゲームシーン描画
		gameManager_->Draw();

		imguiManager_->End();

		imguiManager_->Draw();
		// 描画後処理
		dxCommon_->PostDraw();

	}

}

/// <summary>
/// 終了
/// </summary>
int Engine::Finalize(){

	imguiManager_->Finalize();
	// ゲームウィンドウ破棄
	win_->TerminateGameWindow();

	return 0;
}
