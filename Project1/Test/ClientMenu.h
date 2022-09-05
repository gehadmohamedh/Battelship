#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include<sstream> 
#include"Textbox.h"


#define DELETE 8
#define ESCAPE 13
#define INTER 27
using namespace std;




void ClientMenu(sf::RenderWindow &window, sf::TcpSocket &socket)
{

	bool LeftReleased = false;
	bool RightReleased = false;
	sf::RectangleShape BackGround(static_cast<sf::Vector2f>(window.getSize()));
	BackGround.setFillColor(sf::Color::Color(29, 42, 104));
	sf::Vector2u windowsize = window.getSize();
	window.setKeyRepeatEnabled(true);
	sf::Font font;

	Textbox textbox1(60, sf::Color::Black, false);
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
		window.draw(BackGround);
		backbutton.loadFromFile("Options/back.png");
		backbuttonlinker.setTexture(backbutton);
		sf::Vector2u buttonbackpos = backbutton.getSize();
		backbuttonlinker.setPosition(sf::Vector2f((windowsize.x *0.05) - buttonbackpos.x, 0));
		sf::Vector2f coonectbutoonpos = conect.getSize();

		backbuttonpos1 = backbuttonlinker.getPosition();
		backbuttonpos2.x = backbuttonpos1.x + backbutton.getSize().x;
		backbuttonpos2.y = backbuttonpos1.y + backbutton.getSize().y;




		textbox.setPosition(sf::Vector2f(windowsize.x / 2 - textbox.getSize().x / 2, windowsize.y / 2 - textbox.getSize().y / 2));
		textbox1.setposition({ windowsize.x / 2 - textbox1.getsize().width / 2 ,windowsize.y / 2 - textbox1.getsize().height / 2 });
		conect.setPosition(sf::Vector2f(windowsize.x / 2 - conect.getSize().x / 2, (windowsize.y *0.75) - conect.getSize().y / 2));
		font.loadFromFile("sound.ttf");
		textbox1.setlimit(true, 15);
		textbox.setFillColor(sf::Color::Color::White);
		conect.setFillColor(sf::Color::Color::White);
		text.setFont(font);
		text.setCharacterSize(45);
		text.setString("Enter Host IP");
		connect.setFont(font);
		connect.setFillColor(sf::Color::Color::Black);
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

		if (LeftReleased)
		{


			if (Mospos.x >= backbuttonpos1.x &&Mospos.y >= backbuttonpos1.y && Mospos.x <= backbuttonpos2.x && Mospos.y <= backbuttonpos2.y) {

				return;
			}
			if (Mospos.x >= connectbuttonpos1.x && Mospos.y >= connectbuttonpos1.y &&Mospos.x <= connectbuttonpos2.x&&Mospos.y <= connectbuttonpos2.y)
			{
				cout << "hhhhh\n";
				EstablishConnection(socket, 'C', textbox1.gettext());
				return;
			}

		}
		LeftReleased = false;
		RightReleased = false;
		window.draw(conect);
		window.draw(connect);
		window.draw(backbuttonlinker);
		window.draw(textbox);
		window.draw(text);
		textbox1.drawto(window);
		window.display();
	}
}



