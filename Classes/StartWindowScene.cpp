#include "StartWindowScene.h"
#include "HelloWorldScene.h"
#include "ui/CocosGUI.h"

using namespace std;
USING_NS_CC;

Scene* StartWindowScene::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::createWithSize(Size(1024, 768));
	// 'layer' is an autorelease object
	auto layer = StartWindowScene::create();
	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}
bool StartWindowScene::init()
{
	if (!Layer::init())
	{
		return false;
	}
	auto s = Director::getInstance()->getWinSize();
	auto button1 = ui::Button::create("myLabel.png");

	button1->setPosition(Vec2(s.width * 0.3, s.height * 0.5));

	button1->setColor(Color3B::BLUE);

	button1->setScale(0.35);

	button1->setAnchorPoint(Vec2(0.5, 0.5));

	button1->setTitleText("Example");
	button1->setTitleFontSize(100);

	button1->addClickEventListener(CC_CALLBACK_0(StartWindowScene::controlWork, this));

	this->addChild(button1, 5);

	this->scheduleUpdate();

	return true;
}

void StartWindowScene::update(float dt)
{
}

void StartWindowScene::controlWork()
{
	auto scene = HelloWorld::createScene();
	Director::getInstance()->replaceScene(scene);
}