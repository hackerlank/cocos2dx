#include "GameOverLayer.h"
#include "TetrisGameLayer.h"
#include "HelloWorldScene.h"
using namespace cocos2d;

CCScene* GameOverLayer::scene()
{
	CCScene * scene = NULL;
	do 
	{
		// 'scene' is an autorelease object
		scene = CCScene::create();
		CC_BREAK_IF(! scene);

		// 'layer' is an autorelease object
		GameOverLayer *layer = GameOverLayer::create();
		CC_BREAK_IF(! layer);

		// add layer as a child to scene
		scene->addChild(layer);
	} while (0);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool GameOverLayer::init()
{
	bool bRet = false;
	do 
	{
		//////////////////////////////////////////////////////////////////////////
		// super init first
		//////////////////////////////////////////////////////////////////////////

		CC_BREAK_IF(! CCLayer::init());

		//////////////////////////////////////////////////////////////////////////
		// add your codes below...
		//////////////////////////////////////////////////////////////////////////

		CC_BREAK_IF(! CCLayerColor::initWithColor(ccc4(255, 255, 255, 255)));


		// 1. Add a menu item with "X" image, which is clicked to quit the program.
		//Background
		CCSize size = CCDirector::sharedDirector()->getWinSize();
		CCSprite *gameBackgroud = CCSprite::create("background.png");
		CC_BREAK_IF(! gameBackgroud);

		gameBackgroud->setPosition(ccp(size.width / 2, size.height / 2));
		this->addChild(gameBackgroud);


		const char *title = "You are a Loser!!!";

		CCLabelTTF* pLabel = CCLabelTTF::create(title, "Arial", 36);
		CC_BREAK_IF(! pLabel);

		pLabel->setPosition(ccp(size.width / 2, size.height * 4 / 5));

		pLabel->setColor(ccc3(255, 255, 255));
		this->addChild(pLabel, 1);

		CCMenuItemImage *restart = CCMenuItemImage::create(
			"restart.png", 
			"restart.png",
			this,
			menu_selector(GameOverLayer::menuCallbackRestart));
		restart->setScale(0.5f);
		restart->setPosition(ccp(size.width / 4, size.height / 2));

		CCMenuItemImage *back = CCMenuItemImage::create(
			"back.png", 
			"back.png",
			this,
			menu_selector(GameOverLayer::menuCallbackBack));
		back->setPosition(ccp((size.width * 3) / 4, size.height / 2));

		CCMenu *menu = CCMenu::create(restart, back, NULL);
		menu->setAnchorPoint(ccp(0, 0));
		menu->setPosition(ccp(0, 0));
		this->addChild(menu);

		bRet = true;
	} while (0);

	return bRet;
}

void GameOverLayer::menuCallbackRestart(CCObject* pSender)
{
	//CCDirector::sharedDirector()->end();
	CCScene *gameRetartScene = TetrisGameLayer::scene();
	CCDirector::sharedDirector()->replaceScene(gameRetartScene);
}

void GameOverLayer::menuCallbackBack(CCObject* pSender)
{
	// "close" menu item clicked
	CCScene *backToMenu = HelloWorld::scene();
	CCDirector::sharedDirector()->replaceScene(backToMenu);
}