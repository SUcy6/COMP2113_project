#include <iostream>
#include "tetris.h"
using namespace std;

bool check_collision ( int ** falling_tetris, int ** middle_tetris, const int falling_coordinates[2], const int falling_width, const int falling_height,
  const int middle_coordinates[2], const int middle_width, const int middle_height, const int orientation )
{
  // update the falling tetris by the next movement
  int next_coordinates[2];
  // 1: left 2: right 3: up 4: down
  if (orientation == 1) {
    next_coordinates[0] = falling_coordinates[0] - 1;
    next_coordinates[1] = falling_coordinates[1];
  }
  else if (orientation == 2) {
    next_coordinates[0] = falling_coordinates[0] + 1;
    next_coordinates[1] = falling_coordinates[1];
  }
  else if (orientation == 3) {
    next_coordinates[0] = falling_coordinates[0];
    next_coordinates[1] = falling_coordinates[1] - 1;
  }
  else if (orientation == 4) {
    next_coordinates[0] = falling_coordinates[0];
    next_coordinates[1] = falling_coordinates[1] + 1;
  }

  // decide the four boundaries of smaller and larger tetris
  int smaller_left = (middle_width > falling_width) ? next_coordinates[0] : middle_coordinates[0];
  int larger_left = (middle_width > falling_width) ? middle_coordinates[0] : next_coordinates[0];
  int smaller_right = (middle_width > falling_width) ? (next_coordinates[0] + falling_width - 1) : (middle_coordinates[0] + middle_width - 1);
  int larger_right = (middle_width > falling_width) ? (middle_coordinates[0] + middle_width - 1) : (next_coordinates[0] + falling_width - 1);
  int smaller_upper = (middle_height > falling_height) ? next_coordinates[1] : middle_coordinates[1];
  int larger_upper = (middle_height > falling_height) ? middle_coordinates[1] : next_coordinates[1];
  int smaller_lower = (middle_height > falling_height) ? (next_coordinates[1] + falling_height - 1) : (middle_coordinates[1] + middle_height - 1);
  int larger_lower = (middle_height > falling_height) ? (middle_coordinates[1] + middle_height - 1) : (next_coordinates[1] + falling_height - 1);

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
        if (falling_tetris[i - next_coordinates[0]][j - next_coordinates[1]] == 1 && middle_tetris[i - middle_coordinates[0]][j - middle_coordinates[1]] == 1) {
          flag = 1;
          break;
        }
      }
    }
  }

  return flag;
}
