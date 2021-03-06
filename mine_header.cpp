#include "mine_header.h"

using namespace std;

int cores[14][3] = {{11, 120, 79}, {10, 106, 70}, {8, 93, 62}, {7, 80, 53}, {6, 67, 44}, {5, 53, 35}, {4, 40, 26}, {15, 166, 110}, {49, 109, 14}, {29, 64, 8}, {26, 57, 7}, {22, 50, 6}, {19, 43, 5}, {16, 36, 4}};

Game::Game()
{
    SDL_Init(SDL_INIT_EVERYTHING); // Initialize SDL2
    TTF_Init();
    IMG_Init(IMG_INIT_PNG);
    ladox = 10;
    ladoy = 10;
    numbombas = 15;
}

Game::~Game()
{
    TTF_Quit();
    IMG_Quit();
    // Limpar Superfícies
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
    // gerar número aleatórios
    static bool initialized = false;
    if (!initialized)
    {
        initialized = true;
        srand(time(NULL));
    }

    return rand() % nr_max + nr_min;
}

void Game::reset(int &numflags, vector<vector<cell>> &pontos)
{
    SDL_SetWindowSize(window,ladox*20 + 40,ladoy*20 + 80);

    SDL_SetRenderDrawColor(renderer, 21, 29, 40, 100);
    SDL_RenderClear(renderer);

    // Gerar casas
    numflags = 0;
    for (int i = 0; i < ladox; i++)
    {
        for (int j = 0; j < ladoy; j++)
        {
            pontos[i][j].bomba = false;
            pontos[i][j].exposto = false;
            pontos[i][j].flag = false;

            draw_image((i + 1) * 20, (j + 1) * 20, 0);
        }
    }

    // Gerar menu
    SDL_SetRenderDrawColor(renderer, 21, 29, 40, 100);
    SDL_Rect rect = {0, (ladoy + 2) * 20, (ladox + 1) * 20, 40};
    SDL_RenderFillRect(renderer, &rect);

    draw_text("RESET", 80, (ladoy + 2) * 20 + 10, 199, 207, 204, 18, 60, ladoy + 1, 232, 228, 227, 60, 40);

    draw_image((ladox - 1) * 20, (ladoy + 2) * 20, 11);
    draw_image((ladox)*20, (ladoy + 2) * 20, 12);
    draw_image((ladox - 1) * 20, (ladoy + 3) * 20, 13);
    draw_image((ladox)*20, (ladoy + 3) * 20, 14);

    SDL_RenderPresent(renderer);
}

void Game::gerarbombas(int xfixo, int yfixo, vector<vector<cell>> &pontos)
{
    // Gerar Bombas
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
        // cout << "bomba: " << numbombas << " " << i << " " << x << " " << y << endl;
        pontos[x][y].bomba = true;
    }
}

int Game::criarjanela()
{
    // Create an application window with the following settings:
    window = SDL_CreateWindow(
        "Minesweeper",                                              // window title
        SDL_WINDOWPOS_CENTERED,                                     // initial x position
        SDL_WINDOWPOS_CENTERED,                                     // initial y position
        240,                                                        // width, in pixels
        280,                                                        // height, in pixels
        SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN // flags - see below
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
    x++;
    y++;
    // fundo
    SDL_SetRenderDrawColor(renderer, 21, 29, 40, 100);
    SDL_Rect rect = {x * 20, y * 20, 20, 20};
    SDL_RenderFillRect(renderer, &rect);

    if (num == 1)
    {
        draw_image(x * 20, y * 20, 2);
    }
    else if (num == 2)
    {
        draw_image(x * 20, y * 20, 3);
    }
    else if (num == 3)
    {
        draw_image(x * 20, y * 20, 4);
    }
    else if (num == 4)
    {
        draw_image(x * 20, y * 20, 5);
    }
    else if (num == 5)
    {
        draw_image(x * 20, y * 20, 6);
        ;
    }
    else if (num == 6)
    {
        draw_image(x * 20, y * 20, 7);
    }
    else if (num == 7)
    {
        draw_image(x * 20, y * 20, 8);
    }
    else if (num == 8)
    {
        draw_image(x * 20, y * 20, 9);
    }
}

int Game::getnumbombas(int xfixo, int yfixo, vector<vector<cell>> pontos)
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

void Game::getaround(int xfixo, int yfixo, vector<vector<cell>> &pontos)
{
    SDL_SetRenderDrawColor(renderer, 21, 29, 40, 100);
    SDL_Rect rect = {(xfixo + 1) * 20, (yfixo + 1) * 20, 20, 20};
    SDL_RenderFillRect(renderer, &rect);
    SDL_RenderPresent(renderer);

    int xtemp = xfixo - 1;
    int ytemp = yfixo - 1;
    int num = 0;

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (xtemp + j >= 0 && ytemp + i >= 0 && xtemp + j < ladox && ytemp + i < ladoy)
            {
                if (Game::getnumbombas(xtemp + j, ytemp + i, pontos) != 0 && pontos[xtemp + j][ytemp + i].flag == false)
                {
                    Game::drawnum(xtemp + j, ytemp + i, Game::getnumbombas(xtemp + j, ytemp + i, pontos));
                    pontos[xtemp + j][ytemp + i].exposto = true;
                }
                if (getnumbombas(xtemp + j, ytemp + i,pontos) == 0 && pontos[xtemp + j][ytemp + i].exposto == false && pontos[xtemp + j][ytemp + i].flag == false)
                {
                    SDL_SetRenderDrawColor(renderer, 21, 29, 40, 100);
                    SDL_Rect rect = {(xtemp + j + 1) * 20, (ytemp + j + 1) * 20, 20, 20};
                    SDL_RenderFillRect(renderer, &rect);
                    SDL_RenderPresent(renderer);

                    pontos[xtemp + j][ytemp + i].exposto = true;
                    Game::getaround(xtemp + j, ytemp + i,pontos);
                }
            }
        }
    }
}

int Game::drawflag(int &numflags, int xfixo, int yfixo, vector<vector<cell>> &pontos)
{
    if (pontos[xfixo][yfixo].flag == false)
    {
        draw_image((xfixo + 1) * 20, (yfixo + 1) * 20, 1);
        pontos[xfixo][yfixo].flag = true;
        numflags++;
        Game::Delay(200);
        return numflags;
    }
    else
    {
        Game::draw_image((xfixo + 1) * 20, (yfixo + 1) * 20, 0);
        pontos[xfixo][yfixo].flag = false;
        numflags--;
        Game::Delay(200);
        return numflags;
    }
}

bool Game::win(vector<vector<cell>> &pontos)
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
    draw_image(xfixo * 20, yfixo * 20, 10);
}

void Game::draw_text(string msg, int x, int y, int r, int g, int b, int size, int rectx, int recty, int rectr, int rectg, int rectb, int rectw, int recth)
{
    // SDL_Surface *surface;
    // SDL_Texture *texture;

    SDL_SetRenderDrawColor(renderer, rectr, rectg, rectb, 100);
    SDL_Rect bg = {rectx * 20, recty * 20, rectw, recth};
    SDL_RenderFillRect(renderer, &bg);
    SDL_RenderPresent(renderer);

    TTF_Font *font = TTF_OpenFont("pixelmix.ttf", size);
    if (!font)
    {
        printf("TTF_OpenFont: %s\n", TTF_GetError());
    }

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
    SDL_RenderPresent(renderer);
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(surface);
    TTF_CloseFont(font);
}

string Game::elapsed_time(clock_t time_init)
{
    time_init = clock() - time_init;
    int time_taken = (int)((double)time_init) / CLOCKS_PER_SEC;
    string s = to_string(time_taken);
    return s;
}

void Game::draw_image(int x, int y, int tile_num)
{
    // Set rendering space and render to screen
    SDL_Rect renderQuad = {x, y, width, height};
    // Render to screen
    SDL_RenderCopy(renderer, TileMap, &SpriteClips[tile_num], &renderQuad);
    SDL_RenderPresent(renderer);
};

void Game::GetTileMap(string file)
{
    TileMap = IMG_LoadTexture(renderer, file.c_str());
    if (TileMap == NULL)
    {
        printf("Unable to load image %s! SDL_image Error: %s\n", file.c_str(), IMG_GetError());
    }
    else
    {
        for (int i = 0; i < num_tiles; i++)
        {
            SpriteClips[i] = {i * 20, 0, width, height};
        }
    }
};

void Game::Settings_Menu(int percent_bombs,int ladox_temp)
{
    SDL_SetRenderDrawColor(renderer, 21, 29, 40, 100);
    SDL_RenderClear(renderer);

    draw_text("SETTINGS", 20, 20, 199, 207, 204, 15, 20, 20, 21, 29, 40, 60, 40);
    draw_text("X", (ladox * 20) + 10, 20, 199, 207, 204, 15, (ladox * 20) + 10, 20,21,29,40, 60, 40);

    draw_text("NUMBER OF BOMBS", 20, 60, 199, 207, 204, 15, 40, 20, 21,29,40, 60, 40);
    draw_text("HEIGHT", 20, 110, 199, 207, 204, 15, 80, 20, 21,29,40, 60, 40);
    draw_text("WIDTH", 20, 160, 199, 207, 204, 15, 120, 20, 21,29,40, 60, 40);

    Draw_Slider(1, percent_bombs, 20 + (percent_bombs*163/20),ladox_temp);
    Draw_Slider(2, percent_bombs, 20,ladox_temp);
    Draw_Slider(3, percent_bombs, 20,ladox_temp);
};

void Game::Draw_Slider(int slidernum, int percent_bombs,int sliderpos,int ladox_temp)
{
    // Sliders
    SDL_SetRenderDrawColor(renderer,21,29,40,100);   

    switch (slidernum)
    {
    case 1:
    {
        SDL_Rect bg1 = {20, 85, 160, 15};
        SDL_RenderFillRect(renderer, &bg1);

        SDL_SetRenderDrawColor(renderer, 199, 207, 204, 100);

        SDL_Rect slide1 = {20, 90, 160, 5};
        SDL_RenderFillRect(renderer, &slide1);

        SDL_SetRenderDrawColor(renderer, 70, 130, 50, 100);

        SDL_Rect slider1 = {sliderpos, 85, 7, 15};
        SDL_RenderFillRect(renderer, &slider1);
        SDL_RenderPresent(renderer);

        draw_text("%", (ladox_temp * 20) + 10, 80, 199, 207, 204, 15,ladox_temp , 4,21,29,40, 30, 20);
        draw_text(to_string(percent_bombs), (ladox_temp * 20) - 10, 80, 199, 207, 204, 15, ladox_temp - 1, 4, 21,29,40, 30, 20);

        break;
    }
    case 2:
    {
        SDL_Rect bg2 = {20, 135, 160, 15};
        SDL_RenderFillRect(renderer, &bg2);

        SDL_SetRenderDrawColor(renderer, 199, 207, 204, 100);

        SDL_Rect slide2 = {20, 140, 160, 5};
        SDL_RenderFillRect(renderer, &slide2);

        SDL_SetRenderDrawColor(renderer, 70, 130, 50, 100);

        SDL_Rect slider2 = {sliderpos, 135, 7, 15};
        SDL_RenderFillRect(renderer, &slider2);
        SDL_RenderPresent(renderer);

        draw_text(to_string(ladoy), (ladox_temp * 20) - 10, 130, 199, 207, 204, 15,ladox_temp - 1, 6, 21, 29,40,30, 40);

        break;
    }
    case 3:
    {
        SDL_Rect bg3 = {20, 185, 160, 15};
        SDL_RenderFillRect(renderer, &bg3);

        SDL_SetRenderDrawColor(renderer, 199, 207, 204, 100);

        SDL_Rect slide3 = {20, 190, 160, 5};
        SDL_RenderFillRect(renderer, &slide3);

        SDL_SetRenderDrawColor(renderer, 70, 130, 50, 100);

        SDL_Rect slider3 = {sliderpos, 185, 7, 15};
        SDL_RenderFillRect(renderer, &slider3);
        SDL_RenderPresent(renderer);

        draw_text(to_string(ladox), (ladox_temp * 20) - 10, 180, 199, 207, 204, 15, ladox_temp - 1, 9, 21,29,40, 50, 20);

        break;
    }
    }
};

void Game::Settings_Menu_Loop()
{
    SDL_Event menu;
    int quit = 0;
    Uint32 buttons;
    int ladox_temp = ladox;

    int percent_bombs = numbombas * 100 / (ladox * ladoy);

    Settings_Menu(percent_bombs,ladox_temp);

    // Loop do Menu
    while (quit == 0)
    {
        // While there's an event to handle
        while (SDL_PollEvent(&event))
        {
            int xmouse, ymouse, xmouse_cord, ymouse_cord;

            SDL_PumpEvents(); // make sure we have the latest mouse state.

            buttons = SDL_GetMouseState(&xmouse, &ymouse);

            xmouse_cord = (int)(xmouse / 20);
            ymouse_cord = (int)(ymouse / 20);

            // LEFT BUTTON CLICK
            if ((buttons & SDL_BUTTON_LMASK) != 0)
            {
                if (xmouse_cord < ladox_temp + 1 && ymouse_cord < 2 && xmouse_cord > ladox_temp - 1 && ymouse_cord > 0)
                {
                    // Quit the program
                    quit = 1;
                }
                //NUMBER OF BOMBS SLIDER
                if(xmouse < 173 && ymouse < 100 && xmouse > 20 && ymouse > 85)
                {
                    percent_bombs = (xmouse-10)*20/163;
                    numbombas = (double)((double)percent_bombs/100)*((double)ladox*ladoy);
                    Draw_Slider(1, percent_bombs,xmouse,ladox_temp);
                }
                //HEIGHT SLIDER
                if(xmouse < 173 && ymouse < 150 && xmouse > 20 && ymouse > 135)
                {
                    ladoy = 9 + (xmouse*15/160);
                    Draw_Slider(2, percent_bombs,xmouse,ladox_temp);
                }
                //WIDTH SLIDER
                if(xmouse < 173 && ymouse < 200 && xmouse > 20 && ymouse > 185)
                {
                    ladox = 9 + (xmouse*25/160);
                    Draw_Slider(3, percent_bombs,xmouse,ladox_temp);
                }
            }
        }
    }
}

int Game::Get_ladox()
{
    return ladox;
};

int Game::Get_ladoy()
{
    return ladoy;
};

int Game::Get_numbombas()
{
    return numbombas;
};
