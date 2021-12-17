#include "mine_header.h"

using namespace std;

int main(int argc, char *argv[])
{
  SDL_Event event;

  int ladox = 10;
  int ladoy = 10;
  int numbombas = 15;
  bool inicial = true;
  bool stop = false;
  int quit = 0;
  int numflags = 0;
  clock_t time_init;
  int tempstring = 0;

  /*while (numbombas >= (ladox * ladoy) - 9)
  {
    cout << "\nNumero de Bombas:";
    cin >> numbombas;
  }*/

  vector<vector<cell>> pontos(ladox, vector<cell>(ladoy));

  srand(time(NULL));

  Game a;

  a.criarjanela();
  a.GetTileMap("tile.png");
  a.reset(numflags, ladox, ladoy, pontos);

  // Loop do programa
  while (quit == 0)
  {
    // While there's an event to handle
    while (SDL_PollEvent(&event))
    {
      if (event.type == SDL_QUIT)
      {
        // Quit the program
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

      // SDL_Log("Mouse cursor is at %d, %d", xmouse_cord, ymouse_cord);

      // LEFT BUTTON CLICK
      if ((buttons & SDL_BUTTON_LMASK) != 0)
      {
        if (xmouse_cord < ladox + 1 && ymouse_cord < ladoy + 1 && xmouse_cord > 0 && ymouse_cord > 0)
        {
          int xfixo = xmouse_cord - 1;
          int yfixo = ymouse_cord - 1;

          // SDL_Log("Mouse Button 1 (left) is pressed.");

          if (inicial == true && pontos[xfixo][yfixo].flag == false && stop == false)
          {
            a.gerarbombas(numbombas, xfixo, yfixo, ladox, ladoy, pontos);
            a.getaround(xfixo, yfixo, ladox, ladoy, pontos);
            inicial = false;
            time_init = clock();
          }

          else if (pontos[xfixo][yfixo].bomba == true && inicial == false && pontos[xfixo][yfixo].flag == false && stop == false)
          {
            for (int i = 0; i < ladoy; i++)
            {
              for (int j = 0; j < ladox; j++)
              {
                if (pontos[j][i].bomba == true)
                {
                  a.drawbomb(j + 1, i + 1);
                }
              }
            }
            // SDL_Log("..............................Perdeste");
            inicial = true;
            stop = true;
          }

          else if (pontos[xfixo][yfixo].flag == false && stop == false && pontos[xfixo][yfixo].exposto == false)
          {
            pontos[xfixo][yfixo].exposto = true;
            if (a.getnumbombas(xfixo, yfixo, ladox, ladoy, pontos) == 0)
            {
              a.getaround(xfixo, yfixo, ladox, ladoy, pontos);
            }
            else
            {
              a.drawnum(xfixo, yfixo, a.getnumbombas(xfixo, yfixo, ladox, ladoy, pontos));
            }
          }
        }
        // RESET BUTTON
        else if (xmouse_cord < 8 && ymouse_cord < ladoy + 4 && xmouse_cord > 3 && ymouse_cord >= ladoy + 2)
        {
          a.reset(numflags, ladox, ladoy, pontos);
          stop = false;
          inicial = true;
        }
      }

      // RIGHT BUTTON CLICK
      if ((buttons & SDL_BUTTON_RMASK) != 0)
      {
        if (xmouse_cord < ladox + 1 && ymouse_cord < ladoy + 1 && xmouse_cord > 0 && ymouse_cord > 0)
        {
          int xfixo = xmouse_cord - 1;
          int yfixo = ymouse_cord - 1;

          // SDL_Log("Mouse Button 1 (right) is pressed.");

          if (pontos[xfixo][yfixo].exposto == false && stop == false)
          {
            numflags = a.drawflag(numflags, xfixo, yfixo, pontos);
          }
        }
      }
    }

    if (numflags == numbombas)
    {
      if (a.win(numbombas, ladox, ladoy, pontos))
      {
        SDL_Log("..............................Ganhaste");
        inicial = true;
        stop = true;
      }
    }

    if (stoi(a.elapsed_time(time_init)) != tempstring && inicial == false)
    {
      // Play time timer
      a.draw_text(a.elapsed_time(time_init), 30, (ladoy + 2) * 20 + 10, 199, 207, 204, 18, 0, ladoy + 2, 21, 29, 40, 60, 40);
      tempstring = stoi(a.elapsed_time(time_init));
    }
  }
  return 0;
}
