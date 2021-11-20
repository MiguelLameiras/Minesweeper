#ifndef __mine_header__
#define __mine_header__

#pragma once

using namespace std;

struct cell
{
  bool bomba;
  bool flag;
  bool exposto;
};

int cores[14][3] = {{11, 120, 79}, {10, 106, 70}, {8, 93, 62}, {7, 80, 53}, {6, 67, 44}, {5, 53, 35}, {4, 40, 26}, {15, 166, 110}, {49, 109, 14}, {29, 64, 8}, {26, 57, 7}, {22, 50, 6}, {19, 43, 5}, {16, 36, 4}};
int numflags = 0;

void Delay(unsigned int Sec);

int randomNum(int nr_min, int nr_max);

void reset(int ladox, int ladoy, vector<vector<cell>> &pontos);

void gerarbombas(int numbombas, int xfixo, int yfixo, int ladox, int ladoy, vector<vector<cell>> &pontos);

int criarjanela(int ladox, int ladoy);

void drawnum(int x, int y, int num);

int getnumbombas(int xfixo, int yfixo, int ladox, int ladoy, vector<vector<cell>> pontos);

int getaround(int xfixo, int yfixo, int ladox, int ladoy, vector<vector<cell>> &pontos);

int drawflag(int xfixo, int yfixo, vector<vector<cell>> &pontos);

bool win(int numbombas,int ladox, int ladoy, vector<vector<cell>> &pontos);

void drawbomb(int xfixo, int yfixo);

void gamefunc(int ladox, int ladoy, int numbombas,vector<vector<cell>> &pontos);

#endif
