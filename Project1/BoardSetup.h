#pragma once
#include "Ship.h"
#include <vector>

using namespace std;
bool Occupied(int length, char orientation, int x, int y, bool board[10][10]);



int RemoveShip(Ship s, bool board[10][10]) {
	/// removes a ship at a certain point

	if (!Occupied(s.length, s.orientation, s.x, s.y, board)) {
		return -1;
	}
	if (s.orientation == 'H') {
		for (int i = s.x; i < s.length + s.x; i++) {
			board[i][s.y] = 0;
		}
	}
	if (s.orientation == 'V') {
		for (int j = s.y; j < s.length + s.y; j++) {
			board[s.x][j] = 0;
		}
	}
	return 0;
}



bool Occupied(int length, char orientation, int x, int y, bool board[10][10]) {
	/// A function that checks if a place on the board is free for a ship to be placed

	if (board[x][y]) {
		return 1;
	}

	if (orientation == 'H') {
		if (length + x > 10) {
			return 1;
		}

		for (int i = x; i < length + x; i++) {
			if (board[i][y]) {
				return 1;
			}
		}
	}

	if (orientation == 'V') {
		if (length + y > 10) {
			return 1;
		}

		for (int j = y; j < length + y; j++) {
			if (board[x][j]) {
				return 1;
			}
		}
	}
	return 0;
}



int PlaceShip(Ship s, bool board[10][10]) {
	/// A function that places a ship in a certain place if it's free. returns 0 if successful otherwise -1

	int length = s.length, x = s.x, y = s.y;
	char orientation = s.orientation;
	if (Occupied(length, orientation, x, y, board)) {
		return -1;
	}
	if (orientation == 'H') {
		for (int i = x; i < length + x; i++) {
			board[i][y] = 1;
		}
	}
	if (orientation == 'V') {
		for (int j = y; j < length + y; j++) {
			board[x][j] = 1;
		}
	}
	return 0;
}


int ChangeOrientation(Ship& s , bool board [10][10]) {
	///A function that changes the orientation of a ship
	RemoveShip(s, board);

	if (s.orientation == 'H')
		s.orientation = 'V';
	else
		s.orientation = 'H';

	int check = PlaceShip(s, board);
	if (check == 0)
		return 0;
	else
	{
		if (s.orientation == 'H') {
			s.orientation = 'V';
		}
		else
			s.orientation = 'H';
		PlaceShip(s, board);
		return -1;
	}
}
