#include <iostream>
#include <ncurses.h>
#include "tetris.h"

using namespace std;

void build_boundary(int field[][62])
{
  for(int i = 0;i < 32; i++){
	for(int j = 0;j < 62; j++){
	  if( i == 0 || i == 31 || j == 0 || j == 61) {
		field[i][j]=1;
	  }
	  else{
		field[i][j]=0;
      }
	}
  }
}

WINDOW * initial_playwin(int Height, int Width, int a, int b)
{
  // use newwin() to build a new window
  // newwin() would return a pointer
  WINDOW * win1;
  win1 = newwin(Height, Width, a, b);
    
  // the window built by newwin() is invisible
  // use box() to add a solid frame
  box(win1, '#', '#');

  wrefresh(win1);  // update the playing window

  return win1;
}


