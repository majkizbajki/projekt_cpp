#include "Player.h"
#include <fstream>
#include <string>

Player::Player()
{
	std::fstream file;
	file.open("saves/player.txt",std::ios::in | std::ios::out);
	if (file.good() == true)
	{
		std::string text;
		while (std::getline(file,text))
		{
			std::string money = text.substr(text.find("money") + 6, text.size()-1);
			this->money = std::stoi(money);
		}

		file.close();
	}
	else
	{
		this->money = 0;
		file.close();
	}
}
