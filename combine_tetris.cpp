#include <iostream>
#include "tetris.h"
using namespace std;

// combine falling tetris and middle tetris to be the new middle tetris
void combine_tetris ( int ** & middle_tetris, int ** falling_tetris, const int falling_height, const int falling_width,
  const int middle_height, const int middle_width, const int middle_coordinates[2], const int falling_coordinates[2] )
{
  int upper_bound, lower_bound, left_bound, right_bound;

  upper_bound = min (falling_coordinates[0], middle_coordinates[0]);
  lower_bound = max (falling_coordinates[0] + falling_height - 1, middle_coordinates[0] + middle_height - 1);
  left_bound = min (falling_coordinates[1], middle_coordinates[1]);
  right_bound = max (falling_coordinates[1] + falling_width - 1, middle_coordinates[1] + middle_width - 1);

  // combined_tetris declaration
  int ** combined_tetris = new int * [lower_bound - upper_bound + 1];
  for (int i = 0; i < lower_bound - upper_bound + 1; i++) {
    combined_tetris[i] = new int[right_bound - left_bound + 1];
  }

  // combined_tetris initialization
 for (int i = 0; i < falling_height; i++) {
   for (int j = 0; j < falling_width; j++) {
     if (falling_tetris[i][j] == 1) {
       combined_tetris[i - upper_bound + falling_coordinates[0]][j - left_bound + falling_coordinates[1]] = 1;
     }
   }
 }

 for (int i = 0; i < middle_height; i++) {
   for (int j = 0; j < middle_width; j++) {
     if (middle_tetris[i][j] == 1) {
       combined_tetris[i - upper_bound + middle_coordinates[0]][j - left_bound + middle_coordinates[1]] = 1;
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
