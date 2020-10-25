#ifndef __STARTWINDOW_SCENE_H__
#define __STARTWINDOW_SCENE_H__
#include "ui/CocosGUI.h";
#include "cocos2d.h";

#pragma once
class StartWindowScene : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	CREATE_FUNC(StartWindowScene);
	virtual void update(float dt);
	void lab51();
	void lab52();
	void controlWork();
};
#endif // __HELLOWORLD_SCENE_H__