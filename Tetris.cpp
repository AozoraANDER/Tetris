#include "Tetris.h"
#include <time.h>
#include <stdlib.h>

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
}

void Tetris::init() { 
    delay = 30;

    srand(time(NULL));
}

void Tetris::play() { 
	init();

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
    update = true;

}

void Tetris::updateWindows() {}

int Tetris::getDelay() { return 0; }

void Tetris::drop() {}

void Tetris::clearLine() {}
