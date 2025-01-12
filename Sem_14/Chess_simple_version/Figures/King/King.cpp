#include "King.h"
#include <cmath>

King::King(bool isWhite) : Figure(isWhite, FigureType::KingFigure)
{}

bool King::canBeMoved(size_t currentX, size_t currentY, size_t destX, size_t destY) const
{
	return abs((int)currentX - (int)destX) <= 1 && abs((int)currentY - (int)destY) <= 1;
}
void King::print() const
{
	getIsWhite() ? std::cout << '%' : std::cout << '$';
}