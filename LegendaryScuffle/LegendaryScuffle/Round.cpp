#include "Round.h"

Round::Round()
{
}

void Round::generateRound()
{
    this->enemyVector.push_back(*this->satyr1);
    this->enemyVector.push_back(*this->satyr2);
    this->enemyVector.push_back(*this->satyr3);
}

Round::~Round()
{
    delete this->satyr1;
    delete this->satyr2;
    delete this->satyr3;
    this->enemyVector.clear();
}
