#pragma once
#include <graphics.h>

struct Point {
  int row;
  int col;
};

class Block {

 public:
  Block();
  void drop();
  void moveLeftRight(int offset);
  void rotate(); 
  void draw(int leftMargin, int topMargin);

  private:
   int blockType;  // Tetris block Type
   Point smallBlock[4];
   IMAGE *img;

   static IMAGE* imgs[7];
   static int size;
};
