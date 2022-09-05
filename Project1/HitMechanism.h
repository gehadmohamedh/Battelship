#pragma once
#include "Ship.h"
#include <vector>
#include"SFML/Graphics.hpp"
using namespace std;



void CheckShips(vector<Ship> &Ships, int HitGrid[10][10], int& remainingShips) {
	/// a function that checks if a ship is completely destroyed then updates the remaining ships.
	for (int i = 0; i < Ships.size(); i++) {
		if (Ships[i].destroyed)
			continue;
		int hits = 0;
		if (Ships[i].orientation == 'H') {
			int y = Ships[i].y;
			for (int j = Ships[i].x; j < Ships[i].x + Ships[i].length; j++) {
				if (HitGrid[j][y] == 1)
					hits++;
			}
		}
		else {
			int x = Ships[i].x;
			for (int j = Ships[i].y; j < Ships[i].y + Ships[i].length; j++) {
				if (HitGrid[x][j] == 1)
					hits++;
			}
		}
		if (hits == Ships[i].length) {
			Ships[i].destroyed = true;
			remainingShips--;
		}
	}
}


void UpdateIndicators(vector<Ship> Ships , sf::RenderWindow &window , sf::Texture ShipIndicator[5], sf::Sprite ShipIndicatorSprite[5], string themeDirectory)
{
	/// a function to update the indicators (destroyed or not).
	for (int i = 0; i < Ships.size(); i++)
	{

		string FileName;
		if (Ships[i].destroyed)
		{
			FileName = themeDirectory + "Indicator_" + to_string(Ships[i].id) + "_Destroyed.png";
		}
		else
		{
			FileName = themeDirectory + "Indicator_" + to_string(Ships[i].id) + "_Undestroyed.png";
		}
		ShipIndicator[i].loadFromFile(FileName);
		ShipIndicatorSprite[i].setTexture(ShipIndicator[i]);
		ShipIndicatorSprite[i].setOrigin(ShipIndicator[i].getSize().x / 2, ShipIndicator[i].getSize().y / 2);
		ShipIndicatorSprite[i].setPosition(window.getSize().x*0.2 + i * 40, (window.getSize().y / 2 - 5 * SIZE) / 2);
	}

}