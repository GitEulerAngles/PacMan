#include <iostream>
#include <vector>
using namespace std;

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
float distance(float x1, float y1, float x2, float y2) {
    return abs(sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2)));
}
node LowestNode(vector<node>& nodes) {
    node lowest = nodes[0];
    for (int i = 1; i < nodes.size(); i++) {
        if (nodes[i].fcost < lowest.fcost) {
            lowest = nodes[i];
        }
    }
    return lowest;
}
node HighestNode(vector<node>& nodes) {
    node highest = nodes[0];
    for (int i = 1; i < nodes.size(); i++) {
        if (nodes[i].fcost > highest.fcost) {
            highest = nodes[i];
        }
    }
    return highest;
}
bool InArray(vector<node>& vector, int nx, int ny) {
    for (int i = 0; i < vector.size(); i++) {
        if (vector[i].x == nx && vector[i].y == ny) {
            return true;
        }
    }
    return false;
}
void AStarClyde(int startx, int starty, int endx, int endy, float slopex, float slopey, vector<node>& path, int maps[31][28], int PacmanSlopex, int PacmanSlopey) {
    for (int i = 0; i < 6; i++) {
        int y = endy + (PacmanSlopey * (5 - i));
        int x = endx + (PacmanSlopex * (5 - i));
        if (maps[y][x] != 1 && y < 31 && y > 0 && x < 28 && x > 0) {
            endx += PacmanSlopex * (5-i);
            endy += PacmanSlopey * (5-i);
            break;
        }
    }
    vector<node> open;
    vector<node> closed;
    node beginning;
    beginning.x = startx;
    beginning.y = starty;
    beginning.scost = distance(beginning.x, beginning.y, startx, starty);
    beginning.ecost = distance(beginning.x, beginning.y, endx, endy);
    beginning.fcost = beginning.ecost + beginning.scost;
    beginning.add(open);
    while (true) {
        node* current = &LowestNode(open);
        current->remove(open);
        current->add(closed);
        if (current->x == endx && current->y == endy) {
            int currentx = current->x;
            int currenty = current->y;
            while (currentx != startx || currenty != starty) {
                for (int i = 0; i < closed.size(); i++) {
                    if (closed[i].x == currentx && closed[i].y == currenty) {
                        path.insert(path.begin(), closed[i]);
                        currentx = closed[i].parentx;
                        currenty = closed[i].parenty;
                        break;
                    }
                }
            }
            return;
        }
        vector< vector < int > > neighbors;
        if (current->x == startx && current->y == starty) {
            int neighborcontrol[4][2] = { {0,1}, {1,0}, {0,-1}, {-1,0} };
            for (int i = 0; i < 4; i++) {
                int roundedslopex = slopex;
                int roundedslopey = slopey;
                if (neighborcontrol[i][1] == -roundedslopey && neighborcontrol[i][0] == -roundedslopex) {
                    continue;
                }
                else {
                    neighbors.insert(neighbors.begin(), { neighborcontrol[i][0], neighborcontrol[i][1] });
                }
            }
        }
        else {
            neighbors = { {0,1}, {1,0}, {0,-1}, {-1,0} };
        }
        for (int i = 0; i < neighbors.size(); i++) {
            node neighbor;
            neighbor.x = current->x + neighbors[i][0];
            neighbor.y = current->y + neighbors[i][1];
            if (maps[neighbor.y][neighbor.x] == 1 || InArray(closed, neighbor.x, neighbor.y)) {
                continue;
            }
            if (InArray(open, neighbor.x, neighbor.y) == false) {
                neighbor.scost = distance(neighbor.x, neighbor.y, startx, starty);
                neighbor.ecost = distance(neighbor.x, neighbor.y, endx, endy);
                neighbor.fcost = neighbor.ecost + neighbor.scost;
                neighbor.parentx = current->x;
                neighbor.parenty = current->y;
                neighbor.add(open);
            }
        }
        if (open.size() == 0) {
            break;
        }
    }
}
void AStarBonny(int startx, int starty, int endx, int endy, float slopex, float slopey, vector<node>& path, int maps[31][28], int PosInkyX, int PosInkyY) {
    vector<node> open;
    vector<node> closed;
    node beginning;
    beginning.x = startx;
    beginning.y = starty;
    beginning.scost = distance(beginning.x, beginning.y, startx, starty);
    beginning.ecost = distance(beginning.x, beginning.y, endx, endy);
    beginning.fcost = (beginning.ecost + beginning.scost) - distance(startx,starty, PosInkyX, PosInkyY);
    beginning.add(open);
    while (true) {
        node* current = &LowestNode(open);
        current->remove(open);
        current->add(closed);

        if (current->x == endx && current->y == endy) {
            int currentx = current->x;
            int currenty = current->y;
            while (currentx != startx || currenty != starty) {
                for (int i = 0; i < closed.size(); i++) {
                    if (closed[i].x == currentx && closed[i].y == currenty) {
                        path.insert(path.begin(), closed[i]);
                        currentx = closed[i].parentx;
                        currenty = closed[i].parenty;
                        break;
                    }
                }
            }
            return;
        }
        vector< vector < int > > neighbors;
        if (current->x == startx && current->y == starty) {
            int neighborcontrol[4][2] = { {0,1}, {1,0}, {0,-1}, {-1,0} };
            for (int i = 0; i < 4; i++) {
                int roundedslopex = slopex;
                int roundedslopey = slopey;
                if (neighborcontrol[i][1] == -roundedslopey && neighborcontrol[i][0] == -roundedslopex) {
                    continue;
                }
                else {
                    neighbors.insert(neighbors.begin(), { neighborcontrol[i][0], neighborcontrol[i][1] });
                }
            }
        }
        else {
            neighbors = { {0,1}, {1,0}, {0,-1}, {-1,0} };
        }
        for (int i = 0; i < neighbors.size(); i++) {
            node neighbor;
            neighbor.x = current->x + neighbors[i][0];
            neighbor.y = current->y + neighbors[i][1];
            if (maps[neighbor.y][neighbor.x] == 1 || InArray(closed, neighbor.x, neighbor.y)) {
                continue;
            }
            if (InArray(open, neighbor.x, neighbor.y) == false) {
                neighbor.scost = distance(neighbor.x, neighbor.y, startx, starty);
                neighbor.ecost = distance(neighbor.x, neighbor.y, endx, endy);
                neighbor.fcost = (neighbor.ecost + neighbor.scost) - distance(neighbor.x, neighbor.y, PosInkyX, PosInkyY);
                neighbor.parentx = current->x;
                neighbor.parenty = current->y;
                neighbor.add(open);
            }
        }
        if (open.size() == 0) {
            break;
        }
    }
}
void AStarInky(int startx, int starty, int endx, int endy, float slopex, float slopey, vector<node>& path, int maps[31][28]) {
    vector<node> open;
    vector<node> closed;
    node beginning;
    beginning.x = startx;
    beginning.y = starty;
    beginning.scost = distance(beginning.x, beginning.y, startx, starty);
    beginning.ecost = distance(beginning.x, beginning.y, endx, endy);
    beginning.fcost = beginning.ecost + beginning.scost;
    beginning.add(open);
    while (true) {
        node* current = &LowestNode(open);
        current->remove(open);
        current->add(closed);
        if (current->x == endx && current->y == endy) {
            int currentx = current->x;
            int currenty = current->y;
            while (currentx != startx || currenty != starty) {
                for (int i = 0; i < closed.size(); i++) {
                    if (closed[i].x == currentx && closed[i].y == currenty) {
                        path.insert(path.begin(), closed[i]);
                        currentx = closed[i].parentx;
                        currenty = closed[i].parenty;
                        break;
                    }
                }
            }
            return;
        }
        vector< vector < int > > neighbors;
        if (current->x == startx && current->y == starty) {
            int neighborcontrol[4][2] = { {0,1}, {1,0}, {0,-1}, {-1,0} };
            for (int i = 0; i < 4; i++) {
                int roundedslopex = slopex;
                int roundedslopey = slopey;
                if (neighborcontrol[i][1] == -roundedslopey && neighborcontrol[i][0] == -roundedslopex) {
                    continue;
                }
                else {
                    neighbors.insert(neighbors.begin(), { neighborcontrol[i][0], neighborcontrol[i][1] });
                }
            }
        }
        else {
            neighbors = { {0,1}, {1,0}, {0,-1}, {-1,0} };
        }
        for (int i = 0; i < neighbors.size(); i++) {
            node neighbor;
            neighbor.x = current->x + neighbors[i][0];
            neighbor.y = current->y + neighbors[i][1];
            if (maps[neighbor.y][neighbor.x] == 1 || InArray(closed, neighbor.x, neighbor.y)) {
                continue;
            }
            if (InArray(open, neighbor.x, neighbor.y) == false) {
                neighbor.scost = distance(neighbor.x, neighbor.y, startx, starty);
                neighbor.ecost = distance(neighbor.x, neighbor.y, endx, endy);
                neighbor.fcost = neighbor.ecost + neighbor.scost + current->fcost;
                neighbor.parentx = current->x;
                neighbor.parenty = current->y;
                neighbor.add(open);
            }
        }
        if (open.size() == 0) {
            break;
        }
    }
}
void AStarStinky(int startx, int starty, int endx, int endy, float slopex, float slopey, vector<node>& path, int maps[31][28]) {
    vector<node> open;
    vector<node> closed;
    node beginning;
    beginning.x = startx;
    beginning.y = starty;
    beginning.scost = distance(beginning.x, beginning.y, startx, starty);
    beginning.ecost = distance(beginning.x, beginning.y, endx, endy);
    beginning.fcost = beginning.ecost + beginning.scost;
    beginning.add(open);
    while (true) {
        node* current = &LowestNode(open);
        current->remove(open);
        current->add(closed);
        if (current->x == endx && current->y == endy) {
            int currentx = current->x;
            int currenty = current->y;
            while (currentx != startx || currenty != starty) {
                for (int i = 0; i < closed.size(); i++) {
                    if (closed[i].x == currentx && closed[i].y == currenty) {
                        path.insert(path.begin(), closed[i]);
                        currentx = closed[i].parentx;
                        currenty = closed[i].parenty;
                        break;
                    }
                }
            }
            return;
        }
        vector< vector < int > > neighbors;
        if (current->x == startx && current->y == starty) {
            int neighborcontrol[4][2] = { {0,1}, {1,0}, {0,-1}, {-1,0} };
            for (int i = 0; i < 4; i++) {
                int roundedslopex = slopex;
                int roundedslopey = slopey;
                if (neighborcontrol[i][1] == -roundedslopey && neighborcontrol[i][0] == -roundedslopex) {
                    continue;
                }
                else {
                    neighbors.insert(neighbors.begin(), { neighborcontrol[i][0], neighborcontrol[i][1] });
                }
            }
        }
        else {
            neighbors = { {0,1}, {1,0}, {0,-1}, {-1,0} };
        }
        for (int i = 0; i < neighbors.size(); i++) {
            node neighbor;
            neighbor.x = current->x + neighbors[i][0];
            neighbor.y = current->y + neighbors[i][1];
            if (maps[neighbor.y][neighbor.x] == 1 || InArray(closed, neighbor.x, neighbor.y)) {
                continue;
            }
            if (InArray(open, neighbor.x, neighbor.y) == false) {
                neighbor.scost = distance(neighbor.x, neighbor.y, startx, starty);
                neighbor.ecost = distance(neighbor.x, neighbor.y, endx, endy);
                neighbor.fcost = neighbor.ecost + neighbor.scost + current->fcost;
                neighbor.parentx = current->x;
                neighbor.parenty = current->y;
                neighbor.add(open);
            }
        }
        if (open.size() == 0) {
            break;
        }
    }
}
void AStarPrison(int startx, int starty, int endx, int endy, float slopex, float slopey, vector<node>& path, int maps[31][28]) {
    vector<node> open;
    vector<node> closed;
    node beginning;
    beginning.x = startx;
    beginning.y = starty;
    beginning.scost = distance(beginning.x, beginning.y, startx, starty);
    beginning.ecost = distance(beginning.x, beginning.y, endx, endy);
    beginning.fcost = beginning.ecost + beginning.scost;
    beginning.add(open);
    while (true) {
        node* current = &LowestNode(open);
        current->remove(open);
        current->add(closed);
        if (current->x == endx && current->y == endy) {
            int currentx = current->x;
            int currenty = current->y;
            while (currentx != startx || currenty != starty) {
                for (int i = 0; i < closed.size(); i++) {
                    if (closed[i].x == currentx && closed[i].y == currenty) {
                        path.insert(path.begin(), closed[i]);
                        currentx = closed[i].parentx;
                        currenty = closed[i].parenty;
                        break;
                    }
                }
            }
            return;
        }
        vector< vector < int > > neighbors;
        if (current->x == startx && current->y == starty) {
            int neighborcontrol[4][2] = { {0,1}, {1,0}, {0,-1}, {-1,0} };
            for (int i = 0; i < 4; i++) {
                int roundedslopex = slopex;
                int roundedslopey = slopey;
                if (neighborcontrol[i][1] == -roundedslopey && neighborcontrol[i][0] == -roundedslopex) {
                    continue;
                }
                else {
                    neighbors.insert(neighbors.begin(), { neighborcontrol[i][0], neighborcontrol[i][1] });
                }
            }
        }
        else {
            neighbors = { {0,1}, {1,0}, {0,-1}, {-1,0} };
        }
        for (int i = 0; i < neighbors.size(); i++) {
            node neighbor;
            neighbor.x = current->x + neighbors[i][0];
            neighbor.y = current->y + neighbors[i][1];
            if (maps[neighbor.y][neighbor.x] == 1 || InArray(closed, neighbor.x, neighbor.y)) {
                continue;
            }
            if (InArray(open, neighbor.x, neighbor.y) == false) {
                neighbor.scost = distance(neighbor.x, neighbor.y, startx, starty);
                neighbor.ecost = distance(neighbor.x, neighbor.y, endx, endy);
                neighbor.fcost = neighbor.ecost + neighbor.scost + current->fcost;
                neighbor.parentx = current->x;
                neighbor.parenty = current->y;
                neighbor.add(open);
            }
        }
        if (open.size() == 0) {
            break;
        }
    }
}

void AStarRetreat(int startx, int starty, int PacManX, int PacManY, float slopex, float slopey, vector<node>& path, int maps[31][28]) {
    vector<node> open;
    vector<node> closed; 
    node beginning;
    beginning.x = startx;
    beginning.y = starty;
    beginning.add(open);
    int count = 0;
    while (true) {
        count++;
        node* current = &HighestNode(open);
        current->remove(open);
        current->add(closed);
        if (count >= 10) {
            int currentx = current->x;
            int currenty = current->y;
            while (currentx != startx || currenty != starty) {
                for (int i = 0; i < closed.size(); i++) {
                    if (closed[i].x == currentx && closed[i].y == currenty) {
                        path.insert(path.begin(), closed[i]);
                        currentx = closed[i].parentx;
                        currenty = closed[i].parenty;
                        break;
                    }
                }
            }
            return;
        }
        vector< vector < int > > neighbors;
        if (current->x == startx && current->y == starty) {
            int neighborcontrol[4][2] = { {0,1}, {1,0}, {0,-1}, {-1,0} };
            for (int i = 0; i < 4; i++) {
                int roundedslopex = slopex;
                int roundedslopey = slopey;
                if (neighborcontrol[i][1] == -roundedslopey && neighborcontrol[i][0] == -roundedslopex) {
                    continue;
                }
                else {
                    neighbors.insert(neighbors.begin(), { neighborcontrol[i][0], neighborcontrol[i][1] });
                }
            }
        }
        else {
            neighbors = { {0,1}, {1,0}, {0,-1}, {-1,0} };
        }
        for (int i = 0; i < neighbors.size(); i++) {
            node neighbor;
            neighbor.x = current->x + neighbors[i][0];
            neighbor.y = current->y + neighbors[i][1];
            if (maps[neighbor.y][neighbor.x] == 1 || InArray(closed, neighbor.x, neighbor.y)) {
                continue;
            }
            if (InArray(open, neighbor.x, neighbor.y) == false) {
                neighbor.fcost = distance(neighbor.x, neighbor.y, PacManX, PacManY);
                neighbor.parentx = current->x;
                neighbor.parenty = current->y;
                neighbor.add(open);
            }
        }
        if (open.size() == 0) {
            break;
        }
    }
}
