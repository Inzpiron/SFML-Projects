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
    int menu = 0;
    sf::ContextSettings settings;
    settings.antialiasingLevel  = 8;
    sf::VideoMode video(480,640);
    sf::RenderWindow WindowGame(video, "SFML TETRIS++", sf::Style::Default, settings);
    WindowGame.setFramerateLimit(60);

    Tetris tetris(200, 240, 20, 0);
    Tetris projecao(200, 240, 20, 0);

    projecao.projecao = true;
    tetris.SetTetris();
    Map * mapa = newMap(24, 32);

    sf::RectangleShape mapRect[32][24];
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
    bool checkLineRemove = false;
    
    sf::Event event;
    sf::Font font;
    font.loadFromFile("Monofett.ttf");
    
    TetrisText TitleText(17, 100, "Tetris++", font, 100, sf::Color::Blue);
    TitleText.setPosition((480-TitleText.Width)/2.0, 100);
    
    vector< vector<TetrisText> > MenuText (3);// = MenuText(17, 30, "Tetris++", font, 100);
    
    int pos = 230;
    for(int i = 0; i < 3; i++){
        string TextOfButton = "";
        switch(i){
            case 0: TextOfButton = "Play"; break;
            case 1: TextOfButton = "Draw"; break;
            case 2: TextOfButton = "Quit"; break;
        }

        string aux1 = "*" + TextOfButton + "*";
        TetrisText aux(80, pos + 10, TextOfButton, font, 96, sf::Color::Red);
        TetrisText aux2(90, pos, aux1, font, 96, sf::Color::Red);
        sf::Color corAux = sf::Color::White; corAux.a = 200;
        sf::Color corAux1 = corAux; corAux1.a = 50;
        MenuText[i].push_back(TetrisText((480 - aux.Width)/2.0 + 7, pos, TextOfButton, font, 90, corAux1)); //Botão não selecionado
        MenuText[i].push_back(TetrisText((480 - aux2.Width)/2.0, pos, aux1, font, 96, corAux)); //Botao selecionado
        pos += MenuText[i][1].Height + 3;
    }

    int menuOpc = 0;

    while (WindowGame.isOpen()){
        if(menu == 0){
            TitleText.slideEffect();
            while (WindowGame.pollEvent(event)){
                if(event.type == sf::Event::KeyPressed){   
                    if(event.key.code == sf::Keyboard::Return){
                        switch(menuOpc){
                            case 0: menu = 1; break;
                            case 2: WindowGame.close(); break;
                        }
                    }

                    if(event.key.code == sf::Keyboard::Up){
                        if(menuOpc > 0)
                            menuOpc--;
                    }

                    if(event.key.code == sf::Keyboard::Down){
                        if(menuOpc < 2)
                            menuOpc++;   
                    }
                }
                if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                    WindowGame.close();
            }



            WindowGame.clear();
            TitleText.draw(WindowGame);
            for(int i = 0; i < (int) MenuText.size(); i++){
                if(menuOpc == i){
                    MenuText[i][1].setColor(TitleText.corAtual);
                    MenuText[i][1].draw(WindowGame);
                }else{
                    //MenuText[i][0].setColor(TitleText.corAtual);
                    MenuText[i][0].draw(WindowGame);
                }
            }
            WindowGame.display();

        }else{
            sf::Event event;
            if(tetris.canDown(mapa)){
                while (WindowGame.pollEvent(event)){
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
                        if(tetris.canMove(mapa, "left")){
                            x -= 20;
                            //projecao.posy = 0;
                        }
                    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
                        if(tetris.canMove(mapa, "right")){
                            x += 20;
                            //projecao.posy = 0;
                        }
                    }
                    
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
                        tetris.setPecaRot(mapa);
                        //projecao.posy = 0;
                    }

                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
                        x = projecao.posx;
                        y = projecao.posy - 2;
                        tempo = 30;
                    }

                    if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                        WindowGame.close();
                }
            }
            int incremento = 0;
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
               incremento = 8;

            back:
            if(tetris.canDown(mapa)){
                y += 2 + incremento;
                if(!tetris.canDown(mapa)){
                    y -= (double)(((int)y)%20);
                    tetris.MoveTetris(x, y);
                }
                projecao.size = tetris.size;
                projecao.posx = x;
                projecao.rot  = tetris.rot;
                projecao.type = tetris.type;
                projecao.posy = tetris.posy;
                while(projecao.canDown(mapa)){
                    projecao.posy += 20;
                    //cout << projecao.posy << endl;
                }
                projecao.posy -= (double)(((int)projecao.posy)%20);
            }else{
                int delay;
                if(GameOver == true) delay = 10; else delay = 20; 
                y -= (double)(((int)y)%20);
                tetris.MoveTetris(x, y);
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
                    projecao.Reset();
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
                if(timeToDelete > 3){
                    //cout << lineToRemove << endl;
                    deleteCompleteLine(mapa, lineToRemove);

                    if(checkMapLineComplete(mapa) == -1){
                        tempo = 0;
                        checkLineRemove = false;
                        timeToDelete = 0;
                    }
                }
            }

            tetris.MoveTetris(x, y);
            projecao.MoveTetris(projecao.posx, projecao.posy);
            //system("clear");

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
                        if(!GameOver)
                            mapRect[i][j].setFillColor(mapa -> map[i][j].cor);
                        else
                            mapRect[i][j].setFillColor(tetris.getColor());

                        WindowGame.draw(mapRect[i][j]);
                    }
                }
            }
            if(!tetris.canDown(mapa)){y -= (double)(((int)y)%20); tetris.MoveTetris(x, y);}
            tetris.draw(WindowGame);
            if(projecao.posy != 0 && tetris.canDown(mapa))
                projecao.draw(WindowGame);
            WindowGame.display();
        }
    }
    return 0;
}