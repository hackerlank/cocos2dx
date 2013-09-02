#include "TetrisBlockType.h"

TetrisBlockType::TetrisBlockType()
{
	this->init();
}

TetrisBlockType::~TetrisBlockType()
{
	if (t_childBlockArray)
	{
		t_childBlockArray->removeAllObjects();
		t_childBlockArray->autorelease();
	}
}

void TetrisBlockType::init()
{
	int random_state = (CCRANDOM_0_1()*100);
	t_count = 4;
	t_typeIndex = random_state % 4;
	t_childBlockArray = new CCArray();
	t_childBlockArray->init();
}

bool TetrisBlockType::T_checkLeftMove()
{
	CCLog("TetrisBlockType check LeftMove!");
	return false;
}

bool TetrisBlockType::T_checkRightMove()
{
	CCLog("TetrisBlockType check RightMove!");
	return false;
}

bool TetrisBlockType::T_checkDropDown()
{
	CCLog("TetrisBlockType check DropDown!");
	return false;
}

void TetrisBlockType::T_leftMove()
{
}

void TetrisBlockType::T_rightMove()
{
}

void TetrisBlockType::T_dropDown()
{
}

void TetrisBlockType::T_rotate()
{
	CCLog("TetrisBlockType check rotate!");
}

void TetrisBlockType::T_updateTetrisStateArray(int _value)
{
}

bool TetrisBlockType::T_playerHandle(PlayerHandle _handleType)
{
	bool _flag = false;
	switch(_handleType)
	{
	case DROPDOWN:
		_flag = T_checkDropDown();
		if (_flag)
		{
			T_updateTetrisStateArray(0);
			T_dropDown();
			T_updateTetrisStateArray(1);
		}
		break;
	case LEFTMOVE:
		_flag = T_checkLeftMove();
		if (_flag)
		{
			CCLog("flag is true left\n");
			T_updateTetrisStateArray(0);
			T_leftMove();
			T_updateTetrisStateArray(1);
		}
		break;
	case RIGHTMOVE:
		_flag =T_checkRightMove();
		if (_flag)
		{
			T_updateTetrisStateArray(0);
			T_rightMove();
			T_updateTetrisStateArray(1);
		}
		break;
	case ROTATE:
			T_updateTetrisStateArray(0);
			T_rotate();
			T_updateTetrisStateArray(1);
		break;
	default:
		break;
	}
//	TetrisDataHandle::getSharedTetrisDataHandle()->h_ShowDebug();
	return _flag;
}