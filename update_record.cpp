#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

void update_record ( int new_score, string new_username )
{
  ifstream fin;
  ofstream fout;
  fin.open ("gamerecord.txt");

  int lineNum = 1;
  string record;
  bool nameflag = 1; // 1: username not found; 0: username found
  bool scoreflag = 0; // 0: not higher; 1: higher

  // find the line number
  while ( getline (fin, record) && nameflag ) {
    string username;
    int score;
    istringstream iss(record);
    iss >> username >> score;
    if ( username == new_username && new_score > score ) {
      nameflag = 0;
      scoreflag = 1;
      break;
    }
    else if ( username == new_username && new_score <= score ) {
      nameflag = 0;
      break;
    }
    else {
      lineNum += 1;
    }
  }

  fin.close();
  fin.open("gamerecord.txt");

  int n = 1;

  // delete existing record, move remaining contents to temp.txt
  fout.open("temp.txt", ios::app);
  while (getline(fin, record)) {
    if ( n != lineNum || ( n == lineNum && scoreflag == 0 )) {
      fout << record << endl;
    }
    n++;
  }

  // append new record if higher
  if ( scoreflag || nameflag ) {
    fout.close();
    fout.open("temp.txt", ios::app);
    fout << new_username << ' ' << new_score << endl;
    fout.close();
  }

  system("rm gamerecord.txt");

  // remane temp.txt to gamerecords.txt
  system("mv temp.txt gamerecord.txt");

}
