/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.

 http://www.cocos2d-x.org

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "HelloWorldScene.h"
#include "StartWindowScene.h"
#include "ui/CocosGUI.h"

using namespace std;
USING_NS_CC;
Scene* HelloWorld::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::createWithSize(Size(1024, 768));
	// 'layer' is an autorelease object
	auto layer = HelloWorld::create();
	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
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

	animateStop = SpriteFrame::create("boy.png", Rect(30, 25, 35, 75));

	Vector <SpriteFrame*> animFrames;
	animFrames.pushBack(SpriteFrame::create("boy.png", Rect(30, 25, 35, 75)));
	animFrames.pushBack(SpriteFrame::create("boy.png", Rect(365, 122, 43, 78)));
	animFrames.pushBack(SpriteFrame::create("boy.png", Rect(408, 122, 46, 75)));
	animFrames.pushBack(SpriteFrame::create("boy.png", Rect(465, 122, 43, 73)));
	animFrames.pushBack(SpriteFrame::create("boy.png", Rect(514, 121, 44, 79)));
	animFrames.pushBack(SpriteFrame::create("boy.png", Rect(560, 121, 41, 79)));
	auto animation = Animation::createWithSpriteFrames(animFrames, 0.1f);
	animation->setLoops(-1);
	animate = Animate::create(animation);

	Vector <SpriteFrame*> animFramesDown;
	animFramesDown.pushBack(SpriteFrame::create("boy.png", Rect(210, 237, 66, 53)));
	auto animationDown = Animation::createWithSpriteFrames(animFramesDown, 0.1f);
	animationDown->setLoops(-1);
	animateDown = Animate::create(animationDown);

	Vector <SpriteFrame*> animFramesJump;
	animFrames.pushBack(SpriteFrame::create("boy.png", Rect(30, 25, 35, 75)));
	auto animationJump = Animation::createWithSpriteFrames(animFramesJump, 0.1f);
	animationJump->setLoops(-1);
	animateJump = Animate::create(animationJump);

	auto listener = EventListenerKeyboard::create();
	listener->onKeyPressed = CC_CALLBACK_2(HelloWorld::onKeyPressed, this);
	listener->onKeyReleased = CC_CALLBACK_2(HelloWorld::onKeyReleased, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	animate->retain();
	animateDown->retain();
	this->scheduleUpdate();
	return true;
}

void HelloWorld::update(float dt) {
	auto boyPosition = boy->getPosition();
	if (l_move) {
		boy->setPosition(Vec2(boyPosition.x - 5, boyPosition.y));
		boy->setFlipX(true);
	}
	if (r_move) {
		boy->setPosition(Vec2(boyPosition.x + 5, boyPosition.y));
		boy->setFlipX(false);
	}
}

void HelloWorld::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
	if ((int)keyCode == 27 && !isMove) {
		r_move = true;
		isMove = true;
		if (!b_move)
			boy->runAction(animate);
	}
	if ((int)keyCode == 26 && !isMove) {
		l_move = true;
		isMove = true;
		if (!b_move)
			boy->runAction(animate);
	}
	if ((int)keyCode == 29 && isMove)
	{
		b_move = true;
		boy->stopAction(animate);
		boy->runAction(animateDown);
	}

	if ((int)keyCode == 59) {
		jumpBy = JumpBy::create(0.5, Vec2(0, 0), 50, 1);
		boy->runAction(jumpBy);
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
	if ((int)keyCode == 29)
	{
		b_move = false;
		boy->stopAction(animateDown);
		boy->setSpriteFrame(animateStop);
	}
}