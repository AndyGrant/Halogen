#pragma once
#include "BitBoardDefine.h"
#include "Move.h"
#include <vector>

class BoardParamiters;

extern std::vector<BoardParamiters> PreviousParamiters;

class BoardParamiters
{
public:
	BoardParamiters();
	~BoardParamiters();

	unsigned int GetTurnCount() const { return m_TurnCount; }
	bool GetTurn() const { return m_CurrentTurn; }
	bool HasCastledWhite() const { return m_HasCastledWhite; }
	bool HasCastledBlack() const { return m_HasCastledBlack; }
	bool CanCastleWhiteKingside() const { return m_WhiteKingCastle; }
	bool CanCastleWhiteQueenside() const { return m_WhiteQueenCastle; }
	bool CanCastleBlackKingside() const { return m_BlackKingCastle; }
	bool CanCastleBlackQueenside() const { return m_BlackQueenCastle; }
	unsigned int GetEnPassant() const { return m_EnPassant; }
	unsigned int GetCaptureSquare() const { return m_CaptureSquare; }

protected:
	bool InitialiseParamitersFromFen(std::vector<std::string> fen);
	void SaveParamiters();
	void RestorePreviousParamiters();
	void UpdateCastleRights(Move move);
	void SetEnPassant(unsigned int var) { m_EnPassant = var; }
	void WhiteCastled();
	void BlackCastled();
	void NextTurn();
	void SetCaptureSquare(unsigned int sq) { m_CaptureSquare = sq; }

	void Init();

private:
	bool m_CurrentTurn;
	bool m_WhiteKingCastle;
	bool m_WhiteQueenCastle;
	bool m_BlackKingCastle;
	bool m_BlackQueenCastle;

	unsigned int m_EnPassant;
	unsigned int m_FiftyMoveCount;
	unsigned int m_TurnCount;

	bool m_HasCastledWhite;
	bool m_HasCastledBlack;

	unsigned int m_CaptureSquare;
};
