#include <iostream>
#include <ncurses.h>
#include "tetris.h"

using namespace std;

void swap(int &a, int &b){
	int tmp=a;
	a = b;
	b = tmp;
}

void rotate (mtetris mp, int ** middle_tetris, ftetris * & fp, WINDOW * main_win)
{
  int tmp_h = (fp)->H;
  int tmp_w = (fp)->W;

  int tmp [4][4] = {0};
  int tmp_o [4][4] = {0};
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      tmp[i][j] = fp->shape[i][j];
      tmp_o[i][j] = fp->shape[i][j];
    }
  }

  if ((mp).ctr == 'k') {
    // skew symmetry
    for(int i=0; i<4;i++){
      for(int j=0;j<4;j++) {
        tmp[j][i] = fp->shape[i][j];
      }
    }

    // bilateral symmetry
    swap((fp)->H, (fp)->W);
    for(int i=0; i < (fp)->H; i++) {
      for(int j=0; j < (fp)->W; j++) {
        fp->shape[i][(fp)->W-1-j] = tmp[i][j];
      }
    }
  }

  else {
    // 'j'
    // skew symmetry
    for(int i=0; i<4;i++){
      for(int j=0;j<4;j++) {
        tmp[j][i] = fp->shape[i][j];
      }
    }

    // bilateral symmetry
    swap((fp)->H, (fp)->W);
    for(int i=0; i < (fp)->H; i++) {
      for(int j=0; j < (fp)->W; j++) {
        fp->shape[(fp)->H-1-i][j] = tmp[i][j];
      }
    }
  }

  if (check_collision(fp, mp, middle_tetris)){

    // undo rotation
    for(int i=0; i<4; i++){
      for(int j=0; j<4; j++){
        fp->shape[i][j]=tmp_o[i][j];
      }
      (fp)->H = tmp_w;
      (fp)->W = tmp_h;
    }
  }
  else{
    // eliminate #
    for(int i=0; i<4; i++){
      for(int j=0; j<4; j++){
        if(tmp_o[i][j]==1){
          mvwaddch(main_win, (fp)->y+i, (fp)->x+j, ' ');
          wrefresh(main_win);
        }
      }
    }

    // show new #
    for(int i=0; i<fp->H; i++){
      for(int j=0; j<fp->W; j++){
        if(fp->shape[i][j]==1){
          mvwaddch(main_win, (fp)->y+i, (fp)->x+j, '#');
          wrefresh(main_win);
        }
      }
    }
  }
}


void next(ftetris *& fp, WINDOW * main_win)
{
  initial_tetris(fp);
  wrefresh(main_win);
}

void falling(ftetris *& fp, WINDOW * main_win)
{ 
  if ((fp)->choice_p == 1) {
    (fp)->y++;
    for(int i = fp->H-1; i >= 0; i--){
      for(int j = 0; j < (fp)->W; j++){
        if((fp)->shape[i][j] == 1){
          mvwaddch(main_win, (fp)->y+i-1, (fp)->x+j, ' ');
          mvwaddch(main_win, (fp)->y+i, (fp)->x+j, '#');
        }
      }
    }
  }
  else if ((fp)->choice_p == 2) {
    (fp)->y--;
    for(int i = 0; i < (fp)->H; i++){
      for(int j = 0; j < (fp)->W; j++){
        if((fp)->shape[i][j] == 1){
          mvwaddch(main_win, (fp)->y+i+1, (fp)->x+j, ' ');
          mvwaddch(main_win, (fp)->y+i, (fp)->x+j, '#');
        }
      }
    }
  }
  else if ((fp)->choice_p == 3) {
    (fp)->x++;
    for(int i=0; i < (fp)->H; i++){
      for(int j=(fp)->W-1; j >= 0; j--){
        if((fp)->shape[i][j] == 1){
          mvwaddch(main_win, (fp)->y+i, (fp)->x+j-1, ' ');
          mvwaddch(main_win, (fp)->y+i, (fp)->x+j, '#');
        }
      }
    }     
  }
  else if ((fp)->choice_p == 4) {
    (fp)->x--;
    for(int i=0; i < (fp)->H; i++){
      for(int j=0; j < (fp)->W; j++){
        if((fp)->shape[i][j] == 1){
          mvwaddch(main_win, (fp)->y+i, (fp)->x+j+1, ' ');
          mvwaddch(main_win, (fp)->y+i, (fp)->x+j, '#');
        }
      }
    }  
  }
  
  wrefresh(main_win);

}

void move (mtetris & mp, int ** & middle_tetris, ftetris * & fp, WINDOW * main_win)
{
  // left
  if (mp.ctr == 'a'){
    if (check_collision (fp, mp, middle_tetris) == false){
      (mp).x--;
      for(int i=0; i < (mp).H; i++) {
        for(int j=0; j < (mp).W; j++){
          if(middle_tetris[i][j] == 1){
            mvwaddch(main_win, (mp).y+i, (mp).x+j+1, ' ');
            mvwaddch(main_win, (mp).y+i, (mp).x+j, '#');
          }
        }
      }
    }
    else {
      combine_tetris( middle_tetris, fp, mp);
      next(fp, main_win);
    }
    wrefresh(main_win);
  }
  // right
  else if (mp.ctr == 'd') {
    if (check_collision (fp, mp, middle_tetris) == false){
      (mp).x++;
      for(int i=0; i < (mp).H; i++){
        for(int j=(mp).W-1; j >= 0; j--){
          if(middle_tetris[i][j] == 1){
            mvwaddch(main_win, (mp).y+i, (mp).x+j-1, ' ');
            mvwaddch(main_win, (mp).y+i, (mp).x+j, '#');
          }
        }
      }
    }
    else {
      combine_tetris(middle_tetris, fp, mp);
      next(fp, main_win);
    }
    wrefresh(main_win);
  }
  // down
  else if(mp.ctr == 's'){
    if (check_collision (fp, mp, middle_tetris) == true) {
      combine_tetris(middle_tetris, fp, mp);
      next(fp, main_win);
    }
    else{
      mp.y++;
      for(int i = (mp).H-1; i >= 0; i--){
        for(int j = 0; j < (mp).W; j++){
          if(middle_tetris[i][j] == 1){
            mvwaddch(main_win, (mp).y+i-1, (mp).x+j, ' ');
            mvwaddch(main_win, (mp).y+i, (mp).x+j, '#');
          }
        }
      }
    }
    wrefresh(main_win);
  }
  // up
  else if(mp.ctr == 'w'){
    if(check_collision (fp, mp, middle_tetris) == true){
      combine_tetris(middle_tetris, fp, mp);
      next(fp, main_win);
    }
    else{
      mp.y--;
      for(int i = 0; i < (mp).H; i++){
        for(int j = 0; j < (mp).W; j++){
          if(middle_tetris[i][j] == 1){
            mvwaddch(main_win, (mp).y+i+1, (mp).x+j, ' ');
            mvwaddch(main_win, (mp).y+i, (mp).x+j, '#');
          }
        }
      }
    }
    wrefresh(main_win);
  }

  else if (mp.ctr == 'j' || mp.ctr == 'k'){
      rotate (mp, middle_tetris, fp, main_win);
  }
}

bool falling_boundary ( ftetris *& p )
{ 
  bool r;
  switch(p->choice_p){
    case 1:
      if ( (p)->y + p->H > 30 ) {
        r = 1;
      }
      else{
        r=0;
      }
      break;
    
    case 2:
      if ( (p)->y == 0 ) {
        r = 1;
      }
      else{
        r=0;
      }
      break;
    
    case 3:
      if ( (p)->x + p->W > 60 ) {
        r = 1;
      }
      else{
        r=0;
      }
      break;

    case 4:
      if (p->x == 0 ) {
        r = 1;
      }
      else{
        r=0;
      }
      break;
  }
  return r;
}

bool middle_boundary ( mtetris p, int ** middle_tetris )
{
  if (p.H >= 30 || p.W >= 60) {
    return 1;
  }

  for ( int i = 0; i < p.H; i++ ) {
    for ( int j = 0; j < p.W; j++ ) {
      if ( middle_tetris[i][j] == 1 && ( p.x + j == 1 || p.x + j >= 60 || p.y + i == 1 || p.y + i >= 30 )) {
        return 1;
      }
    }
  }
  return 0;
}
