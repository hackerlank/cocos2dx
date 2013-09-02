#ifndef _TETRIS_DATA_HANDLE__
#define _TETRIS_DATA_HANDLE__

#include <iostream>

#include "cocos2d.h"

using namespace cocos2d;

class TetrisDataHandle
{
public:

	static TetrisDataHandle *getSharedTetrisDataHandle();

	TetrisDataHandle();

	~TetrisDataHandle();

	inline void initWith_C_R_S(int c, int r, CCSize size)
	{
		t_colum = c;
		t_row = r;
		t_counts = t_colum * t_row;
		t_contentSize = size;
		disappearRowCount = 0;
		h_initTetrisState_PositionArray();
	}

	void h_initTetrisState_PositionArray();

	//Getters
	inline unsigned int h_getTetrisColum()
	{
		return t_colum;
	}

	inline unsigned int h_getTetrisRow()
	{
		return t_row;
	}

	inline unsigned int h_getTetrisTotalCounts()
	{
		return t_counts;
	}

	inline CCSize h_getTetrisContentSize()
	{
		return t_contentSize;
	}

	inline CCPoint h_getPostionAtIndex(int index)
	{
		if (positionArray)
		{
			return positionArray[index];
		}
		else
		{
			CCLog("Position array is NULL");
		}
		return CCPointZero;
	}

	inline int h_getTetrisStateArrayAtIndex(int index)
	{
		if (tetrisStateArray)
		{
			return tetrisStateArray[index];
		}
		else
		{
			CCLog("Tetris State Array is NULL");
		}
		return -1;
	}
	
	inline int h_getIndexAt(int colum, int row)
	{
		int index = row * t_colum + colum;

		if (index >= t_counts || index < 0)
		{
			CCLog("index out of range in Tetris State Array!");
			return -1;
		}
		return index;
	}

	//Update Tetris State Array
	inline void h_updateTetrisStateArray(int index, int value)
	{
		if (tetrisStateArray)
		{
			tetrisStateArray[index] = value;
		}
		else
			CCLog("Tetris State Array is NULL");
	}

	inline void h_clearTetrisStateArray()
	{
		memset(tetrisStateArray, 0, sizeof(int) * t_counts);
	}

	bool h_checkWillDisappearBlocks();

	int h_checkTetrisStateArrayRow_State(int index);

public:
	int t_colum;//总列数
	int t_row;//总行数
	int t_counts;//总格子数
	CCPoint *positionArray;//地图坐标
	int *tetrisStateArray;//地图状态
	CCSize t_contentSize;
	int disappearRowCount;
};

#endif