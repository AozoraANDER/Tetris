#include "Tetris.h"
#include <time.h>
#include <stdlib.h>

Tetris::Tetris(int rows, int cols, int left, int top, int blockSize) {}

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
