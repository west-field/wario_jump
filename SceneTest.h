#pragma once

class SceneTest
{
public:
	SceneTest();
	virtual ~SceneTest();

	//初期化処理、終了処理
	void init();
	void end();

	//ゲームの処理
	bool update();
	//描画
	void draw();

private:

};