#pragma once
#include "Move.h"
#include "BitBoardDefine.h"

class TTEntry
{
public:
	TTEntry();
	TTEntry(Move best, uint64_t ZobristKey, int Score, int Depth, unsigned int Cutoff);
	~TTEntry();

	uint64_t GetKey() { return key; }
	int GetScore() { return score; }		
	char GetDepth() { return depth; }
	bool IsAncient() { return ancient; }
	char GetCutoff() { return cutoff; }
	Move GetMove() { return bestMove; }

	void SetAncient(bool isAncient) { ancient = isAncient; }

private:
	//21 bytes 
	uint64_t key;			//8 bytes
	int score;				//4 bytes
	int depth;				//4 bytes
	Move bestMove;			//3 bytes  
	bool ancient;			//1 byte 
	char cutoff;			//1 byte   
};
