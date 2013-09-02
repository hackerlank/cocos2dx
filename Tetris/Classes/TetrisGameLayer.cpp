#include "TetrisGameLayer.h"

#include "TetrisDataHandle.h"

static TetrisGameLayer * s_sharedTetrisGameLayer = NULL;

TetrisGameLayer * TetrisGameLayer::getSharedTetrisGameLayer()
{
	if (! s_sharedTetrisGameLayer)
	{
		s_sharedTetrisGameLayer = TetrisGameLayer::create();
	}
	return s_sharedTetrisGameLayer;
}

cocos2d::CCScene* TetrisGameLayer::scene()
{
	CCScene * scene = NULL;
	do
	{
		scene = CCScene::create();
		CC_BREAK_IF(! scene);

		TetrisGameLayer *layer = TetrisGameLayer::create();
		CC_BREAK_IF(! layer);

		scene->addChild(layer);
	} while(0);

	return scene;
}

// TetrisGameLayer* TetrisGameLayer::createWithStart()
// {
// 	TetrisGameLayer *pRet = getSharedTetrisGameLayer();
// 	if (pRet && pRet->initWithStart())
// 	{
// 		pRet->autorelease();
// 		return pRet;
// 	}
// 	else
// 	{
// 		CC_SAFE_DELETE(pRet);
// 		return NULL;
// 	}
// }

bool TetrisGameLayer::init()
{
	bool bRet = false;
	do 
	{
		CC_BREAK_IF(! CCLayer::init());

		CC_BREAK_IF(! CCLayerColor::initWithColor(ccc4(255, 255, 255, 255)));

		s_sharedTetrisGameLayer = this;

		score = 0;

		this->setTouchMode(kCCTouchesOneByOne);
		this->setTouchEnabled(true);

		isRunning = true;
		isClick = false;
		level = 1;
		CCDirector::sharedDirector()->resume();

		CCSize size = CCDirector::sharedDirector()->getWinSize();

		CCSprite *gameBackgroud = CCSprite::create("background.png");
		CC_BREAK_IF(! gameBackgroud);

		gameBackgroud->setPosition(ccp(size.width / 2, size.height / 2));
		this->addChild(gameBackgroud);

		CCSprite *gameBox = CCSprite::create("gamebox.png");
		CC_BREAK_IF(! gameBox);
		gameBox->setAnchorPoint(ccp(0, 0));
		/*gameBox->setPosition(ccp(10, 100));*/
		gameBox->setPosition(ccp(10, 100));
		this->addChild(gameBox);

		CCMenuItemImage *left = CCMenuItemImage::create(
			"left.png", 
			"left.png",
			this,
			menu_selector(TetrisGameLayer::leftButtonPressed));
		/*left->setScale(0.3f);*/
		left->setAnchorPoint(ccp(0, 0));
		left->setPosition(ccp(0, 20));

		CCMenuItemImage *right = CCMenuItemImage::create(
			"right.png", 
			"right.png",
			this,
			menu_selector(TetrisGameLayer::rightButtonPressed));
		/*right->setScale(0.3f);*/
		right->setAnchorPoint(ccp(0, 0));
		right->setPosition(ccp(size.width / 2 + size.width / 4, 20));

		CCMenuItemImage *down = CCMenuItemImage::create(
			"down.png", 
			"down.png",
			this,
			menu_selector(TetrisGameLayer::downButtonPressed));
		/*down->setScale(0.3f);*/
		down->setAnchorPoint(ccp(0, 0));
		down->setPosition(ccp(size.width / 4, 20));

		CCMenuItemImage *rotate = CCMenuItemImage::create(
			"rotate.png", 
			"rotate.png",
			this,
			menu_selector(TetrisGameLayer::rotateButtonPressed));
		/*rotate->setScale(0.5f);*/
		rotate->setAnchorPoint(ccp(0, 0));
		rotate->setPosition(ccp(size.width / 2, 20));

		CCMenuItemImage *pause = CCMenuItemImage::create(
			"pause.png", 
			"resume.png",
			this,
			menu_selector(TetrisGameLayer::pauseButtonPressed));
		/*pause->setScale(0.3f);*/
		rotate->setAnchorPoint(ccp(0, 0));
		pause->setPosition(ccp(size.width - 60, size.height - 50));

		CCMenuItemImage *back = CCMenuItemImage::create(
			"back.png", 
			"back.png",
			this,
			menu_selector(TetrisGameLayer::backToMainMenu));
		/*back->setPosition(ccp(size.width - 60, size.height - 400));*/
		back->setPosition(ccp(size.width - 60, size.height - 120));

		CCMenu *menu = CCMenu::create(left, down, right, rotate, pause, back, NULL);
		menu->setAnchorPoint(ccp(0, 0));
		menu->setPosition(ccp(0, 0));
		this->addChild(menu);

		CCSprite *_score = CCSprite::create("score.png");
		CC_BREAK_IF(! _score);
		/*_score->setPosition(ccp(size.width - 60, size.height - 300));*/
		_score->setPosition(ccp(size.width - 60, size.height - 400));
		this->addChild(_score);

		lblScore = CCLabelTTF::create("000000", "Arial", 22);
		CC_BREAK_IF(! lblScore);
		lblScore->setColor(ccc3(255, 255, 0));
		/*lblScore->setPosition(ccp(size.width - 60, size.height - 295));*/
		lblScore->setPosition(ccp(size.width - 60, size.height - 405));
		this->addChild(lblScore);

		CCSprite *_level = CCSprite::create("lv.png");
		CC_BREAK_IF(! _level);
		/*_score->setPosition(ccp(size.width - 60, size.height - 300));*/
		_level->setPosition(ccp(size.width - 60, size.height - 500));
		this->addChild(_level);

		lblLevel = CCLabelTTF::create("1", "Arial", 22);
		CC_BREAK_IF(! lblLevel);
		lblLevel->setColor(ccc3(255, 255, 0));
		/*lblScore->setPosition(ccp(size.width - 60, size.height - 295));*/
		lblLevel->setPosition(ccp(size.width - 60, size.height - 505));
		this->addChild(lblLevel);

		CCSprite *next = CCSprite::create("next.png");
		CC_BREAK_IF(! next);
		/*next->setPosition(ccp(size.width - 60, size.height - 170));*/
		next->setPosition(ccp(size.width - 60, size.height - 250));
		this->addChild(next);

		int colum = 10;
		float width = 34;/*size.width / colum*/
		int row = 20;/*(size.height - 200) / width*/

		TetrisDataHandle *datahandle = TetrisDataHandle::getSharedTetrisDataHandle();

		CCSize cs = CCSizeMake(width, width);

		_row = row;
		_colum = colum;
		_width = width;
		_height = width;//?

		datahandle->initWith_C_R_S(colum, row, cs);

		//drawRect = CCRect(20, 50, (colum - 1) * width, row * width);

		blockParent = CCNode::create();
		/*blockParent->setAnchorPoint(ccp(0, 0));*/
		blockParent->setPosition(ccp(10, 100));
		this->addChild(blockParent);

		//ÎÆÀí
		CCTexture2D *texture1 = CCTextureCache::sharedTextureCache()->addImage("pause.png");
		pausePreFrame = CCSpriteFrame::createWithTexture(texture1, CCRect(0, 0, 90, 60));

		CCTexture2D *texture2 = CCTextureCache::sharedTextureCache()->addImage("resume.png");
		pauseAfterFrame = CCSpriteFrame::createWithTexture(texture2, CCRect(0, 0, 90, 60));

		pausePreFrame->retain();
		pauseAfterFrame->retain();
		/*startGame();*/
		randomTetrisType();
		currentHandleType = nextHandleType;
		currentHandleType->init();

		nextTypeFrame = NULL;
		randomTetrisType();
		nextHandleType = NULL;
		drawNextType();


		this->schedule(schedule_selector(TetrisGameLayer::update), 0.5f);
		this->schedule(schedule_selector(TetrisGameLayer::down), 0.01f);
		bRet = true;
	} while (0);

	return bRet;
}

void TetrisGameLayer::update(float dt)
{
	if (!currentHandleType->T_playerHandle(DROPDOWN))
	{
		isClick = false;
		for (int i = 0; i < _colum; ++i)
		{
			if (TetrisDataHandle::getSharedTetrisDataHandle()->tetrisStateArray[(_row - 1) * _colum + i])
			{
				CCDirector::sharedDirector()->replaceScene(GameOverLayer::scene());
			}
		}
		delete currentHandleType;
		currentHandleType = NULL;

		currentHandleType = nextHandleType;
		nextHandleType = NULL;
		while (TetrisDataHandle::getSharedTetrisDataHandle()->h_checkWillDisappearBlocks())
		{
			blockParentChildDropDown();
			int rowCounts = TetrisDataHandle::getSharedTetrisDataHandle()->disappearRowCount;
			if (rowCounts >= 2)
				score += 20 * rowCounts;
			else
				score += 10 * rowCounts;
			runChangeScore();
			if (score >= 600)
			{
				level = 4;

				char temStr[3] = {};
				sprintf(temStr, "%d", level);
				lblLevel->setString(temStr);

				this->unschedule(schedule_selector(TetrisGameLayer::update));
				this->schedule(schedule_selector(TetrisGameLayer::update), 0.1f);
			}
			else 
				if (score >= 400)
				{
					level = 3;

					char temStr[3] = {};
					sprintf(temStr, "%d", level);
					lblLevel->setString(temStr);

					this->unschedule(schedule_selector(TetrisGameLayer::update));
					this->schedule(schedule_selector(TetrisGameLayer::update), 0.2f);
				} else 
					  if (score >= 200)
					  {
						  level = 2;
						  
						  char temStr[3] = {};
						  sprintf(temStr, "%d", level);
						  lblLevel->setString(temStr);
						  
						  this->unschedule(schedule_selector(TetrisGameLayer::update));
						  this->schedule(schedule_selector(TetrisGameLayer::update), 0.3f);
					  }
		}	
		currentHandleType->init();
	}
	if (! nextHandleType)
	{
		randomTetrisType();
		drawNextType();
	}
}

void TetrisGameLayer::runChangeScore()
{
	char temStr[20] = {};
	sprintf(temStr, "%06d", score);
	lblScore->setString(temStr);
// 	int temScore = atoi(lblScore->getString());
// 	int addScore = score - temScore;
// 	char temStr[20] = {};
// 	if (abs(addScore) > 10)
// 	{
// 		temScore += addScore / 10;
// 		sprintf(temStr, "%06d", temScore);
// 		lblScore->setString(temStr);
// 	}
// 	else
// 		if (abs(addScore) > 2 && abs(addScore) <= 10)
// 		{
// 			temScore += addScore / abs(addScore);
// 			sprintf(temStr, "%06d", temScore);
// 			lblScore->setString(temStr);
// 		}
// 		else
// 		{
// 			sprintf(temStr, "%06d", score);
// 			lblScore->setString(temStr);
// 		}
}
// void TetrisGameLayer::onEnter(void)
// {
// 	CCLayer::onEnter();
// 
// 	this->setTouchMode(kCCTouchesOneByOne);
// 	this->setTouchEnabled(true);
// }
// 
// void TetrisGameLayer::onExit(void)
// {
// 	CCLayer::onExit();
// 	CCDirector::sharedDirector()->end();
//  }
// 
// void TetrisGameLayer::onEnterTransitionDidFinish(void)
// {
// 	CCLayer::onEnterTransitionDidFinish();
// }

// void TetrisGameLayer::draw(void)
// {
// 	//CCLog("_colum:%d, _row:%d", _colum, _row);
// 	for (int i = 0; i <= _colum; ++i)
// 	{//ÊúÏß
// 		CCPoint s = ccp(i * _width, 0);
// 		CCPoint e = ccp(i * _width, 800);
// 		ccDrawLine(s, e);
// 	}
// 
// 	for (int j = 0; j <= _row; ++j)
// 	{//ºáÏß
// 		CCPoint s = ccp(0, j * _height);
// 		CCPoint e = ccp(480, j * _height);
// 		ccDrawLine(s, e);
// 	}
// }

// void TetrisGameLayer::startGame()
// {
// 	randomTetrisType();
// }

void TetrisGameLayer::drawNextType()
{
	if (nextTypeFrame)
	{
		nextTypeFrame->setVisible(false);
		nextTypeFrame->release();
	}
	CCSize size = CCDirector::sharedDirector()->getWinSize();
	switch(nextType)
	{
	case 0:
		nextTypeFrame = CCSprite::create("I.png");
		CC_BREAK_IF(! nextTypeFrame);
		/*nextTypeFrame->setAnchorPoint(ccp(0, 0));*/
		/*nextTypeFrame->setPosition(ccp(size.width - 60, size.height - 180));*/
		nextTypeFrame->setPosition(ccp(size.width - 60, size.height - 250));
		this->addChild(nextTypeFrame);
		break;
	case 1:
		nextTypeFrame = CCSprite::create("L.png");
		CC_BREAK_IF(! nextTypeFrame);
		/*nextTypeFrame->setAnchorPoint(ccp(0, 0));*/
		/*nextTypeFrame->setPosition(ccp(size.width - 60, size.height - 180));*/
		nextTypeFrame->setPosition(ccp(size.width - 60, size.height - 250));
		this->addChild(nextTypeFrame);
		break;
	case 2:
		nextTypeFrame = CCSprite::create("O.png");
		CC_BREAK_IF(! nextTypeFrame);
		/*nextTypeFrame->setAnchorPoint(ccp(0, 0));*/
		/*nextTypeFrame->setPosition(ccp(size.width - 60, size.height - 180));*/
		nextTypeFrame->setPosition(ccp(size.width - 60, size.height - 250));
		this->addChild(nextTypeFrame);
		break;
	case 3:
		nextTypeFrame = CCSprite::create("P.png");
		CC_BREAK_IF(! nextTypeFrame);
		/*nextTypeFrame->setAnchorPoint(ccp(0, 0));*/
		/*nextTypeFrame->setPosition(ccp(size.width - 60, size.height - 180));*/
		nextTypeFrame->setPosition(ccp(size.width - 60, size.height - 250));
		this->addChild(nextTypeFrame);
		break;
	case 4:
		nextTypeFrame = CCSprite::create("S.png");
		CC_BREAK_IF(! nextTypeFrame);
		/*nextTypeFrame->setAnchorPoint(ccp(0, 0));*/
		/*nextTypeFrame->setPosition(ccp(size.width - 60, size.height - 180));*/
		nextTypeFrame->setPosition(ccp(size.width - 60, size.height - 250));
		this->addChild(nextTypeFrame);
		break;
	case 5:
		nextTypeFrame = CCSprite::create("T.png");
		CC_BREAK_IF(! nextTypeFrame);
		/*nextTypeFrame->setAnchorPoint(ccp(0, 0));*/
		/*nextTypeFrame->setPosition(ccp(size.width - 60, size.height - 180));*/
		nextTypeFrame->setPosition(ccp(size.width - 60, size.height - 250));
		this->addChild(nextTypeFrame);
		break;
	case 6:
		nextTypeFrame = CCSprite::create("Z.png");
		CC_BREAK_IF(! nextTypeFrame);
		/*nextTypeFrame->setAnchorPoint(ccp(0, 0));*/
		/*nextTypeFrame->setPosition(ccp(size.width - 60, size.height - 180));*/
		nextTypeFrame->setPosition(ccp(size.width - 60, size.height - 250));
		this->addChild(nextTypeFrame);
		break;
	}
	nextTypeFrame->retain();
}

void TetrisGameLayer::randomTetrisType()
{
	 cc_timeval psv;
	 CCTime::gettimeofdayCocos2d(&psv, NULL);
	 unsigned long int seed = psv.tv_sec * 1000 + psv.tv_usec / 1000;
	 srand(seed);
	 int random_type = CCRANDOM_0_1() * 100; 
	/* int random_state = (CCRANDOM_0_1()*100);*/
	 switch(random_type % 7)
	 {
	 case 0:
		 nextHandleType = new I_TetrisBlockType();
		 nextType = 0;
		/* currentHandleType->t_typeIndex = 1/ *random_state % 4* /;*/
		 /*currentHandleType->init();*/
		 break;
	 case 1:
		 nextHandleType = new L_TetrisBlockType();
		 nextType = 1;
		/* currentHandleType->t_typeIndex = 1/ *random_state % 2* /;*/
		 /*currentHandleType->init();*/
		 break;
	 case 2:
		 nextHandleType = new O_TetrisBlockType();
		 nextType = 2;
		 /*currentHandleType->init();*/
		 break;
	 case 3:
		 nextHandleType = new P_TetrisBlockType();
		 nextType = 3;
		 /*currentHandleType->init();*/
		 break;
	 case 4:
		 nextHandleType = new S_TetrisBlockType();
		 nextType = 4;
		 /*currentHandleType->init();*/
		 break;
	 case 5:
		 nextHandleType = new T_TetrisBlockType();
		 nextType = 5;
		 /*currentHandleType->init();*/
		 break;
	 case 6:
		 nextHandleType = new Z_TetrisBlockType();
		 nextType = 6;
		 /*currentHandleType->init();*/
		 break;
	 }
}

void TetrisGameLayer::rotateButtonPressed(CCObject *pSender)
{
	if (isRunning)
	{
		currentHandleType->T_playerHandle(ROTATE);
	}
}

void TetrisGameLayer::down(float dt)
{
	if (isClick)
		currentHandleType->T_playerHandle(DROPDOWN);
}
void TetrisGameLayer::downButtonPressed(CCObject *pSender)
{
	if (isRunning)
	{
		isClick = true;
	}
}

void TetrisGameLayer::leftButtonPressed(CCObject *pSender)
{
	if (isRunning)
	{
		currentHandleType->T_playerHandle(LEFTMOVE);
	}
}

void TetrisGameLayer::rightButtonPressed(CCObject *pSender)
{
	if (isRunning)
	{
		currentHandleType->T_playerHandle(RIGHTMOVE);
	}
}

void TetrisGameLayer::pauseButtonPressed(CCObject *pSender)
{
	CCMenuItemImage *button = (CCMenuItemImage*)pSender;
	if (isRunning)
	{
		CCDirector::sharedDirector()->pause();
		isRunning = false;
		button->setNormalSpriteFrame(pauseAfterFrame);
		button->setSelectedSpriteFrame(pauseAfterFrame);
	}
	else
	{
		CCDirector::sharedDirector()->resume();
		isRunning = true;
		button->setNormalSpriteFrame(pausePreFrame);
		button->setSelectedSpriteFrame(pausePreFrame);
	}
}

bool TetrisGameLayer::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
	if (isRunning)
	{
		if (! currentHandleType)
		{
			return false;
		}
		
		CCPoint location = this->convertTouchToNodeSpace(pTouch);
		CCSize sz = CCDirector::sharedDirector()->getWinSize();
		if (location.x < blockParent->getPositionX() || location.x > blockParent->getPositionX() + _colum * _width ||
			location.y < blockParent->getPositionY() || location.y > blockParent->getPositionY() + _row * _height)
		{
			return false;
		}
		currentHandleType->T_playerHandle(ROTATE);
		return true;
	}
	return false;
}

void TetrisGameLayer::ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent)
{

}

void TetrisGameLayer::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{

}

void TetrisGameLayer::ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent)
{

}

TetrisGameLayer::~TetrisGameLayer()
{
	blockParent->removeAllChildrenWithCleanup(true);

	if (blockParent)
	{
		blockParent->autorelease();
	}
	

	pausePreFrame->release();
	pauseAfterFrame->release();
}

void TetrisGameLayer::blockParentAddChild(CCNode * node)
{
	if (! blockParent)
	{
		CCLog("blockParent is NULL");
		return;
	}
	blockParent->addChild(node);
}

void TetrisGameLayer::blockParentRemoveChildWithRow(const int row)
{
	CCArray *_childArr = blockParent->getChildren();
	unsigned int count = _childArr->count();
	int _index = 0;
	for (unsigned int i = 0; i < count; ++i)
	{
		TetrisBlock *_block = (TetrisBlock*)_childArr->objectAtIndex(i - _index);
		if (_block->b_getBlockRow() == row)
		{
			_block->b_disapper();
			++_index;
		}
		else 
			if (_block->b_getBlockRow() > row)
			{
				_block->b_DropDown();
			}
	}	
}

void TetrisGameLayer::blockParentChildDropDown()
{
	unsigned int count = blockParent->getChildrenCount();

	TetrisDataHandle::getSharedTetrisDataHandle()->h_clearTetrisStateArray();

	for (unsigned int i = 0; i < count; ++i)
	{
		TetrisBlock *_block = (TetrisBlock*)blockParent->getChildren()->objectAtIndex(i);
		_block->b_UpdateTetrisStateArray(1);
	}
}

void TetrisGameLayer::gameOverDone(CCObject* pSender)
{
	CCDirector::sharedDirector()->replaceScene(GameOverLayer::scene());
}

void TetrisGameLayer::backToMainMenu(CCObject* pSender)
{
	CCDirector::sharedDirector()->replaceScene(HelloWorld::scene());
}
