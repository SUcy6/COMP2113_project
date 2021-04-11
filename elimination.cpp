#include <vector>
#include "tetris.h"
using namespace std;

void elimination ( mtetris & mp, int ** & middle_tetris, int & score )
{
  class Elimination {
  public:
    int x;
    int y;
    int side;
  };

  vector<Elimination> eliminations;

  int upper_bound = mp.y;
  int lower_bound = mp.y + mp.H - 1;
  int left_bound = mp.x;
  int right_bound = mp.x + mp.W - 1;

  // check_tetris declaration: 0 if no tile or checked; 1 for unchecked tile
  int ** check_tetris = new int * [mp.H];
  for (int i = 0; i < mp.H; i++) {
    check_tetris[i] = new int [mp.W];
  }

  // check_tetris initialization
  for (int i = 0; i < mp.H; i++) {
    for (int j = 0; j < mp.W; j++) {
      if (middle_tetris[i][j] == 1) {
        check_tetris[i][j] = 1;
      }
      else {
        check_tetris[i][j] = 0;
      }
    }
  }

  // middle tetris larger than 3x3
  if ( mp.W >= 3 && mp.H >= 3 ) {
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
        while ( i + current_side <= lower_bound && j + current_side <= mp.W ) {
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
    for ( int x = eliminations[i].x; x < eliminations[i].x + eliminations[i].side; x++ ) {
      for ( int y = eliminations[i].y; y < eliminations[i].y + eliminations[i].side; y++ ) {
        middle_tetris [x][y] = 0;
        score += 10;
      }
    }
  }

  delete[] check_tetris;
}
