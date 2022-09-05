
#include<SFML/Graphics.hpp>
#include<iostream>
#include<string>
#include "Options.h"
#include "OptionsMenu.h" 
#include "Stats.h"
#include"ClientMenu.h"
#include "HostMenu.h"
#include <SFML/Audio.hpp>

using namespace std;








char MainMenu(sf::RenderWindow& window, sf::TcpSocket &socket, Options &gameOptions, sf::Music& sound)
{
	sf::Sprite Exit;
	sf::Texture ExitButton;
	ExitButton.loadFromFile(gameOptions.theme + "exit.png");
	Exit.setTexture(ExitButton);
	Exit.setOrigin(ExitButton.getSize().x, 0.0f);
	Exit.setPosition(window.getSize().x, 0.0f);

	sf::Vector2f optionSpriteOrigin;
	sf::Vector2f optionSpriteBounds;
	bool LeftReleased = false;
	bool RightReleased = false;
	sf::Texture  BattleShipPhoto;

	sf::Vector2u WindowSize = window.getSize();
	sf::Sprite battleShipSprite;

	sf::Sprite background;
	sf::Texture bgTexture;
	bgTexture.loadFromFile(gameOptions.theme + "background.jpg");
	background.setTexture(bgTexture);
	background.setScale(sf::Vector2f(window.getSize().x / background.getGlobalBounds().width, window.getSize().y / background.getGlobalBounds().height));
	sf::Text menuText;
	sf::Font menuFont;
	sf::Texture optionsTexture;
	sf::Sprite optionsSprite;
	
	int fontsize = 35;
	sf::SoundBuffer buffer;
	sound.openFromFile(gameOptions.musicFile);
	sound.setVolume(50);
	sound.play();



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
		if (sound.getStatus() == sf::Sound::Status::Playing) {
			if (!gameOptions.sound) {
				sound.stop();
			}
		}
		else {
			if (gameOptions.sound) {
				sound.play();
			}
		}
		window.clear();
		bgTexture.loadFromFile(gameOptions.backgroundImage);
		background.setTexture(bgTexture);
		window.draw(background);
		if (!BattleShipPhoto.loadFromFile(gameOptions.theme + "BATTLESSHIPS.png")) {
			cout << "didnot work for now" << endl;
		}
		battleShipSprite.setTexture(BattleShipPhoto);
		sf::Vector2u BattleShipSize = BattleShipPhoto.getSize();
		battleShipSprite.setPosition(sf::Vector2f(WindowSize.x / 2 - BattleShipSize.x / 2, window.getSize().y * 0.175));

		menuText.setFont(menuFont);
		menuFont.loadFromFile(gameOptions.theme + "sound.ttf");
		menuText.setString("Click This Side To Be HOST" + string((int)(0.1*WindowSize.x/fontsize), '\t') + "Click This Side To Be CLIENT ");
		menuText.setCharacterSize(fontsize);
		menuText.setFillColor(gameOptions.textColor);
		menuText.setOutlineThickness(4);
		menuText.setOutlineColor(sf::Color::Black);


		sf::FloatRect textsize = menuText.getGlobalBounds();


		menuText.setPosition(sf::Vector2f(WindowSize.x / 2 - textsize.width / 2, (WindowSize.y*0.9) - textsize.height / 2));



		optionsTexture.loadFromFile(gameOptions.theme + "options.png");
		optionsSprite.setTexture(optionsTexture);
		sf::Vector2u OptionSize = optionsTexture.getSize();
		optionsSprite.setPosition(sf::Vector2f(0, 0));
		optionSpriteOrigin = optionsSprite.getPosition();

		optionSpriteBounds.x = optionSpriteOrigin.x + optionsTexture.getSize().x;
		optionSpriteBounds.y = optionSpriteOrigin.y + optionsTexture.getSize().y;
		sf::Vector2i MousePos = sf::Mouse::getPosition(window);
		if (MousePos.x > window.getSize().x - ExitButton.getSize().x && MousePos.y < ExitButton.getSize().y && event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) { window.close(); }

		if (MousePos.x >= optionSpriteOrigin.x&&MousePos.y >= optionSpriteOrigin.y&&MousePos.x <= optionSpriteBounds.x&&MousePos.y <= optionSpriteBounds.y)
		{
			cout << LeftReleased << endl;
			if (LeftReleased)
			{
				optionsFunction(window, gameOptions, sound);
			}
		}
		else {
			if (LeftReleased) {
				
				if (MousePos.x <= WindowSize.x / 2) {
					cout << "host";
					int check = HostMenu(window, socket, gameOptions);
					if (check == 0)
						return 'H';
				}
				else {
					int check = ClientMenu(window, socket, gameOptions);
					if(check == 0)
						return 'C';
				}
			}
		}
		LeftReleased = false;
		RightReleased = false;
		window.draw(Exit);
		window.draw(battleShipSprite);
		window.draw(optionsSprite);
		window.draw(menuText);
		window.display();
	}
}







