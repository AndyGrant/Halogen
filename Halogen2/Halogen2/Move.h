#pragma once
#include <iostream>
#include <assert.h>

enum MoveFlag
{
	QUIET,							//0		0 0 0 0
	PAWN_DOUBLE_MOVE,				//1		0 0 0 1
	KING_CASTLE,					//2		0 0 1 0
	QUEEN_CASTLE,					//3		0 0 1 1
	CAPTURE,						//4		0 1 0 0
	EN_PASSANT,						//5		0 1 0 1
	KNIGHT_PROMOTION = 8,			//8		1 0 0 0
	BISHOP_PROMOTION,				//9		1 0 0 1
	ROOK_PROMOTION,					//10	1 0 1 0
	QUEEN_PROMOTION,				//11	1 0 1 1
	KNIGHT_PROMOTION_CAPTURE,		//12	1 1 0 0
	BISHOP_PROMOTION_CAPTURE,		//13	1 1 0 1	
	ROOK_PROMOTION_CAPTURE,			//14	1 1 1 0
	QUEEN_PROMOTION_CAPTURE			//15	1 1 1 1
};

class Move
{
public:
	Move();
	Move(unsigned int from, unsigned int to, unsigned int flag);
	~Move();

	unsigned int GetFrom() const;
	unsigned int GetTo() const;
	unsigned int GetFlag() const;

	bool IsPromotion() const;
	bool IsCapture() const;

	void Print() const;

	bool operator==(const Move& rhs) const;
	
	int SEE = 0;

private:

	void SetFrom(unsigned int from);
	void SetTo(unsigned int to);
	void SetFlag(unsigned int flag);

	char m_from;
	char m_to;
	char m_flag;
};


