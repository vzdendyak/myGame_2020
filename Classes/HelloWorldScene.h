#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__
#include "ui/CocosGUI.h";
#include "cocos2d.h";
class HelloWorld : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	virtual void update(float dt);
	void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
	void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
	CREATE_FUNC(HelloWorld);
private:
	cocos2d::Sprite* boy;
	cocos2d::JumpBy* jumpBy;
	cocos2d::Animate* animate;
	cocos2d::Animate* animateJump;
	cocos2d::Animate* animateFastMove;
	cocos2d::Animate* animateDown;
	cocos2d::SpriteFrame* animateStop;

	bool r_move = false, l_move = false, b_move = false, isMove = false;
};
#endif // __HELLOWORLD_SCENE_H__