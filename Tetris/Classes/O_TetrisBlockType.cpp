#include "O_TetrisBlockType.h"
#include "TetrisDataHandle.h"
#include "TetrisGameLayer.h"
void O_TetrisBlockType::init()
{
	TetrisBlockType::init();

	t_count = 4;

	if (! t_childBlockArray)
	{
		CCLog("t_childBlockArray is NULL");
		return;
	}

	TetrisBlock *_block0 = TetrisBlock::create();
	_block0->b_initWithType(20);
	t_childBlockArray->addObject(_block0);
	TetrisGameLayer::getSharedTetrisGameLayer()->blockParentAddChild(_block0);

	TetrisBlock *_block1 = TetrisBlock::create();
	_block1->b_initWithType(21);
	t_childBlockArray->addObject(_block1);
	TetrisGameLayer::getSharedTetrisGameLayer()->blockParentAddChild(_block1);

	TetrisBlock *_block2 = TetrisBlock::create();
	_block2->b_initWithType(22);
	t_childBlockArray->addObject(_block2);
	TetrisGameLayer::getSharedTetrisGameLayer()->blockParentAddChild(_block2);

	TetrisBlock *_block3 = TetrisBlock::create();
	_block3->b_initWithType(23);
	t_childBlockArray->addObject(_block3);
	TetrisGameLayer::getSharedTetrisGameLayer()->blockParentAddChild(_block3);

	int _colum = TetrisDataHandle::getSharedTetrisDataHandle()->h_getTetrisColum() / 2 - 1;
	int _row = TetrisDataHandle::getSharedTetrisDataHandle()->h_getTetrisRow() - 1;

	if(t_typeIndex == 1)
	{

		TetrisBlock * _bk = (TetrisBlock*)t_childBlockArray->objectAtIndex(0);
		_bk->b_Update_C_R(_colum, _row/*_row - 1*/);

		_bk = (TetrisBlock*)t_childBlockArray->objectAtIndex(1);
		_bk->b_Update_C_R(_colum, _row + 1/*_row*/);

		_bk = (TetrisBlock*)t_childBlockArray->objectAtIndex(2);
		_bk->b_Update_C_R(_colum + 1,_row + 1/*_row*/);

		_bk = (TetrisBlock*)t_childBlockArray->objectAtIndex(3);
		_bk->b_Update_C_R(_colum + 1, _row/*_row - 1*/);
	}
	if(t_typeIndex == 2)
	{
		TetrisBlock * _bk = (TetrisBlock*)t_childBlockArray->objectAtIndex(0);
		_bk->b_leftRotate(90.0f);
		_bk->b_Update_C_R(_colum, _row);

		_bk = (TetrisBlock*)t_childBlockArray->objectAtIndex(1);
		_bk->b_leftRotate(90.0f);
		_bk->b_Update_C_R(_colum - 1, _row);

		_bk = (TetrisBlock*)t_childBlockArray->objectAtIndex(2);
		_bk->b_leftRotate(90.0f);
		_bk->b_Update_C_R(_colum - 1 , _row + 1);

		_bk = (TetrisBlock*)t_childBlockArray->objectAtIndex(3);
		_bk->b_leftRotate(90.0f);
		_bk->b_Update_C_R(_colum, _row + 1);
	}
	if(t_typeIndex == 3)
	{
		TetrisBlock * _bk = (TetrisBlock*)t_childBlockArray->objectAtIndex(0);
		_bk->b_leftRotate(180.0f);
		_bk->b_Update_C_R(_colum, _row);

		_bk = (TetrisBlock*)t_childBlockArray->objectAtIndex(1);
		_bk->b_leftRotate(180.0f);
		_bk->b_Update_C_R(_colum, _row - 1);

		_bk = (TetrisBlock*)t_childBlockArray->objectAtIndex(2);
		_bk->b_leftRotate(180.0f);
		_bk->b_Update_C_R(_colum - 1, _row - 1);

		_bk = (TetrisBlock*)t_childBlockArray->objectAtIndex(3);
		_bk->b_leftRotate(180.0f);
		_bk->b_Update_C_R(_colum - 1, _row);
	}
	if(t_typeIndex == 0)
	{
		TetrisBlock * _bk = (TetrisBlock*)t_childBlockArray->objectAtIndex(0);
		_bk->b_rightRotate(90.0f);
		_bk->b_Update_C_R(_colum, _row);

		_bk = (TetrisBlock*)t_childBlockArray->objectAtIndex(1);
		_bk->b_rightRotate(90.0f);
		_bk->b_Update_C_R(_colum + 1, _row);

		_bk = (TetrisBlock*)t_childBlockArray->objectAtIndex(2);
		_bk->b_rightRotate(90.0f);
		_bk->b_Update_C_R(_colum + 1, _row - 1);

		_bk = (TetrisBlock*)t_childBlockArray->objectAtIndex(3);
		_bk->b_rightRotate(90.0f);
		_bk->b_Update_C_R(_colum, _row - 1);
	}
	T_updateTetrisStateArray(1);
}

bool O_TetrisBlockType::T_checkDropDown()
{
	if (t_typeIndex == 1)//
	{
		TetrisBlock *_block0 = (TetrisBlock*)t_childBlockArray->objectAtIndex(0);
		TetrisBlock *_block3 = (TetrisBlock*)t_childBlockArray->objectAtIndex(3);
		if (_block0->b_checkWithDirection(0) && _block3->b_checkWithDirection(0))
		{
			return true;
		}
	}
	if (t_typeIndex == 2)//
	{
		TetrisBlock *_block0 = (TetrisBlock*)t_childBlockArray->objectAtIndex(0);
		TetrisBlock *_block1 = (TetrisBlock*)t_childBlockArray->objectAtIndex(1);
		if (_block0->b_checkWithDirection(0) && _block1->b_checkWithDirection(0))
		{
			return true;
		}
	}
	if (t_typeIndex == 3)//
	{
		TetrisBlock *_block1 = (TetrisBlock*)t_childBlockArray->objectAtIndex(1);
		TetrisBlock *_block2 = (TetrisBlock*)t_childBlockArray->objectAtIndex(2);
		if (_block1->b_checkWithDirection(0) && _block2->b_checkWithDirection(0))
		{
			return true;
		}
	}
	if (t_typeIndex == 0)//
	{
		TetrisBlock *_block2 = (TetrisBlock*)t_childBlockArray->objectAtIndex(2);
		TetrisBlock *_block3 = (TetrisBlock*)t_childBlockArray->objectAtIndex(3);
		if (_block2->b_checkWithDirection(0) && _block3->b_checkWithDirection(0))
		{
			return true;
		}
	}
	return false;
}

void O_TetrisBlockType::T_dropDown()
{
	for (unsigned int i = 0; i < t_count; ++i)
	{
		TetrisBlock * _block = (TetrisBlock*)t_childBlockArray->objectAtIndex(i);
		_block->b_DropDown();
	}
}

bool O_TetrisBlockType::T_checkLeftMove()
{
	if (t_typeIndex == 1)//
	{
		TetrisBlock *_block0 = (TetrisBlock*)t_childBlockArray->objectAtIndex(0);
		TetrisBlock *_block1 = (TetrisBlock*)t_childBlockArray->objectAtIndex(1);
		if (_block0->b_checkWithDirection(1) && _block1->b_checkWithDirection(1))
		{
			return true;
		}
	}
	if (t_typeIndex == 2)//
	{
		TetrisBlock *_block1 = (TetrisBlock*)t_childBlockArray->objectAtIndex(1);
		TetrisBlock *_block2 = (TetrisBlock*)t_childBlockArray->objectAtIndex(2);
		if (_block1->b_checkWithDirection(1) && _block2->b_checkWithDirection(1))
		{
			return true;
		}
	}
	if (t_typeIndex == 3)//
	{
		TetrisBlock *_block2 = (TetrisBlock*)t_childBlockArray->objectAtIndex(2);
		TetrisBlock *_block3 = (TetrisBlock*)t_childBlockArray->objectAtIndex(3);
		if (_block2->b_checkWithDirection(1) && _block3->b_checkWithDirection(1))
		{
			return true;
		}
	}
	if (t_typeIndex == 0)//
	{
		TetrisBlock *_block0 = (TetrisBlock*)t_childBlockArray->objectAtIndex(0);
		TetrisBlock *_block3 = (TetrisBlock*)t_childBlockArray->objectAtIndex(3);
		if (_block0->b_checkWithDirection(1) && _block3->b_checkWithDirection(1))
		{
			return true;
		}
	}
	return false;
}

void O_TetrisBlockType::T_leftMove()
{
	for (unsigned int i = 0; i < t_count; ++i)
	{
		TetrisBlock * _block = (TetrisBlock*)t_childBlockArray->objectAtIndex(i);
		_block->b_LeftMove();
	}
}

bool O_TetrisBlockType::T_checkRightMove()
{
	if (t_typeIndex == 1)//
	{
		TetrisBlock *_block2 = (TetrisBlock*)t_childBlockArray->objectAtIndex(2);
		TetrisBlock *_block3 = (TetrisBlock*)t_childBlockArray->objectAtIndex(3);
		if (_block2->b_checkWithDirection(2) && _block3->b_checkWithDirection(2))
		{
			return true;
		}
	}
	if (t_typeIndex == 2)//
	{
		TetrisBlock *_block0 = (TetrisBlock*)t_childBlockArray->objectAtIndex(0);
		TetrisBlock *_block3 = (TetrisBlock*)t_childBlockArray->objectAtIndex(3);
		if (_block0->b_checkWithDirection(2) && _block3->b_checkWithDirection(2))
		{
			return true;
		}
	}
	if (t_typeIndex == 3)//
	{
		TetrisBlock *_block0 = (TetrisBlock*)t_childBlockArray->objectAtIndex(0);
		TetrisBlock *_block1 = (TetrisBlock*)t_childBlockArray->objectAtIndex(1);
		if (_block0->b_checkWithDirection(2) && _block1->b_checkWithDirection(2))
		{
			return true;
		}
	}
	if (t_typeIndex == 0)//
	{
		TetrisBlock *_block1 = (TetrisBlock*)t_childBlockArray->objectAtIndex(1);
		TetrisBlock *_block2 = (TetrisBlock*)t_childBlockArray->objectAtIndex(2);
		if (_block1->b_checkWithDirection(2) && _block2->b_checkWithDirection(2))
		{
			return true;
		}
	}
	return false;
}

void O_TetrisBlockType::T_rightMove()
{
	for (unsigned int i = 0; i < t_count; ++i)
	{
		TetrisBlock *_block = (TetrisBlock*)t_childBlockArray->objectAtIndex(i);
		_block->b_RightMove();
	}
}

void O_TetrisBlockType::T_rotate()
{
	TetrisDataHandle *_sharedHandle = TetrisDataHandle::getSharedTetrisDataHandle();
	int _t_colum = _sharedHandle->h_getTetrisColum();

	TetrisBlock *_block1 = (TetrisBlock*)t_childBlockArray->objectAtIndex(0);

	int _firstBlockColum = _block1->b_getBlockColum();
	int _firstBlockRow = _block1->b_getBlockRow();

	if (t_typeIndex == 0)
	{
		TetrisBlock *_block1 = (TetrisBlock*)t_childBlockArray->objectAtIndex(0);
		_block1->b_leftRotate(90.0f);
		_block1->b_Update_C_R(_firstBlockColum, _firstBlockRow - 1);

		TetrisBlock *_block2 = (TetrisBlock*)t_childBlockArray->objectAtIndex(1);
		_block2->b_leftRotate(90.0f);
		_block2->b_Update_C_R(_firstBlockColum, _firstBlockRow);

		TetrisBlock *_block3 = (TetrisBlock*)t_childBlockArray->objectAtIndex(2);
		_block3->b_leftRotate(90.0f);
		_block3->b_Update_C_R(_firstBlockColum + 1, _firstBlockRow);

		TetrisBlock *_block4 = (TetrisBlock*)t_childBlockArray->objectAtIndex(3);
		_block4->b_leftRotate(90.0f);
		_block4->b_Update_C_R(_firstBlockColum + 1, _firstBlockRow - 1);

		t_typeIndex = 1;
		return;
	}
	if (t_typeIndex == 1)//
	{
		TetrisBlock *_block1 = (TetrisBlock*)t_childBlockArray->objectAtIndex(0);
		_block1->b_leftRotate(90.0f);
		_block1->b_Update_C_R(_firstBlockColum + 1, _firstBlockRow);

		TetrisBlock *_block2 = (TetrisBlock*)t_childBlockArray->objectAtIndex(1);
		_block2->b_leftRotate(90.0f);
		_block2->b_Update_C_R(_firstBlockColum, _firstBlockRow);

		TetrisBlock *_block3 = (TetrisBlock*)t_childBlockArray->objectAtIndex(2);
		_block3->b_leftRotate(90.0f);
		_block3->b_Update_C_R(_firstBlockColum, _firstBlockRow + 1);

		TetrisBlock *_block4 = (TetrisBlock*)t_childBlockArray->objectAtIndex(3);
		_block4->b_leftRotate(90.0f);
		_block4->b_Update_C_R(_firstBlockColum + 1, _firstBlockRow + 1);

		t_typeIndex = 2;
		return;
	}
	if (t_typeIndex == 2)//
	{
		TetrisBlock *_block1 = (TetrisBlock*)t_childBlockArray->objectAtIndex(0);
		_block1->b_leftRotate(90.0f);
		_block1->b_Update_C_R(_firstBlockColum, _firstBlockRow + 1);

		TetrisBlock *_block2 = (TetrisBlock*)t_childBlockArray->objectAtIndex(1);
		_block2->b_leftRotate(90.0f);
		_block2->b_Update_C_R(_firstBlockColum, _firstBlockRow);

		TetrisBlock *_block3 = (TetrisBlock*)t_childBlockArray->objectAtIndex(2);
		_block3->b_leftRotate(90.0f);
		_block3->b_Update_C_R(_firstBlockColum - 1, _firstBlockRow);

		TetrisBlock *_block4 = (TetrisBlock*)t_childBlockArray->objectAtIndex(3);
		_block4->b_leftRotate(90.0f);
		_block4->b_Update_C_R(_firstBlockColum - 1, _firstBlockRow + 1);

		t_typeIndex = 3;
		return;
	}
	if (t_typeIndex == 3)//竖向转为横向
	{
		TetrisBlock *_block1 = (TetrisBlock*)t_childBlockArray->objectAtIndex(0);
		_block1->b_leftRotate(90.0f);
		_block1->b_Update_C_R(_firstBlockColum - 1, _firstBlockRow);

		TetrisBlock *_block2 = (TetrisBlock*)t_childBlockArray->objectAtIndex(1);
		_block2->b_leftRotate(90.0f);
		_block2->b_Update_C_R(_firstBlockColum, _firstBlockRow);

		TetrisBlock *_block3 = (TetrisBlock*)t_childBlockArray->objectAtIndex(2);
		_block3->b_leftRotate(90.0f);
		_block3->b_Update_C_R(_firstBlockColum, _firstBlockRow - 1);

		TetrisBlock *_block4 = (TetrisBlock*)t_childBlockArray->objectAtIndex(3);
		_block4->b_leftRotate(90.0f);
		_block4->b_Update_C_R(_firstBlockColum - 1, _firstBlockRow - 1);

		t_typeIndex = 0;
		return;
	}
}

void O_TetrisBlockType::T_updateTetrisStateArray(int _value)
{
	for (unsigned int i = 0; i < t_count; ++i)
	{
		TetrisBlock *_block = (TetrisBlock*)t_childBlockArray->objectAtIndex(i);
		_block->b_UpdateTetrisStateArray(_value);
	}
}
