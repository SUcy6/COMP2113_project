#include "tetris.h"
#include <algorithm>

using namespace std;

// combine falling tetris and middle tetris to be the new middle tetris
void combine_tetris ( int ** & middle_tetris, ftetris * fp, mtetris & mp )
{
  int upper_bound, lower_bound, left_bound, right_bound;

  upper_bound = min ((fp)->y, mp.y);
  lower_bound = max ((fp)->y + (fp)->H - 1, mp.y + mp.H - 1);
  left_bound = min ((fp)->x, mp.x);
  right_bound = max ((fp)->x + (fp)->W - 1, mp.x + mp.W - 1);

  int temp_w = right_bound - left_bound + 1;
  int temp_h = lower_bound - upper_bound + 1;
  int temp_x = left_bound;
  int temp_y = upper_bound;

  // combined_tetris declaration
  int ** combined_tetris = new int * [temp_h];
  for (int i = 0; i < temp_h; i++) {
    combined_tetris[i] = new int[temp_w];
  }

  // record units from fp
 for (int i = 0; i < fp->H; i++) { // 0, 1
   for (int j = 0; j < fp->W; j++) { // 0, 1
     if ((fp)->shape[i][j] == 1) {
       combined_tetris [i - upper_bound + fp->y][j - left_bound + fp->x] = 1;
     }
   }
 }

 // record units from mp
 for (int i = 0; i < mp.H; i++) {
   for (int j = 0; j < mp.W; j++) {
     if (middle_tetris[i][j] == 1) {
       combined_tetris[i - upper_bound + mp.y][j - left_bound + mp.x] = 1;
     }
   }
 }

 // initial the rest
 for (int i = 0; i < mp.H; i++) {
   for (int j = 0; j < mp.W; j++) {
     if (combined_tetris[i][j] != 1) {
       combined_tetris[i][j] = 0;
     }
   }
 }

  middle_tetris = combined_tetris;

  mp.W = temp_w;
  mp.H = temp_h;
  mp.x = temp_x;
  mp.y = temp_y;
}
