#include "HelloWorldScene.h"
/*#include "CodeConvert.h"*/
#include "TetrisGameLayer.h"
using namespace cocos2d;

CCScene* HelloWorld::scene()
{
	CCScene * scene = NULL;
	do 
	{
		// 'scene' is an autorelease object
		scene = CCScene::create();
		CC_BREAK_IF(! scene);

		// 'layer' is an autorelease object
		HelloWorld *layer = HelloWorld::create();
		CC_BREAK_IF(! layer);

		// add layer as a child to scene
		scene->addChild(layer);
	} while (0);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
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
		CCSprite *backgroud = CCSprite::create("MainMenu.png");
		CC_BREAK_IF(! backgroud);

		backgroud->setPosition(ccp(size.width / 2, size.height / 2));
		this->addChild(backgroud);
		// 2. Add a label shows "Hello World".

		// Create a label and initialize with string "Hello World".
// 		const char *title = "俄罗斯方块";
// 		const char *startGame = "开始游戏";
// 		const char *gameSet = "游戏设置";
// 		const char *score = "游戏得分";
// 		const char *gameOver = "游戏结束";

/*		const char *title = "TetrisGame";*/
// 		const char *startGame = "startGame";
// 		const char *gameSet = "gameSet";
// 		const char *score = "score";
// 		const char *gameOver = "gameEnd";

// 		CCLabelTTF* pLabel = CCLabelTTF::create(title, "Arial", 36);
// 		CC_BREAK_IF(! pLabel);
// 
// 		// Get window size and place the label upper. 
// 		pLabel->setPosition(ccp(size.width / 2, size.height * 4 / 5));
// 
// 		pLabel->setColor(ccc3(255, 255, 255));
// 		// Add the label to HelloWorld layer as a child layer.
// 		this->addChild(pLabel, 1);


		// 加入4个行走方向的控制菜单
// 		CCMenuItem *first = CCMenuItemFont::create(startGame, this, menu_selector(HelloWorld::menuCallbackStart));
// 		CCMenuItem *second = CCMenuItemFont::create(gameSet, this, menu_selector(HelloWorld::menuCallbackSet));
// 		CCMenuItem *third = CCMenuItemFont::create(score, this, menu_selector(HelloWorld::menuCallbackScore));
// 		CCMenuItem *forth = CCMenuItemFont::create(gameOver, this, menu_selector(HelloWorld::menuCallbackEnd));


// 		CCMenu *menu = CCMenu::create(first, second, third, forth, NULL);
// 		menu->setColor(ccc3(255, 255, 255));
		// 为了查找方便，给菜单项设置tag
		//down->setTag(kDown);
		//left->setTag(kLeft);
		//right->setTag(kRight);
		//up->setTag(kUp);
		// 菜单项按间距垂直排列
// 		menu->alignItemsVerticallyWithPadding(50);
// 		this->addChild(menu

		CCMenuItemImage *play = CCMenuItemImage::create(
			"play.png", 
			"play.png",
			this,
			menu_selector(HelloWorld::menuCallbackStart));
		play->setAnchorPoint(ccp(0, 0));
		play->setPosition(ccp(size.width / 4, (size.height * 2) / 5));
		

		CCMenuItemImage *end = CCMenuItemImage::create(
			"end.png", 
			"end.png",
			this,
			menu_selector(HelloWorld::menuCallbackEnd));
		end->setAnchorPoint(ccp(0, 0));
		end->setPosition(ccp(size.width / 4, (size.height * 2) / 7));

		CCMenu *menu = CCMenu::create(play, end, NULL);
		menu->setAnchorPoint(ccp(0, 0));
		menu->setPosition(ccp(0, 0));
		this->addChild(menu);


		bRet = true;
	} while (0);

	return bRet;
}

void HelloWorld::menuCallbackStart(CCObject* pSender)
{
	//CCDirector::sharedDirector()->end();
	CCScene *gameStartScene = TetrisGameLayer::scene();
	CCDirector::sharedDirector()->replaceScene(gameStartScene);
}

void HelloWorld::menuCallbackSet(CCObject* pSender)
{
	// "close" menu item clicked
	CCDirector::sharedDirector()->end();
}

void HelloWorld::menuCallbackScore(CCObject* pSender)
{
	// "close" menu item clicked
	CCDirector::sharedDirector()->end();
}

void HelloWorld::menuCallbackEnd(CCObject* pSender)
{
	// "close" menu item clicked
	CCDirector::sharedDirector()->end();
}

