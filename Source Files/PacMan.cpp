#include <SFML/Graphics.hpp>
#include <array>
#include <math.h>
#include "Ghost.h"
#define Pi 3.14159265358979323846264338327950;
using namespace std;
void Controls();
void main()
{
    //Calling objects
    sf::ContextSettings settings;//Settings for window
    sf::RenderWindow window(sf::VideoMode(1120, 1240), "PacMan", sf::Style::Default, settings);//Window
    sf::Texture maptexture;//Texture for map
    sf::Sprite mapsprite;//Sprite for map
    sf::RectangleShape coins(sf::Vector2f(4, 4));//Graphics for coins
    sf::CircleShape megacoins(10, 12);//Graphics for megacoins
    sf::CircleShape player(22, 22);//Graphics for pacman
    sf::Clock retreatCount;//Timer for amount retreat
    //
    //Setting up
    maptexture.loadFromFile("C:/Users/Kurt/source/repos/PacMan/PacMan/map.png");//Calls map.png from my drive
    mapsprite.setTexture(maptexture);//Loads the map texture
    mapsprite.setScale(sf::Vector2f(2.5f, 2.48995983936f));//Resizes the image
    window.setFramerateLimit(60);//Puts maximum framerate
    int multiples = 40;//Size of each tile
    int functions = 0;//function integer which controls ghosts.
    int timeformegacoin = 10;
    //
    while (window.isOpen())
    {
        window.clear(sf::Color(0, 0, 0));
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) {
            //If hits red X button close the window
                window.close();
            }
        }
        for (int y = 0; y < 31; y++) {
            for (int x = 0; x < 28; x++) {
                if (pacman.playerx == x && pacman.playery == y) {//Does Action
                    switch (maps[y][x]) {
                    case 0://Coin
                        maps[y][x] = 4;//No Coin
                        break;
                    case 2://Move Node With Coin
                        maps[y][x] = 3;//Move Node Without Coin
                        break;
                    case 8://"mega"coin
                        maps[y][x] = 9;//No MegaCoin
                        functions = 1;//Ghosts Retreat
                        retreatCount.restart();//Timer Restarts
                        break;
                    }
                }
                else {//Draws Stuff
                    switch (maps[y][x]) {
                    case 0://Coin
                    case 2://Move Node
                        coins.setFillColor(sf::Color(254, 169, 163));
                        coins.setPosition(x * multiples + multiples / 2 - 0, y * multiples + multiples / 2 - 0);
                        window.draw(coins);
                        break;
                    case 8://"mega"coin
                        megacoins.setFillColor(sf::Color(254, 169, 163));
                        megacoins.setPosition(x * multiples + multiples / 2 - 8, y * multiples + multiples / 2 - 8);
                        window.draw(megacoins);
                        break;
                    }
                }
            }
        }
        if (maps[pacman.playery + pacman.slopey][pacman.playerx + pacman.slopex] != 1) {
        //If ahead of pacman is not a wall
            pacman.PixelstoPlayerx += pacman.slopex * pacman.speed;//Add pacman's slope to his position
            pacman.PixelstoPlayery += pacman.slopey * pacman.speed;
            if (distance((pacman.playerx + pacman.slopex) * multiples + multiples / 2, (pacman.playery + pacman.slopey) * multiples + multiples / 2, pacman.PixelstoPlayerx + multiples / 2, pacman.PixelstoPlayery + multiples / 2) < pacman.speed) {
            //If pacman is close to the tile pacman wants to go
                pacman.playerx = pacman.playerx + pacman.slopex;//Set pacman's tile x position to the tile
                pacman.playery = pacman.playery + pacman.slopey;//Set pacman's tile y position to the tile
                pacman.PixelstoPlayerx = pacman.playerx * multiples;//Set pacman's actual x position to the tile
                pacman.PixelstoPlayery = pacman.playery * multiples;//Set pacman's actual y position to the tile
                Controls();//See if the player wants to change direction
            }
        }
        else {
        //Else if there is a wall
            pacman.slopex = 0;//Stop pacman
            pacman.slopey = 0;
        }
        if (functions == 1) {
        //If pacman has hit a megacoin OR time has not run out
            sf::Time time = retreatCount.getElapsedTime();//Get how much time is left
            int colortime = time.asSeconds() * 5;//Get the amount of time before color of ghosts change
            int color;//Set ready for the color of the ghosts
            if (colortime % 2 == 0) {
                color = 255;
            }
            else {
                color = 100;
            }
            if (time.asSeconds() >= timeformegacoin) {
            //If time has run out
                functions = 0;//Ghosts no longer retreat
            }
            else {
                inkya.draw(window, color, color, color);
                bonnya.draw(window, color, color, color);
                stinkya.draw(window, color, color, color);
                clydea.draw(window, color, color, color);
            }
        }
        inkya.move(functions,window);//Move all ghosts to player
        bonnya.move(functions, window);
        stinkya.move(functions, window);
        clydea.move(functions, window);
        player.setFillColor(sf::Color(255, 255, 0));//Set color value of pacman
        player.setPosition(pacman.PixelstoPlayerx + 0, pacman.PixelstoPlayery + 0);//Set position of graphics for pacman
        window.draw(player);//Put pacman onto the screen
        window.draw(mapsprite);//Put the map onto the screen
        window.display();//Put the frame onto the screen
    }
}

void Controls() {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    //If keyboard press left arrow
    {
        if (maps[pacman.playery][pacman.playerx - 1] != 1) {
        //If left of pacman is not a wall
            pacman.slopex = -1;//Tell pacman to move left
            pacman.slopey = 0;
        }
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    //If keyboard press right arrow
    {
        if (maps[pacman.playery][pacman.playerx+1] != 1) {
        //If right of pacman is not a wall
            pacman.slopex = 1;//Tell pacman to move right
            pacman.slopey = 0;
        }
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    //If keyboard press up arrow
    {
        if (maps[pacman.playery-1][pacman.playerx] != 1) {
        //If ahead of pacman is not a wall
            pacman.slopex = 0;
            pacman.slopey = -1;//Tell pacman to go up
        }
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    //If keyboard press down arrow
    {
        if (maps[pacman.playery + 1][pacman.playerx] != 1) {
        //If beneath pacman is not a wall
            pacman.slopex = 0;
            pacman.slopey = 1;//Tell pacman to go down
        }
    }
}
