#pragma once
#include<SFML/Graphics.hpp>
#include<iostream>
#include<string>
#include "Options.h"
#include "Stats.h";

Options optionsWindow;

Options optionsFunction(sf::RenderWindow &window)
{
	sf::RectangleShape BackGround2(static_cast<sf::Vector2f>(window.getSize()));

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
	sf::Text themes;
	sf::Text statics;
	sf::Vector2f staticspos1;
	sf::Vector2f  statocspos2;


	int fontsize = 40;

	sf::Vector2f  soundPos1;
	sf::Vector2f soundPos2;
	soundoptionOn.loadFromFile("Options/soundbuttonon.png");
	soundfxon.loadFromFile("Options/soundfxon.png");
	invertgridon.loadFromFile("Options/invertgridon.png");

	soundlinkerOn.setTexture(soundoptionOn);
	soundfxlinker.setTexture(soundfxon);
	invertgridlinker.setTexture(invertgridon);



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
		BackGround2.setFillColor(optionsWindow.BackGroundColor);

		window.draw(BackGround2);



		soundoptionOff.loadFromFile("Options/soundbuttonoff.png");
		soundfxoff.loadFromFile("Options/soundfxoff.png");
		invertgridoff.loadFromFile("Options/invertgridoff.png");
		space.loadFromFile("Options/SPACE EDITION.jpg");
		golden.loadFromFile("Options/GOLDENAGE EDITION.jpg");
		back.loadFromFile("Options/back.png");
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
		goldenlinker.setPosition(sf::Vector2f((windowsize.x * 0.60) - goldenpos.x / 2, (windowsize.y*0.70) - goldenpos.y / 2));
		backlinker.setPosition(sf::Vector2f((windowsize.x *0.05) - backpos.x, 0));
		soundword.setFont(soundfont);

		soundword.setCharacterSize(fontsize);
		soundfont.loadFromFile("sound.ttf");
		soundword.setString("Sound");
		soundfxword.setFont(soundfont);
		invertgridword.setFont(soundfont);
		invertgridword.setString("InvertGrid");
		invertgridword.setFillColor(sf::Color::Color::White);
		invertgridword.setCharacterSize(fontsize);
		soundfxword.setCharacterSize(fontsize);
		soundfxword.setString("SoundFX");
		themes.setFont(soundfont);
		themes.setCharacterSize(fontsize);
		themes.setString("Themes");
		statics.setFont(soundfont);
		statics.setFillColor(sf::Color::Color::White);
		statics.setCharacterSize(fontsize);
		statics.setString("Statistics");
		soundfxword.setFillColor(sf::Color::Color::White);
		themes.setFillColor(sf::Color::Color::White);
		soundword.setFillColor(sf::Color::Color::White);
		sf::FloatRect textpixls = soundword.getGlobalBounds();
		sf::FloatRect soundfxsize = soundfxword.getGlobalBounds();
		sf::FloatRect invertsize = invertgridword.getGlobalBounds();
		sf::FloatRect themessize = themes.getGlobalBounds();
		sf::FloatRect staticssize = statics.getGlobalBounds();
		soundword.setPosition(sf::Vector2f((windowsize.x*0.25) - textpixls.width / 2, (windowsize.y* 0.10) - textpixls.height / 2));
		soundfxword.setPosition(sf::Vector2f((windowsize.x*0.25) - soundfxsize.width / 2, (windowsize.y *0.30) - soundfxsize.height / 2));
		invertgridword.setPosition(sf::Vector2f((windowsize.x*0.25) - invertsize.width / 2, (windowsize.y*0.50) - invertsize.height / 2));
		themes.setPosition(sf::Vector2f((windowsize.x * 0.25) - themessize.width / 2, (windowsize.y*0.70) - themessize.height / 2));
		statics.setPosition(sf::Vector2f((windowsize.x*0.25) - staticssize.width / 2, (windowsize.y*0.90) - staticssize.height / 2));

		sf::RectangleShape outlinespace;
		outlinespace.setOutlineThickness(5.0f);
		outlinespace.setSize(static_cast<sf::Vector2f>(space.getSize()));
		outlinespace.setPosition(sf::Vector2f((windowsize.x* 0.80) - spacepos.x / 2, (windowsize.y*0.70) - spacepos.y / 2));

		sf::RectangleShape outlinegolden;
		outlinegolden.setOutlineThickness(5.0f);
		outlinegolden.setSize(static_cast<sf::Vector2f>(golden.getSize()));
		outlinegolden.setPosition(sf::Vector2f((windowsize.x * 0.60) - goldenpos.x / 2, (windowsize.y*0.70) - goldenpos.y / 2));


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
		if (LeftReleased)
		{
			if (Mospos.x >= soundPos1.x && Mospos.y >= soundPos1.y && Mospos.x <= soundPos2.x && Mospos.y <= soundPos2.y)
			{
				cout << "sound\n";
				if (optionsWindow.sound == true)
				{


					optionsWindow.sound = !optionsWindow.sound;
					soundlinkerOn.setTexture(soundoptionOff);



				}
				else if (optionsWindow.sound == false)
				{

					optionsWindow.sound = !optionsWindow.sound;
					soundlinkerOn.setTexture(soundoptionOn);





				}

			}

			else if (Mospos.x >= soundfxPos1.x && Mospos.y >= soundfxPos1.y && Mospos.x <= soundfxPos2.x && Mospos.y <= soundfxPos2.y)
			{
				cout << "soundfx\n";

				if (optionsWindow.soundFX == false)
				{
					optionsWindow.soundFX = !optionsWindow.soundFX;
					soundfxlinker.setTexture(soundfxon);
				}
				else if (optionsWindow.soundFX == true)
				{
					optionsWindow.soundFX = !optionsWindow.soundFX;
					soundfxlinker.setTexture(soundfxoff);
				}
			}

			else if (Mospos.x >= invertgridpos1.x && Mospos.y >= invertgridpos1.y&&Mospos.x <= invertgridpos2.x && Mospos.y <= invertgridpos2.y)
			{
				cout << "invert\n";
				if (optionsWindow.InvertGrid == false)
				{
					optionsWindow.InvertGrid = !optionsWindow.InvertGrid;
					invertgridlinker.setTexture(invertgridon);
				}
				else if (optionsWindow.InvertGrid == true)
				{
					optionsWindow.InvertGrid = !optionsWindow.InvertGrid;
					invertgridlinker.setTexture(invertgridoff);
				}
			}
			else if (Mospos.x >= spacepos1.x && Mospos.y >= spacepos1.y && Mospos.x <= spacepos2.x && Mospos.y <= spacepos2.y)
			{
				optionsWindow.themes = "Ships_Blueprint/";
				optionsWindow.BackGroundColor = sf::Color::Color(29, 42, 104);
			}
			else if (Mospos.x >= goldenpos1.x && Mospos.y >= goldenpos1.y && Mospos.x <= goldenpos2.x&& Mospos.y <= goldenpos2.y)
			{
				optionsWindow.themes = "Ships_Goldenage/";
				optionsWindow.BackGroundColor = sf::Color::Color(237, 186, 0);

			}
			else if (Mospos.x >= staticspos1.x && Mospos.y >= staticspos1.y && Mospos.x <= statocspos2.x && Mospos.y <= statocspos2.y)
			{
				cout << "heeheh\n";
				statistics(window);

			}

			else if (Mospos.x >= backpos1.x && Mospos.y >= backpos1.y && Mospos.x <= backpos2.x &&Mospos.y <= backpos2.y)
			{

				return optionsWindow;
			}

		}

		if (optionsWindow.themes == "Ships_Blueprint/")
		{
			outlinespace.setOutlineColor(sf::Color::Color::White);
			outlinegolden.setOutlineColor(sf::Color::Color(29, 42, 104));
		}
		else
		{
			outlinegolden.setOutlineColor(sf::Color::Color::White);
			outlinespace.setOutlineColor(sf::Color::Color(29, 42, 104));
		}
		window.draw(statics);
		window.draw(backlinker);
		window.draw(outlinegolden);
		window.draw(outlinespace);
		window.draw(themes);
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
	system("pause");
}
