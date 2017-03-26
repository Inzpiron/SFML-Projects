#include <cstdio>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <string>
using namespace std;

typedef struct{
    sf::Color cor;
    char valor;
}Pixel;

typedef struct{
    Pixel map[24][12];
    int xsize;
    int ysize;
}Map;

Map * newMap(int xsize, int ysize);
void MapLineComplete(Map * m);
class Tetris{
    private:
        int posx, vel;
        double posy;
        int rot;
        int type;
        int size;
        sf::Color color[5] = {sf::Color::Red, sf::Color::Green, sf::Color::Yellow, sf::Color::Blue + sf::Color::Red, sf::Color::Blue};
        string peca[5][4][3] = { { {" # ","###","   "},  {" # "," ##"," # "} , {"   ","###"," # "}, {" # ","## "," # "} },
                                 { {"  #","  #","  #"},  {"###","   ","   "} , {"  #","  #","  #"}, {"###","   ","   "} },
                                 { {" ##","## ","   "},  {"#  ","## "," # "} , {" ##","## ","   "}, {"#  ","## "," # "} },
                                 { {" ##"," ##","   "},  {" ##"," ##","   "} , {" ##"," ##","   "}, {" ##"," ##","   "} },
                                 { {"#  ","#  ","## "},  {"   ","  #","###"} , {"## "," # "," # "}, {"   ","###","#  "} } };

    public:
        sf::RectangleShape Rect[3][3];
        sf::Color getColor();
        bool colorTrue[3][3];
    	Tetris(int posx, double posy, int size, int type);
    	void SetTetris();
        int * Limitant(string dir);
    	void MoveTetris(int posx, double posy);
    	bool canDown(Map * m);
        bool canMove(Map * m, string direction);
    	sf::RectangleShape teste(int i, int j);
        void setPecaRot(Map * m);
        void addToMap(Map * m);
        void Reset();
        char getPeca(int type, int rot, int i, int j);
};