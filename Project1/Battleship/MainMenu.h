
#include<SFML/Graphics.hpp>
#include<iostream>
#include<string>
#include "Options.h"
#include "OptionsMenu.h" 
#include "Stats.h"
#include"ClientMenu.h"
#include "HostMenu.h"

using namespace std;








char MainMenu(sf::RenderWindow& window, sf::TcpSocket &socket)
{

	sf::Vector2f position1;
	sf::Vector2f position2;
	bool LeftReleased = false;
	bool RightReleased = false;
	sf::Texture  BattleShipPhoto;

	sf::Vector2u WindowSize = window.getSize();
	sf::Sprite PhotoLinker;

	sf::RectangleShape BackGround(static_cast<sf::Vector2f>(window.getSize()));
	BackGround.setFillColor(sf::Color::Color(29, 42, 104));
	sf::Text MenueText;
	sf::Font menueFont;
	sf::Texture Options;
	sf::Sprite OptionsSprite;
	
	int fontsize = 35;



	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{

			if (event.type == event.Closed) {
				window.close();
			}
			if (event.type == sf::Event::MouseButtonReleased&&event.mouseButton.button == sf::Mouse::Left) {
				LeftReleased = true;
			}
			if (event.type == sf::Event::MouseButtonReleased&&event.mouseButton.button == sf::Mouse::Right) {
				RightReleased = true;
			}


		}

		window.clear();
		window.draw(BackGround);
		if (!BattleShipPhoto.loadFromFile("BATTLESSHIPS.jpg")) {
			cout << "didnot work for now" << endl;
		}
		PhotoLinker.setTexture(BattleShipPhoto);
		sf::Vector2u BattleShipSize = BattleShipPhoto.getSize();
		PhotoLinker.setPosition(sf::Vector2f(WindowSize.x / 2 - BattleShipSize.x / 2, WindowSize.y / 2 - BattleShipSize.y / 2));

		MenueText.setFont(menueFont);
		menueFont.loadFromFile("sound.ttf");
		MenueText.setString("Click This Side To Be HOST" + string((int)(0.1*WindowSize.x/fontsize), '\t') + "Click This Side To Be CLIENT ");
		MenueText.setCharacterSize(fontsize);


		sf::FloatRect textsize = MenueText.getGlobalBounds();


		MenueText.setPosition(sf::Vector2f(WindowSize.x / 2 - textsize.width / 2, (WindowSize.y*0.9) - textsize.height / 2));



		Options.loadFromFile("options.png");
		OptionsSprite.setTexture(Options);
		sf::Vector2u OptionSize = Options.getSize();
		OptionsSprite.setPosition(sf::Vector2f(WindowSize.x - OptionSize.x, 0));
		position1 = OptionsSprite.getPosition();

		position2.x = position1.x + Options.getSize().x;
		position2.y = position1.y + Options.getSize().y;
		sf::Vector2i MosPosition = sf::Mouse::getPosition(window);

		if (MosPosition.x >= position1.x&&MosPosition.y >= position1.y&&MosPosition.x <= position2.x&&MosPosition.y <= position2.y)
		{
			cout << LeftReleased << endl;
			if (LeftReleased)
			{

				optionsFunction(window);


			}
		}
		else {
			if (LeftReleased) {
				
				if (MosPosition.x <= WindowSize.x / 2) {
					cout << "host";
					int check = HostMenu(window, socket);
					if (check == 0)
						return 'H';
				}
				else {
					int check = ClientMenu(window, socket);
					if(check == 0)
						return 'C';
				}
			}
		}


		if (LeftReleased)
		{
			LeftReleased = false;
		}
		if (RightReleased)
		{

			RightReleased = false;
		}

		window.draw(PhotoLinker);
		window.draw(OptionsSprite);
		window.draw(MenueText);
		window.display();

	}
}







