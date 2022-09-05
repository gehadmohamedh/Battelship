#include <iostream>
#include <vector>
#include "BoardSetup.h"
#include "GameSetup.h"
#include "GamePlay.h"
#include "Ship.h"
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/Audio.hpp>
#include "HitMechanism.h"
#include "MainMenu.h"
#include "Stats.h"
using namespace std;


//Hits on player's board (-1 for untried, 0 for miss, 1 for hit)
int myBoardHits[10][10];

//Hits on opponent's board (-1 for untried, 0 for miss, 1 for hit)
int oppBoardHits[10][9+1];


//Where there's ships on player's board (0 for vacant, 1 for occupied)
bool myBoard[10][10];

//Global socket
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

	//Game Options variable is passed to all menus/functions.
	Options gameOptions;

	//Global window across all menus.
	sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "Battleship", sf::Style::Fullscreen);

	//Global background music.
	sf::Music sound;
	sound.setLoop(true);

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == event.Closed) {
				window.close();
			}
		}

		//Reset the ships
		v.clear();
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


		//Initialize all boards.
		for (int i = 0; i < 10; i++) {
			for (int j = 0; j < 10; j++) {
				myBoard[i][j] = 0;
				myBoardHits[i][j] = -1;
				oppBoardHits[i][j] = -1;
			}
		}
		//The Main Menu returns a character indicating the type of connection (H)ost / (C)lient.
		char connectionType = MainMenu(window, socket, gameOptions, sound);

		//Open game setup.
		GameSetup(v, myBoard, socket, window, gameOptions);
		cout << "Game started";

		//If the user is a Host he gets to play first.
		bool firstTurn = (connectionType == 'H' ? 1 : 0);
		GamePlay(myBoard, myBoardHits, oppBoardHits, v, socket, firstTurn, window, gameOptions);
		cout << "Game is finished" << endl;
		sf::Sprite Exit;
		sf::Texture ExitButton;
		ExitButton.loadFromFile(gameOptions.theme + "exit.png");
		Exit.setTexture(ExitButton);
		Exit.setOrigin(ExitButton.getSize().x, 0.0f);
		Exit.setPosition(window.getSize().x, 0.0f);
		statistics(gameOptions, window);
		sound.stop();
		socket.disconnect();
	}
	return 0;
}




