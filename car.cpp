#include "DxLib.h"
#include "game.h"
#include "car.h"

namespace
{
	//待ち時間
	constexpr int kWaitFrameMin = 60;
	constexpr int kWaitFrameMax = 180;

	//車の速度
	constexpr float kSpeed = -30.0f;

	//ジャンプ力
	constexpr float kJumpAcc = -18.0f;
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
	m_isReversal = false;


	m_isField = false;
	m_num = 0;
	m_isOutside = false;
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

	//デバッグ用
//	m_moveType = kMoveTypeReturn;

	//動き始めるまでの時間を設定 1秒から3秒待つ
	m_waitFrame = GetRand(kWaitFrameMax) + kWaitFrameMin;
}

void Car::update()
{
	if (m_isOutside)	return;

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
	DrawRectGraphF(m_pos.x, m_pos.y,0,0,(int)m_size.x, (int)m_size.y, m_handle, true, m_isReversal);
	DrawFormatString(0, 0, GetColor(255, 255, 255), "wait:%d", m_waitFrame);
	DrawFormatString(0, 20, GetColor(255, 255, 255), "move:%d", m_moveType);
	DrawFormatString(0, 40, GetColor(255, 255, 255), "pos.x:%3f", m_pos.x);
	DrawFormatString(0, 60, GetColor(255, 255, 255), "pos.y:%d", m_pos.y);
}

//-----------------private-----------------

//まっすぐ進む
void Car::updateNormal()
{
	if (m_isOutside)	return;

	m_pos += m_vec;

	setOutside();
}
//一時停止フェイント
void Car::updateStop()
{
	if (m_isOutside)	return;

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

	setOutside();
}
//ジャンプする
void Car::updateJump()
{

	if (m_isOutside)	return;

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

	setOutside();
	
}
//途中で引き返す(必ず成功)
void Car::updateReturn()
{
	if (m_isOutside)	return;

	if (m_pos.x < kPlace - 50)
	{
		m_isField = true;
	}
	
	if (m_isField)
	{
		m_pos -= m_vec;
		m_isReversal = true;
	}
	else
	{
		m_pos += m_vec;
	}
	setOutside();
}

void Car::setOutside()
{
	if (m_pos.x < 0 - m_size.x || m_pos.x > Game::kScreenWidth + 16.0f)
	{
		m_isOutside = true;
	}
}