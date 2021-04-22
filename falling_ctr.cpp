#include <iostream>
#include <ncurses.h>
#include "tetris.h"

using namespace std;

void swap(int &a, int &b){
	int tmp=a;
	a = b;
	b = tmp;
}

void rotate(mtetris &mp, int ** middle_tetris, ftetris *& fp, WINDOW * main_win)
{
  int tmp_h = (mp).H;
  int tmp_w = (mp).W;

  int ** tmp = new int * [mp.H];
  int ** tmp_o = new int * [mp.H];
  for (int i = 0; i < mp.H; i++) {
    tmp[i] = new int [mp.W];
    tmp_o[i] = new int [mp.W];
  }

  for(int i=0; i<mp.H;i++){
    for(int j=0;j<mp.W;j++) {  
      tmp[i][j] = middle_tetris[i][j];  
      tmp_o[i][j] = middle_tetris[i][j];
    }
  }
  
  if ((mp).ctr == 'k') {
    // skew symmetry
    for(int i=0; i<mp.H;i++){
      for(int j=0;j<mp.W;j++) {    
        tmp[j][i] = middle_tetris[i][j];
      }
    }

    // bilateral symmetry
    swap((mp).H, (mp).W);
    for(int i=0; i < (mp).H; i++) {
      for(int j=0; j < (mp).W; j++) {
        middle_tetris[i][(mp).W-1-j] = tmp[i][j];
      }
    }
  }

  else { 
    // 'j'
    // skew symmetry
    for(int i=0; i<mp.H;i++){
      for(int j=0;j<mp.W;j++) {    
        tmp[j][i] = middle_tetris[i][j];
      }
    }

    // bilateral symmetry
    swap((mp).H, (mp).W);
    for(int i=0; i < (mp).H; i++) {
      for(int j=0; j < (mp).W; j++) {
        middle_tetris[(mp).H-1-i][j] = tmp[i][j];
      }
    }
  }

  if(check_collision(fp, mp, middle_tetris)){

    // undo rotation
	  for(int i=0; i<mp.H; i++){
	    for(int j=0; j<mp.W; j++){
		    middle_tetris[i][j]=tmp_o[i][j];
      }
	    (mp).H = tmp_w;
	    (mp).W = tmp_h;
	  }
  }
  else{
    // eliminate #
	  for(int i=0; i<mp.H; i++){
		  for(int j=0; j<mp.W; j++){
			  if(tmp_o[i][j]==1){
				  mvwaddch(main_win, (mp).y+i, (mp).x+j, ' ');
				  wrefresh(main_win);
			  }
		  }
    }
    
    // show new #
	  for(int i=0; i<(mp).H; i++){
		  for(int j=0; j<(mp).W; j++){
			  if(middle_tetris[i][j]==1){
				  mvwaddch(main_win, (mp).y+i, (mp).x+j, '#');
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

void move(mtetris &mp, int ** middle_tetris, ftetris *& fp, WINDOW * main_win)
{
  if(mp.ctr == 'a'){
	  if(check_collision(fp, mp, middle_tetris) == false){
      (mp).x--;
	    for(int i=0; i < (mp).H; i++){
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
  
  else if(mp.ctr == 'd'){
	  if(check_collision(fp, mp, middle_tetris) == false){
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

  else if(mp.ctr == 's'){
	  if(check_collision(fp, mp, middle_tetris) == true){
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

  else if(mp.ctr == 'w'){
	  if(check_collision(fp, mp, middle_tetris) == true){
	    combine_tetris(middle_tetris, fp, mp);	
      next(fp, main_win);	
	  }
	  else{
      mp.y--;
      for(int i = 0; i < (mp).W; i++){
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
      rotate(mp, middle_tetris, fp, main_win);
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
  for ( int i = 0; i < p.H; i++ ) {
    for ( int j = 0; j < p.W; j++ ) {
      if ( middle_tetris[i][j] == 1 && ( p.x + j == 0 || p.x + j > 60 || p.y + i == 0 || p.y + i > 30 )) {
        return 1;
      }
    }
  }
  return 0;
}
