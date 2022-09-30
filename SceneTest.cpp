#include "DxLib.h"

#include "SceneTest.h"

SceneTest::SceneTest()
{

}
SceneTest::~SceneTest()
{

}

//初期化処理
void SceneTest::init()
{

}
//終了処理
void SceneTest::end()
{

}
//更新
bool SceneTest::update()
{
	return false;
}
//描画
void SceneTest::draw()
{
	DrawString(20, 20, "SceneTestの表示", GetColor(255, 255, 255));
}