#include <iostream>
#include <ncurses.h>
#include <stdlib.h> // for calling system
#include <unistd.h> // for calling sleep
#include "tetris.h"
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

int main()
{
  // choose game mode and read game record
  string username;
  int best_score;
  int choice;

  cout << "1: New User 2: Use an Existing Username" << endl;
  cout << "Please input your choice: ";
  cin >> choice;
  cout << "Please input your username: ";
  cin >> username;

  // new user
  if ( choice == '1' ) {
    best_score = 0;
  }
  // old user
  else {
    ifstream fin;
    fin.open("gamerecord.txt");
    string record, past_user;
    int past_score;
    while (getline(fin, record)) {
      istringstream iss(record);
      record >> past_user >> past_score;
      if (past_user == username) {
        best_score = past_score;
        break;
      }
    }
    fin.close();
  }

  initscr();    // begin NCURSES mode

  curs_set(0);  // set cursor invisible

  noecho();     // do not dispaly characters input by user

  raw();        // forbid line buffering

  refresh();    // display virtual window

  // the main playing window
  main_win = initial_playwin(height, width, 0, 0);
  build_boundary(field);

  // the score field
  score_box = initial_playwin(sheight, swidth, 0, width+5);
  // print content in score box
  mvprintw(0, width+5+2, "Username: ");
  mvprintw(2, width+5+2, "Best Score: ");
  mvprintw(4, width+5+2, "Score: ", "%d", s);

  wrefresh(main_win); // update the main playing window
  wrefresh(score_box); // update the score field
  refresh();

  // initialize middle piece
  tetris * mp = new tetris;
  initial_tetris( *mp );

  // initialize falling piece
  tetris * fp = new tetris;
  initial_tetris( *fp );

  char cmd = getch();
  while(cmd != 'q'){
    // initialize ctr to an invalid value each time
    (*mp).ctr = 'i';

    (*mp).ctr = getch();
    cmd = (*mp).ctr;

    move(*mp, *fp); // move mp & fall fp
    sleep(1);
    elimination(*mp, s);
    boundary_test(*mp, field);
    next(*fp);

    if(GameOver){
	  break;
    }
  }

  // output game status


  // end the game
  delete fp;
  delwin(main_win);
  delwin(score_box);
  system("cls");   // clears the screen
  endwin();        // end NUCURSES mode

  update_record (score, username);

  return 0;
}
