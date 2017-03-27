#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include "tetris.h"
#include <string.h>

Tetris::Tetris(int posx, double posy, int size, int type){
	this -> posx = posx;
	this -> posy = posy;
	this -> type = type;
    this -> rot  = 0;
    this -> size = size;
}

void Tetris::SetTetris(){
	for(int i = 0; i < 3; i++){
		for(int j = 0; j < 3; j++){
			Rect[i][j].setSize(sf::Vector2f(20,20));
			if(this -> peca[this -> type][this -> rot][j][i] != '#'){
				Rect[i][j].setFillColor(sf::Color::Black);
			}else{
				Rect[i][j].setFillColor(this -> color[this -> type]);
			}
		}
	}
}

void Tetris::setPecaRot(Map * m){
	bool CanI = true;
	int prox = this->rot + 1;
	if(prox >= 4)
		prox = 0;
	for(int i = 0; i < 3; i++){
		for(int j = 0; j < 3; j++){
			if(this -> peca[this->type][prox][i][j] == '#'){
				//if (m -> map[]){CanI = false; break;}
				if (m -> map[(int)(this->posy/20)+i][(int)(this->posx/20)+j].valor != '-')
					CanI = false;
			}
		}
	}

	if(this -> posx < 0){
		int l = abs(this->posx/20);	
		for(int i = 0; i < 3; i++){
			for(int j = 0; j < l; j++){
				if(this->peca[this->type][prox][i][j] == '#')
					CanI = false;
			}
		}
	}

	int k = 3-(m->xsize - (int)posx/20);
	if(k > 0){
		for(int i = 0; i < 3; i++){
			for(int j = k-1; j >= 0; j--){
				if(this->peca[this->type][prox][i][j] == '#')
					CanI = false;
			}
		}
	}

	if(CanI){
    	this -> rot = prox;
    	Tetris::SetTetris();
	}
}

void Tetris::MoveTetris(int posx, double posy){
	this->posx = posx;
	this->posy = posy;

	for(int i = 0; i < 3; i++){
		for(int j = 0; j < 3; j++){
			Rect[i][j].setPosition(this -> posx + (i* this->size), this -> posy + (j * this->size));
		}
	}
}

bool Tetris::canDown(Map * m){
	for(int i = 0; i < 3; i++){
		for(int j = 0; j < 3; j++){
			if(this->peca[this->type][this->rot][i][j] == '#' && m->map[(int)(this->posy/20) + i + 1][(int)(this->posx/20) + j].valor != '-')
				return false;
		}
	}

	return true;
}

bool Tetris::canMove(Map * m, string direction){
	if(direction == "right"){
		for(int i = 0; i < 3; i++){
			for(int j = 0; j < 3; j++){
				if(this->peca[this->type][this->rot][i][j] == '#' && this->posx/20 + j > m -> xsize - 2) return false;
				if(this->peca[this->type][this->rot][i][j] == '#' && m->map[(int)(this->posy/20) + i][(int)(this->posx/20) + j + 1].valor != '-')
					return false;
			}
		}
	}

	if(direction == "left"){
		for(int i = 0; i < 3; i++){
			for(int j = 0; j < 3; j++){
				if(this->peca[this->type][this->rot][i][j] == '#'){
					if((int)this->posx/20 + j <= 0) return false;
					if(m->map[(int)(this->posy/20) + i][(int)(this->posx/20) + j - 1].valor != '-') return false;
					break;
				}
			}
		}
	}
	return true;
}


sf::Color Tetris::getColor(){
	return this->color[this->type];
}

void  Tetris::addToMap(Map * m){
	int py = (int)this->posy/20, px = (int)this->posx/20;
	for(int i = 0; i < 3; i++){
		for(int j = 0; j < 3; j++){
			if(this -> peca[this->type][this->rot][i][j] == '#'){
				m -> map[i+py][j+px].cor = this->color[this->type];
				m -> map[i+py][j+px].valor = '#';
			}
		}
	}
}

void Tetris::Reset(){
	this -> posx = 0;
	this -> posy = 0; 
	this -> type = (++this -> type)%5;
	this -> rot  = 0;
	Tetris::SetTetris();
}

void Tetris::draw(sf::RenderWindow &WindowGame){
	Tetris::SetTetris();
	for(int i = 0; i < 3; i++){
		for(int j = 0; j < 3; j++){
            if(Rect[i][j].getFillColor() != sf::Color::Black)
                WindowGame.draw(Rect[i][j]);
        }
	}

	for(int i = 0; i < 3; i++){
		for(int j = 0; j < 3; j++)
			cout << this->peca[this->type][this->rot][i][j];	
		cout << endl;
	}
	cout << this->type << " " << this->rot << endl;
}