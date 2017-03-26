#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <vector>
#include <stdlib.h>
#include <stdio.h>
#include "tetris.h"

using namespace std;
int tt = 0;

int main(){   
    sf::ContextSettings settings;
    settings.antialiasingLevel  = 0;
    sf::VideoMode video(400,480);
    sf::RenderWindow WindowGame(video, "SFML Tetris++", sf::Style::Default, settings);
    WindowGame.setFramerateLimit(60);

    Tetris tetris(0, 0, 20, 0);
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
    bool GameOver = false;
    while (WindowGame.isOpen()){
        sf::Event event;

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

        int incremento = 0;
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
           incremento = 9;

        back:
        if(tetris.canDown(mapa)){
            y += 1 + incremento;
        }else{
            int delay;
            if(GameOver == true) delay = 5; else delay = 15; 
            y -= (double)(((int)y)%20);
            if (tempo < delay){
                if(WindowGame.pollEvent(event)){
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
                        if(tetris.canMove(mapa, "left")){
                            x -= 20;
                            tempo = 0;
                            goto back;
                        }
                    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
                        if(tetris.canMove(mapa, "right")){
                            x += 20;
                            tempo = 0;
                            goto back;
                        }
                    }
                }
                tempo++;
            } else {
                tempo = 0;
                tetris.addToMap(mapa);
                tetris.Reset();
                MapLineComplete(mapa);

                y = -30;
                x = 100;
            }
        }

        tetris.MoveTetris(x, y);

        system("clear");

        if(!GameOver){
            for(int i = 0; i < mapa->ysize; i++){
                for(int j = 0; j < mapa->xsize; j++){
                    cout << mapa -> map[i][j].valor;
                }
                cout << endl;
            }
            cout << x/20 << " " << (int)y/20 << endl;
        }
        
        if((int)y/20 < 0 && tetris.canDown(mapa) == false){
            system("clear");
            GameOver = true;
            cout << "Game Over!" << endl;
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
                WindowGame.close();
        }

        
        WindowGame.clear();

        for(int i = 0; i < mapa -> ysize; i++){
            for(int j = 0; j < mapa -> xsize; j++){
                if(mapa -> map[i][j].valor == '#'){
                    if(tetris.canDown(mapa) && tempo == 0)
                        mapRect[i][j].setFillColor(mapa -> map[i][j].cor);
                    else
                        mapRect[i][j].setFillColor(tetris.getColor());
                    
                    WindowGame.draw(mapRect[i][j]);
                }
            }
        }
    
        for(int i = 0; i < 3; i++){
            for(int j = 0; j < 3; j++){
                if(tetris.colorTrue[i][j])
                    WindowGame.draw(tetris.Rect[i][j]);
            }
        }
        WindowGame.display();
    }
    return 0;
}