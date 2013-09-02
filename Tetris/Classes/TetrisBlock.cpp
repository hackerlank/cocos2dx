#include "TetrisBlock.h"
#include "TetrisDataHandle.h"
using namespace std;

bool TetrisBlock::init(void)
{
	if (!CCSprite::init())
	{
		return false;
	}
	this->setVisible(false);
	b_colum = 0;
	b_row = 0;
	return true;
}

void TetrisBlock::draw(void)
{
	CCSprite::draw();
}

void TetrisBlock::b_initWithType(int _type)
{
	CCSize cs = TetrisDataHandle::getSharedTetrisDataHandle()->h_getTetrisContentSize();
	cs = CCSizeMake(cs.width, cs.height);
	this->setContentSize(cs);
	string s;
	switch(_type)
	{
		case 0://I
			s = "0.png";
			break;
		case 1://I
			s = "1.png";
			break;
		case 2://I
			s = "2.png";
			break;
		case 3://I
			s = "3.png";
			break;
		case 10://L
			s = "10.png";
			break;
		case 11://L
			s = "11.png";
			break;
		case 12://L
			s = "12.png";
			break;
		case 13://L
			s = "13.png";
			break;
		case 20://O
			s = "20.png";
			break;
		case 21://O
			s = "21.png";
			break;
		case 22://O
			s = "22.png";
			break;
		case 23://O
			s = "23.png";
			break;
		case 30://P
			s = "30.png";
			break;
		case 31://P
			s = "31.png";
			break;
		case 32://P
			s = "32.png";
			break;
		case 33://P
			s = "33.png";
			break;
		case 40://S
			s = "40.png";
			break;
		case 41://S
			s = "41.png";
			break;
		case 42://S
			s = "42.png";
			break;
		case 43://S
			s = "43.png";
			break;
		case 50://T
			s = "50.png";
			break;
		case 51://T
			s = "51.png";
			break;
		case 52://T
			s = "52.png";
			break;
		case 53://T
			s = "53.png";
			break;
		case 60://Z
			s = "60.png";
			break;
		case 61://Z
			s = "61.png";
			break;
		case 62://Z
			s = "62.png";
			break;
		case 63://Z
			s = "63.png";
			break;
		default:
			s = "blue.png";
			break;
	}
	//ÎÆÀí
	CCTexture2D *texture = CCTextureCache::sharedTextureCache()->addImage(s.c_str());
	//±ß¿ò
	CCSpriteFrame *frame = CCSpriteFrame::createWithTexture(texture, CCRectMake(0, 0, cs.width, cs.height));
	this->setDisplayFrame(frame);
}

void TetrisBlock::b_LeftMove()
{
	//this->b_UpdateTetrisStateArray(0);
	--b_colum;
	//this->b_UpdateTetrisStateArray(1);
}

void TetrisBlock::b_RightMove()
{
	//this->b_UpdateTetrisStateArray(0);
	++b_colum;
	//this->b_UpdateTetrisStateArray(1);
}

void TetrisBlock::b_DropDown()
{
	--b_row;
}

bool TetrisBlock::b_checkWithDirection(int _direction)
{
	int _tag = 0;
	int _index = 0;

	TetrisDataHandle * _tetrisDataHandle = TetrisDataHandle::getSharedTetrisDataHandle();
	int t_colum = _tetrisDataHandle->t_colum;

	switch(_direction)
	{
		//check with down
		case 0: 
			{
				if (b_row - 1 < 0)
				{
					return false;
				}
				_index = _tetrisDataHandle->h_getIndexAt(b_colum, b_row - 1);//?
				_tag = _tetrisDataHandle->h_getTetrisStateArrayAtIndex(_index);
			}
			break;
		//check with left
		case 1:
			{
				if (b_colum - 1< 0)
				{
					return false;
				}
				CCLog("colum %d, row %d", b_colum, b_row);
				_index = _tetrisDataHandle->h_getIndexAt(b_colum - 1, b_row);
				_tag = _tetrisDataHandle->h_getTetrisStateArrayAtIndex(_index);
			}
			break;
		//check with right
		case 2:
			{
				if (b_colum + 1 > t_colum - 1)
				{
					return false;
				}
				_index = _tetrisDataHandle->h_getIndexAt(b_colum + 1, b_row);
				_tag = _tetrisDataHandle->h_getTetrisStateArrayAtIndex(_index);
			}
			break;
		
		default:
			break;
	}
	return !(bool)_tag;
}

void TetrisBlock::b_UpdateTetrisStateArray(int _value)
{
	TetrisDataHandle * _tetrisDataHandle = TetrisDataHandle::getSharedTetrisDataHandle();

	int _index = _tetrisDataHandle->h_getIndexAt(b_colum, b_row);

	if (_index == -1)
	{//ÉèÎªÒþ²Ø
		this->setVisible(false);
		return;
	}

	_tetrisDataHandle->h_updateTetrisStateArray(_index, _value);//ÖØÖÃtetris state array×´Ì¬

	if (_value)
	{
		CCPoint _pos = _tetrisDataHandle->h_getPostionAtIndex(_index);

		this->setPosition(_pos);//ÖØÖÃÎ»ÖÃ

		if (! this->isVisible())
		{
			this->setVisible(true);
		}
	}
}

void TetrisBlock::b_Update_C_R(int _colum, int _row)
{
	//this->b_UpdateTetrisStateArray(0);
	b_colum = _colum;
	b_row = _row;
	//this->b_UpdateTetrisStateArray(1);
}

void TetrisBlock::b_disapper()
{
	b_UpdateTetrisStateArray(0);
	this->removeFromParentAndCleanup(true);
}

void TetrisBlock::b_leftRotate(float angle)
{
	CCActionInterval *rotateby = CCRotateBy::create(0.1, -angle);
	this->runAction(CCSequence::create(rotateby, NULL));
}

void TetrisBlock::b_rightRotate(float angle)
{
	CCActionInterval *rotateby = CCRotateBy::create(0.1, angle);
	this->runAction(CCSequence::create(rotateby, NULL));
}