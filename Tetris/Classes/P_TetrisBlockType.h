#ifndef _P_TETRIS_BLOCK_TYPE_H_
#define _P_TETRIS_BLOCK_TYPE_H_

#include "TetrisBlockType.h"

class P_TetrisBlockType : public TetrisBlockType
{
public:
	virtual void init();

	virtual bool T_checkLeftMove();

	virtual void T_leftMove();

	virtual bool T_checkRightMove();

	virtual void T_rightMove();

	virtual bool T_checkDropDown();

	virtual void T_dropDown();

	virtual void T_rotate();

	virtual void T_updateTetrisStateArray(int _value);
};

#endif