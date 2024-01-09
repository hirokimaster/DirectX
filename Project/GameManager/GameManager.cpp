#include "GameManager.h"
#include "GameScene/GameScene.h"
#include "TitleScene/TitleScene.h"


GameManager::GameManager() {
	// 各シーンの配列
	sceneArr_[TITLE] = std::make_unique<TitleScene>();
	sceneArr_[GAME] = std::make_unique<GameScene>();

	// 初期シーン
	currentSceneNo_ = TITLE;

}

GameManager::~GameManager() {}

void GameManager::Run() {

	sceneArr_[currentSceneNo_]->Update();
	// シ－ン変更のチェック
	if (prevSceneNo_ != currentSceneNo_) {
		sceneArr_[currentSceneNo_]->Initialize();

	}
}

void GameManager::Initialize()
{
	// シーンのチェック
	prevSceneNo_ = currentSceneNo_;
	currentSceneNo_ = sceneArr_[currentSceneNo_]->GetSceneNo();
	sceneArr_[currentSceneNo_]->Initialize();

}

void GameManager::Draw()
{
	sceneArr_[currentSceneNo_]->Draw();

}