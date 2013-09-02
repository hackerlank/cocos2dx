#ifndef _TETRIS_GAME_LAYER_H_
#define _TETRIS_GAME_LAYER_H_

#include "cocos2d.h"
#include "HelloWorldScene.h"
#include "GameOverLayer.h"
/*#include "CodeConvert.h"*/
#include "I_TetrisBlockType.h"
#include "L_TetrisBlockType.h"
#include "P_TetrisBlockType.h"
#include "T_TetrisBlockType.h"
#include "Z_TetrisBlockType.h"
#include "S_TetrisBlockType.h"
#include "O_TetrisBlockType.h"

using namespace cocos2d;

//class TetrisBlockType;

class TetrisGameLayer:public CCLayerColor
{
public:
	static cocos2d::CCScene* scene();

	virtual bool init();

	/*static TetrisGameLayer* createWithStart();*/
	
// 	virtual void onEnter(void);
// 	
// 	virtual void onExit(void);
// 
// 	virtual void onEnterTransitionDidFinish(void);

/*	virtual void draw(void);*/

	/*void startGame();*/

	void gameOverDone(CCObject *pSender);

	void backToMainMenu(CCObject *pSender);

	//default implements are used to call script callback if exist

	void leftButtonPressed(CCObject *pSender);

	void rightButtonPressed(CCObject *pSender);

	void downButtonPressed(CCObject *pSender);

	void rotateButtonPressed(CCObject *pSender);

	void pauseButtonPressed(CCObject *pSender);


	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);

	virtual void ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent);

	virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);

	virtual void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent);

	CREATE_FUNC(TetrisGameLayer);

	~TetrisGameLayer();


	void blockParentAddChild(CCNode * node);

	void blockParentRemoveChildWithRow(const int row);

	void blockParentChildDropDown();

	static TetrisGameLayer * getSharedTetrisGameLayer();

	void update(float dt);

	void down(float dt);

	void randomTetrisType();

	void runChangeScore();

	void drawNextType();
public:
	int _colum, _row;

	float _width, _height;

	CCNode * blockParent;

	TetrisBlockType *currentHandleType;

	TetrisBlockType *nextHandleType;

	int nextType;

	CCSprite *nextTypeFrame;

	bool isRunning;

	bool isClick;

	int score;

	int level;

	CCSpriteFrame *pausePreFrame, *pauseAfterFrame;

	CCLabelTTF *lblScore;

	CCLabelTTF *lblLevel;
private:
	CCRect drawRect;
};


#endif