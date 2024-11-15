#include "Tetris.h"
#include <time.h>
#include <stdlib.h>
#include "Block.h"
#include <conio.h>
#include <iostream>

const int SPEED_NORMAL = 500;//0.5s
const int SPEED_HARD = 50;//0.05s

Tetris::Tetris(int rows, int cols, int left, int top, int blockSize) {
  this->rows = rows;
  this->cols = cols;
  leftMargin = left;
  topMargin = top;
  this->blockSize = blockSize;

  /* for (int i = 0; i < rows; i++) {
  
      vector<int> mapRow;
    for (int j = 0; j < cols; j++) {
    
        mapRow.push_back(0);
    }
    map.push_back(mapRow);
    */
    map = vector<vector<int>>(rows, vector<int>(cols, 0));
  }

void Tetris::init() { 

    delay = SPEED_NORMAL;

    //random seed
    srand(time(NULL));

    //create game window
    initgraph(938,896);

    //load background image
    loadimage(&imgBg, "res/bg2.png");

    //initialize the data here
    char data[20][10];

    for (int i = 0; i < rows; i++) {

        for (int j = 0; j < cols; j++) {
      
            map[i][j] = 0;
        }
    }
}

void Tetris::play() { 
	init();
  if (nextBlock != nullptr) {
    delete nextBlock;
  }
    nextBlock = new Block;
    curBlock = nextBlock;
    nextBlock = new Block;

	int timer = 0;

	while (true) {
          keyEvent();  // get input from keyboard

          timer += getDelay();

          if (timer > delay) {
            drop();
            timer = 0;
            update = true;
          }
          if (update) {
            update = false;
            updateWindows();//update screen
            //update game data
            clearLine(); 
          }
        }
}

void Tetris::keyEvent() { 
    //update = true;
    unsigned char ch;
    bool is_rotate = false;
    int dx = 0;
  if (_kbhit()) {
    ch = _getch();

    if (ch == 224) {
    
        ch = _getch();
        switch (ch) { 
        case 72: //up
          is_rotate = true;
          break;
        case 80: //down
          delay = SPEED_HARD;
          break;
        case 75: //left
          dx = -1;
          break;
        case 77: //right
          dx = 1;
          break;
        default:
          break;

      }
    }
  }
  if (is_rotate) {
    rotate();
    update = true;
  }
  if (dx != 0) {
    moveLeftRight(dx);
    update = true;
  }
}

void Tetris::updateWindows() { 
    
  putimage(0, 0, &imgBg);  // draw the background image

  IMAGE **imgs = Block::getImage();

  BeginBatchDraw();

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {

      if (map[i][j] == 0) continue;

      int x = j * blockSize + leftMargin;
      int y = i * blockSize + topMargin;
      putimage(x, y, imgs[map[i][j]-1]);
    }
  }

  curBlock->draw(leftMargin, topMargin);
  nextBlock->draw(689, 150);

  /*Block block;// test block
  block.draw(263,133);*/

  EndBatchDraw();

}

int Tetris::getDelay() { 
    static unsigned long long lastTime = 0;
    unsigned long long currentTime = GetTickCount();

    if (lastTime == 0) {
    
      lastTime = currentTime;
      return 0;
    } else {
    
      int ret = currentTime - lastTime;
      lastTime = currentTime;

      return ret;
    }
    return 0; 
}

void Tetris::drop() { 

    BackupBlock = *curBlock;
    curBlock->drop();

    if (curBlock->blockInMap(map) == false) {
    
        //solidify the block here
      BackupBlock.solidify(map);

      delete curBlock;

      curBlock = nextBlock;
      nextBlock = new Block;
    }
    delay = SPEED_NORMAL;
}

void Tetris::clearLine() {}

void Tetris::moveLeftRight(int offset) { 
    BackupBlock = *curBlock;
    curBlock->moveLeftRight(offset); 

    if (!curBlock->blockInMap(map)) {
      *curBlock = BackupBlock;
    }
}

void Tetris::rotate() { 
    if (curBlock->getBlockType() == 7) return;
    BackupBlock = *curBlock;
    curBlock->rotate();

    if (!curBlock->blockInMap(map)) {
      *curBlock = BackupBlock;
    }
}
