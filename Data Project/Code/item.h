#ifndef ITEM_H
#define ITEM_H

#include <iostream>
#include <string>
using namespace std;

#include "avlTree.h"
#include "maze.h";


class Item {
public:
	Sprite item;
	Texture itText;
	int value;
	string name;
	string type;
	int defence;
	int attack;
	Item(int v=0, string n="", string t="", int a=0, int d=0) : value(v), name(n), type(t), attack(a), defence(d) {}

	Item(Item& o) : value(o.value), name(o.name), type(o.type) {
		item = o.item;
		itText = o.itText;
	}

	virtual bool operator>(Item& other) = 0;

	virtual void print(ostream& o) {}

	friend ostream& operator<<(ostream& o,Item& item) {
		item.print(o);
	}
	virtual bool operator<(Item& other) = 0;
	virtual bool operator==(Item& other) = 0;

};


class Weapon : public Item {
public:
	int damage;

	Weapon(int v, string n, int d) : Item(v, n, "Weapon",d,0) {
		if (n == "Sword") {
			itText.loadFromFile("img/Treasury/sword.png");
			item.setTexture(itText);
			item.setScale(0.2, 0.15);
		}
		else if (n == "Dreamweaver Sword") {
			itText.loadFromFile("img/Treasury/dreamweaversword.png");
			item.setTexture(itText);
			item.setScale(0.3, 0.3);
		}
		else if (n == "Fire Dagger") {
			itText.loadFromFile("img/Treasury/firedagger.png");
			item.setTexture(itText);
			item.setScale(0.3, 0.3);
		}
			
	
	
	}

	bool operator>(Item& other) override{
		if (value > other.value)
			return true;
		return false;
	}
	bool operator<(Item& other) override {
		if (value < other.value)
			return true;
		return false;
	}

	void print(ostream& o) override {
		o << "\nName: " << name << "Value: " << value << "\nType: " << type<<"\n Damage: "<<damage<<"\n";
	}

	bool operator==(Item& other) override {
		if (name == other.name)
			return true;
		return false;
	}

};

class Armour : public Item {
public:
	Armour(int v, string n, int d) : Item(v, n, "Armour",0,d) {
		if (n == "Shield") {
			itText.loadFromFile("img/Treasury/shield.png");
			item.setTexture(itText);
			item.setScale(0.2, 0.2);
		}
		else if (n == "Gauntlets of Old Gods") {
			itText.loadFromFile("img/Treasury/gauntletsofoldgod.png");
			item.setTexture(itText);
			item.setScale(0.3, 0.3);
		}
		else if (n == "Hellmail") {
			itText.loadFromFile("img/Treasury/hellmail.png");
			item.setTexture(itText);
			item.setScale(0.3, 0.3);
		}
	
	}
	bool operator>(Item& other) override {
		if (value > other.value)
			return true;
		return false;
	}

	void print(ostream& o) override {
		o << "\nName: " << name << "Value: " << value << "\nType: " << type << "\n Defence: " << defence << "\n";
	}

	bool operator==(Item& other) override {
		if (name == other.name)
			return true;
		return false;
	}

	bool operator<(Item& other) override {
		if (value < other.value)
			return true;
		return false;
	}

};

class Treasure : public Item {
public:

	Treasure(int v, string n) : Item(v, n, "Treasure") {
		if (n == "Gold Chest") {
			itText.loadFromFile("img/Treasury/goldchest.png");
			item.setTexture(itText);
			item.setScale(0.15, 0.15);
		}		
		else if (n == "Sun Amulet") {
			itText.loadFromFile("img/Treasury/sunamulet.png");
			item.setTexture(itText);
			item.setScale(0.4, 0.4);
		}		
		else if (n == "Amulet of Mara") {
			itText.loadFromFile("img/Treasury/amuletofmara.png");
			item.setTexture(itText);
			item.setScale(0.3, 0.3);
		}		
		else if (n == "Ethereal Embers") {
			itText.loadFromFile("img/Treasury/etherealembers.png");
			item.setTexture(itText);
			item.setScale(0.4, 0.4);
		}
		else if (n == "Glimmering Goblet") {
			itText.loadFromFile("img/Treasury/glimeringgoblet.png");
			item.setTexture(itText);
			item.setScale(0.3, 0.3);
		}
		else if (n == "Dreamweaver Crystal") {
			itText.loadFromFile("img/Treasury/dreamweavercrystal.png");
			item.setTexture(itText);
			item.setScale(0.3, 0.3);
		}
	}

	bool operator>(Item& other) override {
		if (value > other.value)
			return true;
		return false;
	}

	void print(ostream& o) override {
		o << "\nName: " << name << "Value: " << value << "\nType: " << type << "\n";
	}

	bool operator==(Item& other) override {
		if (name == other.name)
			return true;
		return false;
	}
	bool operator<(Item& other) override {
		if (value < other.value)
			return true;
		return false;
	}

};


class Potion : public Item {
public:
	Potion(int v, string n) : Item(v, n, "Potion") {
		itText.loadFromFile("img/Treasury/healingpotion.png");
		item.setTexture(itText);
		item.setScale(0.3, 0.3);
	}


	bool operator>(Item& other) override {
		if (value > other.value)
			return true;
		return false;
	}

	void print(ostream& o) override {
		o << "\nName: " << name << "Value: " << value << "\nType: " << type << "\n";
	}

	bool operator==(Item& other) override {
		if (name == other.name)
			return true;
		return false;
	}
	bool operator<(Item& other) override {
		if (value < other.value)
			return true;
		return false;
	}
};

class Key : public Item {
public:
	Key(int v = 30, string n = "Key") : Item(v, n, "Key") {
		itText.loadFromFile("img/key.png");
		item.setTexture(itText);
		item.setScale(0.3, 0.3);
	}

	bool operator>(Item& other) override {
		if (value > other.value)
			return true;
		return false;
	}

	void print(ostream& o) override {
		o << "\nName: " << name << "Value: " << value << "\nType: " << type << "\n";
	}

	bool operator==(Item& other) override {
		if (name == other.name)
			return true;
		return false;
	}
	bool operator<(Item& other) override {
		if (value < other.value)
			return true;
		return false;
	}




};



Item** intializeItems(int round, Cell* maze, RenderWindow& window) {
	Item** items;
	items = new Item * [7];

	//6 items per map;

	//1 weapon
	//1 armour
	//1 potion
	//3 treasures
	// 1 key
	if (round == 1) {
		items[0] = new Weapon(20, "Sword", 20);
		items[1] = new Armour(10, "Shield", 20);
		items[2] = new Potion(5, "Healing Potion");
		items[3] = new Treasure(40, "Gold Chest");
		items[4] = new Treasure(30, "Gold Chest");
		items[5] = new Treasure(50, "Sun Amulet");

	}
	if (round == 2) {
		items[0] = new Weapon(20, "Sword", 30);
		items[1] = new Armour(10, "Shield", 20);
		items[2] = new Potion(5, "Healing Potion");
		items[3] = new Treasure(30, "Gold Chest");
		items[4] = new Treasure(40, "Gold Chest");
		items[5] = new Treasure(50, "Amulet of Mara");
	}
	if (round == 3) {
		items[0] = new Weapon(50, "Fire Dagger", 50);
		items[1] = new Armour(10, "Shield", 20);
		items[2] = new Potion(5, "Healing Potion");
		items[3] = new Treasure(30, "Gold Chest");
		items[4] = new Treasure(40, "Gold Chest");
		items[5] = new Treasure(70, "Ethereal Embers");
	}
	if (round == 4) {
		items[0] = new Weapon(20, "Sword", 20);
		items[1] = new Armour(10, "Gauntlets of Old Gods", 50);
		items[2] = new Potion(5, "Healing Potion");
		items[3] = new Treasure(50, "Gold Chest");
		items[4] = new Treasure(60, "Gold Chest");
		items[5] = new Treasure(70, "Glimmering Goblet");
	}
	if (round == 5) {
		items[0] = new Weapon(60, "Dreamweaver Sword", 60);
		items[1] = new Armour(50, "Hellmail ", 60);
		items[2] = new Potion(5, "Healing Potion");
		items[3] = new Treasure(80, "Gold Chest");
		items[4] = new Treasure(90, "Gold Chest");
		items[5] = new Treasure(100, "Dreamweaver Crystal");
	}
	items[6] = new Key;

	//place at random
	int* random = new int[6];
	int a = 0;
	random[a] = 0;
	for (int i = 0; i < 7; i++) {
		while (random[a] < 30) {
			random[a] = rand() % (SIZE * SIZE);
			for (int k = 0; k < a; k++)
				if (random[a] == random[k])
					random[a] = 0;
		}
		
		items[i]->item.setPosition(maze[random[a]].x, maze[random[a]].y);
		a++;
	}

	return items;
}



#endif // ITEM_H