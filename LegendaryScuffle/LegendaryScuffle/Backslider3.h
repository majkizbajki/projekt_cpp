#pragma once
#include <SFML/Graphics.hpp>
#include "Ally.h"
#include <fstream>

class Backslider3 : public Ally
{
public:
	Backslider3();
	~Backslider3();
private:
	std::fstream file;
};
