#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

using namespace std;

struct Options
{
	bool sound = true;
	bool soundFX = true;
	string theme = "Ships_Blueprint/";
	bool InvertGrid = false;
	string backgroundImage = theme + "background.jpg";
	sf::Color textColor = sf::Color::White;
	string musicFile = "Sounds/blueprint.wav";
};