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
    Game(SDL_Event event_,SDL_Window *window_,SDL_Renderer *renderer_,SDL_Surface *screenSurface_,SDL_Surface *background_);
    ~Game() = default;

  void Delay(int milliseconds);
  int randomNum(int nr_min, int nr_max);
  void reset(int &numflags, int ladox, int ladoy, vector<vector<cell>> &pontos);
  void gerarbombas(int numbombas, int xfixo, int yfixo, int ladox, int ladoy, vector<vector<cell>> &pontos);
  int criarjanela(int ladox, int ladoy);
  void drawnum(int x, int y, int num);
  int getnumbombas(int xfixo, int yfixo, int ladox, int ladoy, vector<vector<cell>> pontos);
  void getaround(int xfixo, int yfixo, int ladox, int ladoy, vector<vector<cell>> &pontos);
  int drawflag(int &numflags, int xfixo, int yfixo, vector<vector<cell>> &pontos);
  bool win(int numbombas, int ladox, int ladoy, vector<vector<cell>> &pontos);
  void drawbomb(int xfixo, int yfixo);

private:
  SDL_Event event;
  SDL_Window *window; // Declare a pointer
  SDL_Renderer *renderer;
  SDL_Surface *screenSurface = NULL; //The surface contained by the window
  SDL_Surface *background = NULL;    //Fundo

};
#endif
