/*
 _     _  __
| |   (_)/ _| ___
| |   | | |_ / _ \
| |___| |  _|  __/
|_____|_|_|  \___|

*/
#include <cmath>
#include <cstdlib>
#include <iostream>

#define MAX 1000
#define MAXCIJFERS 20
using namespace std;


void lees_Optie (char & );
void lees_Getal (int &, int);
void random_Getal ();
void menu (char & , int &);
void sub_Menu ();

class Life {
  private:
    bool wereld[MAX][MAX];
    bool hulpwereld[MAX][MAX];
    int hoogte, breedte, hoeki, hoekj;
    int schuif, percentage, generaties;
  public:
    Life (); //constructor
    void menu();
    void drukaf ();
    void vulrandom ();
    void maakschoon ();
    void zetpercentage (int& getal);
    void gaan ();
};

Life::Life(){
  hoogte = 20;
  breedte = 30;
  hoeki = 3;
  hoekj = 3;
}

//stel percentage in tussen 0 en 100
void Life::zetpercentage(int& getal){
  lees_Getal(getal, 100);
  cout << "Nieuwe waarde.. " << endl;
  cin >> getal;
}


int main() {

  Life mylife;

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
    random_Getal();
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
  bool doen=true;
  cout << "(T)erug (P)ercentage" << endl;
  lees_Optie(kies);
  while(doen){
    switch (kies) {
    case 't': //terug
    case 'T': //terug
      doen=false;
      break;
    case 'p': //percentage
    case 'P': //percentage
      //mylife.zetpercentage();
      doen=false;
      break;
    default:
      //sub_Menu(Life &mylife);
      break;
    }
  }//while
}
// LEESOPTIE
void lees_Optie(char& kies) {
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
void lees_Getal(int& getal, int maximum) {
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
// RANDOMGENERATOR
// SHEET 10
// geef random getal tussen 0 en 999
void random_Getal() {
  static int getal = 42;
  getal = (221 * getal + 1) % 1000; // niet aan knoeien
  //return getal;
  cout << 1 + rand() % 11 << endl;
} // randomgetal
