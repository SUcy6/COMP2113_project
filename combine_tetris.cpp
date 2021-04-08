#include "tetris.h"
using namespace std;

// combine falling tetris and middle tetris to be the new middle tetris
void combine_tetris ( int ** & middle_tetris, tetris fp, tetris mp )
{
  int upper_bound, lower_bound, left_bound, right_bound;

  upper_bound = min (fp.y, mp.y);
  lower_bound = max (fp.y + fp.H - 1, mp.y + mp.H - 1);
  left_bound = min (fp.x, mp.x);
  right_bound = max (fp.x + fp.W - 1, mp.x + mp.W - 1);

  // combined_tetris declaration
  int ** combined_tetris = new int * [lower_bound - upper_bound + 1];
  for (int i = 0; i < lower_bound - upper_bound + 1; i++) {
    combined_tetris[i] = new int[right_bound - left_bound + 1];
  }

  // combined_tetris initialization
 for (int i = 0; i < 4; i++) {
   for (int j = 0; j < 4; j++) {
     if (fp.shape[i][j] == 1) {
       combined_tetris[i - upper_bound + fp.y][j - left_bound + fp.x] = 1;
     }
   }
 }

 for (int i = 0; i < mp.H; i++) {
   for (int j = 0; j < mp.W; j++) {
     if (middle_tetris[i][j] == 1) {
       combined_tetris[i - upper_bound + mp.y]][j - left_bound + mp.x] = 1;
     }
   }
 }

  for (int i = 0; i < lower_bound - upper_bound + 1; i++) {
    for (int j = 0; j < right_bound - left_bound + 1; j++) {
      if (combined_tetris[i][j] != 1) {
        combined_tetris[i][j] = 0;
      }
    }
  }

  middle_tetris = combined_tetris;

  delete[] combined_tetris;
}
