#include "Tetris.h"
#include <time.h>
#include <stdlib.h>
#include "Block.h"
#include <conio.h>
#include <iostream>

#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")

#define MAX_LEVEL 5

const int SPEED_NORMAL[MAX_LEVEL] = {500, 300, 150, 100, 80};
const int SPEED_HARD = 30;

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

    delay = SPEED_NORMAL[0];

    //random seed
    srand(time(NULL));

    //create game window
    initgraph(938,896);

    //load background image
    loadimage(&imgBg, "res/background.png");

    //initialize the data here
    char data[20][10];

    int score = 0;

    for (int i = 0; i < rows; i++) {

        for (int j = 0; j < cols; j++) {
      
            map[i][j] = 0;
        }
    }
    score = 0;
    lineCount = 0;
    level = 1;
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

  drawScore();

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
    delay = SPEED_NORMAL[level-1];
}

void Tetris::clearLine() { 
  int lines = 0;
  int k = rows - 1;
  for (int i = rows - 1; i >= 0; i--) {
    int count = 0;
    for (int j = 0; j < cols; j++) {
      if (map[i][j]) {
        count++;
      }
      map[k][j] = map[i][j];//scan while storage
    }
    if (count < cols) { // if not full then continue
      k--;
    } else {//in case of full
      lines++;
    }
  }
  if (lines > 0) {
    int addScore[4] = {10, 30, 60, 80};
    score += addScore[lines - 1];

    mciSendString("play res/eliminate.mp3",0,0,0);
    update = true;

    //increase level for every 100 points of score
    level = (score + 99)/ 100;
    
  }
}

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

void Tetris::drawScore() {
  char scoreText[32];
  sprintf_s(scoreText, sizeof(scoreText), "% d", score);

  setcolor(RGB(180, 180, 180));

  LOGFONT f;
  gettextstyle(&f);
  f.lfHeight = 60;
  f.lfWeight = 30;
  f.lfQuality = ANTIALIASED_QUALITY;//make the font antialias
  strcpy_s(f.lfFaceName,sizeof(f.lfFaceName),_T("Segoe UI Black"));

  settextstyle(&f);

  outtextxy(670, 727, scoreText);

  sprintf_s(scoreText, sizeof(scoreText), "%d", lineCount);
  gettextstyle(&f);
  int xPos = 224 - f.lfWidth * strlen(scoreText);
  outtextxy(xPos, 817, scoreText);

  sprintf_s(scoreText, sizeof(scoreText), "%d", level);
  outtextxy(224 - 30, 727, scoreText);
}
