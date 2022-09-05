#pragma once

#include <SFML/Graphics.hpp>

#include <iostream>
#include <string>
#include<sstream>


#define DELETE 8
#define ESCAPE 13
#define INTER 27
using namespace std;

class Textbox
{
public:
	Textbox() {};
	Textbox(int size, sf::Color color, bool sel)
	{
		textbox.setCharacterSize(size);
		textbox.setFillColor(color);
		isslected = sel;
		if (sel) {
			textbox.setString("|");
		}
		else {
			textbox.setString("");
		}
	}
	void setfont(sf::Font &font)
	{
		textbox.setFont(font);
	}
	void setposition(sf::Vector2f pos)
	{
		textbox.setPosition(pos);
	}
	void setlimit(bool TOF)
	{
		haslimit = TOF;
	}
	void setlimit(bool tof, int lim)
	{
		haslimit = tof;
		limit = lim - 1;

	}
	void setselected(bool sel)
	{
		isslected = sel;
		if (!sel)
		{
			string t = text.str();
			string newT = "";
			for (int i = 0; i < t.length(); i++)
			{
				newT += t[i];
			}
			textbox.setString(newT);
		}
	}
	std::string gettext() {
		return text.str();
	}
	void drawto(sf::RenderWindow &window)
	{
		window.draw(textbox);
	}
	void typeon(sf::Event input)
	{
		if (isslected) {
			int characterType = input.text.unicode;
			if (characterType < 128) {
				if (haslimit) {
					if (text.str().length() <= limit) {
						InputLogic(characterType);
					}
					else if (text.str().length() > limit && characterType == DELETE) {
						deletelastchar();
					}

				}
				else {
					InputLogic(characterType);
				}
			}
		}
	}
	sf::FloatRect getsize() {
		return textbox.getGlobalBounds();
	}
	sf::Vector2f getPosition() {
		return textbox.getPosition();
	}
private:
	sf::Text textbox;
	std::ostringstream text;
	bool isslected = false;
	bool haslimit = false;
	int limit;
	void InputLogic(int characterType)
	{
		if (characterType != DELETE && characterType != ESCAPE && characterType != INTER)
		{
			text << static_cast<char>(characterType);
		}
		else if (characterType == DELETE)
		{
			if (text.str().length() > 0)
			{
				deletelastchar();
			}
		}
		textbox.setString(text.str() + "|");
	}
	void deletelastchar()
	{
		string t = text.str();
		string newT = "";
		for (int i = 0; i < t.length() - 1; i++)
		{
			newT += t[i];
		}
		text.str("");
		text << newT;
		textbox.setString(text.str());
	}
};