#include <iostream>
#include <vector>
#include "BoardSetup.h"
#include "GameSetup.h"
#include "GamePlay.h"
#include "Ship.h"
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include "HitMechanism.h"
using namespace std;

int myBoardHits[10][10];
int oppBoardHits[10][10];
bool myBoard[10][10];
sf::TcpSocket socket;

int main()
{
	//Create a vector for Ships.
	vector<Ship> v;
	v.push_back(Ship(5, 'H', -1, -1, 1));
	v.push_back(Ship(4, 'H', -1, -1, 2));
	v.push_back(Ship(3, 'H', -1, -1, 3));
	v.push_back(Ship(3, 'H', -1, -1, 4));
	v.push_back(Ship(2, 'H', -1, -1, 5));


	//Initialize all boards.
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			myBoard[i][j] = 0;
			myBoardHits[i][j] = -1;
			oppBoardHits[i][j] = -1;
		}
	}

	//Try to establish a connection.
	char checkConnection = EstablishConnection(socket);
	while (checkConnection == 'n') {
		cout << "Connection can't be made...Try again\n";
		checkConnection = EstablishConnection(socket);
	}

	sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "Battleship", sf::Style::Close);
	
	//Open game setup.
	GameSetup(v, myBoard, socket, window);
	cout << "Game started";
	bool firstTurn = (checkConnection == 'H' ? 1 : 0);
	GamePlay(myBoard, myBoardHits, oppBoardHits, v, socket, firstTurn, window);
	cout << "Game is finished" << endl;
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == event.Closed) {
				window.close();
			}
		}
	}
	system("pause");
	return 0;
}




