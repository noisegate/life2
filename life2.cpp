
/*
_     _  __
| |   (_)/ _| ___
| |   | | |_ / _ \
| |___| |  _|  __/
|_____|_|_|  \___|

*/
#include <cmath>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>

#define MAX 1000
#define MAXCIJFERS 20
using namespace std;

#define LOOPX                                                                  \
  int x = hoeki;                                                               \
  x < (hoeki + breedte);                                                       \
  x++
#define LOOPY                                                                  \
  int y = hoekj;                                                               \
  y < (hoekj + hoogte);                                                        \
  y++

class Life {
private:
  bool wereld[MAX][MAX];
  bool hulpwereld[MAX][MAX];
  int hoogte, breedte, hoeki, hoekj;
  int schuif, percentage, generaties;
  char kies, levend, dood;
  int getal;
  void copytohulp();
  void copytoreal();

public:
  Life(); // constructor
  Life(int, int);
  void menu();
  void sub_Menu();
  void lees_Optie();
  void lees_Getal();
  int random_Getal();
  void wereldafdruk();
  void drukaf();
  void vulrandom();
  void maakschoon();
  void zetpercentage();
  int aantalburen(int, int);
  void gaan();
  void start();
  void heelschoon();
  void schoon();
  void glidergun();
  void karakters();
};

Life::Life() {
  hoogte = 40;
  breedte = 80;
  hoeki = 1;
  hoekj = 1;
}

Life::Life(int width, int height) {
  hoogte = height;
  breedte = width;
  hoeki = 3;
  hoekj = 3;
}

void Life::heelschoon() {
  for (int i = 0; i < MAX; i++)
    for (int j = 0; j < MAX; j++)
      wereld[i][j] = false;

} // wereld schoonmaken

void Life::schoon() {
  for (int y = 0; y < hoogte; y++) {
    for (int x = 0; x < breedte; x++)
      wereld[y + hoekj][x + hoeki] = false;
  }
} // view schoonmaken

void Life::copytohulp() {
  for (int x = 0; x < MAX; x++)
    for (int y = 0; y < MAX; y++)
      hulpwereld[y][x] = wereld[y][x];
}
void Life::copytoreal() {
  for (int x = 0; x < MAX; x++)
    for (int y = 0; y < MAX; y++)
      wereld[y][x] = hulpwereld[y][x];
}

void Life::drukaf() {
  for (LOOPY) {
    for (LOOPX)
      cout << (wereld[y][x] ? 'x' : ' ');
    cout << endl;
  }
  // menu();
} // afdrukken van de view

void Life::karakters() {}

void Life::wereldafdruk() {
  for (int i = 0; i < MAX; i++)
    for (int j = 0; j < MAX; j++)
      cout << (wereld[i][j] ? 'x' : ' ');
  cout << endl;
} // afdrukken van gehele wereld

void Life::zetpercentage() {
  cout << "Nieuwe waarde.. " << endl;
  lees_Getal();

} // stel percentage in tussen 0 en 100

void Life::start() {
  kies = 'a';
  while (kies != 's' && kies != 'S') {
    menu();
  }
} // start

void Life::menu() {
  cout << "(H)eelschoon s(C)hoon (R)andom (P)arameters (S)toppen (G)lidergun"
       << endl;
  lees_Optie();
  switch (kies) {
  case 'h':
  case 'H':
    heelschoon();
    break;
  case 'c': // schoon
  case 'C': // schoon
    cout << "Hier moet nog ge-sChoon-d worden." << endl;
    schoon();
    break;
  case 'r': // random
  case 'R': // random
    vulrandom();
    break;
  case 'p': // submenu
  case 'P': // submenu
    sub_Menu();
    break;
  case 'd':
  case 'D':
    // heelschoon();
    drukaf();
    break;
  case 'g':
  case 'G':
    glidergun();
    break;
  case 'w':
    wereldafdruk();
    break;
  case 'a':
    for (int teller = 0; teller < 1000; teller++) {
      copytohulp();
      for (LOOPX)
        for (LOOPY) {
          int dummy = aantalburen(x, y);
          if (((dummy == 2) || (dummy == 3)) && wereld[y][x])
            hulpwereld[y][x] = true;
          else if (dummy == 3 && !wereld[y][x])
            hulpwereld[y][x] = true;
          else
            hulpwereld[y][x] = false;
        }
      copytoreal();
      drukaf();
    }
    break;
  case 's': // stoppen
  case 'S': // stoppen
    break;
  }
} // menu

void Life::sub_Menu() {

  bool doen = true;
  cout << "(T)erug (P)ercentage (K)arakters (S)tapgrootte" << endl;
  lees_Optie();
  while (doen) {
    switch (kies) {
    case 't': // terug
    case 'T': // terug
      doen = false;
      break;
    case 'p': // percentage
    case 'P': // percentage
      zetpercentage();
      doen = false;
      cout << getal;
      break;
    case 'k':
    case 'K':
      karakters();
      break;
    default:
      // sub_Menu(Life &mylife);
      break;
    }
  } // while
} // submenu

void Life::vulrandom() {
  for (int x = hoeki; x < (hoeki + breedte); x++)
    for (int y = hoekj; y < (hoekj + hoogte); y++)
      wereld[y][x] = (random_Getal() < 500 ? false : true);
} // randomn vullen van view

void Life::lees_Optie() {
  char weg = 'a';
  kies = '\n';
  do {
    cin.get(kies);
  } while (kies == '\n');
  do {
    cin.get(weg);
  } while (weg != '\n');
} // lees optie in

void Life::lees_Getal() {
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
} // lees getal in

// RANDOMGENERATOR
// SHEET 10
// geef random getal tussen 0 en 999
int Life::random_Getal() {
  static int _getal = 42;
  _getal = (221 * _getal + 1) % 1000; // niet aan knoeien
  return _getal;

} // randomgetal

int Life::aantalburen(int x, int y) {
  // check check
  int buren = 0;

  if((x > 0) && (y > 0) && (x < MAX) && (y < MAX)){
    if (wereld[y - 1][x - 1])
      buren++;
    if (wereld[y][x - 1])
      buren++;
    if (wereld[y + 1][x - 1])
      buren++;
    if (wereld[y - 1][x])
      buren++;
    if (wereld[y + 1][x])
      buren++;
    if (wereld[y - 1][x + 1])
      buren++;
    if (wereld[y][x + 1])
      buren++;
    if (wereld[y + 1][x + 1])
      buren++;
  }
  
  return buren;
}

void Life::glidergun() {
  int x = 0;
  int y = 0;
  string line;
  string filenaam;
  cin >> filenaam;
  ifstream myfile;
  myfile.open(filenaam.c_str());
  if (myfile.is_open()) {
    while (getline(myfile, line)) {
      for (unsigned int i = 0; i < line.length(); i++) {
        x = i;
        if (line[i] == 'x')
          wereld[y][x] = true;
        if (line[i] == ' ')
          wereld[y][x] = false;
        cout << line[i];
      }
      y++;
      cout << endl;
    }
    myfile.close();
  } else
    cout << "Deze file kan niet geopend worden.";
} // glidergun

int main() {

  Life mylife(80, 60);

  mylife.heelschoon();
  mylife.start();

  return 0;
}
