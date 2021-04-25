#include <vector>
#include "tetris.h"
using namespace std;

void elimination ( mtetris & mp, int ** middle_tetris, int & score, WINDOW * main_win )
{
  vector<Elimination> eliminations;

  // boudaries before elimination
  int upper_bound = mp.y;
  int lower_bound = mp.y + mp.H - 1;
  int left_bound = mp.x;
  int right_bound = mp.x + mp.W - 1;

  // check initialization: 0 if no tile or checked; 1 for unchecked tile
  int * check = new int [mp.H * mp.W];

  for (int i = 0; i < mp.H; i++) {
    for (int j = 0; j < mp.W; j++) {
      if (middle_tetris[i][j] == 1) {
        check [i * mp.W + j] = 1;
      }
      else {
        check [i * mp.W + j] = 0;
      }
    }
  }

  // middle tetris larger than 3x3
  if ( mp.W >= 3 && mp.H >= 3 ) {

    for (int i = upper_bound - mp.y; i < mp.H - 2; i++) {
      for (int j = left_bound - mp.x; j < mp.W - 2; j++) {

        if (check [i * mp.W + j] == 1) {

          if ( middle_tetris [i][j] == 1 && middle_tetris [i][j + 1] == 1 && middle_tetris [i][j + 2] == 1 &&
          middle_tetris [i + 1][j] == 1 && middle_tetris [i + 1][j + 1] == 1 && middle_tetris [i + 1][j + 2] == 1 &&
        middle_tetris [i + 2][j] == 1 && middle_tetris [i + 2][j + 1] == 1 && middle_tetris [i + 2][j + 2] == 1 ) { // 3x3 tetris existing

            Elimination e;
            e.y = i; // relative coordinates
            e.x = j;
            int current_side = 3;

            bool flag = 1;

            // find the biggest square
            while ( i + current_side < mp.H && j + current_side < mp.W ) {
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
              if (flag) {
                current_side += 1;
              }
              else {
                break;
              }
              flag = 1;
            }

            // record the elimination square
            e.side = current_side;
            eliminations.push_back(e);

            // label as checked
            for ( int x = i; x < i + current_side - 1; x++ ) {
              for (int y = j; y < j + current_side - 1; y++ ) {
                check [x * mp.W + y] = 0;
              }
            }
          }
        }
      }
    }

    // elimination
    for ( int i = 0; i < eliminations.size(); i++ ) {
      for ( int x = eliminations[i].y; x < eliminations[i].y + eliminations[i].side; x++ ) {
        for ( int y = eliminations[i].x; y < eliminations[i].x + eliminations[i].side; y++ ) {
          if (middle_tetris[x][y] == 1) {
            middle_tetris[x][y] = 0;
            mvwaddch(main_win, (mp).y+x, (mp).x+y, ' ');
            score += 10;
          }
        }
      }
    }

    wrefresh(main_win);

    upper_bound = mp.y + mp.H - 1;
    lower_bound = mp.y;
    left_bound = mp.x + mp.W - 1;
    right_bound = mp.x;

    // update mtetris mp
    for (int i = 0; i < mp.H; i++) {
      for (int j = 0; j < mp.W; j++) {
        if (middle_tetris[i][j] == 1) {
          if (i + mp.y < upper_bound) {
            upper_bound = i + mp.y;
          }
          if (i + mp.y > lower_bound) {
            lower_bound = i + mp.y;
          }
          if (j + mp.x < left_bound) {
            left_bound = j + mp.x;
          }
          if (j + mp.x > right_bound) {
            right_bound = j + mp.x;
          }
        }
      }
    }

    // store new mp information
    int temp_x = left_bound;
    int temp_y = upper_bound;
    int temp_W = right_bound - left_bound + 1;
    int temp_H = lower_bound - upper_bound + 1;

    // new_tetris declaration
    int ** eliminated_tetris = new int * [temp_H];
    for (int i = 0; i < temp_H; i++) {
      eliminated_tetris[i] = new int[temp_W];
    }

    // new_tetris initialization
    for (int i = 0; i < temp_H; i++) {
      for (int j = 0; j < temp_W; j++) {
        //cout << i << ' ' << j << ' ' << i + temp_y - mp.y << ' ' << j + temp_x - mp.x << endl;
        //cout << new_tetris[i][j] << ' ' << middle_tetris[i + temp_y - mp.y][j + temp_x - mp.x] << endl;
        eliminated_tetris[i][j] = middle_tetris[i + temp_y - mp.y][j + temp_x - mp.x];
      }
    }

    middle_tetris = eliminated_tetris;

    // update new mp info
    mp.x = temp_x;
    mp.y = temp_y;
    mp.H = temp_H;
    mp.W = temp_W;
  }
}
