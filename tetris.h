#ifndef TETRIS_H 
#define TETRIS_H
// g++ -pedantic-errors -std=c++11

// the playing field
const int height(32), width(62);
int field[height][width];

// the score field
const int sheight(15), swidth(30);

// required windows
WINDOW * main_win, *score_box;

// game status
bool GameOver = false;
int s;

// tetrominoes
class tetris
{
public:

  // the shape of a tetris piece
  int choice_s, choice_p; 
  int shape[4][4];

  // the coordinate of a tetris piece
  int x;
  int y;
    
  // the height and width of a piece
  int H;
  int W;

  // the user input about tetris movement 
  char ctr;
}

// tetris_piece.cpp
void initial_tetris(tetris * &fp)  // initialize tetris piece

void build_tetris(int &choice_s, int &choice_p, int shape[][4], int &H, int &W);  // build tetris


// playing_field.cpp
void build_boundary(); // build boundary

WINDOW * initial_playwin(int , int ); // initialize playing window

void score(); // update score

void check_complete(); // check whether a 3x3 matrix is formed


// falling_ctr.cpp 
void move(tetris * &mp, tetris * &fp); // move middle piece

void rotate(tetris * &mp, tetris * &fp); // rotate middle piece

void next(); // set next tetris


// check_collision.cpp
bool check_collision ( int ** falling_tetris, int ** middle_tetris, const int falling_coordinates[2], const int falling_width, const int falling_height,
  const int middle_coordinates[2], const int middle_width, const int middle_height, const int orientation );  // check_collision 


// combine_tetris.cpp
void combine_tetris ( int ** & middle_tetris, int ** falling_tetris, const int falling_height, const int falling_width,
  const int middle_height, const int middle_width, const int middle_coordinates[2], const int falling_coordinates[2] ); // combine collide pieces

#endif