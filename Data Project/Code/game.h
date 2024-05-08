#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <time.h>
#include <iostream>
#include<fstream>
#include <sstream>
using namespace std;
const char title[] = "DATA STRUCTURES PROJ";
using namespace sf;
#include "maze.h"
#include"avlTree.h"
#include "item.h"
#include "enemies.h"
#include"player.h"
#include "combat.h"
#include"menu.h"



class Game
{
public:
    
    // add other game attributes
    //Player and everything 
    Player* player;
    Enemy*** enemies;
    Combat combat;
    Cell* maze;
    Text roundtxt;
    Text healthtxt;
    Text XPtxt;
    Text defencetxt;
    Text attacktxt;
    Font font;

    bool reset;
    int round;
    AVLTree ItemsInMaze;
    Item** items;

    Item* key;

    SoundBuffer buffer;
    Sound sound;
   
    

    Game()
    {
        key = new Key;
        player = new Player(100, 20,20, 10);
        enemies = new Enemy * *[2];
        round = 5;
        // Allocate memory for each row
        for (int i = 0; i < 3; ++i) {
            enemies[i] = new Enemy * [2];
        }

        enemies[0][0] = new Tree;
        enemies[1][0] = new Tree;
        enemies[0][1] = new Minotaur;
        enemies[1][1] = new Minotaur;
        reset = true;


        buffer.loadFromFile("img/sounds/cresent-hell-escalate-3-11647.mp3");
        sound.setBuffer(buffer);
    }

    void updateText() {
        string str;
        str = "Round: ";
        str += to_string(round);
        str += " of 5";
        font.loadFromFile("img/combatfont.ttf");
        roundtxt.setFont(font);
        roundtxt.setCharacterSize(30);
        roundtxt.setString(str);
        roundtxt.setFillColor(Color::White);
        roundtxt.setPosition(CELL_WIDTH * SIZE + 70, 20); 
        
        str = "Health: ";
        str += to_string(player->health);
        str += "%";
        healthtxt.setFont(font);
        healthtxt.setCharacterSize(30);
        healthtxt.setString(str);
        healthtxt.setFillColor(Color::White);
        healthtxt.setPosition(CELL_WIDTH * SIZE + 70, 70);

        str = "XP: ";
        str += to_string(player->XP);
        XPtxt.setFont(font);
        XPtxt.setCharacterSize(30);
        XPtxt.setString(str);
        XPtxt.setFillColor(Color::White);
        XPtxt.setPosition(CELL_WIDTH * SIZE + 70, 120);

        str = "Defence: ";
        str += to_string(player->total_defence);
        defencetxt.setFont(font);
        defencetxt.setCharacterSize(30);
        defencetxt.setString(str);
        defencetxt.setFillColor(Color::White);
        defencetxt.setPosition(CELL_WIDTH * SIZE + 70,170);

        
        str = "Attack: ";
        str += to_string(player->attack);
        attacktxt.setFont(font);
        attacktxt.setCharacterSize(30);
        attacktxt.setString(str);
        attacktxt.setFillColor(Color::White);
        attacktxt.setPosition(CELL_WIDTH * SIZE + 70,220);
        
    }



    int start_game(int argc, char* argv[], string playername)
    {
        srand(time(0));
        int currentPos = 0;
       // AVLTree<int> treasureTree;
        sf::RenderWindow window(sf::VideoMode(CELL_WIDTH * SIZE + 360, CELL_WIDTH * SIZE + 60), "maze");

        // Load the background image
        sf::Texture backgroundTexture;
        if (!backgroundTexture.loadFromFile("img/gamebg.jpg")) {
            cout << "Failed to load the background image." << endl;
            // Handle the error
        }

        // Create a sprite for the background
        sf::Sprite backgroundSprite(backgroundTexture);
        backgroundSprite.setScale(
            static_cast<float>(window.getSize().x) / backgroundTexture.getSize().x,
            0.5
        );

        Sprite door;
        Texture doorOpen;
        Texture doorClose;
        doorOpen.loadFromFile("img/portal(open).png");
        doorClose.loadFromFile("img/portal(close).png");

        door.setPosition(CELL_WIDTH * SIZE-30, CELL_WIDTH * SIZE-30);
        door.setScale(0.3, 0.3);
        door.setTexture(doorClose);


        sf::RectangleShape box(sf::Vector2f(350, CELL_WIDTH * SIZE + 60));
        box.setPosition(CELL_WIDTH * SIZE+60,0);
        box.setFillColor(Color::Black);

        maze = new Cell[SIZE * SIZE];
        window.setFramerateLimit(30);
        window.setVerticalSyncEnabled(true);

        for (int i = 30, k = 0; i < CELL_WIDTH * SIZE + 30; i += CELL_WIDTH) {
            for (int j = 30; j < CELL_WIDTH * SIZE + 30; j += CELL_WIDTH, k++) {
                maze[k].y = i;
                maze[k].x = j;
                maze[k].size = CELL_WIDTH;
                maze[k].pos = k;
            }
        }
        /////////////////////////avl///////////
       // makeMaze(maze, SIZE, treasureTree);
        /////////////////////////////////////
        makeMaze(maze, SIZE);
        maze[currentPos].isActive = true;
        int randomIndex[4] = { 0 };
        srand(time(0));
        if (reset) { //intialize postion

            //avl tree integration

            
            items = intializeItems(round, maze, window);
            for (int i = 0; i < 7; i++) {
                ItemsInMaze.insert(items[i]);
            }


            int a = 0;
            for (int j = 0; j < 2; j++) {
                for (int i = 0; i < 2; i++) {
                    randomIndex[a] = 0;
                    while (randomIndex[a]<30) {
                        randomIndex[a] = rand() % (SIZE * SIZE);
                        for (int k = 0; k < a; k++)
                            if (randomIndex[a] == randomIndex[k])
                                randomIndex[a] = 0;
                    }
                    enemies[i][j]->ensprite.setPosition(maze[randomIndex[a]].x, maze[randomIndex[a]].y);
                    a++;
                }
            }
            reset = false;
        }



        sound.play();

        while (window.isOpen()) {
            sf::Event event;
            updateText();
            while (window.pollEvent(event)) {
                switch (event.type) {
                case sf::Event::Closed:
                    window.close();
                    return 0;

                case sf::Event::KeyPressed:
                    if (event.key.code == Keyboard::P) {
                        if (!pauseScreen()) {
                            window.close();
                            saveScore(player->XP, playername);
                            return 2;
                        }
                    }
                    player->handleMove(event, maze, &currentPos, SIZE);
                    break;

                default:
                    break;
                }
            }

            if (player->health <= 0) {
                window.close();
                saveScore(player->XP, playername);
                return 0;
            }
            for (int j = 0; j < 2; j++) {
                for (int i = 0; i < 2; i++) {
                    if (player->checkEnemyCollision(enemies[i][j]->ensprite))
                            combat.start_combat_simple(player, enemies[i][j], window);
                }
            }
            for (int i = 0; i < 7; i++) {
                if (player->checkItemCollision(items[i])) {
                    player->addToInventory(items[i]);
                    ItemsInMaze.remove(items[i]);
                }
            }


            if (player->key) {
                door.setTexture(doorOpen);
            }
            else
                door.setTexture(doorClose);


            if (currentPos == (SIZE * SIZE - 1) && player->key) {
                 makeMaze(maze, SIZE);
                 ////////////////////////////////////////
                //makeMaze(maze, SIZE, treasureTree);
                currentPos = 0;
                maze[currentPos].isActive = true;
                reset = true;
                player->key = false;
                round++;
              //  emptyTree(itemsTree);
                
                if (round > 5) {
                    window.close();
                    saveScore(player->XP, playername);
                    return 1;
                }

            }
            //window.clear();
            if (reset) {
                int a = 0;
                for (int j = 0; j < 2; j++) {
                    for (int i = 0; i < 2; i++) {
                        randomIndex[a] = 0;
                        while (randomIndex[a] < 30) {
                            randomIndex[a] = rand() % (SIZE * SIZE);
                            for (int k = 0; k < a; k++)
                                if (randomIndex[a] == randomIndex[k])
                                    randomIndex[a] = 0;
                        }
                        enemies[i][j]->ensprite.setPosition(maze[randomIndex[a]].x, maze[randomIndex[a]].y);
                        a++;
                    }

                }

                while (!ItemsInMaze.isEmpty()) {
                    ItemsInMaze.remove(ItemsInMaze.root->data);
                }

                items = intializeItems(round,maze, window);
                for (int i = 0; i < 6; i++) {
                    ItemsInMaze.insert(items[i]);
                }

                reset = false;
            }


            // Draw the background first
            window.draw(backgroundSprite);

            for (int i = 0; i < SIZE * SIZE; i++) {
                maze[i].draw(&window);
            }

            int shortestPath[SIZE * SIZE];
            int shortestLength;
            findShortestPath(maze, SIZE, 0, SIZE* SIZE - 1, shortestPath, shortestLength);




            // Draw the knight
            player->sprite.setPosition(maze[currentPos].x, maze[currentPos].y);
            window.draw(player->sprite);


            player->displayInventory(window);
            // Draw the tree
            srand(time(0));
            for (int j = 0; j < 2; j++) {
                for (int i = 0; i < 2; i++) {
                    window.draw(enemies[i][j]->ensprite);
                }
            }
            player->sprite.setPosition(maze[currentPos].x, maze[currentPos].y);
            window.draw(player->sprite);

            for (int i = 0; i < 7; i++) {
                window.draw(items[i]->item);
            }

            window.draw(box);
            window.draw(healthtxt);
            window.draw(roundtxt);
            window.draw(XPtxt);
            window.draw(defencetxt);
            window.draw(attacktxt);
            window.draw(door);
            player->displayInventory(window);
            window.display();
        }

        delete[] maze;
    }






    bool pauseScreen() {
        Sprite bg;
        Texture bgtexture;
        Text* options;
        Text start;
        Font font;
        Sprite cursor;
        Texture cursorTexture;
        options = new Text[3];
        cursorTexture.loadFromFile("img/Cursor Default.png");
        cursor.setTexture(cursorTexture);

        bgtexture.loadFromFile("img/pause screen.jpg");
        bg.setTexture(bgtexture);
        bg.setScale(0.38, 0.4);
        bg.setPosition(0, 0);


        RenderWindow window(VideoMode(700, 700), "Pause");

        window.setMouseCursorVisible(false);

        font.loadFromFile("img/Enchanted Land.otf");
        start.setFont(font);
        start.setCharacterSize(100);
        start.setString("Game Paused");
        start.setFillColor(Color::White);
        start.setPosition(300, 30);


        options[0].setFont(font);
        options[0].setCharacterSize(80);
        options[0].setString("Resume");
        options[0].setFillColor(Color::White);
        options[0].setPosition(300, 300);

        options[1].setFont(font);
        options[1].setCharacterSize(80);
        options[1].setString("Save Score&\nBack to Menu");
        options[1].setFillColor(Color::White);
        options[1].setPosition(200, 400);



        while (window.isOpen())
        {
            Event e;
            while (window.pollEvent(e))
            {
                if (options[0].getGlobalBounds().intersects(sf::FloatRect(static_cast<float>(Mouse::getPosition(window).x), static_cast<float>(Mouse::getPosition(window).y), 1, 1))) {
                    options[0].setFillColor(Color(67, 83, 49));
                    if (e.type == sf::Event::MouseButtonPressed && e.mouseButton.button == sf::Mouse::Left) {
                        if (options[0].getGlobalBounds().intersects(sf::FloatRect(static_cast<float>(Mouse::getPosition(window).x), static_cast<float>(Mouse::getPosition(window).y), 1, 1))) {
                            window.close();
                            return true;
                        }
                    }
                }
                else {
                    options[0].setFillColor(Color::White);
                }
                if (options[1].getGlobalBounds().intersects(sf::FloatRect(static_cast<float>(Mouse::getPosition(window).x), static_cast<float>(Mouse::getPosition(window).y), 1, 1))) {
                    options[1].setFillColor(Color(67, 83, 49));
                    if (e.type == sf::Event::MouseButtonPressed && e.mouseButton.button == sf::Mouse::Left) {
                        if (options[1].getGlobalBounds().intersects(sf::FloatRect(static_cast<float>(Mouse::getPosition(window).x), static_cast<float>(Mouse::getPosition(window).y), 1, 1))) {
                            window.close();
                            return false;
                        }
                    }
                }
                else {
                    options[1].setFillColor(Color::White);

                }

            }

            cursor.setPosition(static_cast<float>(Mouse::getPosition(window).x), static_cast<float>(Mouse::getPosition(window).y));

            window.clear(Color::Black); //clears the screen
            window.draw(bg);  // setting background
            window.draw(options[0]);
            window.draw(options[1]);
            window.draw(cursor);
            window.draw(start);

            window.display();

        }

    }

    void saveScore(int XP, string str) {

        

        std::fstream file("highscore.txt", std::ios::in | std::ios::out);
        if (!file.is_open()) {
            std::ofstream outputFile("highscore.txt");
        }

        str += " - " + to_string(XP) + "\n";

        // Alternatively, you can append data to the end of the file
        file.seekp(0, std::ios::end);
        file << str;

        // Close the file
        file.close();

        std::cout << "File updated successfully\n";

        return;

        return;
    }

};

#endif // GAME_H