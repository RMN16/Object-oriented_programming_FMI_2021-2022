#include "Pawn.h"
#include <cmath>

Pawn::Pawn(bool isWhite) : Figure(isWhite, FigureType::PawnFigure), isFirstMove(true)
{}

bool Pawn::canBeMoved(size_t currentX, size_t currentY, size_t destX, size_t destY) const
{
	if (getIsWhite())
		return currentY - 1 == destY && abs((int)currentX - (int)destX) <= 1;
	else
		return currentY + 1 == destY && abs((int)currentX - (int)destX) <= 1;
}
void Pawn::print() const
{
	getIsWhite() ? std::cout << 'P' : std::cout << 'p';
}