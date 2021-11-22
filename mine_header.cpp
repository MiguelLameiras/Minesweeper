#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include <time.h>
#include <iostream>
#include <string>
#include <vector>

#include "mine_header.h"

using namespace std;

int cores[14][3] = {{11, 120, 79}, {10, 106, 70}, {8, 93, 62}, {7, 80, 53}, {6, 67, 44}, {5, 53, 35}, {4, 40, 26}, {15, 166, 110}, {49, 109, 14}, {29, 64, 8}, {26, 57, 7}, {22, 50, 6}, {19, 43, 5}, {16, 36, 4}};

Game::Game(SDL_Event event_, SDL_Window *window_, SDL_Renderer *renderer_, SDL_Surface *screenSurface_, SDL_Surface *background_)
{
    event = event_;
    window = window_;
    renderer = renderer_;
    screenSurface = screenSurface_;
    background = background_;
    TTF_Init();
}

Game::~Game()
{
    TTF_Quit();
    //Limpar Superfícies
    SDL_FreeSurface(background);
    SDL_FreeSurface(screenSurface);
    // Clean up
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void Game::Delay(int milliseconds)
{
    long pause;
    clock_t now, then;

    pause = milliseconds * (CLOCKS_PER_SEC / 1000);
    now = then = clock();
    while ((now - then) < pause)
        now = clock();
}

int Game::randomNum(int nr_min, int nr_max)
{
    //gerar número aleatórios
    static bool initialized = false;
    if (!initialized)
    {
        initialized = true;
        srand(time(NULL));
    }

    return rand() % nr_max + nr_min;
}

void Game::reset(int &numflags, int ladox, int ladoy, vector<vector<cell>> &pontos)
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
            cor = Game::randomNum(0, 13);
            SDL_SetRenderDrawColor(renderer, cores[cor][0], cores[cor][1], cores[cor][2], 100);
            SDL_Rect rect = {i * 20, j * 20, 20, 20};
            SDL_RenderFillRect(renderer, &rect);
        }
    }

    //Gerar menu
    for (int i = 0; i < ladox; i++)
    {
        for (int j = ladoy; j < ladoy + 2; j++)
        {
            //cout << "criando..." << endl;
            SDL_SetRenderDrawColor(renderer, 232, 228, 227, 100);
            SDL_Rect rect = {i * 20, j * 20, 20, 20};
            SDL_RenderFillRect(renderer, &rect);
        }
    }

    SDL_RenderPresent(renderer);
    SDL_RenderPresent(renderer);
}

void Game::gerarbombas(int numbombas, int xfixo, int yfixo, int ladox, int ladoy, vector<vector<cell>> &pontos)
{
    //Gerar Bombas
    int x, y = 0;
    for (int i = 0; i < numbombas; i++)
    {
    start:
        x = randomNum(0, ladox);
        y = randomNum(0, ladoy);
        for (int j = xfixo - 1; j <= xfixo + 1; j++)
        {
            for (int k = yfixo - 1; k <= yfixo + 1; k++)
            {
                if ((x == j && y == k) || pontos[x][y].bomba == true)
                {
                    goto start;
                }
            }
        }
        cout << "bomba: " << numbombas << " " << i << " " << x << " " << y << endl;
        pontos[x][y].bomba = true;
    }
}

int Game::criarjanela(int ladox, int ladoy)
{
    // Create an application window with the following settings:
    window = SDL_CreateWindow(
        "Minesweeper",          // window title
        SDL_WINDOWPOS_CENTERED, // initial x position
        SDL_WINDOWPOS_CENTERED, // initial y position
        ladox,                  // width, in pixels
        ladoy + 40,             // height, in pixels
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

void Game::drawnum(int x, int y, int num)
{
    //fundo
    SDL_SetRenderDrawColor(renderer, 255, 236, 181, 100);
    SDL_Rect rect = {x * 20, y * 20, 20, 20};
    SDL_RenderFillRect(renderer, &rect);

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

int Game::getnumbombas(int xfixo, int yfixo, int ladox, int ladoy, vector<vector<cell>> pontos)
{
    int xtemp = xfixo - 1;
    int ytemp = yfixo - 1;
    int num = 0;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (ytemp + i >= 0 && xtemp + j >= 0 && ytemp + i < ladoy && xtemp + j < ladox)
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

void Game::getaround(int xfixo, int yfixo, int ladox, int ladoy, vector<vector<cell>> &pontos)
{
    SDL_SetRenderDrawColor(renderer, 255, 236, 181, 100);
    SDL_Rect rect = {xfixo * 20, yfixo * 20, 20, 20};
    SDL_RenderFillRect(renderer, &rect);
    SDL_RenderPresent(renderer);

    int xtemp = xfixo - 1;
    int ytemp = yfixo - 1;
    int num = 0;

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (yfixo > 0 && xfixo > 0 && yfixo < ladoy - 1 && xfixo < ladox - 1)
            {
                if (Game::getnumbombas(xtemp + j, ytemp + i, ladox, ladoy, pontos) != 0 && pontos[xtemp + j][ytemp + i].flag == false)
                {
                    SDL_SetRenderDrawColor(renderer, 255, 236, 181, 100);
                    SDL_Rect rect = {(xtemp + j) * 20, (ytemp + i) * 20, 20, 20};
                    SDL_RenderFillRect(renderer, &rect);

                    SDL_RenderPresent(renderer);

                    Game::drawnum(xtemp + j, ytemp + i, Game::getnumbombas(xtemp + j, ytemp + i, ladox, ladoy, pontos));
                    pontos[xtemp + j][ytemp + i].exposto = true;
                }
                if (getnumbombas(xtemp + j, ytemp + i, ladox, ladoy, pontos) == 0 && pontos[xtemp + j][ytemp + i].exposto == false && pontos[xtemp + j][ytemp + i].flag == false)
                {
                    SDL_SetRenderDrawColor(renderer, 255, 236, 181, 100);
                    SDL_Rect rect = {(xtemp + j) * 20, (ytemp + i) * 20, 20, 20};
                    SDL_RenderFillRect(renderer, &rect);
                    SDL_RenderPresent(renderer);

                    pontos[xtemp + j][ytemp + i].exposto = true;
                    Game::getaround(xtemp + j, ytemp + i, ladox, ladoy, pontos);
                }
            }
        }
    }
}

int Game::drawflag(int &numflags, int xfixo, int yfixo, vector<vector<cell>> &pontos)
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
        Game::Delay(200);
        return numflags;
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
        Game::Delay(200);
        return numflags;
    }
}

bool Game::win(int numbombas, int ladox, int ladoy, vector<vector<cell>> &pontos)
{
    int flags = 0;
    int exposed = 0;
    for (int i = 0; i < ladoy; i++)
    {
        for (int j = 0; j < ladox; j++)
        {
            if (pontos[j][i].flag == true && pontos[j][i].bomba == true)
            {
                flags++;
            }
        }
    }
    for (int i = 0; i < ladoy; i++)
    {
        for (int j = 0; j < ladox; j++)
        {
            if (pontos[j][i].exposto == true)
            {
                exposed++;
            }
        }
    }
    if (flags == numbombas && exposed == ((ladox * ladoy) - numbombas))
    {
        SDL_Log("..............................Ganhaste");
        return true;
    }
    else
    {
        return false;
    }
}

void Game::drawbomb(int xfixo, int yfixo)

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

void Game::draw_text(string msg, int x, int y, int r, int g, int b, int size,int ladox,int ladoy)
{
    SDL_Surface *surface;
    SDL_Texture *texture;

    SDL_SetRenderDrawColor(renderer, 232, 228, 227, 100);
    SDL_Rect bg = {0,ladoy*20 , ladox*20, 40};
    SDL_RenderFillRect(renderer, &bg);
    SDL_RenderPresent(renderer);

    TTF_Font *font = TTF_OpenFont("Font.ttf", size);
    if (!font)
    {
        printf("TTF_OpenFont: %s\n", TTF_GetError());
    }
    cout << msg.c_str() << endl;
    surface = TTF_RenderText_Blended(font, msg.c_str(), {r, g, b});
    if (surface == NULL)
    {
        cout << "Could not render surface" << endl;
    }
    SDL_Rect rect;
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    rect.x = x;
    rect.y = y;
    rect.w = surface->w;
    rect.h = surface->h;

    SDL_RenderCopy(renderer, texture, NULL, &rect);
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(surface);
    TTF_CloseFont(font);

}

string Game::elapsed_time(clock_t time_init)
{
      time_init = clock() - time_init;
      int time_taken = (int)((double)time_init)/CLOCKS_PER_SEC;
      string s = to_string(time_taken);
      return s;
}

Uint32 Game::callback(Uint32 interval, void* param)
{
    //Print callback message
    printf( "Callback called back with message: %s\n", (char*)param );

    return 0;
}