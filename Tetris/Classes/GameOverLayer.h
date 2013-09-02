#ifndef __GAME_OVER_SCENE_H__
#define __GAME_OVER_SCENE_H__

#include "cocos2d.h"
#include "TetrisGameLayer.h"
#include "HelloWorldScene.h"

class GameOverLayer : public cocos2d::CCLayerColor
{
public:
	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();  

	// there's no 'id' in cpp, so we recommand to return the exactly class pointer
	static cocos2d::CCScene* scene();

	//menuItem callback
	void menuCallbackRestart(CCObject* pSender);

	void menuCallbackBack(CCObject* pSender);

	// implement the "static node()" method manually
	CREATE_FUNC(GameOverLayer);
};

#endif  // 