#include "DxLib.h"

#include "SceneTest.h"

SceneTest::SceneTest()
{

}
SceneTest::~SceneTest()
{

}

//����������
void SceneTest::init()
{

}
//�I������
void SceneTest::end()
{

}
//�X�V
bool SceneTest::update()
{
	return false;
}
//�`��
void SceneTest::draw()
{
	DrawString(20, 20, "SceneTest�̕\��", GetColor(255, 255, 255));
}