#include "GameScene.h"

GameScene::GameScene()
{
}

GameScene::~GameScene()
{
}

void GameScene::Initialize()
{
	c.Initialize();
	t = TextureManager::Load("resources/uvChecker.png");
	s.reset(Sprite::Create({ 0.0f,0.0f }, t));
}

void GameScene::Update()
{
	c.UpdateMatrix();
}

void GameScene::Draw()
{
	s->Draw(c);
}
