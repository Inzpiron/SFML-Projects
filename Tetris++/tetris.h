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
    Pixel map[32][24];
    int xsize;
    int ysize;
}Map;

Map * newMap(int xsize, int ysize);
int checkMapLineComplete(Map * m);
void deleteCompleteLine(Map * m, int line);

typedef struct{
    int x, y, fsize;
    sf::Color color;
}LetraConfig;

class TetrisText{
    private:
        int posx, posy;
        sf::Font font;
        sf::Color cor;
        LetraConfig * conf;
        string str;

        //Slide effect aux vars:
        bool check;
        int pos;
    public:
        double Width, Height;
        TetrisText(int posx, int posy, string str, sf::Font font, int size);
        void setPosition(int x, int y);
        void draw(sf::RenderWindow &WindowGame);
        void slideEffect();
};

class Tetris{
    private:
        /*int posx, vel;
        double posy;
        int rot;
        int type;
        int size;*/
        sf::Color color[5] = {sf::Color::Red, sf::Color::Green, sf::Color::Yellow, sf::Color::Blue + sf::Color::Red, sf::Color::Blue};
        string peca[5][4][4] = { { {" #  ","### ","    ","    "},  {" #  "," ## "," #  ","    "}, {"    ","### "," #  ","    "}, {" #  ","##  "," #  ","    "} },
                                 { {"  # ","  # ","  # ","  # "},  {"    ","    ","####","    "}, {"  # ","  # ","  # ","  # "}, {"    ","    ","####","    "} },
                                 { {" ## ","##  ","    ","    "},  {"#   ","##  "," #  ","    "}, {" ## ","##  ","    ","    "}, {"#   ","##  "," #  ","    "} },
                                 { {"##  ","##  ","    ","    "},  {"##  ","##  ","    ","    "}, {"##  ","##  ","    ","    "}, {"##  ","##  ","    ","    "} },
                                 { {"#   ","#   ","##  ","    "},  {"    ","  # ","### ","    "}, {"##  "," #  "," #  ","    "}, {"    ","### ","#   ","    "} } };

    public:
        bool projecao;
        int posx, posy, rot, type, size, velo;
        sf::RectangleShape Rect[4][4];
        sf::Color getColor();
        bool colorTrue[4][4];
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