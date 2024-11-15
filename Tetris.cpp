#include "Tetris.h"
#include <time.h>
#include <stdlib.h>
#include "Block.h"

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
//void Tetris::inputEvent() {}
void Tetris::keyEvent() { 
    //update = true;

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
      putimage(x, y, imgs[map[i][j]]-1);
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
    curBlock->drop(); 
}

void Tetris::clearLine() {}
