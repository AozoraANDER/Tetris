#pragma once
#include <graphics.h>
#include <vector>

using namespace std;

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
  static IMAGE** getImage();

  Block& operator=(const Block& other);

  bool blockInMap(const vector<vector<int>>& map);
  void solidify(vector<vector<int>>& map);
  int getBlockType();
  //Point* getSmallBlock();

  private:
   int blockType;  // Tetris block Type
   Point smallBlock[4];
   IMAGE *img;

   static IMAGE* imgs[7];
   static int size;
};
