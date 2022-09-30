#pragma once

class SceneTitle
{
public:
	SceneTitle();
	virtual ~SceneTitle();

	//初期化処理、終了処理
	void init();
	void end();

	//ゲームの処理 シーンの切り替え時はtrue
	bool update();
	//描画
	void draw();

private:
	//フェード処理
	int m_fadeBright;
	//フェード速度
	int m_fadeSpeed;
};