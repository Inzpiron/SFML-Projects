#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include "tetris.h"
#include <string.h>

using namespace std;

Map * newMap(int xsize, int ysize){
	Map * m = (Map *) malloc(sizeof(Map));
	m -> xsize = xsize;
	m -> ysize = ysize;

	for(int i = 0; i < ysize; i++){
		for(int j = 0; j < xsize; j++){
			m -> map[i][j].valor = '-';
			m -> map[i][j].cor = sf::Color::Black;
		}
	}

	return m;
}

int checkMapLineComplete(Map * m){
	int i  = m->ysize - 1;
	bool check0 = false;
	int pos = -20;
	for(; i >= 0; i--){
		bool check = true;
		for(int j = 0; j < m->xsize; j++){
			if(m -> map[i][j].valor == '-') 
				check = false; 
		}

		//SELECT RIGHT LINE TO ERASE
		if(check){
			for(int r = 0; r < m->xsize; r++){
				m -> map[i][r].cor = sf::Color::White;
			}
			if(check0 == false){pos = i;check0 = true;}
		}
	}

	if(check0 && pos != -20)
		return pos;

	return -1;
}

void deleteCompleteLine(Map * m, int line){
	for(int k = line; k > 0; k--){
		for(int l = 0; l < m->xsize; l++)
			m->map[k][l] = m->map[k-1][l];
	}
	//cout << "deletei" << endl;
}

TetrisText::TetrisText(int posx, int posy, string str, sf::Font font, int fsize, sf::Color cor){
	this->conf = new LetraConfig[str.size()];
	this->font = font;
	this->str = str;
	this->cor = cor;
	this->posx = posx; this->posy = posy;
	sf::Text letra[this->str.size()];
	this -> Width = 0;

	for(int i = 0; i <  (int) this->str.size(); i++){
		string aux = "";
		aux += str[i];

		this->conf[i].x     = this->posx + this->Width;
		this->conf[i].y     = this->posy;
		this->conf[i].color = this->cor;
		this->conf[i].fsize = fsize;

		letra[i].setCharacterSize(this->conf[i].fsize);
		letra[i].setFont(this->font);
		letra[i].setString(aux);
		letra[i].setFillColor(this->conf[i].color);

		this -> Width += letra[i].getLocalBounds().width;
		this -> Height = letra[0].getLocalBounds().height;
	}

	//SLIDE EFFECT AUX Var
		this -> check = false;
		this -> pos = 0;
		this -> corPos = 0;
}

void TetrisText::setPosition(int x, int y){
	this -> posx = x;
	this -> posy = y;
}

void TetrisText::setColor(sf::Color cor){
	this->cor = cor;

	for(int i = 0; i < this->str.size(); i++)
		this->conf[i].color = cor; 
}

void TetrisText::draw(sf::RenderWindow &WindowGame){
	sf::Text letra[this->str.size()];
	for(int i = 0; i < (int) this->str.size(); i++){
		//cout << this->str << endl;
		string aux = "";
		aux += str[i];
		letra[i].setCharacterSize(this->conf[i].fsize);
		letra[i].setFont(this->font);
		letra[i].setString(aux);
		letra[i].setFillColor(this->conf[i].color);
		letra[i].setOrigin(0, ((int)this->Height)/2);
	}

	for(int i = 0; i < (int) this->str.size(); i++){
		letra[i].setPosition(this->conf[i].x, this->conf[i].y);
		WindowGame.draw(letra[i]);
	}
}

void TetrisText::slideEffect(){
	sf::Color CorAux[5] = {sf::Color::Green, sf::Color::Red, sf::Color::Yellow, sf::Color::Blue};
	corAtual = CorAux[corPos];
	for(int i = 0; i < ((int) this->str.size()); i++){
		if(this->pos != i){
			if(this->conf[i].y < posy){
				this->conf[i].y += 2;
			}
		}
	}

	if(this->conf[this->pos].y > posy-20 && this->check == false){
		this->conf[this->pos].y -= 2;
		this->conf[this->pos].color = CorAux[corPos];
	}else check = true;

	if(check == true){
		//this->conf[this->pos].color = sf::Color::White;
		//this->conf[this->pos].y = this->posy;
		(++this->pos) %= this->str.size();
		this->check = false;
	}

	if(this->pos == 0 && check == false && this->conf[this->pos].y == posy)
		(++corPos) %= 4;
}