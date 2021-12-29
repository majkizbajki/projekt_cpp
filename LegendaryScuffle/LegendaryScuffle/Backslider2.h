#pragma once
#include <SFML/Graphics.hpp>
#include "Ally.h"
#include <fstream>

class Backslider2 : public Ally
{
public:
	Backslider2();
	~Backslider2();
private:
	std::fstream file;
};

