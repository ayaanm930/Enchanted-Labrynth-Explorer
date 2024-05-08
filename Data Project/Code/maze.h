#ifndef MAZE_H
#define MAZE_H

#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <ctime>
#include <stack>
#include <iostream>
#include <random>

using namespace std;
#define SIZE 15
#define CELL_WIDTH 55

class Cell {
public:
    int x, y;
    int pos;
    float size = 30.f;
    float thickness = 5.f;
    bool walls[4] = { true,true,true,true };
    bool visited = false;
    bool isActive = false;
    /////////////////for avl//////////////////////
    bool hasTreasure;
    ///////////////////////////////
    Cell();
    Cell(int, int);
    void draw(sf::RenderWindow* window);
};
Cell::Cell() {}
Cell::Cell(int _x, int _y) {
    x = _x;
    y = _y;
}

void Cell::draw(sf::RenderWindow* window) {
    sf::RectangleShape rect;

    if (isActive) {
        rect.setFillColor(sf::Color::Transparent);
        rect.setSize(sf::Vector2f(size, size));
        rect.setPosition(x, y);
        window->draw(rect);
    }
    rect.setFillColor(sf::Color(150, 150, 150));

    if (walls[0]) {
        rect.setSize(sf::Vector2f(size, thickness));
        rect.setPosition(x, y);
        window->draw(rect);
    }
    // right
    if (walls[1]) {
        rect.setSize(sf::Vector2f(thickness, size));
        rect.setPosition(x + size, y);
        window->draw(rect);
    }
    // bottom
    if (walls[2]) {
        rect.setSize(sf::Vector2f(size + thickness, thickness));
        rect.setPosition(x, y + size);
        window->draw(rect);
    }
    // left
    if (walls[3]) {
        rect.setSize(sf::Vector2f(thickness, size));
        rect.setPosition(x, y);
        window->draw(rect);
    }

    // Modify the draw function to draw treasures as blue boxes
   //////////////////////////////avl////////////////////
        // Existing drawing logic...
        // Draw treasure if the cell contains one
   /* if (hasTreasure) {
        sf::RectangleShape treasureRect;
        treasureRect.setFillColor(sf::Color(0,0,128));
        treasureRect.setSize(sf::Vector2f(size, size));
        treasureRect.setPosition(x, y);
        window->draw(treasureRect);
    }*/

}

void resetMaze(Cell* maze, int size) {
    for (int i = 0; i < size * size; i++) {
        for (int j = 0; j < 4; j++) {
            maze[i].walls[j] = true;
            maze[i].visited = false;
            maze[i].isActive = false;
        }
    }

}

void removeWallsBetween(Cell* maze, Cell* current, Cell* chosen, int size) {
    // top
    if (current->pos - size == chosen->pos) {
        current->walls[0] = false;
        chosen->walls[2] = false;
        // right
    }
    else if (current->pos + 1 == chosen->pos) {
        current->walls[1] = false;
        chosen->walls[3] = false;
        // bottom 
    }
    else if (current->pos + size == chosen->pos) {
        current->walls[2] = false;
        chosen->walls[0] = false;
        // left 
    }
    else if (current->pos - 1 == chosen->pos) {
        current->walls[3] = false;
        chosen->walls[1] = false;
    }
}

/////////////////////////////avl///////////////////////////
void makeMaze(Cell* maze, int size){
//void makeMaze(Cell* maze, int size, AVLTree treasureTree) {
    resetMaze(maze, size);
    std::stack<Cell> stack;
    maze[0].visited = true;
    stack.push(maze[0]);

    while (!stack.empty()) {
        Cell current = stack.top();
        stack.pop();
        int pos = current.pos;
        std::vector<int> neighbours;

        if ((pos) % (size) != 0 && pos > 0) {
            Cell left = maze[pos - 1];
            if (!left.visited) {
                neighbours.push_back(pos - 1);
            }
        }
        if ((pos + 1) % (size) != 0 && pos < size * size) {
            Cell right = maze[pos + 1];
            if (!right.visited) {
                neighbours.push_back(pos + 1);
            }

        }
        if ((pos + size) < size * size) {
            Cell bottom = maze[pos + size];
            if (!bottom.visited) {
                neighbours.push_back(pos + size);
            }
        }

        if ((pos - size) > 0) {
            Cell top = maze[pos - size];
            if (!top.visited) {
                neighbours.push_back(pos - size);
            }
        }

        if (neighbours.size() > 0) {
            // generate a random array index for selecting a neighbour
            std::random_device dev;
            std::mt19937 rng(dev());
            std::uniform_int_distribution<std::mt19937::result_type> dist6(0, neighbours.size() - 1);
            int randneighbourpos = dist6(rng);

            Cell* chosen = &maze[neighbours[randneighbourpos]];

            stack.push(current);

            removeWallsBetween(maze, &maze[current.pos], chosen, size);

            chosen->visited = true;
            stack.push(*chosen);
        }

    }
    /////////////avl/////////////////////////////////
    //srand(time(nullptr));
    //int treasurePos = rand() % (size * size); // Generate a random position
    //maze[treasurePos].hasTreasure = true; // Mark the cell as containing a treasure
    //treasureTree.insert(treasurePos); // Insert the treasure position into the AVL tree


    
};
///////////////////////avl///////////////////////////

void backtracking(Cell* maze, int size, int start, int end, int* path, int& pathLength, int* shortestPath, int& shortestLength) {
    if (start == end) {
        if (pathLength < shortestLength) {
            shortestLength = pathLength;
            for (int i = 0; i < shortestLength; ++i) {
                shortestPath[i] = path[i];
            }
        }
        return;
    }

    maze[start].visited = true;

    int xx[] = { 0, 1, 0, -1 };
    int yy[] = { -1, 0, 1, 0 };
    for (int dir = 0; dir < 4; ++dir) {
        int nx = start % size + xx[dir];
        int ny = start / size + yy[dir];
        int newPos = ny * size + nx;

        if (nx >= 0 && nx < size && ny >= 0 && ny < size && !maze[start].walls[dir] && !maze[newPos].visited) {
            path[pathLength++] = newPos;
            backtracking(maze, size, newPos, end, path, pathLength, shortestPath, shortestLength);
            --pathLength;
        }
    }

    maze[start].visited = false;
}

void findShortestPath(Cell* maze, int size, int start, int end, int* shortestPath, int& shortestLength) {
    int path[SIZE * SIZE];
    int pathLength = 0;
    shortestLength = size * size + 1;

    backtracking(maze, size, start, end, path, pathLength, shortestPath, shortestLength);
}



void handleMove(sf::Event event, Cell* maze, int* currentPos, int size) {
    if (
        event.key.code == sf::Keyboard::Left || event.key.code == sf::Keyboard::A) {
        if (!maze[*currentPos].walls[3] && !maze[*currentPos - 1].walls[1]) {
            *currentPos = *currentPos - 1;
            maze[*currentPos].isActive = true;
        }
    }
    else if (
        event.key.code == sf::Keyboard::Right || event.key.code == sf::Keyboard::D) {
        if (!maze[*currentPos].walls[1] && !maze[*currentPos + 1].walls[3]) {
            *currentPos = *currentPos + 1;
            maze[*currentPos].isActive = true;
        }
    }
    else if (event.key.code == sf::Keyboard::Up || event.key.code == sf::Keyboard::W) {
        if ((*currentPos - size) < 0) {
            return;
        }
        if (!maze[*currentPos].walls[0] && !maze[*currentPos - size].walls[2]) {
            *currentPos = *currentPos - size;
            maze[*currentPos].isActive = true;
        }
    }
    else if (event.key.code == sf::Keyboard::Down || event.key.code == sf::Keyboard::S) {
        if ((*currentPos + size) > size * size) {
            return;
        }
        if (!maze[*currentPos].walls[2] && !maze[*currentPos + size].walls[0]) {
            *currentPos = *currentPos + size;
            maze[*currentPos].isActive = true;
        }
    }
}



#endif // MAZE_H