#ifndef PLAYER_H
#define PLAYER_H


#include "maze.h"
#include "avlTree.h"
#include "item.h"
using namespace sf;
using namespace std;

class Player {
public:
	Sprite sprite;
	Texture playText;
    AVLTree inventory;
	int health;
    int attack;
	int total_defence;
	int XP;
    string str;
    bool key;

	Player(int h, int def,int a, int xp) : health(h), total_defence(def), attack(a), XP(xp) {
		playText.loadFromFile("img/knight.png");
		sprite.setTexture(playText);
		sprite.setScale(0.1f, 0.1f);
		sprite.setPosition(0, 0);
        str = "";
        key = false;
	}


    void handleMove(sf::Event event, Cell* maze, int* currentPos, int size) {
        if (
            event.key.code == sf::Keyboard::Left ||
            event.key.code == sf::Keyboard::A
            ) {
            if (!maze[*currentPos].walls[3] && !maze[*currentPos - 1].walls[1]) {
                *currentPos = *currentPos - 1;
                maze[*currentPos].isActive = true;

            }
        }
        else if (
            event.key.code == sf::Keyboard::Right ||
            event.key.code == sf::Keyboard::D
            ) {
            if (!maze[*currentPos].walls[1] && !maze[*currentPos + 1].walls[3]) {
                *currentPos = *currentPos + 1;
                maze[*currentPos].isActive = true;
            }
        }
        else if (
            event.key.code == sf::Keyboard::Up ||
            event.key.code == sf::Keyboard::W
            ) {
            if ((*currentPos - size) < 0) {
                return;
            }
            if (!maze[*currentPos].walls[0] && !maze[*currentPos - size].walls[2]) {
                *currentPos = *currentPos - size;
                maze[*currentPos].isActive = true;
            }
        }
        else if (
            event.key.code == sf::Keyboard::Down ||
            event.key.code == sf::Keyboard::S
            ) {
            if ((*currentPos + size) > size * size) {
                return;
            }
            if (!maze[*currentPos].walls[2] && !maze[*currentPos + size].walls[0]) {
                *currentPos = *currentPos + size;
                maze[*currentPos].isActive = true;
            }
        }
    }

    bool checkEnemyCollision(Sprite en) {
        if (sprite.getGlobalBounds().intersects(sf::FloatRect(static_cast<float>(en.getPosition().x), static_cast<float>(en.getPosition().y), 1, 1))) {
            return true;
        }
        return false;
        
    }

    bool checkItemCollision(Item* items) {
        if (sprite.getGlobalBounds().intersects(sf::FloatRect(static_cast<float>(items->item.getPosition().x), static_cast<float>(items->item.getPosition().y), 1, 1))) {
            return true;
        }
        return false;
    }

    void addToInventory(Item* item) {
        XP += item->value;
        if(item->type!="Potion" && item->type!="Key")
            inventory.insert(item);
        item->item.setPosition(-100, -100);

        if (item->type == "Weapon") {
            attack += (item->attack / 2);
        }
        if (item->type == "Armour") {
            total_defence += item->defence;
        }
        if (item->type == "Potion") {
            if (health < 100) {
                health = 100;
            }
            else
                health += 10;
        }
        if (item->type == "Key") {
            key = true;
        }
    }

    void displayInventory(RenderWindow& window) {
        str = "Inventory:\n";
        inventory.inorderTraversal(str);
        Text inv;
        Font font;
        font.loadFromFile("img/combatfont.ttf");
        inv.setFont(font);
        inv.setCharacterSize(20);
        inv.setFillColor(Color::White);
        inv.setPosition(CELL_WIDTH * SIZE + 70, 400);
        inv.setString(str);

        window.draw(inv);
    }


};


#endif // PLAYER_H