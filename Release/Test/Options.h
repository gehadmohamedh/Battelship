#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

using namespace std;

class Options
{
public:
	bool  sound = false;
	bool soundFX = false;
	string themes = "Ships_Blueprint/";
	bool InvertGrid = false;
	sf::Color BackGroundColor = (sf::Color::Color(29, 42, 104));
	Options(){}
};