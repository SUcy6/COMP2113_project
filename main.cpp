#include <iostream>
using namespace std;

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
