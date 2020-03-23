#include <vector>
#include <SFML/Graphics.hpp>
#include <math.h>
using namespace std;
float distance(float x1, float y1, float x2, float y2);//From Pathfinding.cpp
int maps[31][28] = {//Map data
    //1 is a coin
    //2 is a node which ghosts have the option to go different directions (2 also has a coin on it)
    //3 is a node which ghosts have the option to go different directions (3 does not have a coin on it)
    //4 is an empty coin spot
    //5 is an empty spot
    //6 is a node that allows jailed ghosts to go into the prison
    //8 is a mega coin
    //9 is an empty mega coin spot
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 2, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 2, 1, 1, 2, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 2, 1},
    {1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1},
    {1, 8, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 8, 1},
    {1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1},
    {1, 2, 0, 0, 0, 0, 2, 0, 0, 2, 0, 0, 2, 0, 0, 2, 0, 0, 2, 0, 0, 2, 0, 0, 0, 0, 2, 1},
    {1, 0, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 0, 1},
    {1, 0, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 0, 1},
    {1, 2, 0, 0, 0, 0, 2, 1, 1, 2, 0, 0, 2, 1, 1, 2, 0, 0, 2, 1, 1, 2, 0, 0, 0, 0, 2, 1},
    {1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 5, 1, 1, 5, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 5, 1, 1, 5, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 1, 0, 1, 1, 3, 5, 5, 3, 5, 5, 3, 5, 5, 3, 1, 1, 0, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 1, 0, 1, 1, 5, 1, 1, 1, 6, 6, 1, 1, 1, 5, 1, 1, 0, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 1, 0, 1, 1, 5, 1, 1, 6, 6, 6, 6, 1, 1, 5, 1, 1, 0, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 1, 2, 5, 5, 3, 1, 1, 6, 6, 6, 6, 1, 1, 3, 5, 5, 2, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 1, 0, 1, 1, 5, 1, 1, 1, 1, 1, 1, 1, 1, 5, 1, 1, 0, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 1, 0, 1, 1, 5, 1, 1, 1, 1, 1, 1, 1, 1, 5, 1, 1, 0, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 1, 0, 1, 1, 3, 5, 5, 5, 5, 5, 5, 5, 5, 3, 1, 1, 0, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 1, 0, 1, 1, 5, 1, 1, 1, 1, 1, 1, 1, 1, 5, 1, 1, 0, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 1, 0, 1, 1, 5, 1, 1, 1, 1, 1, 1, 1, 1, 5, 1, 1, 0, 1, 1, 1, 1, 1, 1},
    {1, 2, 0, 0, 0, 0, 2, 0, 0, 2, 0, 0, 2, 1, 1, 2, 0, 0, 2, 0, 0, 2, 0, 0, 0, 0, 2, 1},
    {1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1},
    {1, 8, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 8, 1},
    {1, 2, 0, 2, 1, 1, 2, 0, 0, 2, 0, 0, 2, 0, 0, 2, 0, 0, 2, 0, 0, 2, 1, 1, 2, 0, 2, 1},
    {1, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 1},
    {1, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 1},
    {1, 2, 0, 2, 0, 0, 2, 1, 1, 2, 0, 0, 2, 1, 1, 2, 0, 0, 2, 1, 1, 2, 0, 0, 2, 0, 2, 1},
    {1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1},
    {1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1},
    {1, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
};
int multiples = 40;//Size of each tile
int TimeInPrison = 15;
class player {//Pacman :)
public:
    int playerx = 14;//Tile x value
    int playery = 17;//Tile y value
    int PixelstoPlayerx = playerx * multiples;//In-game x pacman position
    int PixelstoPlayery = playery * multiples;//In-game y pacman position
    int slopex = 0;//Pacman directions x
    int slopey = 0;//Pacman directions y
    int speed = 2;//Speed of which pacman moves per pixel
};
player pacman;//Call pacman class
class node {//Nodes for A* algorithms
public:
    float scost;//"Start cost" which is the distance from where the tile is to the player
    float ecost;//"End cost" which is the distance from where the tile is to where the player wants to go
    float fcost;//Sum of both the "scost" and the "ecost"
    int x;//X coordinates of the tile
    int y;//Y coordinates of the tile
    int parentx;//X coordinates of the parent's tile
    int parenty;//Y coordinates of the parent's tile
    void remove(vector<node>& vector) {//Remove this node from a vector
        for (int i = 0; i < vector.size(); i++) {
        //For every node in the vector
            if (vector[i].x == x && vector[i].y == y) {
            //If the vector node is equal to both x and y coordinates of this tile
                vector.erase(vector.begin() + i, vector.begin() + (i + 1));//Erase the tile from the vector
            }
        }
    }
    void add(vector<node>& vector) {//Add this node to a vector
        node self;//Declare a new node object
        self.scost = scost;//Set new node object to this node object
        self.ecost = ecost;
        self.fcost = fcost;
        self.x = x;
        self.y = y;
        self.parentx = parentx;
        self.parenty = parenty;
        vector.insert(vector.begin(), self);//Put the node object into a vector
    }
};
void AStarClyde(int startx, int starty, int endx, int endy, float slopex, float slopey, vector<node>& path, int maps[31][28], int PacmanSlopex, int PacmanSlopey);//From PathFinding.cpp
void AStarInky(int startx, int starty, int endx, int endy, float slopex, float slopey, vector<node>& path, int maps[31][28]);
void AStarStinky(int startx, int starty, int endx, int endy, float slopex, float slopey, vector<node>& path, int maps[31][28]);
void AStarBonny(int startx, int starty, int endx, int endy, float slopex, float slopey, vector<node>& path, int maps[31][28], int PosClydeX, int PosClydeY);
void AStarRetreat(int startx, int starty, int PacManX, int PacManY, float slopex, float slopey, vector<node>& path, int maps[31][28]);
void AStarPrison(int startx, int starty, int endx, int endy, float slopex, float slopey, vector<node>& path, int maps[31][28]);
bool ghostplayercollision(int x, int y) {//See if the ghost and the player have touched
    if (distance(x, y, pacman.PixelstoPlayerx, pacman.PixelstoPlayery) <= 44) {
    //If the ghost and the player have collided
        return true;//returns true :/
    }
    return false;
}
void breaktime(int posx, int posy, int x, int y) {

}
class clyde {
public:
    //Ready up objects for class
    sf::Clock jailtime;//Haha! see what I did there?
    vector <node> path;//Declar no path object
    int x = 1;//Set position of X coordinates in tile
    int y = 23;//Set position of Y coordinates in tile
    float PixelstoX = x * multiples;//In-game X coordinates equals to tile X coordinates times how big tiles are
    float PixelstoY = y * multiples;//In-game Y coordinates equals to tile Y coordinates times how big tiles are
    float speed = 1.75;//Speed of clyde is seven eigths to that of pacman (Speed changes)
    float slopex;//Set the variable for slope X coordinate ready
    float slopey;//Set the variable for slope Y coordinate ready
    bool prison;
    //
    //Ready up functions for class
    void pathfindtoprison() {
        path.erase(path.begin(), path.end());
        AStarPrison(x, y, 12, 14, slopex, slopey, path, maps);
    }
    void pathfindtoplayer() {//Uses the A* algorithm to coordinate a path to the player
        path.erase(path.begin(), path.end());//Delete everything from the vector "path"
        AStarClyde(x, y, pacman.playerx, pacman.playery, slopex, slopey, path, maps, pacman.slopex, pacman.slopey);//Coordinate a path to the player for clyde
    }
    void pathfindawayplayer() {//Uses algorithm to coordinate a path away from the player
        path.erase(path.begin(), path.end());//Delete everything from path
        AStarRetreat(x, y, pacman.playerx, pacman.playery, slopex, slopey, path, maps);//Coordinate a path away from the player for clyde
    }
    void draw(sf::RenderWindow& window, int R, int G, int B) {//Draw function that draws its planned path and the ghost
        sf::CircleShape ClydeSprite(22, 22);//Graphics for the ghost
        ClydeSprite.setFillColor(sf::Color(R, G, B));//Set the color for the graphics of clyde1
        ClydeSprite.setPosition(PixelstoX, PixelstoY);//Set the position of clyde to in-game position
        window.draw(ClydeSprite);//Draw clyde graphics into the window
        for (int i = 1; i < path.size(); i++) {
        //For every node in path vector
            sf::Vertex Path[] =//Draw line from one path node to another
            {
                sf::Vertex(sf::Vector2f(path[i - 1].x* multiples + 22, path[i - 1].y* multiples + 22), sf::Color(ClydeSprite.getFillColor())),
                sf::Vertex(sf::Vector2f(path[i].x* multiples + 22, path[i].y* multiples + 22), sf::Color(ClydeSprite.getFillColor())),
            };
            window.draw(Path, 2, sf::Lines);//Draw each line graphic onto the window
        }
    }
    void move(int func, sf::RenderWindow& window) {
        if (prison) {
            func = 2;
        }
        if (path.size() != 0) {
            switch (func) {
            case 0:
                draw(window, 255, 0, 0);
                speed = 1.75;
                if (ghostplayercollision(PixelstoX, PixelstoY)) {
                    window.close();
                }
                break;
            case 1:
                speed = 1;
                if (ghostplayercollision(PixelstoX, PixelstoY)) {
                    jailtime.restart();
                    prison = true;
                }
                break;
            case 2:
                sf::Time time = jailtime.getElapsedTime();
                if (time.asSeconds() >= 15) {
                    x = 13;
                    y = 12;
                    prison = false;
                }
                draw(window, 150, 150, 255);
                speed = 7;
            }
            float rad = atan2(path[0].y * multiples - PixelstoY, path[0].x * multiples - PixelstoX);
            slopey = sin(rad);
            slopex = cos(rad);
            PixelstoX += slopex * speed;
            PixelstoY += slopey * speed;
            if (distance(PixelstoX, PixelstoY, path[0].x * multiples, path[0].y * multiples) < speed) {
                x = path[0].x;
                y = path[0].y;
                PixelstoX = path[0].x * multiples;
                PixelstoY = path[0].y * multiples;
                path.erase(path.begin(), path.begin() + 1);
                if (maps[y][x] == 2 || maps[y][x] == 3) {
                    switch (func)
                    {
                    case 0:
                        pathfindtoplayer();
                        break;
                    case 1:
                        pathfindawayplayer();
                        break;
                    case 2:
                        pathfindtoprison();
                        break;
                    }
                }
            }
        }
        else {
            switch (func)
            {
            case 0:
                pathfindtoplayer();
                draw(window, 255, 0, 0);
                speed = 1.75;
                if (ghostplayercollision(PixelstoX, PixelstoY)) {
                    window.close();
                }
            case 1:
                pathfindawayplayer();
                if (ghostplayercollision(PixelstoX, PixelstoY)) {
                    prison = true;
                }
                break;
            case 2:
                sf::Time time = jailtime.getElapsedTime();
                if (time.asSeconds() >= TimeInPrison) {
                    prison = false;
                }
                draw(window, 150, 150, 255);
                speed = 7;
            }
        }
    }
    //
};
//Im not writing comments for all these, most of it is similar.
clyde clydea;
class inky {
public:
    sf::Clock jailtime;
    vector <node> path;
    int x = 23;
    int y = 1;
    float PixelstoX = x * multiples;
    float PixelstoY = y * multiples;
    float speed = 1.25;
    float slopex;
    float slopey;
    bool prison;
    void pathfindtoprison() {
        path.erase(path.begin(), path.end());
        AStarPrison(x, y, 13, 14, slopex, slopey, path, maps);
    }
    void pathfindtoplayer() {
        path.erase(path.begin(), path.end());
        AStarInky(x, y, pacman.playerx, pacman.playery, slopex, slopey, path, maps);
    }
    void pathfindawayplayer() {
        path.erase(path.begin(), path.end());
        AStarRetreat(x, y, pacman.playerx, pacman.playery, slopex, slopey, path, maps);
    }
    void draw(sf::RenderWindow& window, int R, int G, int B) {
        sf::CircleShape ClydeSprite(22, 22);
        ClydeSprite.setFillColor(sf::Color(R, G, B));
        ClydeSprite.setPosition(PixelstoX, PixelstoY);
        window.draw(ClydeSprite);
        for (int i = 1; i < path.size(); i++) {
            sf::Vertex Path[] =
            {
                sf::Vertex(sf::Vector2f(path[i - 1].x * multiples + 22, path[i - 1].y * multiples + 22), sf::Color(ClydeSprite.getFillColor())),
                sf::Vertex(sf::Vector2f(path[i].x * multiples + 22, path[i].y * multiples + 22), sf::Color(ClydeSprite.getFillColor())),
            };
            window.draw(Path, 2, sf::Lines);
        }
    }
    void move(int func, sf::RenderWindow& window) {
        if (prison) {
            func = 2;
        }
        if (path.size() != 0) {
            switch (func) {
            case 0:
                draw(window, 100, 100, 255);
                speed = 1.25;
                if (ghostplayercollision(PixelstoX, PixelstoY)) {
                    window.close();
                }
                break;
            case 1:
                speed = 1;
                if (ghostplayercollision(PixelstoX, PixelstoY)) {
                    jailtime.restart();
                    prison = true;
                }
                break;
            case 2:
                sf::Time time = jailtime.getElapsedTime();
                if (time.asSeconds() >= 15) {
                    prison = false;
                }
                draw(window, 150, 150, 255);
                speed = 7;
            }
            float rad = atan2(path[0].y * multiples - PixelstoY, path[0].x * multiples - PixelstoX);
            slopey = sin(rad);
            slopex = cos(rad);
            PixelstoX += slopex * speed;
            PixelstoY += slopey * speed;
            if (distance(PixelstoX, PixelstoY, path[0].x * multiples, path[0].y * multiples) < speed) {
                x = path[0].x;
                y = path[0].y;
                PixelstoX = path[0].x * multiples;
                PixelstoY = path[0].y * multiples;
                path.erase(path.begin(), path.begin() + 1);
                if (maps[y][x] == 2 || maps[y][x] == 3) {
                    switch (func)
                    {
                    case 0:
                        pathfindtoplayer();
                        break;
                    case 1:
                        pathfindawayplayer();
                        break;
                    case 2:
                        pathfindtoprison();
                        break;
                    }
                }
            }
        }
        else {
            switch (func)
            {
            case 0:
                pathfindtoplayer();
                draw(window, 255, 0, 0);
                speed = 1.75;
                if (ghostplayercollision(PixelstoX, PixelstoY)) {
                    window.close();
                }
            case 1:
                pathfindawayplayer();
                break;
            case 2:
                sf::Time time = jailtime.getElapsedTime();
                if (time.asSeconds() >= TimeInPrison) {
                    prison = false;
                }
                draw(window, 150, 150, 255);
                speed = 7;
            }
        }
    }
};
inky inkya;
class bonny {
public:
    sf::Clock jailtime;
    vector <node> path;
    int x = 23;
    int y = 23;
    float PixelstoX = x * multiples;
    float PixelstoY = y * multiples;
    float speed = 1.85;
    float slopex;
    float slopey;
    bool prison;
    void pathfindtoprison() {
        path.erase(path.begin(), path.end());
        AStarPrison(x, y, 15, 14, slopex, slopey, path, maps);
    }
    void pathfindtoplayer() {
        path.erase(path.begin(), path.end());
        AStarBonny(x, y, pacman.playerx, pacman.playery, slopex, slopey, path, maps, inkya.x, inkya.y);
    }
    void pathfindawayplayer() {
        path.erase(path.begin(), path.end());
        AStarRetreat(x, y, pacman.playerx, pacman.playery, slopex, slopey, path, maps);
    }
    void draw(sf::RenderWindow& window, int R, int G, int B) {
        sf::CircleShape ClydeSprite(22, 22);
        ClydeSprite.setFillColor(sf::Color(R, G, B));
        ClydeSprite.setPosition(PixelstoX, PixelstoY);
        window.draw(ClydeSprite);
        for (int i = 1; i < path.size(); i++) {
            sf::Vertex Path[] =
            {
                sf::Vertex(sf::Vector2f(path[i - 1].x * multiples + 22, path[i - 1].y * multiples + 22), sf::Color(ClydeSprite.getFillColor())),
                sf::Vertex(sf::Vector2f(path[i].x * multiples + 22, path[i].y * multiples + 22), sf::Color(ClydeSprite.getFillColor())),
            };
            window.draw(Path, 2, sf::Lines);
        }

    }
    void move(int func,sf::RenderWindow& window) {
        if (prison) {
            func = 2;
        }
        if (path.size() != 0) {
            switch (func) {
            case 0:
                draw(window, 0, 255, 0);
                speed = 1.85;
                if (ghostplayercollision(PixelstoX, PixelstoY)) {
                    window.close();
                }
                break;
            case 1:
                speed = 1;
                if (ghostplayercollision(PixelstoX, PixelstoY)) {
                    jailtime.restart();
                    prison = true;
                }
                break;
            case 2:
                sf::Time time = jailtime.getElapsedTime();
                if (time.asSeconds() >= 15) {
                    prison = false;
                }
                draw(window, 150, 150, 255);
                speed = 7;
            }
            float rad = atan2(path[0].y * multiples - PixelstoY, path[0].x * multiples - PixelstoX);
            slopey = sin(rad);
            slopex = cos(rad);
            PixelstoX += slopex * speed;
            PixelstoY += slopey * speed;
            if (distance(PixelstoX, PixelstoY, path[0].x * multiples, path[0].y * multiples) < speed) {
                x = path[0].x;
                y = path[0].y;
                PixelstoX = path[0].x * multiples;
                PixelstoY = path[0].y * multiples;
                path.erase(path.begin(), path.begin() + 1);
                if (maps[y][x] == 2 || maps[y][x] == 3) {
                    switch (func)
                    {
                    case 0:
                        pathfindtoplayer();
                        break;
                    case 1:
                        pathfindawayplayer();
                        break;
                    case 2:
                        pathfindtoprison();
                        break;
                    }
                }
            }
        }
        else {
            switch (func)
            {
            case 0:
                pathfindtoplayer();
                draw(window, 255, 0, 0);
                speed = 1.75;
                if (ghostplayercollision(PixelstoX, PixelstoY)) {
                    window.close();
                }
            case 1:
                pathfindawayplayer();
                if (ghostplayercollision(PixelstoX, PixelstoY)) {
                    prison = true;
                }
                break;
            case 2:
                sf::Time time = jailtime.getElapsedTime();
                if (time.asSeconds() >= TimeInPrison) {
                    prison = false;
                }
                draw(window, 150, 150, 255);
                speed = 7;
            }
        }
    }
};
bonny bonnya;
class stinky {
public:
    sf::Clock jailtime;
    vector <node> path;
    int x = 1;
    int y = 1;
    float PixelstoX = x * multiples;
    float PixelstoY = y * multiples;
    float speed = 2;
    float slopex;
    float slopey;
    bool prison;
    void pathfindtoprison() {
        path.erase(path.begin(), path.end());
        AStarPrison(x, y, 14, 14, slopex, slopey, path, maps);
    }
    void pathfindtoplayer() {
        path.erase(path.begin(), path.end());
        AStarStinky(x, y, pacman.playerx, pacman.playery, slopex, slopey, path, maps);
    }
    void pathfindawayplayer() {
        path.erase(path.begin(), path.end());
        AStarRetreat(x, y, pacman.playerx, pacman.playery, slopex, slopey, path, maps);
    }
    void draw(sf::RenderWindow& window, int R, int G, int B) {
        sf::CircleShape ClydeSprite(22, 22);
        ClydeSprite.setFillColor(sf::Color(R,G,B));
        ClydeSprite.setPosition(PixelstoX, PixelstoY);
        window.draw(ClydeSprite);
        for (int i = 1; i < path.size(); i++) {
            sf::Vertex Path[] =
            {
                sf::Vertex(sf::Vector2f(path[i - 1].x * multiples + 22, path[i - 1].y * multiples + 22), sf::Color(ClydeSprite.getFillColor())),
                sf::Vertex(sf::Vector2f(path[i].x * multiples + 22, path[i].y * multiples + 22), sf::Color(ClydeSprite.getFillColor())),
            };
            window.draw(Path, 2, sf::Lines);
        }
    }
    void move(int func, sf::RenderWindow& window) {
        if (prison) {
            func = 2;
        }
        if (path.size() != 0) {
            switch (func) {
            case 0:
                draw(window, 255, 0, 255);
                speed = 2;
                if (ghostplayercollision(PixelstoX, PixelstoY)) {
                    window.close();
                }
                break;
            case 1:
                speed = 1;
                if (ghostplayercollision(PixelstoX, PixelstoY)) {
                    jailtime.restart();
                    prison = true;
                }
                break;
            case 2:
                sf::Time time = jailtime.getElapsedTime();
                if (time.asSeconds() >= 15) {
                    prison = false;
                }
                draw(window, 150, 150, 255);
                speed = 7;
            }
            float rad = atan2(path[0].y * multiples - PixelstoY, path[0].x * multiples - PixelstoX);
            slopey = sin(rad);
            slopex = cos(rad);
            PixelstoX += slopex * speed;
            PixelstoY += slopey * speed;
            if (distance(PixelstoX, PixelstoY, path[0].x * multiples, path[0].y * multiples) < speed) {
                x = path[0].x;
                y = path[0].y;
                PixelstoX = path[0].x * multiples;
                PixelstoY = path[0].y * multiples;
                path.erase(path.begin(), path.begin() + 1);
                if (maps[y][x] == 2 || maps[y][x] == 3) {
                    switch (func)
                    {
                    case 0:
                        pathfindtoplayer();
                        break;
                    case 1:
                        pathfindawayplayer();
                        break;
                    case 2:
                        pathfindtoprison();
                        break;
                    }
                }
            }
        }
        else {
            switch (func)
            {
            case 0:
                pathfindtoplayer();
                draw(window, 255, 0, 0);
                speed = 1.75;
                if (ghostplayercollision(PixelstoX, PixelstoY)) {
                    window.close();
                }
            case 1:
                pathfindawayplayer();
                if (ghostplayercollision(PixelstoX, PixelstoY)) {
                    prison = true;
                }
                break;
            case 2:
                sf::Time time = jailtime.getElapsedTime();
                if (time.asSeconds() >= TimeInPrison) {
                    prison = false;
                }
                draw(window, 150, 150, 255);
                speed = 7;
            }
        }
    }
};
stinky stinkya;
