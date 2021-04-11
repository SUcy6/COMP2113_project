#include <iostream>
#include <ncurses.h>
#include "tetris.h"

using namespace std;

void swap(int &a, int &b){
	int tmp=a;
	a = b;
	b = tmp;
}

void rotate(mtetris &mp, int ** middle_tetris, ftetris ** fp)
{
  int tmp[4][4]={0};
  int tmp_o[4][4]={0};
  int tmp_h = (mp).H;
  int tmp_w = (mp).W;

  for(int i=0; i<4;i++){
    for(int j=0;j<4;j++) {    
      tmp_o[i][j] = middle_tetris[i][j];
    }
  }
  
  if ((mp).ctr == 'k') {
    // skew symmetry
    for(int i=0; i<4;i++){
      for(int j=0;j<4;j++) {    
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
  else { // 'j'
    // skew symmetry
    for(int i=0; i<4;i++){
      for(int j=0;j<4;j++) {    
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

  if(check_collision(mp, &fp)){

    // undo rotation
	for(int i=0; i<4; i++){
	  for(int j=0; j<4; j++){
		  middle_tetris[i][j]=tmp_o[i][j];
      }
	  (mp).H = tmp_w;
	  (mp).W = tmp_h;
	}
  }
  else{
    // eliminate #
	for(int i=0; i<4; i++){
		for(int j=0; j<4; j++){
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


void next(ftetris ** fp)
{
  initial_tetris(&fp);
  wrefresh(main_win);
}

void falling(ftetris ** fp)
{ 
  if (fp->choice_p == 1) {
    (*fp).y++;
    for(int i = (*fp).H-1; i >= 0; i--){
	  for(int j = 0; j < (*fp).W; j++){
		if((*fp).shape[i][j] == 1){
		  mvwaddch(main_win, (*fp).y+i-1, (*fp).x+j, ' ');
		  mvwaddch(main_win, (*fp).y+i, (*fp).x+j, '#');
		}
	  }
    }
  }
  else if (fp->choice_p == 2) {
    (*fp).y--;
      for(int i = 0; i < (*fp).W; i++){
		for(int j = 0; j < (*fp).W; j++){
			if((*fp).shape[i][j] == 1){
			  mvwaddch(main_win, (*fp).y+i+1, (*fp).x+j, ' ');
			  mvwaddch(main_win, (*fp).y+i, (*fp).x+j, '#');
			}
		}
      }
  }
  else if (fp->choice_p == 3) {
    (*fp).x++;
	  for(int i=0; i < (*fp).H; i++){
		for(int j=(*fp).W-1; j >= 0; j--){
			if((*fp).shape[i][j] == 1){
			  mvwaddch(main_win, (*fp).y+i, (*fp).x+j-1, ' ');
			  mvwaddch(main_win, (*fp).y+i, (*fp).x+j, '#');
			}
		}
      }     
  }
  else if (fp->choice_p == 4) {
    (*fp).x--;
	  for(int i=0; i < (*fp).H; i++){
		for(int j=0; j < (*fp).W; j++){
			if((*fp).shape[i][j] == 1){
			  mvwaddch(main_win, (*fp).y+i, (*fp).x+j+1, ' ');
			  mvwaddch(main_win, (*fp).y+i, (*fp).x+j, '#');
			}
		}
      }  
  }
  
  if (falling_boundary ( fp )) {
    initial_tetris(fp);
  }
  
}

void move(mtetris &mp, int ** middle_tetris, ftetris ** fp)
{
  if(check_collision(*mp, *fp) == true){
	combine_tetris(*mp, *fp);		
    next(*fp);
  }
  else{
    // free fall
    falling(*fp);
  }
  wrefresh(main_win);
  
  if((*mp).ctr == 'a'){
	if(check_collision(*mp, *fp) == false){
      (*mp).x--;
	  for(int i=0; i < (*mp).H; i++){
		for(int j=0; j < (*mp).W; j++){
			if((*mp).shape[i][j] == 1){
			  mvwaddch(main_win, (*mp).y+i, (*mp).x+j+1, ' ');
			  mvwaddch(main_win, (*mp).y+i, (*mp).x+j, '#');
			}
		}
      } 
	}
    else {
        combine_tetris(*mp, *fp);
        next(*fp);
    }
    wrefresh(main_win);
  }
  
  else if((*mp).ctr == 'd'){
	if(check_collision(*mp, *fp) == false){
      (*mp).x++;
	  for(int i=0; i < (*mp).H; i++){
		for(int j=(*mp).W-1; j >= 0; j--){
			if((*mp).shape[i][j] == 1){
			  mvwaddch(main_win, (*mp).y+i, (*mp).x+j-1, ' ');
			  mvwaddch(main_win, (*mp).y+i, (*mp).x+j, '#');
			}
		}
      }  
	}
    else {
        combine_tetris(*mp, *fp);
        next(*fp);
    }
    wrefresh(main_win);
  }

  else if((*mp).ctr == 's'){
	if(check_collision(*mp, *fp) == true){
	  combine_tetris(*mp, *fp);	
          next(*fp);	
	}
      else{
        (*mp).y++;
        for(int i = (*mp).H-1; i >= 0; i--){
	  for(int j = 0; j < (*mp).W; j++){
			if((*mp).shape[i][j] == 1){
			  mvwaddch(main_win, (*mp).y+i-1, (*mp).x+j, ' ');
			  mvwaddch(main_win, (*mp).y+i, (*mp).x+j, '#');
			}
		}
        }
      }
    wrefresh(main_win);
  }

  else if((*mp).ctr == 'w'){
	if(check_collision(*mp, *fp) == true){
	  combine_tetris(*mp, *fp);	
      next(*fp);	
	}
	else{
      (*mp).y--;
      for(int i = 0; i < (*mp).W; i++){
		for(int j = 0; j < (*mp).W; j++){
			if((*mp).shape[i][j] == 1){
			  mvwaddch(main_win, (*mp).y+i+1, (*mp).x+j, ' ');
			  mvwaddch(main_win, (*mp).y+i, (*mp).x+j, '#');
			}
		}
      }
      }
    wrefresh(main_win);
  }
  
  else if ((*mp).ctr == 'j' || (*mp).ctr == 'k'){
      rotate(*mp, *fp);
  }

}

bool falling_boundary ( ftetris ** p )
{
  for ( int i = 0; i < 4; i++ ) {
    for ( int j = 0; j < 4; j++ ) {
      if ( p.shape[i][j] == 1 && ( p.x + i == 0 || p.x + i > 30 || p.y + j == 0 || p.y + j > 60 )) {
        return 1;
      }
    }
  }
}

bool middle_boundary ( mtetris p, int ** middle_tetris ) 
{
  for ( int i = 0; i < p.H; i++ ) {
    for ( int j = 0; j < p.W; j++ ) {
      if ( middle_tetris[i][j] == 1 && ( p.x + i == 0 || p.x + i > 30 || p.y + j == 0 || p.y + j > 60 )) {
        return 1;
      }
    }
  }
}
