#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <iostream>
#include <string>
#include "Ship.h"
#include "BoardSetup.h"
#include "Network.h"
using namespace std;

const int SIZE = 50;

string themeDirectory = "Ships_Blueprint/";
bool isSelfReady = false;

sf::Vector2i getCellFromCoordinates(sf::Vector2i PixelPos, sf::Vector2f GridOrigin) {
	sf::Vector2i BoardPos((PixelPos.x - GridOrigin.x) / SIZE, (-GridOrigin.y + PixelPos.y) / SIZE);
	return BoardPos;
}

sf::Vector2i getCoordinatesFromCell(sf::Vector2i CellPos, sf::Vector2f GridOrigin) {
	sf::Vector2i PixelPos(GridOrigin.x + CellPos.x * SIZE + 2, GridOrigin.y + CellPos.y * SIZE + 1);
	return PixelPos;
}

void reloadTextures(sf::Texture ShipTextures[5][3], vector<Ship> v) {
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 3; j++) {
			string FileName = themeDirectory + to_string(v[i].id) + "_" + v[i].orientation + "_";
			if (j == 0) {
				FileName += "Normal.png";
			}
			if (j == 1) {
				FileName += "Hover.png";
			}
			if (j == 2) {
				FileName += "Pressed.png";
			}
			ShipTextures[i][j].loadFromFile(FileName);
		}
	}
}
void GameSetup(vector<Ship> &v, bool board[10][10], sf::TcpSocket &socket, sf::RenderWindow &window)
{
	//Create a window and a background rectangle.
	sf::RectangleShape background(static_cast<sf::Vector2f>(window.getSize()));
	background.setFillColor(sf::Color::Color(29, 42, 104));

	//Create an origin vector for the grid.
	sf::Vector2f origin(window.getSize().x / 2 - 5 * SIZE, window.getSize().y / 2 - 5 * SIZE);

	//Create labels
	sf::Text Header;
	string label = "Place your ships!";
	Header.setString(label);
	sf::Font font;
	font.loadFromFile("arial.ttf");
	Header.setFont(font);
	Header.setCharacterSize(45);
	Header.setOrigin(Header.getGlobalBounds().width / 2, Header.getGlobalBounds().height / 2);
	Header.setPosition(window.getSize().x / 2, 50);



	//index of currently selected ship.
	int selectedid = -1;

	//Create a ready button.

	//Create a template Sprite for a cell grid.
	sf::Sprite Grid;
	sf::Texture GridText;
	GridText.loadFromFile(themeDirectory + "Grid.png");
	Grid.setTexture(GridText);
	Grid.setPosition(origin);




	//Create an Array for the Current and Original Position of each ship.
	sf::Vector2f Positions[5];
	sf::Vector2f OriginalPosition[5];

	for (int i = 0; i < 5; i++) {
		Positions[i].x = origin.x / 2.0 - (v[i].length / 2.0 * SIZE);
		Positions[i].y = origin.y + (100 * i);
		OriginalPosition[i] = Positions[i];
	}

	//Load All 3 textures in a 2D Array 0 representing Normal, 1 for Hovered, 2 for pressed. 
	sf::Texture ShipTextures[5][3];
	reloadTextures(ShipTextures, v);


	//Flags marking if a mouse button is released (updated once per frame).
	bool RightReleased = false, LeftReleased = false;

	//Main Loop
	while (window.isOpen()) {
		if (isSelfReady) {
			send_over_network(socket, "READY!!!");
			string result = wait_for_data(socket);
			cout << result << endl;
			if (result == "READY!!!") {
				return;
			}
		}
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == event.Closed) {
				window.close();
			}
			//Was the right mouse button released.
			if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Right) {
				RightReleased = true;
			}
			//Was the left mouse button released.
			if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
			{
				LeftReleased = true;
			}
		}
		//Clearing the Window then Drawing the Background.
		window.clear();
		window.draw(background);
		window.draw(Header);

		//Drawing the Grid.
		window.draw(Grid);

		//Create an array for the Ship Sprites and draw the Normal Texture Initially.
		sf::Sprite ShipSprites[5];

		for (int i = 0; i < 5; i++) {
			ShipSprites[i].setTexture(ShipTextures[i][0]);
			ShipSprites[i].setPosition(Positions[i].x, Positions[i].y);
			window.draw(ShipSprites[i]);
		}

		//Get the current mouse position.
		sf::Vector2i MousePos = sf::Mouse::getPosition(window);


		//If No Ship is Selected.
		if (selectedid == -1) {

			//For each ship.
			for (int i = 0; i < 5; i++) {
				//Get the Bottom Right Corner of the Ship.
				sf::Vector2f Position2;
				if (v[i].orientation == 'H') {
					Position2.x = Positions[i].x + 50 * v[i].length;
					Position2.y = Positions[i].y + 50;
				}
				else {
					Position2.x = Positions[i].x + 50;
					Position2.y = Positions[i].y + 50 * v[i].length;
				}

				//If the mouse was over a ship.
				if ((MousePos.x >= Positions[i].x && MousePos.x <= Position2.x) && (MousePos.y >= Positions[i].y && MousePos.y <= Position2.y)) {

					//If the Left Mouse Button Was Pressed.
					if (LeftReleased) {

						//Remove the ship from the board to be able to place it somewhere else.
						if (v[i].placed) {
							RemoveShip(v[i], board);
						}
						//Sets the texture to the pressed texture and redrawing the ship.
						ShipSprites[i].setTexture(ShipTextures[i][2]);
						window.draw(ShipSprites[i]);

						//Set the selected id to i.
						selectedid = i;
					}
					//Change orientation of the ship if right mouse button is pressed.
					else if (RightReleased) {
						if (v[i].placed) {
							ChangeOrientation(v[i], board);
							reloadTextures(ShipTextures, v);
						}
					}
					//If the Mouse Button is NOT Pressed.
					else {
						//Sets the texture to the Hover texture and redrawing the ship.
						ShipSprites[i].setTexture(ShipTextures[i][1]);
						window.draw(ShipSprites[i]);
					}
				}
				//If the Mouse is NOT over the Ship.
				else {
					//Set the texture to the normal texture and redrawing the ship.
					ShipSprites[i].setTexture(ShipTextures[i][0]);
					window.draw(ShipSprites[i]);
				}
			}
		}
		//If there is a Selected Ship.
		else {
			//Set the position of selected ship to the Mouse Position.
			Positions[selectedid] = sf::Vector2f(MousePos.x - SIZE / 2, MousePos.y - SIZE / 2);

			//If Right Mouse Button is Clicked.
			if (RightReleased)
			{
				//Change the Orientation of the Ship.
				if (v[selectedid].orientation == 'H') {
					v[selectedid].orientation = 'V';
				}
				else
				{
					v[selectedid].orientation = 'H';
				}
				//Reload the Texures to apply effect.
				reloadTextures(ShipTextures, v);
			}
			//If Left Mouse Button is Clicked.
			if (LeftReleased)
			{
				//If the mouse is on the Grid.
				if (MousePos.x >= origin.x &&
					MousePos.y >= origin.y &&
					MousePos.x <= origin.x + SIZE * 10 &&
					MousePos.y <= origin.y + SIZE * 10) {

					//Convert the Current Mouse Position in Pixels to a Grid Coordinate ([0, 9], [0, 9]).
					sf::Vector2i pos = getCellFromCoordinates(MousePos, origin);

					//Set the position of the selected ship to the clicked cell.
					v[selectedid].x = pos.x;
					v[selectedid].y = pos.y;

					//Try to place the ship on the board.
					int check = PlaceShip(v[selectedid], board);

					//If successful.
					if (check == 0)
					{
						//Set the placed flag to true;
						v[selectedid].placed = true;

						//Set the position of the Ship to the position of the Cell in Pixels.
						Positions[selectedid] = sf::Vector2f(static_cast<sf::Vector2f>(getCoordinatesFromCell(pos, origin)));

						//Unselect the ship.
						selectedid = -1;
					}
				}
				//If the user trys to place a ship anywhere else it returns to it's original position.
				else {
					v[selectedid].orientation = 'H';
					reloadTextures(ShipTextures, v);
					Positions[selectedid] = OriginalPosition[selectedid];
					v[selectedid].placed = false;
					selectedid = -1;
				}
			}
		}

		//Check if the ships are placed.
		bool allPlaced = true;
		for (int i = 0; i < 5; i++) {
			if (!v[i].placed) {
				allPlaced = false;
				break;
			}
		}

		//If all ships are placed show the READY button.
		if (allPlaced) {
			sf::Sprite button;
			sf::Texture Normal, Hover, Pressed;
			Normal.loadFromFile(themeDirectory + "READY.png");
			Hover.loadFromFile(themeDirectory + "READY_hover.png");
			Pressed.loadFromFile(themeDirectory + "READY_pressed.png");
			button.setPosition(window.getSize().x * 0.85 - Normal.getSize().x / 2, window.getSize().y * 0.75 - Normal.getSize().y / 2);
			if (MousePos.x >= button.getPosition().x &&
				MousePos.y >= button.getPosition().y &&
				MousePos.x <= button.getPosition().x + Normal.getSize().x &&
				MousePos.y <= button.getPosition().y + Normal.getSize().y) {
				if (LeftReleased) {
					button.setTexture(Normal);
					isSelfReady = true;
				}
				else {
					button.setTexture(Hover);
				}
			}
			else {
				button.setTexture(Normal);
			}
			if (v[0].x == 0 && v[0].y == 0 && v[0].orientation == 'V' &&
				v[1].x == 1 && v[1].y == 1 && v[1].orientation == 'V' &&
				v[2].x == 2 && v[2].y == 2 && v[2].orientation == 'V' &&
				v[3].x == 3 && v[3].y == 3 && v[3].orientation == 'V' &&
				v[4].x == 4 && v[4].y == 4 && v[4].orientation == 'V') {
				Header.setString("MARIA STOP DEBUGGING!!");
				Header.setOrigin(Header.getGlobalBounds().width / 2, Header.getGlobalBounds().height / 2);
				Header.setPosition(window.getSize().x / 2, 50);
			}
			window.draw(button);
		}
		window.display();

		//Reset the click flags.
		LeftReleased = false;
		RightReleased = false;
	}
	return;
}