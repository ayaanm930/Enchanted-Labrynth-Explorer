#ifndef COMBAT_H
#define COMBAT_H
class Combat {
public:


    Text start;
    Font font;


    string str;



	Combat() {

        font.loadFromFile("img/combatfont.ttf");
        start.setFont(font);
        start.setCharacterSize(30);
        start.setString("Battle started");
        start.setFillColor(Color::Black);
        start.setPosition(10, 520);

	}

    void start_combat_simple(Player*& player, Enemy*& en, RenderWindow& window) {
        RectangleShape rect;
        rect.setSize(Vector2f(300, 100));
        rect.setPosition(CELL_WIDTH * SIZE + 60, 270);
        rect.setFillColor(Color::Black);
        string str = en->name;
        str += " \nEncountered\npress enter";
        bool enter = false;

        start.setCharacterSize(25);
        Event e;
        start.setString(str);
        start.setFillColor(Color::White);
        start.setPosition(CELL_WIDTH * SIZE + 70, 270);
        window.draw(rect);
        window.draw(start);
        window.display();

        while (!enter) {
            while (window.pollEvent(e)) {
                if (e.type == sf::Event::KeyPressed) {
                    if (e.key.code == sf::Keyboard::Enter) {
                        enter = true;
                        break; // Exit the inner while loop when Enter is pressed
                    }
                }
            }
        }
        enter = false;

        str = "Your Score: ";
        str += to_string(player->attack + player->total_defence);
        str += "\npress enter";
        start.setString("");
        start.setString(str);
        window.draw(rect);
        window.draw(start);
        window.display();

        while (!enter) {
            while (window.pollEvent(e)) {
                if (e.type == sf::Event::KeyPressed) {
                    if (e.key.code == sf::Keyboard::Enter) {
                        enter = true;
                        break; // Exit the inner while loop when Enter is pressed
                    }
                }
            }
        }
        enter = false;

        str = "Enemy Score: ";
        str += to_string(en->attack);
        str += "\npress enter";
        start.setString("");
        start.setString(str);
        window.draw(rect);
        window.draw(start);
        window.display();

        while (!enter) {
            while (window.pollEvent(e)) {
                if (e.type == sf::Event::KeyPressed) {
                    if (e.key.code == sf::Keyboard::Enter) {
                        enter = true;
                        break; // Exit the inner while loop when Enter is pressed
                    }
                }
            }
        }
        enter = false;

        if (player->total_defence + player->attack< en->attack) {


            player->health -= en->attack;
            window.display();
            str = "You Lost. ";
            if (player->health > 0) {
                str += "\nBut you did not\n succumb\n";
                en->health = 0;
                en->ensprite.setPosition(-100, -100);



            }
            else {
                str += "\n You are dead...\n";
            }
            str += "\npress enter";
            start.setString("");
            start.setString(str);
            window.draw(rect);
            window.draw(start);
            window.display();

            while (!enter) {
                while (window.pollEvent(e)) {
                    if (e.type == sf::Event::KeyPressed) {
                        if (e.key.code == sf::Keyboard::Enter) {
                            enter = true;
                            break; // Exit the inner while loop when Enter is pressed
                        }
                    }
                }
            }
            enter = false;
        }
        else {
            if (player->total_defence > 0) {
                player->total_defence -= en->attack;
                if (player->total_defence < 0)
                    player->total_defence = 0;
            }

            else {
                int attack = en->attack;
                player->health -= en->attack + player->total_defence;
            }

            en->health = 0;
            en->ensprite.setPosition(-100, -100);
            player->XP += en->value;
            str = "";
            str = "You Won!! \nXP +";
            str += to_string(en->value);
            str += "\npress enter";

            start.setString("");
            start.setString(str);
            window.draw(rect);
            window.draw(start);
            window.display();

            while (!enter) {
                while (window.pollEvent(e)) {
                    if (e.type == sf::Event::KeyPressed) {
                        if (e.key.code == sf::Keyboard::Enter) {
                            enter = true;
                            break; // Exit the inner while loop when Enter is pressed
                        }
                    }
                }
            }
            enter = false;
        }
    }
};  




#endif // COMBAT_H
