#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include<sstream> 
#include "Options.h"
#include"Textbox.h"


#define DELETE 8
#define ESCAPE 13
#define INTER 27
using namespace std;




int ClientMenu(sf::RenderWindow &window, sf::TcpSocket &socket, Options gameOptions)
{
	sf::Sprite Exit;
	sf::Texture ExitButton;
	ExitButton.loadFromFile(gameOptions.theme + "exit.png");
	Exit.setTexture(ExitButton);
	Exit.setOrigin(ExitButton.getSize().x, 0.0f);
	Exit.setPosition(window.getSize().x, 0.0f);


	bool LeftReleased = false;
	bool RightReleased = false;
	sf::RectangleShape BackGround(static_cast<sf::Vector2f>(window.getSize()));
	sf::Sprite background;
	sf::Texture bgTexture;
	bgTexture.loadFromFile(gameOptions.backgroundImage);
	background.setTexture(bgTexture);
	background.setScale(sf::Vector2f(window.getSize().x / background.getGlobalBounds().width, window.getSize().y / background.getGlobalBounds().height));

	sf::Vector2u windowsize = window.getSize();
	window.setKeyRepeatEnabled(true);
	sf::Font font;

	Textbox textbox1(60, sf::Color::Black, true);
	textbox1.setfont(font);


	sf::RectangleShape textbox;
	textbox.setSize(sf::Vector2f(windowsize.x*0.75, windowsize.y*0.10));

	sf::Text text;
	sf::Font fonts;

	sf::Texture backbutton;
	sf::Sprite  backbuttonlinker;
	sf::Vector2f backbuttonpos1;
	sf::Vector2f backbuttonpos2;

	sf::Vector2f connectbuttonpos1;
	sf::Vector2f connectbuttonpos2;

	sf::RectangleShape conect;
	conect.setSize(sf::Vector2f(windowsize.x*0.20, windowsize.y*0.10));
	sf::Text connect;
	while (window.isOpen())
	{

		sf::Event event;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) {
			textbox1.setselected(true);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
			textbox1.setselected(false);
		}
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::MouseButtonReleased&&event.mouseButton.button == sf::Mouse::Left) {
				LeftReleased = true;
			}
			if (event.type == sf::Event::MouseButtonReleased&&event.mouseButton.button == sf::Mouse::Right) {
				RightReleased = true;
			}

			switch (event.type) {
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::TextEntered:
				textbox1.typeon(event);
				break;
			}

		}
		window.clear();
		window.draw(background);
		backbutton.loadFromFile(gameOptions.theme + "Options/back.png");
		backbuttonlinker.setTexture(backbutton);
		sf::Vector2u buttonbackpos = backbutton.getSize();
		backbuttonlinker.setPosition(sf::Vector2f(0, 0));
		sf::Vector2f coonectbutoonpos = conect.getSize();

		backbuttonpos1 = backbuttonlinker.getPosition();
		backbuttonpos2.x = backbuttonpos1.x + backbutton.getSize().x;
		backbuttonpos2.y = backbuttonpos1.y + backbutton.getSize().y;




		textbox.setPosition(sf::Vector2f(windowsize.x / 2 - textbox.getSize().x / 2, windowsize.y / 2 - textbox.getSize().y / 2));
		//textbox.setFillColor(sf::Color::Color(abs(gameOptions.textColor.r - 255), abs(gameOptions.textColor.g - 255), abs(gameOptions.textColor.b - 255)));
		textbox1.setposition({ windowsize.x / 2 - textbox1.getsize().width / 2, textbox.getPosition().y});
		conect.setPosition(sf::Vector2f(windowsize.x / 2 - conect.getSize().x / 2, (windowsize.y *0.75) - conect.getSize().y / 2));
		font.loadFromFile(gameOptions.theme + "sound.ttf");
		textbox1.setlimit(true, 15);
		textbox.setFillColor(sf::Color::White);
		conect.setFillColor(sf::Color::Black);
		text.setFont(font);
		text.setFillColor(gameOptions.textColor);
		text.setOutlineThickness(4);
		text.setOutlineColor(sf::Color::Black);
		text.setCharacterSize(45);
		text.setString("Enter Host IP");
		connect.setFont(font);
		connect.setFillColor(gameOptions.textColor);
		connect.setCharacterSize(45);
		connect.setString("Connect");
		sf::FloatRect textsize = text.getGlobalBounds();
		sf::FloatRect connectsize = connect.getGlobalBounds();
		text.setPosition(sf::Vector2f(windowsize.x / 2 - textsize.width / 2, (windowsize.y*0.30) - textsize.height / 2));
		connect.setPosition(sf::Vector2f(windowsize.x / 2 - connectsize.width / 2, (windowsize.y*0.74) - textsize.height / 2));
		connectbuttonpos1 = conect.getPosition();
		connectbuttonpos2.x = connectbuttonpos1.x + conect.getSize().x;
		connectbuttonpos2.y = connectbuttonpos1.y + conect.getSize().y;


		sf::Vector2i Mospos = sf::Mouse::getPosition(window);
		if (Mospos.x > window.getSize().x - ExitButton.getSize().x && Mospos.y < ExitButton.getSize().y && event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) { window.close(); }
		if (LeftReleased)
		{


			if (Mospos.x >= backbuttonpos1.x &&Mospos.y >= backbuttonpos1.y && Mospos.x <= backbuttonpos2.x && Mospos.y <= backbuttonpos2.y) {
				return -1;
			}
			if (Mospos.x >= connectbuttonpos1.x && Mospos.y >= connectbuttonpos1.y &&Mospos.x <= connectbuttonpos2.x&&Mospos.y <= connectbuttonpos2.y)
			{
				cout << "hhhhh\n";
				char checkConnection = EstablishConnection(socket, 'C', textbox1.gettext());
				if (checkConnection == 'C')
					return 0;
			}

		}
		LeftReleased = false;
		RightReleased = false;
		window.draw(Exit);
		window.draw(conect);
		window.draw(connect);
		window.draw(backbuttonlinker);
		window.draw(textbox);
		window.draw(text);
		textbox1.drawto(window);
		window.display();
	}
}



