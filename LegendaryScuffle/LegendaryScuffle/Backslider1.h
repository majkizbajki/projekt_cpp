#pragma once
#include <SFML/Graphics.hpp>
#include "Ally.h"
#include <fstream>

class Backslider1 : public Ally
{
public:
	Backslider1();
	~Backslider1();
private:
	std::fstream file;
};

