#include "DxLib.h"
#include "game.h"
#include "car.h"

namespace
{
	//待ち時間
	constexpr int kWaitFrameMin = 60;
	constexpr int kWaitFrameMax = 180;

	//車の速度
	constexpr float kSpeed = -20.0f;
}

Car::Car()
{
	m_handle = -1;
	m_fieldY = 0.0f;
	m_waitFrame = 0;
}

void Car::setGraphic(int handle)
{
	m_handle = handle;
	GetGraphSizeF(m_handle, &m_size.x, &m_size.y);
}

void Car::setup(float fieldY)
{
	m_fieldY = fieldY;
	m_pos.x = Game::kScreenWidth + 16.0f;
	m_pos.y = m_fieldY - m_size.y;

	m_vec.x = kSpeed;
	m_vec.y = 0.0f;

	//動き始めるまでの時間を設定 1秒から3秒待つ
	m_waitFrame = GetRand(kWaitFrameMax) + kWaitFrameMin;
}

void Car::update()
{
	if (m_waitFrame > 0)
	{
		m_waitFrame--;
		return;
	}

	updateNormal();
}

void Car::draw()
{
	DrawGraphF(m_pos.x, m_pos.y, m_handle, true);
//	DrawFormatString(0, 0, GetColor(255, 255, 255), "wait:%d", m_waitFrame);
}

//-----------------private-----------------

//まっすぐ進む
void Car::updateNormal()
{
	m_pos += m_vec;
}
//一時停止フェイント
void Car::updateStop()
{

}
//ジャンプする
void Car::updateJump()
{

}
//途中で引き返す(必ず成功)
void Car::updateReturn()
{

}
