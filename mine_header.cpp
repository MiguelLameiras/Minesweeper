#include "mine_header.h"

using namespace std;

int cores[14][3] = {{11, 120, 79}, {10, 106, 70}, {8, 93, 62}, {7, 80, 53}, {6, 67, 44}, {5, 53, 35}, {4, 40, 26}, {15, 166, 110}, {49, 109, 14}, {29, 64, 8}, {26, 57, 7}, {22, 50, 6}, {19, 43, 5}, {16, 36, 4}};

Game::Game()
{
    SDL_Init(SDL_INIT_EVERYTHING); // Initialize SDL2
    TTF_Init();
    IMG_Init(IMG_INIT_PNG);
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

void Game::reset(int &numflags, int ladox, int ladoy, vector<vector<cell>> &pontos)
{
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

    SDL_RenderPresent(renderer);
}

void Game::gerarbombas(int numbombas, int xfixo, int yfixo, int ladox, int ladoy, vector<vector<cell>> &pontos)
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

    // SDL_SetWindowSize(window,10,10);

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
        shadow = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
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
                if (Game::getnumbombas(xtemp + j, ytemp + i, ladox, ladoy, pontos) != 0 && pontos[xtemp + j][ytemp + i].flag == false)
                {
                    Game::drawnum(xtemp + j, ytemp + i, Game::getnumbombas(xtemp + j, ytemp + i, ladox, ladoy, pontos));
                    pontos[xtemp + j][ytemp + i].exposto = true;
                }
                if (getnumbombas(xtemp + j, ytemp + i, ladox, ladoy, pontos) == 0 && pontos[xtemp + j][ytemp + i].exposto == false && pontos[xtemp + j][ytemp + i].flag == false)
                {
                    SDL_SetRenderDrawColor(renderer, 21, 29, 40, 100);
                    SDL_Rect rect = {(xtemp + j + 1) * 20, (ytemp + j + 1) * 20, 20, 20};
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

void Game::Draw_Shadow(int x, int y)
{
    SDL_SetRenderDrawColor(shadow, 21, 29, 40, 100);
    SDL_Rect shadow_rect = {x, y, 20, 20};
    SDL_RenderFillRect(shadow, &shadow_rect);
    SDL_RenderPresent(shadow);
};