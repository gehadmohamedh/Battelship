#pragma once



/// a Ship class holding it's position id length and orientation.

class Ship
{
public:
	int id;
	int x, y;
	char orientation;	 // orientation of the ship V for vertical or H for horizontal.
	int length;			 // size of the ship
	bool destroyed;		 // is the ship currently destroyed. A ship is destroyed if all it's cells have been hit.
	bool placed = 0;
	//default constructor !!DO NOT USE!!
	Ship() {
		x = 0;
		y = 0;
		id = 0;
		orientation = 'V';
		length = 1;
		destroyed = false;
	}

	//constructor used to initialize the Ship.
	Ship(int l, char o, int x_, int y_, int id_) {
		length = l;
		x = x_;
		y = y_;
		orientation = o;
		id = id_;
		destroyed = false;
	}

};


