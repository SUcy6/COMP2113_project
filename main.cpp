#include <iostream>
#include <ncurses.h>
#include <stdlib.h> // for calling system()
#include <unistd.h> // for calling sleep()
#include <cstdlib>      
#include <ctime>        
#include "tetris.h"
#include <fstream>
#include <sstream>
#include <cstring>
#include <string>
#include <sys/time.h>
#include <sys/types.h>

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
      string past_user;
      int past_score;
      iss >> past_user >> past_score;
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

  // required windows
  WINDOW * main_win, *score_box;

  // game status
  bool GameOver = false;
  int s(0); //score
  
  // the main playing window
  main_win = initial_playwin(height, width, 0, 0);
  
  //build_boundary(field);

  // the score field
  score_box = initial_playwin(sheight, swidth, 0, width+5);

  // print content in score box
  mvprintw(1, width+5+2, "Username: %s", username.c_str());
  mvprintw(3, width+5+2, "Best Score: %d", best_score);
  mvprintw(5, width+5+2, "Score: %d", s);

  wrefresh(main_win); // update the main playing window
  wrefresh(score_box); // update the score field
  refresh();

  // initialize middle piece
  mtetris mp;
  mp.H = 1;
  mp.W = 1;
  mp.x = 30;
  mp.y = 15;
	
  int ** middle_tetris = new int * [mp.H];
  for (int i = 0; i < mp.H; i++) {
    middle_tetris[i] = new int [mp.W];
  }
  
  mvwaddch(main_win, height/2, width/2, '#');
  middle_tetris[0][0] = 1;
  wrefresh(main_win);

  // initialize falling piece
  srand((unsigned)time(NULL));
  ftetris * fp = new ftetris;
  initial_tetris( fp );

  while(1){
    char cmd;

    // set waiting time
    fd_set readfd;
    FD_ZERO(&readfd);
    FD_SET(0, &readfd);   
    struct timeval timeout;
    timeout.tv_sec = 0;
    timeout.tv_usec= 200000;

    if (select(1, &readfd, NULL, NULL, &timeout) == 0){

      falling(fp, main_win);
      mvprintw(7, width+5+2, "Position: %d", fp->choice_p);
      wrefresh(score_box);

      if (falling_boundary ( fp )) {
        for(int i=0; i < (fp)->H; i++){
          for(int j=0; j < (fp)->W; j++){
	    if((fp)->shape[i][j] == 1 && (fp)->y+i != 0 && (fp)->x+j != 0 && (fp)->y+i <= 30 && (fp)->x+j != 61){
	      mvwaddch(main_win, (fp)->y+i, (fp)->x+j, ' ');
	    }
          }
        }  
        initial_tetris(fp);
      } 

      if(check_collision(fp, mp, middle_tetris) == true){
	combine_tetris(middle_tetris, fp, mp);	
        next(fp, main_win);	
      }

      refresh();
    }
	      
      if (FD_ISSET(0, &readfd)) {
        cmd = getch();
        if (cmd == 'q') {
        break;
        }
    
        mp.ctr = cmd;
        move(mp, middle_tetris, fp, main_win); // move mp & fall fp
        elimination(mp, middle_tetris, s);
        GameOver = middle_boundary(mp, middle_tetris);
        next(fp);
      }

      if(GameOver){
	break;
      }

    // initialize ctr to an invalid value each time
    (mp).ctr = 'i';
  }

  // output game status
  update_record (s, username);
  
  // end the game
  delete [] middle_tetris;
  delete fp;
  delwin(main_win);
  delwin(score_box);
  system("cls");   // clears the screen
  endwin();        // end NUCURSES mode

  return 0;
}
