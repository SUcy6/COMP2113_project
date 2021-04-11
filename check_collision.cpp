#include "tetris.h"

// check collision
bool check_collision ( tetris * fp, tetris * mp, int ** middle_tetris, int orientation )
{
  // update the falling tetris by the next movement
  int next_coordinates[2];
  // 1: left 2: right 3: up 4: down
  if (orientation == 1) {
    next_coordinates[0] = fp.x - 1;
    next_coordinates[1] = fp.y;
  }
  else if (orientation == 2) {
    next_coordinates[0] = fp.x + 1;
    next_coordinates[1] = fp.y;
  }
  else if (orientation == 3) {
    next_coordinates[0] = fp.x;
    next_coordinates[1] = fp.y - 1;
  }
  else if (orientation == 4) {
    next_coordinates[0] = fp.x;
    next_coordinates[1] = fp.y + 1;
  }

  // decide the four boundaries of smaller and larger tetris
  int smaller_left = (mp.W > fp.W) ? next_coordinates[0] : mp.x;
  int larger_left = (mp.W > fp.W) ? mp.x : next_coordinates[0];
  int smaller_right = (mp.W > fp.W) ? (next_coordinates[0] + fp.W - 1) : (mp.x + mp.W - 1);
  int larger_right = (mp.W > fp.W) ? (mp.x + mp.W - 1) : (next_coordinates[0] + fp.W - 1);
  int smaller_upper = (mp.H > mp.H) ? next_coordinates[1] : mp.y;
  int larger_upper = (mp.H > fp.H) ? mp.y : next_coordinates[1];
  int smaller_lower = (mp.H > fp.H) ? (next_coordinates[1] + fp.H - 1) : (mp.y + mp.H - 1);
  int larger_lower = (mp.H > fp.H) ? (mp.y + mp.H - 1) : (next_coordinates[1] + fp.H - 1);

  int overlapping_right, overlapping_left, overlapping_upper, overlapping_lower;

  // decide the left and right boundaries of overlapping area
  if (larger_left < smaller_right && smaller_left < larger_left) {
    overlapping_left = larger_left;
    overlapping_right = smaller_right;
  }
  else if (smaller_left >= larger_left && smaller_right <= larger_right) {
    overlapping_left = smaller_left;
    overlapping_right = smaller_right;
  }
  else if (smaller_left < larger_right && smaller_right > larger_right) {
    overlapping_left = smaller_left;
    overlapping_right = larger_right;
  }
  else {
    overlapping_left = overlapping_right = -1;
  }

  // decide the upper and lower boundaries of overlapping tetris
  if (larger_upper < smaller_lower && smaller_upper < larger_upper) {
    overlapping_upper = larger_upper;
    overlapping_lower = smaller_lower;
  }
  else if (smaller_upper >= larger_upper && smaller_lower <= larger_lower) {
    overlapping_upper = smaller_upper;
    overlapping_lower = smaller_lower;
  }
  else if (smaller_upper < larger_lower && smaller_lower > larger_lower) {
    overlapping_upper = smaller_upper;
    overlapping_lower = larger_lower;
  }
  else {
    overlapping_upper = overlapping_lower = -1;
  }

  bool flag = 0;

  // check overlapping tiles in the overlapping area
  if (overlapping_upper != -1 && overlapping_left != -1) {
    for (int i = overlapping_upper; i <= overlapping_lower; i++) {
      for (int j = overlapping_left; j <= overlapping_right; j++) {
        if (fp.shape[i - next_coordinates[0]][j - next_coordinates[1]] == 1 && middle_tetris[i - mp.x][j - mp.y] == 1) {
          flag = 1;
          break;
        }
      }
    }
  }

  return flag;
}

