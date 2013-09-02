#include "TetrisDataHandle.h"

#include "TetrisGameLayer.h"

static TetrisDataHandle * s_sharedTetrisDataHandle = NULL;

TetrisDataHandle * TetrisDataHandle::getSharedTetrisDataHandle()
{
	if (s_sharedTetrisDataHandle == NULL)
	{
		s_sharedTetrisDataHandle = new TetrisDataHandle();
	}
	return s_sharedTetrisDataHandle;
}

TetrisDataHandle::TetrisDataHandle()
{
	if (s_sharedTetrisDataHandle == NULL)
	{
		s_sharedTetrisDataHandle = this;
	}
}

TetrisDataHandle::~TetrisDataHandle()
{
	s_sharedTetrisDataHandle = NULL;
}

void TetrisDataHandle::h_initTetrisState_PositionArray()
{
	tetrisStateArray = new int[t_counts]();
	positionArray = new CCPoint[t_counts]();

	if (tetrisStateArray == NULL || positionArray == NULL)
	{
		CCLOG("Tetris State Array or Position Array Initialize failed");
		return;
	}

	float h_width = t_contentSize.width / 2;
	float h_height = t_contentSize.height / 2;

	for (int r = 0; r < t_row; ++r)
	{
		for (int c = 0; c < t_colum; ++c)
		{
			int index = (r * t_colum) +  c;
			tetrisStateArray[index] = 0;
			positionArray[index] = CCPointMake(t_contentSize.width * c + h_width, 
				t_contentSize.height * r + h_height);
		}
	}
}

bool TetrisDataHandle::h_checkWillDisappearBlocks()
{
	bool _tag = false;
	int _index = 0;
	for (int r = 0; r < t_row; ++r)
	{
		int _in = h_getIndexAt(0, r);
		int _flag = h_checkTetrisStateArrayRow_State(_in);

		if(_flag == 1)
		{
			TetrisGameLayer::getSharedTetrisGameLayer()->blockParentRemoveChildWithRow(r - _index);
			++_index;
			_tag = true;
			continue;
		}
		if (_flag == 0)
		{
			disappearRowCount = _index;
			return _tag;
		}
		if (_flag == -1)
		{
			continue;
		}
	}
	disappearRowCount = _index;
	return _tag;
}

int TetrisDataHandle::h_checkTetrisStateArrayRow_State(int index)
{
	int flag = h_getTetrisStateArrayAtIndex(index);
	for (int c = 1; c < t_colum; ++c)
	{
		int _nextState = h_getTetrisStateArrayAtIndex(index + c);
		if (flag == _nextState)
		{
			continue;
		}
		else
		{
			return -1;
		}
	}
	return flag;
}
