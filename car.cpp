#include "DxLib.h"
#include "game.h"
#include "car.h"

namespace
{
	//待ち時間
	constexpr int kWaitFrameMin = 60;
	constexpr int kWaitFrameMax = 180;

	//車の速度
	constexpr float kSpeed = -25.0f;

	//ジャンプ力
	constexpr float kJumpAcc = -20.0f;
	//重力
	constexpr float kGravity = 0.7f;
	//場所
	constexpr float kPlace = 400.0f;
}

Car::Car()
{
	m_handle = -1;
	m_fieldY = 0.0f;
	m_moveType = kMoveTypeNormal;
	m_waitFrame = 0;

	m_isRestart = false;

	m_isField = false;
	m_num = 0;
}

void Car::setGraphic(int handle)
{
	m_handle = handle;
	GetGraphSizeF(m_handle, &m_size.x, &m_size.y);
}

//初期化はまとめる
void Car::setup(float fieldY)
{
	m_fieldY = fieldY;
	m_pos.x = Game::kScreenWidth + 16.0f;
	m_pos.y = m_fieldY - m_size.y;

	m_vec.x = kSpeed;
	m_vec.y = 0.0f;

	//動きのバリエーションを選択
	int randNum = GetRand(99);
	if (randNum < 38)
	{
		m_moveType = kMoveTypeNormal;
	}
	else if (randNum < 38 + 30)
	{
		m_moveType = kMoveTypeStop;
	}
	else if (randNum < 38 + 30 + 30)
	{
		m_moveType = kMoveTypeJump;
	}
	else
	{
		m_moveType = kMoveTypeReturn;
	}
	//動き始めるまでの時間を設定 1秒から3秒待つ
	m_waitFrame = GetRand(kWaitFrameMax) + kWaitFrameMin;

	m_isRestart = false;
	m_isField = false;
	m_num = 0;
}

void Car::update()
{
	if (m_waitFrame > 0)
	{
		m_waitFrame--;
		return;
	}

	switch (m_moveType)
	{
	case kMoveTypeNormal:
		updateNormal();
		break;
	case kMoveTypeStop:
		updateStop();
		break;
	case kMoveTypeJump:
		updateJump();
		break;
	case kMoveTypeReturn:
		updateReturn();
		break;
	default:
		updateNormal();
		break;
	}
}

void Car::draw()
{
	if (m_vec.x <= 0.0f)
	{
		DrawGraphF(m_pos.x, m_pos.y, m_handle, true);
	}
	else
	{
		DrawTurnGraphF(m_pos.x, m_pos.y, m_handle, true);
	}

	DrawFormatString(0, 0, GetColor(255, 255, 255), "move%d", m_moveType);
}

bool Car::isRestart()
{
	return m_isRestart;
}

//-----------------private-----------------

//まっすぐ進む
void Car::updateNormal()
{
	m_pos += m_vec;

	if (m_pos.x < 0 - m_size.x)
	{
		m_isRestart = true;
	}
}
//一時停止フェイント
void Car::updateStop()
{
	if (m_pos.x < kPlace)
	{
		m_isField = true;
	}
	
	if (m_isField && m_num <= 100)
	{
		m_num++;
	}
	else //if(!m_isField)
	{
		m_pos += m_vec;
	}

	if (m_isField && m_num > 100)
	{
		m_pos += m_vec;
	}

	if (m_pos.x < 0 - m_size.x)
	{
		m_isRestart = true;
	}
}
//ジャンプする
void Car::updateJump()
{
	m_pos += m_vec;
	bool isField = false;
	if (m_pos.y >= m_fieldY - m_size.y)
	{
		m_pos.y = m_fieldY - m_size.y;
		isField = true;
	}
	if (isField && m_pos.x < kPlace)
	{
		m_vec.y = kJumpAcc;//ジャンプ開始
	}

	m_vec.y += kGravity; 

	if (m_pos.x < 0 - m_size.x)
	{
		m_isRestart = true;
	}
	
}
//途中で引き返す(必ず成功)
void Car::updateReturn()
{
	//いったん止まって引き返す　m_stopFrame で止まって　ベクトルを反転させる

	if (m_pos.x < kPlace - 50)
	{
		m_isField = true;
	}
	
	if (m_isField)
	{
		m_pos -= m_vec;
	}
	else
	{
		m_pos += m_vec;
	}
	// 画面外に出たら終了

	if (m_pos.x > Game::kScreenWidth + 16.0f)
	{
		m_isRestart = true;
	}
}