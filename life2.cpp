
/*
_     _  __
| |   (_)/ _| ___
| |   | | |_ / _ \
| |___| |  _|  __/
|_____|_|_|  \___|

*/

//Programma Life
//Gebruikte compiler: clang++
//In dit programma kan het spel Life worden gespeeld

#include <cmath>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <unistd.h>
//#include <stdio.h>

#define MAX 1000
#define MAXCIJFERS 20
#define SERIEGROOTTE 100
using namespace std;

#define MENUSTRING \
"(H)eelschoon s(C)hoon (R)andom (E)en (P)arameters (S)toppen g(A)an (D)ruk af (G)lidergun (V)erschuif[i/j/k/m] (T)oggle[w/a/s/z]"

#define LOOPX                                                                  \
  int x = hoeki;                                                               \
  x < (hoeki + breedte);                                                       \
  x++

#define LOOPY                                                                  \
  int y = hoekj;                                                               \
  y < (hoekj + hoogte);                                                        \
  y++

#define WORLDLOOPX                                                             \
  int x = 0;                                                                   \
  x < MAX;                                                                     \
  x++;

#define WORLDLOOPY                                                             \
  int y = 0;                                                                   \
  y < MAX;                                                                     \
  y++;

class Life {
private:
  bool wereld[MAX][MAX];
  bool hulpwereld[MAX][MAX];
  int breedte, hoogte, hoeki, hoekj;
  int schuif, percentage, generaties;
  int cursorx;
  int cursory;
  char kies, levend, dood;
  int getal;
  int step;
  double fraction;
  void killborder();
  void copytohulp();
  void copytoreal();
  void verschuif();
  void footer();
  void eengeneratie(bool, bool);
  void toggle();
  void stapgrootte();

public:
  Life(); // constructor
  Life(int width, int height);
  void menu();
  void sub_Menu();
  char lees_Optie();
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

//Default constructor
Life::Life() {
  breedte = 80;
  hoogte = 40;

  hoeki = 1;
  hoekj = 1;
  levend = 'x';
  dood = ' ';
  fraction = 0.5;
  step=1;
}

//Constructor
Life::Life(int width, int height):breedte(width),hoogte(height) {
  hoeki = 3;
  hoekj = 3;
  levend = 'x';
  dood = ' ';
  fraction=0.5;
  step=1;
}

//Toggle klapt levend en dood om met cursorpositie
void Life::toggle(){
  char key;
  key = ' ';
  while(key!='q'){
    key = lees_Optie();
    switch(key){
      case 'w':
        cursory--;
        break;
      case 'z':
        cursory++;
        break;
      case 'a':
        cursorx--;
        break;
      case 's':
        cursorx++;
        break;
    }
    if (cursorx<hoeki) cursorx=hoeki;
    if (cursory<hoekj) cursory=hoekj;
    if (cursorx>hoeki+breedte) cursorx=hoeki+breedte;
    if (cursory>hoekj+hoogte) cursory=hoekj+hoogte;
    wereld[cursory][cursorx] = !wereld[cursory][cursorx];
    drukaf();
    cout << "(" << cursorx << ","<< cursory << ")";
  }
}

//Een generatie, er wordt één generatie uitgevoerd
void Life::eengeneratie(bool metmenu, bool afdrukken){
  killborder();
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
  if (afdrukken){
    drukaf();
    if (metmenu) footer();
    cout<<endl;
    usleep(100000);
  }
}

//Heelschoon, maakt de hele wereld leeg
void Life::heelschoon() {
  for (int i = 0; i < MAX; i++)
    for (int j = 0; j < MAX; j++)
      wereld[i][j] = false;

}

//Schoon, maakt de view schoon
void Life::schoon() {
  for (int y = 0; y < hoogte; y++) {
    for (int x = 0; x < breedte; x++)
      wereld[y + hoekj][x + hoeki] = false;
  }
}

//Killborder, maakt de randen van de wereld dood
void Life::killborder(){
  for (int x=0;x<MAX;x++) {
    wereld[0][x]=false;
    wereld[MAX-1][x]=false;
  }//for
  for (int y=0;y<MAX;y++) {
    wereld[y][0]=false;
    wereld[y][MAX-1]=false;
  }//for
}

//Copytohulp, kopieert naar hulpwereld
void Life::copytohulp() {
  for (int x = 0; x < MAX; x++)
    for (int y = 0; y < MAX; y++)
      hulpwereld[y][x] = wereld[y][x];
}
//Copyhulp, kopieert naar wereld
void Life::copytoreal() {
  for (int x = 0; x < MAX; x++)
    for (int y = 0; y < MAX; y++)
      wereld[y][x] = hulpwereld[y][x];
}
//Karakters, verwisselen van karakters voor levend en dood
void Life::karakters() {
  cout << "levend: ";
  levend = lees_Optie();
  cout << "dood: ";
  dood = lees_Optie();
}
//Wereldafdruk, drukt de gehele wereld af
void Life::wereldafdruk() {
  for (int i = 0; i < MAX; i++)
    for (int j = 0; j < MAX; j++)
      cout << (wereld[i][j] ? 'x' : ' ');
  cout << endl;
}
//Zetpercentage, bepalen van percentage levende cellen tussen 0 en 100
void Life::zetpercentage() {
  cout << "Nieuw percentage levende cellen.. " ;
  lees_Getal();
  fraction = (double)(getal/100.0);
}

void Life::stapgrootte(){
  cout << "Nieuwe stapgrootte.. ";
  lees_Getal();
  step = getal;
}

//Start, begin van programma met schone wereld
void Life::start() {
  kies = 'a';
  drukaf();
  while (kies != 's' && kies != 'S') {
    menu();
  }
} // start
//Footer, print menu
void Life::footer(){
  cout << MENUSTRING;
}
//Menu, opties in menu
void Life::menu() {
  footer();
  kies = lees_Optie();
  switch (kies) {
  case 'e': //Een generatie
  case 'E':
    eengeneratie(false,true);
    break;
  case 'h': //Heelschoon
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
  case 'd': //view afdrukken
  case 'D': //view afrdukken
    // heelschoon();
    drukaf();
    break;
  case 'g': //glidergun
  case 'G': //glidergun
    glidergun();
    break;
  case 'v': //verschuiven
    verschuif();
    break;
  case 'w': //wereld afdrukken
    wereldafdruk();
    break;
  case 'a': //generaties afdrukken
    gaan();
    break;
  case 's': // stoppen
  case 'S': // stoppen
    break;
  case 't': //cellen omklappen
  case 'T': //cellen omklappen
    toggle();
    break;

  }//switch
}
//Submenu, keuze in submenu
void Life::sub_Menu() {
  char localkies;
  bool doen = true;
  cout << "(T)erug (P)ercentage (K)arakters (S)tapgrootte" << endl;

  while (doen) {
    localkies = lees_Optie();
    switch (localkies) {
    case 't': // terug
    case 'T': // terug
      doen = false;
      cout << "leaving submenu" << endl;
      break;
    case 'p': // percentage
    case 'P': // percentage
      zetpercentage();
      doen = false;
      break;
    case 's': //stapgrootte
    case 'S': //stapgrootte
      stapgrootte();
      doen=false;
      break;
    case 'k': //karakters
    case 'K': //karakters
      karakters();
      doen=false;
      break;
    default:
      cout << "Deze optie bestaat niet";
      break;
    }
  } // while
}
//Gaan, toont meerdere generaties achter elkaar
void Life::gaan(){
  for (int teller = 0; teller < SERIEGROOTTE-1; teller++) {
    eengeneratie(true,teller%step==0);
  }//for
  eengeneratie(false,true);
}
//Drukaf, print de view
void Life::drukaf() {
  for (int i=0; i<breedte;i++) cout << "=";
  cout<<endl;

  for (LOOPY) {
    for (LOOPX)
      cout << (wereld[y][x] ? levend : dood);
    cout << endl;
  }//for

  for (int i=0; i<breedte;i++) cout << "=";
  cout << endl;
}
//Verschuif, verschuiven van view
void Life::verschuif(){
  char key;
  key=' ';
  while(key!='q'){
    cin.get(key);
    switch(key){
      case 'i':
        hoekj--;
        if (hoekj<0) hoekj=0;
        break;
      case 'm':
        hoekj++;
        if (hoekj>(MAX-hoogte))hoekj=MAX-hoogte;
        break;
      case 'j':
        hoeki--;
        if (hoeki<0) hoeki=0;
        break;
      case 'k':
        hoeki++;
        if (hoeki>(MAX-breedte))hoeki=MAX-breedte;
        break;
      default:
        {}
    }//switch
    drukaf();
  }//while
  cout << "x hoek" << hoeki << ", y hoek" << hoekj << endl;
}
//Vulrandom, vullen van de view met random
void Life::vulrandom() {
  int thresh;
  thresh = (int)((1.0-fraction)*1000);

  for (int x = hoeki; x < (hoeki + breedte); x++)
    for (int y = hoekj; y < (hoekj + hoogte); y++)
      wereld[y][x] = (random_Getal() < thresh ? false : true);
} // randomn vullen van view

//Lees optie, lees een optie in
char Life::lees_Optie() {
  char weg;
  char dummy = '\n';
  do {
    cin.get(dummy);
  } while (dummy == '\n');

  cin.get(weg);
  return dummy;
}
//Lees getal, leest getal in
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
    dummygetal += (myarray[j] - 48) * pow(10, teller-j-1);
  }

  getal = dummygetal;
} // lees getal in

// RANDOMGENERATOR
// SHEET 10
// geef random getal tussen 0 en 999
int Life::random_Getal() {
  static int _getal = 42;
  _getal = (221 * _getal + 1) % 1000; // niet aan knoeien
  return _getal;

}
//Aantalburen, bepaald het aantal buren
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
//Glidergun, leest een txt file in (bijv: glidergun.txt)
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
    }//while
    myfile.close();
  }//if
   else
    cout << "Deze file kan niet geopend worden.";
}

int main() {

  string line;
  ifstream infofile;
  infofile.open("info.txt");
  if (infofile.is_open()){
    while (getline(infofile, line)){
      cout << line << endl;
    }//while
  }//if
   infofile.close();

  cout << "Press enter to continue .. " << endl;
  cin.get(); // line;

  Life mylife(60,30);
  mylife.heelschoon();
  mylife.start();

  return 0;
}
