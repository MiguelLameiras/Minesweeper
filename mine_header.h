#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

#include <time.h>
#include <iostream>
#include <string>
#include <vector>

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

class Game
{
public: 
  // constructors and destructor
  Game();
  ~Game();

  void Delay(int milliseconds);
  int randomNum(int nr_min, int nr_max);
  void reset(int &numflags, vector<vector<cell>> &pontos);
  void gerarbombas(int xfixo, int yfixo, vector<vector<cell>> &pontos);
  int criarjanela();
  void drawnum(int x, int y, int num);
  int getnumbombas(int xfixo, int yfixo, vector<vector<cell>> pontos);
  void getaround(int xfixo, int yfixo, vector<vector<cell>> &pontos);
  int drawflag(int &numflags, int xfixo, int yfixo, vector<vector<cell>> &pontos);
  bool win(vector<vector<cell>> &pontos);
  void drawbomb(int xfixo, int yfixo);
  void draw_text(string msg, int x, int y, int r, int g, int b, int size, int rectx, int recty, int rectr, int rectg, int rectb, int rectw, int recth);
  string elapsed_time(clock_t time_init);
  void draw_image(int x, int y,int tile_num);
  void GetTileMap(string file);
  void Draw_Shadow(int x, int y);
  void Settings_Menu(int percent_bombs,int ladox_temp);
  void Settings_Menu_Loop();
  void Draw_Slider(int slidernum,int percent_bombs, int sliderpos,int ladox_temp);
  int Get_ladox();
  int Get_ladoy();
  int Get_numbombas();

private:
  SDL_Event event;
  SDL_Window *window; // Declare a pointer
  SDL_Renderer *renderer;
  SDL_Surface *screenSurface = NULL; //The surface contained by the window
  SDL_Surface *background = NULL;    //Fundo
  SDL_Surface *surface;
  SDL_Texture *texture;
  int ladox,ladoy;
  int numbombas;
  //Load images from one big tileset 
  int width = 20; //tile size in pixels
  int height = 20;
  int num_tiles = 15;
  SDL_Texture *TileMap = NULL;
  SDL_Rect SpriteClips[15];
};
#endif
