#include <iostream>
#include <ncurses.h>
#include <cstdlib>      // for calling srand(), rand()
#include <ctime>        // for calling time() 
#include "tetris.h"

using namespace std;

void build_tetris(int &choice_s, int &choice_p, int shape[][4], int &H, int &W, int &x, int &y)
{ 
  // build a 4x4 empty matrix to initialize a tetris piece
  for(int i = 0;i < 4; i++){
    for(int j = 0; j < 4; j++){
	  shape[i][j]=0;
    }
  }

  switch(choice_s)
  {
	case 1:	// '####' shape
	  H = 1;
	  W = 4;	
      for (int i = 0; i < 4; i++){
          shape[0][i] = 1;
      }
	  break;

	case 2: 
    //         '#  ' shape
    //          ###   
	  H = 2;
	  W = 3;
	  shape[0][0]=1;
      for (int i = 0; i < 3; i++){
          shape[1][i] = 1;
      }
	  break;

	case 3:
    //         '  #' shape
    //          ### 
	  H = 2;
	  W = 3;	
	  shape[0][2]=1;
	  for (int i = 0; i < 3; i++){
          shape[1][i] = 1;
      }
	  break;

	case 4:
    //        '## ' shape
    //          ##
	  H = 2;
	  W = 3;
	  shape[0][0] = shape[0][1] = shape[1][1] = shape[1][2] = 1;
	  break;
    
    case 5:
    //        ' ##' shape
    //         ##
	  H = 2;
	  W = 3;
	  shape[0][1] = shape[0][2] = shape[1][0] = shape[1][1] = 1;
	  break;

	case 6:	
    //        '##' shape
    //         ##
	  H = 2;
	  W = 2;
	  shape[0][0] = shape[0][1] = shape[1][0] = shape[1][1] = 1;
	  break;

	case 7:	
    //        ' # ' shape
    //         ###
	  H = 2;
	  W = 3;
	  shape[0][1]=1;
	  for (int i = 0; i < 3; i++){
          shape[1][i] = 1;
    }
	  break;
  }

  // set falling tetris position
  switch(choice_p)
  {
    case 1:
      x = 30;
      y = 1;
      break;
    
    case 2:
      x = 30;
      y = 30-H;
      break;
    
    case 3:
      x = 1;
      y = 15;
      break;
    
    case 4:
      x = 60-W;
      y = 15;
      break;
  }
}

void initial_tetris(ftetris * & fp)
{ 
  // get random shape no. and position no. 
  fp->choice_s = rand()%7 + 1;
  fp->choice_p = rand()%4 + 1;
  
  // build a tetris piece
  build_tetris(fp->choice_s, fp->choice_p, fp->shape, fp->H, fp->W, fp->x, fp->y);

}
