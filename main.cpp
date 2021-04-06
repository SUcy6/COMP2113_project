#include <iostream>
#include <ncurses.h>
#include "tetris.h"
using namespace std;

int main()
{
  // start the game and input game record



  initscr();    // begin NCURSES mode

  curs_set(0);  // set cursor invisible
	
  noecho();     // do not dispaly characters input by user
    
  raw();        // forbid line buffering

  refresh();    // display virtual window

  // the main playing window	
  main_win = initial_playwin(height, width, 0, 0); 
    
  // the score field
  score_box = initial_playwin(sheight, swidth, 0, width+5); 
  // print content in score box
  mvprintw(0, width+5+2, "Username: ");
  mvprintw(2, width+5+2, "Best Score: ");
  mvprintw(4, width+5+2, "Score: ");

  wrefresh(main_win); // update the main playing window
  wrefresh(score_box); // update the score field	
  refresh();

  // initialize middle piece
  tetris * mp = new tetris;
  initial_tetris( *mp );

  // start tetris falling
  tetris * fp = new tetris;
  initial_tetris( *fp );
  
  char cmd = getch();
  while(cmd != 'q'){
    // set a value to ctr each time
    // in case the user does not enter anything
    (*mp).ctr = 't';
    (*mp).ctr = getch();
    cmd = (*mp).ctr;

	move(*mp, *fp);
	check_complete(*mp);
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

  return 0;
}




// for debugging 
int main()
{
  // initial values
  int middle_width = 1, middle_height = 1, falling_width, falling_height, falling_coordinates[2], middle_coordinates[2] = {30, 30};

  // middle tetris declaration
  int ** middle_tetris = new int * [middle_height];
  for (int i = 0; i <= middle_height; i++) {
    middle_tetris[i] = new int[middle_width];
  }

  middle_tetris[0][0] = 1;

  // debugging test (to be modified)
  falling_width = falling_height = 2;
  falling_coordinates[0] = 30;
  falling_coordinates[1] = 30;

  // falling tetris declaration
  int ** falling_tetris = new int * [falling_height];
  for (int i = 0; i <= falling_height; i++) {
    falling_tetris[i] = new int[falling_width];
  }
  
  // falling tetris initialization
  for (int i = 0; i < falling_height; i++) {
    for (int j = 0; j < falling_widtht; j++) {
      falling_tetris[i][j] = 1;
    }
  }

  int orientation = 4; // 1 left 2 right 3 up 4 down
}
