#pragma once

#include<string>
#include "Options.h"
#include "OptionsMenu.h"

void statistics(sf::RenderWindow &window)
{
	window.clear();
	sf::RectangleShape BackGround3(static_cast<sf::Vector2f>(window.getSize()));
	BackGround3.setFillColor(sf::Color::Color::White);
	sf::Vector2u windowsize = window.getSize();

	bool LeftReleased = false;
	bool RightReleased = false;


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
		window.draw(BackGround3);
		window.display();



	}
}