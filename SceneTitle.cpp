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

//初期化処理
void SceneTitle::init()
{
	m_fadeBright = 0;
	m_fadeSpeed = 8;
}
//終了処理
void SceneTitle::end()
{
	SetDrawBright(255, 255, 255);
}
//更新
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
		//フェードアウトしきったら次のシーンへ
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
//描画
void SceneTitle::draw()
{
	SetDrawBright(m_fadeBright, m_fadeBright, m_fadeBright);//描画輝度をセット
	DrawString(20, 20, "SceneMainの表示", GetColor(255, 255, 255));
}