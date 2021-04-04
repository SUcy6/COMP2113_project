// one error to be solved

#include <vector>
using namespace std;

void elimination ( int ** & middle_tetris, int middle_coordinates[2], int middle_width, int middle_height )
{
  class Elimination {
  public:
    int x;
    int y;
    int side;
  };

  vector<Elimination> eliminations;

  int upper_bound = middle_coordinates[0];
  int lower_bound = middle_coordinates[0] + middle_height - 1;
  int left_bound = middle_coordinates[1];
  int right_bound = middle_coordinates[1] + middle_width - 1;

  // check_tetris declaration: 0 if no tile or checked; 1 for unchecked tile
  int ** check_tetris = new int * [middle_height];
  for (int i = 0; i < middle_height; i++) {
    check_tetris[i] = new int [middle_width];
  }

  // check_tetris initialization
  for (int i = 0; i < middle_height; i++) {
    for (int j = 0; j < middle_width; j++) {
      if (middle_tetris[i][j] == 1) {
        check_tetris[i][j] = 1;
      }
      else {
        check_tetris[i][j] = 0;
      }
    }
  }

  // middle tetris larger than 3x3
  if ( middle_width >= 3 && middle_height >= 3 ) {
    int i = upper_bound, j = left_bound;
    while ( check_tetris[i][j] == 1 && i < lower_bound - 1 && j < right_bound - 1 ) {
      if ( middle_tetris [i][j] == 1 && middle_tetris [i][j + 1] == 1 && middle_tetris [i][j + 2] == 1 &&
      middle_tetris [i + 1][j] == 1 && middle_tetris [i + 1][j + 1] == 1 && middle_tetris [i + 1][j + 2] == 1 &&
    middle_tetris [i + 2][j] == 1 && middle_tetris [i + 2][j + 1] == 1 && middle_tetris [i + 2][j + 2] == 1 ) { // 3x3 tetris existing
        Elimination e;
        e.x = i;
        e.y = j;
        int current_side = 3;
        bool flag = 1;
        // find the biggest square
        while ( i + current_side <= lower_bound && j + current_side <= middle_width ) {
          // check larger square
          for ( int k = 0; k < current_side + 1; k++ ) {
            if ( middle_tetris [i + current_side] [j + k] != 1 ) {
              flag = 0;
              break;
            }
          }
          for ( int k = 0; k < current_side + 1; k++ ) {
            if ( middle_tetris [i + k] [j + current_side] != 1 ) {
              flag = 0;
              break;
            }
          }
          // end the loop if fails
          if ( flag ) {
            current_side += 1;
          }
          else {
            break;
          }
          flag = 1;
        }
        e.side = current_side;
        eliminations.push_back(e);
        for ( int x = i; x < i + current_side - 1; x++ ) {
          for (int y = j; y < j + current_side - 1; y++ ) {
            check_tetris [x][y] = 0;
          }
        }
      }
    }
  }

  // elimination
  for ( int i = 0; i < eliminations.size(); i++ ) {
    for ( int x = eliminations[i].x; x < eliminations[i].x + eliminations[i].size; x++ ) {
      for ( int y = eliminations[i].y; y < eliminations[i].y + eliminations[i].size; y++ ) {
        middle_tetris [x][y] = 0;
      }
    }
  }

  delete[] check_tetris;
}
