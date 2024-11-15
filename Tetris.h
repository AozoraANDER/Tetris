#pragma once

#include <vector>
#include <graphics.h>
#include "Block.h"

using namespace std;

class Tetris {
 public:

  Tetris(int rows, int cols, int left, int top, int blockSize);
  void init();
  void play();

 private:
  void keyEvent();

  void updateWindows();
  int getDelay();//return the delta time.
  void drop();
  void clearLine();
  void moveLeftRight(int offset);

  private:
  int delay;
  bool update;

  vector<vector<int>> map;//map data
  int cols;
  int rows;
  int leftMargin;
  int topMargin;
  int blockSize;
  IMAGE imgBg;

  Block* curBlock;
  Block* nextBlock;
  Block BackupBlock; //Backup current block to its last legal location 
};
