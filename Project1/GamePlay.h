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
#include <fstream>
#include <SFML/Audio.hpp>

using namespace std;

pair<int, int> getCoordinatesFromString(string data) {
	stringstream s;
	s << data;
	string check;
	int x, y;
	s >> check >> x >> y;
	return make_pair(x, y);
}

string coordinatesToString(pair<int, int> p) {
	string ret = "coord ";
	ret += to_string(p.first);
	ret += " ";
	ret += to_string(p.second);
	return ret;
}


sf::Texture ShipIndicator[5];
sf::Sprite ShipIndicatorSprite[5];

void GamePlay(bool myBoard[10][10], int myBoardHits[10][10], int oppBoardHits[10][10], vector<Ship>& v, sf::TcpSocket& socket, bool firstTurn, sf::RenderWindow &window, Options gameOptions)
{
	// create array for statistic
	int stat[6] = {};
	ifstream input;
	input.open("stat.txt");
	for (int i = 0; i < 6; i++)
		input >> stat[i];

	input.close();

	//incrementing the number of game plays
	stat[0]++;

	sf::Sprite Exit;
	sf::Texture ExitButton;
	ExitButton.loadFromFile(gameOptions.theme + "exit.png");
	Exit.setTexture(ExitButton);
	Exit.setOrigin(ExitButton.getSize().x, 0.0f);
	Exit.setPosition(window.getSize().x, 0.0f);

	sf::Sound sounde;
	sf::SoundBuffer buffer;

	bool gameEnded = false;
	const int SIZE = 50;
	string themeDirectory = gameOptions.theme;
	bool myTurn = firstTurn;
	string title = "Battleship";
	title += (firstTurn ? " H" : " C");
	window.setTitle(title);
	sf::Vector2f myGridOrigin(window.getSize().x * 0.1, window.getSize().y / 2 - 5 * SIZE);
	sf::Vector2f oppGridOrigin(window.getSize().x * 0.9 - 10 * SIZE, window.getSize().y / 2 - 5 * SIZE);
	if (gameOptions.InvertGrid) {
		swap(myGridOrigin, oppGridOrigin);
	}
	sf::Text whoseTurnLabel;
	sf::Font font;
	font.loadFromFile(gameOptions.theme + "sound.ttf");
	whoseTurnLabel.setFont(font);
	whoseTurnLabel.setCharacterSize(30);
	whoseTurnLabel.setFillColor(gameOptions.textColor);

	sf::Sprite myindc123, myindcABC;
	sf::Texture mytext123, mytextABC;
	mytext123.loadFromFile(gameOptions.theme + "123.png");
	mytextABC.loadFromFile(gameOptions.theme + "ABC.png");
	myindc123.setTexture(mytext123);
	myindcABC.setTexture(mytextABC);

	myindc123.setPosition(myGridOrigin.x - 20, myGridOrigin.y);
	myindcABC.setPosition(myGridOrigin.x, myGridOrigin.y - 20);

	sf::Sprite oppindc123, oppindcABC;
	sf::Texture opptext123, opptextABC;
	opptext123.loadFromFile(gameOptions.theme + "123.png");
	opptextABC.loadFromFile(gameOptions.theme + "ABC.png");
	oppindc123.setTexture(opptext123);
	oppindcABC.setTexture(opptextABC);

	oppindc123.setPosition(oppGridOrigin.x - 20, oppGridOrigin.y);
	oppindcABC.setPosition(oppGridOrigin.x, oppGridOrigin.y - 20);

	if (firstTurn) {
		whoseTurnLabel.setString("Your Turn");
		whoseTurnLabel.setOrigin(sf::Vector2f(whoseTurnLabel.getGlobalBounds().width / 2, whoseTurnLabel.getGlobalBounds().height / 2));
		whoseTurnLabel.setPosition(sf::Vector2f(window.getSize().x / 2, myGridOrigin.y / 2));
	}
	else {
		whoseTurnLabel.setString("Opponent's Turn");
		whoseTurnLabel.setOrigin(sf::Vector2f(whoseTurnLabel.getGlobalBounds().width / 2, whoseTurnLabel.getGlobalBounds().height / 2));
		whoseTurnLabel.setPosition(sf::Vector2f(window.getSize().x / 2, myGridOrigin.y / 2));
	}


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

	



	
	sf::Sprite background;
	sf::Texture bgTexture;
	bgTexture.loadFromFile(gameOptions.theme + "background2.jpg");
	background.setTexture(bgTexture);
	background.setScale(sf::Vector2f(window.getSize().x / background.getGlobalBounds().width, window.getSize().y / background.getGlobalBounds().height));

	vector<sf::Texture> shipTexts;
	for (int i = 0; i < v.size(); i++) {
		sf::Texture text;
		string img = themeDirectory + to_string(v[i].id) + (v[i].orientation == 'H' ? "_H" : "_V") + "_Normal.PNG";
		text.loadFromFile(img);
		shipTexts.push_back(text);
	}

	int RemainingShips = 5;

	bool LeftReleased = false;
	//Main Game Loop
	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == event.Closed) {
				window.close();
			}
			if (event.type == event.MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
				LeftReleased = true;
			}
		}
		window.clear();
		window.draw(background);
		//Player's Board
		window.draw(myGrid);
		//Opponent's Board
		window.draw(oppGrid);

		window.draw(myindc123);
		window.draw(myindcABC);

		window.draw(oppindc123);
		window.draw(oppindcABC);

		window.draw(Exit);
		window.draw(whoseTurnLabel);

		UpdateIndicators(v, window, ShipIndicator, ShipIndicatorSprite, themeDirectory);

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
					X.setPosition(myGridOrigin.x + i*SIZE + 1, myGridOrigin.y + j*SIZE + 1);
					window.draw(X);
				}
				else if (myBoardHits[i][j] == 0) {
					O.setPosition(myGridOrigin.x + i * SIZE + 2, myGridOrigin.y + j * SIZE + 2);
					window.draw(O);
				}
			}
		}

	
		

		//Draw hits and misses on opponent board.
		for (int i = 0; i < 10; i++) {
			for (int j = 0; j < 10; j++) {
				if (oppBoardHits[i][j] == 1) {
					X.setPosition(oppGridOrigin.x + i * SIZE + 1, oppGridOrigin.y + j * SIZE + 1);
					window.draw(X);
				}
				else if (oppBoardHits[i][j] == 0) {
					O.setPosition(oppGridOrigin.x + i * SIZE + 2, oppGridOrigin.y + j * SIZE + 2);
					window.draw(O);
				}
			}
		}

	



		
		window.display();
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
		
		sf::Vector2i mousePos = sf::Mouse::getPosition(window);
		if (mousePos.x > window.getSize().x - ExitButton.getSize().x && mousePos.y < ExitButton.getSize().y && LeftReleased) { 
			window.close();
		}

		if (myTurn)
		{
			whoseTurnLabel.setString("Your Turn");
			whoseTurnLabel.setOrigin(sf::Vector2f(whoseTurnLabel.getGlobalBounds().width / 2, whoseTurnLabel.getGlobalBounds().height / 2));
			whoseTurnLabel.setPosition(sf::Vector2f(window.getSize().x / 2, myGridOrigin.y / 2));
			if (LeftReleased)
			{
					int x, y;
					if (mousePos.x >= oppGridOrigin.x && mousePos.x <= oppGridOrigin.x + 503 && mousePos.y >= oppGridOrigin.y && mousePos.y <= oppGridOrigin.y + 503)
					{
						x = (mousePos.x - oppGridOrigin.x) / SIZE;
						y = (mousePos.y - oppGridOrigin.y) / SIZE;
						if (oppBoardHits[x][y] != -1) {
							cout << "You tried this cell before\n";
						}
						else {
							//counting number of tries 
							stat[1]++;
							string state, result;
							send_over_network(socket, coordinatesToString(make_pair(x, y)));
							state = wait_for_data(socket);
							while (state == "NULL") {
								cout << "Nothing recieved" << endl;
								state = wait_for_data(socket);
							}
							cout << "NETWORK: " << state << endl;
							if (state == "SUCCESS AND WON")
							{
								sounde.setBuffer(buffer);
								buffer.loadFromFile("Sounds/hit.wav");
								sounde.play();
								oppBoardHits[x][y] = 1;
								cout << "You hit'em!!" << endl;
								cout << "You've Won The Game" << endl;
								whoseTurnLabel.setString("YOU WIN!");
								whoseTurnLabel.setCharacterSize(50);
								whoseTurnLabel.setOrigin(sf::Vector2f(whoseTurnLabel.getGlobalBounds().width / 2, whoseTurnLabel.getGlobalBounds().height / 2));
								whoseTurnLabel.setPosition(sf::Vector2f(window.getSize().x / 2, myGridOrigin.y / 2));
								window.draw(whoseTurnLabel);
								gameEnded = true;
								//incrementing number of hits
								stat[2]++;
								// counting number of wins 
								stat[4]++;
								myTurn = false;
								continue;
							}
							else if (state == "SUCCESS") {
								oppBoardHits[x][y] = 1;
								if (gameOptions.soundFX) {
									sounde.setBuffer(buffer);
									buffer.loadFromFile("Sounds/hit.wav");
									sounde.play();
								}
								cout << "You hit'em!!" << endl;
								// counting number of hits
								stat[2]++;
							}
							else if("you missed me")
							{
								if (gameOptions.soundFX) {
									sounde.setBuffer(buffer);
									buffer.loadFromFile("Sounds/miss.wav");
									sounde.play();
								}
								oppBoardHits[x][y] = 0;
								// counting number of misses 
								stat[3]++;
								myTurn = false;
							}
						}
					}
			}
		}
		else if(!gameEnded)
		{
			whoseTurnLabel.setString("Opponent's Turn");
			whoseTurnLabel.setOrigin(sf::Vector2f(whoseTurnLabel.getGlobalBounds().width / 2, whoseTurnLabel.getGlobalBounds().height / 2));
			whoseTurnLabel.setPosition(sf::Vector2f(window.getSize().x / 2, myGridOrigin.y / 2));
			window.draw(whoseTurnLabel);
			string data = wait_for_data(socket);
			if (data == "NULL") {
				continue;
			}
			if (data.substr(0, 5) != "coord") {
				continue;
			}
			pair <int, int> coordinates = getCoordinatesFromString(data);
			int x = coordinates.first;
			int y = coordinates.second;
			cout << "NETWORK: " << data << endl;
			if (myBoard[x][y])
			{
				cout << "You've been hit!" << endl;
				if (gameOptions.soundFX) {
					sounde.setBuffer(buffer);
					buffer.loadFromFile("Sounds/hit.wav");
					sounde.play();
				}
				myBoardHits[x][y] = 1;
				CheckShips(v, myBoardHits, RemainingShips);
				UpdateIndicators(v, window, ShipIndicator , ShipIndicatorSprite, themeDirectory);
				for (int i = 0; i < v.size(); i++)
				//for (int i = 0; i < 5; i++)
			
				cout << RemainingShips << endl;
				if (RemainingShips == 0)

				{
					send_over_network(socket, "SUCCESS AND WON");
					cout << "You've been Defeated :(";
					// counting number of losses 
					stat[5]++;
					whoseTurnLabel.setString("You Lost :(");
					whoseTurnLabel.setCharacterSize(50);
					whoseTurnLabel.setOrigin(sf::Vector2f(whoseTurnLabel.getGlobalBounds().width / 2, whoseTurnLabel.getGlobalBounds().height / 2));
					whoseTurnLabel.setPosition(sf::Vector2f(window.getSize().x / 2, myGridOrigin.y / 2));
					gameEnded = true;
					continue;
				}
				else
				{
					send_over_network(socket, "SUCCESS");
				}
			}
			else {
				myBoardHits[x][y] = 0;
				cout << "You weren't hit" << endl;
				if (gameOptions.soundFX) {
					sounde.setBuffer(buffer);
					buffer.loadFromFile("Sounds/miss.wav");
					sounde.play();
				}
				send_over_network(socket, "you missed me");
				myTurn = true;
			}
		}
		if (gameEnded) {
			ofstream output;
			output.open("stat.txt");
			for (int i = 0; i < 6; i++)
			{
				output << stat[i] << endl;
			}
			output.close();
			sf::sleep(sf::seconds(2));
			return;
		}
		LeftReleased = false;
	}
}