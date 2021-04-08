#ifndef TETRIS_H 
#define TETRIS_H

// the playing field
const int height(32), width(62);
int field[height][width];

// the score field
const int sheight(15), swidth(30);

// required windows
WINDOW * main_win, *score_box;

// game status
bool GameOver = false;
int s(0); //score

// falling tetrominoes
class ftetris
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
};

// middle tetrominoes
class mtetris
{
  public: 
    // the coordinate of middle tetris
    int x;
    int y;
  
    // the height an width of middle tetris
    int H;
    int W;
  
    // the user input about tetris movement 
    char ctr;
};

// tetris_piece.cpp
void initial_tetris(tetris * &fp)  // initialize tetris piece

void build_tetris(int &choice_s, int &choice_p, int shape[][4], int &H, int &W);  // build tetris


// playing_field.cpp
void build_boundary(int field[][62]); // build boundary

WINDOW * initial_playwin(int , int ); // initialize playing window


// elimination.cpp
void elimination(tetris * &mp, int &s); // check whether a 3x3 matrix is formed & update score


// falling_ctr.cpp 
void move(tetris * &mp, tetris * &fp); // move middle piece & fall tetris

void rotate(tetris * &mp, tetris * &fp); // rotate middle piece

void next(tetris * &fp); // set next tetris

void falling(tetris * &fp); // control tetris falling


// check_collision.cpp
bool check_collision ( tetris * &mp, tetris * &fp );  // check_collision 


// combine_tetris.cpp
void combine_tetris ( tetris * &mp, tetris * &fp ); // combine collide pieces

#endif
