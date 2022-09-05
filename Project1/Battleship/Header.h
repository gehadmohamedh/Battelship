#pragma once
#pragma once
#include "Ship.h"
#include "Network.h"
#include "BoardSetup.h"
#include <iostream>
#include <iomanip>
#include <vector>
#include <sstream>
#include"HitMechanism.h"
using namespace std;

pair<int, int> getCoordinatesFromString(string data) {
	stringstream s;
	s << data;
	int x, y;
	s >> x >> y;
	return make_pair(x, y);
}

string coordinatesToString(pair<int, int> p) {
	string ret;
	ret += to_string(p.first);
	ret += " ";
	ret += to_string(p.second);
	return ret;
}

void GamePlay(bool myBoard[10][10], int myBoardHits[10][10], int oppBoardHits[10][10], vector<Ship>& v, sf::TcpSocket& socket, bool firstTurn)
{
	bool myTurn = firstTurn;


	while (true) {
		cout << "myBoard\n";
		int RemainingShips = v.size();
		for (int i = 0; i < 10; i++) {
			for (int j = 0; j < 10; j++) {
				cout << setw(3) << myBoard[j][i] << " ";
			}
			cout << endl;
		}
		cout << "myBoardHits\n";
		for (int i = 0; i < 10; i++) {
			for (int j = 0; j < 10; j++) {
				cout << setw(3) << myBoardHits[j][i] << " ";
			}
			cout << endl;
		}
		cout << "oppBoardHits\n";
		for (int i = 0; i < 10; i++) {
			for (int j = 0; j < 10; j++) {
				cout << setw(3) << oppBoardHits[j][i] << " ";
			}
			cout << endl;
		}
		if (myTurn)
		{
			cout << "Your turn" << endl;
			int x, y;
			string state, result;
			cin >> x >> y;
			while (oppBoardHits[x][y] != -1) {
				cout << "You tried this cell before\n";
				cin >> x >> y;
			}
			send_over_network(socket, coordinatesToString(make_pair(x, y)));
			state = wait_for_data(socket);
			cout << "NETWORK: " << state << endl;
			if (state == "SUCCESS")
			{
				oppBoardHits[x][y] = 1;
				result = wait_for_data(socket);
				cout << "You hit'em!!" << endl;
				cout << "NETWORK: " << result << endl;
				if (result == "WON") {
					cout << "You've Won The Game" << endl;
					return;
				}
			}
			else
			{
				oppBoardHits[x][y] = 0;
				myTurn = false;
			}
		}
		else
		{
			cout << "Opponent Turn" << endl;
			string data = wait_for_data(socket);
			pair <int, int > coordinates = getCoordinatesFromString(data);
			int x = coordinates.first;
			int y = coordinates.second;
			cout << "NETWORK: " << x << " " << y << endl;
			if (myBoard[x][y])
			{
				cout << "You've been hit!" << endl;
				myBoardHits[x][y] = 1;
				send_over_network(socket, "SUCCESS");
				CheckShips(v, myBoardHits, RemainingShips);

				if (RemainingShips == 0)

				{
					send_over_network(socket, "WON");
					cout << "You've been Defeated :(";
					return;
				}
				else
				{
					send_over_network(socket, "Not Yet");
				}
			}
			else {
				myBoardHits[x][y] = 0;
				cout << "You weren't hit" << endl;
				send_over_network(socket, "you missed me");
				myTurn = true;
			}
		}
	}
}
