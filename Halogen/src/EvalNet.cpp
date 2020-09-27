#include "EvalNet.h"

int pieceValueVector[N_PIECE_TYPES] = {100, 305, 333, 563, 950, 0}; //Values from AlphaZero (https://en.wikipedia.org/wiki/Chess_piece_relative_value)

bool BlackBlockade(uint64_t wPawns, uint64_t bPawns);
bool WhiteBlockade(uint64_t wPawns, uint64_t bPawns);

int EvaluatePositionNet(Position& position)
{
    return std::min(4000, std::max(-4000, static_cast<int>(std::round(position.GetEvaluation()))));
}

int PieceValues(unsigned int Piece)
{
    assert(Piece < N_PIECES);
    assert(Piece != WHITE_KING);
    assert(Piece != BLACK_KING);

    return pieceValueVector[Piece % N_PIECE_TYPES];
}

bool DeadPosition(const Position& position)
{
    if ((position.GetPieceBB(WHITE_PAWN)) != 0) return false;
    if ((position.GetPieceBB(WHITE_ROOK)) != 0) return false;
    if ((position.GetPieceBB(WHITE_QUEEN)) != 0) return false;

    if ((position.GetPieceBB(BLACK_PAWN)) != 0) return false;
    if ((position.GetPieceBB(BLACK_ROOK)) != 0) return false;
    if ((position.GetPieceBB(BLACK_QUEEN)) != 0) return false;

    /*
    From the Chess Programming Wiki:
        According to the rules of a dead position, Article 5.2 b, when there is no possibility of checkmate for either side with any series of legal moves, the position is an immediate draw if
        - both sides have a bare king													1.
        - one side has a king and a minor piece against a bare king						2.
        - both sides have a king and a bishop, the bishops being the same color			Not covered
    */

    //We know the board must contain just knights, bishops and kings
    int WhiteBishops = GetBitCount(position.GetPieceBB(WHITE_BISHOP));
    int BlackBishops = GetBitCount(position.GetPieceBB(BLACK_BISHOP));
    int WhiteKnights = GetBitCount(position.GetPieceBB(WHITE_KNIGHT));
    int BlackKnights = GetBitCount(position.GetPieceBB(BLACK_KNIGHT));
    int WhiteMinor = WhiteBishops + WhiteKnights;
    int BlackMinor = BlackBishops + BlackKnights;

    if (WhiteMinor == 0 && BlackMinor == 0) return true;	//1
    if (WhiteMinor == 1 && BlackMinor == 0) return true;	//2
    if (WhiteMinor == 0 && BlackMinor == 1) return true;	//2

    return false;
}




