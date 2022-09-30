#include "DxLib.h"

#include "SceneTitle.h"

SceneTitle::SceneTitle()
{
	m_fadeBright = 0;
	m_fadeSpeed = 0;
}
SceneTitle::~SceneTitle()
{

}

//����������
void SceneTitle::init()
{
	m_fadeBright = 0;
	m_fadeSpeed = 8;
}
//�I������
void SceneTitle::end()
{
	SetDrawBright(255, 255, 255);
}
//�X�V
bool SceneTitle::update()
{
	m_fadeBright += m_fadeSpeed;

	if (m_fadeBright >= 255)
	{
		m_fadeBright = 255;
		m_fadeSpeed = 0;
	}
	if ((m_fadeBright <= 0) && (m_fadeSpeed < 0))
	{
		//�t�F�[�h�A�E�g���������玟�̃V�[����
		m_fadeBright = 0;
		return true;
	}

	int padState = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	if (m_fadeSpeed == 0)
	{
		if (padState & PAD_INPUT_1)
		{
			m_fadeSpeed = -8;
		}
	}
	

	return false;
}
//�`��
void SceneTitle::draw()
{
	SetDrawBright(m_fadeBright, m_fadeBright, m_fadeBright);//�`��P�x���Z�b�g
	DrawString(20, 20, "SceneMain�̕\��", GetColor(255, 255, 255));
}