#include <SDL2/SDL.h>
#include <time.h>
#include <iostream>
#include <vector>
#include "mine_header.h"

using namespace std;

int main(int argc, char *argv[])
{
  int ladox = 100;
  int ladoy = 100;
  int numbombas = 10000;

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

  vector<vector<cell>> pontos(ladox, vector<cell>(ladoy));
  
  gamefunc(ladox,ladoy,numbombas,pontos);
  
  return 0;
}
