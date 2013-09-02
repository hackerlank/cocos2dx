#ifndef _TETRISBLOCK_H_
#define _TETRISBLOCK_H_

#include "cocos2d.h"

using namespace cocos2d;

class TetrisBlock:public CCSprite
{
public:
	virtual bool init(void);
	virtual void draw(void);
	CREATE_FUNC(TetrisBlock);

	void b_initWithType(int _type);

	void b_LeftMove();
	void b_RightMove();
	void b_DropDown();

	void b_Update_C_R(int _colum, int _row);
	void b_UpdateTetrisStateArray(int _value);

	inline int b_getBlockColum()
	{
		return b_colum;
	}
	inline int b_getBlockRow()
	{
		return b_row;
	}

	bool b_checkWithDirection(int _direction);//¼ì²é³ö½ç
	void b_disapper();
	void b_leftRotate(float angle);
	void b_rightRotate(float angle);
private:
	int b_colum;
	int b_row;
};

#endif