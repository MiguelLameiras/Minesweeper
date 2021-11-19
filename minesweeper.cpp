#include <SDL2/SDL.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <stdbool.h>
#include <iostream>
#include <vector>

//compilar g++ minesweeper.cpp -w -lSDL2 -o mine

SDL_Event event;
SDL_Window *window; // Declare a pointer
SDL_Renderer *renderer;
SDL_Surface *screenSurface = NULL; //The surface contained by the window
SDL_Surface *background = NULL;    //Fundo
int cores[14][3] = {{11, 120, 79}, {10, 106, 70}, {8, 93, 62}, {7, 80, 53}, {6, 67, 44}, {5, 53, 35}, {4, 40, 26}, {15, 166, 110}, {49, 109, 14}, {29, 64, 8}, {26, 57, 7}, {22, 50, 6}, {19, 43, 5}, {16, 36, 4}};
int numflags = 0;
using namespace std;

struct cell
{
  //int coord[4]; //xmin,xmax,ymin,ymax
  bool bomba;
  bool flag;
  bool exposto;
};

void Delay(unsigned int Sec)
{
  clock_t ticks1 = clock(), ticks2 = ticks1;
  while ((ticks2 / CLOCKS_PER_SEC - ticks1 / CLOCKS_PER_SEC) < Sec)
    ticks2 = clock();
}

//gerar número aleatórios
int randomNum(int nr_min, int nr_max)
{
  static bool initialized = false;
  if (!initialized)
  {
    initialized = true;
    srand(time(NULL));
  }

  return rand() % nr_max + nr_min;
}

void reset(int ladox, int ladoy, vector<vector<cell>> &pontos)
{
  int cor;

  //Gerar casas
  for (int i = 0; i < ladox; i++)
  {
    for (int j = 0; j < ladoy; j++)
    {
      pontos[i][j].bomba = false;
      pontos[i][j].exposto = false;
      pontos[i][j].flag = false;
      numflags = 0;
      cor = randomNum(0, 13);
      SDL_SetRenderDrawColor(renderer, cores[cor][0], cores[cor][1], cores[cor][2], 100);
      SDL_Rect rect = {i * 20, j * 20, 20, 20};
      SDL_RenderFillRect(renderer, &rect);
    }
  }

  SDL_RenderPresent(renderer);
}

void gerarbombas(int numbombas, int xfixo, int yfixo, int ladox, int ladoy, vector<vector<cell>> &pontos)
{
  //Gerar Bombas
  int x, y = 0;
  for (int i = 0; i < numbombas; i++)
  {
  start:
    x = randomNum(0, ladox);
    y = randomNum(0, ladoy);
    for (int i = xfixo - 1; i <= xfixo + 1; i++)
    {
      for (int j = yfixo - 1; j <= yfixo + 1; j++)
      {
        if (x == i && y == j)
        {
          goto start;
        }
      }
    }
    pontos[x][y].bomba = true;
  }
}

int criarjanela(int ladox, int ladoy)
{

  // Create an application window with the following settings:
  window = SDL_CreateWindow(
      "Minesweeper",          // window title
      SDL_WINDOWPOS_CENTERED, // initial x position
      SDL_WINDOWPOS_CENTERED, // initial y position
      ladox,                  // width, in pixels
      ladoy,                  // height, in pixels
      SDL_WINDOW_OPENGL       // flags - see below
  );

  // Check that the window was successfully created
  if (window == NULL)
  {
    // In the case that the window could not be made...
    printf("Could not create window: %s\n", SDL_GetError());
    return 1;
  }

  else
  {
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  }
}

void drawnum(int x, int y, int num)
{
  if (num == 1)
  {
    SDL_SetRenderDrawColor(renderer, 42, 46, 128, 100);
    SDL_Rect rect1 = {x * 20 + 10, y * 20 + 3, 4, 14};
    SDL_RenderFillRect(renderer, &rect1);

    SDL_Rect rect2 = {x * 20 + 7, y * 20 + 6, 3, 4};
    SDL_RenderFillRect(renderer, &rect2);

    SDL_RenderPresent(renderer);
  }
  else if (num == 2)
  {
    SDL_SetRenderDrawColor(renderer, 9, 87, 29, 100);
    SDL_Rect rect3 = {x * 20 + 5, y * 20 + 3, 7, 3};
    SDL_RenderFillRect(renderer, &rect3);

    SDL_Rect rect4 = {x * 20 + 5, y * 20 + 14, 10, 3};
    SDL_RenderFillRect(renderer, &rect4);

    SDL_Rect rect5 = {x * 20 + 8, y * 20 + 8, 4, 3};
    SDL_RenderFillRect(renderer, &rect5);

    SDL_Rect rect6 = {x * 20 + 12, y * 20 + 5, 3, 4};
    SDL_RenderFillRect(renderer, &rect6);

    SDL_Rect rect7 = {x * 20 + 5, y * 20 + 11, 3, 4};
    SDL_RenderFillRect(renderer, &rect7);

    SDL_RenderPresent(renderer);
  }
  else if (num == 3)
  {
    SDL_SetRenderDrawColor(renderer, 128, 42, 42, 100);
    SDL_Rect rect8 = {x * 20 + 5, y * 20 + 3, 7, 3};
    SDL_RenderFillRect(renderer, &rect8);

    SDL_Rect rect9 = {x * 20 + 5, y * 20 + 14, 7, 3};
    SDL_RenderFillRect(renderer, &rect9);

    SDL_Rect rect10 = {x * 20 + 8, y * 20 + 8, 4, 3};
    SDL_RenderFillRect(renderer, &rect10);

    SDL_Rect rect11 = {x * 20 + 12, y * 20 + 5, 3, 10};
    SDL_RenderFillRect(renderer, &rect11);

    SDL_RenderPresent(renderer);
  }
  else if (num == 4)
  {
    SDL_SetRenderDrawColor(renderer, 89, 42, 128, 100);
    SDL_Rect rect12 = {x * 20 + 5, y * 20 + 3, 3, 7};
    SDL_RenderFillRect(renderer, &rect12);

    SDL_Rect rect13 = {x * 20 + 5, y * 20 + 9, 7, 3};
    SDL_RenderFillRect(renderer, &rect13);

    SDL_Rect rect14 = {x * 20 + 12, y * 20 + 3, 3, 14};
    SDL_RenderFillRect(renderer, &rect14);

    SDL_RenderPresent(renderer);
  }
  else if (num == 5)
  {
    SDL_SetRenderDrawColor(renderer, 128, 82, 42, 100);
    SDL_Rect rect15 = {x * 20 + 5, y * 20 + 3, 10, 3};
    SDL_RenderFillRect(renderer, &rect15);

    SDL_Rect rect16 = {x * 20 + 5, y * 20 + 14, 10, 3};
    SDL_RenderFillRect(renderer, &rect16);

    SDL_Rect rect17 = {x * 20 + 5, y * 20 + 8, 10, 3};
    SDL_RenderFillRect(renderer, &rect17);

    SDL_Rect rect18 = {x * 20 + 5, y * 20 + 5, 3, 4};
    SDL_RenderFillRect(renderer, &rect18);

    SDL_Rect rect19 = {x * 20 + 12, y * 20 + 11, 3, 4};
    SDL_RenderFillRect(renderer, &rect19);

    SDL_RenderPresent(renderer);
  }
  else if (num == 6)
  {
    SDL_SetRenderDrawColor(renderer, 189, 87, 157, 100);
    SDL_Rect rect20 = {x * 20 + 5, y * 20 + 3, 10, 3};
    SDL_RenderFillRect(renderer, &rect20);

    SDL_Rect rect21 = {x * 20 + 5, y * 20 + 14, 10, 3};
    SDL_RenderFillRect(renderer, &rect21);

    SDL_Rect rect22 = {x * 20 + 5, y * 20 + 8, 10, 3};
    SDL_RenderFillRect(renderer, &rect22);

    SDL_Rect rect23 = {x * 20 + 5, y * 20 + 5, 3, 4};
    SDL_RenderFillRect(renderer, &rect23);

    SDL_Rect rect24 = {x * 20 + 12, y * 20 + 11, 3, 4};
    SDL_RenderFillRect(renderer, &rect24);

    SDL_Rect rect25 = {x * 20 + 5, y * 20 + 11, 3, 4};
    SDL_RenderFillRect(renderer, &rect25);

    SDL_RenderPresent(renderer);
  }
  else if (num == 7)
  {
    SDL_SetRenderDrawColor(renderer, 19, 64, 15, 100);
    SDL_Rect rect33 = {x * 20 + 6, y * 20 + 3, 8, 3};
    SDL_RenderFillRect(renderer, &rect33);

    SDL_Rect rect34 = {x * 20 + 10, y * 20 + 3, 4, 14};
    SDL_RenderFillRect(renderer, &rect34);

    SDL_RenderPresent(renderer);
  }
  else if (num == 8)
  {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 100);
    SDL_Rect rect26 = {x * 20 + 6, y * 20 + 3, 8, 3};
    SDL_RenderFillRect(renderer, &rect26);

    SDL_Rect rect27 = {x * 20 + 6, y * 20 + 14, 8, 3};
    SDL_RenderFillRect(renderer, &rect27);

    SDL_Rect rect28 = {x * 20 + 6, y * 20 + 9, 8, 2};
    SDL_RenderFillRect(renderer, &rect28);

    SDL_Rect rect29 = {x * 20 + 5, y * 20 + 5, 3, 4};
    SDL_RenderFillRect(renderer, &rect29);

    SDL_Rect rect30 = {x * 20 + 12, y * 20 + 11, 3, 4};
    SDL_RenderFillRect(renderer, &rect30);

    SDL_Rect rect31 = {x * 20 + 5, y * 20 + 11, 3, 4};
    SDL_RenderFillRect(renderer, &rect31);

    SDL_Rect rect32 = {x * 20 + 12, y * 20 + 5, 3, 4};
    SDL_RenderFillRect(renderer, &rect32);

    SDL_RenderPresent(renderer);
  }
}

int getnumbombas(int xfixo, int yfixo, int ladox, int ladoy, vector<vector<cell>> pontos)
{
  int xtemp = xfixo - 1;
  int ytemp = yfixo - 1;
  int num = 0;
  for (int i = 0; i < 3; i++)
  {
    for (int j = 0; j < 3; j++)
    {
      if (ytemp + i >= 0 && xtemp + j >= 0 && ytemp + i < ladoy && xtemp + j < ladox )
      {
        if (pontos[xtemp + j][ytemp + i].bomba == true)
        {
          num++;
        }
      }
    }
  }

  return num;
}

int getaround(int xfixo, int yfixo, int ladox, int ladoy, vector<vector<cell>> &pontos)
{
  int xtemp = xfixo - 1;
  int ytemp = yfixo - 1;
  int num = 0;
  for (int i = 0; i < 3; i++)
  {
    for (int j = 0; j < 3; j++)
    {
      if (yfixo > 0 && xfixo > 0 && yfixo < ladoy - 1 && xfixo < ladox - 1)
      {
        if (getnumbombas(xtemp + j, ytemp + i, ladox, ladoy, pontos) != 0 && pontos[xtemp + j][ytemp + i].flag == false)
        {
          SDL_SetRenderDrawColor(renderer, 255, 236, 181, 100);
          SDL_Rect rect = {(xtemp + j) * 20, (ytemp + i) * 20, 20, 20};
          SDL_RenderFillRect(renderer, &rect);

          SDL_RenderPresent(renderer);

          drawnum(xtemp + j, ytemp + i, getnumbombas(xtemp + j, ytemp + i, ladox, ladoy, pontos));
          pontos[xtemp + j][ytemp + i].exposto = true;
        }
        if (getnumbombas(xtemp + j, ytemp + i, ladox, ladoy, pontos) == 0 && pontos[xtemp + j][ytemp + i].exposto == false && pontos[xtemp + j][ytemp + i].flag == false)
        {
          SDL_SetRenderDrawColor(renderer, 255, 236, 181, 100);
          SDL_Rect rect = {(xtemp + j) * 20, (ytemp + i) * 20, 20, 20};
          SDL_RenderFillRect(renderer, &rect);
          SDL_RenderPresent(renderer);
          pontos[xtemp + j][ytemp + i].exposto = true;
          getaround(xtemp + j, ytemp + i, ladox, ladoy, pontos);
        }
      }
    }
  }

  return num;
}

int drawflag(int xfixo, int yfixo, vector<vector<cell>> &pontos)
{
  if (pontos[xfixo][yfixo].flag == false)
  {
    SDL_SetRenderDrawColor(renderer, 108, 81, 0, 100);
    SDL_Rect rect = {xfixo * 20 + 5, yfixo * 20 + 2, 1, 16};
    SDL_RenderFillRect(renderer, &rect);
    SDL_SetRenderDrawColor(renderer, 19, 20, 19, 100);
    SDL_Rect rect1 = {xfixo * 20 + 6, yfixo * 20 + 2, 1, 16};
    SDL_RenderFillRect(renderer, &rect1);
    SDL_Rect rect6 = {xfixo * 20 + 4, yfixo * 20 + 17, 4, 1};
    SDL_RenderFillRect(renderer, &rect6);
    SDL_Rect rect7 = {xfixo * 20 + 3, yfixo * 20 + 18, 6, 2};
    SDL_RenderFillRect(renderer, &rect7);
    SDL_SetRenderDrawColor(renderer, 255, 69, 51, 100);
    SDL_Rect rect2 = {xfixo * 20 + 7, yfixo * 20 + 2, 2, 9};
    SDL_RenderFillRect(renderer, &rect2);
    SDL_Rect rect3 = {xfixo * 20 + 9, yfixo * 20 + 3, 2, 7};
    SDL_RenderFillRect(renderer, &rect3);
    SDL_Rect rect4 = {xfixo * 20 + 11, yfixo * 20 + 4, 2, 5};
    SDL_RenderFillRect(renderer, &rect4);
    SDL_Rect rect5 = {xfixo * 20 + 13, yfixo * 20 + 5, 2, 3};
    SDL_RenderFillRect(renderer, &rect5);
    SDL_RenderPresent(renderer);
    pontos[xfixo][yfixo].flag = true;
    numflags++;
    return 1;
  }
  else
  {
    int cor = randomNum(0, 13);
    SDL_SetRenderDrawColor(renderer, cores[cor][0], cores[cor][1], cores[cor][2], 100);
    SDL_Rect rect = {xfixo * 20, yfixo * 20, 20, 20};
    SDL_RenderFillRect(renderer, &rect);
    SDL_RenderPresent(renderer);
    pontos[xfixo][yfixo].flag = false;
    numflags--;
    return 1;
  }
}

bool win(int numbombas,int ladox, int ladoy, vector<vector<cell>> &pontos){
  int flags = 0;
  int exposed = 0;
  for(int i = 0; i < ladoy;i++){
    for(int j = 0;j < ladox;j++){
        if(pontos[j][i].flag == true && pontos[j][i].bomba == true){
          flags++;
      }
    }
  }
  for(int i = 0; i < ladoy;i++){
    for(int j = 0;j < ladox;j++){
        if(pontos[j][i].exposto == true){
          exposed++;
      }
    }
  }
  cout << "flags: " << flags << "exposto: " << exposed << endl;
  if(flags == numbombas && exposed == ((ladox*ladoy) - numbombas)){
    SDL_Log("..............................Ganhaste");
    return true;
  }
  else{return false;}
}
void drawbomb(int xfixo, int yfixo)
{
  //fundo

  SDL_SetRenderDrawColor(renderer, 255, 236, 181, 100);
  SDL_Rect rect = {xfixo * 20, yfixo * 20, 20, 20};
  SDL_RenderFillRect(renderer, &rect);

  //bomba
  SDL_SetRenderDrawColor(renderer, 19, 20, 19, 100);

  SDL_Rect rect1 = {xfixo * 20 + 10, yfixo * 20 + 3, 2, 16};
  SDL_RenderFillRect(renderer, &rect1);

  SDL_Rect rect2 = {xfixo * 20 + 3, yfixo * 20 + 10, 16, 2};
  SDL_RenderFillRect(renderer, &rect2);

  SDL_Rect rect3 = {xfixo * 20 + 5, yfixo * 20 + 8, 12, 6};
  SDL_RenderFillRect(renderer, &rect3);

  SDL_Rect rect4 = {xfixo * 20 + 8, yfixo * 20 + 5, 6, 12};
  SDL_RenderFillRect(renderer, &rect4);

  SDL_Rect rect5 = {xfixo * 20 + 4, yfixo * 20 + 4, 2, 2};
  SDL_RenderFillRect(renderer, &rect5);

  SDL_Rect rect6 = {xfixo * 20 + 4, yfixo * 20 + 16, 2, 2};
  SDL_RenderFillRect(renderer, &rect6);

  SDL_Rect rect7 = {xfixo * 20 + 16, yfixo * 20 + 4, 2, 2};
  SDL_RenderFillRect(renderer, &rect7);

  SDL_Rect rect8 = {xfixo * 20 + 16, yfixo * 20 + 16, 2, 2};
  SDL_RenderFillRect(renderer, &rect8);

  SDL_Rect rect9 = {xfixo * 20 + 7, yfixo * 20 + 6, 8, 1};
  SDL_RenderFillRect(renderer, &rect9);

  SDL_Rect rect10 = {xfixo * 20 + 7, yfixo * 20 + 15, 8, 1};
  SDL_RenderFillRect(renderer, &rect10);

  SDL_Rect rect11 = {xfixo * 20 + 6, yfixo * 20 + 7, 2, 8};
  SDL_RenderFillRect(renderer, &rect11);

  SDL_Rect rect12 = {xfixo * 20 + 14, yfixo * 20 + 7, 2, 8};
  SDL_RenderFillRect(renderer, &rect12);

  //reflexo
  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 100);

  SDL_Rect rect13 = {xfixo * 20 + 8, yfixo * 20 + 7, 2, 1};
  SDL_RenderFillRect(renderer, &rect13);

  SDL_Rect rect14 = {xfixo * 20 + 7, yfixo * 20 + 8, 2, 1};
  SDL_RenderFillRect(renderer, &rect14);

  SDL_Rect rect15 = {xfixo * 20 + 6, yfixo * 20 + 9, 2, 1};
  SDL_RenderFillRect(renderer, &rect15);

  SDL_RenderPresent(renderer);
}

int main(int argc, char *argv[])
{
  int quit = 0;
  int ladox = 100;
  int ladoy = 100;
  int numbombas = 10000;
  bool inicial = true;

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

  while (numbombas >= (ladox * ladoy))
  {
    cout << "\nNumero de Bombas:";
    cin >> numbombas;
  }

  srand(time(NULL));

  SDL_Init(SDL_INIT_EVERYTHING); // Initialize SDL2

  criarjanela(ladox * 20, ladoy * 20);

  vector<vector<cell>> pontos(ladox, vector<cell>(ladoy));

  reset(ladox, ladoy, pontos);

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

      temp = xmouse / 20;
      xmouse_cord = (int)temp;
      temp = ymouse / 20;
      ymouse_cord = (int)temp;

      //SDL_Log("Mouse cursor is at %d, %d", xmouse_cord, ymouse_cord);

      //Botão esquerdo
      if ((buttons & SDL_BUTTON_LMASK) != 0)
      {
        int xfixo = xmouse_cord;
        int yfixo = ymouse_cord;

        //SDL_Log("Mouse Button 1 (left) is pressed.");

        if (inicial == true && pontos[xfixo][yfixo].flag == false)
        {
          gerarbombas(numbombas, xfixo, yfixo, ladox, ladoy, pontos);
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
                drawbomb(j, i);
              }
            }
          }
          SDL_Log("..............................Perdeste");
          inicial = true;
          Delay(2);
          reset(ladox, ladoy, pontos);
        }
        else if (pontos[xfixo][yfixo].flag == false)
        {
          SDL_SetRenderDrawColor(renderer, 255, 236, 181, 100);
          SDL_Rect rect = {xfixo * 20, yfixo * 20, 20, 20};
          SDL_RenderFillRect(renderer, &rect);

          SDL_RenderPresent(renderer);
          pontos[xfixo][yfixo].exposto = true;

          if (getnumbombas(xfixo, yfixo, ladox, ladoy, pontos) == 0)
          {
            getaround(xfixo, yfixo, ladox, ladoy, pontos);
          }
          else
          {
            drawnum(xmouse_cord, ymouse_cord, getnumbombas(xfixo, yfixo, ladox, ladoy, pontos));
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
          numflags = drawflag(xfixo, yfixo, pontos);
        }
      }

      if(numflags >= numbombas){
        if(win(numbombas,ladox,ladoy,pontos)){
          inicial = true;
          Delay(2);
          reset(ladox, ladoy, pontos);
        }
      }
    }
  }

  SDL_RenderPresent(renderer);

  // Close and destroy the window
  SDL_DestroyWindow(window);

  //Limpar Superfícies
  SDL_FreeSurface(background);
  background = NULL;

  // Clean up
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();

  return 0;
}
