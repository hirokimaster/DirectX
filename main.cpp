#include "WinApp.h"
#include "DirectXCommon.h"
#include "ShaderCompile.h"
#include "Sprite.h"
#include "GameScene.h"
#include "GraphicsPipeline.h"

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	WinApp* win = WinApp::GetInstance();
	DirectXCommon* dxCommon = DirectXCommon::GetInstance();
	Sprite* sprite = Sprite::GetInstance();

	// ゲームシーンの初期化
	GameScene* gameScene = new GameScene();
	gameScene->Initialize();
	
	// ウィンドウの作成
	win->CreateGameWindow(L"DirectXGame");
	// DirectX初期化
	dxCommon->Initialize(win);
	GraphicsPipeline::Initialize();
	sprite->Initialize();

	WorldTransform transform;
	transform.Initialize();
	
	// メインループ
	while (true) {
		// メッセージ処理
		if (win->ProcessMessage()) {
			break;
		}

		// ゲームの処理
		transform.translate = { 0.0f,0.0f,0.0f };
		transform.UpdateMatrix();

		// 描画前処理
		dxCommon->PreDraw();
		// ゲームシーン描画
		//gameScene->Draw();
		
		// 三角形描画
		sprite->DrawTriangle(transform);

		// 描画後処理
		dxCommon->PostDraw();


	}

	CloseWindow(win->GetHwnd());

	return 0;
}