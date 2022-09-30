#include "DxLib.h"
#include "game.h"
#include "SceneMain.h"

namespace
{
	// 地面の高さ
	constexpr int kFieldY = Game::kScreenHeight - 64;
}

SceneMain::SceneMain()
{
	m_hPlayer = -1;
	m_hCar = -1;
}
SceneMain::~SceneMain()
{

}

//初期化処理
void SceneMain::init()
{
	m_hPlayer = LoadGraph("data/player.png");
	m_hCar = LoadGraph("data/car.png");

	m_player.setGraphic(m_hPlayer);
	m_player.setup(kFieldY);

	m_car.setGraphic(m_hCar);
	m_car.setup(kFieldY);
}
//終了処理
void SceneMain::end()
{
	DeleteGraph(m_hPlayer);
	DeleteGraph(m_hCar);
}
//更新
bool SceneMain::update()
{
	m_player.update();
	m_car.update();

	//当たり判定
	if (m_player.isCol(m_car))
	{
		m_player.setDead(true);
	}
	//再登場フラグ
	
	if (m_car.isRestart())
	{
		m_car.setup(kFieldY);
		m_player.setDead(false);
	}
	return false;
}
//描画
void SceneMain::draw()
{
	// 地面の描画
	DrawLine(0, kFieldY, Game::kScreenWidth, kFieldY, GetColor(255, 255, 255));
	m_player.draw();
	m_car.draw();
}