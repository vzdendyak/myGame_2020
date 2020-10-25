#include "HelloWorldScene.h"
USING_NS_CC;
int pixelCount = 3;

Scene* HelloWorld::createScene()
{
	auto scene = Scene::create();
	auto layer = HelloWorld::create();
	scene->addChild(layer);
	return scene;
}
bool HelloWorld::init()
{
	if (!Layer::init())
	{
		return false;
	}
	auto visibleSize = &Director::getInstance()->getVisibleSize();

	boy = Sprite::create("boy.png", Rect(30, 25, 35, 75));
	boy->setPosition(Vec2(visibleSize->width / 2, visibleSize->height / 2));
	boy->setScale(2.0);
	this->addChild(boy);

	Vector <SpriteFrame*> animFrames;
	animFrames.pushBack(SpriteFrame::create("boy.png", Rect(365, 122, 43, 78)));
	animFrames.pushBack(SpriteFrame::create("boy.png", Rect(408, 122, 46, 75)));
	animFrames.pushBack(SpriteFrame::create("boy.png", Rect(465, 122, 43, 73)));
	animFrames.pushBack(SpriteFrame::create("boy.png", Rect(514, 121, 44, 79)));
	animFrames.pushBack(SpriteFrame::create("boy.png", Rect(560, 121, 41, 79)));	
	auto animation = Animation::createWithSpriteFrames(animFrames, 0.1f);
	animation->setLoops(-1);
	animate = Animate::create(animation);

	Vector <SpriteFrame*> animFramesFastMove;
	animFramesFastMove.pushBack(SpriteFrame::create("boy.png", Rect(23, 221, 55, 69)));
	animFramesFastMove.pushBack(SpriteFrame::create("boy.png", Rect(83, 221, 56, 69)));
	animFramesFastMove.pushBack(SpriteFrame::create("boy.png", Rect(140, 221, 56, 69)));
	auto animationFastMove = Animation::createWithSpriteFrames(animFramesFastMove, 0.1f);
	animationFastMove->setLoops(-1);
	animateFastMove = Animate::create(animationFastMove);

	auto listener = EventListenerKeyboard::create();
	listener->onKeyPressed = CC_CALLBACK_2(HelloWorld::onKeyPressed, this);
	listener->onKeyReleased = CC_CALLBACK_2(HelloWorld::onKeyReleased, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	animate->retain();
	animateFastMove->retain();
	this->scheduleUpdate();
	return true;
}

void HelloWorld::update(float dt) {
	auto boyPosition = boy->getPosition();
	if (l_move) {
		boy->setPosition(Vec2(boyPosition.x - pixelCount, boyPosition.y));
		boy->setFlipX(true);
	}
	if (r_move) {
		boy->setPosition(Vec2(boyPosition.x + pixelCount, boyPosition.y));
		boy->setFlipX(false);
	}
}

void HelloWorld::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
	if ((int)keyCode == 27 && !isMove) {
		r_move = true;
		isMove = true;
		boy->runAction(animate);
	}
	if ((int)keyCode == 26 && !isMove) {
		l_move = true;
		isMove = true;
		boy->runAction(animate);
	}
	if ((int)keyCode == 59) {
		jumpBy = JumpBy::create(0.5, Vec2(0, 0), 50, 1);
		boy->runAction(jumpBy);
	}
	if ((int)keyCode == 12 && isMove) {
		pixelCount = 10;
		boy->stopAction(animate);
		boy->runAction(animateFastMove);
	}
	log("Key with keycode %d pressed", keyCode);
}

void HelloWorld::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{
	animateStop = SpriteFrame::create("boy.png", Rect(30, 25, 35, 75));
	if ((int)keyCode == 27) {
		r_move = false;
		isMove = false;
		boy->stopAction(animate);
		boy->setSpriteFrame(animateStop);
	}
	if ((int)keyCode == 26) {
		l_move = false;
		isMove = false;
		boy->stopAction(animate);
		boy->setSpriteFrame(animateStop);
	}
	if ((int)keyCode == 12) {
		pixelCount = 3;
		boy->stopAction(animateFastMove);
		boy->setSpriteFrame(animateStop);
	}
}