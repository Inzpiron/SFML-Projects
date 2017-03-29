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

void MapLineComplete(Map * m){
	int i  = m->ysize - 1;
	for(; i >= 0; i--){
		bool check = true;
		for(int j = 0; j < m->xsize; j++){
			if(m -> map[i][j].valor == '-') 
				check = false; 
		}

		if(check){
			for(int k = i; k > 0; k--){
				for(int l = 0; l < m->xsize; l++)
					m->map[k][l] = m->map[k-1][l];
			}
			i = m->ysize;
		}
	}
}

TetrisText::TetrisText(int x, int y, string str, sf::Font font, int fsize){
	this->font = font;
	this->fsize = fsize;
	this->str = str;
	this->cor = sf::Color::Yellow;
	this->x = 40; this->y = 40;
}

void TetrisText::draw(sf::RenderWindow &WindowGame){
	sf::Text letra[this->str.size()];
	double MaxWidth;
	for(int i = 0; i < str.size(); i++){
		string aux = "";
		aux += str[i];
		letra[i].setCharacterSize(this->fsize);
		letra[i].setFont(this->font);
		letra[i].setString(aux);
		letra[i].setFillColor(this->cor);

		if(letra[i].getLocalBounds().width > MaxWidth)
			MaxWidth = letra[i].getLocalBounds().width;
	}
	for(int i = 0; i < str.size(); i++){
		letra[i].setPosition(this->x + (i*MaxWidth) + 1,this->y);
		WindowGame.draw(letra[i]);
	}
}
