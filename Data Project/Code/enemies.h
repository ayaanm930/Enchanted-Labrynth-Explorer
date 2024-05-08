#ifndef ENEMIES_H
#define ENEMIES_H

class Enemy {
public:
    int health;
    Sprite ensprite;
    Texture entext;
    int value;
    int attack;
    string name;

    Enemy(int h = 100, int val = 30, int a = 30, string n = "") : health(h), value(val), attack(a), name(n) {}

    virtual void  initialiseEnemy(Cell* maze) {}
    virtual void enemyMovement(Cell* maze, int* currentPos, int size) {}

};

class Tree : public Enemy {
public:

    Tree() : Enemy(100, 20, 20,"Cursed Tree") {
        entext.loadFromFile("img/tree.png");
        ensprite.setTexture(entext);
        ensprite.setScale(0.35, 0.35);
    }

};

class Minotaur : public Enemy {
public:

    Minotaur() : Enemy(100, 30, 40, "Minotaur") {
        entext.loadFromFile("img/minotaur.png");
        ensprite.setTexture(entext);
        ensprite.setScale(0.3, 0.3);
    }
};

#endif // ENEMIES_H