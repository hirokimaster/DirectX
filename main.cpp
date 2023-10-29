#include "WinApp.h"
#include "DirectXCommon.h"
#include "ShaderCompile.h"
#include "Sprite.h"
#include "GameScene.h"
#include "GraphicsPipeline.h"
#include "ImGuiManager.h"
#include "TextureManager.h"

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	
	WinApp* win = WinApp::GetInstance();
	DirectXCommon* dxCommon = DirectXCommon::GetInstance();
	TextureManager::GetInstance()->Initialize();
	Sprite* sprite = Sprite::GetInstance();

	// ゲームシーンの初期化
	//GameScene* gameScene = new GameScene();
	//gameScene->Initialize();
	
	// ウィンドウの作成
	win->CreateGameWindow(L"DirectXGame");
	// DirectX初期化
	dxCommon->Initialize(win);
	GraphicsPipeline::Initialize();
	sprite->Initialize();
	uint32_t texHandle = TextureManager::Load("resources/uvChecker.png");
	
	// ImGuiの初期化
	ImGuiManager* imguiManager = ImGuiManager::GetInstance();
	imguiManager->Initialize(win, dxCommon);

	WorldTransform transform;
	ViewProjection viewProjection;
	viewProjection.Initialize();
	transform.Initialize();
	
	// メインループ
	while (true) {
		// メッセージ処理
		if (win->ProcessMessage()) {
			break;
		}

		//imgui受付開始
		imguiManager->Begin();
		// 開発用のUIの処理。実際に開発用のUIを出す場合はここをゲーム固有の処理に置き換える
		ImGui::ShowDemoWindow();

		// ゲームの処理
		viewProjection.UpdateMatrix();
		transform.UpdateMatrix();
		transform.rotate.y += 0.003f;

		imguiManager->End();

		// 描画前処理
		dxCommon->PreDraw();
		// ゲームシーン描画
		//gameScene->Draw();
		
		// 三角形描画
		sprite->DrawTriangle(transform, viewProjection, texHandle);

		//imguiManager->Draw();
		// 描画後処理
		dxCommon->PostDraw();


	}

	imguiManager->Finalize();

	// COMの終了処理
	CoUninitialize();

	CloseWindow(win->GetHwnd());

	return 0;
}