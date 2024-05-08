#ifndef MENU_H
#define MENU_H

#include "game.h"







class Menu {
public:
    Sprite bg;
    Texture bgtexture;
    Text* options;
    Text start;
    Font font;
    Sprite cursor;
    Texture cursorTexture;
    //add menu attributes here
    Menu()
    {
        bgtexture.loadFromFile("img/mainscreen.jpg");
        bg.setTexture(bgtexture);
        bg.setScale(0.5, 0.5);
        bg.setPosition(0, 0);
        cursorTexture.loadFromFile("img/Cursor Default.png");
        cursor.setTexture(cursorTexture);

        font.loadFromFile("img/Enchanted Land.otf");
        start.setFont(font);
        start.setCharacterSize(100);
        start.setString("Enchanted\nLabrynth");
        start.setFillColor(Color::White);
        start.setPosition(250, 30);

        options = new Text[4];



        //constructors body
    }


    void intializeText() {
        bgtexture.loadFromFile("img/mainscreen.jpg");
        bg.setTexture(bgtexture);
        bg.setScale(0.5, 0.5);
        bg.setPosition(0, 0);

        font.loadFromFile("img/Enchanted Land.otf");
        start.setFont(font);
        start.setCharacterSize(100);
        start.setString("Enchanted\nLabrynth");
        start.setFillColor(Color::White);
        start.setPosition(250, 30);



        options[0].setFont(font);
        options[0].setCharacterSize(80);
        options[0].setString("Start");
        options[0].setFillColor(Color::White);
        options[0].setPosition(200, 300);

        options[1].setFont(font);
        options[1].setCharacterSize(80);
        options[1].setString("Instructions");
        options[1].setFillColor(Color::White);
        options[1].setPosition(200, 400);

        options[2].setFont(font);
        options[2].setCharacterSize(80);
        options[2].setString("Scoreboard");
        options[2].setFillColor(Color::White);
        options[2].setPosition(200, 500);

        options[3].setFont(font);
        options[3].setCharacterSize(80);
        options[3].setString("Exit");
        options[3].setFillColor(Color::White);
        options[3].setPosition(200, 600);
    }

    void display_menu()

    {
        intializeText();


        Game g;
        //display menu screen here
        //Maze m;
        // add functionality of all the menu options here

        //if Start game option is chosen 
        RenderWindow window(VideoMode(700, 700), title);
        //Picture ki ye dimensions thi but can change^
        window.setMouseCursorVisible(false);




        while (window.isOpen())
        {

            //cout<<time<<endl; 
            Event e;
            while (window.pollEvent(e))
            {

                if (e.type == Event::Closed) // If cross/close is clicked/pressed
                    window.close();
                if (e.type == sf::Event::KeyPressed && e.key.code == sf::Keyboard::Enter) {
                    window.close(); //close the game                        	    

                }

                if (options[0].getGlobalBounds().intersects(sf::FloatRect(static_cast<float>(Mouse::getPosition(window).x), static_cast<float>(Mouse::getPosition(window).y), 1, 1))) {
                    options[0].setFillColor(Color(67, 83, 49));
                    if (e.type == sf::Event::MouseButtonPressed && e.mouseButton.button == sf::Mouse::Left) {
                        if (options[0].getGlobalBounds().intersects(sf::FloatRect(static_cast<float>(Mouse::getPosition(window).x), static_cast<float>(Mouse::getPosition(window).y), 1, 1))) {

                            window.close();
                            string name;
                            name = enterName();
                            if (name != "") {
                                int argc = 0;
                                char* argv[] = { nullptr };
                                int result = g.start_game(argc, argv, name);
                                if (result == 1)
                                    winScreen();
                                else if (result == 0)
                                    loseScreen();
                                else
                                    display_menu();
                            }
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
                            display_instruction();
                        }
                    }
                }
                else {
                    options[1].setFillColor(Color::White);
                }

                if (options[2].getGlobalBounds().intersects(sf::FloatRect(static_cast<float>(Mouse::getPosition(window).x), static_cast<float>(Mouse::getPosition(window).y), 1, 1))) {
                    options[2].setFillColor(Color(67, 83, 49));
                    if (e.type == sf::Event::MouseButtonPressed && e.mouseButton.button == sf::Mouse::Left) {
                        if (options[2].getGlobalBounds().intersects(sf::FloatRect(static_cast<float>(Mouse::getPosition(window).x), static_cast<float>(Mouse::getPosition(window).y), 1, 1))) {
                            window.close();
                            Highscore();
                        }
                    }
                }
                else {
                    options[2].setFillColor(Color::White);
                }

                if (options[3].getGlobalBounds().intersects(sf::FloatRect(static_cast<float>(Mouse::getPosition(window).x), static_cast<float>(Mouse::getPosition(window).y), 1, 1))) {
                    options[3].setFillColor(Color(67, 83, 49));
                    if (e.type == sf::Event::MouseButtonPressed && e.mouseButton.button == sf::Mouse::Left) {
                        if (options[3].getGlobalBounds().intersects(sf::FloatRect(static_cast<float>(Mouse::getPosition(window).x), static_cast<float>(Mouse::getPosition(window).y), 1, 1))) {
                            window.close();
                        }
                    }
                }
                else {
                    options[3].setFillColor(Color::White);
                }



            }

            cursor.setPosition(static_cast<float>(Mouse::getPosition(window).x), static_cast<float>(Mouse::getPosition(window).y));

            window.clear(Color::Black); //clears the screen
            window.draw(bg);  // setting background
            window.draw(options[0]);
            window.draw(options[1]);
            window.draw(options[2]);
            window.draw(options[3]);
            window.draw(cursor);
            window.draw(start);

            window.display();  //Displying all the sprites
        }

    }

    void winScreen() {
        bgtexture.loadFromFile("img/win screen.jpg");
        bg.setTexture(bgtexture);
        bg.setScale(0.38, 0.4);
        bg.setPosition(0, 0);


        RenderWindow window(VideoMode(700, 700), "YOU WON");

        window.setMouseCursorVisible(false);
        font.loadFromFile("img/Enchanted Land.otf");
        start.setFont(font);
        start.setCharacterSize(100);
        start.setString("YOU WON!\nyou can rest now...");
        start.setFillColor(Color::White);
        start.setPosition(100, 30);


        options[0].setFont(font);
        options[0].setCharacterSize(80);
        options[0].setString("Back To Menu");
        options[0].setFillColor(Color::White);
        options[0].setPosition(300, 300);

        options[1].setFont(font);
        options[1].setCharacterSize(80);
        options[1].setString("Exit");
        options[1].setFillColor(Color::White);
        options[1].setPosition(500, 400);

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
                            display_menu();

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
    void loseScreen() {
        bgtexture.loadFromFile("img/lose screen.jpg");
        bg.setTexture(bgtexture);
        bg.setScale(0.38, 0.4);
        bg.setPosition(0, 0);


        RenderWindow window(VideoMode(700, 700), "you lost");

        window.setMouseCursorVisible(false);
        font.loadFromFile("img/Enchanted Land.otf");
        start.setFont(font);
        start.setCharacterSize(100);
        start.setString("you lost\nwhat a shame...");
        start.setFillColor(Color::White);
        start.setPosition(100, 30);


        options[0].setFont(font);
        options[0].setCharacterSize(80);
        options[0].setString("Back To Menu");
        options[0].setFillColor(Color::White);
        options[0].setPosition(300, 300);

        options[1].setFont(font);
        options[1].setCharacterSize(80);
        options[1].setString("Exit");
        options[1].setFillColor(Color::White);
        options[1].setPosition(500, 400);

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
                            display_menu();

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

    void display_instruction() {
        sf::RenderWindow window(sf::VideoMode(700, 700), "Game");

        // Load the background image
        sf::Texture backgroundTexture;
        if (!backgroundTexture.loadFromFile("img/Enchanted_Labyrinth_explorer.png")) {
            std::cerr << "Failed to load background image." << std::endl;
            // Handle the error
        }

        // Create a sprite for the background
        sf::Sprite backgroundSprite(backgroundTexture);
        backgroundSprite.setScale(
            static_cast<float>(window.getSize().x) / backgroundTexture.getSize().x,
            static_cast<float>(window.getSize().y) / backgroundTexture.getSize().y
        );



        while (window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed)
                    window.close();
                //if (e.type == Event::Closed) // If cross/close is clicked/pressed
                else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                    window.close();
                    display_menu();
                }
            }

            window.clear();

            // Draw the background first
            window.draw(backgroundSprite);

            // Draw other game elements here

            if (!font.loadFromFile("img/combatfont.ttf")) {
                cout << "Failed to load font." << std::endl;
                /* if (!font.loadFromFile(sf::Font::getDefaultFont())) {
                     std::cerr << "Failed to load default font." << std::endl;
                 }*/
            }

            start.setFont(font);
            start.setCharacterSize(30);
            start.setFillColor(sf::Color::White);
            start.setOutlineColor(Color::Black);
            start.setPosition(20, 40);
            start.setString(
                "\t\t\t\t\tINSTRUCTIONS\n\n"
                "\tUse arrow keys or WASD to move\n the knight.\n\n"
                "\tFind your way through the maze, \ngrab the key and\nreach the end.\n\n"
                "\tTreasures (sword, armour, rare items) \nare scattered in the maze.\n\n"
                "\tCollect as much as you can to boost\nyour stats\n\n"
                "\tcombat the enemy.\n\n"
                "\t Survive.\n\n"
                "\tPress 'Esc' to go back to menu."
            );

            window.draw(start);

            window.display();
        }

    }

    void pauseScreen(RenderWindow& win) {
        bgtexture.loadFromFile("img/lose screen.jpg");
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
        start.setPosition(100, 30);


        options[0].setFont(font);
        options[0].setCharacterSize(80);
        options[0].setString("Resume");
        options[0].setFillColor(Color::White);
        options[0].setPosition(300, 300);

        options[1].setFont(font);
        options[1].setCharacterSize(80);
        options[1].setString("Back to Menu");
        options[1].setFillColor(Color::White);
        options[1].setPosition(500, 400);



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
                            win.close();
                            display_menu();
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



    ////////////BONUS//////////
    string enterName() {
        //if Start game option is chosen 
        RenderWindow window(VideoMode(700, 700), title);
        //Picture ki ye dimensions thi but can change^
        window.setMouseCursorVisible(false);

        font.loadFromFile("img/Enchanted Land.otf");
        start.setFont(font);
        start.setCharacterSize(100);
        start.setString("Enter\nName");
        start.setFillColor(Color::White);
        start.setPosition(300, 30);


        options[0].setFont(font);
        options[0].setCharacterSize(80);
        options[0].setString("Back");
        options[0].setFillColor(Color::White);
        options[0].setPosition(100, 500);

        bgtexture.loadFromFile("img/mainscreen.jpg");
        bg.setTexture(bgtexture);
        bg.setScale(0.5, 0.5);
        bg.setPosition(0, 0);

        Font infont;
        infont.loadFromFile("img/combatfont.ttf");
        Text input;
        input.setFont(infont);
        input.setCharacterSize(40);
        input.setString("");
        input.setFillColor(Color::White);
        input.setPosition(200, 350);

        cursorTexture.loadFromFile("img/Cursor Default.png");
        cursor.setTexture(cursorTexture);
        string name="";

        while (window.isOpen())
        {
            
            //cout<<time<<endl; 
            Event e;
            while (window.pollEvent(e)) {
                if (e.type == sf::Event::Closed)
                    window.close();
                else if (e.type == sf::Event::TextEntered) {
                    if (e.text.unicode < 128) {
                        char typedChar = static_cast<char>(e.text.unicode);
                        if (typedChar == '\r') { // Enter key
                            window.close();
                        }
                        else if (typedChar == '\b') { // Backspace key
                            if (!name.empty()) {
                                name.pop_back(); // Remove the last character from the string
                                input.setString(name);
                            }
                        }
                        else if (name.size() < 10) { // Limit the string to 10 chars
                            name += typedChar;
                            input.setString(name);
                        }
                    }
                }
            }

            if (options[0].getGlobalBounds().intersects(sf::FloatRect(static_cast<float>(Mouse::getPosition(window).x), static_cast<float>(Mouse::getPosition(window).y), 1, 1))) {
                options[0].setFillColor(Color(67, 83, 49));
                if (e.type == sf::Event::MouseButtonPressed && e.mouseButton.button == sf::Mouse::Left) {
                    if (options[0].getGlobalBounds().intersects(sf::FloatRect(static_cast<float>(Mouse::getPosition(window).x), static_cast<float>(Mouse::getPosition(window).y), 1, 1))) {

                        window.close();
                        display_menu();
                        return "";
                    }

                }
            }
            else {
                options[0].setFillColor(Color::White);
            }
        cursor.setPosition(static_cast<float>(Mouse::getPosition(window).x), static_cast<float>(Mouse::getPosition(window).y));

        window.clear(Color::Black);
        window.draw(bg);
        window.draw(options[0]);
        window.draw(cursor);
        window.draw(start);
        window.draw(input);
        window.display();  //Displying all the sprites

        }
        return name;

    }



    struct PlayerInfo {
        std::string name;
        int score;
    };

    void bubbleSort(PlayerInfo players[], int n) {
        for (int i = 0; i < n - 1; ++i) {
            for (int j = 0; j < n - i - 1; ++j) {
                if (players[j].score < players[j + 1].score) { 

                    PlayerInfo temp = players[j];
                    players[j] = players[j + 1];
                    players[j + 1] = temp;
                }
            }
        }
    }





    void Highscore() {
        //if Start game option is chosen 
        RenderWindow window(VideoMode(700, 700), title);
        //Picture ki ye dimensions thi but can change^
        window.setMouseCursorVisible(false);

        font.loadFromFile("img/Enchanted Land.otf");
        start.setFont(font);
        start.setCharacterSize(100);
        start.setString("Scoreboard");
        start.setFillColor(Color::White);
        start.setPosition(250, 30);


        options[0].setFont(font);
        options[0].setCharacterSize(80);
        options[0].setString("Back");
        options[0].setFillColor(Color::White);
        options[0].setPosition(100, 500);

        bgtexture.loadFromFile("img/mainscreen.jpg");
        bg.setTexture(bgtexture);
        bg.setScale(0.5, 0.5);
        bg.setPosition(0, 0);

        Font infont;
        infont.loadFromFile("img/combatfont.ttf");
        Text output;
        output.setFont(infont);
        output.setCharacterSize(50);
        output.setString("");
        output.setFillColor(Color::White);
        output.setPosition(200,150);

        cursorTexture.loadFromFile("img/Cursor Default.png");
        cursor.setTexture(cursorTexture);
        string name = " ";

  


            const std::string filename = "highscore.txt";
            const int MAX_PLAYERS = 10;
            PlayerInfo players[MAX_PLAYERS];
            int numPlayers = 0;


            std::ifstream file(filename);
            if (!file.is_open()) {
                std::cerr << "Failed to open file\n";
                return;
            }

            std::string line;
            while (std::getline(file, line)) {
                std::string name;
                std::string score;
                int i = 0;

                while (i < line.size() && line[i] != ' ') {
                    name += line[i];
                    i++;
                }
                i += 3;
              
                while (i < line.size() && std::isdigit(line[i])) {
                    score += line[i];
                    i++;
                }
                
                players[numPlayers].name = name;
                players[numPlayers].score = std::stoi(score);
                ++numPlayers;
            }
            file.close();

            // sort
            bubbleSort(players, numPlayers);

            // Rewrite data 
            std::ofstream outputFile(filename);
            if (!outputFile.is_open()) {
                std::cerr << "Failed to open file for writing\n";
                return;
            }

            for (int i = 0; i < numPlayers; ++i) {
                outputFile << players[i].name << " - " << players[i].score << "\n";
            }
            outputFile.close();

            // Read sorted content
            file.open(filename);
            if (!file.is_open()) {
                std::cerr << "Failed to open file\n";
                return;
            }
            std::string content;
            line = "";
            int a = 0;
            while (std::getline(file, line) && a < 5) {
                content += line + "\n";
                a++;
            }
            file.close();

            output.setString(content);
        while (window.isOpen())
        {
            Event e;
            while (window.pollEvent(e)) {
                if (e.type == sf::Event::Closed)
                    window.close();

            }
            if (options[0].getGlobalBounds().intersects(sf::FloatRect(static_cast<float>(Mouse::getPosition(window).x), static_cast<float>(Mouse::getPosition(window).y), 1, 1))) {
                options[0].setFillColor(Color(67, 83, 49));
                if (e.type == sf::Event::MouseButtonPressed && e.mouseButton.button == sf::Mouse::Left) {
                    if (options[0].getGlobalBounds().intersects(sf::FloatRect(static_cast<float>(Mouse::getPosition(window).x), static_cast<float>(Mouse::getPosition(window).y), 1, 1))) {

                        window.close();
                        display_menu();
                        return;
                    }

                }
            }
            else {
                options[0].setFillColor(Color::White);
            }
            cursor.setPosition(static_cast<float>(Mouse::getPosition(window).x), static_cast<float>(Mouse::getPosition(window).y));

            window.clear(Color::Black); //clears the screen
            window.draw(bg);  // setting background
            window.draw(options[0]);
            window.draw(cursor);
            window.draw(start);
            window.draw(output);
            window.display();  //Displying all the sprites

        }
    }


};



#endif // MENU_H