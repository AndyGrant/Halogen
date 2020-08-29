#pragma once

#include "BoardParamiters.h"
#include "BitBoard.h"
#include "Zobrist.h"
#include "Network.h"
#include <sstream>

#ifdef _MSC_VER 
#define NOMINMAX
#endif 

#include <Windows.h>

/*
This class holds all the data required to define a chess board position, as well as some functions to manipulate and extract this data in convienient ways.
*/

class Position : public BoardParamiters, public BitBoard
{
public:
	Position();
	Position(std::vector<std::string> moves);																								//Initialise from a vector of moves from the starting position
	Position(std::string board, std::string turn, std::string castle, std::string ep, std::string fiftyMove, std::string turnCount);		//split fen
	Position(std::string fen);																												//whole fen
	~Position();

	void ApplyMove(Move move);
	void ApplyMove(std::string strmove);
	void RevertMove();

	void ApplyNullMove();
	void RevertNullMove();

	void Print() const;

	void StartingPosition();
	bool InitialiseFromFen(std::vector<std::string> fen);
	bool InitialiseFromFen(std::string board, std::string turn, std::string castle, std::string ep, std::string fiftyMove, std::string turnCount); //Returns true after sucsessful execution, false otherwise
	bool InitialiseFromFen(std::string fen);
	bool InitialiseFromMoves(std::vector<std::string> moves);

	uint64_t GetZobristKey() const;
	uint64_t GetNodeCount() const { return NodeCount; }

	void ResetNodeCount() { NodeCount = 0; }
	void IncreaseNodeCount() { NodeCount++; }
	void Reset();

	size_t GetPreviousKeysSize() const { return PreviousKeys.size(); }
	uint64_t GetPreviousKey(size_t index);

	/*Seriously, don't use these functions outside of static exchange evaluation*/
	void ApplySEECapture(Move move);	//does ApplyMove functionality but much quicker. Only for use within see() and seeAttack()
	void RevertSEECapture();			//does RevertMove functionality but much quicker. Only for use within see() and seeAttack()

	Network net;

	double GetEvaluation();

private:
	uint64_t NodeCount;
	uint64_t key;
	std::vector<uint64_t> PreviousKeys;
	std::vector<std::vector<std::pair<size_t, double>>> PreviousDeltas;

	uint64_t GenerateZobristKey() const;
	uint64_t IncrementZobristKey(Move move);	

	std::vector<double> GetInputLayer();
	std::vector<std::pair<size_t, double>> CalculateMoveDelta(Move move);				//A vector which calculates the CHANGE in each input paramiter

	size_t modifier(size_t index);						//no inputs for pawns on front or back rank for neural net: we need to modify zobrist-like indexes
};

