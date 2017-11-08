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
    char kies;
    int getal;
  public:
    Life (); //constructor
    void menu();
    void sub_Menu();
    void lees_Optie();
    void lees_Getal();
    int random_Getal();
    void drukaf ();
    void vulrandom ();
    void maakschoon ();
    void zetpercentage ();
    void gaan ();
    void start();
    void heelschoon();
    void schoon();
};

Life::Life(){
  hoogte = 20;
  breedte = 30;
  hoeki = 3;
  hoekj = 3;
}

void Life::heelschoon(){
  for (int i=0;i<MAX;i++)
    for (int j=0;j<MAX;j++)
      wereld[i][j]=false;

}

void Life::drukaf(){
  for(int y=0; y<hoogte;y++){
    for (int x=0; x<breedte;x++)
      cout << (wereld[y+hoekj][x+hoeki]?'x':' ');
    cout << endl;
  }
}

//stel percentage in tussen 0 en 100
void Life::zetpercentage(){
  cout << "Nieuwe waarde.. " << endl;
  lees_Getal();
  //cin >> getal;
}

void Life::start(){
  kies = 'a';
  while (kies != 's' && kies != 'S') {
    menu();
  }
}

void Life::menu() {
  cout << "s(C)hoon (R)andom (P)arameters (S)toppen" << endl;
  lees_Optie();
  switch (kies) {
  case 'c': // schoon
  case 'C': // schoon
    cout << "Hier moet nog ge-sChoon-d worden." << endl;
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
    //heelschoon();
    drukaf();
  case 't':
    lees_Getal();
    cout << getal << endl;
    break;
  case 's': // stoppen
  case 'S': // stoppen
    break;
  }
}

// SUBMENU
void Life::sub_Menu() {

  bool doen=true;
  cout << "(T)erug (P)ercentage" << endl;
  lees_Optie();
  while(doen){
    switch (kies) {
    case 't': //terug
    case 'T': //terug
      doen=false;
      break;
    case 'p': //percentage
    case 'P': //percentage
      zetpercentage();
      doen=false;
      cout << getal;
      break;
    default:
      //sub_Menu(Life &mylife);
      break;
    }
  }//while
}

void Life::vulrandom(){
  for (int x = hoeki; x<(hoeki+breedte); x++)
    for (int y = hoekj; y<(hoekj+hoogte); y++)
      wereld[y][x]=(random_Getal()<500?false:true);
}

// LEESOPTIE
void Life::lees_Optie() {
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
}

// RANDOMGENERATOR
// SHEET 10
// geef random getal tussen 0 en 999
int Life::random_Getal() {
  static int _getal = 42;
  _getal = (221 * _getal + 1) % 1000; // niet aan knoeien
  return _getal;

} // randomgetal

int main() {

  Life mylife;

  mylife.heelschoon();
  mylife.start();

  return 0;
}
// HOOFDMENU
