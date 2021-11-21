#include <SDL2/SDL.h>
#include <time.h>
#include <iostream>
#include <vector>
#include "mine_header.h"

using namespace std;

int main(int argc, char *argv[])
{
  SDL_Event event;
  SDL_Window *window; // Declare a pointer
  SDL_Renderer *renderer;
  SDL_Surface *screenSurface = NULL; //The surface contained by the window
  SDL_Surface *background = NULL;    //Fundo

  int ladox = 100;
  int ladoy = 100;
  int numbombas = 10000;
  bool inicial = true;
  int quit = 0;
  int numflags = 0;

  Game a(event, window, renderer, screenSurface, background);

  while (ladox > 70 && ladox > 5)
  {
    cout << "Largura:";
    cin >> ladox;
  }
  while (ladoy > 40 && ladoy > 5)
  {
    cout << "\nAltura:";
    cin >> ladoy;
  }

  int temp;
  temp = ladox * ladoy * 0.1;
  cout << "\nFacil: " << temp << " Bombas";
  temp = ladox * ladoy * 0.15;
  cout << "\nMédio: " << temp << " Bombas";
  temp = ladox * ladoy * 0.2;
  cout << "\nDificil: " << temp << " Bombas" << endl;

  while (numbombas >= (ladox * ladoy) - 9)
  {
    cout << "\nNumero de Bombas:";
    cin >> numbombas;
  }

  vector<vector<cell>> pontos(ladox, vector<cell>(ladoy));

  srand(time(NULL));
  SDL_Init(SDL_INIT_EVERYTHING); // Initialize SDL2

  a.criarjanela(ladox * 20, ladoy * 20);

  a.reset(numflags, ladox, ladoy, pontos);

  //Loop do programa
  while (quit == 0)
  {
    //While there's an event to handle
    while (SDL_PollEvent(&event))
    {
      if (event.type == SDL_QUIT)
      {
        //Quit the program
        quit = 1;
      }

      int xmouse, ymouse, xmouse_cord, ymouse_cord;
      Uint32 buttons;
      float temp;

      SDL_PumpEvents(); // make sure we have the latest mouse state.

      buttons = SDL_GetMouseState(&xmouse, &ymouse);

      SDL_Log("Mouse cursor is at %d, %d", xmouse, ymouse);

      temp = xmouse / 20;
      xmouse_cord = (int)temp;
      temp = ymouse / 20;
      ymouse_cord = (int)temp;

      //Botão esquerdo
      if ((buttons & SDL_BUTTON_LMASK) != 0)
      {
        if (ymouse_cord < ladoy )
        {
          int xfixo = xmouse_cord;
          int yfixo = ymouse_cord;

          //SDL_Log("Mouse Button 1 (left) is pressed.");

          if (inicial == true && pontos[xfixo][yfixo].flag == false)
          {
            a.gerarbombas(numbombas, xfixo, yfixo, ladox, ladoy, pontos);
            a.getaround(xfixo, yfixo, ladox, ladoy, pontos);
            inicial = false;
          }

          else if (pontos[xfixo][yfixo].bomba == true && inicial == false && pontos[xfixo][yfixo].flag == false)
          {
            for (int i = 0; i < ladoy; i++)
            {
              for (int j = 0; j < ladox; j++)
              {
                if (pontos[j][i].bomba == true)
                {
                  a.drawbomb(j, i);
                }
              }
            }
            SDL_Log("..............................Perdeste");
            inicial = true;
            a.Delay(1000);
            a.reset(numflags, ladox, ladoy, pontos);
          }
          else if (pontos[xfixo][yfixo].flag == false)
          {
            pontos[xfixo][yfixo].exposto = true;
            if (a.getnumbombas(xfixo, yfixo, ladox, ladoy, pontos) == 0)
            {
              a.getaround(xfixo, yfixo, ladox, ladoy, pontos);
            }
            else
            {
              a.drawnum(xmouse_cord, ymouse_cord, a.getnumbombas(xfixo, yfixo, ladox, ladoy, pontos));
            }
          }
        }

        //botão direito
        if ((buttons & SDL_BUTTON_RMASK) != 0)
        {
          int xfixo = xmouse_cord;
          int yfixo = ymouse_cord;

          //SDL_Log("Mouse Button 1 (right) is pressed.");
          if (pontos[xfixo][yfixo].exposto == false)
          {
            numflags = a.drawflag(numflags, xfixo, yfixo, pontos);
          }
        }

        if (numflags == numbombas)
        {
          cout << "flags: " << numflags << "bombas: " << numbombas << endl;
          if (a.win(numbombas, ladox, ladoy, pontos))
          {
            inicial = true;
            a.Delay(1000);
            a.reset(numflags, ladox, ladoy, pontos);
          }
        }
      }
    }
  }

  SDL_RenderPresent(renderer);

  // Close and destroy the window
  SDL_DestroyWindow(window);

  //Limpar Superfícies
  SDL_FreeSurface(background);

  // Clean up
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();

  return 0;
}
