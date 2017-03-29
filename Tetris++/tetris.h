#include <cstdio>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <string>
#include <vector>
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
int checkMapLineComplete(Map * m);
void deleteCompleteLine(Map * m, int line);

class TetrisText{
    private:
        int x, y, fsize;
        string realText;
        sf::Font font;
        sf::Color cor;
        string str;
    public:
        TetrisText(int x, int y, string str, sf::Font font, int size);
        void draw(sf::RenderWindow &WindowGame);
};

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
                                 { {"## ","## ","   "},  {"## ","## ","   "} , {"## ","## ","   "}, {"## ","## ","   "} },
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
        void draw(sf::RenderWindow &WindowGame);
};