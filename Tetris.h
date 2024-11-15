#pragma once
class Tetris {
 public:

  Tetris(int rows, int cols, int left, int top, int blockSize);
  void init();
  void play();

 private:
  void keyEvent();
  //void inputEvent();

  void updateWindows();
  int getDelay();//return the delta time.
  void drop();
  void clearLine();

  private:
  int delay;
  bool update;

};
