#ifndef TETRIS_H 
#define TETRIS_H
#include <ncurses.h>
#include <string>

// the playing field
const int height(32), width(62);
int field[height][width];

// the score field
const int sheight(15), swidth(30);

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
void initial_tetris(ftetris ** fp);  // initialize tetris piece

void build_tetris(int &choice_s, int &choice_p, int shape[][4], int &H, int &W, int &x, int &y);  // build tetris


// playing_field.cpp
void build_boundary(int field[][62]); // build boundary

WINDOW * initial_playwin(int, int, int, int); // initialize playing window


// elimination.cpp
void elimination(mtetris  &mp, int **  middle_tetris, int &s); // check whether a 3x3 matrix is formed & update score


// falling_ctr.cpp 
void move(mtetris  &mp, int ** middle_tetris, ftetris ** fp); // move middle piece & fall tetris

void rotate(mtetris  &mp, ftetris * &fp); // rotate middle piece

void next(ftetris ** fp); // set next tetris

void falling(ftetris * &fp); // control tetris falling

bool falling_boundary ( ftetris * &p );

bool middle_boundary ( mtetris p, int ** middle_tetris );


// check_collision.cpp
bool check_collision ( mtetris  &mp, ftetris * &fp );  // check_collision 


// combine_tetris.cpp
void combine_tetris ( int ** & middle_tetris, mtetris  &mp, ftetris ** fp ); // combine collide pieces

// update_record.cpp 
void update_record ( int new_score, std::string new_username ); // update record

#endif
