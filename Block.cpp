#include "Block.h"
#include <stdlib.h>

IMAGE* Block::imgs[7] = {
    NULL,
}; 

int Block::size = 36;

Block::Block() 
{
  if (imgs[0] == NULL) {
    IMAGE imgTmp;
    loadimage(&imgTmp, "res/tiles.png");

    SetWorkingImage(&imgTmp);
    for (int i = 0; i < 7; i++) {
      imgs[i] = new IMAGE;
      getimage(imgs[i], i*size, 0, size, size);
    }
    SetWorkingImage();
  }

    int blocks[7][4] = {
    1, 3, 5, 7,  // I
    2, 4, 5, 7,  // Type 1 Z
    3, 5, 4, 6,  // Type 2 Z
    3, 5, 4, 7,  // T
    2, 3, 5, 7,  // L
    3, 5, 7, 6,  // J
    2, 3, 4, 5,  // Square
  };
  // randomly generate one kinds of Tetris
    blockType = 1 + rand() % 7;

    // initialize smallBlocks
    for (int i = 0; i < 4; i++) {
      int value = blocks[blockType - 1][i];
      smallBlock[i].row = value / 2;
      smallBlock[i].col = value % 2;
    }

    img = imgs[blockType - 1];

}

void Block::drop() {

    for (auto &block: smallBlock) {
    block.row++;
    }
}

void Block::moveLeftRight(int offset) {}

void Block::rotate() {


}

void Block::draw(int leftMargin, int topMargin) {

    for (int i = 0; i < 4; i++) {
      int x = leftMargin + smallBlock[i].col * size;
      int y = topMargin + smallBlock[i].row * size;
      putimage(x, y, img);

    }
}

IMAGE** Block::getImage() { 
    return imgs; 
}
