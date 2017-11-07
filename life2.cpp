#include "life2.h"
#include <cmath>
#include <cstdlib>
#include <iostream>
/*
 _     _  __
| |   (_)/ _| ___
| |   | | |_ / _ \
| |___| |  _|  __/
|_____|_|_|  \___|

*/

#define MAXCIJFERS 20

using namespace std;

int main() {
  char kies; // kiezen van C,R,P of S
  int getal;

  kies = 'a'; // kies wordt gebruikt in het menu

  while (kies != 's' && kies != 'S') {
    menu(kies, getal);
  }

  return 0;
}
// HOOFDMENU
void menu(char &kies, int &getal) {
  cout << "s(C)hoon (R)andom (P)arameters (S)toppen" << endl;
  lees_Optie(kies);
  switch (kies) {
  case 'c': // schoon
  case 'C': // schoon
    cout << "Hier moet nog ge-sChoon-d worden." << endl;
    break;
  case 'r': // random
  case 'R': // random
    cout << "Tekstje op scherm." << endl;
    break;
  case 'p': // submenu
  case 'P': // submenu
    sub_Menu();
    break;
  case 't':
    lees_Getal(getal, 1000);
    cout << getal << endl;
    break;
  case 's': // stoppen
  case 'S': // stoppen
    break;
  }
}
// SUBMENU
void sub_Menu() {
  char kies;
  cout << "(T)erug" << endl;
  lees_Optie(kies);
  switch (kies) {
  case 't':
    break;
  case 'T':
    break;
  }
}
// LEESOPTIE
void lees_Optie(char &kies) {
  char weg = 'a';
  kies = '\n';
  do {
    cin.get(kies);
  } while (kies == '\n');
  do {
    cin.get(weg);
  } while (weg != '\n');
}
// LEESGETAL
void lees_Getal(int &getal, int maximum) {
  char dummy;
  char myarray[MAXCIJFERS];
  int teller = 0;

  do {
    cin.get(dummy);
    if (isdigit(dummy)) {
      myarray[teller] = dummy;
      teller++;
      if (teller > MAXCIJFERS) {
        teller = MAXCIJFERS;
      }
    }
  } while (dummy != '\n');

  int dummygetal = 0;

  for (int j = 0; j < teller; j++) {
    dummygetal = 0;
    for (int i = 0; i < j; i++) {
      dummygetal += (myarray[i] - 48) * pow(10, j - i - 1);

      // dummygetal += (myarray[i] - 48) * pow(10, teller - i - 1);
      // cout << i;
    }
    // cout << endl << dummygetal << endl;
  }
  // cout << endl << dummygetal << endl;

  getal = dummygetal;
}
