#ifndef _TETRIS_BLOCK_TYPE_H_
#define _TETRIS_BLOCK_TYPE_H_

#include "TetrisBlock.h"
#include "Config.h"

using namespace cocos2d;

class TetrisBlockType
{
public:
	TetrisBlockType();

	~TetrisBlockType();

	virtual void init();

	virtual bool T_playerHandle(PlayerHandle _handleType);

	virtual bool T_checkLeftMove();

	virtual void T_leftMove();

	virtual bool T_checkRightMove();

	virtual void T_rightMove();

	virtual bool T_checkDropDown();

	virtual void T_dropDown();

	//rotate
	virtual void T_rotate();

	virtual void T_updateTetrisStateArray(int _value);

public:
	unsigned int t_count;

	int t_typeIndex;

	CCArray * t_childBlockArray;//存放当前形状的block数组
};

#endif