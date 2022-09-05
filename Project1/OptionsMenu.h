#pragma once
#include<SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include<iostream>
#include<string>
#include "Options.h"
#include "Stats.h";



void optionsFunction(sf::RenderWindow &window, Options &gameOptions, sf::Music& sound) {
	///Options Menu modifies the gameOptions variable according to the user's ineractions.
	sf::Sprite Exit;
	sf::Texture ExitButton;
	ExitButton.loadFromFile(gameOptions.theme + "exit.png");
	Exit.setTexture(ExitButton);
	Exit.setOrigin(ExitButton.getSize().x, 0.0f);
	Exit.setPosition(window.getSize().x, 0.0f);

	sf::Sprite background;
	sf::Texture bgTexture;
	bgTexture.loadFromFile(gameOptions.backgroundImage);
	background.setTexture(bgTexture);
	background.setScale(sf::Vector2f(window.getSize().x / background.getGlobalBounds().width, window.getSize().y / background.getGlobalBounds().height));


	sf::Vector2u windowsize = window.getSize();
	bool LeftReleased = false;
	bool RightReleased = false;

	sf::Texture back;
	sf::Sprite  backlinker;
	sf::Vector2f backpos1;
	sf::Vector2f backpos2;
	sf::Texture soundoptionOn;
	sf::Sprite  soundlinkerOn;

	sf::Texture  soundoptionOff;

	sf::Texture soundfxon;
	sf::Texture soundfxoff;
	sf::Sprite soundfxlinker;
	sf::Vector2f soundfxPos1;
	sf::Vector2f soundfxPos2;

	sf::Texture invertgridon;
	sf::Texture invertgridoff;
	sf::Sprite invertgridlinker;
	sf::Vector2f invertgridpos1;
	sf::Vector2f invertgridpos2;

	sf::Texture space;
	sf::Sprite  spacelinker;
	sf::Vector2f spacepos1;
	sf::Vector2f spacepos2;

	sf::Texture golden;
	sf::Sprite goldenlinker;
	sf::Vector2f goldenpos1;
	sf::Vector2f goldenpos2;

	sf::Text soundword;
	sf::Font soundfont;
	sf::Text soundfxword;
	sf::Text invertgridword;
	sf::Text theme;
	sf::Text statics;
	sf::Vector2f staticspos1;
	sf::Vector2f  statocspos2;


	int fontsize = 40;

	sf::Vector2f  soundPos1;
	sf::Vector2f soundPos2;
	soundoptionOn.loadFromFile(gameOptions.theme + "Options/soundbuttonon.png");
	soundoptionOff.loadFromFile(gameOptions.theme + "Options/soundbuttonoff.png");
	soundfxon.loadFromFile(gameOptions.theme + "Options/soundfxon.png");
	soundfxoff.loadFromFile(gameOptions.theme + "Options/soundfxoff.png");
	invertgridon.loadFromFile(gameOptions.theme + "Options/invertgridon.png");
	invertgridoff.loadFromFile(gameOptions.theme + "Options/invertgridoff.png");
	if (gameOptions.sound) {
		soundlinkerOn.setTexture(soundoptionOn);
	}
	else {
		soundlinkerOn.setTexture(soundoptionOff);
	}
	if (gameOptions.InvertGrid) {
		invertgridlinker.setTexture(invertgridon);
	}
	else {
		invertgridlinker.setTexture(invertgridoff);
	}
	if (gameOptions.soundFX) {
		soundfxlinker.setTexture(soundfxon);
	}
	else {
		soundfxlinker.setTexture(soundfxoff);
	}



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

		window.draw(background);




		space.loadFromFile(gameOptions.theme + "Options/SPACE EDITION.jpg");
		golden.loadFromFile(gameOptions.theme + "Options/GOLDENAGE EDITION.jpg");
		back.loadFromFile(gameOptions.theme + "Options/back.png");
		goldenlinker.setTexture(golden);
		spacelinker.setTexture(space);
		backlinker.setTexture(back);
		sf::Vector2u invgridpos = invertgridon.getSize();
		sf::Vector2u soundfxPos = soundfxon.getSize();
		sf::Vector2u soundbuttonsize = soundoptionOn.getSize();
		sf::Vector2u spacepos = space.getSize();
		sf::Vector2u goldenpos = golden.getSize();
		sf::Vector2u backpos = back.getSize();
		soundlinkerOn.setPosition(sf::Vector2f((windowsize.x * 0.75) - soundbuttonsize.x / 2, (windowsize.y * 0.10) - soundbuttonsize.y / 2));
		soundfxlinker.setPosition(sf::Vector2f((windowsize.x*0.75) - soundfxPos.x / 2, (windowsize.y*0.30) - soundfxPos.y / 2));
		invertgridlinker.setPosition(sf::Vector2f((windowsize.x *0.75) - invgridpos.x / 2, (windowsize.y* 0.50) - invgridpos.y / 2));
		spacelinker.setPosition(sf::Vector2f((windowsize.x* 0.80) - spacepos.x / 2, (windowsize.y*0.70) - spacepos.y / 2));
		goldenlinker.setPosition(sf::Vector2f((windowsize.x * 0.50) - goldenpos.x / 2, (windowsize.y*0.70) - goldenpos.y / 2));
		backlinker.setPosition(sf::Vector2f(0, 0));
		soundword.setFont(soundfont);

		soundword.setCharacterSize(fontsize);
		soundfont.loadFromFile(gameOptions.theme + "sound.ttf");
		soundword.setString("Sound");
		soundfxword.setFont(soundfont);
		invertgridword.setFont(soundfont);
		invertgridword.setString("InvertGrid");
		invertgridword.setFillColor(gameOptions.textColor);
		invertgridword.setCharacterSize(fontsize);
		soundfxword.setCharacterSize(fontsize);
		soundfxword.setString("SoundFX");
		theme.setFont(soundfont);
		theme.setCharacterSize(fontsize);
		theme.setString("theme");
		statics.setFont(soundfont);
		statics.setFillColor(gameOptions.textColor);
		statics.setCharacterSize(fontsize);
		statics.setString("Statistics");
		soundfxword.setFillColor(gameOptions.textColor);
		theme.setFillColor(gameOptions.textColor);
		soundword.setFillColor(gameOptions.textColor);
		sf::FloatRect textpixls = soundword.getGlobalBounds();
		sf::FloatRect soundfxsize = soundfxword.getGlobalBounds();
		sf::FloatRect invertsize = invertgridword.getGlobalBounds();
		sf::FloatRect themesize = theme.getGlobalBounds();
		sf::FloatRect staticssize = statics.getGlobalBounds();
		soundword.setPosition(sf::Vector2f((windowsize.x*0.25) - textpixls.width / 2, (windowsize.y* 0.10) - textpixls.height / 2));
		soundfxword.setPosition(sf::Vector2f((windowsize.x*0.25) - soundfxsize.width / 2, (windowsize.y *0.30) - soundfxsize.height / 2));
		invertgridword.setPosition(sf::Vector2f((windowsize.x*0.25) - invertsize.width / 2, (windowsize.y*0.50) - invertsize.height / 2));
		theme.setPosition(sf::Vector2f((windowsize.x * 0.25) - themesize.width / 2, (windowsize.y*0.70) - themesize.height / 2));
		statics.setPosition(sf::Vector2f((windowsize.x*0.25) - staticssize.width / 2, (windowsize.y*0.90) - staticssize.height / 2));

		sf::RectangleShape outlinespace;
		outlinespace.setOutlineThickness(5.0f);
		outlinespace.setSize(static_cast<sf::Vector2f>(space.getSize()));
		outlinespace.setPosition(spacelinker.getPosition());

		sf::RectangleShape outlinegolden;
		outlinegolden.setOutlineThickness(5.0f);
		outlinegolden.setSize(static_cast<sf::Vector2f>(golden.getSize()));
		outlinegolden.setPosition(goldenlinker.getPosition());


		soundfxPos1 = soundfxlinker.getPosition();
		soundfxPos2.x = soundfxPos1.x + soundfxon.getSize().x;
		soundfxPos2.y = soundfxPos1.y + soundfxon.getSize().y;

		invertgridpos1 = invertgridlinker.getPosition();
		invertgridpos2.x = invertgridpos1.x + invertgridon.getSize().x;
		invertgridpos2.y = invertgridpos1.y + invertgridon.getSize().y;

		soundPos1 = soundlinkerOn.getPosition();
		soundPos2.x = soundPos1.x + soundoptionOn.getSize().x;
		soundPos2.y = soundPos1.y + soundoptionOn.getSize().y;

		spacepos1 = spacelinker.getPosition();
		spacepos2.x = spacepos1.x + space.getSize().x;
		spacepos2.y = spacepos1.y + space.getSize().y;

		goldenpos1 = goldenlinker.getPosition();
		goldenpos2.y = goldenpos1.y + golden.getSize().y;
		goldenpos2.x = goldenpos1.x + golden.getSize().x;

		backpos1 = backlinker.getPosition();
		backpos2.x = backpos1.x + back.getSize().x;
		backpos2.y = backpos1.y + back.getSize().y;

		staticspos1 = statics.getPosition();
		statocspos2.x = staticspos1.x + statics.getGlobalBounds().width;
		statocspos2.y = staticspos1.y + statics.getGlobalBounds().height;


		sf::Vector2i Mospos = sf::Mouse::getPosition(window);
		if (Mospos.x > window.getSize().x - ExitButton.getSize().x && Mospos.y < ExitButton.getSize().y && LeftReleased) { window.close(); }
		if (LeftReleased)
		{
			if (Mospos.x >= soundPos1.x && Mospos.y >= soundPos1.y && Mospos.x <= soundPos2.x && Mospos.y <= soundPos2.y)
			{
				cout << "sound\n";
				if (gameOptions.sound == true)
				{


					gameOptions.sound = !gameOptions.sound;
					soundlinkerOn.setTexture(soundoptionOff);



				}
				else if (gameOptions.sound == false)
				{

					gameOptions.sound = !gameOptions.sound;
					soundlinkerOn.setTexture(soundoptionOn);
				}

			}

			else if (Mospos.x >= soundfxPos1.x && Mospos.y >= soundfxPos1.y && Mospos.x <= soundfxPos2.x && Mospos.y <= soundfxPos2.y)
			{
				cout << "soundfx\n";

				if (gameOptions.soundFX == false)
				{
					gameOptions.soundFX = !gameOptions.soundFX;
					soundfxlinker.setTexture(soundfxon);
				}
				else if (gameOptions.soundFX == true)
				{
					gameOptions.soundFX = !gameOptions.soundFX;
					soundfxlinker.setTexture(soundfxoff);
				}
			}

			else if (Mospos.x >= invertgridpos1.x && Mospos.y >= invertgridpos1.y&&Mospos.x <= invertgridpos2.x && Mospos.y <= invertgridpos2.y)
			{
				cout << "invert\n";
				if (gameOptions.InvertGrid == false)
				{
					gameOptions.InvertGrid = !gameOptions.InvertGrid;
					invertgridlinker.setTexture(invertgridon);
				}
				else if (gameOptions.InvertGrid == true)
				{
					gameOptions.InvertGrid = !gameOptions.InvertGrid;
					invertgridlinker.setTexture(invertgridoff);
				}
			}
			else if (Mospos.x >= spacepos1.x && Mospos.y >= spacepos1.y && Mospos.x <= spacepos2.x && Mospos.y <= spacepos2.y)
			{
				gameOptions.theme = "Ships_Blueprint/";
				gameOptions.backgroundImage = gameOptions.theme + "background.jpg";
				bgTexture.loadFromFile(gameOptions.backgroundImage);
				background.setTexture(bgTexture);
				gameOptions.textColor = sf::Color::White;
				gameOptions.musicFile = "Sounds/blueprint.wav";
				sound.stop();
				sound.openFromFile(gameOptions.musicFile);
				if (gameOptions.sound)
					sound.play();
			}
			else if (Mospos.x >= goldenpos1.x && Mospos.y >= goldenpos1.y && Mospos.x <= goldenpos2.x&& Mospos.y <= goldenpos2.y)
			{
				gameOptions.theme = "Ships_Goldenage/";
				gameOptions.backgroundImage = gameOptions.theme + "background.jpg";
				bgTexture.loadFromFile(gameOptions.backgroundImage);
				background.setTexture(bgTexture);
				gameOptions.textColor = sf::Color::Color(237, 186, 0);
				gameOptions.musicFile = "Sounds/goldenage.wav";
				sound.stop();
				sound.openFromFile(gameOptions.musicFile);
				if (gameOptions.sound)
					sound.play();

			}
			else if (Mospos.x >= staticspos1.x && Mospos.y >= staticspos1.y && Mospos.x <= statocspos2.x && Mospos.y <= statocspos2.y)
			{
				cout << "heeheh\n";
				statistics(gameOptions, window);

			}

			else if (Mospos.x >= backpos1.x && Mospos.y >= backpos1.y && Mospos.x <= backpos2.x &&Mospos.y <= backpos2.y)
			{

				return;
			}

		}

		if (gameOptions.theme == "Ships_Blueprint/")
		{
			outlinespace.setOutlineColor(gameOptions.textColor);
			outlinegolden.setOutlineColor(sf::Color::Transparent);
		}
		else
		{
			outlinegolden.setOutlineColor(gameOptions.textColor);
			outlinespace.setOutlineColor(sf::Color::Transparent);
		}
		window.draw(Exit);
		window.draw(statics);
		window.draw(backlinker);
		window.draw(outlinegolden);
		window.draw(outlinespace);
		window.draw(theme);
		window.draw(goldenlinker);
		window.draw(spacelinker);
		window.draw(invertgridword);
		window.draw(invertgridlinker);
		window.draw(soundfxword);
		window.draw(soundfxlinker);
		window.draw(soundword);
		window.draw(soundlinkerOn);
		window.display();
		LeftReleased = false;
		RightReleased = false;
	}
}
