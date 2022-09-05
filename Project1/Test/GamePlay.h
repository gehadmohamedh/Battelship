#pragma once
#include "Ship.h"
#include "Network.h"
#include <SFML/Graphics.hpp>
#include "BoardSetup.h"
#include <iostream>
#include <iomanip>
#include <vector>
#include <sstream>
#include"HitMechanism.h"
using namespace std;

pair<int, int> getCoordinatesFromString(string data) {
	stringstream s;
	s << data;
	int x, y;
	s >> x >> y;
	return make_pair(x, y);
}

string coordinatesToString(pair<int, int> p) {
	string ret;
	ret += to_string(p.first);
	ret += " ";
	ret += to_string(p.second);
	return ret;
}


sf::Texture ShipIndicator[5];
sf::Sprite ShipIndicatorSprite[5];

void GamePlay(bool myBoard[10][10], int myBoardHits[10][10], int oppBoardHits[10][10], vector<Ship>& v, sf::TcpSocket& socket, bool firstTurn, sf::RenderWindow &window)
{

	bool gameEnded = false;
	const int SIZE = 50;
	string themeDirectory = "Ships_Blueprint/";
	bool myTurn = firstTurn;
	string title = "Battleship";
	title += (firstTurn ? " H" : " C");
	sf::Vector2f myGridOrigin(window.getSize().x * 0.1, window.getSize().y / 2 - 5 * SIZE);
	sf::Vector2f oppGridOrigin(window.getSize().x * 0.9 - 10 * SIZE, window.getSize().y / 2 - 5 * SIZE);
	sf::RectangleShape background(static_cast<sf::Vector2f>(window.getSize()));
	

	sf::Sprite myGrid, oppGrid;
	sf::Texture gridText;
	gridText.loadFromFile(themeDirectory + "Grid.png");
	myGrid.setTexture(gridText);
	oppGrid.setTexture(gridText);

	myGrid.setPosition(myGridOrigin);
	oppGrid.setPosition(oppGridOrigin);

	sf::Sprite X, O;
	sf::Texture xText, oText;
	xText.loadFromFile(themeDirectory + "X.png");
	oText.loadFromFile(themeDirectory + "O.png");
	X.setTexture(xText);
	O.setTexture(oText);

	



	
	background.setFillColor(sf::Color::Color(29, 42, 104));
	vector<sf::Texture> shipTexts;
	for (int i = 0; i < v.size(); i++) {
		sf::Texture text;
		string img = themeDirectory + to_string(v[i].id) + (v[i].orientation == 'H' ? "_H" : "_V") + "_Normal.PNG";
		text.loadFromFile(img);
		shipTexts.push_back(text);

		
	}

	int RemainingShips = 5;

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == event.Closed) {
				window.close();
			}
		}
		window.clear();
		window.draw(background);
		//Player's Board
		window.draw(myGrid);
		//Opponent's Board
		window.draw(oppGrid);
		
		
		UpdateIndicators(v, window, ShipIndicator, ShipIndicatorSprite);

		for (int i = 0; i < 5; i++)
		{
			window.draw(ShipIndicatorSprite[i]);
		}

	

		//My Ships
		for (int i = 0; i < shipTexts.size(); i++) {
			sf::Sprite ship;
			ship.setTexture(shipTexts[i]);
			ship.setPosition(sf::Vector2f(myGridOrigin.x + SIZE * v[i].x + 2, myGridOrigin.y + SIZE * v[i].y + 2));
			window.draw(ship);
		}

		//Draw hits and misses on my board.
		for (int i = 0; i < 10; i++) {
			for (int j = 0; j < 10; j++) {
				if (myBoardHits[i][j] == 1) {
					X.setPosition(myGridOrigin.x + i*SIZE, myGridOrigin.y + j*SIZE);
					window.draw(X);
				}
				else if (myBoardHits[i][j] == 0) {
					O.setPosition(myGridOrigin.x + i * SIZE, myGridOrigin.y + j * SIZE);
					window.draw(O);
				}
			}
		}

	
			//for (int i = 0; i < 5; i++)
		

		//Draw hits and misses on opponent board.
		for (int i = 0; i < 10; i++) {
			for (int j = 0; j < 10; j++) {
				if (oppBoardHits[i][j] == 1) {
					X.setPosition(oppGridOrigin.x + i * SIZE, oppGridOrigin.y + j * SIZE);
					window.draw(X);
				}
				else if (oppBoardHits[i][j] == 0) {
					O.setPosition(oppGridOrigin.x + i * SIZE, oppGridOrigin.y + j * SIZE);
					window.draw(O);
				}
			}
		}

	


		window.display();

		if (gameEnded) {
			return;
		}

		/*for (int i = 0; i < 10; i++) {
			for (int j = 0; j < 10; j++) {
				cout << setw(3) << myBoard[j][i] << " ";
			}
			cout << endl;
		}
		cout << "myBoardHits\n";
		for (int i = 0; i < 10; i++) {
			for (int j = 0; j < 10; j++) {
				cout << setw(3) << myBoardHits[j][i] << " ";
			}
			cout << endl;
		}
		cout << "oppBoardHits\n";
		for (int i = 0; i < 10; i++) {
			for (int j = 0; j < 10; j++) {
				cout << setw(3) << oppBoardHits[j][i] << " ";
			}
			cout << endl;
		}*/
		if (myTurn)
		{
			sf::Vector2i mousePos = sf::Mouse::getPosition(window);

			if (event.type == sf::Event::MouseButtonReleased)
			{
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					int x, y;
					if (mousePos.x >= oppGridOrigin.x && mousePos.x <= oppGridOrigin.x + 500 && mousePos.y >= oppGridOrigin.y && mousePos.y <= oppGridOrigin.y + 500)
					{
						x = (mousePos.x - oppGridOrigin.x) / SIZE;
						y = (mousePos.y - oppGridOrigin.y) / SIZE;
						if (oppBoardHits[x][y] != -1) {
							cout << "You tried this cell before\n";
						}
						else {
							string state, result;
							send_over_network(socket, coordinatesToString(make_pair(x, y)));
							state = wait_for_data(socket);
							cout << "NETWORK: " << state << endl;
							if (state == "SUCCESS AND WON")
							{
								oppBoardHits[x][y] = 1;
								cout << "You hit'em!!" << endl;
								cout << "You've Won The Game" << endl;
								gameEnded = true;
							}
							else if (state == "SUCCESS") {
								oppBoardHits[x][y] = 1;
								
								cout << "You hit'em!!" << endl;
							}
							else
							{
								oppBoardHits[x][y] = 0;
								myTurn = false;
							}
						}

					}
				}
			}
		}
		else
		{
			string data = wait_for_data(socket);
			if (data == "NULL") {
				continue;
			}
			pair <int, int> coordinates = getCoordinatesFromString(data);
			int x = coordinates.first;
			int y = coordinates.second;
			cout << "NETWORK: " << x << " " << y << endl;
			if (myBoard[x][y])
			{
				cout << "You've been hit!" << endl;
				myBoardHits[x][y] = 1;
				CheckShips(v, myBoardHits, RemainingShips);
				UpdateIndicators(v, window, ShipIndicator , ShipIndicatorSprite);
				for (int i = 0; i < v.size(); i++)
				//for (int i = 0; i < 5; i++)
			
				cout << RemainingShips << endl;
				if (RemainingShips == 0)

				{
					send_over_network(socket, "SUCCESS AND WON");
					cout << "You've been Defeated :(";
					gameEnded = true;
				}
				else
				{
					send_over_network(socket, "SUCCESS");
				}
			}
			else {
				myBoardHits[x][y] = 0;
				cout << "You weren't hit" << endl;
				send_over_network(socket, "you missed me");
				myTurn = true;
			}
		}
	}
}