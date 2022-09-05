#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <iostream>
#include <string>
#include<sstream> 
#include"Textbox.h"

using namespace std;

int HostMenu(sf::RenderWindow &window, sf::TcpSocket &socket) {
	sf::RectangleShape BackGround(static_cast<sf::Vector2f>(window.getSize()));
	BackGround.setFillColor(sf::Color::Color(29, 42, 104));
	sf::Vector2u windowsize = window.getSize();
	window.setKeyRepeatEnabled(true);
	sf::Font font;





	sf::Text IP;
	sf::Font fonts;
	sf::Text hostip;
	sf::Text waiting;
	sf::Texture backbutton;
	sf::Sprite  backbuttonlinker;
	sf::Vector2f backbuttonpos1;
	sf::Vector2f backbuttonpos2;

	sf::RectangleShape  IPshape;
	bool LeftReleased = false, RightReleased = false;


	while (window.isOpen())
	{

		sf::Event event;

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

			}



		}
		window.clear();
		window.draw(BackGround);
		backbutton.loadFromFile("Options/back.png");
		backbuttonlinker.setTexture(backbutton);
		sf::Vector2u buttonbackpos = backbutton.getSize();
		backbuttonlinker.setPosition(sf::Vector2f((windowsize.x *0.05) - buttonbackpos.x / 2, 0));

		font.loadFromFile("sound.ttf");
		IP.setFont(font);
		IP.setCharacterSize(60);
		IP.setFillColor(sf::Color::Color::White);
		IP.setString(sf::IpAddress::getLocalAddress().toString());
		IP.setOutlineColor(sf::Color::Black);
		IP.setOutlineThickness(4.0f);
		sf::FloatRect IPPOS = IP.getGlobalBounds();

		hostip.setFont(font);
		hostip.setCharacterSize(60);
		hostip.setFillColor(sf::Color::Color::White);
		hostip.setString("Host IP: ");

		waiting.setFont(font);
		waiting.setCharacterSize(60);
		waiting.setFillColor(sf::Color::Color::White);
		waiting.setString(sf::IpAddress::getLocalAddress().toString());
		waiting.setString("Waiting For Client");

		sf::FloatRect hostippos = hostip.getGlobalBounds();

		sf::FloatRect waitingpos = waiting.getGlobalBounds();

		IP.setPosition(sf::Vector2f(windowsize.x / 2 - IPPOS.width / 2, windowsize.y / 2 - IPPOS.height / 2));

		hostip.setPosition(sf::Vector2f(windowsize.x / 2 - hostippos.width / 2, (windowsize.y *0.30) - hostippos.height / 2));

		waiting.setPosition(sf::Vector2f(windowsize.x / 2 - waitingpos.width / 2, (windowsize.y *0.70) - waitingpos.height / 2));

		backbuttonpos1 = backbuttonlinker.getPosition();
		backbuttonpos2.x = backbuttonpos1.x + backbutton.getSize().x;
		backbuttonpos2.y = backbuttonpos1.y + backbutton.getSize().y;





		sf::Vector2i Mospos = sf::Mouse::getPosition(window);

		if (LeftReleased)
		{


			if (Mospos.x >= backbuttonpos1.x &&Mospos.y >= backbuttonpos1.y && Mospos.x <= backbuttonpos2.x && Mospos.y <= backbuttonpos2.y) {

				return -1;
			}


		}
		LeftReleased = false;
		RightReleased = false;
		window.draw(waiting);
		window.draw(hostip);
		window.draw(IP);
		window.draw(backbuttonlinker);

		window.display();
		char connection = EstablishConnection(socket, 'H', "");
		if (connection == 'H')
			return 0;
	}
}


