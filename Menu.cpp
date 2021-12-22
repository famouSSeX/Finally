#include "Menu.hpp"
#include "SFML/Graphics.hpp"
using namespace sf;

namespace ko {
    bool Menu(RenderWindow& app)
    {
        Texture Start;
        Texture Exit;
        Texture Menu_texture;
        

        Menu_texture.loadFromFile("images/pole.png");
        Start.loadFromFile("images/start.png");
        Exit.loadFromFile("images/exit.png");
       
        Sprite menu_texture;
        menu_texture.setTexture(Menu_texture);

        Sprite start;
        start.setTexture(Start);
        start.setOrigin(60, 30);
        start.setPosition(170, 120);

        Sprite exit;
        exit.setTexture(Exit);
        exit.setOrigin(85, 30);
        exit.setPosition(220, 250);

        int nombermenu = 0;
        bool menu = true;

        while (menu)
        {
            start.setColor(Color::White);
            exit.setColor(Color::White);

            app.clear();

            if (IntRect(100, 100, 200, 50).contains(Mouse::getPosition(app))) { start.setColor(Color::Red); nombermenu = 1; }
            if (IntRect(120, 230, 150, 50).contains(Mouse::getPosition(app))) { exit.setColor(Color::Red); nombermenu = 2; }

            //if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            if (Keyboard::isKeyPressed(Keyboard::Enter))
            {
                if (nombermenu == 1) {menu = false;}
                if (nombermenu == 2) { return false; app.close(); menu = false; }
            }

            app.draw(menu_texture);
            app.draw(start);
            app.draw(exit);

            app.display();
        }
    }
}
