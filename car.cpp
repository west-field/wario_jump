#include "DxLib.h"
#include "game.h"
#include "car.h"

namespace
{
	//�҂�����
	constexpr int kWaitFrameMin = 60;
	constexpr int kWaitFrameMax = 180;

	//�Ԃ̑��x
	constexpr float kSpeed = -20.0f;

	//�W�����v��
	constexpr float kJumpAcc = -18.0f;
	//�d��
	constexpr float kGravity = 0.7f;
	//�ꏊ
	constexpr float kPlace = 300.0f;
}

Car::Car()
{
	m_handle = -1;
	m_fieldY = 0.0f;
	m_moveType = kMoveTypeNormal;
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

	//�����̃o���G�[�V������I��
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

	//�f�o�b�O�p
	m_moveType = kMoveTypeStop;

	//�����n�߂�܂ł̎��Ԃ�ݒ� 1�b����3�b�҂�
	m_waitFrame = GetRand(kWaitFrameMax) + kWaitFrameMin;
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
	DrawGraphF(m_pos.x, m_pos.y, m_handle, true);
	DrawFormatString(0, 0, GetColor(255, 255, 255), "wait:%d", m_waitFrame);
	DrawFormatString(0, 20, GetColor(255, 255, 255), "move:%d", m_moveType);
	DrawFormatString(0, 40, GetColor(255, 255, 255), "pos.x:%3f", m_pos.x);
	DrawFormatString(0, 60, GetColor(255, 255, 255), "pos.y:%d", m_pos.y);
}

//-----------------private-----------------

//�܂������i��
void Car::updateNormal()
{
	m_pos += m_vec;
}
//�ꎞ��~�t�F�C���g
void Car::updateStop()
{
	m_pos += m_vec;
	
}
//�W�����v����
void Car::updateJump()
{
	m_pos += m_vec;
	bool isField = false;
	if (m_pos.y >= m_fieldY - m_size.y)
	{
		m_pos.y = m_fieldY - m_size.y;
		isField = true;
	}
	if (isField)
	{
		m_vec.y = kJumpAcc;//�W�����v�J�n
	}

	m_vec.y += kGravity; 
	
}
//�r���ň����Ԃ�(�K������)
void Car::updateReturn()
{
	m_pos += m_vec;
	
}