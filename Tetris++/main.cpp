#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <vector>
#include <stdlib.h>
#include <stdio.h>
#include "tetris.h"
//CASA
using namespace std;
int tt = 0;

int main(){   
    int menu = 1;
    sf::ContextSettings settings;
    settings.antialiasingLevel  = 8;
    sf::VideoMode video(480,640);
    sf::RenderWindow WindowGame(video, "SFML Tetris++", sf::Style::Default, settings);
    WindowGame.setFramerateLimit(60);

    Tetris tetris(200, 240, 20, 0);
    tetris.SetTetris();
    Map * mapa = newMap(12, 24);

    sf::RectangleShape mapRect[24][12];
    for(int i = 0; i < mapa -> ysize; i++){
        for(int j = 0; j < mapa -> xsize; j++){
            mapRect[i][j].setPosition(j * 20, i * 20);
            mapRect[i][j].setSize(sf::Vector2f(20,20));
            mapRect[i][j].setFillColor(sf::Color::Green);
        }
    }

    int x = 100, tempo = 0; double y = -30;
    int timeToDelete = 0;
    int lineToRemove = -1;
    int movment = 0;
    bool GameOver = false;
    bool checkLR = false;
    bool checkLineRemove = false;
    while (WindowGame.isOpen()){
        if(menu == 0){ 
            sf::Event event;
            sf::Font font;
            font.loadFromFile("Monofett.ttf");
            TetrisText PlayButton(0, 0, "Tetris", font, 48);
            
            while (WindowGame.pollEvent(event)){
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){}
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){}

                if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                    WindowGame.close();
            }

            WindowGame.clear();
            PlayButton.draw(WindowGame);
            WindowGame.display();

        }else{
            sf::Event event;
            if(tetris.canDown(mapa)){
                while (WindowGame.pollEvent(event)){
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
                        if(tetris.canMove(mapa, "left"))
                            x -= 20;
                    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
                        if(tetris.canMove(mapa, "right"))
                            x += 20;
                    }
                    
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
                        tetris.setPecaRot(mapa);

                    if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                        WindowGame.close();
                }
            }
            int incremento = 0;
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
               incremento = 9;

            back:
            if(tetris.canDown(mapa)){
                y += 1 + incremento;
            }else{
                int delay;
                if(GameOver == true) delay = 5; else delay = 20; 
                y -= (double)(((int)y)%20);
                if (tempo < delay){
                    while(WindowGame.pollEvent(event)){
                        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
                            if(tetris.canMove(mapa, "left")){
                                x -= 20;
                                tempo = 0;
                                movment++;
                                goto back;
                            }
                        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
                            if(tetris.canMove(mapa, "right")){
                                x += 20;
                                tempo = 0;
                                movment++;
                                goto back;
                            }
                        } 
                    }

                    if(movment > 3)
                        tempo = delay;
                    tempo++;
                } else {
                    movment = 0;
                    tetris.addToMap(mapa);
                    tetris.Reset();
                    x = 100;
                    y = -30;
        
                    if(checkMapLineComplete(mapa) != -1){
                        checkLineRemove = true;
                        lineToRemove = checkMapLineComplete(mapa);
                    }else
                        tempo = 0;
                }
            }

            if(checkLineRemove){
                timeToDelete++;
                if(timeToDelete > 50){
                    cout << lineToRemove << endl;
                    deleteCompleteLine(mapa, lineToRemove);

                    if(checkMapLineComplete(mapa) == -1){
                        tempo = 0;
                        checkLineRemove = false;
                        timeToDelete = 0;
                    }
                }

                cout << timeToDelete << endl;
            }


            tetris.MoveTetris(x, y);

            //system("clear");

            if(!GameOver){
                for(int i = 0; i < mapa->ysize; i++){
                    for(int j = 0; j < mapa->xsize; j++){
                        //cout << mapa -> map[i][j].valor;
                    }
                    //cout << endl;
                }
                //cout << x/20 << " " << (int)y/20 << endl;
            }
            
            if((int)y/20 < 0 && tetris.canDown(mapa) == false){
                //system("clear");
                GameOver = true;
                cout << "Game Over!" << endl;
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
                    WindowGame.close();
            }

            
            WindowGame.clear();
            //system("tput reset");
            for(int i = 0; i < mapa -> ysize; i++){
                for(int j = 0; j < mapa -> xsize; j++){
                    if(mapa -> map[i][j].valor == '#'){
                        mapRect[i][j].setFillColor(mapa -> map[i][j].cor);
                        WindowGame.draw(mapRect[i][j]);
                    }
                }
            }
        
            tetris.draw(WindowGame);
            WindowGame.display();
        }
    }
    return 0;
}