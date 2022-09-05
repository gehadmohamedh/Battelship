#pragma once

#include <string>
#include <sstream>
#include "Options.h"
#include "OptionsMenu.h"

string toString(float rate) {
	stringstream ss;
	ss << fixed << setprecision(2) << rate;
	return ss.str();
}

void statistics(Options gameOptions, sf::RenderWindow &window)
{
	sf::Sprite Exit;
	sf::Texture ExitButton;
	ExitButton.loadFromFile(gameOptions.theme + "exit.png");
	Exit.setTexture(ExitButton);
	Exit.setOrigin(ExitButton.getSize().x, 0.0f);
	Exit.setPosition(window.getSize().x, 0.0f);

	window.clear();
	sf::Sprite background;
	sf::Texture bgTexture;
	bgTexture.loadFromFile(gameOptions.backgroundImage);
	background.setTexture(bgTexture);
	sf::Vector2u windowsize = window.getSize();
	background.setScale(sf::Vector2f(window.getSize().x / background.getGlobalBounds().width, window.getSize().y / background.getGlobalBounds().height));

	// for statistics values
	float stat[6] = {};
	ifstream input;
	input.open("stat.txt");

	for (int i = 0; i < 6; i++)
		input >> stat[i];
	input.close();

	// stat percentges
	float statrate[4];
	// win and lose rate
	if (stat[0] != 0)
	{

		statrate[0] = (float)(stat[4] / (float)stat[0]) * 100;
		statrate[1] = (float)(stat[5] / (float)stat[0]) * 100;
	}
	else {
		statrate[0] = 0;
		statrate[1] = 0;
	}

	// hit and miss rate
	if (stat[1] != 0) {

		statrate[2] = (float)(stat[2] / (float)stat[1]) * 100;
		statrate[3] = (float)(stat[3] / (float)stat[1]) * 100;
	}
	else {
		statrate[2] = 0;
		statrate[3] = 0;

	}

	sf::Font font, fontt;
	font.loadFromFile(gameOptions.theme + "sound.ttf");
	sf::Text rates[6], textt;
	string r[6], stt;
	r[0] = "Total Games:  " + to_string((int)stat[0]);
	r[1] = "Games Won:  " + to_string((int)stat[4]) + " (" + toString(statrate[0]) + "%)";
	r[2] = "Games Lost:  " + to_string((int)stat[5]) + " (" + toString(statrate[1]) + "%)";
	r[3] = "Total Tries:  " + to_string((int)stat[1]);
	r[4] = "Number of hits:  " + to_string((int)stat[2]) + " (" + toString(statrate[2]) + "%)";
	r[5] = "Number of misses:  " + to_string((int)stat[3])+ " (" + toString(statrate[3]) + "%)";





	sf::Sprite backButton;
	sf::Texture backButtonTexture;
	backButtonTexture.loadFromFile(gameOptions.theme + "Options/back.png");
	backButton.setTexture(backButtonTexture);
	backButton.setPosition(sf::Vector2f(0, 0));



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
			sf::Vector2i MosPosition = sf::Mouse::getPosition(window);
			
			if (event.type == sf::Event::MouseButtonReleased&&event.mouseButton.button == sf::Mouse::Left) {
				LeftReleased = true;
			}
			if (event.type == sf::Event::MouseButtonReleased&&event.mouseButton.button == sf::Mouse::Right) {
				RightReleased = true;
			}


		}
		window.clear();
		window.draw(background);
		for (int i = 0; i < 6; i++) {
			rates[i].setFont(font);
			rates[i].setString(r[i]);
			rates[i].setCharacterSize(30);
			rates[i].setPosition(sf::Vector2f(window.getSize().x / 2 - rates[i].getGlobalBounds().width/2, window.getSize().y*0.24 + i * 100));
			rates[i].setFillColor(sf::Color::Color(255, 255, 255));
			window.draw(rates[i]);
		}
		fontt.loadFromFile(gameOptions.theme + "sound.ttf");
		textt.setFont(fontt);
		textt.setString("Statistics");
		textt.setCharacterSize(35);
		textt.setFillColor(sf::Color::Color(255, 255, 255));
		textt.setPosition(sf::Vector2f(window.getSize().x *0.42, window.getSize().y *0.09));

		sf::Vector2i MousePos = sf::Mouse::getPosition();
		if (LeftReleased) {
			if (MousePos.x <= (backButton.getPosition().x + backButtonTexture.getSize().y) &&
				MousePos.y <= (backButton.getPosition().y + backButtonTexture.getSize().x)) {
				cout << "Backpressed" << endl;
				return;
			}
			if (MousePos.x >= window.getSize().x - Exit.getGlobalBounds().width &&
				MousePos.y <= Exit.getGlobalBounds().height) {
				window.close();
			}
		}
		window.draw(backButton);
		window.draw(textt);
		window.draw(Exit);
		window.display();


		LeftReleased = false;
	}
}