#include <iostream>
#include <stdlib.h>

using namespace std;

int main(){
  srand(time(NULL));

  int computer = rand() % 3 + 1;

  int user = 0;

  cout << "Play Rock Paper Scissor" << endl;
  cout << "1 = rock, 2 = paper, 3 = scissors:" << endl;

  cin >> user;

  bool win = false;

  if (computer == user) {
    cout << "Draw";
  } else {

    switch(user) {
      case 1:
        win = (computer == 2) ? false : true;

      case 2:
        win = (computer == 3) ? false : true;
      case 3:
        win = (computer == 1) ? false : true;

    }
  if (win == true) {
    cout << "Great You Win!" << endl;
  } else {
    cout << "You Lose" << endl;
  }
  }
  
}